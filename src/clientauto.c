#include "pyclient.h"
// void update_info_label(void)
void update_info_label(void){
	PyObject* ret = PY_CALL("s", "update_info_label");
	Py_DECREF(ret);
}
// void update_unit_info_label(struct unit_list *punitlist)
void update_unit_info_label(struct unit_list *punitlist){
	PyObject* ret = PY_CALL("sO", "update_unit_info_label", py_mapper_unit_list(punitlist));
	Py_DECREF(ret);
}
// void update_mouse_cursor(enum cursor_type new_cursor_type)
void update_mouse_cursor(enum cursor_type new_cursor_type){
	PyObject* ret = PY_CALL("si", "update_mouse_cursor", (int)new_cursor_type);
	Py_DECREF(ret);
}
// void update_timeout_label(void)
void update_timeout_label(void){
	PyObject* ret = PY_CALL("s", "update_timeout_label");
	Py_DECREF(ret);
}
// void update_turn_done_button(bool do_restore)
void update_turn_done_button(bool do_restore){
	PyObject* ret = PY_CALL("si", "update_turn_done_button", (int)do_restore);
	Py_DECREF(ret);
}
// void set_indicator_icons(struct sprite *bulb, struct sprite *sol, struct sprite *flake, struct sprite *gov)
void set_indicator_icons(struct sprite *bulb, struct sprite *sol, struct sprite *flake, struct sprite *gov){
	PyObject* ret = PY_CALL("sOOOO", "set_indicator_icons", py_get_pyobject(bulb), py_get_pyobject(sol), py_get_pyobject(flake), py_get_pyobject(gov));
	Py_DECREF(ret);
}
// struct canvas *get_overview_window(void)
struct canvas *get_overview_window(void){
	PyObject* ret = PY_CALL("s", "get_overview_window");
	PyObject* retval;
	if(PyArg_ParseTuple(ret, "O", &retval) == 0) fprintf(stderr, "TypeError: bad return value from get_overview_window (expected 'O')\n");
	Py_INCREF(retval);
	Py_DECREF(ret);

	struct canvas* retstru = py_alloc_struct(retval);
	return retstru;

}
// void flush_mapcanvas(int canvas_x, int canvas_y, int pixel_width, int pixel_height)
void flush_mapcanvas(int canvas_x, int canvas_y, int pixel_width, int pixel_height){
	PyObject* ret = PY_CALL("siiii", "flush_mapcanvas", canvas_x, canvas_y, pixel_width, pixel_height);
	Py_DECREF(ret);
}
// void dirty_rect(int canvas_x, int canvas_y, int pixel_width, int pixel_height)
void dirty_rect(int canvas_x, int canvas_y, int pixel_width, int pixel_height){
	PyObject* ret = PY_CALL("siiii", "dirty_rect", canvas_x, canvas_y, pixel_width, pixel_height);
	Py_DECREF(ret);
}
// void dirty_all(void)
void dirty_all(void){
	PyObject* ret = PY_CALL("s", "dirty_all");
	Py_DECREF(ret);
}
// void flush_dirty(void)
void flush_dirty(void){
	PyObject* ret = PY_CALL("s", "flush_dirty");
	Py_DECREF(ret);
}
// void gui_flush(void)
void gui_flush(void){
	PyObject* ret = PY_CALL("s", "gui_flush");
	Py_DECREF(ret);
}
// void update_map_canvas_scrollbars(void)
void update_map_canvas_scrollbars(void){
	PyObject* ret = PY_CALL("s", "update_map_canvas_scrollbars");
	Py_DECREF(ret);
}
// void update_map_canvas_scrollbars_size(void)
void update_map_canvas_scrollbars_size(void){
	PyObject* ret = PY_CALL("s", "update_map_canvas_scrollbars_size");
	Py_DECREF(ret);
}
// void put_cross_overlay_tile(struct tile *ptile)
void put_cross_overlay_tile(struct tile *ptile){
	PyObject* ret = PY_CALL("sO", "put_cross_overlay_tile", py_mapper_tile(ptile));
	Py_DECREF(ret);
}
// void draw_selection_rectangle(int canvas_x, int canvas_y, int w, int h)
void draw_selection_rectangle(int canvas_x, int canvas_y, int w, int h){
	PyObject* ret = PY_CALL("siiii", "draw_selection_rectangle", canvas_x, canvas_y, w, h);
	Py_DECREF(ret);
}
// void tileset_changed(void)
void tileset_changed(void){
	PyObject* ret = PY_CALL("s", "tileset_changed");
	Py_DECREF(ret);
}
// void get_overview_area_dimensions(int *width, int *height)
// ignored

// void overview_size_changed(void)
void overview_size_changed(void){
	PyObject* ret = PY_CALL("s", "overview_size_changed");
	Py_DECREF(ret);
}
// const char **gfx_fileextensions(void)
// ignored

// struct sprite *load_gfxfile(const char *filename)
struct sprite *load_gfxfile(const char *filename){
	PyObject* ret = PY_CALL("ss", "load_gfxfile", filename);
	PyObject* retval;
	if(PyArg_ParseTuple(ret, "O", &retval) == 0) fprintf(stderr, "TypeError: bad return value from load_gfxfile (expected 'O')\n");
	Py_INCREF(retval);
	Py_DECREF(ret);

