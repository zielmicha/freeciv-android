
 /****************************************************************************
 *                       THIS FILE WAS GENERATED                             *
 * Script: common/generate_packets.py                                        *
 * Input:  common/packets.def                                                *
 *                       DO NOT CHANGE THIS FILE                             *
 ****************************************************************************/


#ifndef FC__PACKHAND_GEN_H
#define FC__PACKHAND_GEN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* utility */
#include "shared.h"

/* common */
#include "packets.h"

bool client_handle_packet(enum packet_type type, const void *packet);

void handle_processing_started(void);
void handle_processing_finished(void);
void handle_server_join_reply(bool you_can_join, const char *message, const char *capability, const char *challenge_file, int conn_id);
void handle_authentication_req(enum authentication_type type, const char *message);
void handle_server_shutdown(void);
struct packet_endgame_report;
void handle_endgame_report(const struct packet_endgame_report *packet);
struct packet_endgame_player;
void handle_endgame_player(const struct packet_endgame_player *packet);
struct packet_tile_info;
void handle_tile_info(const struct packet_tile_info *packet);
struct packet_game_info;
void handle_game_info(const struct packet_game_info *packet);
void handle_map_info(int xsize, int ysize, int topology_id);
void handle_nuke_tile_info(int tile);
void handle_team_name_info(int team_id, const char *team_name);
void handle_chat_msg(const char *message, int tile, enum event_type event, int conn_id);
void handle_connect_msg(const char *message);
void handle_city_remove(int city_id);
struct packet_city_info;
void handle_city_info(const struct packet_city_info *packet);
struct packet_city_short_info;
void handle_city_short_info(const struct packet_city_short_info *packet);
void handle_city_name_suggestion_info(int unit_id, const char *name);
void handle_city_sabotage_list(int diplomat_id, int city_id, bv_imprs improvements);
void handle_player_remove(int playerno);
struct packet_player_info;
void handle_player_info(const struct packet_player_info *packet);
void handle_tech_gained(int tech);
struct packet_player_attribute_chunk;
void handle_player_attribute_chunk_CLIENT(const struct packet_player_attribute_chunk *packet);
void handle_player_attribute_chunk_SERVER(const struct packet_player_attribute_chunk *packet);
struct packet_player_diplstate;
void handle_player_diplstate(const struct packet_player_diplstate *packet);
void handle_unit_remove(int unit_id);
struct packet_unit_info;
void handle_unit_info(const struct packet_unit_info *packet);
struct packet_unit_short_info;
void handle_unit_short_info(const struct packet_unit_short_info *packet);
void handle_unit_combat_info(int attacker_unit_id, int defender_unit_id, int attacker_hp, int defender_hp, bool make_winner_veteran);
void handle_unit_diplomat_answer(int diplomat_id, int target_id, int cost, enum diplomat_actions action_type);
void handle_diplomacy_init_meeting(int counterpart, int initiated_from);
void handle_diplomacy_cancel_meeting(int counterpart, int initiated_from);
void handle_diplomacy_create_clause(int counterpart, int giver, enum clause_type type, int value);
void handle_diplomacy_remove_clause(int counterpart, int giver, enum clause_type type, int value);
void handle_diplomacy_accept_treaty(int counterpart, bool I_accepted, bool other_accepted);
void handle_page_msg_old(const char *caption, const char *headline, const char *lines, enum event_type event);
void handle_page_msg_new(const char *caption, const char *headline, enum event_type event, int len, int parts);
void handle_page_msg_part(const char *lines);
struct packet_conn_info;
void handle_conn_info(const struct packet_conn_info *packet);
void handle_conn_ping_info(int connections, const int *conn_id, const float *ping_time);
void handle_conn_ping(void);
void handle_end_phase(void);
void handle_start_phase(int phase);
void handle_new_year(int year, int turn);
void handle_begin_turn(void);
void handle_end_turn(void);
void handle_freeze_client(void);
void handle_thaw_client(void);
struct packet_spaceship_info;
void handle_spaceship_info(const struct packet_spaceship_info *packet);
struct packet_ruleset_unit;
void handle_ruleset_unit(const struct packet_ruleset_unit *packet);
struct packet_ruleset_unit_bonus;
void handle_ruleset_unit_bonus(const struct packet_ruleset_unit_bonus *packet);
struct packet_ruleset_unit_flag;
void handle_ruleset_unit_flag(const struct packet_ruleset_unit_flag *packet);
struct packet_ruleset_game;
void handle_ruleset_game(const struct packet_ruleset_game *packet);
struct packet_ruleset_specialist;
void handle_ruleset_specialist(const struct packet_ruleset_specialist *packet);
struct packet_ruleset_government_ruler_title;
void handle_ruleset_government_ruler_title(const struct packet_ruleset_government_ruler_title *packet);
struct packet_ruleset_tech;
void handle_ruleset_tech(const struct packet_ruleset_tech *packet);
struct packet_ruleset_tech_flag;
void handle_ruleset_tech_flag(const struct packet_ruleset_tech_flag *packet);
struct packet_ruleset_government;
void handle_ruleset_government(const struct packet_ruleset_government *packet);
struct packet_ruleset_terrain_control;
void handle_ruleset_terrain_control(const struct packet_ruleset_terrain_control *packet);
void handle_rulesets_ready(void);
struct packet_ruleset_nation_sets;
void handle_ruleset_nation_sets(const struct packet_ruleset_nation_sets *packet);
struct packet_ruleset_nation_groups;
void handle_ruleset_nation_groups(const struct packet_ruleset_nation_groups *packet);
struct packet_ruleset_nation;
void handle_ruleset_nation(const struct packet_ruleset_nation *packet);
void handle_nation_availability(int ncount, const bool *is_pickable, bool nationset_change);
struct packet_ruleset_city;
void handle_ruleset_city(const struct packet_ruleset_city *packet);
struct packet_ruleset_building;
void handle_ruleset_building(const struct packet_ruleset_building *packet);
struct packet_ruleset_terrain;
void handle_ruleset_terrain(const struct packet_ruleset_terrain *packet);
struct packet_ruleset_terrain_flag;
void handle_ruleset_terrain_flag(const struct packet_ruleset_terrain_flag *packet);
struct packet_ruleset_unit_class;
void handle_ruleset_unit_class(const struct packet_ruleset_unit_class *packet);
struct packet_ruleset_base;
void handle_ruleset_base(const struct packet_ruleset_base *packet);
struct packet_ruleset_road;
void handle_ruleset_road(const struct packet_ruleset_road *packet);
struct packet_ruleset_disaster;
void handle_ruleset_disaster(const struct packet_ruleset_disaster *packet);
struct packet_ruleset_trade;
void handle_ruleset_trade(const struct packet_ruleset_trade *packet);
struct packet_ruleset_control;
void handle_ruleset_control(const struct packet_ruleset_control *packet);
void handle_single_want_hack_reply(bool you_have_hack);
struct packet_ruleset_choices;
void handle_ruleset_choices(const struct packet_ruleset_choices *packet);
void handle_game_load(bool load_successful, const char *load_filename);
struct packet_server_setting_control;
void handle_server_setting_control(const struct packet_server_setting_control *packet);
struct packet_server_setting_const;
void handle_server_setting_const(const struct packet_server_setting_const *packet);
struct packet_server_setting_bool;
void handle_server_setting_bool(const struct packet_server_setting_bool *packet);
struct packet_server_setting_int;
void handle_server_setting_int(const struct packet_server_setting_int *packet);
struct packet_server_setting_str;
void handle_server_setting_str(const struct packet_server_setting_str *packet);
struct packet_server_setting_enum;
void handle_server_setting_enum(const struct packet_server_setting_enum *packet);
struct packet_server_setting_bitwise;
void handle_server_setting_bitwise(const struct packet_server_setting_bitwise *packet);
struct packet_ruleset_effect;
void handle_ruleset_effect(const struct packet_ruleset_effect *packet);
struct packet_ruleset_effect_req;
void handle_ruleset_effect_req(const struct packet_ruleset_effect_req *packet);
struct packet_ruleset_resource;
void handle_ruleset_resource(const struct packet_ruleset_resource *packet);
struct packet_scenario_info;
void handle_scenario_info(const struct packet_scenario_info *packet);
struct packet_vote_new;
void handle_vote_new(const struct packet_vote_new *packet);
void handle_vote_update(int vote_no, int yes, int no, int abstain, int num_voters);
void handle_vote_remove(int vote_no);
void handle_vote_resolve(int vote_no, bool passed);
struct packet_edit_startpos;
void handle_edit_startpos_CLIENT(const struct packet_edit_startpos *packet);
void handle_edit_startpos_SERVER(const struct packet_edit_startpos *packet);
struct packet_edit_startpos_full;
void handle_edit_startpos_full_CLIENT(const struct packet_edit_startpos_full *packet);
void handle_edit_startpos_full_SERVER(const struct packet_edit_startpos_full *packet);
void handle_edit_object_created(int tag, int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FC__PACKHAND_GEN_H */
