#include "pyclient.h"
#define errlog(VARS...) do{fprintf(stderr, "%s:%d: ", __FILE__, __LINE__);fprintf(stderr, VARS);fflush(stderr);}while(false)
#define _RESOLV(name) name
#define PY_SETUP_CONST(name) PY_CALL("ssi", "set_const", #name, _RESOLV(name))
#define B2I(B) ((B)?1:0)

#include "repodlgs_common.h"
#include "fc_types.h"
#include "government.h"

enum city_get_mode {
    MODE_PROD,
    MODE_SURPLUS,
    MODE_WASTE
};

PyObject* py_mapper_city(struct city* s) {
    return Py_BuildValue("i", (int)s);
}
PyObject* py_mapper_player(struct player* s){
    return Py_BuildValue("i", 0);
}
PyObject* py_mapper_unit(struct unit* s){
    return Py_BuildValue("i", (int)s);
}
PyObject* get_unit_properties(struct unit* s) {
    struct terrain* t = tile_terrain(s->tile);
    return Py_BuildValue("iiOs", (int)s, (int)s->tile, py_mapper_city(tile_city(s->tile)),
                terrain_rule_name(t));
}

PyObject* py_mapper_tile(struct tile* s){
    return Py_BuildValue("i", (int)s);
}
PyObject* py_mapper_packet_game_load(struct packet_game_load* s){
    return Py_BuildValue("i", 0);
}
PyObject* py_mapper_text_tag_list(struct text_tag_list* s){
    return Py_BuildValue("i", 0);
}
PyObject* py_mapper_unit_list(struct unit_list* s){
    if(s == NULL)
        return Py_BuildValue("");
    int length = unit_list_size(s);
    int i;
    PyObject* list = PyList_New(length);
    for(i=0; i<length; i++) {
        struct unit* u = unit_list_get(s, i);
        PyObject* item = py_mapper_unit(u);
        PyList_SetItem(list, i, item);
    }
    return list;
}
PyObject* py_mapper_color(struct color* s){
    return Py_BuildValue("(iii)", s->r, s->g, s->b);
}
PyObject* py_mapper_packet_endgame_report(struct packet_endgame_report* s) {
    return Py_BuildValue("i", 0);
}
PyObject* py_mapper_message(struct message* s) {
    return Py_BuildValue("(s(iii)i)", s->descr, B2I(s->location_ok), B2I(s->city_ok), B2I(s->visited), (int)s->tile);
}

void recenter_at_tile_int(int tile) {
    if(tile == 0)
        errlog("recenter_at_tile_int: tile == 0\n");
    center_tile_mapcanvas((struct tile*)tile);
}

struct unit_list* get_units_at_tile(int tile) {
    return ((struct tile*)tile)->units;
}

void finish_city_at_unit(int unit, char* title) {
    struct unit* u = (struct unit*)unit;
    finish_city(u->tile, title);
}

void* py_alloc_struct(PyObject* stru) {
    /*PyObject* attr = PyObject_GetAttrString(stru, "_civstruct");
    if(!attr) errlog("No _civstruct member\n");
    long val = PyInt_AsLong(attr);
    if(val == -1 && PyErr_Occurred())
        errlog("_civstruct was not integer\n");
    return (void*)val;*/
    //errlog("refcnt: %d\n", stru->ob_refcnt);
    if(stru == NULL)
        errlog("py_alloc_struct: stru == NULL");
    Py_INCREF(stru);
    return (void*)stru;
}

PyObject* py_get_pyobject(void* stru) {
    if(stru == NULL) {
        Py_RETURN_NONE;
    }
    //errlog("refcnt: %d\n", ((PyObject*)stru) -> ob_refcnt);
    return (PyObject*)stru;
}

const char* get_unit_name(const struct unit* u) {
    return utype_name_translation(unit_type(u));
}

void get_overview_area_dimensions(int *width, int *height) {
    PyObject* ret = PY_CALL("s", "get_overview_area_dimensions");
    if(PyArg_ParseTuple(ret, "ii", width, height) == 0) errlog("Type error\n");
}

const char* gfx_fileextensions_const[5] = {
    "gif",
    "png",
    "jpg",
    "jpeg",
    NULL
};