	struct sprite* retstru = py_alloc_struct(retval);
	return retstru;

}
// struct sprite *create_sprite(int width, int height, struct color *pcolor)
struct sprite *create_sprite(int width, int height, struct color *pcolor){
	PyObject* ret = PY_CALL("siiO", "create_sprite", width, height, py_mapper_color(pcolor));
	PyObject* retval;
	if(PyArg_ParseTuple(ret, "O", &retval) == 0) fprintf(stderr, "TypeError: bad return value from create_sprite (expected 'O')\n");
	Py_INCREF(retval);
	Py_DECREF(ret);

	struct sprite* retstru = py_alloc_struct(retval);
	return retstru;
}
// int color_brightness_score(struct color *pcolor)
int color_brightness_score(struct color *pcolor){
	PyObject* ret = PY_CALL("sO", "color_brightness_score", py_mapper_color(pcolor));
	PyObject* retval;
	if(PyArg_ParseTuple(ret, "O", &retval) == 0) fprintf(stderr, "TypeError: bad return value from color_brightness_score (expected 'O')\n");
	Py_INCREF(retval);
	Py_DECREF(ret);

	struct sprite* retstru = py_alloc_struct(retval);
	return retstru;
}

void real_luaconsole_append(const char *astring,
                            const struct text_tag_list *tags)
{
  /* PORTME */
}

// struct sprite *crop_sprite(struct sprite *source, int x, int y, int width, int height, struct sprite *mask, int mask_offset_x, int mask_offset_y)
struct sprite *crop_sprite(struct sprite *source, int x, int y, int width, int height, struct sprite *mask, int mask_offset_x, int mask_offset_y){
	PyObject* ret = PY_CALL("sOiiiiOii", "crop_sprite", py_get_pyobject(source), x, y, width, height, py_get_pyobject(mask), mask_offset_x, mask_offset_y);
	PyObject* retval;
	if(PyArg_ParseTuple(ret, "O", &retval) == 0) fprintf(stderr, "TypeError: bad return value from crop_sprite (expected 'O')\n");
	Py_INCREF(retval);
	Py_DECREF(ret);

	struct sprite* retstru = py_alloc_struct(retval);
	return retstru;

}
// void get_sprite_dimensions(struct sprite *sprite, int *width, int *height)
// ignored

// void free_sprite(struct sprite *s)
void free_sprite(struct sprite *s){
	PyObject* ret = PY_CALL("sO", "free_sprite", py_get_pyobject(s));
	Py_DECREF(ret);
}
// void update_menus(void)
void update_menus(void){
	PyObject* ret = PY_CALL("s", "update_menus");
	Py_DECREF(ret);
}
// void popup_goto_dialog(void)
void popup_goto_dialog(void){
	PyObject* ret = PY_CALL("s", "popup_goto_dialog");
	Py_DECREF(ret);
}
// void popup_rates_dialog(void)
void popup_rates_dialog(void){
	PyObject* ret = PY_CALL("s", "popup_rates_dialog");
	Py_DECREF(ret);
}
// void voteinfo_gui_update(void)
void voteinfo_gui_update(void){
	PyObject* ret = PY_CALL("s", "voteinfo_gui_update");
	Py_DECREF(ret);
}
// void popdown_city_dialog(struct city *pcity)
void popdown_city_dialog(struct city *pcity){
	PyObject* ret = PY_CALL("sO", "popdown_city_dialog", py_mapper_city(pcity));
	Py_DECREF(ret);
}
// void popdown_all_city_dialogs(void)
void popdown_all_city_dialogs(void){
	PyObject* ret = PY_CALL("s", "popdown_all_city_dialogs");
	Py_DECREF(ret);
}
// void refresh_unit_city_dialogs(struct unit *punit)
void refresh_unit_city_dialogs(struct unit *punit){
	PyObject* ret = PY_CALL("sO", "refresh_unit_city_dialogs", py_mapper_unit(punit));
	Py_DECREF(ret);
}
// bool city_dialog_is_open(struct city *pcity)
// ignored

// struct canvas *canvas_create(int width, int height)
struct canvas *canvas_create(int width, int height){
	PyObject* ret = PY_CALL("sii", "canvas_create", width, height);
	PyObject* retval;
	if(PyArg_ParseTuple(ret, "O", &retval) == 0) fprintf(stderr, "TypeError: bad return value from canvas_create (expected 'O')\n");
	Py_INCREF(retval);
	Py_DECREF(ret);

