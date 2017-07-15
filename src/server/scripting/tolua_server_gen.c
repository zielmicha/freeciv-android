/*
** Lua binding: server
*/

#include "tolua.h"

#ifndef __cplusplus
#include <stdlib.h>
#endif
#ifdef __cplusplus
 extern "C" int tolua_bnd_takeownership (lua_State* L); // from tolua_map.c
#else
 int tolua_bnd_takeownership (lua_State* L); /* from tolua_map.c */
#endif
#include <string.h>

/* Exported function */
TOLUA_API int tolua_server_open (lua_State* tolua_S);
LUALIB_API int luaopen_server (lua_State* tolua_S);

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif
#include "luascript_types.h"
#include "commands.h"
#include "console.h"
#include "api_server_edit.h"
#include "api_server_base.h"
#include "api_server_notify.h"
#include "script_server.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"Direction");
 tolua_usertype(tolua_S,"Tech_Type");
 tolua_usertype(tolua_S,"Nation_Type");
 tolua_usertype(tolua_S,"Unit_Type");
 tolua_usertype(tolua_S,"City");
 tolua_usertype(tolua_S,"Unit");
 tolua_usertype(tolua_S,"Tile");
}

/* function: api_server_save */
static int tolua_server_server_save00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  const char* filename = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_server_save(L,filename);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'save'.",&tolua_err);
 return 0;
#endif
}

/* function: api_server_was_started */
static int tolua_server_server_started00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
 {
  bool tolua_ret = (bool)  api_server_was_started(L);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'started'.",&tolua_err);
 return 0;
#endif
}

/* function: api_server_player_civilization_score */
static int tolua_server_server_civilization_score00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_server_player_civilization_score(L,pplayer);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'civilization_score'.",&tolua_err);
 return 0;
#endif
}

/* function: api_server_setting_get */
static int tolua_server_server_setting_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  const char* setting_name = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_server_setting_get(L,setting_name);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}

/* function: api_notify_embassies_msg */
static int tolua_server_notify_embassies_msg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  int event = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,4,0));
 {
  api_notify_embassies_msg(L,pplayer,ptile,event,message);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'embassies_msg'.",&tolua_err);
 return 0;
#endif
}