const char **gfx_fileextensions(void) {
    return gfx_fileextensions_const;
}
void get_sprite_dimensions(struct sprite *sprite, int *width, int *height) { 
    PyObject* ret = PY_CALL("sO", "get_sprite_dimensions", py_get_pyobject(sprite));
    if(PyArg_ParseTuple(ret, "ii", width, height) == 0) errlog("Type error\n");
}
bool city_dialog_is_open(struct city *pcity) {
    PyObject* ret = PY_CALL("sO", "city_dialog_is_open", py_mapper_city(pcity));
    int retval;
    if(PyArg_ParseTuple(ret, "i", &retval) == 0) errlog("Type error\n");
    return (bool)retval;
}
void get_text_size(int *width, int *height, enum client_font font, const char *text) {
    PyObject* ret = PY_CALL("sis", "get_text_size", font, text);
    if(PyArg_ParseTuple(ret, "ii", width, height) == 0) errlog("Type error\n");
    //errlog("TODO: get_text_size\n");
}
void gui_set_rulesets(int num_rulesets, char **rulesets) {
    errlog("TODO: get_set_rulesets\n");
}

void control_mouse_cursor_pos(int x, int y) {
    control_mouse_cursor(canvas_pos_to_tile(x, y));
}

int canvas_pos_to_nearest_tile_id(int x, int y) {
    return (int)canvas_pos_to_nearest_tile(x, y);
}

PyObject* get_map_view_origin() {
    return Py_BuildValue("(ii)", mapview.gui_x0, mapview.gui_y0);
}

typedef void (*idle_callback_func)(void *);
struct IdleCallback {
    idle_callback_func callback;
    void *data;
};
struct IdleCallback idle_callbacks[512];
int idle_callback_count = 0;
void add_idle_callback(void (callback)(void *), void *data) {
    //errlog("add_idle_callback\n");
    if(idle_callback_count >= 512)
        errlog("Too many idle callbacks.\n");
    idle_callbacks[idle_callback_count].data = data;
    idle_callbacks[idle_callback_count].callback = callback;
    idle_callback_count ++;
}
void call_idle_callbacks() {
    int i;
    for(i=0; i<idle_callback_count; i++) {
        idle_callbacks[i].callback(idle_callbacks[i].data);
    }
    idle_callback_count = 0;
}
bool caravan_dialog_is_open(int *unit_id, int *city_id) {
    errlog("TODO: caravan_dialog_is_open\n");
    return false;
}
void popup_pillage_dialog(struct unit *punit, bv_special may_pillage, bv_bases bases) {
    errlog("TODO: popup_pillage_dialog\n");
}

void init_things() {
    //tilespec_try_read("amplio", true);
    errlog("tileset_init: before\n");
    if(tileset == NULL) errlog("tileset is NULL\n");
    tileset_init(tileset);
    errlog("tileset_init\n");
    tileset_load_tiles(tileset);
    errlog("tileset_load_tile\n");
    tileset_use_prefered_theme(tileset);
    errlog("tileset_use_prefered_theme\n");
}

struct canvas* get_mapview_store() {
    return mapview.store;
}

static char** parse_char_seq(PyObject* seq, int *count) {
    if(!seq)
        errlog("Sequence is NULL\n");
    if(!PySequence_Check(seq))
        errlog("Bad type - expected sequence\n");
    *count = PySequence_Size(seq);
    char** vals = malloc((*count) * sizeof(char*));
    int i;
    for(i=0; i<*count; i++) {
        PyObject* item = PySequence_GetItem(seq, i);
        vals[i] = PyString_AsString(item);
        if(!vals[i]) errlog("Found NULL item at %d\n", i);
    }
    return vals;
}

char **get_gui_specific_themes_directories(int *count) {
    PyObject* seq = PY_CALL("s", "get_gui_specific_themes_directories");
    return parse_char_seq(seq, count);
}
char **get_useable_themes_in_directory(const char *directory, int *count) {
    PyObject* seq = PY_CALL("ss", "get_useable_themes_in_directory", directory);
    return parse_char_seq(seq, count);
}

void py_dsend_packet_player_ready(int number, bool ready) {
    dsend_packet_player_ready(&client.conn, number, ready);
}

void key_unit_move_direction(int gui_dir) {
    key_unit_move(gui_dir);
}

void ui_main(int argc, char *argv[]) {
    PY_CALL("s", "ui_main");
}

