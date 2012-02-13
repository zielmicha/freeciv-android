#include "pyclient.h"
// void call_idle_callbacks()
void call_idle_callbacks();

static PyObject* python_call_idle_callbacks(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	call_idle_callbacks();
	return Py_BuildValue("i", 0);
}
// bool client_start_server(void)
bool client_start_server(void);

static PyObject* python_client_start_server(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	bool retval = client_start_server();
	return Py_BuildValue("i", (int)retval);
}
// int connect_to_server(const char *username, const char *hostname, int port, char *errbuf, int errbufsize)
int connect_to_server(const char *username, const char *hostname, int port, char *errbuf, int errbufsize);

static PyObject* python_connect_to_server(PyObject* self, PyObject* args) {
	char* arg_username;
	char* arg_hostname;
	int arg_port;
	char* arg_errbuf;
	int arg_errbufsize;
	if(PyArg_ParseTuple(args, "ssisi", &arg_username, &arg_hostname, &arg_port, &arg_errbuf, &arg_errbufsize) == 0) return NULL;





	int retval = connect_to_server(arg_username, arg_hostname, arg_port, arg_errbuf, arg_errbufsize);
	return Py_BuildValue("i", retval);
}
// double real_timer_callback()
double real_timer_callback();

static PyObject* python_real_timer_callback(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	double retval = real_timer_callback();
	return Py_BuildValue("d", retval);
}
// void input_from_server(int fd)
void input_from_server(int fd);

static PyObject* python_input_from_server(PyObject* self, PyObject* args) {
	int arg_fd;
	if(PyArg_ParseTuple(args, "i", &arg_fd) == 0) return NULL;

	input_from_server(arg_fd);
	return Py_BuildValue("i", 0);
}
// void py_dsend_packet_player_ready(int number, bool ready)
void py_dsend_packet_player_ready(int number, bool ready);

static PyObject* python_py_dsend_packet_player_ready(PyObject* self, PyObject* args) {
	int arg_number;
	int arg_ready;
	if(PyArg_ParseTuple(args, "ii", &arg_number, &arg_ready) == 0) return NULL;


	py_dsend_packet_player_ready(arg_number, (bool)arg_ready);
	return Py_BuildValue("i", 0);
}
// void send_chat(char* msg)
void send_chat(char* msg);

static PyObject* python_send_chat(PyObject* self, PyObject* args) {
	char* arg_msg;
	if(PyArg_ParseTuple(args, "s", &arg_msg) == 0) return NULL;

	send_chat(arg_msg);
	return Py_BuildValue("i", 0);
}
// void control_mouse_cursor_pos(int x, int y)
void control_mouse_cursor_pos(int x, int y);

static PyObject* python_control_mouse_cursor_pos(PyObject* self, PyObject* args) {
	int arg_x;
	int arg_y;
	if(PyArg_ParseTuple(args, "ii", &arg_x, &arg_y) == 0) return NULL;


	control_mouse_cursor_pos(arg_x, arg_y);
	return Py_BuildValue("i", 0);
}
// void recenter_button_pressed(int canvas_x, int canvas_y)
void recenter_button_pressed(int canvas_x, int canvas_y);

static PyObject* python_recenter_button_pressed(PyObject* self, PyObject* args) {
	int arg_canvas_x;
	int arg_canvas_y;
	if(PyArg_ParseTuple(args, "ii", &arg_canvas_x, &arg_canvas_y) == 0) return NULL;


	recenter_button_pressed(arg_canvas_x, arg_canvas_y);
	return Py_BuildValue("i", 0);
}
// void recenter_at_tile_int(int tile)
void recenter_at_tile_int(int tile);

static PyObject* python_recenter_at_tile_int(PyObject* self, PyObject* args) {
	int arg_tile;
	if(PyArg_ParseTuple(args, "i", &arg_tile) == 0) return NULL;

	recenter_at_tile_int(arg_tile);
	return Py_BuildValue("i", 0);
}
// void init_mapcanvas_and_overview()
void init_mapcanvas_and_overview();

static PyObject* python_init_mapcanvas_and_overview(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	init_mapcanvas_and_overview();
	return Py_BuildValue("i", 0);
}
// bool map_canvas_resized(int width, int height)
bool map_canvas_resized(int width, int height);

static PyObject* python_map_canvas_resized(PyObject* self, PyObject* args) {
	int arg_width;
	int arg_height;
	if(PyArg_ParseTuple(args, "ii", &arg_width, &arg_height) == 0) return NULL;


	bool retval = map_canvas_resized(arg_width, arg_height);
	return Py_BuildValue("i", (int)retval);
}
// void init_things()
void init_things();

static PyObject* python_init_things(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	init_things();
	return Py_BuildValue("i", 0);
}
// void update_map_canvas_visible()
void update_map_canvas_visible();

static PyObject* python_update_map_canvas_visible(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	update_map_canvas_visible();
	return Py_BuildValue("i", 0);
}
// void update_map_canvas(int canvas_x, int canvas_y, int width, int height)
void update_map_canvas(int canvas_x, int canvas_y, int width, int height);

static PyObject* python_update_map_canvas(PyObject* self, PyObject* args) {
	int arg_canvas_x;
	int arg_canvas_y;
	int arg_width;
	int arg_height;
	if(PyArg_ParseTuple(args, "iiii", &arg_canvas_x, &arg_canvas_y, &arg_width, &arg_height) == 0) return NULL;




	update_map_canvas(arg_canvas_x, arg_canvas_y, arg_width, arg_height);
	return Py_BuildValue("i", 0);
}
// struct canvas* get_mapview_store()
struct canvas* get_mapview_store();

