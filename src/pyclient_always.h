// Some methods have different implementations in client and server.
// But since we build single binary, they have to be choosen at runtime

_Bool is_server(void);

#define GET_AMBIGUOUS_METHOD(name) ( is_server() ? name##_SERVER : name##_CLIENT )

#define handle_scenario_info GET_AMBIGUOUS_METHOD(handle_scenario_info)
#define handle_edit_startpos GET_AMBIGUOUS_METHOD(handle_edit_startpos)
#define handle_edit_startpos_full GET_AMBIGUOUS_METHOD(handle_edit_startpos_full)
#define handle_player_attribute_chunk GET_AMBIGUOUS_METHOD(handle_player_attribute_chunk)