/* function: api_notify_event_msg */
static int tolua_server_notify_event_msg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  int event = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,4,0));
 {
  api_notify_event_msg(L,pplayer,ptile,event,message);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'event_msg'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_create_unit */
static int tolua_server_edit_create_unit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"Unit_Type",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,5,"City",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,6,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  Unit_Type* ptype = ((Unit_Type*)  tolua_tousertype(tolua_S,3,0));
  int veteran_level = ((int)  tolua_tonumber(tolua_S,4,0));
  City* homecity = ((City*)  tolua_tousertype(tolua_S,5,0));
  int moves_left = ((int)  tolua_tonumber(tolua_S,6,0));
 {
  Unit* tolua_ret = (Unit*)  api_edit_create_unit(L,pplayer,ptile,ptype,veteran_level,homecity,moves_left);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_unit'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_create_unit_full */
static int tolua_server_edit_create_unit_full00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"Unit_Type",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,5,"City",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,6,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,7,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,8,"Unit",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  Unit_Type* ptype = ((Unit_Type*)  tolua_tousertype(tolua_S,3,0));
  int veteran_level = ((int)  tolua_tonumber(tolua_S,4,0));
  City* homecity = ((City*)  tolua_tousertype(tolua_S,5,0));
  int moves_left = ((int)  tolua_tonumber(tolua_S,6,0));
  int hp_left = ((int)  tolua_tonumber(tolua_S,7,0));
  Unit* ptransport = ((Unit*)  tolua_tousertype(tolua_S,8,0));
 {
  Unit* tolua_ret = (Unit*)  api_edit_create_unit_full(L,pplayer,ptile,ptype,veteran_level,homecity,moves_left,hp_left,ptransport);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_unit_full'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_unit_teleport */
static int tolua_server_edit_unit_teleport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit* self = ((Unit*)  tolua_tousertype(tolua_S,1,0));
  Tile* dest = ((Tile*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_edit_unit_teleport(L,self,dest);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit_teleport'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_create_city */
static int tolua_server_edit_create_city00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
 {
  api_edit_create_city(L,pplayer,ptile,name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_city'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_create_base */
static int tolua_server_edit_create_base00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,3,0));
 {
  api_edit_create_base(L,ptile,name,pplayer);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_base'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_create_road */
static int tolua_server_edit_create_road00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  api_edit_create_road(L,ptile,name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_road'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_tile_set_label */
static int tolua_server_edit_tile_set_label00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  const char* label = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  api_edit_tile_set_label(L,ptile,label);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tile_set_label'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_create_player */
static int tolua_server_edit_create_player00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Nation_Type",0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  const char* username = ((const char*)  tolua_tostring(tolua_S,1,0));
  Nation_Type* nation = ((Nation_Type*)  tolua_tousertype(tolua_S,2,0));
  const char* ai = ((const char*)  tolua_tostring(tolua_S,3,0));
 {
  Player* tolua_ret = (Player*)  api_edit_create_player(L,username,nation,ai);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_player'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_change_gold */
static int tolua_server_edit_change_gold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  int amount = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  api_edit_change_gold(L,pplayer,amount);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'change_gold'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_give_technology */
static int tolua_server_edit_give_technology00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tech_Type",0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tech_Type* ptech = ((Tech_Type*)  tolua_tousertype(tolua_S,2,0));
  const char* reason = ((const char*)  tolua_tostring(tolua_S,3,0));
 {
  Tech_Type* tolua_ret = (Tech_Type*)  api_edit_give_technology(L,pplayer,ptech,reason);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tech_Type");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'give_technology'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_trait_mod */
static int tolua_server_edit_trait_mod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  const char* trait_name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const int mod = ((const int)  tolua_tonumber(tolua_S,3,0));
 {
  bool tolua_ret = (bool)  api_edit_trait_mod(L,pplayer,trait_name,mod);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'trait_mod'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_unleash_barbarians */
static int tolua_server_edit_unleash_barbarians00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_edit_unleash_barbarians(L,ptile);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unleash_barbarians'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_place_partisans */
static int tolua_server_edit_place_partisans00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  int sq_radius = ((int)  tolua_tonumber(tolua_S,4,0));
 {
  api_edit_place_partisans(L,ptile,pplayer,count,sq_radius);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'place_partisans'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_climate_change */
static int tolua_server_edit_climate_change00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  enum climate_change_type type = ((enum climate_change_type) (int)  tolua_tonumber(tolua_S,1,0));
  int effect = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  api_edit_climate_change(L,type,effect);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'climate_change'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_civil_war */
static int tolua_server_edit_civil_war00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  int probability = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Player* tolua_ret = (Player*)  api_edit_civil_war(L,pplayer,probability);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'civil_war'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_unit_turn */
static int tolua_server_edit_unit_turn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Direction",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit* punit = ((Unit*)  tolua_tousertype(tolua_S,1,0));
  Direction dir = *((Direction*)  tolua_tousertype(tolua_S,2,0));
 {
  api_edit_unit_turn(L,punit,dir);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit_turn'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_player_victory */
static int tolua_server_edit_player_victory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  api_edit_player_victory(L,self);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'player_victory'.",&tolua_err);
 return 0;
#endif
}

/* function: api_edit_unit_move */
static int tolua_server_edit_unit_move00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit* self = ((Unit*)  tolua_tousertype(tolua_S,1,0));
  Tile* moveto = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  int movecost = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  bool tolua_ret = (bool)  api_edit_unit_move(L,self,moveto,movecost);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit_move'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_server (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"server",0);
 tolua_beginmodule(tolua_S,"server");
 tolua_function(tolua_S,"save",tolua_server_server_save00);
 tolua_function(tolua_S,"started",tolua_server_server_started00);
 tolua_function(tolua_S,"civilization_score",tolua_server_server_civilization_score00);
 tolua_module(tolua_S,"setting",0);
 tolua_beginmodule(tolua_S,"setting");
 tolua_function(tolua_S,"get",tolua_server_server_setting_get00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"notify",0);
 tolua_beginmodule(tolua_S,"notify");
 tolua_function(tolua_S,"embassies_msg",tolua_server_notify_embassies_msg00);
 tolua_function(tolua_S,"event_msg",tolua_server_notify_event_msg00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,110,111,116,105,102,
 121, 46, 97,108,108, 40, 46, 46, 46, 41, 10,108,111, 99, 97,
 108, 32, 97,114,103, 32, 61, 32,116, 97, 98,108,101, 46,112,
  97, 99,107, 40, 46, 46, 46, 41, 59, 10,110,111,116,105,102,
 121, 46,101,118,101,110,116, 95,109,115,103, 40,110,105,108,
  44, 32,110,105,108, 44, 32, 69, 46, 83, 67, 82, 73, 80, 84,
  44, 32,115,116,114,105,110,103, 46,102,111,114,109, 97,116,
  40,116, 97, 98,108,101, 46,117,110,112, 97, 99,107, 40, 97,
 114,103, 41, 41, 41, 10,101,110,100, 10,102,117,110, 99,116,
 105,111,110, 32,110,111,116,105,102,121, 46,112,108, 97,121,
 101,114, 40,112,108, 97,121,101,114, 44, 32, 46, 46, 46, 41,
  10,108,111, 99, 97,108, 32, 97,114,103, 32, 61, 32,116, 97,
  98,108,101, 46,112, 97, 99,107, 40, 46, 46, 46, 41, 59, 10,
 110,111,116,105,102,121, 46,101,118,101,110,116, 95,109,115,
 103, 40,112,108, 97,121,101,114, 44, 32,110,105,108, 44, 32,
  69, 46, 83, 67, 82, 73, 80, 84, 44, 32,115,116,114,105,110,
 103, 46,102,111,114,109, 97,116, 40,116, 97, 98,108,101, 46,
 117,110,112, 97, 99,107, 40, 97,114,103, 41, 41, 41, 10,101,
 110,100, 10,102,117,110, 99,116,105,111,110, 32,110,111,116,
 105,102,121, 46,101,118,101,110,116, 40,112,108, 97,121,101,
 114, 44, 32,116,105,108,101, 44, 32,101,118,101,110,116, 44,
  32, 46, 46, 46, 41, 10,108,111, 99, 97,108, 32, 97,114,103,
  32, 61, 32,116, 97, 98,108,101, 46,112, 97, 99,107, 40, 46,
  46, 46, 41, 59, 10,110,111,116,105,102,121, 46,101,118,101,
 110,116, 95,109,115,103, 40,112,108, 97,121,101,114, 44, 32,
 116,105,108,101, 44, 32,101,118,101,110,116, 44, 32,115,116,
 114,105,110,103, 46,102,111,114,109, 97,116, 40,116, 97, 98,
 108,101, 46,117,110,112, 97, 99,107, 40, 97,114,103, 41, 41,
  41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
 110,111,116,105,102,121, 46,101,109, 98, 97,115,115,105,101,
 115, 40,112,108, 97,121,101,114, 44, 32,112,116,105,108,101,
  44, 32,101,118,101,110,116, 44, 32, 46, 46, 46, 41, 10,108,
 111, 99, 97,108, 32, 97,114,103, 32, 61, 32,116, 97, 98,108,
 101, 46,112, 97, 99,107, 40, 46, 46, 46, 41, 59, 10,110,111,
 116,105,102,121, 46,101,109, 98, 97,115,115,105,101,115, 95,
 109,115,103, 40,112,108, 97,121,101,114, 44, 32,112,116,105,
 108,101, 44, 32,101,118,101,110,116, 44, 32,115,116,114,105,
 110,103, 46,102,111,114,109, 97,116, 40,116, 97, 98,108,101,
  46,117,110,112, 97, 99,107, 40, 97,114,103, 41, 41, 41, 10,
 101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"edit",0);
 tolua_beginmodule(tolua_S,"edit");
 tolua_function(tolua_S,"create_unit",tolua_server_edit_create_unit00);
 tolua_function(tolua_S,"create_unit_full",tolua_server_edit_create_unit_full00);
 tolua_function(tolua_S,"unit_teleport",tolua_server_edit_unit_teleport00);
 tolua_function(tolua_S,"create_city",tolua_server_edit_create_city00);
 tolua_function(tolua_S,"create_base",tolua_server_edit_create_base00);
 tolua_function(tolua_S,"create_road",tolua_server_edit_create_road00);
 tolua_function(tolua_S,"tile_set_label",tolua_server_edit_tile_set_label00);
 tolua_function(tolua_S,"create_player",tolua_server_edit_create_player00);
 tolua_function(tolua_S,"change_gold",tolua_server_edit_change_gold00);
 tolua_function(tolua_S,"give_technology",tolua_server_edit_give_technology00);
 tolua_function(tolua_S,"trait_mod",tolua_server_edit_trait_mod00);
 tolua_function(tolua_S,"unleash_barbarians",tolua_server_edit_unleash_barbarians00);
 tolua_function(tolua_S,"place_partisans",tolua_server_edit_place_partisans00);
 tolua_constant(tolua_S,"GLOBAL_WARMING",CLIMATE_CHANGE_GLOBAL_WARMING);
 tolua_constant(tolua_S,"NUCLEAR_WINTER",CLIMATE_CHANGE_NUCLEAR_WINTER);
 tolua_function(tolua_S,"climate_change",tolua_server_edit_climate_change00);
 tolua_function(tolua_S,"civil_war",tolua_server_edit_civil_war00);
 tolua_function(tolua_S,"unit_turn",tolua_server_edit_unit_turn00);
 tolua_function(tolua_S,"player_victory",tolua_server_edit_player_victory00);
 tolua_function(tolua_S,"unit_move",tolua_server_edit_unit_move00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 99,114,101, 97,116,
 101, 95,117,110,105,116, 40,112,108, 97,121,101,114, 44, 32,
 116,105,108,101, 44, 32,117,116,121,112,101, 44, 32,118,101,
 116,101,114, 97,110, 95,108,101,118,101,108, 44, 32,104,111,
 109,101, 99,105,116,121, 44, 32,109,111,118,101,115, 95,108,
 101,102,116, 41, 10,114,101,116,117,114,110, 32,101,100,105,
 116, 46, 99,114,101, 97,116,101, 95,117,110,105,116, 40,112,
 108, 97,121,101,114, 44, 32,116,105,108,101, 44, 32,117,116,
 121,112,101, 44, 32,118,101,116,101,114, 97,110, 95,108,101,
 118,101,108, 44, 32,104,111,109,101, 99,105,116,121, 44, 10,
 109,111,118,101,115, 95,108,101,102,116, 41, 10,101,110,100,
  10,102,117,110, 99,116,105,111,110, 32, 99,114,101, 97,116,
 101, 95,117,110,105,116, 95,102,117,108,108, 40,112,108, 97,
 121,101,114, 44, 32,116,105,108,101, 44, 32,117,116,121,112,
 101, 44, 32,118,101,116,101,114, 97,110, 95,108,101,118,101,
 108, 44, 32,104,111,109,101, 99,105,116,121, 44, 10,109,111,
 118,101,115, 95,108,101,102,116, 44, 32,104,112, 95,108,101,
 102,116, 44, 32,116,114, 97,110,115,112,111,114,116, 41, 10,
 114,101,116,117,114,110, 32,101,100,105,116, 46, 99,114,101,
  97,116,101, 95,117,110,105,116, 95,102,117,108,108, 40,112,
 108, 97,121,101,114, 44, 32,116,105,108,101, 44, 32,117,116,
 121,112,101, 44, 32,118,101,116,101,114, 97,110, 95,108,101,
 118,101,108, 44, 32,104,111,109,101, 99,105,116,121, 44, 10,
 109,111,118,101,115, 95,108,101,102,116, 44, 32,104,112, 95,
 108,101,102,116, 44, 32,116,114, 97,110,115,112,111,114,116,
  41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  99,114,101, 97,116,101, 95, 99,105,116,121, 40,112,108, 97,
 121,101,114, 44, 32,116,105,108,101, 44, 32,110, 97,109,101,
  41, 10,101,100,105,116, 46, 99,114,101, 97,116,101, 95, 99,
 105,116,121, 32, 40,112,108, 97,121,101,114, 44, 32,116,105,
 108,101, 44, 32,110, 97,109,101, 41, 10,101,110,100, 10,102,
 117,110, 99,116,105,111,110, 32, 99,114,101, 97,116,101, 95,
  98, 97,115,101, 40,116,105,108,101, 44, 32,110, 97,109,101,
  44, 32,112,108, 97,121,101,114, 41, 10,101,100,105,116, 46,
  99,114,101, 97,116,101, 95, 98, 97,115,101, 40,116,105,108,
 101, 44, 32,110, 97,109,101, 44, 32,112,108, 97,121,101,114,
  41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  99,114,101, 97,116,101, 95,112,108, 97,121,101,114, 40,117,
 115,101,114,110, 97,109,101, 44, 32,110, 97,116,105,111,110,
  41, 10,114,101,116,117,114,110, 32,101,100,105,116, 46, 99,
 114,101, 97,116,101, 95,112,108, 97,121,101,114, 40,117,115,
 101,114,110, 97,109,101, 44, 32,110, 97,116,105,111,110, 44,
  32,110,105,108, 41, 10,101,110,100, 10,102,117,110, 99,116,
 105,111,110, 32, 99,104, 97,110,103,101, 95,103,111,108,100,
  40,112,112,108, 97,121,101,114, 44, 32, 97,109,111,117,110,
 116, 41, 10,101,100,105,116, 46, 99,104, 97,110,103,101, 95,
 103,111,108,100, 40,112,112,108, 97,121,101,114, 44, 32, 97,
 109,111,117,110,116, 41, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32,103,105,118,101, 95,116,101, 99,104,110,
 111,108,111,103,121, 40,112,108, 97,121,101,114, 44, 32,116,
 101, 99,104, 44, 32,114,101, 97,115,111,110, 41, 10,114,101,
 116,117,114,110, 32,101,100,105,116, 46,103,105,118,101, 95,
 116,101, 99,104,110,111,108,111,103,121, 40,112,108, 97,121,
 101,114, 44, 32,116,101, 99,104, 44, 32,114,101, 97,115,111,
 110, 41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110,
  32,116,114, 97,105,116, 95,109,111,100, 40,112,108, 97,121,
 101,114, 44, 32,116,114, 97,105,116, 44, 32,109,111,100, 41,
  10,114,101,116,117,114,110, 32,101,100,105,116, 46,116,114,
  97,105,116, 95,109,111,100, 40,112,108, 97,121,101,114, 44,
  32,116,114, 97,105,116, 44, 32,109,111,100, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32,117,110,108,101,
  97,115,104, 95, 98, 97,114, 98, 97,114,105, 97,110,115, 40,
 116,105,108,101, 41, 10,114,101,116,117,114,110, 32,101,100,
 105,116, 46,117,110,108,101, 97,115,104, 95, 98, 97,114, 98,
  97,114,105, 97,110,115, 40,116,105,108,101, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32,112,108, 97, 99,
 101, 95,112, 97,114,116,105,115, 97,110,115, 40,116,105,108,
 101, 44, 32,112,108, 97,121,101,114, 44, 32, 99,111,117,110,
 116, 44, 32,115,113, 95,114, 97,100,105,117,115, 41, 10,101,
 100,105,116, 46,112,108, 97, 99,101, 95,112, 97,114,116,105,
 115, 97,110,115, 40,116,105,108,101, 44, 32,112,108, 97,121,
 101,114, 44, 32, 99,111,117,110,116, 44, 32,115,113, 95,114,
  97,100,105,117,115, 41, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32, 80,108, 97,121,101,114, 58, 99,114,101,
  97,116,101, 95,117,110,105,116, 40,116,105,108,101, 44, 32,
 117,116,121,112,101, 44, 32,118,101,116,101,114, 97,110, 95,
 108,101,118,101,108, 44, 32,104,111,109,101, 99,105,116,121,
  44, 32,109,111,118,101,115, 95,108,101,102,116, 41, 10,114,
 101,116,117,114,110, 32,101,100,105,116, 46, 99,114,101, 97,
 116,101, 95,117,110,105,116, 40,115,101,108,102, 44, 32,116,
 105,108,101, 44, 32,117,116,121,112,101, 44, 32,118,101,116,
 101,114, 97,110, 95,108,101,118,101,108, 44, 32,104,111,109,
 101, 99,105,116,121, 44, 10,109,111,118,101,115, 95,108,101,
 102,116, 41, 10,101,110,100, 10,102,117,110, 99,116,105,111,
 110, 32, 80,108, 97,121,101,114, 58, 99,114,101, 97,116,101,
  95,117,110,105,116, 95,102,117,108,108, 40,116,105,108,101,
  44, 32,117,116,121,112,101, 44, 32,118,101,116,101,114, 97,
 110, 95,108,101,118,101,108, 44, 32,104,111,109,101, 99,105,
 116,121, 44, 10,109,111,118,101,115, 95,108,101,102,116, 44,
  32,104,112, 95,108,101,102,116, 44, 32,112,116,114, 97,110,
 115,112,111,114,116, 41, 10,114,101,116,117,114,110, 32,101,
 100,105,116, 46, 99,114,101, 97,116,101, 95,117,110,105,116,
  95,102,117,108,108, 40,115,101,108,102, 44, 32,116,105,108,
 101, 44, 32,117,116,121,112,101, 44, 32,118,101,116,101,114,
  97,110, 95,108,101,118,101,108, 44, 32,104,111,109,101, 99,
 105,116,121, 44, 10,109,111,118,101,115, 95,108,101,102,116,
  44, 32,104,112, 95,108,101,102,116, 44, 32,112,116,114, 97,
 110,115,112,111,114,116, 41, 10,101,110,100, 10,102,117,110,
  99,116,105,111,110, 32, 80,108, 97,121,101,114, 58, 99,105,
 118,105,108,105,122, 97,116,105,111,110, 95,115, 99,111,114,
 101, 40, 41, 10,114,101,116,117,114,110, 32,115,101,114,118,
 101,114, 46, 99,105,118,105,108,105,122, 97,116,105,111,110,
  95,115, 99,111,114,101, 40,115,101,108,102, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32, 80,108, 97,121,
 101,114, 58, 99,114,101, 97,116,101, 95, 99,105,116,121, 40,
 116,105,108,101, 44, 32,110, 97,109,101, 41, 10,101,100,105,
 116, 46, 99,114,101, 97,116,101, 95, 99,105,116,121, 40,115,
 101,108,102, 44, 32,116,105,108,101, 44, 32,110, 97,109,101,
  41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  80,108, 97,121,101,114, 58, 99,104, 97,110,103,101, 95,103,
 111,108,100, 40, 97,109,111,117,110,116, 41, 10,101,100,105,
 116, 46, 99,104, 97,110,103,101, 95,103,111,108,100, 40,115,
 101,108,102, 44, 32, 97,109,111,117,110,116, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32, 80,108, 97,121,
 101,114, 58,103,105,118,101, 95,116,101, 99,104,110,111,108,
 111,103,121, 40,116,101, 99,104, 44, 32,114,101, 97,115,111,
 110, 41, 10,114,101,116,117,114,110, 32,101,100,105,116, 46,
 103,105,118,101, 95,116,101, 99,104,110,111,108,111,103,121,
  40,115,101,108,102, 44, 32,116,101, 99,104, 44, 32,114,101,
  97,115,111,110, 41, 10,101,110,100, 10,102,117,110, 99,116,
 105,111,110, 32, 80,108, 97,121,101,114, 58,116,114, 97,105,
 116, 95,109,111,100, 40,116,114, 97,105,116, 44, 32,109,111,
 100, 41, 10,114,101,116,117,114,110, 32,101,100,105,116, 46,
 116,114, 97,105,116, 95,109,111,100, 40,115,101,108,102, 44,
  32,116,114, 97,105,116, 44, 32,109,111,100, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32, 80,108, 97,121,
 101,114, 58, 99,105,118,105,108, 95,119, 97,114, 40,112,114,
 111, 98, 97, 98,105,108,105,116,121, 41, 10,114,101,116,117,
 114,110, 32,101,100,105,116, 46, 99,105,118,105,108, 95,119,
  97,114, 40,115,101,108,102, 44, 32,112,114,111, 98, 97, 98,
 105,108,105,116,121, 41, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32, 80,108, 97,121,101,114, 58,118,105, 99,
 116,111,114,121, 40, 41, 10,101,100,105,116, 46,112,108, 97,
 121,101,114, 95,118,105, 99,116,111,114,121, 40,115,101,108,
 102, 41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110,
  32, 85,110,105,116, 58,116,101,108,101,112,111,114,116, 40,
 100,101,115,116, 41, 10,114,101,116,117,114,110, 32,101,100,
 105,116, 46,117,110,105,116, 95,116,101,108,101,112,111,114,
 116, 40,115,101,108,102, 44, 32,100,101,115,116, 41, 10,101,
 110,100, 10,102,117,110, 99,116,105,111,110, 32, 85,110,105,
 116, 58,116,117,114,110, 40,100,105,114,101, 99,116,105,111,
 110, 41, 10,101,100,105,116, 46,117,110,105,116, 95,116,117,
 114,110, 40,115,101,108,102, 44, 32,100,105,114,101, 99,116,
 105,111,110, 41, 10,101,110,100, 10,102,117,110, 99,116,105,
 111,110, 32, 85,110,105,116, 58,109,111,118,101, 40,109,111,
 118,101,116,111, 44, 32,109,111,118,101, 99,111,115,116, 41,
  10,114,101,116,117,114,110, 32,101,100,105,116, 46,117,110,
 105,116, 95,109,111,118,101, 40,115,101,108,102, 44, 32,109,
 111,118,101,116,111, 44, 32,109,111,118,101, 99,111,115,116,
  41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  84,105,108,101, 58, 99,114,101, 97,116,101, 95, 98, 97,115,
 101, 40,110, 97,109,101, 44, 32,112,108, 97,121,101,114, 41,
  10,101,100,105,116, 46, 99,114,101, 97,116,101, 95, 98, 97,
 115,101, 40,115,101,108,102, 44, 32,110, 97,109,101, 44, 32,
 112,108, 97,121,101,114, 41, 10,101,110,100, 10,102,117,110,
  99,116,105,111,110, 32, 84,105,108,101, 58, 99,114,101, 97,
 116,101, 95,114,111, 97,100, 40,110, 97,109,101, 41, 10,101,
 100,105,116, 46, 99,114,101, 97,116,101, 95,114,111, 97,100,
  40,115,101,108,102, 44, 32,110, 97,109,101, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32, 84,105,108,101,
  58,117,110,108,101, 97,115,104, 95, 98, 97,114, 98, 97,114,
 105, 97,110,115, 40, 41, 10,114,101,116,117,114,110, 32,101,
 100,105,116, 46,117,110,108,101, 97,115,104, 95, 98, 97,114,
  98, 97,114,105, 97,110,115, 40,115,101,108,102, 41, 10,101,
 110,100, 10,102,117,110, 99,116,105,111,110, 32, 84,105,108,
 101, 58,112,108, 97, 99,101, 95,112, 97,114,116,105,115, 97,
 110,115, 40,112,108, 97,121,101,114, 44, 32, 99,111,117,110,
 116, 44, 32,115,113, 95,114, 97,100,105,117,115, 41, 10,101,
 100,105,116, 46,112,108, 97, 99,101, 95,112, 97,114,116,105,
 115, 97,110,115, 40,115,101,108,102, 44, 32,112,108, 97,121,
 101,114, 44, 32, 99,111,117,110,116, 44, 32,115,113, 95,114,
  97,100,105,117,115, 41, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32, 84,105,108,101, 58,115,101,116, 95,108,
  97, 98,101,108, 40,108, 97, 98,101,108, 41, 10,101,100,105,
 116, 46,116,105,108,101, 95,115,101,116, 95,108, 97, 98,101,
 108, 40,115,101,108,102, 44, 32,108, 97, 98,101,108, 41, 10,
 101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_server_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_server);
 lua_pushstring(tolua_S, "server");
 lua_call(tolua_S, 1, 0);
 return 1;
}
