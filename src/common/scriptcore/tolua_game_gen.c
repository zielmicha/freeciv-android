/*
** Lua binding: game
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
TOLUA_API int tolua_game_open (lua_State* tolua_S);
LUALIB_API int luaopen_game (lua_State* tolua_S);

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif
#include "api_common_utilities.h"
#include "api_game_effects.h"
#include "api_game_find.h"
#include "api_game_methods.h"
#include "luascript_types.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Direction (lua_State* tolua_S)
{
 Direction* self = (Direction*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Nonexistent");
 tolua_usertype(tolua_S,"Direction");
 tolua_usertype(tolua_S,"Nation_Type");
 tolua_usertype(tolua_S,"City_List_Link");
 tolua_usertype(tolua_S,"Building_Type");
 tolua_usertype(tolua_S,"Terrain");
 tolua_usertype(tolua_S,"Tech_Type");
 tolua_usertype(tolua_S,"Unit");
 tolua_usertype(tolua_S,"Unit_List_Link");
 tolua_usertype(tolua_S,"Connection");
 tolua_usertype(tolua_S,"Disaster");
 tolua_usertype(tolua_S,"City");
 tolua_usertype(tolua_S,"Unit_Type");
 tolua_usertype(tolua_S,"Tile");
 tolua_usertype(tolua_S,"Government");
 tolua_usertype(tolua_S,"Player");
}

/* get function: name of class  Player */
static int tolua_get_Player_Player_name(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}

/* get function: nation of class  Player */
static int tolua_get_Player_Player_nation_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nation'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->nation,"Nation_Type");
 return 1;
}

/* set function: nation of class  Player */
static int tolua_set_Player_Player_nation_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nation'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Nation_Type",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nation = ((Nation_Type*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: ai_controlled of class  Player */
static int tolua_get_Player_Player_ai_controlled(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ai_controlled'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->ai_controlled);
 return 1;
}

/* set function: ai_controlled of class  Player */
static int tolua_set_Player_Player_ai_controlled(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ai_controlled'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ai_controlled = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: is_alive of class  Player */
static int tolua_get_Player_Player_is_alive(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'is_alive'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->is_alive);
 return 1;
}

/* set function: is_alive of class  Player */
static int tolua_set_Player_Player_is_alive(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'is_alive'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->is_alive = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: name of class  City */
static int tolua_get_City_City_name(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}

/* get function: owner of class  City */
static int tolua_get_City_City_owner_ptr(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'owner'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->owner,"Player");
 return 1;
}

/* set function: owner of class  City */
static int tolua_set_City_City_owner_ptr(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'owner'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Player",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->owner = ((Player*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: original of class  City */
static int tolua_get_City_City_original_ptr(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'original'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->original,"Player");
 return 1;
}

/* set function: original of class  City */
static int tolua_set_City_City_original_ptr(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'original'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Player",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->original = ((Player*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: id of class  City */
static int tolua_get_City_City_id(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->id);
 return 1;
}

/* get function: id of class  Connection */
static int tolua_get_Connection_Connection_id(lua_State* tolua_S)
{
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->id);
 return 1;
}

/* get function: utype of class  Unit */
static int tolua_get_Unit_Unit_utype_ptr(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'utype'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->utype,"Unit_Type");
 return 1;
}

/* set function: utype of class  Unit */
static int tolua_set_Unit_Unit_utype_ptr(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'utype'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Unit_Type",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->utype = ((Unit_Type*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: owner of class  Unit */
static int tolua_get_Unit_Unit_owner_ptr(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'owner'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->owner,"Player");
 return 1;
}

/* set function: owner of class  Unit */
static int tolua_set_Unit_Unit_owner_ptr(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'owner'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Player",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->owner = ((Player*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: homecity of class  Unit */
static int tolua_get_Unit_Unit_homecity(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'homecity'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->homecity);
 return 1;
}

/* set function: homecity of class  Unit */
static int tolua_set_Unit_Unit_homecity(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'homecity'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->homecity = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: id of class  Unit */
static int tolua_get_Unit_Unit_id(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->id);
 return 1;
}

/* get function: terrain of class  Tile */
static int tolua_get_Tile_Tile_terrain_ptr(lua_State* tolua_S)
{
  Tile* self = (Tile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'terrain'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->terrain,"Terrain");
 return 1;
}