	struct canvas* retstru = py_alloc_struct(retval);
	return retstru;

}
// void canvas_free(struct canvas *store)
void canvas_free(struct canvas *store){
	PyObject* ret = PY_CALL("sO", "canvas_free", py_get_pyobject(store));
	Py_DECREF(ret);
}
// void canvas_copy(struct canvas *dest, struct canvas *src, int src_x, int src_y, int dest_x, int dest_y, int width, int height)
void canvas_copy(struct canvas *dest, struct canvas *src, int src_x, int src_y, int dest_x, int dest_y, int width, int height){
	PyObject* ret = PY_CALL("sOOiiiiii", "canvas_copy", py_get_pyobject(dest), py_get_pyobject(src), src_x, src_y, dest_x, dest_y, width, height);
	Py_DECREF(ret);
}
// void canvas_put_sprite(struct canvas *pcanvas, int canvas_x, int canvas_y, struct sprite *sprite, int offset_x, int offset_y, int width, int height)
void canvas_put_sprite(struct canvas *pcanvas, int canvas_x, int canvas_y, struct sprite *sprite, int offset_x, int offset_y, int width, int height){
	PyObject* ret = PY_CALL("sOiiOiiii", "canvas_put_sprite", py_get_pyobject(pcanvas), canvas_x, canvas_y, py_get_pyobject(sprite), offset_x, offset_y, width, height);
	Py_DECREF(ret);
}
// void canvas_put_sprite_full(struct canvas *pcanvas, int canvas_x, int canvas_y, struct sprite *sprite)
void canvas_put_sprite_full(struct canvas *pcanvas, int canvas_x, int canvas_y, struct sprite *sprite){
	PyObject* ret = PY_CALL("sOiiO", "canvas_put_sprite_full", py_get_pyobject(pcanvas), canvas_x, canvas_y, py_get_pyobject(sprite));
	Py_DECREF(ret);
}
// void canvas_put_sprite_fogged(struct canvas *pcanvas, int canvas_x, int canvas_y, struct sprite *psprite, bool fog, int fog_x, int fog_y)
void canvas_put_sprite_fogged(struct canvas *pcanvas, int canvas_x, int canvas_y, struct sprite *psprite, bool fog, int fog_x, int fog_y){
	PyObject* ret = PY_CALL("sOiiOiii", "canvas_put_sprite_fogged", py_get_pyobject(pcanvas), canvas_x, canvas_y, py_get_pyobject(psprite), (int)fog, fog_x, fog_y);
	Py_DECREF(ret);
}
// void canvas_put_rectangle(struct canvas *pcanvas, struct color *pcolor, int canvas_x, int canvas_y, int width, int height)
void canvas_put_rectangle(struct canvas *pcanvas, struct color *pcolor, int canvas_x, int canvas_y, int width, int height){
	PyObject* ret = PY_CALL("sOOiiii", "canvas_put_rectangle", py_get_pyobject(pcanvas), py_mapper_color(pcolor), canvas_x, canvas_y, width, height);
	Py_DECREF(ret);
}
// void canvas_fill_sprite_area(struct canvas *pcanvas, struct sprite *psprite, struct color *pcolor, int canvas_x, int canvas_y)
void canvas_fill_sprite_area(struct canvas *pcanvas, struct sprite *psprite, struct color *pcolor, int canvas_x, int canvas_y){
	PyObject* ret = PY_CALL("sOOOii", "canvas_fill_sprite_area", py_get_pyobject(pcanvas), py_get_pyobject(psprite), py_mapper_color(pcolor), canvas_x, canvas_y);
	Py_DECREF(ret);
}
// void canvas_fog_sprite_area(struct canvas *pcanvas, struct sprite *psprite, int canvas_x, int canvas_y)
void canvas_fog_sprite_area(struct canvas *pcanvas, struct sprite *psprite, int canvas_x, int canvas_y){
	PyObject* ret = PY_CALL("sOOii", "canvas_fog_sprite_area", py_get_pyobject(pcanvas), py_get_pyobject(psprite), canvas_x, canvas_y);
	Py_DECREF(ret);
}
// void canvas_put_line(struct canvas *pcanvas, struct color *pcolor, enum line_type ltype, int start_x, int start_y, int dx, int dy)
void canvas_put_line(struct canvas *pcanvas, struct color *pcolor, enum line_type ltype, int start_x, int start_y, int dx, int dy){
	PyObject* ret = PY_CALL("sOOiiiii", "canvas_put_line", py_get_pyobject(pcanvas), py_mapper_color(pcolor), (int)ltype, start_x, start_y, dx, dy);
	Py_DECREF(ret);
}
// void canvas_put_curved_line(struct canvas *pcanvas, struct color *pcolor, enum line_type ltype, int start_x, int start_y, int dx, int dy)
void canvas_put_curved_line(struct canvas *pcanvas, struct color *pcolor, enum line_type ltype, int start_x, int start_y, int dx, int dy){
	PyObject* ret = PY_CALL("sOOiiiii", "canvas_put_curved_line", py_get_pyobject(pcanvas), py_mapper_color(pcolor), (int)ltype, start_x, start_y, dx, dy);
	Py_DECREF(ret);
}
// void get_text_size(int *width, int *height, enum client_font font, const char *text)
// ignored

// void canvas_put_text(struct canvas *pcanvas, int canvas_x, int canvas_y, enum client_font font, struct color *pcolor, const char *text)
void canvas_put_text(struct canvas *pcanvas, int canvas_x, int canvas_y, enum client_font font, struct color *pcolor, const char *text){
	PyObject* ret = PY_CALL("sOiiiOs", "canvas_put_text", py_get_pyobject(pcanvas), canvas_x, canvas_y, (int)font, py_mapper_color(pcolor), text);
	Py_DECREF(ret);
}
// void popup_city_report_dialog(bool raise)
void popup_city_report_dialog(bool raise){
	PyObject* ret = PY_CALL("si", "popup_city_report_dialog", (int)raise);
	Py_DECREF(ret);
}
// void popup_meswin_dialog(bool raise)
void popup_meswin_dialog(bool raise){
	PyObject* ret = PY_CALL("si", "popup_meswin_dialog", (int)raise);
	Py_DECREF(ret);
}
// bool is_meswin_open(void)
bool is_meswin_open(void){
	PyObject* ret = PY_CALL("s", "is_meswin_open");
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from is_meswin_open (expected 'i')\n");
	Py_DECREF(ret);
	return (bool)retval;
}
// void real_update_meswin_dialog(void)
void real_update_meswin_dialog(void){
	PyObject* ret = PY_CALL("s", "real_update_meswin_dialog");
	Py_DECREF(ret);
}
// void gui_set_rulesets(int num_rulesets, char **rulesets)
// ignored

