#include <Python.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "game.h"
#include "unit.h"
#include "tilespec.h"
#include "unitlist.h"
#include "featured_text.h"
#include "player.h"
#include "city.h"
#include "tile.h"
#include "helpdata.h"
#include "client_main.h"
#include "mapview_common.h"
#include "messagewin_common.h"
#include "overview_common.h"

#include "canvas_g.h"
#include "pages_g.h"

#define PY_CALL(TUPLE, VARARG...) PyObject_CallFunction(python_callback, TUPLE, ##VARARG)

extern PyObject* python_callback;

struct canvas {
    PyObject* py_object;
};

struct sprite {
    PyObject* py_object;
};

struct color {
    int r, g, b;
};


PyObject* py_mapper_city(struct city* s);
PyObject* py_mapper_player(struct player* s);
PyObject* py_mapper_unit(struct unit* s);
PyObject* py_mapper_tile(struct tile* s);
PyObject* py_mapper_packet_game_load(struct packet_game_load* s);
PyObject* py_mapper_text_tag_list(struct text_tag_list* s);
PyObject* py_mapper_unit_list(struct unit_list* s);
PyObject* py_mapper_color(struct color* s);
PyObject* py_mapper_packet_endgame_report(struct packet_endgame_report* s);
PyObject* py_mapper_message(struct message* s);

void* py_alloc_struct(PyObject* stru);
void py_setup_callglue();