/* set function: terrain of class  Tile */
static int tolua_set_Tile_Tile_terrain_ptr(lua_State* tolua_S)
{
  Tile* self = (Tile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'terrain'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Terrain",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->terrain = ((Terrain*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: index of class  Tile */
static int tolua_get_Tile_Tile_index(lua_State* tolua_S)
{
  Tile* self = (Tile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'index'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->index);
 return 1;
}

/* get function: item_number of class  Government */
static int tolua_get_Government_Government_item_number(lua_State* tolua_S)
{
  Government* self = (Government*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'item_number'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->item_number);
 return 1;
}

/* get function: item_number of class  Nation_Type */
static int tolua_get_Nation_Type_Nation_Type_item_number(lua_State* tolua_S)
{
  Nation_Type* self = (Nation_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'item_number'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->item_number);
 return 1;
}

/* get function: build_cost of class  Building_Type */
static int tolua_get_Building_Type_Building_Type_build_cost(lua_State* tolua_S)
{
  Building_Type* self = (Building_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'build_cost'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->build_cost);
 return 1;
}

/* set function: build_cost of class  Building_Type */
static int tolua_set_Building_Type_Building_Type_build_cost(lua_State* tolua_S)
{
  Building_Type* self = (Building_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'build_cost'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->build_cost = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: item_number of class  Building_Type */
static int tolua_get_Building_Type_Building_Type_item_number(lua_State* tolua_S)
{
  Building_Type* self = (Building_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'item_number'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->item_number);
 return 1;
}

/* get function: build_cost of class  Unit_Type */
static int tolua_get_Unit_Type_Unit_Type_build_cost(lua_State* tolua_S)
{
  Unit_Type* self = (Unit_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'build_cost'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->build_cost);
 return 1;
}

/* set function: build_cost of class  Unit_Type */
static int tolua_set_Unit_Type_Unit_Type_build_cost(lua_State* tolua_S)
{
  Unit_Type* self = (Unit_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'build_cost'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->build_cost = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: item_number of class  Unit_Type */
static int tolua_get_Unit_Type_Unit_Type_item_number(lua_State* tolua_S)
{
  Unit_Type* self = (Unit_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'item_number'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->item_number);
 return 1;
}

/* get function: item_number of class  Tech_Type */
static int tolua_get_Tech_Type_Tech_Type_item_number(lua_State* tolua_S)
{
  Tech_Type* self = (Tech_Type*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'item_number'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->item_number);
 return 1;
}

/* get function: item_number of class  Terrain */
static int tolua_get_Terrain_Terrain_item_number(lua_State* tolua_S)
{
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'item_number'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->item_number);
 return 1;
}

/* get function: id of class  Disaster */
static int tolua_get_Disaster_Disaster_id(lua_State* tolua_S)
{
  Disaster* self = (Disaster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->id);
 return 1;
}

/* function: api_methods_game_turn */
static int tolua_game_game_turn00(lua_State* tolua_S)
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
  int tolua_ret = (int)  api_methods_game_turn(L);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'turn'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_number */
static int tolua_game_Player_properties_id00(lua_State* tolua_S)
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
  int tolua_ret = (int)  api_methods_player_number(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'id'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_num_cities */
static int tolua_game_Player_num_cities00(lua_State* tolua_S)
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
  int tolua_ret = (int)  api_methods_player_num_cities(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'num_cities'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_num_units */
static int tolua_game_Player_num_units00(lua_State* tolua_S)
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
  int tolua_ret = (int)  api_methods_player_num_units(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'num_units'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_has_wonder */
static int tolua_game_Player_has_wonder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Building_Type* building = ((Building_Type*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_player_has_wonder(L,self,building);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'has_wonder'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_gold */
static int tolua_game_Player_gold00(lua_State* tolua_S)
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
  int tolua_ret = (int)  api_methods_player_gold(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gold'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_knows_tech */
static int tolua_game_Player_knows_tech00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tech_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tech_Type* ptech = ((Tech_Type*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_player_knows_tech(L,self,ptech);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'knows_tech'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_shares_research */
static int tolua_game_Player_shares_research00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Player* other = ((Player*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_player_shares_research(L,self,other);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shares_research'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_private_player_unit_list_head */
static int tolua_game_methods_private_Player_unit_list_head00(lua_State* tolua_S)
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
  Unit_List_Link* tolua_ret = (Unit_List_Link*)  api_methods_private_player_unit_list_head(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit_List_Link");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit_list_head'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_private_player_city_list_head */
static int tolua_game_methods_private_Player_city_list_head00(lua_State* tolua_S)
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
  City_List_Link* tolua_ret = (City_List_Link*)  api_methods_private_player_city_list_head(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"City_List_Link");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'city_list_head'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_city_size_get */
static int tolua_game_City_properties_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City* self = ((City*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_city_size_get(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_city_tile_get */
static int tolua_game_City_properties_tile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City* self = ((City*)  tolua_tousertype(tolua_S,1,0));
 {
  Tile* tolua_ret = (Tile*)  api_methods_city_tile_get(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tile'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_city_has_building */
static int tolua_game_City_has_building00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City* self = ((City*)  tolua_tousertype(tolua_S,1,0));
  Building_Type* building = ((Building_Type*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_city_has_building(L,self,building);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'has_building'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_city_map_sq_radius */
static int tolua_game_City_map_sq_radius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City* self = ((City*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_city_map_sq_radius(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'map_sq_radius'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_city_inspire_partisans */
static int tolua_game_City_inspire_partisans00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City* self = ((City*)  tolua_tousertype(tolua_S,1,0));
  Player* inspirer = ((Player*)  tolua_tousertype(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_methods_city_inspire_partisans(L,self,inspirer);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'inspire_partisans'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_tile_get */
static int tolua_game_Unit_properties_tile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit* self = ((Unit*)  tolua_tousertype(tolua_S,1,0));
 {
  Tile* tolua_ret = (Tile*)  api_methods_unit_tile_get(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tile'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_city_can_be_built_here */
static int tolua_game_Unit_is_on_possible_city_tile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit* self = ((Unit*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_city_can_be_built_here(L,self);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'is_on_possible_city_tile'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_orientation_get */
static int tolua_game_Unit_facing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit* self = ((Unit*)  tolua_tousertype(tolua_S,1,0));
 {
  Direction tolua_ret =  api_methods_unit_orientation_get(L,self);
 {
#ifdef __cplusplus
 void* tolua_obj = new Direction(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_Direction),"Direction");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Direction));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"Direction");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'facing'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_nat_x */
static int tolua_game_Tile_properties_nat_x00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_tile_nat_x(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nat_x'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_nat_y */
static int tolua_game_Tile_properties_nat_y00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_tile_nat_y(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nat_y'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_map_x */
static int tolua_game_Tile_properties_x00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_tile_map_x(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_map_y */
static int tolua_game_Tile_properties_y00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_tile_map_y(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_city */
static int tolua_game_Tile_city00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  City* tolua_ret = (City*)  api_methods_tile_city(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"City");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'city'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_city_exists_within_max_city_map */
static int tolua_game_Tile_city_exists_within_max_city_map00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isboolean(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  bool center = ((bool)  tolua_toboolean(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_tile_city_exists_within_max_city_map(L,self,center);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'city_exists_within_max_city_map'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_has_base */
static int tolua_game_Tile_has_base00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_tile_has_base(L,self,name);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'has_base'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_has_road */
static int tolua_game_Tile_has_road00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_tile_has_road(L,self,name);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'has_road'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_num_units */
static int tolua_game_Tile_num_units00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_tile_num_units(L,self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'num_units'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tile_sq_distance */
static int tolua_game_Tile_sq_distance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  Tile* other = ((Tile*)  tolua_tousertype(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_methods_tile_sq_distance(L,self,other);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sq_distance'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_private_tile_next_outward_index */
static int tolua_game_methods_private_Tile_next_outward_index00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* pcenter = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int max_dist = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  int tolua_ret = (int)  api_methods_private_tile_next_outward_index(L,pcenter,index,max_dist);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'next_outward_index'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_private_tile_for_outward_index */
static int tolua_game_methods_private_Tile_tile_for_outward_index00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tile* pcenter = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Tile* tolua_ret = (Tile*)  api_methods_private_tile_for_outward_index(L,pcenter,index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tile_for_outward_index'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_private_tile_unit_list_head */
static int tolua_game_methods_private_Tile_unit_list_head00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  Unit_List_Link* tolua_ret = (Unit_List_Link*)  api_methods_private_tile_unit_list_head(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit_List_Link");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit_list_head'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_government_rule_name */
static int tolua_game_Government_rule_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Government",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Government* self = ((Government*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_government_rule_name(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule_name'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_government_name_translation */
static int tolua_game_Government_name_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Government",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Government* self = ((Government*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_government_name_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_nation_type_rule_name */
static int tolua_game_Nation_Type_rule_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Nation_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Nation_Type* self = ((Nation_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_nation_type_rule_name(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule_name'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_nation_type_name_translation */
static int tolua_game_Nation_Type_name_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Nation_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Nation_Type* self = ((Nation_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_nation_type_name_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_nation_type_plural_translation */
static int tolua_game_Nation_Type_plural_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Nation_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Nation_Type* self = ((Nation_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_nation_type_plural_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'plural_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_building_type_is_wonder */
static int tolua_game_Building_Type_is_wonder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_wonder(L,self);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'is_wonder'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_building_type_is_great_wonder */
static int tolua_game_Building_Type_is_great_wonder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_great_wonder(L,self);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'is_great_wonder'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_building_type_is_small_wonder */
static int tolua_game_Building_Type_is_small_wonder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_small_wonder(L,self);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'is_small_wonder'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_building_type_is_improvement */
static int tolua_game_Building_Type_is_improvement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_improvement(L,self);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'is_improvement'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_building_type_rule_name */
static int tolua_game_Building_Type_rule_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_building_type_rule_name(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule_name'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_building_type_name_translation */
static int tolua_game_Building_Type_name_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Building_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_building_type_name_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_type_has_flag */
static int tolua_game_Unit_Type_has_flag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit_Type",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
  const char* flag = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_type_has_flag(L,self,flag);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'has_flag'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_type_has_role */
static int tolua_game_Unit_Type_has_role00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit_Type",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
  const char* role = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_type_has_role(L,self,role);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'has_role'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_type_rule_name */
static int tolua_game_Unit_Type_rule_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_unit_type_rule_name(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule_name'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_type_name_translation */
static int tolua_game_Unit_Type_name_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_unit_type_name_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_type_can_exist_at_tile */
static int tolua_game_Unit_Type_can_exist_at_tile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit_Type",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_type_can_exist_at_tile(L,self,ptile);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'can_exist_at_tile'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tech_type_rule_name */
static int tolua_game_Tech_Type_rule_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tech_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tech_Type* self = ((Tech_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_tech_type_rule_name(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule_name'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_tech_type_name_translation */
static int tolua_game_Tech_Type_name_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Tech_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Tech_Type* self = ((Tech_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_tech_type_name_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_terrain_rule_name */
static int tolua_game_Terrain_rule_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Terrain* self = ((Terrain*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_terrain_rule_name(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule_name'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_terrain_name_translation */
static int tolua_game_Terrain_name_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Terrain* self = ((Terrain*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_terrain_name_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_disaster_rule_name */
static int tolua_game_Disaster_rule_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Disaster",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Disaster* self = ((Disaster*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_disaster_rule_name(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule_name'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_disaster_name_translation */
static int tolua_game_Disaster_name_translation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Disaster",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Disaster* self = ((Disaster*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_disaster_name_translation(L,self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name_translation'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_list_link_data */
static int tolua_game_Unit_List_Link_data00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit_List_Link",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit_List_Link* self = ((Unit_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  Unit* tolua_ret = (Unit*)  api_methods_unit_list_link_data(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'data'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_unit_list_next_link */
static int tolua_game_Unit_List_Link_next00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit_List_Link",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Unit_List_Link* self = ((Unit_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  Unit_List_Link* tolua_ret = (Unit_List_Link*)  api_methods_unit_list_next_link(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit_List_Link");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'next'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_city_list_link_data */
static int tolua_game_City_List_Link_data00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City_List_Link",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City_List_Link* self = ((City_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  City* tolua_ret = (City*)  api_methods_city_list_link_data(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"City");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'data'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_city_list_next_link */
static int tolua_game_City_List_Link_next00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City_List_Link",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City_List_Link* self = ((City_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  City_List_Link* tolua_ret = (City_List_Link*)  api_methods_city_list_next_link(L,self);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"City_List_Link");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'next'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_player */
static int tolua_game_find_player00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  int player_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Player* tolua_ret = (Player*)  api_find_player(L,player_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'player'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_city */
static int tolua_game_find_city00(lua_State* tolua_S)
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
  int city_id = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  City* tolua_ret = (City*)  api_find_city(L,pplayer,city_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"City");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'city'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_unit */
static int tolua_game_find_unit00(lua_State* tolua_S)
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
  int unit_id = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Unit* tolua_ret = (Unit*)  api_find_unit(L,pplayer,unit_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_transport_unit */
static int tolua_game_find_transport_unit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Unit_Type",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"Tile",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Unit_Type* ptype = ((Unit_Type*)  tolua_tousertype(tolua_S,2,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,3,0));
 {
  Unit* tolua_ret = (Unit*)  api_find_transport_unit(L,pplayer,ptype,ptile);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'transport_unit'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_tile */
static int tolua_game_find_tile00(lua_State* tolua_S)
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
  int nat_x = ((int)  tolua_tonumber(tolua_S,1,0));
  int nat_y = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Tile* tolua_ret = (Tile*)  api_find_tile(L,nat_x,nat_y);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tile'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_tile_by_index */
static int tolua_game_find_tile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  lua_State* L =  tolua_S;
  int index = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Tile* tolua_ret = (Tile*)  api_find_tile_by_index(L,index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
 }
 }
 return 1;
tolua_lerror:
 return tolua_game_find_tile00(tolua_S);
}

/* function: api_find_government_by_name */
static int tolua_game_find_government00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Government* tolua_ret = (Government*)  api_find_government_by_name(L,name_orig);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Government");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'government'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_government */
static int tolua_game_find_government01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  lua_State* L =  tolua_S;
  int government_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Government* tolua_ret = (Government*)  api_find_government(L,government_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Government");
 }
 }
 return 1;
tolua_lerror:
 return tolua_game_find_government00(tolua_S);
}

/* function: api_find_nation_type_by_name */
static int tolua_game_find_nation_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Nation_Type* tolua_ret = (Nation_Type*)  api_find_nation_type_by_name(L,name_orig);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Nation_Type");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nation_type'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_nation_type */
static int tolua_game_find_nation_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  lua_State* L =  tolua_S;
  int nation_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Nation_Type* tolua_ret = (Nation_Type*)  api_find_nation_type(L,nation_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Nation_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_game_find_nation_type00(tolua_S);
}

/* function: api_find_building_type_by_name */
static int tolua_game_find_building_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Building_Type* tolua_ret = (Building_Type*)  api_find_building_type_by_name(L,name_orig);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Building_Type");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'building_type'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_building_type */
static int tolua_game_find_building_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  lua_State* L =  tolua_S;
  int building_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Building_Type* tolua_ret = (Building_Type*)  api_find_building_type(L,building_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Building_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_game_find_building_type00(tolua_S);
}

/* function: api_find_unit_type_by_name */
static int tolua_game_find_unit_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Unit_Type* tolua_ret = (Unit_Type*)  api_find_unit_type_by_name(L,name_orig);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit_Type");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit_type'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_unit_type */
static int tolua_game_find_unit_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  lua_State* L =  tolua_S;
  int unit_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Unit_Type* tolua_ret = (Unit_Type*)  api_find_unit_type(L,unit_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_game_find_unit_type00(tolua_S);
}

/* function: api_find_role_unit_type */
static int tolua_game_find_role_unit_type00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  const char* role_name = ((const char*)  tolua_tostring(tolua_S,1,0));
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
 {
  Unit_Type* tolua_ret = (Unit_Type*)  api_find_role_unit_type(L,role_name,pplayer);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit_Type");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'role_unit_type'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_tech_type_by_name */
static int tolua_game_find_tech_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Tech_Type* tolua_ret = (Tech_Type*)  api_find_tech_type_by_name(L,name_orig);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tech_Type");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tech_type'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_tech_type */
static int tolua_game_find_tech_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  lua_State* L =  tolua_S;
  int tech_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Tech_Type* tolua_ret = (Tech_Type*)  api_find_tech_type(L,tech_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tech_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_game_find_tech_type00(tolua_S);
}

/* function: api_find_terrain_by_name */
static int tolua_game_find_terrain00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Terrain* tolua_ret = (Terrain*)  api_find_terrain_by_name(L,name_orig);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Terrain");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'terrain'.",&tolua_err);
 return 0;
#endif
}

/* function: api_find_terrain */
static int tolua_game_find_terrain01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  lua_State* L =  tolua_S;
  int terrain_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Terrain* tolua_ret = (Terrain*)  api_find_terrain(L,terrain_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Terrain");
 }
 }
 return 1;
tolua_lerror:
 return tolua_game_find_terrain00(tolua_S);
}

/* function: api_find_nonexistent */
static int tolua_game_find_nonexistent00(lua_State* tolua_S)
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
  Nonexistent* tolua_ret = (Nonexistent*)  api_find_nonexistent(L);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Nonexistent");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nonexistent'.",&tolua_err);
 return 0;
#endif
}

/* function: api_effects_world_bonus */
static int tolua_game_effects_world_bonus00(lua_State* tolua_S)
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
  const char* effect_type = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_effects_world_bonus(L,effect_type);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'world_bonus'.",&tolua_err);
 return 0;
#endif
}

/* function: api_effects_player_bonus */
static int tolua_game_effects_player_bonus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  const char* effect_type = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_effects_player_bonus(L,pplayer,effect_type);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'player_bonus'.",&tolua_err);
 return 0;
#endif
}

/* function: api_effects_city_bonus */
static int tolua_game_effects_city_bonus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"City",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  City* pcity = ((City*)  tolua_tousertype(tolua_S,1,0));
  const char* effect_type = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_effects_city_bonus(L,pcity,effect_type);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'city_bonus'.",&tolua_err);
 return 0;
#endif
}

/* function: api_utilities_str2dir */
static int tolua_game_direction_str2dir00(lua_State* tolua_S)
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
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Direction tolua_ret =  api_utilities_str2dir(L,str);
 {
#ifdef __cplusplus
 void* tolua_obj = new Direction(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_Direction),"Direction");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Direction));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"Direction");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'str2dir'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_game (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"Player","Player","",NULL);
 tolua_beginmodule(tolua_S,"Player");
 tolua_variable(tolua_S,"name",tolua_get_Player_Player_name,NULL);
 tolua_variable(tolua_S,"nation",tolua_get_Player_Player_nation_ptr,tolua_set_Player_Player_nation_ptr);
 tolua_variable(tolua_S,"ai_controlled",tolua_get_Player_Player_ai_controlled,tolua_set_Player_Player_ai_controlled);
 tolua_variable(tolua_S,"is_alive",tolua_get_Player_Player_is_alive,tolua_set_Player_Player_is_alive);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"City","City","",NULL);
 tolua_beginmodule(tolua_S,"City");
 tolua_variable(tolua_S,"name",tolua_get_City_City_name,NULL);
 tolua_variable(tolua_S,"owner",tolua_get_City_City_owner_ptr,tolua_set_City_City_owner_ptr);
 tolua_variable(tolua_S,"original",tolua_get_City_City_original_ptr,tolua_set_City_City_original_ptr);
 tolua_variable(tolua_S,"id",tolua_get_City_City_id,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Connection","Connection","",NULL);
 tolua_beginmodule(tolua_S,"Connection");
 tolua_variable(tolua_S,"id",tolua_get_Connection_Connection_id,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Unit","Unit","",NULL);
 tolua_beginmodule(tolua_S,"Unit");
 tolua_variable(tolua_S,"utype",tolua_get_Unit_Unit_utype_ptr,tolua_set_Unit_Unit_utype_ptr);
 tolua_variable(tolua_S,"owner",tolua_get_Unit_Unit_owner_ptr,tolua_set_Unit_Unit_owner_ptr);
 tolua_variable(tolua_S,"homecity",tolua_get_Unit_Unit_homecity,tolua_set_Unit_Unit_homecity);
 tolua_variable(tolua_S,"id",tolua_get_Unit_Unit_id,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Tile","Tile","",NULL);
 tolua_beginmodule(tolua_S,"Tile");
 tolua_variable(tolua_S,"terrain",tolua_get_Tile_Tile_terrain_ptr,tolua_set_Tile_Tile_terrain_ptr);
 tolua_variable(tolua_S,"id",tolua_get_Tile_Tile_index,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Government","Government","",NULL);
 tolua_beginmodule(tolua_S,"Government");
 tolua_variable(tolua_S,"id",tolua_get_Government_Government_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Nation_Type","Nation_Type","",NULL);
 tolua_beginmodule(tolua_S,"Nation_Type");
 tolua_variable(tolua_S,"id",tolua_get_Nation_Type_Nation_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Building_Type","Building_Type","",NULL);
 tolua_beginmodule(tolua_S,"Building_Type");
 tolua_variable(tolua_S,"build_cost",tolua_get_Building_Type_Building_Type_build_cost,tolua_set_Building_Type_Building_Type_build_cost);
 tolua_variable(tolua_S,"id",tolua_get_Building_Type_Building_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Unit_Type","Unit_Type","",NULL);
 tolua_beginmodule(tolua_S,"Unit_Type");
 tolua_variable(tolua_S,"build_cost",tolua_get_Unit_Type_Unit_Type_build_cost,tolua_set_Unit_Type_Unit_Type_build_cost);
 tolua_variable(tolua_S,"id",tolua_get_Unit_Type_Unit_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Tech_Type","Tech_Type","",NULL);
 tolua_beginmodule(tolua_S,"Tech_Type");
 tolua_variable(tolua_S,"id",tolua_get_Tech_Type_Tech_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Terrain","Terrain","",NULL);
 tolua_beginmodule(tolua_S,"Terrain");
 tolua_variable(tolua_S,"id",tolua_get_Terrain_Terrain_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Disaster","Disaster","",NULL);
 tolua_beginmodule(tolua_S,"Disaster");
 tolua_variable(tolua_S,"id",tolua_get_Disaster_Disaster_id,NULL);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Unit_List_Link","Unit_List_Link","",NULL);
 tolua_beginmodule(tolua_S,"Unit_List_Link");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"City_List_Link","City_List_Link","",NULL);
 tolua_beginmodule(tolua_S,"City_List_Link");
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"game",0);
 tolua_beginmodule(tolua_S,"game");
 tolua_function(tolua_S,"turn",tolua_game_game_turn00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Player",0);
 tolua_beginmodule(tolua_S,"Player");
 tolua_module(tolua_S,"properties",0);
 tolua_beginmodule(tolua_S,"properties");
 tolua_function(tolua_S,"id",tolua_game_Player_properties_id00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"num_cities",tolua_game_Player_num_cities00);
 tolua_function(tolua_S,"num_units",tolua_game_Player_num_units00);
 tolua_function(tolua_S,"has_wonder",tolua_game_Player_has_wonder00);
 tolua_function(tolua_S,"gold",tolua_game_Player_gold00);
 tolua_function(tolua_S,"knows_tech",tolua_game_Player_knows_tech00);
 tolua_function(tolua_S,"shares_research",tolua_game_Player_shares_research00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"methods_private",0);
 tolua_beginmodule(tolua_S,"methods_private");
 tolua_module(tolua_S,"Player",0);
 tolua_beginmodule(tolua_S,"Player");
 tolua_function(tolua_S,"unit_list_head",tolua_game_methods_private_Player_unit_list_head00);
 tolua_function(tolua_S,"city_list_head",tolua_game_methods_private_Player_city_list_head00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 80,108, 97,121,101,
 114, 58,105,115, 95,104,117,109, 97,110, 40, 41, 10,114,101,
 116,117,114,110, 32,110,111,116, 32,115,101,108,102, 46, 97,
 105, 95, 99,111,110,116,114,111,108,108,101,100, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32, 80,108, 97,121,
 101,114, 58,101,120,105,115,116,115, 40, 41, 10,114,101,116,
 117,114,110, 32,116,114,117,101, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"City",0);
 tolua_beginmodule(tolua_S,"City");
 tolua_module(tolua_S,"properties",0);
 tolua_beginmodule(tolua_S,"properties");
 tolua_function(tolua_S,"size",tolua_game_City_properties_size00);
 tolua_function(tolua_S,"tile",tolua_game_City_properties_tile00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"has_building",tolua_game_City_has_building00);
 tolua_function(tolua_S,"map_sq_radius",tolua_game_City_map_sq_radius00);
 tolua_function(tolua_S,"inspire_partisans",tolua_game_City_inspire_partisans00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 67,105,116,121, 58,
 101,120,105,115,116,115, 40, 41, 10,114,101,116,117,114,110,
  32,116,114,117,101, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"Unit",0);
 tolua_beginmodule(tolua_S,"Unit");
 tolua_module(tolua_S,"properties",0);
 tolua_beginmodule(tolua_S,"properties");
 tolua_function(tolua_S,"tile",tolua_game_Unit_properties_tile00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"is_on_possible_city_tile",tolua_game_Unit_is_on_possible_city_tile00);
 tolua_function(tolua_S,"facing",tolua_game_Unit_facing00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 85,110,105,116, 58,
 101,120,105,115,116,115, 40, 41, 10,114,101,116,117,114,110,
  32,116,114,117,101, 10,101,110,100, 10,102,117,110, 99,116,
 105,111,110, 32, 85,110,105,116, 58,103,101,116, 95,104,111,
 109,101, 99,105,116,121, 40, 41, 10,114,101,116,117,114,110,
  32,102,105,110,100, 46, 99,105,116,121, 40,115,101,108,102,
  46,111,119,110,101,114, 44, 32,115,101,108,102, 46,104,111,
 109,101, 99,105,116,121, 41, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"Tile",0);
 tolua_beginmodule(tolua_S,"Tile");
 tolua_module(tolua_S,"properties",0);
 tolua_beginmodule(tolua_S,"properties");
 tolua_function(tolua_S,"nat_x",tolua_game_Tile_properties_nat_x00);
 tolua_function(tolua_S,"nat_y",tolua_game_Tile_properties_nat_y00);
 tolua_function(tolua_S,"x",tolua_game_Tile_properties_x00);
 tolua_function(tolua_S,"y",tolua_game_Tile_properties_y00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"city",tolua_game_Tile_city00);
 tolua_function(tolua_S,"city_exists_within_max_city_map",tolua_game_Tile_city_exists_within_max_city_map00);
 tolua_function(tolua_S,"has_base",tolua_game_Tile_has_base00);
 tolua_function(tolua_S,"has_road",tolua_game_Tile_has_road00);
 tolua_function(tolua_S,"num_units",tolua_game_Tile_num_units00);
 tolua_function(tolua_S,"sq_distance",tolua_game_Tile_sq_distance00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 84,105,108,101, 58,
  99,105,116,121, 95,101,120,105,115,116,115, 95,119,105,116,
 104,105,110, 95, 99,105,116,121, 95,114, 97,100,105,117,115,
  40, 99,101,110,116,101,114, 41, 10,114,101,116,117,114,110,
  32,115,101,108,102, 58, 99,105,116,121, 95,101,120,105,115,
 116,115, 95,119,105,116,104,105,110, 95,109, 97,120, 95, 99,
 105,116,121, 95,109, 97,112, 40, 99,101,110,116,101,114, 41,
  10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"methods_private",0);
 tolua_beginmodule(tolua_S,"methods_private");
 tolua_module(tolua_S,"Tile",0);
 tolua_beginmodule(tolua_S,"Tile");
 tolua_function(tolua_S,"next_outward_index",tolua_game_methods_private_Tile_next_outward_index00);
 tolua_function(tolua_S,"tile_for_outward_index",tolua_game_methods_private_Tile_tile_for_outward_index00);
 tolua_function(tolua_S,"unit_list_head",tolua_game_methods_private_Tile_unit_list_head00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Government",0);
 tolua_beginmodule(tolua_S,"Government");
 tolua_function(tolua_S,"rule_name",tolua_game_Government_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_game_Government_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Nation_Type",0);
 tolua_beginmodule(tolua_S,"Nation_Type");
 tolua_function(tolua_S,"rule_name",tolua_game_Nation_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_game_Nation_Type_name_translation00);
 tolua_function(tolua_S,"plural_translation",tolua_game_Nation_Type_plural_translation00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Building_Type",0);
 tolua_beginmodule(tolua_S,"Building_Type");
 tolua_function(tolua_S,"is_wonder",tolua_game_Building_Type_is_wonder00);
 tolua_function(tolua_S,"is_great_wonder",tolua_game_Building_Type_is_great_wonder00);
 tolua_function(tolua_S,"is_small_wonder",tolua_game_Building_Type_is_small_wonder00);
 tolua_function(tolua_S,"is_improvement",tolua_game_Building_Type_is_improvement00);
 tolua_function(tolua_S,"rule_name",tolua_game_Building_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_game_Building_Type_name_translation00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 66,117,105,108,100,
 105,110,103, 95, 84,121,112,101, 58, 98,117,105,108,100, 95,
 115,104,105,101,108,100, 95, 99,111,115,116, 40, 41, 10,114,
 101,116,117,114,110, 32,115,101,108,102, 46, 98,117,105,108,
 100, 95, 99,111,115,116, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"Unit_Type",0);
 tolua_beginmodule(tolua_S,"Unit_Type");
 tolua_function(tolua_S,"has_flag",tolua_game_Unit_Type_has_flag00);
 tolua_function(tolua_S,"has_role",tolua_game_Unit_Type_has_role00);
 tolua_function(tolua_S,"rule_name",tolua_game_Unit_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_game_Unit_Type_name_translation00);
 tolua_function(tolua_S,"can_exist_at_tile",tolua_game_Unit_Type_can_exist_at_tile00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 85,110,105,116, 95,
  84,121,112,101, 58, 98,117,105,108,100, 95,115,104,105,101,
 108,100, 95, 99,111,115,116, 40, 41, 10,114,101,116,117,114,
 110, 32,115,101,108,102, 46, 98,117,105,108,100, 95, 99,111,
 115,116, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"Tech_Type",0);
 tolua_beginmodule(tolua_S,"Tech_Type");
 tolua_function(tolua_S,"rule_name",tolua_game_Tech_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_game_Tech_Type_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Terrain",0);
 tolua_beginmodule(tolua_S,"Terrain");
 tolua_function(tolua_S,"rule_name",tolua_game_Terrain_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_game_Terrain_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Disaster",0);
 tolua_beginmodule(tolua_S,"Disaster");
 tolua_function(tolua_S,"rule_name",tolua_game_Disaster_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_game_Disaster_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Unit_List_Link",0);
 tolua_beginmodule(tolua_S,"Unit_List_Link");
 tolua_function(tolua_S,"data",tolua_game_Unit_List_Link_data00);
 tolua_function(tolua_S,"next",tolua_game_Unit_List_Link_next00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"City_List_Link",0);
 tolua_beginmodule(tolua_S,"City_List_Link");
 tolua_function(tolua_S,"data",tolua_game_City_List_Link_data00);
 tolua_function(tolua_S,"next",tolua_game_City_List_Link_next00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"find",0);
 tolua_beginmodule(tolua_S,"find");
 tolua_function(tolua_S,"player",tolua_game_find_player00);
 tolua_function(tolua_S,"city",tolua_game_find_city00);
 tolua_function(tolua_S,"unit",tolua_game_find_unit00);
 tolua_function(tolua_S,"transport_unit",tolua_game_find_transport_unit00);
 tolua_function(tolua_S,"tile",tolua_game_find_tile00);
 tolua_function(tolua_S,"tile",tolua_game_find_tile01);
 tolua_function(tolua_S,"government",tolua_game_find_government00);
 tolua_function(tolua_S,"government",tolua_game_find_government01);
 tolua_function(tolua_S,"nation_type",tolua_game_find_nation_type00);
 tolua_function(tolua_S,"nation_type",tolua_game_find_nation_type01);
 tolua_function(tolua_S,"building_type",tolua_game_find_building_type00);
 tolua_function(tolua_S,"building_type",tolua_game_find_building_type01);
 tolua_function(tolua_S,"unit_type",tolua_game_find_unit_type00);
 tolua_function(tolua_S,"unit_type",tolua_game_find_unit_type01);
 tolua_function(tolua_S,"role_unit_type",tolua_game_find_role_unit_type00);
 tolua_function(tolua_S,"tech_type",tolua_game_find_tech_type00);
 tolua_function(tolua_S,"tech_type",tolua_game_find_tech_type01);
 tolua_function(tolua_S,"terrain",tolua_game_find_terrain00);
 tolua_function(tolua_S,"terrain",tolua_game_find_terrain01);
 tolua_function(tolua_S,"nonexistent",tolua_game_find_nonexistent00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"E",0);
 tolua_beginmodule(tolua_S,"E");
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"effects",0);
 tolua_beginmodule(tolua_S,"effects");
 tolua_function(tolua_S,"world_bonus",tolua_game_effects_world_bonus00);
 tolua_function(tolua_S,"player_bonus",tolua_game_effects_player_bonus00);
 tolua_function(tolua_S,"city_bonus",tolua_game_effects_city_bonus00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"direction",0);
 tolua_beginmodule(tolua_S,"direction");
 tolua_function(tolua_S,"str2dir",tolua_game_direction_str2dir00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,115,116,114, 50,100,
 105,114,101, 99,116,105,111,110, 40,115,116,114, 41, 10,114,
 101,116,117,114,110, 32,100,105,114,101, 99,116,105,111,110,
  46,115,116,114, 50,100,105,114, 40,115,116,114, 41, 10,101,
 110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */


 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,100,111, 10,108,111, 99, 97,108, 32,112,114,105,118, 97,
 116,101, 32, 61, 32,109,101,116,104,111,100,115, 95,112,114,
 105,118, 97,116,101, 10,108,111, 99, 97,108, 32,102,117,110,
  99,116,105,111,110, 32,118, 97,108,117,101, 95,105,116,101,
 114, 97,116,111,114, 40, 97,114,114, 97,121, 41, 10,108,111,
  99, 97,108, 32,105, 32, 61, 32, 48, 10,108,111, 99, 97,108,
  32,102,117,110, 99,116,105,111,110, 32,105,116,101,114, 97,
 116,111,114, 40, 41, 10,105, 32, 61, 32,105, 32, 43, 32, 49,
  10,114,101,116,117,114,110, 32, 97,114,114, 97,121, 91,105,
  93, 10,101,110,100, 10,114,101,116,117,114,110, 32,105,116,
 101,114, 97,116,111,114, 10,101,110,100, 10,108,111, 99, 97,
 108, 32,102,117,110, 99,116,105,111,110, 32,115, 97,102,101,
  95,105,116,101,114, 97,116,101, 95,108,105,115,116, 40,108,
 105,110,107, 41, 10,108,111, 99, 97,108, 32,111, 98,106,115,
  32, 61, 32,123,125, 10,119,104,105,108,101, 32,108,105,110,
 107, 32,100,111, 10,111, 98,106,115, 91, 35,111, 98,106,115,
  32, 43, 32, 49, 93, 32, 61, 32,108,105,110,107, 58,100, 97,
 116, 97, 40, 41, 10,108,105,110,107, 32, 61, 32,108,105,110,
 107, 58,110,101,120,116, 40, 41, 10,101,110,100, 10,114,101,
 116,117,114,110, 32,118, 97,108,117,101, 95,105,116,101,114,
  97,116,111,114, 40,111, 98,106,115, 41, 10,101,110,100, 10,
 102,117,110, 99,116,105,111,110, 32, 80,108, 97,121,101,114,
  58,117,110,105,116,115, 95,105,116,101,114, 97,116,101, 40,
  41, 10,114,101,116,117,114,110, 32,115, 97,102,101, 95,105,
 116,101,114, 97,116,101, 95,108,105,115,116, 40,112,114,105,
 118, 97,116,101, 46, 80,108, 97,121,101,114, 46,117,110,105,
 116, 95,108,105,115,116, 95,104,101, 97,100, 40,115,101,108,
 102, 41, 41, 10,101,110,100, 10,102,117,110, 99,116,105,111,
 110, 32, 80,108, 97,121,101,114, 58, 99,105,116,105,101,115,
  95,105,116,101,114, 97,116,101, 40, 41, 10,114,101,116,117,
 114,110, 32,115, 97,102,101, 95,105,116,101,114, 97,116,101,
  95,108,105,115,116, 40,112,114,105,118, 97,116,101, 46, 80,
 108, 97,121,101,114, 46, 99,105,116,121, 95,108,105,115,116,
  95,104,101, 97,100, 40,115,101,108,102, 41, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32, 84,105,108,101,
  58,117,110,105,116,115, 95,105,116,101,114, 97,116,101, 40,
  41, 10,114,101,116,117,114,110, 32,115, 97,102,101, 95,105,
 116,101,114, 97,116,101, 95,108,105,115,116, 40,112,114,105,
 118, 97,116,101, 46, 84,105,108,101, 46,117,110,105,116, 95,
 108,105,115,116, 95,104,101, 97,100, 40,115,101,108,102, 41,
  41, 10,101,110,100, 10,101,110,100, 10,100,111, 10,108,111,
  99, 97,108, 32,110,101,120,116, 95,111,117,116,119, 97,114,
 100, 95,105,110,100,101,120, 32, 61, 32,109,101,116,104,111,
 100,115, 95,112,114,105,118, 97,116,101, 46, 84,105,108,101,
  46,110,101,120,116, 95,111,117,116,119, 97,114,100, 95,105,
 110,100,101,120, 10,108,111, 99, 97,108, 32,116,105,108,101,
  95,102,111,114, 95,111,117,116,119, 97,114,100, 95,105,110,
 100,101,120, 32, 61, 32,109,101,116,104,111,100,115, 95,112,
 114,105,118, 97,116,101, 46, 84,105,108,101, 46,116,105,108,
 101, 95,102,111,114, 95,111,117,116,119, 97,114,100, 95,105,
 110,100,101,120, 10,102,117,110, 99,116,105,111,110, 32, 84,
 105,108,101, 58,115,113,117, 97,114,101, 95,105,116,101,114,
  97,116,101, 40,114, 97,100,105,117,115, 41, 10,108,111, 99,
  97,108, 32,105,110,100,101,120, 32, 61, 32, 45, 49, 10,108,
 111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,105,
 116,101,114, 97,116,111,114, 40, 41, 10,105,110,100,101,120,
  32, 61, 32,110,101,120,116, 95,111,117,116,119, 97,114,100,
  95,105,110,100,101,120, 40,115,101,108,102, 44, 32,105,110,
 100,101,120, 44, 32,114, 97,100,105,117,115, 41, 10,105,102,
  32,105,110,100,101,120, 32, 60, 32, 48, 32,116,104,101,110,
  10,114,101,116,117,114,110, 32,110,105,108, 10,101,108,115,
 101, 10,114,101,116,117,114,110, 32,116,105,108,101, 95,102,
 111,114, 95,111,117,116,119, 97,114,100, 95,105,110,100,101,
 120, 40,115,101,108,102, 44, 32,105,110,100,101,120, 41, 10,
 101,110,100, 10,101,110,100, 10,114,101,116,117,114,110, 32,
 105,116,101,114, 97,116,111,114, 10,101,110,100, 10,102,117,
 110, 99,116,105,111,110, 32, 84,105,108,101, 58, 99,105,114,
  99,108,101, 95,105,116,101,114, 97,116,101, 40,115,113, 95,
 114, 97,100,105,117,115, 41, 10,108,111, 99, 97,108, 32, 99,
 114, 95,114, 97,100,105,117,115, 32, 61, 32,109, 97,116,104,
  46,102,108,111,111,114, 40,109, 97,116,104, 46,115,113,114,
 116, 40,115,113, 95,114, 97,100,105,117,115, 41, 41, 10,108,
 111, 99, 97,108, 32,115,113, 95,105,116,101,114, 32, 61, 32,
 115,101,108,102, 58,115,113,117, 97,114,101, 95,105,116,101,
 114, 97,116,101, 40, 99,114, 95,114, 97,100,105,117,115, 41,
  10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,110,
  32,105,116,101,114, 97,116,111,114, 40, 41, 10,108,111, 99,
  97,108, 32,116,105,108,101, 32, 61, 32,110,105,108, 10,114,
 101,112,101, 97,116, 10,116,105,108,101, 32, 61, 32,115,113,
  95,105,116,101,114, 40, 41, 10,117,110,116,105,108, 32,110,
 111,116, 32,116,105,108,101, 32,111,114, 32,115,101,108,102,
  58,115,113, 95,100,105,115,116, 97,110, 99,101, 40,116,105,
 108,101, 41, 32, 60, 61, 32,115,113, 95,114, 97,100,105,117,
 115, 10,114,101,116,117,114,110, 32,116,105,108,101, 10,101,
 110,100, 10,114,101,116,117,114,110, 32,105,116,101,114, 97,
 116,111,114, 10,101,110,100, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */


 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,100,111, 10,108,111, 99, 97,108, 32,102,117,110, 99,116,
 105,111,110, 32,105,110,100,101,120, 95,105,116,101,114, 97,
 116,101, 40,108,111,111,107,117,112, 41, 10,108,111, 99, 97,
 108, 32,105,110,100,101,120, 32, 61, 32, 45, 49, 10,108,111,
  99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,105,116,
 101,114, 97,116,111,114, 40, 41, 10,105,110,100,101,120, 32,
  61, 32,105,110,100,101,120, 32, 43, 32, 49, 10,114,101,116,
 117,114,110, 32,108,111,111,107,117,112, 40,105,110,100,101,
 120, 41, 10,101,110,100, 10,114,101,116,117,114,110, 32,105,
 116,101,114, 97,116,111,114, 10,101,110,100, 10,102,117,110,
  99,116,105,111,110, 32,112,108, 97,121,101,114,115, 95,105,
 116,101,114, 97,116,101, 40, 41, 10,114,101,116,117,114,110,
  32,105,110,100,101,120, 95,105,116,101,114, 97,116,101, 40,
 102,105,110,100, 46,112,108, 97,121,101,114, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32,119,104,111,108,
 101, 95,109, 97,112, 95,105,116,101,114, 97,116,101, 40, 41,
  10,114,101,116,117,114,110, 32,105,110,100,101,120, 95,105,
 116,101,114, 97,116,101, 40,102,105,110,100, 46,116,105,108,
 101, 41, 10,101,110,100, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_game_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_game);
 lua_pushstring(tolua_S, "game");
 lua_call(tolua_S, 1, 0);
 return 1;
}