// void update_start_page(void)
void update_start_page(void){
	PyObject* ret = PY_CALL("s", "update_start_page");
	Py_DECREF(ret);
}
// void popup_players_dialog(bool raise)
void popup_players_dialog(bool raise){
	PyObject* ret = PY_CALL("si", "popup_players_dialog", (int)raise);
	Py_DECREF(ret);
}
// void update_players_dialog(void)
void update_players_dialog(void){
	PyObject* ret = PY_CALL("s", "update_players_dialog");
	Py_DECREF(ret);
}
// void science_dialog_update(void)
void science_dialog_update(void){
	PyObject* ret = PY_CALL("s", "science_dialog_update");
	Py_DECREF(ret);
}
// void popup_science_dialog(bool raise)
void popup_science_dialog(bool raise){
	PyObject* ret = PY_CALL("si", "popup_science_dialog", (int)raise);
	Py_DECREF(ret);
}
// void popup_economy_report_dialog(bool raise)
void popup_economy_report_dialog(bool raise){
	PyObject* ret = PY_CALL("si", "popup_economy_report_dialog", (int)raise);
	Py_DECREF(ret);
}
// void activeunits_report_dialog_update(void)
void activeunits_report_dialog_update(void){
	PyObject* ret = PY_CALL("s", "activeunits_report_dialog_update");
	Py_DECREF(ret);
}
// void popup_activeunits_report_dialog(bool raise)
void popup_activeunits_report_dialog(bool raise){
	PyObject* ret = PY_CALL("si", "popup_activeunits_report_dialog", (int)raise);
	Py_DECREF(ret);
}
// void popup_activeunits_report_dialog(bool raise)
// continue popup_activeunits_report_dialog - was processed
// void popup_settable_options_dialog(void)
void popup_settable_options_dialog(void){
	PyObject* ret = PY_CALL("s", "popup_settable_options_dialog");
	Py_DECREF(ret);
}
// void science_dialog_redraw(void)
void science_dialog_redraw(void){
	PyObject* ret = PY_CALL("s", "science_dialog_redraw");
	Py_DECREF(ret);
}
// void set_city_names_font_sizes(int my_city_names_font_size, int my_city_productions_font_size)
void set_city_names_font_sizes(int my_city_names_font_size, int my_city_productions_font_size){
	PyObject* ret = PY_CALL("sii", "set_city_names_font_sizes", my_city_names_font_size, my_city_productions_font_size);
	Py_DECREF(ret);
}
// void ui_init(void)
void ui_init(void){
	PyObject* ret = PY_CALL("s", "ui_init");
	Py_DECREF(ret);
}
// void ui_main(int argc, char *argv[])
// ignored

// void ui_exit()
void ui_exit(){
	PyObject* ret = PY_CALL("s", "ui_exit");
	Py_DECREF(ret);
}
// void update_conn_list_dialog(void)
void update_conn_list_dialog(void){
	PyObject* ret = PY_CALL("s", "update_conn_list_dialog");
	Py_DECREF(ret);
}
// void sound_bell(void)
void sound_bell(void){
	PyObject* ret = PY_CALL("s", "sound_bell");
	Py_DECREF(ret);
}
// void add_net_input(int sock)
void add_net_input(int sock){
	PyObject* ret = PY_CALL("si", "add_net_input", sock);
	Py_DECREF(ret);
}
// void remove_net_input(void)
void remove_net_input(void){
	PyObject* ret = PY_CALL("s", "remove_net_input");
	Py_DECREF(ret);
}
// void add_ggz_input(int sock)
void add_ggz_input(int sock){
	PyObject* ret = PY_CALL("si", "add_ggz_input", sock);
	Py_DECREF(ret);
}
// void remove_ggz_input(void)
void remove_ggz_input(void){
	PyObject* ret = PY_CALL("s", "remove_ggz_input");
	Py_DECREF(ret);
}
// void set_unit_icon(int idx, struct unit *punit)
void set_unit_icon(int idx, struct unit *punit){
	PyObject* ret = PY_CALL("siO", "set_unit_icon", idx, py_mapper_unit(punit));
	Py_DECREF(ret);
}
// void set_unit_icons_more_arrow(bool onoff)
void set_unit_icons_more_arrow(bool onoff){
	PyObject* ret = PY_CALL("si", "set_unit_icons_more_arrow", (int)onoff);
	Py_DECREF(ret);
}
// void add_idle_callback(void (callback)(void *), void *data)
// ignored