static PyObject* python_get_mapview_store(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	struct canvas* retval = get_mapview_store();
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// void key_unit_move_direction(int gui_dir)
void key_unit_move_direction(int gui_dir);

static PyObject* python_key_unit_move_direction(PyObject* self, PyObject* args) {
	int arg_gui_dir;
	if(PyArg_ParseTuple(args, "i", &arg_gui_dir) == 0) return NULL;

	key_unit_move_direction(arg_gui_dir);
	return Py_BuildValue("i", 0);
}
// void key_unit_goto()
void key_unit_goto();

static PyObject* python_key_unit_goto(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_goto();
	return Py_BuildValue("i", 0);
}
// void update_line(int canvas_x, int canvas_y)
void update_line(int canvas_x, int canvas_y);

static PyObject* python_update_line(PyObject* self, PyObject* args) {
	int arg_canvas_x;
	int arg_canvas_y;
	if(PyArg_ParseTuple(args, "ii", &arg_canvas_x, &arg_canvas_y) == 0) return NULL;


	update_line(arg_canvas_x, arg_canvas_y);
	return Py_BuildValue("i", 0);
}
// void key_cancel_action()
void key_cancel_action();

static PyObject* python_key_cancel_action(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_cancel_action();
	return Py_BuildValue("i", 0);
}
// void key_unit_road()
void key_unit_road();

static PyObject* python_key_unit_road(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_road();
	return Py_BuildValue("i", 0);
}
// void key_unit_build_city()
void key_unit_build_city();

static PyObject* python_key_unit_build_city(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_build_city();
	return Py_BuildValue("i", 0);
}
// void key_unit_trade_route()
void key_unit_trade_route();

static PyObject* python_key_unit_trade_route(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_trade_route();
	return Py_BuildValue("i", 0);
}
// void key_unit_irrigate()
void key_unit_irrigate();

static PyObject* python_key_unit_irrigate(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_irrigate();
	return Py_BuildValue("i", 0);
}
// void key_unit_mine()
void key_unit_mine();

static PyObject* python_key_unit_mine(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_mine();
	return Py_BuildValue("i", 0);
}
// void key_unit_transform()
void key_unit_transform();

static PyObject* python_key_unit_transform(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_transform();
	return Py_BuildValue("i", 0);
}
// void key_unit_fortress()
void key_unit_fortress();

static PyObject* python_key_unit_fortress(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_fortress();
	return Py_BuildValue("i", 0);
}
// void key_unit_fortify()
void key_unit_fortify();

static PyObject* python_key_unit_fortify(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_fortify();
	return Py_BuildValue("i", 0);
}
// void key_unit_airbase()
void key_unit_airbase();

static PyObject* python_key_unit_airbase(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_airbase();
	return Py_BuildValue("i", 0);
}
// void key_unit_pollution()
void key_unit_pollution();

static PyObject* python_key_unit_pollution(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_pollution();
	return Py_BuildValue("i", 0);
}
// void key_unit_paradrop()
void key_unit_paradrop();

static PyObject* python_key_unit_paradrop(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_paradrop();
	return Py_BuildValue("i", 0);
}
// void key_unit_fallout()
void key_unit_fallout();

static PyObject* python_key_unit_fallout(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_fallout();
	return Py_BuildValue("i", 0);
}
// void key_unit_sentry()
void key_unit_sentry();

static PyObject* python_key_unit_sentry(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_sentry();
	return Py_BuildValue("i", 0);
}
// void key_unit_pillage()
void key_unit_pillage();

static PyObject* python_key_unit_pillage(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_pillage();
	return Py_BuildValue("i", 0);
}
// void key_unit_homecity()
void key_unit_homecity();

static PyObject* python_key_unit_homecity(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_homecity();
	return Py_BuildValue("i", 0);
}
// void key_unit_unload_all()
void key_unit_unload_all();

static PyObject* python_key_unit_unload_all(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_unload_all();
	return Py_BuildValue("i", 0);
}
// void key_unit_wait()
void key_unit_wait();

static PyObject* python_key_unit_wait(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_wait();
	return Py_BuildValue("i", 0);
}
// void key_unit_done()
void key_unit_done();

static PyObject* python_key_unit_done(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_done();
	return Py_BuildValue("i", 0);
}
// void key_unit_disband()
void key_unit_disband();

static PyObject* python_key_unit_disband(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_unit_disband();
	return Py_BuildValue("i", 0);
}
// void action_button_pressed(int canvas_x, int canvas_y, int qtype)
void action_button_pressed(int canvas_x, int canvas_y, int qtype);

static PyObject* python_action_button_pressed(PyObject* self, PyObject* args) {
	int arg_canvas_x;
	int arg_canvas_y;
	int arg_qtype;
	if(PyArg_ParseTuple(args, "iii", &arg_canvas_x, &arg_canvas_y, &arg_qtype) == 0) return NULL;



	action_button_pressed(arg_canvas_x, arg_canvas_y, arg_qtype);
	return Py_BuildValue("i", 0);
}
// void free_ref(struct sprite* ref)
void free_ref(struct sprite* ref);

static PyObject* python_free_ref(PyObject* self, PyObject* args) {
	PyObject* arg_ref;
	if(PyArg_ParseTuple(args, "O", &arg_ref) == 0) return NULL;

	struct sprite* argp_ref = py_alloc_struct(arg_ref);
        
	free_ref(argp_ref);
	return Py_BuildValue("i", 0);
}
// void key_end_turn()
void key_end_turn();

static PyObject* python_key_end_turn(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	key_end_turn();
	return Py_BuildValue("i", 0);
}
// int meswin_get_num_messages(void)
int meswin_get_num_messages(void);

static PyObject* python_meswin_get_num_messages(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	int retval = meswin_get_num_messages();
	return Py_BuildValue("i", retval);
}
// const struct message *meswin_get_message(int message_index)
const struct message *meswin_get_message(int message_index);

static PyObject* python_meswin_get_message(PyObject* self, PyObject* args) {
	int arg_message_index;
	if(PyArg_ParseTuple(args, "i", &arg_message_index) == 0) return NULL;

	const struct message* retval = meswin_get_message(arg_message_index);
	return Py_BuildValue("O", py_mapper_message(retval));
}
// void finish_city_at_unit(int unit, char* title)
void finish_city_at_unit(int unit, char* title);

static PyObject* python_finish_city_at_unit(PyObject* self, PyObject* args) {
	int arg_unit;
	char* arg_title;
	if(PyArg_ParseTuple(args, "is", &arg_unit, &arg_title) == 0) return NULL;


	finish_city_at_unit(arg_unit, arg_title);
	return Py_BuildValue("i", 0);
}
// int canvas_pos_to_nearest_tile_id(int x, int y)
int canvas_pos_to_nearest_tile_id(int x, int y);

static PyObject* python_canvas_pos_to_nearest_tile_id(PyObject* self, PyObject* args) {
	int arg_x;
	int arg_y;
	if(PyArg_ParseTuple(args, "ii", &arg_x, &arg_y) == 0) return NULL;


	int retval = canvas_pos_to_nearest_tile_id(arg_x, arg_y);
	return Py_BuildValue("i", retval);
}
// void set_mapview_origin(int gui_x0, int gui_y0)
void set_mapview_origin(int gui_x0, int gui_y0);

static PyObject* python_set_mapview_origin(PyObject* self, PyObject* args) {
	int arg_gui_x0;
	int arg_gui_y0;
	if(PyArg_ParseTuple(args, "ii", &arg_gui_x0, &arg_gui_y0) == 0) return NULL;


	set_mapview_origin(arg_gui_x0, arg_gui_y0);
	return Py_BuildValue("i", 0);
}
// PyObject* get_map_view_origin()
PyObject* get_map_view_origin();

static PyObject* python_get_map_view_origin(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	PyObject* retval = get_map_view_origin();
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// struct unit_list* get_units_in_focus()
struct unit_list* get_units_in_focus();

static PyObject* python_get_units_in_focus(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	struct unit_list* retval = get_units_in_focus();
	return Py_BuildValue("O", py_mapper_unit_list(retval));
}
// struct unit_list* get_units_at_tile(int tile)
struct unit_list* get_units_at_tile(int tile);

static PyObject* python_get_units_at_tile(PyObject* self, PyObject* args) {
	int arg_tile;
	if(PyArg_ParseTuple(args, "i", &arg_tile) == 0) return NULL;

	struct unit_list* retval = get_units_at_tile(arg_tile);
	return Py_BuildValue("O", py_mapper_unit_list(retval));
}
// bool can_unit_do_activity(const struct unit* unit, enum unit_activity activity)
bool can_unit_do_activity(const struct unit* unit, enum unit_activity activity);

static PyObject* python_can_unit_do_activity(PyObject* self, PyObject* args) {
	int arg_unit;
	int arg_activity;
	if(PyArg_ParseTuple(args, "ii", &arg_unit, &arg_activity) == 0) return NULL;


	bool retval = can_unit_do_activity((struct unit*)arg_unit, (enum unit_activity)arg_activity);
	return Py_BuildValue("i", (int)retval);
}
// int tile_activity_time(enum unit_activity activity, const struct tile *ptile)
int tile_activity_time(enum unit_activity activity, const struct tile *ptile);

static PyObject* python_tile_activity_time(PyObject* self, PyObject* args) {
	int arg_activity;
	int arg_ptile;
	if(PyArg_ParseTuple(args, "ii", &arg_activity, &arg_ptile) == 0) return NULL;


	int retval = tile_activity_time((enum unit_activity)arg_activity, (struct tile*)arg_ptile);
	return Py_BuildValue("i", retval);
}
// bool unit_can_add_or_build_city(const struct unit *punit)
bool unit_can_add_or_build_city(const struct unit *punit);

static PyObject* python_unit_can_add_or_build_city(PyObject* self, PyObject* args) {
	int arg_punit;
	if(PyArg_ParseTuple(args, "i", &arg_punit) == 0) return NULL;

	bool retval = unit_can_add_or_build_city((struct unit*)arg_punit);
	return Py_BuildValue("i", (int)retval);
}
// bool unit_can_help_build_wonder_here(const struct unit *punit)
bool unit_can_help_build_wonder_here(const struct unit *punit);

static PyObject* python_unit_can_help_build_wonder_here(PyObject* self, PyObject* args) {
	int arg_punit;
	if(PyArg_ParseTuple(args, "i", &arg_punit) == 0) return NULL;

	bool retval = unit_can_help_build_wonder_here((struct unit*)arg_punit);
	return Py_BuildValue("i", (int)retval);
}
// bool can_unit_paradrop(const struct unit *punit)
bool can_unit_paradrop(const struct unit *punit);

static PyObject* python_can_unit_paradrop(PyObject* self, PyObject* args) {
	int arg_punit;
	if(PyArg_ParseTuple(args, "i", &arg_punit) == 0) return NULL;

	bool retval = can_unit_paradrop((struct unit*)arg_punit);
	return Py_BuildValue("i", (int)retval);
}
// bool can_unit_change_homecity(const struct unit *punit)
bool can_unit_change_homecity(const struct unit *punit);

static PyObject* python_can_unit_change_homecity(PyObject* self, PyObject* args) {
	int arg_punit;
	if(PyArg_ParseTuple(args, "i", &arg_punit) == 0) return NULL;

	bool retval = can_unit_change_homecity((struct unit*)arg_punit);
	return Py_BuildValue("i", (int)retval);
}
// PyObject* get_unit_properties(struct unit* s)
PyObject* get_unit_properties(struct unit* s);

static PyObject* python_get_unit_properties(PyObject* self, PyObject* args) {
	int arg_s;
	if(PyArg_ParseTuple(args, "i", &arg_s) == 0) return NULL;

	PyObject* retval = get_unit_properties((struct unit*)arg_s);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// const char* get_unit_name(const struct unit* u)
const char* get_unit_name(const struct unit* u);

static PyObject* python_get_unit_name(PyObject* self, PyObject* args) {
	int arg_u;
	if(PyArg_ParseTuple(args, "i", &arg_u) == 0) return NULL;

	const char* retval = get_unit_name((struct unit*)arg_u);
	return Py_BuildValue("s", retval);
}
// void request_new_unit_activity(struct unit *punit, enum unit_activity act)
void request_new_unit_activity(struct unit *punit, enum unit_activity act);

static PyObject* python_request_new_unit_activity(PyObject* self, PyObject* args) {
	int arg_punit;
	int arg_act;
	if(PyArg_ParseTuple(args, "ii", &arg_punit, &arg_act) == 0) return NULL;


	request_new_unit_activity((struct unit*)arg_punit, (enum unit_activity)arg_act);
	return Py_BuildValue("i", 0);
}
// void set_unit_focus(struct unit *punit)
void set_unit_focus(struct unit *punit);

static PyObject* python_set_unit_focus(PyObject* self, PyObject* args) {
	int arg_punit;
	if(PyArg_ParseTuple(args, "i", &arg_punit) == 0) return NULL;

	set_unit_focus((struct unit*)arg_punit);
	return Py_BuildValue("i", 0);
}
// void city_dialog_redraw_map(struct city *pcity, struct canvas* canvas)
void city_dialog_redraw_map(struct city *pcity, struct canvas* canvas);

static PyObject* python_city_dialog_redraw_map(PyObject* self, PyObject* args) {
	int arg_pcity;
	PyObject* arg_canvas;
	if(PyArg_ParseTuple(args, "iO", &arg_pcity, &arg_canvas) == 0) return NULL;


	struct canvas* argp_canvas = py_alloc_struct(arg_canvas);
        
	city_dialog_redraw_map((struct city*)arg_pcity, argp_canvas);
	return Py_BuildValue("i", 0);
}
// int get_citydlg_canvas_width()
int get_citydlg_canvas_width();

static PyObject* python_get_citydlg_canvas_width(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	int retval = get_citydlg_canvas_width();
	return Py_BuildValue("i", retval);
}
// int get_citydlg_canvas_height()
int get_citydlg_canvas_height();

static PyObject* python_get_citydlg_canvas_height(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	int retval = get_citydlg_canvas_height();
	return Py_BuildValue("i", retval);
}
// bool city_unhappy(const struct city *pcity)
bool city_unhappy(const struct city *pcity);

static PyObject* python_city_unhappy(PyObject* self, PyObject* args) {
	int arg_pcity;
	if(PyArg_ParseTuple(args, "i", &arg_pcity) == 0) return NULL;

	bool retval = city_unhappy((struct city*)arg_pcity);
	return Py_BuildValue("i", (int)retval);
}
// bool city_happy(const struct city *pcity)
bool city_happy(const struct city *pcity);

static PyObject* python_city_happy(PyObject* self, PyObject* args) {
	int arg_pcity;
	if(PyArg_ParseTuple(args, "i", &arg_pcity) == 0) return NULL;

	bool retval = city_happy((struct city*)arg_pcity);
	return Py_BuildValue("i", (int)retval);
}
// bool city_celebrating(const struct city *pcity)
bool city_celebrating(const struct city *pcity);

static PyObject* python_city_celebrating(PyObject* self, PyObject* args) {
	int arg_pcity;
	if(PyArg_ParseTuple(args, "i", &arg_pcity) == 0) return NULL;

	bool retval = city_celebrating((struct city*)arg_pcity);
	return Py_BuildValue("i", (int)retval);
}
// int city_get_prod(struct city* pCity, int mode, int type)
int city_get_prod(struct city* pCity, int mode, int type);

static PyObject* python_city_get_prod(PyObject* self, PyObject* args) {
	int arg_pCity;
	int arg_mode;
	int arg_type;
	if(PyArg_ParseTuple(args, "iii", &arg_pCity, &arg_mode, &arg_type) == 0) return NULL;



	int retval = city_get_prod((struct city*)arg_pCity, arg_mode, arg_type);
	return Py_BuildValue("i", retval);
}
// int city_get_size(struct city* pCity)
int city_get_size(struct city* pCity);

static PyObject* python_city_get_size(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	int retval = city_get_size((struct city*)arg_pCity);
	return Py_BuildValue("i", retval);
}
// int city_turns_to_grow(const struct city *pCity)
int city_turns_to_grow(const struct city *pCity);

static PyObject* python_city_turns_to_grow(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	int retval = city_turns_to_grow((struct city*)arg_pCity);
	return Py_BuildValue("i", retval);
}
// int city_granary_size(int size)
int city_granary_size(int size);

static PyObject* python_city_granary_size(PyObject* self, PyObject* args) {
	int arg_size;
	if(PyArg_ParseTuple(args, "i", &arg_size) == 0) return NULL;

	int retval = city_granary_size(arg_size);
	return Py_BuildValue("i", retval);
}
// int city_production_turns_to_build(const struct city *pcity, bool include_shield_stock)
int city_production_turns_to_build(const struct city *pcity, bool include_shield_stock);

static PyObject* python_city_production_turns_to_build(PyObject* self, PyObject* args) {
	int arg_pcity;
	int arg_include_shield_stock;
	if(PyArg_ParseTuple(args, "ii", &arg_pcity, &arg_include_shield_stock) == 0) return NULL;


	int retval = city_production_turns_to_build((struct city*)arg_pcity, (bool)arg_include_shield_stock);
	return Py_BuildValue("i", retval);
}
// int city_get_shield_stock(struct city* pCity)
int city_get_shield_stock(struct city* pCity);

static PyObject* python_city_get_shield_stock(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	int retval = city_get_shield_stock((struct city*)arg_pCity);
	return Py_BuildValue("i", retval);
}
// const char* city_name(const struct city* pCity)
const char* city_name(const struct city* pCity);

static PyObject* python_city_name(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	const char* retval = city_name((struct city*)arg_pCity);
	return Py_BuildValue("s", retval);
}
// struct sprite* city_get_production_image(struct city* pCity)
struct sprite* city_get_production_image(struct city* pCity);

static PyObject* python_city_get_production_image(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	struct sprite* retval = city_get_production_image((struct city*)arg_pCity);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// int city_get_production_cost(struct city* pCity)
int city_get_production_cost(struct city* pCity);

static PyObject* python_city_get_production_cost(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	int retval = city_get_production_cost((struct city*)arg_pCity);
	return Py_BuildValue("i", retval);
}
// char* city_get_production_name(struct city* pCity)
char* city_get_production_name(struct city* pCity);

static PyObject* python_city_get_production_name(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	char* retval = city_get_production_name((struct city*)arg_pCity);
	return Py_BuildValue("s", retval);
}
// int city_get_citizen_count(struct city* pCity, bool specialist, int type)
int city_get_citizen_count(struct city* pCity, bool specialist, int type);

static PyObject* python_city_get_citizen_count(PyObject* self, PyObject* args) {
	int arg_pCity;
	int arg_specialist;
	int arg_type;
	if(PyArg_ParseTuple(args, "iii", &arg_pCity, &arg_specialist, &arg_type) == 0) return NULL;



	int retval = city_get_citizen_count((struct city*)arg_pCity, (bool)arg_specialist, arg_type);
	return Py_BuildValue("i", retval);
}
// void city_rotate_specialist(struct city *pcity, int citizen_index)
void city_rotate_specialist(struct city *pcity, int citizen_index);

static PyObject* python_city_rotate_specialist(PyObject* self, PyObject* args) {
	int arg_pcity;
	int arg_citizen_index;
	if(PyArg_ParseTuple(args, "ii", &arg_pcity, &arg_citizen_index) == 0) return NULL;


	city_rotate_specialist((struct city*)arg_pcity, arg_citizen_index);
	return Py_BuildValue("i", 0);
}
// void city_map_click(struct city* pCity, int canvas_x, int canvas_y)
void city_map_click(struct city* pCity, int canvas_x, int canvas_y);

static PyObject* python_city_map_click(PyObject* self, PyObject* args) {
	int arg_pCity;
	int arg_canvas_x;
	int arg_canvas_y;
	if(PyArg_ParseTuple(args, "iii", &arg_pCity, &arg_canvas_x, &arg_canvas_y) == 0) return NULL;



	city_map_click((struct city*)arg_pCity, arg_canvas_x, arg_canvas_y);
	return Py_BuildValue("i", 0);
}
// void city_change_production_type(struct city* pCity, int type, int value)
void city_change_production_type(struct city* pCity, int type, int value);

static PyObject* python_city_change_production_type(PyObject* self, PyObject* args) {
	int arg_pCity;
	int arg_type;
	int arg_value;
	if(PyArg_ParseTuple(args, "iii", &arg_pCity, &arg_type, &arg_value) == 0) return NULL;



	city_change_production_type((struct city*)arg_pCity, arg_type, arg_value);
	return Py_BuildValue("i", 0);
}
// struct unit_list* get_units_present_in_city(struct city* pCity)
struct unit_list* get_units_present_in_city(struct city* pCity);

static PyObject* python_get_units_present_in_city(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	struct unit_list* retval = get_units_present_in_city((struct city*)arg_pCity);
	return Py_BuildValue("O", py_mapper_unit_list(retval));
}
// int get_playable_nation_count()
int get_playable_nation_count();

static PyObject* python_get_playable_nation_count(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	int retval = get_playable_nation_count();
	return Py_BuildValue("i", retval);
}
// int city_style_of_nation_id(int id)
int city_style_of_nation_id(int id);

static PyObject* python_city_style_of_nation_id(PyObject* self, PyObject* args) {
	int arg_id;
	if(PyArg_ParseTuple(args, "i", &arg_id) == 0) return NULL;

	int retval = city_style_of_nation_id(arg_id);
	return Py_BuildValue("i", retval);
}
// char* get_name_of_nation_id(int id)
char* get_name_of_nation_id(int id);

static PyObject* python_get_name_of_nation_id(PyObject* self, PyObject* args) {
	int arg_id;
	if(PyArg_ParseTuple(args, "i", &arg_id) == 0) return NULL;

	char* retval = get_name_of_nation_id(arg_id);
	return Py_BuildValue("s", retval);
}
// void set_nation_settings(int nation, char* leader_name, int sex, int city_style)
void set_nation_settings(int nation, char* leader_name, int sex, int city_style);

static PyObject* python_set_nation_settings(PyObject* self, PyObject* args) {
	int arg_nation;
	char* arg_leader_name;
	int arg_sex;
	int arg_city_style;
	if(PyArg_ParseTuple(args, "isii", &arg_nation, &arg_leader_name, &arg_sex, &arg_city_style) == 0) return NULL;




	set_nation_settings(arg_nation, arg_leader_name, arg_sex, arg_city_style);
	return Py_BuildValue("i", 0);
}
// void disconnect_from_server(void)
void disconnect_from_server(void);

static PyObject* python_disconnect_from_server(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	disconnect_from_server();
	return Py_BuildValue("i", 0);
}
// PyObject* get_buildable_improvements_in_city(struct city* pcity)
PyObject* get_buildable_improvements_in_city(struct city* pcity);

static PyObject* python_get_buildable_improvements_in_city(PyObject* self, PyObject* args) {
	int arg_pcity;
	if(PyArg_ParseTuple(args, "i", &arg_pcity) == 0) return NULL;

	PyObject* retval = get_buildable_improvements_in_city((struct city*)arg_pcity);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// PyObject* get_buildable_units_in_city(struct city* pCity)
PyObject* get_buildable_units_in_city(struct city* pCity);

static PyObject* python_get_buildable_units_in_city(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	PyObject* retval = get_buildable_units_in_city((struct city*)arg_pCity);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// void set_tax_values(int tax, int luxury, int science)
void set_tax_values(int tax, int luxury, int science);

static PyObject* python_set_tax_values(PyObject* self, PyObject* args) {
	int arg_tax;
	int arg_luxury;
	int arg_science;
	if(PyArg_ParseTuple(args, "iii", &arg_tax, &arg_luxury, &arg_science) == 0) return NULL;



	set_tax_values(arg_tax, arg_luxury, arg_science);
	return Py_BuildValue("i", 0);
}
// int get_tax_value(bool luxury)
int get_tax_value(bool luxury);

static PyObject* python_get_tax_value(PyObject* self, PyObject* args) {
	int arg_luxury;
	if(PyArg_ParseTuple(args, "i", &arg_luxury) == 0) return NULL;

	int retval = get_tax_value((bool)arg_luxury);
	return Py_BuildValue("i", retval);
}
// int get_gold_amount()
int get_gold_amount();

static PyObject* python_get_gold_amount(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	int retval = get_gold_amount();
	return Py_BuildValue("i", retval);
}
// int get_gold_income()
int get_gold_income();

static PyObject* python_get_gold_income(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	int retval = get_gold_income();
	return Py_BuildValue("i", retval);
}
// PyObject* get_techs(int level)
PyObject* get_techs(int level);

static PyObject* python_get_techs(PyObject* self, PyObject* args) {
	int arg_level;
	if(PyArg_ParseTuple(args, "i", &arg_level) == 0) return NULL;

	PyObject* retval = get_techs(arg_level);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// void set_tech_goal(int index)
void set_tech_goal(int index);

static PyObject* python_set_tech_goal(PyObject* self, PyObject* args) {
	int arg_index;
	if(PyArg_ParseTuple(args, "i", &arg_index) == 0) return NULL;

	set_tech_goal(arg_index);
	return Py_BuildValue("i", 0);
}
// PyObject* get_current_tech()
PyObject* get_current_tech();

static PyObject* python_get_current_tech(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	PyObject* retval = get_current_tech();
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// char* get_current_year_name()
char* get_current_year_name();

static PyObject* python_get_current_year_name(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	char* retval = get_current_year_name();
	return Py_BuildValue("s", retval);
}
// PyObject* get_governments()
PyObject* get_governments();

static PyObject* python_get_governments(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	PyObject* retval = get_governments();
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// void change_government(int gov)
void change_government(int gov);

static PyObject* python_change_government(PyObject* self, PyObject* args) {
	int arg_gov;
	if(PyArg_ParseTuple(args, "i", &arg_gov) == 0) return NULL;

	change_government(arg_gov);
	return Py_BuildValue("i", 0);
}
// void py_accept_treaty(int counterpart)
void py_accept_treaty(int counterpart);

static PyObject* python_py_accept_treaty(PyObject* self, PyObject* args) {
	int arg_counterpart;
	if(PyArg_ParseTuple(args, "i", &arg_counterpart) == 0) return NULL;

	py_accept_treaty(arg_counterpart);
	return Py_BuildValue("i", 0);
}
// void py_cancel_treaty(int counterpart)
void py_cancel_treaty(int counterpart);

static PyObject* python_py_cancel_treaty(PyObject* self, PyObject* args) {
	int arg_counterpart;
	if(PyArg_ParseTuple(args, "i", &arg_counterpart) == 0) return NULL;

	py_cancel_treaty(arg_counterpart);
	return Py_BuildValue("i", 0);
}
// int call_callback(int val)
int call_callback(int val);

static PyObject* python_call_callback(PyObject* self, PyObject* args) {
	int arg_val;
	if(PyArg_ParseTuple(args, "i", &arg_val) == 0) return NULL;

	int retval = call_callback(arg_val);
	return Py_BuildValue("i", retval);
}
// int city_production_buy_gold_cost(const struct city *pcity)
int city_production_buy_gold_cost(const struct city *pcity);

static PyObject* python_city_production_buy_gold_cost(PyObject* self, PyObject* args) {
	int arg_pcity;
	if(PyArg_ParseTuple(args, "i", &arg_pcity) == 0) return NULL;

	int retval = city_production_buy_gold_cost((struct city*)arg_pcity);
	return Py_BuildValue("i", retval);
}
// bool city_can_buy(const struct city *pcity)
bool city_can_buy(const struct city *pcity);

static PyObject* python_city_can_buy(PyObject* self, PyObject* args) {
	int arg_pcity;
	if(PyArg_ParseTuple(args, "i", &arg_pcity) == 0) return NULL;

	bool retval = city_can_buy((struct city*)arg_pcity);
	return Py_BuildValue("i", (int)retval);
}
// int city_buy_production(struct city *pcity)
int city_buy_production(struct city *pcity);

static PyObject* python_city_buy_production(PyObject* self, PyObject* args) {
	int arg_pcity;
	if(PyArg_ParseTuple(args, "i", &arg_pcity) == 0) return NULL;

	int retval = city_buy_production((struct city*)arg_pcity);
	return Py_BuildValue("i", retval);
}
// bool get_turn_done_button_state(void)
bool get_turn_done_button_state(void);

static PyObject* python_get_turn_done_button_state(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	bool retval = get_turn_done_button_state();
	return Py_BuildValue("i", (int)retval);
}
// PyObject* get_built_improvements_in_city(struct city* pCity)
PyObject* get_built_improvements_in_city(struct city* pCity);

static PyObject* python_get_built_improvements_in_city(PyObject* self, PyObject* args) {
	int arg_pCity;
	if(PyArg_ParseTuple(args, "i", &arg_pCity) == 0) return NULL;

	PyObject* retval = get_built_improvements_in_city((struct city*)arg_pCity);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// struct sprite* get_unit_image(const struct unit* u)
struct sprite* get_unit_image(const struct unit* u);

static PyObject* python_get_unit_image(PyObject* self, PyObject* args) {
	int arg_u;
	if(PyArg_ParseTuple(args, "i", &arg_u) == 0) return NULL;

	struct sprite* retval = get_unit_image((struct unit*)arg_u);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// void authenticate(const char* password)
void authenticate(const char* password);

static PyObject* python_authenticate(PyObject* self, PyObject* args) {
	char* arg_password;
	if(PyArg_ParseTuple(args, "s", &arg_password) == 0) return NULL;

	authenticate(arg_password);
	return Py_BuildValue("i", 0);
}
// PyObject* get_players()
PyObject* get_players();

static PyObject* python_get_players(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	PyObject* retval = get_players();
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// const char *player_name(const struct player *pplayer);
const char *player_name(const struct player *pplayer);;

static PyObject* python_player_name(PyObject* self, PyObject* args) {
	int arg_pplayer;
	if(PyArg_ParseTuple(args, "i", &arg_pplayer) == 0) return NULL;

	const char* retval = player_name((struct player*)arg_pplayer);
	return Py_BuildValue("s", retval);
}
// void set_tech_research(int index)
void set_tech_research(int index);

static PyObject* python_set_tech_research(PyObject* self, PyObject* args) {
	int arg_index;
	if(PyArg_ParseTuple(args, "i", &arg_index) == 0) return NULL;

	set_tech_research(arg_index);
	return Py_BuildValue("i", 0);
}
// bool can_unit_do_activity_base(const struct unit *punit, int base);
bool can_unit_do_activity_base(const struct unit *punit, int base);;

static PyObject* python_can_unit_do_activity_base(PyObject* self, PyObject* args) {
	int arg_punit;
	int arg_base;
	if(PyArg_ParseTuple(args, "ii", &arg_punit, &arg_base) == 0) return NULL;


	bool retval = can_unit_do_activity_base((struct unit*)arg_punit, arg_base);
	return Py_BuildValue("i", (int)retval);
}
// void set_unit_activity_base(struct unit *punit, int base);
void set_unit_activity_base(struct unit *punit, int base);;

static PyObject* python_set_unit_activity_base(PyObject* self, PyObject* args) {
	int arg_punit;
	int arg_base;
	if(PyArg_ParseTuple(args, "ii", &arg_punit, &arg_base) == 0) return NULL;


	set_unit_activity_base((struct unit*)arg_punit, arg_base);
	return Py_BuildValue("i", 0);
}
// int impr_sell_gold(const struct impr_type *pimprove)
int impr_sell_gold(const struct impr_type *pimprove);

static PyObject* python_impr_sell_gold(PyObject* self, PyObject* args) {
	int arg_pimprove;
	if(PyArg_ParseTuple(args, "i", &arg_pimprove) == 0) return NULL;

	int retval = impr_sell_gold((struct impr_type*)arg_pimprove);
	return Py_BuildValue("i", retval);
}
// bool can_city_sell_building(const struct city *pcity, struct impr_type *pimprove);
bool can_city_sell_building(const struct city *pcity, struct impr_type *pimprove);;

static PyObject* python_can_city_sell_building(PyObject* self, PyObject* args) {
	int arg_pcity;
	int arg_pimprove;
	if(PyArg_ParseTuple(args, "ii", &arg_pcity, &arg_pimprove) == 0) return NULL;


	bool retval = can_city_sell_building((struct city*)arg_pcity, (struct impr_type*)arg_pimprove);
	return Py_BuildValue("i", (int)retval);
}
// int city_sell_improvement_type(struct city *pcity, const struct impr_type *pimprove)
int city_sell_improvement_type(struct city *pcity, const struct impr_type *pimprove);

static PyObject* python_city_sell_improvement_type(PyObject* self, PyObject* args) {
	int arg_pcity;
	int arg_pimprove;
	if(PyArg_ParseTuple(args, "ii", &arg_pcity, &arg_pimprove) == 0) return NULL;


	int retval = city_sell_improvement_type((struct city*)arg_pcity, (struct impr_type*)arg_pimprove);
	return Py_BuildValue("i", retval);
}
// const char *nation_adjective_for_player(const struct player *pplayer)
const char *nation_adjective_for_player(const struct player *pplayer);

static PyObject* python_nation_adjective_for_player(PyObject* self, PyObject* args) {
	int arg_pplayer;
	if(PyArg_ParseTuple(args, "i", &arg_pplayer) == 0) return NULL;

	const char* retval = nation_adjective_for_player((struct player*)arg_pplayer);
	return Py_BuildValue("s", retval);
}
// const char *nation_plural_for_player(const struct player *pplayer)
const char *nation_plural_for_player(const struct player *pplayer);

static PyObject* python_nation_plural_for_player(PyObject* self, PyObject* args) {
	int arg_pplayer;
	if(PyArg_ParseTuple(args, "i", &arg_pplayer) == 0) return NULL;

	const char* retval = nation_plural_for_player((struct player*)arg_pplayer);
	return Py_BuildValue("s", retval);
}
// bool can_meet_with_player(const struct player *pplayer)
bool can_meet_with_player(const struct player *pplayer);

static PyObject* python_can_meet_with_player(PyObject* self, PyObject* args) {
	int arg_pplayer;
	if(PyArg_ParseTuple(args, "i", &arg_pplayer) == 0) return NULL;

	bool retval = can_meet_with_player((struct player*)arg_pplayer);
	return Py_BuildValue("i", (int)retval);
}
// void py_init_meeting(int counterpart)
void py_init_meeting(int counterpart);

static PyObject* python_py_init_meeting(PyObject* self, PyObject* args) {
	int arg_counterpart;
	if(PyArg_ParseTuple(args, "i", &arg_counterpart) == 0) return NULL;

	py_init_meeting(arg_counterpart);
	return Py_BuildValue("i", 0);
}
// struct player *player_by_number(const int player_id)
struct player *player_by_number(const int player_id);

static PyObject* python_player_by_number(PyObject* self, PyObject* args) {
	int arg_player_id;
	if(PyArg_ParseTuple(args, "i", &arg_player_id) == 0) return NULL;

	struct player* retval = player_by_number(arg_player_id);
	return Py_BuildValue("O", py_mapper_player(retval));
}
// int player_number(const struct player *pplayer)
int player_number(const struct player *pplayer);

static PyObject* python_player_number(PyObject* self, PyObject* args) {
	int arg_pplayer;
	if(PyArg_ParseTuple(args, "i", &arg_pplayer) == 0) return NULL;

	int retval = player_number((struct player*)arg_pplayer);
	return Py_BuildValue("i", retval);
}
// struct sprite *py_get_nation_flag(const struct player *pplayer)
struct sprite *py_get_nation_flag(const struct player *pplayer);

static PyObject* python_py_get_nation_flag(PyObject* self, PyObject* args) {
	int arg_pplayer;
	if(PyArg_ParseTuple(args, "i", &arg_pplayer) == 0) return NULL;

	struct sprite* retval = py_get_nation_flag((struct player*)arg_pplayer);
	return Py_BuildValue("O", py_get_pyobject(retval));
}
// struct player* get_playing()
struct player* get_playing();

static PyObject* python_get_playing(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	struct player* retval = get_playing();
	return Py_BuildValue("O", py_mapper_player(retval));
}
// void py_add_clause(int counterpart, int giver, int type, int value)
void py_add_clause(int counterpart, int giver, int type, int value);

static PyObject* python_py_add_clause(PyObject* self, PyObject* args) {
	int arg_counterpart;
	int arg_giver;
	int arg_type;
	int arg_value;
	if(PyArg_ParseTuple(args, "iiii", &arg_counterpart, &arg_giver, &arg_type, &arg_value) == 0) return NULL;




	py_add_clause(arg_counterpart, arg_giver, arg_type, arg_value);
	return Py_BuildValue("i", 0);
}
void py_setup_callglue() {
void* ptr;
	ptr = python_call_idle_callbacks;
	PY_CALL("ssi", "add_function", "call_idle_callbacks", (int)ptr);
	ptr = python_client_start_server;
	PY_CALL("ssi", "add_function", "client_start_server", (int)ptr);
	ptr = python_connect_to_server;
	PY_CALL("ssi", "add_function", "connect_to_server", (int)ptr);
	ptr = python_real_timer_callback;
	PY_CALL("ssi", "add_function", "real_timer_callback", (int)ptr);
	ptr = python_input_from_server;
	PY_CALL("ssi", "add_function", "input_from_server", (int)ptr);
	ptr = python_py_dsend_packet_player_ready;
	PY_CALL("ssi", "add_function", "py_dsend_packet_player_ready", (int)ptr);
	ptr = python_send_chat;
	PY_CALL("ssi", "add_function", "send_chat", (int)ptr);
	ptr = python_control_mouse_cursor_pos;
	PY_CALL("ssi", "add_function", "control_mouse_cursor_pos", (int)ptr);
	ptr = python_recenter_button_pressed;
	PY_CALL("ssi", "add_function", "recenter_button_pressed", (int)ptr);
	ptr = python_recenter_at_tile_int;
	PY_CALL("ssi", "add_function", "recenter_at_tile_int", (int)ptr);
	ptr = python_init_mapcanvas_and_overview;
	PY_CALL("ssi", "add_function", "init_mapcanvas_and_overview", (int)ptr);
	ptr = python_map_canvas_resized;
	PY_CALL("ssi", "add_function", "map_canvas_resized", (int)ptr);
	ptr = python_init_things;
	PY_CALL("ssi", "add_function", "init_things", (int)ptr);
	ptr = python_update_map_canvas_visible;
	PY_CALL("ssi", "add_function", "update_map_canvas_visible", (int)ptr);
	ptr = python_update_map_canvas;
	PY_CALL("ssi", "add_function", "update_map_canvas", (int)ptr);
	ptr = python_get_mapview_store;
	PY_CALL("ssi", "add_function", "get_mapview_store", (int)ptr);
	ptr = python_key_unit_move_direction;
	PY_CALL("ssi", "add_function", "key_unit_move_direction", (int)ptr);
	ptr = python_key_unit_goto;
	PY_CALL("ssi", "add_function", "key_unit_goto", (int)ptr);
	ptr = python_update_line;
	PY_CALL("ssi", "add_function", "update_line", (int)ptr);
	ptr = python_key_cancel_action;
	PY_CALL("ssi", "add_function", "key_cancel_action", (int)ptr);
	ptr = python_key_unit_road;
	PY_CALL("ssi", "add_function", "key_unit_road", (int)ptr);
	ptr = python_key_unit_build_city;
	PY_CALL("ssi", "add_function", "key_unit_build_city", (int)ptr);
	ptr = python_key_unit_trade_route;
	PY_CALL("ssi", "add_function", "key_unit_trade_route", (int)ptr);
	ptr = python_key_unit_irrigate;
	PY_CALL("ssi", "add_function", "key_unit_irrigate", (int)ptr);
	ptr = python_key_unit_mine;
	PY_CALL("ssi", "add_function", "key_unit_mine", (int)ptr);
	ptr = python_key_unit_transform;
	PY_CALL("ssi", "add_function", "key_unit_transform", (int)ptr);
	ptr = python_key_unit_fortress;
	PY_CALL("ssi", "add_function", "key_unit_fortress", (int)ptr);
	ptr = python_key_unit_fortify;
	PY_CALL("ssi", "add_function", "key_unit_fortify", (int)ptr);
	ptr = python_key_unit_airbase;
	PY_CALL("ssi", "add_function", "key_unit_airbase", (int)ptr);
	ptr = python_key_unit_pollution;
	PY_CALL("ssi", "add_function", "key_unit_pollution", (int)ptr);
	ptr = python_key_unit_paradrop;
	PY_CALL("ssi", "add_function", "key_unit_paradrop", (int)ptr);
	ptr = python_key_unit_fallout;
	PY_CALL("ssi", "add_function", "key_unit_fallout", (int)ptr);
	ptr = python_key_unit_sentry;
	PY_CALL("ssi", "add_function", "key_unit_sentry", (int)ptr);
	ptr = python_key_unit_pillage;
	PY_CALL("ssi", "add_function", "key_unit_pillage", (int)ptr);
	ptr = python_key_unit_homecity;
	PY_CALL("ssi", "add_function", "key_unit_homecity", (int)ptr);
	ptr = python_key_unit_unload_all;
	PY_CALL("ssi", "add_function", "key_unit_unload_all", (int)ptr);
	ptr = python_key_unit_wait;
	PY_CALL("ssi", "add_function", "key_unit_wait", (int)ptr);
	ptr = python_key_unit_done;
	PY_CALL("ssi", "add_function", "key_unit_done", (int)ptr);
	ptr = python_key_unit_disband;
	PY_CALL("ssi", "add_function", "key_unit_disband", (int)ptr);
	ptr = python_action_button_pressed;
	PY_CALL("ssi", "add_function", "action_button_pressed", (int)ptr);
	ptr = python_free_ref;
	PY_CALL("ssi", "add_function", "free_ref", (int)ptr);
	ptr = python_key_end_turn;
	PY_CALL("ssi", "add_function", "key_end_turn", (int)ptr);
	ptr = python_meswin_get_num_messages;
	PY_CALL("ssi", "add_function", "meswin_get_num_messages", (int)ptr);
	ptr = python_meswin_get_message;
	PY_CALL("ssi", "add_function", "meswin_get_message", (int)ptr);
	ptr = python_finish_city_at_unit;
	PY_CALL("ssi", "add_function", "finish_city_at_unit", (int)ptr);
	ptr = python_canvas_pos_to_nearest_tile_id;
	PY_CALL("ssi", "add_function", "canvas_pos_to_nearest_tile_id", (int)ptr);
	ptr = python_set_mapview_origin;
	PY_CALL("ssi", "add_function", "set_mapview_origin", (int)ptr);
	ptr = python_get_map_view_origin;
	PY_CALL("ssi", "add_function", "get_map_view_origin", (int)ptr);
	ptr = python_get_units_in_focus;
	PY_CALL("ssi", "add_function", "get_units_in_focus", (int)ptr);
	ptr = python_get_units_at_tile;
	PY_CALL("ssi", "add_function", "get_units_at_tile", (int)ptr);
	ptr = python_can_unit_do_activity;
	PY_CALL("ssi", "add_function", "can_unit_do_activity", (int)ptr);
	ptr = python_tile_activity_time;
	PY_CALL("ssi", "add_function", "tile_activity_time", (int)ptr);
	ptr = python_unit_can_add_or_build_city;
	PY_CALL("ssi", "add_function", "unit_can_add_or_build_city", (int)ptr);
	ptr = python_unit_can_help_build_wonder_here;
	PY_CALL("ssi", "add_function", "unit_can_help_build_wonder_here", (int)ptr);
	ptr = python_can_unit_paradrop;
	PY_CALL("ssi", "add_function", "can_unit_paradrop", (int)ptr);
	ptr = python_can_unit_change_homecity;
	PY_CALL("ssi", "add_function", "can_unit_change_homecity", (int)ptr);
	ptr = python_get_unit_properties;
	PY_CALL("ssi", "add_function", "get_unit_properties", (int)ptr);
	ptr = python_get_unit_name;
	PY_CALL("ssi", "add_function", "get_unit_name", (int)ptr);
	ptr = python_request_new_unit_activity;
	PY_CALL("ssi", "add_function", "request_new_unit_activity", (int)ptr);
	ptr = python_set_unit_focus;
	PY_CALL("ssi", "add_function", "set_unit_focus", (int)ptr);
	ptr = python_city_dialog_redraw_map;
	PY_CALL("ssi", "add_function", "city_dialog_redraw_map", (int)ptr);
	ptr = python_get_citydlg_canvas_width;
	PY_CALL("ssi", "add_function", "get_citydlg_canvas_width", (int)ptr);
	ptr = python_get_citydlg_canvas_height;
	PY_CALL("ssi", "add_function", "get_citydlg_canvas_height", (int)ptr);
	ptr = python_city_unhappy;
	PY_CALL("ssi", "add_function", "city_unhappy", (int)ptr);
	ptr = python_city_happy;
	PY_CALL("ssi", "add_function", "city_happy", (int)ptr);
	ptr = python_city_celebrating;
	PY_CALL("ssi", "add_function", "city_celebrating", (int)ptr);
	ptr = python_city_get_prod;
	PY_CALL("ssi", "add_function", "city_get_prod", (int)ptr);
	ptr = python_city_get_size;
	PY_CALL("ssi", "add_function", "city_get_size", (int)ptr);
	ptr = python_city_turns_to_grow;
	PY_CALL("ssi", "add_function", "city_turns_to_grow", (int)ptr);
	ptr = python_city_granary_size;
	PY_CALL("ssi", "add_function", "city_granary_size", (int)ptr);
	ptr = python_city_production_turns_to_build;
	PY_CALL("ssi", "add_function", "city_production_turns_to_build", (int)ptr);
	ptr = python_city_get_shield_stock;
	PY_CALL("ssi", "add_function", "city_get_shield_stock", (int)ptr);
	ptr = python_city_name;
	PY_CALL("ssi", "add_function", "city_name", (int)ptr);
	ptr = python_city_get_production_image;
	PY_CALL("ssi", "add_function", "city_get_production_image", (int)ptr);
	ptr = python_city_get_production_cost;
	PY_CALL("ssi", "add_function", "city_get_production_cost", (int)ptr);
	ptr = python_city_get_production_name;
	PY_CALL("ssi", "add_function", "city_get_production_name", (int)ptr);
	ptr = python_city_get_citizen_count;
	PY_CALL("ssi", "add_function", "city_get_citizen_count", (int)ptr);
	ptr = python_city_rotate_specialist;
	PY_CALL("ssi", "add_function", "city_rotate_specialist", (int)ptr);
	ptr = python_city_map_click;
	PY_CALL("ssi", "add_function", "city_map_click", (int)ptr);
	ptr = python_city_change_production_type;
	PY_CALL("ssi", "add_function", "city_change_production_type", (int)ptr);
	ptr = python_get_units_present_in_city;
	PY_CALL("ssi", "add_function", "get_units_present_in_city", (int)ptr);
	ptr = python_get_playable_nation_count;
	PY_CALL("ssi", "add_function", "get_playable_nation_count", (int)ptr);
	ptr = python_city_style_of_nation_id;
	PY_CALL("ssi", "add_function", "city_style_of_nation_id", (int)ptr);
	ptr = python_get_name_of_nation_id;
	PY_CALL("ssi", "add_function", "get_name_of_nation_id", (int)ptr);
	ptr = python_set_nation_settings;
	PY_CALL("ssi", "add_function", "set_nation_settings", (int)ptr);
	ptr = python_disconnect_from_server;
	PY_CALL("ssi", "add_function", "disconnect_from_server", (int)ptr);
	ptr = python_get_buildable_improvements_in_city;
	PY_CALL("ssi", "add_function", "get_buildable_improvements_in_city", (int)ptr);
	ptr = python_get_buildable_units_in_city;
	PY_CALL("ssi", "add_function", "get_buildable_units_in_city", (int)ptr);
	ptr = python_set_tax_values;
	PY_CALL("ssi", "add_function", "set_tax_values", (int)ptr);
	ptr = python_get_tax_value;
	PY_CALL("ssi", "add_function", "get_tax_value", (int)ptr);
	ptr = python_get_gold_amount;
	PY_CALL("ssi", "add_function", "get_gold_amount", (int)ptr);
	ptr = python_get_gold_income;
	PY_CALL("ssi", "add_function", "get_gold_income", (int)ptr);
	ptr = python_get_techs;
	PY_CALL("ssi", "add_function", "get_techs", (int)ptr);
	ptr = python_set_tech_goal;
	PY_CALL("ssi", "add_function", "set_tech_goal", (int)ptr);
	ptr = python_get_current_tech;
	PY_CALL("ssi", "add_function", "get_current_tech", (int)ptr);
	ptr = python_get_current_year_name;
	PY_CALL("ssi", "add_function", "get_current_year_name", (int)ptr);
	ptr = python_get_governments;
	PY_CALL("ssi", "add_function", "get_governments", (int)ptr);
	ptr = python_change_government;
	PY_CALL("ssi", "add_function", "change_government", (int)ptr);
	ptr = python_py_accept_treaty;
	PY_CALL("ssi", "add_function", "py_accept_treaty", (int)ptr);
	ptr = python_py_cancel_treaty;
	PY_CALL("ssi", "add_function", "py_cancel_treaty", (int)ptr);
	ptr = python_call_callback;
	PY_CALL("ssi", "add_function", "call_callback", (int)ptr);
	ptr = python_city_production_buy_gold_cost;
	PY_CALL("ssi", "add_function", "city_production_buy_gold_cost", (int)ptr);
	ptr = python_city_can_buy;
	PY_CALL("ssi", "add_function", "city_can_buy", (int)ptr);
	ptr = python_city_buy_production;
	PY_CALL("ssi", "add_function", "city_buy_production", (int)ptr);
	ptr = python_get_turn_done_button_state;
	PY_CALL("ssi", "add_function", "get_turn_done_button_state", (int)ptr);
	ptr = python_get_built_improvements_in_city;
	PY_CALL("ssi", "add_function", "get_built_improvements_in_city", (int)ptr);
	ptr = python_get_unit_image;
	PY_CALL("ssi", "add_function", "get_unit_image", (int)ptr);
	ptr = python_authenticate;
	PY_CALL("ssi", "add_function", "authenticate", (int)ptr);
	ptr = python_get_players;
	PY_CALL("ssi", "add_function", "get_players", (int)ptr);
	ptr = python_player_name;
	PY_CALL("ssi", "add_function", "player_name", (int)ptr);
	ptr = python_set_tech_research;
	PY_CALL("ssi", "add_function", "set_tech_research", (int)ptr);
	ptr = python_can_unit_do_activity_base;
	PY_CALL("ssi", "add_function", "can_unit_do_activity_base", (int)ptr);
	ptr = python_set_unit_activity_base;
	PY_CALL("ssi", "add_function", "set_unit_activity_base", (int)ptr);
	ptr = python_impr_sell_gold;
	PY_CALL("ssi", "add_function", "impr_sell_gold", (int)ptr);
	ptr = python_can_city_sell_building;
	PY_CALL("ssi", "add_function", "can_city_sell_building", (int)ptr);
	ptr = python_city_sell_improvement_type;
	PY_CALL("ssi", "add_function", "city_sell_improvement_type", (int)ptr);
	ptr = python_nation_adjective_for_player;
	PY_CALL("ssi", "add_function", "nation_adjective_for_player", (int)ptr);
	ptr = python_nation_plural_for_player;
	PY_CALL("ssi", "add_function", "nation_plural_for_player", (int)ptr);
	ptr = python_can_meet_with_player;
	PY_CALL("ssi", "add_function", "can_meet_with_player", (int)ptr);
	ptr = python_py_init_meeting;
	PY_CALL("ssi", "add_function", "py_init_meeting", (int)ptr);
	ptr = python_player_by_number;
	PY_CALL("ssi", "add_function", "player_by_number", (int)ptr);
	ptr = python_player_number;
	PY_CALL("ssi", "add_function", "player_number", (int)ptr);
	ptr = python_py_get_nation_flag;
	PY_CALL("ssi", "add_function", "py_get_nation_flag", (int)ptr);
	ptr = python_get_playing;
	PY_CALL("ssi", "add_function", "get_playing", (int)ptr);
	ptr = python_py_add_clause;
	PY_CALL("ssi", "add_function", "py_add_clause", (int)ptr);
}