PyObject* mask_sprite(PyObject* self, PyObject* args) {
    int* surf;
    int* mask;
    int w, h, mx, my, maskw;
    
    if(PyArg_ParseTuple(args, "wiiwiii", &surf, &w, &h, &mask, &maskw, &mx, &my) == 0)
        return NULL;
    
    int x, y;
    for(x=0; x<w; x++) {
        for(y=0; y<h; y++) {
            int rgba = surf[w * y + x];
            int rgb = rgba & 0xFFFFFF;
            int a = (rgba >> 24) & 0xFF;
            
            int smx = x + mx, smy = y + my;
            
            int mask_rgba = mask[smy * maskw + smx];
            int mask_a = (mask_rgba >> 24) & 0xFF;
            int dest_a = mask_a * a / 256;
            
            surf[w * y + x] = (dest_a << 24) | rgb;
        }
    }
    
    return Py_BuildValue("i", 0);
}

struct color *color_alloc(int r, int g, int b) {
    struct color* c = malloc(sizeof(struct color));
    c->r = r;
    c->g = g;
    c->b = b;
    return c;
}

PyObject* python_callback;
typedef PyObject* (*python_func_type)(PyObject*, PyObject*);

static PyObject* call_freeciv(PyObject* self, PyObject* args) {
    int fun;
    PyObject* fargs;
    if(PyArg_ParseTuple(args, "iO", &fun, &fargs) == 0)
        return NULL;
    
    python_func_type func = (python_func_type)fun;
    return func(NULL, fargs);
}

void free_ref(struct sprite* cref) {
    PyObject* ref = (PyObject*)cref;
    if(ref == NULL) {
        errlog("free_ref: ref == NULL\n");
    } else {
        // py_alloc_struct increfs so decref twice
        //if(ref->ob_refcnt != 2)
        //    errlog("free_ref: ref->refcnt == %d\n", ref->ob_refcnt);
        Py_DECREF(ref);
        Py_DECREF(ref);
    }
}

static PyObject* get_overview_size(PyObject* self, PyObject* args) {
    return Py_BuildValue("ii", overview.width, overview.height);
}

int city_get_prod(struct city* city, int mode, int type) {
    if(mode == MODE_PROD)
        return city->prod[type];
    if(mode == MODE_WASTE)
        return city->waste[type];
    if(mode == MODE_SURPLUS)
        return city->surplus[type];
    return FC_INFINITY;
}
int city_get_size(struct city* pCity) {
    return pCity->size;
}

int city_get_shield_stock(struct city* pCity) {
    return pCity->shield_stock;
}

int city_get_citizen_count(struct city* pCity, bool specialist, int type) {
    if(!specialist) {
        return pCity->feel[type][FEELING_FINAL];
    } else {
        return pCity->specialists[type];
    }
}

struct sprite* city_get_production_image(struct city* pCity) {
    int kind = pCity->production.kind;
    if(kind == VUT_UTYPE) {
        struct unit_type *pUnitType = pCity->production.value.utype;
        return get_unittype_sprite(tileset, pUnitType);
    } else {
        struct impr_type *pImprove = pCity->production.value.building;
        return get_building_sprite(tileset, pImprove);
    }
}

int city_get_production_cost(struct city* pCity) {
    int kind = pCity->production.kind;
    if(kind == VUT_UTYPE) {
        struct unit_type *pUnitType = pCity->production.value.utype;
        return utype_build_shield_cost(pUnitType);
    } else {
        struct impr_type *pImprove = pCity->production.value.building;
        return impr_build_shield_cost(pImprove);
    }
}

char* city_get_production_name(struct city* pCity) {
    int kind = pCity->production.kind;
    if(kind == VUT_UTYPE) {
        struct unit_type *pUnitType = pCity->production.value.utype;
        return (char*)utype_name_translation(pUnitType);
    } else {
        struct impr_type *pImprove = pCity->production.value.building;
        return (char*)improvement_name_translation(pImprove);
    }
}

void city_map_click(struct city* pCity, int canvas_x, int canvas_y) {
    int city_x, city_y;
    if (canvas_to_city_pos(&city_x, &city_y, canvas_x, canvas_y)) {
        city_toggle_worker(pCity, city_x, city_y);
    }
}

int city_style_of_nation_id(int id) {
    return city_style_of_nation(nation_by_number(id));
}

void city_change_production_type(struct city* pCity, int type, int value) {
    struct universal u;
    u.kind = type;
    u.value = (universals_u)value;
    city_change_production(pCity, u);
}

char* get_name_of_nation_id(int id) {
    return (char*)nation_plural_translation(nation_by_number(id));
}

int get_playable_nation_count() {
 
  int playable_nation_count = 0;
    
  nations_iterate(pnation) {
    if (pnation->is_playable && !pnation->player && pnation->is_available)
      ++playable_nation_count;        
  } nations_iterate_end;

  return playable_nation_count;
  
}