// void gui_update_font(const char *font_name, const char *font_value)
void gui_update_font(const char *font_name, const char *font_value){
	PyObject* ret = PY_CALL("sss", "gui_update_font", font_name, font_value);
	Py_DECREF(ret);
}
// void popup_help_dialog_typed(const char *item, enum help_page_type htype)
void popup_help_dialog_typed(const char *item, enum help_page_type htype){
	PyObject* ret = PY_CALL("ssi", "popup_help_dialog_typed", item, (int)htype);
	Py_DECREF(ret);
}
// void popdown_help_dialog(void)
void popdown_help_dialog(void){
	PyObject* ret = PY_CALL("s", "popdown_help_dialog");
	Py_DECREF(ret);
}
// void popup_find_dialog(void)
void popup_find_dialog(void){
	PyObject* ret = PY_CALL("s", "popup_find_dialog");
	Py_DECREF(ret);
}
// void popup_intel_dialog(struct player *p)
void popup_intel_dialog(struct player *p){
	PyObject* ret = PY_CALL("sO", "popup_intel_dialog", py_mapper_player(p));
	Py_DECREF(ret);
}
// void update_intel_dialog(struct player *p)
void update_intel_dialog(struct player *p){
	PyObject* ret = PY_CALL("sO", "update_intel_dialog", py_mapper_player(p));
	Py_DECREF(ret);
}
// void update_worklist_report_dialog(void)
void update_worklist_report_dialog(void){
	PyObject* ret = PY_CALL("s", "update_worklist_report_dialog");
	Py_DECREF(ret);
}
// void popup_newcity_dialog(struct unit *punit, char *suggestname)
void popup_newcity_dialog(struct unit *punit, char *suggestname){
	PyObject* ret = PY_CALL("sOs", "popup_newcity_dialog", py_mapper_unit(punit), suggestname);
	Py_DECREF(ret);
}
// void set_turn_done_button_state(bool state)
void set_turn_done_button_state(bool state){
	PyObject* ret = PY_CALL("si", "set_turn_done_button_state", (int)state);
	Py_DECREF(ret);
}
// void create_line_at_mouse_pos(void)
void create_line_at_mouse_pos(void){
	PyObject* ret = PY_CALL("s", "create_line_at_mouse_pos");
	Py_DECREF(ret);
}
// void update_rect_at_mouse_pos(void)
void update_rect_at_mouse_pos(void){
	PyObject* ret = PY_CALL("s", "update_rect_at_mouse_pos");
	Py_DECREF(ret);
}
// void real_output_window_append(const char *astring, const struct text_tag_list *tags, int conn_id)
void real_output_window_append(const char *astring, const struct text_tag_list *tags, int conn_id){
	PyObject* ret = PY_CALL("ssOi", "real_output_window_append", astring, py_mapper_text_tag_list(tags), conn_id);
	Py_DECREF(ret);
}
// void log_output_window(void)
void log_output_window(void){
	PyObject* ret = PY_CALL("s", "log_output_window");
	Py_DECREF(ret);
}
// void clear_output_window(void)
void clear_output_window(void){
	PyObject* ret = PY_CALL("s", "clear_output_window");
	Py_DECREF(ret);
}
// void popup_notify_goto_dialog(const char *headline, const char *lines, const struct text_tag_list *tags, struct tile *ptile)
void popup_notify_goto_dialog(const char *headline, const char *lines, const struct text_tag_list *tags, struct tile *ptile){
	PyObject* ret = PY_CALL("sssOO", "popup_notify_goto_dialog", headline, lines, py_mapper_text_tag_list(tags), py_mapper_tile(ptile));
	Py_DECREF(ret);
}
// void popup_connect_msg(const char *headline, const char *message)
void popup_connect_msg(const char *headline, const char *message){
	PyObject* ret = PY_CALL("sss", "popup_connect_msg", headline, message);
	Py_DECREF(ret);
}
// void popup_notify_dialog(const char *caption, const char *headline, const char *lines)
void popup_notify_dialog(const char *caption, const char *headline, const char *lines){
	PyObject* ret = PY_CALL("ssss", "popup_notify_dialog", caption, headline, lines);
	Py_DECREF(ret);
}
// void popup_races_dialog(struct player *pplayer)
void popup_races_dialog(struct player *pplayer){
	PyObject* ret = PY_CALL("sO", "popup_races_dialog", py_mapper_player(pplayer));
	Py_DECREF(ret);
}
// void popdown_races_dialog(void)
void popdown_races_dialog(void){
	PyObject* ret = PY_CALL("s", "popdown_races_dialog");
	Py_DECREF(ret);
}
// void unit_select_dialog_popup(struct tile *ptile)
void unit_select_dialog_popup(struct tile *ptile){
	PyObject* ret = PY_CALL("sO", "unit_select_dialog_popup", py_mapper_tile(ptile));
	Py_DECREF(ret);
}
// void races_toggles_set_sensitive(void)
void races_toggles_set_sensitive(void){
	PyObject* ret = PY_CALL("s", "races_toggles_set_sensitive");
	Py_DECREF(ret);
}
// void popup_revolution_dialog(void)
void popup_revolution_dialog(void){
	PyObject* ret = PY_CALL("s", "popup_revolution_dialog");
	Py_DECREF(ret);
}
// void popup_caravan_dialog(struct unit *punit, struct city *phomecity, struct city *pdestcity)
void popup_caravan_dialog(struct unit *punit, struct city *phomecity, struct city *pdestcity){
	PyObject* ret = PY_CALL("sOOO", "popup_caravan_dialog", py_mapper_unit(punit), py_mapper_city(phomecity), py_mapper_city(pdestcity));
	Py_DECREF(ret);
}
// bool caravan_dialog_is_open(int *unit_id, int *city_id)
// ignored

// void popup_diplomat_dialog(struct unit *punit, struct tile *ptile)
void popup_diplomat_dialog(struct unit *punit, struct tile *ptile){
	PyObject* ret = PY_CALL("sOO", "popup_diplomat_dialog", py_mapper_unit(punit), py_mapper_tile(ptile));
	Py_DECREF(ret);
}
// void popup_incite_dialog(struct city *pcity, int cost)
void popup_incite_dialog(struct city *pcity, int cost){
	PyObject* ret = PY_CALL("sOi", "popup_incite_dialog", py_mapper_city(pcity), cost);
	Py_DECREF(ret);
}
// void popup_bribe_dialog(struct unit *punit, int cost)
void popup_bribe_dialog(struct unit *punit, int cost){
	PyObject* ret = PY_CALL("sOi", "popup_bribe_dialog", py_mapper_unit(punit), cost);
	Py_DECREF(ret);
}
// void popup_sabotage_dialog(struct city *pcity)
void popup_sabotage_dialog(struct city *pcity){
	PyObject* ret = PY_CALL("sO", "popup_sabotage_dialog", py_mapper_city(pcity));
	Py_DECREF(ret);
}
// void popup_pillage_dialog(struct unit *punit, bv_special may_pillage, bv_bases bases)
// ignored

