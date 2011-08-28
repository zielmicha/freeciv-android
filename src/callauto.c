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
// int get_num_messages(void)
int get_num_messages(void);

static PyObject* python_get_num_messages(PyObject* self, PyObject* args) {
	if(PyArg_ParseTuple(args, "") == 0) return NULL;
	int retval = get_num_messages();
	return Py_BuildValue("i", retval);
}
// struct message *get_message(int message_index)
struct message *get_message(int message_index);

static PyObject* python_get_message(PyObject* self, PyObject* args) {
	int arg_message_index;
	if(PyArg_ParseTuple(args, "i", &arg_message_index) == 0) return NULL;

	struct message* retval = get_message(arg_message_index);
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
// bool can_unit_add_or_build_city(const struct unit *punit)
bool can_unit_add_or_build_city(const struct unit *punit);

static PyObject* python_can_unit_add_or_build_city(PyObject* self, PyObject* args) {
	int arg_punit;
	if(PyArg_ParseTuple(args, "i", &arg_punit) == 0) return NULL;

	bool retval = can_unit_add_or_build_city((struct unit*)arg_punit);
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
	ptr = python_action_button_pressed;
	PY_CALL("ssi", "add_function", "action_button_pressed", (int)ptr);
	ptr = python_free_ref;
	PY_CALL("ssi", "add_function", "free_ref", (int)ptr);
	ptr = python_key_end_turn;
	PY_CALL("ssi", "add_function", "key_end_turn", (int)ptr);
	ptr = python_get_num_messages;
	PY_CALL("ssi", "add_function", "get_num_messages", (int)ptr);
	ptr = python_get_message;
	PY_CALL("ssi", "add_function", "get_message", (int)ptr);
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
	ptr = python_can_unit_add_or_build_city;
	PY_CALL("ssi", "add_function", "can_unit_add_or_build_city", (int)ptr);
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
}