PyObject* get_techs() {
    PyObject* list = PyList_New(0);
    
    int num, i;
    advance_index_iterate(A_FIRST, i) {
        if (player_invention_reachable(client.conn.playing, i)
            && TECH_KNOWN != player_invention_state(client.conn.playing, i)
            && (11 > (num = num_unknown_techs_for_goal(client.conn.playing, i))
                || i == get_player_research(client.conn.playing)->tech_goal)) {
            
            PyList_Append(list, Py_BuildValue("isi", i, advance_name_translation(advance_by_number(i)), num));
        }
    } advance_index_iterate_end;
    
    return list;
}

PyObject* get_current_tech() {
    return Py_BuildValue("ss",
        advance_name_researching(client.conn.playing),
        get_science_target_text(NULL));
}

void set_tech_goal(int index) {
    dsend_packet_player_tech_goal(&client.conn, index);
}

struct unit_list* get_units_present_in_city(struct city* pCity) {
    if (city_owner(pCity) != client.conn.playing) {
        return pCity->info_units_present;
    } else {
        return pCity->tile->units;
    }
}

// get_nation_leaders

PyObject* get_buildable_improvements_in_city(struct city* pCity) {
    PyObject* list = PyList_New(0);
    bool can_build;
    improvement_iterate(pImprove) {
        can_build = can_player_build_improvement_now(client.conn.playing, pImprove);
        can_build = can_build && can_city_build_improvement_now(pCity, pImprove);
        
        if(can_build) {
            const char* name = improvement_name_translation(pImprove);
            //int turns = city_turns_to_build(pCity, cid_production(cid_encode_building(pImprove)), TRUE);
            int stock = pCity->shield_stock;
            int cost = impr_build_shield_cost(pImprove);
            
            PyList_Append(list, Py_BuildValue(
                "iisiii()", (int)pImprove, VUT_IMPROVEMENT, name, -1, stock, cost
            ));
        }
        
    } improvement_iterate_end;
    
    return list;
}

PyObject* get_buildable_units_in_city(struct city* pCity) {
    PyObject* list = PyList_New(0);
    bool can_build;
    
    unit_type_iterate(un) {
        can_build = can_player_build_unit_now(client.conn.playing, un);
        can_build = can_build && can_city_build_unit_now(pCity, un);
        
        if (can_build) {
            const char* name = utype_name_translation(un);
            int attack = un->attack_strength;
            int defense = un->defense_strength;
            int moves = un->move_rate;
            int stock = pCity->shield_stock;
            int cost = utype_build_shield_cost(un);
            int turns = -1; //city_turns_to_build(pCity, cid_production(cid_encode_unit(un)), TRUE)
            
            PyList_Append(list, Py_BuildValue(
                "iisiii(iii)", (int)un, VUT_UTYPE, name, turns, stock, cost,
                attack, defense, moves
            ));
        }
        
    } unit_type_iterate_end;
    
    return list;
}

void set_nation_settings(int nation, char* leader_name, int sex, int city_style) {
    if(client.conn.playing == NULL) errlog("set_nation_settings: client.conn.playing == NULL\n");
    dsend_packet_nation_select_req(&client.conn,
        player_number(client.conn.playing), nation,
        sex, leader_name, city_style);
}

int get_tax_value(bool luxury) {
    if(!client.conn.playing)
        return 0;
    if(luxury)
        return client.conn.playing->economic.luxury;
    else
        return client.conn.playing->economic.science;
}

int get_gold_amount() {
    if(!client.conn.playing)
        return 0;
    else
        return client.conn.playing->economic.gold;
}

int get_gold_income() {
    int total, tax, entries_used;
    struct improvement_entry entries[B_LAST];
    get_economy_report_data(entries, &entries_used, &total, &tax);
    return tax - total;
}

void set_tax_values(int tax, int luxury, int science) {
    dsend_packet_player_rates(&client.conn, tax, luxury, science);
}

char* get_current_year_name() {
    return (char*)textyear(game.info.year);
}

PyObject* get_governments() {
    
    PyObject* list = PyList_New(0);
    
    government_iterate(pGov) {
        
        PyList_Append(list, Py_BuildValue(
            "isi", (int)pGov, government_name_translation(pGov),
                can_change_to_government(client.conn.playing, pGov)?1:0
        ));
        
    } government_iterate_end;
    
    return list;
}

void py_accept_treaty(int counterpart) {
    dsend_packet_diplomacy_accept_treaty_req(&client.conn, counterpart);
}