// void popup_tileset_suggestion_dialog(void)
void popup_tileset_suggestion_dialog(void){
	PyObject* ret = PY_CALL("s", "popup_tileset_suggestion_dialog");
	Py_DECREF(ret);
}
// bool popup_theme_suggestion_dialog(const char *theme_name)
bool popup_theme_suggestion_dialog(const char *theme_name){
	PyObject* ret = PY_CALL("ss", "popup_theme_suggestion_dialog", theme_name);
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from popup_theme_suggestion_dialog (expected 'i')\n");
	Py_DECREF(ret);
	return (bool)retval;
}
// void popdown_all_game_dialogs(void)
void popdown_all_game_dialogs(void){
	PyObject* ret = PY_CALL("s", "popdown_all_game_dialogs");
	Py_DECREF(ret);
}
// void popdown_all_game_dialogs(void)
// continue popdown_all_game_dialogs - was processed
// void popdown_all_game_dialogs(void)
// continue popdown_all_game_dialogs - was processed
// void popdown_all_game_dialogs(void)
// continue popdown_all_game_dialogs - was processed
// void really_close_connection_dialog(void)
void really_close_connection_dialog(void){
	PyObject* ret = PY_CALL("s", "really_close_connection_dialog");
	Py_DECREF(ret);
}
// void close_connection_dialog()
void close_connection_dialog(){
	PyObject* ret = PY_CALL("s", "close_connection_dialog");
	Py_DECREF(ret);
}
// void handle_game_load(struct packet_game_load *packet)
void handle_game_load(struct packet_game_load *packet){
	PyObject* ret = PY_CALL("sO", "handle_game_load", py_mapper_packet_game_load(packet));
	Py_DECREF(ret);
}
// void gui_server_connect(void)
void gui_server_connect(void){
	PyObject* ret = PY_CALL("s", "gui_server_connect");
	Py_DECREF(ret);
}
// bool isometric_view_supported(void)
bool isometric_view_supported(void){
	PyObject* ret = PY_CALL("s", "isometric_view_supported");
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from isometric_view_supported (expected 'i')\n");
	Py_DECREF(ret);
	return (bool)retval;
}
// bool overhead_view_supported(void)
bool overhead_view_supported(void){
	PyObject* ret = PY_CALL("s", "overhead_view_supported");
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from overhead_view_supported (expected 'i')\n");
	Py_DECREF(ret);
	return (bool)retval;
}
// void load_intro_gfx(void)
void load_intro_gfx(void){
	PyObject* ret = PY_CALL("s", "load_intro_gfx");
	Py_DECREF(ret);
}
// void load_cursors(void)
void load_cursors(void){
	PyObject* ret = PY_CALL("s", "load_cursors");
	Py_DECREF(ret);
}
// void popup_spaceship_dialog(struct player *pplayer)
void popup_spaceship_dialog(struct player *pplayer){
	PyObject* ret = PY_CALL("sO", "popup_spaceship_dialog", py_mapper_player(pplayer));
	Py_DECREF(ret);
}
// void popdown_spaceship_dialog(struct player *pplayer)
void popdown_spaceship_dialog(struct player *pplayer){
	PyObject* ret = PY_CALL("sO", "popdown_spaceship_dialog", py_mapper_player(pplayer));
	Py_DECREF(ret);
}
// void refresh_spaceship_dialog(struct player *pplayer)
void refresh_spaceship_dialog(struct player *pplayer){
	PyObject* ret = PY_CALL("sO", "refresh_spaceship_dialog", py_mapper_player(pplayer));
	Py_DECREF(ret);
}
// struct color *color_alloc(int r, int g, int b)
// ignored

// void color_free(struct color *color)
void color_free(struct color *color){
	PyObject* ret = PY_CALL("sO", "color_free", py_mapper_color(color));
	Py_DECREF(ret);
}
// void handle_diplomacy_accept_treaty(int counterpart, bool I_accepted, bool other_accepted)
void handle_diplomacy_accept_treaty(int counterpart, bool I_accepted, bool other_accepted){
	PyObject* ret = PY_CALL("siii", "handle_diplomacy_accept_treaty", counterpart, (int)I_accepted, (int)other_accepted);
	Py_DECREF(ret);
}
// void handle_diplomacy_init_meeting(int counterpart, int initiated_from)
void handle_diplomacy_init_meeting(int counterpart, int initiated_from){
	PyObject* ret = PY_CALL("sii", "handle_diplomacy_init_meeting", counterpart, initiated_from);
	Py_DECREF(ret);
}
// void handle_diplomacy_create_clause(int counterpart, int giver, enum clause_type type, int value)
void handle_diplomacy_create_clause(int counterpart, int giver, enum clause_type type, int value){
	PyObject* ret = PY_CALL("siiii", "handle_diplomacy_create_clause", counterpart, giver, (int)type, value);
	Py_DECREF(ret);
}
// void handle_diplomacy_cancel_meeting(int counterpart, int initiated_from)
void handle_diplomacy_cancel_meeting(int counterpart, int initiated_from){
	PyObject* ret = PY_CALL("sii", "handle_diplomacy_cancel_meeting", counterpart, initiated_from);
	Py_DECREF(ret);
}
// void handle_diplomacy_remove_clause(int counterpart, int giver, enum clause_type type, int value)
void handle_diplomacy_remove_clause(int counterpart, int giver, enum clause_type type, int value){
	PyObject* ret = PY_CALL("siiii", "handle_diplomacy_remove_clause", counterpart, giver, (int)type, value);
	Py_DECREF(ret);
}
// void close_all_diplomacy_dialogs(void)
void close_all_diplomacy_dialogs(void){
	PyObject* ret = PY_CALL("s", "close_all_diplomacy_dialogs");
	Py_DECREF(ret);
}
// void popup_messageopt_dialog(void)
void popup_messageopt_dialog(void){
	PyObject* ret = PY_CALL("s", "popup_messageopt_dialog");
	Py_DECREF(ret);
}
// int diplomat_handled_in_diplomat_dialog(void)
int diplomat_handled_in_diplomat_dialog(void){
	PyObject* ret = PY_CALL("s", "diplomat_handled_in_diplomat_dialog");
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from diplomat_handled_in_diplomat_dialog (expected 'i')\n");
	Py_DECREF(ret);
	return retval;
}
// void toggle_city_hilite(struct city *pcity, bool on_off)
void toggle_city_hilite(struct city *pcity, bool on_off){
	PyObject* ret = PY_CALL("sOi", "toggle_city_hilite", py_mapper_city(pcity), (int)on_off);
	Py_DECREF(ret);
}
// void hilite_cities_from_canvas(void)
void hilite_cities_from_canvas(void){
	PyObject* ret = PY_CALL("s", "hilite_cities_from_canvas");
	Py_DECREF(ret);
}
// void caravan_dialog_update(void)
void caravan_dialog_update(void){
	PyObject* ret = PY_CALL("s", "caravan_dialog_update");
	Py_DECREF(ret);
}
// void close_diplomat_dialog(void)
void close_diplomat_dialog(void){
	PyObject* ret = PY_CALL("s", "close_diplomat_dialog");
	Py_DECREF(ret);
}
// void popup_endgame_report_dialog(struct packet_endgame_report *packet)
void popup_endgame_report_dialog(struct packet_endgame_report *packet){
	PyObject* ret = PY_CALL("sO", "popup_endgame_report_dialog", py_mapper_packet_endgame_report(packet));
	Py_DECREF(ret);
}
// void update_city_descriptions(void)
void update_city_descriptions(void){
	PyObject* ret = PY_CALL("s", "update_city_descriptions");
	Py_DECREF(ret);
}
// void handle_authentication_req(enum authentication_type type, char *message)
void handle_authentication_req(enum authentication_type type, char *message){
	PyObject* ret = PY_CALL("sis", "handle_authentication_req", (int)type, message);
	Py_DECREF(ret);
}
// void update_report_dialogs(void)
void update_report_dialogs(void){
	PyObject* ret = PY_CALL("s", "update_report_dialogs");
	Py_DECREF(ret);
}
// char **get_gui_specific_themes_directories(int *count)
// ignored

// void gui_load_theme(const char *directory, const char *theme_name)
void gui_load_theme(const char *directory, const char *theme_name){
	PyObject* ret = PY_CALL("sss", "gui_load_theme", directory, theme_name);
	Py_DECREF(ret);
}
// void gui_clear_theme(void)
void gui_clear_theme(void){
	PyObject* ret = PY_CALL("s", "gui_clear_theme");
	Py_DECREF(ret);
}
// char **get_useable_themes_in_directory(const char *directory, int *count)
// ignored