void py_cancel_treaty(int counterpart) {
    dsend_packet_diplomacy_cancel_meeting_req(&client.conn, counterpart);
}

void change_government(int gov) {
    set_government_choice((struct government *)gov);
}

int call_callback(int val) {
    return test_glue(val);
}

PyObject* get_cities() {
    PyObject* list = PyList_New(0);
    city_list_iterate(client.conn.playing->cities, pcity) {
	PyList_Append(list, Py_BuildValue("i", pcity));
    } city_list_iterate_end;
    
}

static void py_setup_const() {
    PY_SETUP_CONST(PAGE_START);
    PY_SETUP_CONST(PAGE_SCENARIO);
    PY_SETUP_CONST(PAGE_GAME);
    
    PY_SETUP_CONST(CURSOR_GOTO);
    PY_SETUP_CONST(CURSOR_PATROL);
    PY_SETUP_CONST(CURSOR_PARADROP);
    PY_SETUP_CONST(CURSOR_NUKE);
    PY_SETUP_CONST(CURSOR_SELECT);
    PY_SETUP_CONST(CURSOR_INVALID);
    PY_SETUP_CONST(CURSOR_ATTACK);
    PY_SETUP_CONST(CURSOR_EDIT_PAINT);
    PY_SETUP_CONST(CURSOR_EDIT_ADD);
    PY_SETUP_CONST(CURSOR_WAIT);
    PY_SETUP_CONST(CURSOR_LAST);
    PY_SETUP_CONST(CURSOR_DEFAULT);
    
    PY_SETUP_CONST(DIR8_NORTH);
    PY_SETUP_CONST(DIR8_EAST);
    PY_SETUP_CONST(DIR8_WEST);
    PY_SETUP_CONST(DIR8_SOUTH);
    PY_SETUP_CONST(DIR8_NORTHEAST);
    PY_SETUP_CONST(DIR8_NORTHWEST);
    PY_SETUP_CONST(DIR8_SOUTHEAST);
    PY_SETUP_CONST(DIR8_SOUTHWEST);
    
    PY_SETUP_CONST(O_FOOD);
    PY_SETUP_CONST(O_SHIELD);
    PY_SETUP_CONST(O_TRADE);
    PY_SETUP_CONST(O_GOLD);
    PY_SETUP_CONST(O_SCIENCE);
    PY_SETUP_CONST(O_LUXURY);
    
    PY_SETUP_CONST(MODE_PROD);
    PY_SETUP_CONST(MODE_SURPLUS);
    PY_SETUP_CONST(MODE_WASTE);
    
    PY_SETUP_CONST(FC_INFINITY);
    
    PY_SETUP_CONST(CITIZEN_HAPPY);
    PY_SETUP_CONST(CITIZEN_CONTENT);
    PY_SETUP_CONST(CITIZEN_UNHAPPY);
    PY_SETUP_CONST(CITIZEN_ANGRY);
}

static PyObject* set_callback(PyObject* self, PyObject* args) {
    if(PyArg_ParseTuple(args, "O", &python_callback) == 0)
        return NULL;
    PY_CALL("s", "callback_test");
    py_setup_callglue();
    py_setup_const();
    return Py_BuildValue("i", 0);
}

static PyObject* run_main(PyObject* self, PyObject* args) {
    errlog("run_main\n");
    PyObject* pyargv;
    if(PyArg_ParseTuple(args, "O", &pyargv) == 0)
        return NULL;
    int argc = PySequence_Size(pyargv);
    char** argv = malloc(argc * sizeof(char*));
    int i;
    for(i=0; i<argc; i++) {
        PyObject* item = PyList_GetItem(pyargv, i);
        argv[i] = PyString_AsString(item);
    }
    int result = client_main(argc, argv);
    return Py_BuildValue("i", result);
}

static PyMethodDef FreecivClientMethods[] = {
    {"set_callback", set_callback, METH_VARARGS, "Set Freeciv client callback."},
    {"run_main", run_main, METH_VARARGS, "Run Freeciv Client main."},
    {"call_f", call_freeciv, METH_VARARGS, "Call Freeciv function."},
    {"mask_sprite", mask_sprite, METH_VARARGS, "Mask sprite."},
    {"get_overview_size", get_overview_size, METH_VARARGS, "Get overview size."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initfreecivclient(void)
{
#ifdef ANDROID
    freopen("error.log", "w", stderr);
    setvbuf(stderr, NULL, _IOLBF, 50);
#endif
    errlog("initfreecivclient\n");
    (void) Py_InitModule("freecivclient", FreecivClientMethods);
}