// int test_glue(int val)
int test_glue(int val){
	PyObject* ret = PY_CALL("si", "test_glue", val);
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from test_glue (expected 'i')\n");
	Py_DECREF(ret);
	return retval;
}
// void real_focus_units_changed(void)
void real_focus_units_changed(void){
	PyObject* ret = PY_CALL("s", "real_focus_units_changed");
	Py_DECREF(ret);
}
// bool meswin_dialog_is_open(void)
bool meswin_dialog_is_open(void){
	PyObject* ret = PY_CALL("s", "meswin_dialog_is_open");
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from meswin_dialog_is_open (expected 'i')\n");
	Py_DECREF(ret);
	return (bool)retval;
}
// void real_meswin_dialog_update(void)
void real_meswin_dialog_update(void){
	PyObject* ret = PY_CALL("s", "real_meswin_dialog_update");
	Py_DECREF(ret);
}
// void meswin_dialog_popup(bool raise)
void meswin_dialog_popup(bool raise){
	PyObject* ret = PY_CALL("si", "meswin_dialog_popup", (int)raise);
	Py_DECREF(ret);
}
// void option_gui_update(struct option *poption)
void option_gui_update(struct option *poption){
	PyObject* ret = PY_CALL("sO", "option_gui_update", py_mapper_option(poption));
	Py_DECREF(ret);
}
// void option_dialog_popdown(const struct option_set *poptset)
void option_dialog_popdown(const struct option_set *poptset){
	PyObject* ret = PY_CALL("sO", "option_dialog_popdown", py_mapper_option_set(poptset));
	Py_DECREF(ret);
}
// void option_gui_remove(struct option *poption)
void option_gui_remove(struct option *poption){
	PyObject* ret = PY_CALL("sO", "option_gui_remove", py_mapper_option(poption));
	Py_DECREF(ret);
}
// void option_gui_add(struct option *poption)
void option_gui_add(struct option *poption){
	PyObject* ret = PY_CALL("sO", "option_gui_add", py_mapper_option(poption));
	Py_DECREF(ret);
}
// void science_report_dialog_redraw(void)
void science_report_dialog_redraw(void){
	PyObject* ret = PY_CALL("s", "science_report_dialog_redraw");
	Py_DECREF(ret);
}
// void update_overview_scroll_window_pos(int x, int y)
void update_overview_scroll_window_pos(int x, int y){
	PyObject* ret = PY_CALL("sii", "update_overview_scroll_window_pos", x, y);
	Py_DECREF(ret);
}
// void close_intel_dialog(struct player *p)
void close_intel_dialog(struct player *p){
	PyObject* ret = PY_CALL("sO", "close_intel_dialog", py_mapper_player(p));
	Py_DECREF(ret);
}
// void science_report_dialog_popup(bool raise)
void science_report_dialog_popup(bool raise){
	PyObject* ret = PY_CALL("si", "science_report_dialog_popup", (int)raise);
	Py_DECREF(ret);
}
// void endgame_report_dialog_popup(const struct packet_endgame_report *packet)
void endgame_report_dialog_popup(const struct packet_endgame_report *packet){
	PyObject* ret = PY_CALL("sO", "endgame_report_dialog_popup", py_mapper_packet_endgame_report(packet));
	Py_DECREF(ret);
}
// void real_set_client_page(enum client_pages page)
void real_set_client_page(enum client_pages page){
	PyObject* ret = PY_CALL("si", "real_set_client_page", (int)page);
	Py_DECREF(ret);
}
// enum client_pages get_current_client_page(void)
enum client_pages get_current_client_page(void){
	PyObject* ret = PY_CALL("s", "get_current_client_page");
	int retval;
	if(PyArg_ParseTuple(ret, "i", &retval) == 0) fprintf(stderr, "TypeError: bad return value from get_current_client_page (expected 'i')\n");
	Py_DECREF(ret);
	return (enum client_pages)retval;
}
// void real_menus_init(void)
void real_menus_init(void){
	PyObject* ret = PY_CALL("s", "real_menus_init");
	Py_DECREF(ret);
}
// void real_menus_update(void)
void real_menus_update(void){
	PyObject* ret = PY_CALL("s", "real_menus_update");
	Py_DECREF(ret);
}
// void real_city_report_update_city(struct city *pcity)
void real_city_report_update_city(struct city *pcity){
	PyObject* ret = PY_CALL("sO", "real_city_report_update_city", py_mapper_city(pcity));
	Py_DECREF(ret);
}
// void real_city_dialog_refresh(struct city *pCity)
void real_city_dialog_refresh(struct city *pCity){
	PyObject* ret = PY_CALL("sO", "real_city_dialog_refresh", py_mapper_city(pCity));
	Py_DECREF(ret);
}
// void real_city_dialog_popup(struct city *pcity)
void real_city_dialog_popup(struct city *pcity){
	PyObject* ret = PY_CALL("sO", "real_city_dialog_popup", py_mapper_city(pcity));
	Py_DECREF(ret);
}
// void real_conn_list_dialog_update(void)
void real_conn_list_dialog_update(void){
	PyObject* ret = PY_CALL("s", "real_conn_list_dialog_update");
	Py_DECREF(ret);
}
// void real_players_dialog_update(void)
void real_players_dialog_update(void){
	PyObject* ret = PY_CALL("s", "real_players_dialog_update");
	Py_DECREF(ret);
}
// void real_city_report_dialog_update(void)
void real_city_report_dialog_update(void){
	PyObject* ret = PY_CALL("s", "real_city_report_dialog_update");
	Py_DECREF(ret);
}
// void real_science_report_dialog_update(void)
void real_science_report_dialog_update(void){
	PyObject* ret = PY_CALL("s", "real_science_report_dialog_update");
	Py_DECREF(ret);
}
// void real_economy_report_dialog_update(void)
void real_economy_report_dialog_update(void){
	PyObject* ret = PY_CALL("s", "real_economy_report_dialog_update");
	Py_DECREF(ret);
}
// void real_units_report_dialog_update(void)
void real_units_report_dialog_update(void){
	PyObject* ret = PY_CALL("s", "real_units_report_dialog_update");
	Py_DECREF(ret);
}
// void global_update_tile(int x, int y)
void global_update_tile(int x, int y){
    PyObject* ret = PY_CALL("sii", "global_update_tile", x, y);
	Py_DECREF(ret);
}
// void global_set_mapview_center(int gui_x, int gui_y)
void global_set_mapview_center(int gui_x, int gui_y){
    PyObject* ret = PY_CALL("sii", "global_set_mapview_center", gui_x, gui_y);
	Py_DECREF(ret);
}
// void global_update_everything()
void global_update_everything(){
    PyObject* ret = PY_CALL("s", "global_update_everything");
	Py_DECREF(ret);
}
// IGNORED:
//  void get_overview_area_dimensions(int *width, int *height)
//  const char **gfx_fileextensions(void)
//  void get_sprite_dimensions(struct sprite *sprite, int *width, int *height)
//  bool city_dialog_is_open(struct city *pcity)
//  void get_text_size(int *width, int *height, enum client_font font, const char *text)
//  void gui_set_rulesets(int num_rulesets, char **rulesets)
//  void ui_main(int argc, char *argv[])
//  void add_idle_callback(void (callback)(void *), void *data)
//  bool caravan_dialog_is_open(int *unit_id, int *city_id)
//  void popup_pillage_dialog(struct unit *punit, bv_special may_pillage, bv_bases bases)
//  struct color *color_alloc(int r, int g, int b)
//  char **get_gui_specific_themes_directories(int *count)
//  char **get_useable_themes_in_directory(const char *directory, int *count)
// processed 152 ignored 13
