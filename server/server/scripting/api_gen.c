/*
** Lua binding: api
** Generated automatically by tolua 5.1.3 on Sat Nov 19 20:25:10 2011.
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
TOLUA_API int tolua_api_open (lua_State* tolua_S);
LUALIB_API int luaopen_api (lua_State* tolua_S);

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "api_types.h"
#include "api_actions.h"
#include "api_effects.h"
#include "api_find.h"
#include "api_intl.h"
#include "api_methods.h"
#include "api_notify.h"
#include "api_utilities.h"
#include "script.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Building_Type");
 tolua_usertype(tolua_S,"Tile");
 tolua_usertype(tolua_S,"Terrain");
 tolua_usertype(tolua_S,"Nonexistent");
 tolua_usertype(tolua_S,"Tech_Type");
 tolua_usertype(tolua_S,"Government");
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"Unit_List_Link");
 tolua_usertype(tolua_S,"Unit_Type");
 tolua_usertype(tolua_S,"Unit");
 tolua_usertype(tolua_S,"City_List_Link");
 tolua_usertype(tolua_S,"City");
 tolua_usertype(tolua_S,"Nation_Type");
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

/* function: api_methods_player_number */
static int tolua_api_Player_properties_id00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_player_number(self);
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
static int tolua_api_Player_num_cities00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_player_num_cities(self);
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
static int tolua_api_Player_num_units00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_player_num_units(self);
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
static int tolua_api_Player_has_wonder00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Building_Type* building = ((Building_Type*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_player_has_wonder(self,building);
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

/* function: api_methods_player_victory */
static int tolua_api_Player_victory00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  api_methods_player_victory(self);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'victory'.",&tolua_err);
 return 0;
#endif
}

/* function: api_methods_player_civilization_score */
static int tolua_api_Player_civilization_score00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_player_civilization_score(self);
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

/* function: api_methods_player_gold */
static int tolua_api_Player_gold00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_player_gold(self);
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
static int tolua_api_Player_knows_tech00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tech_Type* ptech = ((Tech_Type*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_player_knows_tech(self,ptech);
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

/* function: api_methods_private_player_unit_list_head */
static int tolua_api_methods_private_Player_unit_list_head00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  Unit_List_Link* tolua_ret = (Unit_List_Link*)  api_methods_private_player_unit_list_head(self);
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
static int tolua_api_methods_private_Player_city_list_head00(lua_State* tolua_S)
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
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  City_List_Link* tolua_ret = (City_List_Link*)  api_methods_private_player_city_list_head(self);
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

/* get function: tile of class  City */
static int tolua_get_City_City_tile_ptr(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tile'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->tile,"Tile");
 return 1;
}

/* set function: tile of class  City */
static int tolua_set_City_City_tile_ptr(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tile'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: size of class  City */
static int tolua_get_City_City_size(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->size);
 return 1;
}

/* set function: size of class  City */
static int tolua_set_City_City_size(lua_State* tolua_S)
{
  City* self = (City*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->size = ((int)  tolua_tonumber(tolua_S,2,0));
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

/* function: api_methods_city_has_building */
static int tolua_api_City_has_building00(lua_State* tolua_S)
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
  City* self = ((City*)  tolua_tousertype(tolua_S,1,0));
  Building_Type* building = ((Building_Type*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_city_has_building(self,building);
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
static int tolua_api_City_map_sq_radius00(lua_State* tolua_S)
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
  City* self = ((City*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_city_map_sq_radius(self);
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

/* get function: tile of class  Unit */
static int tolua_get_Unit_Unit_tile_ptr(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tile'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->tile,"Tile");
 return 1;
}

/* set function: tile of class  Unit */
static int tolua_set_Unit_Unit_tile_ptr(lua_State* tolua_S)
{
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tile'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
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

/* function: api_methods_unit_city_can_be_built_here */
static int tolua_api_Unit_is_on_possible_city_tile00(lua_State* tolua_S)
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
  Unit* self = ((Unit*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_city_can_be_built_here(self);
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

/* get function: nat_x of class  Tile */
static int tolua_get_Tile_Tile_nat_x(lua_State* tolua_S)
{
  Tile* self = (Tile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nat_x'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nat_x);
 return 1;
}

/* get function: nat_y of class  Tile */
static int tolua_get_Tile_Tile_nat_y(lua_State* tolua_S)
{
  Tile* self = (Tile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nat_y'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nat_y);
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

/* function: api_methods_tile_city */
static int tolua_api_Tile_city00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  City* tolua_ret = (City*)  api_methods_tile_city(self);
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
static int tolua_api_Tile_city_exists_within_max_city_map00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  bool center = ((bool)  tolua_toboolean(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_tile_city_exists_within_max_city_map(self,center);
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

/* function: api_methods_tile_num_units */
static int tolua_api_Tile_num_units00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_methods_tile_num_units(self);
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
static int tolua_api_Tile_sq_distance00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  Tile* other = ((Tile*)  tolua_tousertype(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_methods_tile_sq_distance(self,other);
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
static int tolua_api_methods_private_Tile_next_outward_index00(lua_State* tolua_S)
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
  Tile* pcenter = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int max_dist = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  int tolua_ret = (int)  api_methods_private_tile_next_outward_index(pcenter,index,max_dist);
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
static int tolua_api_methods_private_Tile_tile_for_outward_index00(lua_State* tolua_S)
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
  Tile* pcenter = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Tile* tolua_ret = (Tile*)  api_methods_private_tile_for_outward_index(pcenter,index);
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
static int tolua_api_methods_private_Tile_unit_list_head00(lua_State* tolua_S)
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
  Tile* self = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  Unit_List_Link* tolua_ret = (Unit_List_Link*)  api_methods_private_tile_unit_list_head(self);
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

/* function: api_methods_government_rule_name */
static int tolua_api_Government_rule_name00(lua_State* tolua_S)
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
  Government* self = ((Government*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_government_rule_name(self);
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
static int tolua_api_Government_name_translation00(lua_State* tolua_S)
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
  Government* self = ((Government*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_government_name_translation(self);
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

/* function: api_methods_nation_type_rule_name */
static int tolua_api_Nation_Type_rule_name00(lua_State* tolua_S)
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
  Nation_Type* self = ((Nation_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_nation_type_rule_name(self);
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
static int tolua_api_Nation_Type_name_translation00(lua_State* tolua_S)
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
  Nation_Type* self = ((Nation_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_nation_type_name_translation(self);
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
static int tolua_api_Nation_Type_plural_translation00(lua_State* tolua_S)
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
  Nation_Type* self = ((Nation_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_nation_type_plural_translation(self);
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

/* function: api_methods_building_type_is_wonder */
static int tolua_api_Building_Type_is_wonder00(lua_State* tolua_S)
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
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_wonder(self);
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
static int tolua_api_Building_Type_is_great_wonder00(lua_State* tolua_S)
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
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_great_wonder(self);
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
static int tolua_api_Building_Type_is_small_wonder00(lua_State* tolua_S)
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
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_small_wonder(self);
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
static int tolua_api_Building_Type_is_improvement00(lua_State* tolua_S)
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
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_methods_building_type_is_improvement(self);
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
static int tolua_api_Building_Type_rule_name00(lua_State* tolua_S)
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
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_building_type_rule_name(self);
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
static int tolua_api_Building_Type_name_translation00(lua_State* tolua_S)
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
  Building_Type* self = ((Building_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_building_type_name_translation(self);
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

/* function: api_methods_unit_type_has_flag */
static int tolua_api_Unit_Type_has_flag00(lua_State* tolua_S)
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
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
  const char* flag = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_type_has_flag(self,flag);
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
static int tolua_api_Unit_Type_has_role00(lua_State* tolua_S)
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
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
  const char* role = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_type_has_role(self,role);
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
static int tolua_api_Unit_Type_rule_name00(lua_State* tolua_S)
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
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_unit_type_rule_name(self);
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
static int tolua_api_Unit_Type_name_translation00(lua_State* tolua_S)
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
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_unit_type_name_translation(self);
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
static int tolua_api_Unit_Type_can_exist_at_tile00(lua_State* tolua_S)
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
  Unit_Type* self = ((Unit_Type*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_methods_unit_type_can_exist_at_tile(self,ptile);
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

/* function: api_methods_tech_type_rule_name */
static int tolua_api_Tech_Type_rule_name00(lua_State* tolua_S)
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
  Tech_Type* self = ((Tech_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_tech_type_rule_name(self);
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
static int tolua_api_Tech_Type_name_translation00(lua_State* tolua_S)
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
  Tech_Type* self = ((Tech_Type*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_tech_type_name_translation(self);
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

/* function: api_methods_terrain_rule_name */
static int tolua_api_Terrain_rule_name00(lua_State* tolua_S)
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
  Terrain* self = ((Terrain*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_terrain_rule_name(self);
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
static int tolua_api_Terrain_name_translation00(lua_State* tolua_S)
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
  Terrain* self = ((Terrain*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_methods_terrain_name_translation(self);
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
static int tolua_api_Unit_List_Link_data00(lua_State* tolua_S)
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
  Unit_List_Link* self = ((Unit_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  Unit* tolua_ret = (Unit*)  api_methods_unit_list_link_data(self);
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
static int tolua_api_Unit_List_Link_next00(lua_State* tolua_S)
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
  Unit_List_Link* self = ((Unit_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  Unit_List_Link* tolua_ret = (Unit_List_Link*)  api_methods_unit_list_next_link(self);
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
static int tolua_api_City_List_Link_data00(lua_State* tolua_S)
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
  City_List_Link* self = ((City_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  City* tolua_ret = (City*)  api_methods_city_list_link_data(self);
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
static int tolua_api_City_List_Link_next00(lua_State* tolua_S)
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
  City_List_Link* self = ((City_List_Link*)  tolua_tousertype(tolua_S,1,0));
 {
  City_List_Link* tolua_ret = (City_List_Link*)  api_methods_city_list_next_link(self);
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
static int tolua_api_find_player00(lua_State* tolua_S)
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
  int player_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Player* tolua_ret = (Player*)  api_find_player(player_id);
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
static int tolua_api_find_city00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  int city_id = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  City* tolua_ret = (City*)  api_find_city(pplayer,city_id);
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
static int tolua_api_find_unit00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  int unit_id = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Unit* tolua_ret = (Unit*)  api_find_unit(pplayer,unit_id);
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
static int tolua_api_find_transport_unit00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Unit_Type* ptype = ((Unit_Type*)  tolua_tousertype(tolua_S,2,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,3,0));
 {
  Unit* tolua_ret = (Unit*)  api_find_transport_unit(pplayer,ptype,ptile);
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
static int tolua_api_find_tile00(lua_State* tolua_S)
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
  int nat_x = ((int)  tolua_tonumber(tolua_S,1,0));
  int nat_y = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Tile* tolua_ret = (Tile*)  api_find_tile(nat_x,nat_y);
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
static int tolua_api_find_tile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  int index = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Tile* tolua_ret = (Tile*)  api_find_tile_by_index(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
 }
 }
 return 1;
tolua_lerror:
 return tolua_api_find_tile00(tolua_S);
}

/* function: api_find_government_by_name */
static int tolua_api_find_government00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Government* tolua_ret = (Government*)  api_find_government_by_name(name_orig);
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
static int tolua_api_find_government01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  int government_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Government* tolua_ret = (Government*)  api_find_government(government_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Government");
 }
 }
 return 1;
tolua_lerror:
 return tolua_api_find_government00(tolua_S);
}

/* function: api_find_nation_type_by_name */
static int tolua_api_find_nation_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Nation_Type* tolua_ret = (Nation_Type*)  api_find_nation_type_by_name(name_orig);
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
static int tolua_api_find_nation_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  int nation_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Nation_Type* tolua_ret = (Nation_Type*)  api_find_nation_type(nation_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Nation_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_api_find_nation_type00(tolua_S);
}

/* function: api_find_building_type_by_name */
static int tolua_api_find_building_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Building_Type* tolua_ret = (Building_Type*)  api_find_building_type_by_name(name_orig);
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
static int tolua_api_find_building_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  int building_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Building_Type* tolua_ret = (Building_Type*)  api_find_building_type(building_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Building_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_api_find_building_type00(tolua_S);
}

/* function: api_find_unit_type_by_name */
static int tolua_api_find_unit_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Unit_Type* tolua_ret = (Unit_Type*)  api_find_unit_type_by_name(name_orig);
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
static int tolua_api_find_unit_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  int unit_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Unit_Type* tolua_ret = (Unit_Type*)  api_find_unit_type(unit_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Unit_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_api_find_unit_type00(tolua_S);
}

/* function: api_find_role_unit_type */
static int tolua_api_find_role_unit_type00(lua_State* tolua_S)
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
  const char* role_name = ((const char*)  tolua_tostring(tolua_S,1,0));
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
 {
  Unit_Type* tolua_ret = (Unit_Type*)  api_find_role_unit_type(role_name,pplayer);
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
static int tolua_api_find_tech_type00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Tech_Type* tolua_ret = (Tech_Type*)  api_find_tech_type_by_name(name_orig);
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
static int tolua_api_find_tech_type01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  int tech_type_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Tech_Type* tolua_ret = (Tech_Type*)  api_find_tech_type(tech_type_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tech_Type");
 }
 }
 return 1;
tolua_lerror:
 return tolua_api_find_tech_type00(tolua_S);
}

/* function: api_find_terrain_by_name */
static int tolua_api_find_terrain00(lua_State* tolua_S)
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
  const char* name_orig = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  Terrain* tolua_ret = (Terrain*)  api_find_terrain_by_name(name_orig);
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
static int tolua_api_find_terrain01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  int terrain_id = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  Terrain* tolua_ret = (Terrain*)  api_find_terrain(terrain_id);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Terrain");
 }
 }
 return 1;
tolua_lerror:
 return tolua_api_find_terrain00(tolua_S);
}

/* function: api_find_nonexistent */
static int tolua_api_find_nonexistent00(lua_State* tolua_S)
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
 {
  Nonexistent* tolua_ret = (Nonexistent*)  api_find_nonexistent();
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

/* function: script_signal_connect */
static int tolua_api_signal_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const char* signal_name = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* callback_name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  script_signal_connect(signal_name,callback_name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}

/* function: api_intl__ */
static int tolua_api__00(lua_State* tolua_S)
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
  const char* untranslated = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_intl__(untranslated);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '_'.",&tolua_err);
 return 0;
#endif
}

/* function: api_intl_N_ */
static int tolua_api_N_00(lua_State* tolua_S)
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
  const char* untranslated = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_intl_N_(untranslated);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'N_'.",&tolua_err);
 return 0;
#endif
}

/* function: api_intl_Q_ */
static int tolua_api_Q_00(lua_State* tolua_S)
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
  const char* untranslated = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_intl_Q_(untranslated);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Q_'.",&tolua_err);
 return 0;
#endif
}

/* function: api_intl_PL_ */
static int tolua_api_PL_00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const char* singular = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* plural = ((const char*)  tolua_tostring(tolua_S,2,0));
  int n = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  const char* tolua_ret = (const char*)  api_intl_PL_(singular,plural,n);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PL_'.",&tolua_err);
 return 0;
#endif
}

/* function: api_notify_embassies_msg */
static int tolua_api_notify_embassies_msg00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  int event = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,4,0));
 {
  api_notify_embassies_msg(pplayer,ptile,event,message);
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
static int tolua_api_notify_event_msg00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  int event = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,4,0));
 {
  api_notify_event_msg(pplayer,ptile,event,message);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'event_msg'.",&tolua_err);
 return 0;
#endif
}

/* function: api_effects_world_bonus */
static int tolua_api_effects_world_bonus00(lua_State* tolua_S)
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
  const char* effect_type = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  int tolua_ret = (int)  api_effects_world_bonus(effect_type);
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
static int tolua_api_effects_player_bonus00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  const char* effect_type = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_effects_player_bonus(pplayer,effect_type);
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
static int tolua_api_effects_city_bonus00(lua_State* tolua_S)
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
  City* pcity = ((City*)  tolua_tousertype(tolua_S,1,0));
  const char* effect_type = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_effects_city_bonus(pcity,effect_type);
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

/* function: api_utilities_random */
static int tolua_api_random00(lua_State* tolua_S)
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
  int min = ((int)  tolua_tonumber(tolua_S,1,0));
  int max = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_utilities_random(min,max);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'random'.",&tolua_err);
 return 0;
#endif
}

/* function: api_utilities_error_log */
static int tolua_api_error_log00(lua_State* tolua_S)
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
  const char* msg = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  api_utilities_error_log(msg);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'error_log'.",&tolua_err);
 return 0;
#endif
}

/* function: api_utilities_debug_log */
static int tolua_api_debug_log00(lua_State* tolua_S)
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
  const char* msg = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  api_utilities_debug_log(msg);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'debug_log'.",&tolua_err);
 return 0;
#endif
}

/* function: api_actions_create_unit */
static int tolua_api_create_unit00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  Unit_Type* ptype = ((Unit_Type*)  tolua_tousertype(tolua_S,3,0));
  int veteran_level = ((int)  tolua_tonumber(tolua_S,4,0));
  City* homecity = ((City*)  tolua_tousertype(tolua_S,5,0));
  int moves_left = ((int)  tolua_tonumber(tolua_S,6,0));
 {
  Unit* tolua_ret = (Unit*)  api_actions_create_unit(pplayer,ptile,ptype,veteran_level,homecity,moves_left);
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

/* function: api_actions_create_unit_full */
static int tolua_api_create_unit_full00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  Unit_Type* ptype = ((Unit_Type*)  tolua_tousertype(tolua_S,3,0));
  int veteran_level = ((int)  tolua_tonumber(tolua_S,4,0));
  City* homecity = ((City*)  tolua_tousertype(tolua_S,5,0));
  int moves_left = ((int)  tolua_tonumber(tolua_S,6,0));
  int hp_left = ((int)  tolua_tonumber(tolua_S,7,0));
  Unit* ptransport = ((Unit*)  tolua_tousertype(tolua_S,8,0));
 {
  Unit* tolua_ret = (Unit*)  api_actions_create_unit_full(pplayer,ptile,ptype,veteran_level,homecity,moves_left,hp_left,ptransport);
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

/* function: api_actions_create_city */
static int tolua_api_create_city00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
 {
  api_actions_create_city(pplayer,ptile,name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_city'.",&tolua_err);
 return 0;
#endif
}

/* function: api_actions_create_base */
static int tolua_api_create_base00(lua_State* tolua_S)
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
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,3,0));
 {
  api_actions_create_base(ptile,name,pplayer);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create_base'.",&tolua_err);
 return 0;
#endif
}

/* function: api_actions_create_player */
static int tolua_api_create_player00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"Nation_Type",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const char* username = ((const char*)  tolua_tostring(tolua_S,1,0));
  Nation_Type* nation = ((Nation_Type*)  tolua_tousertype(tolua_S,2,0));
 {
  Player* tolua_ret = (Player*)  api_actions_create_player(username,nation);
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

/* function: api_actions_change_gold */
static int tolua_api_change_gold00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  int amount = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  api_actions_change_gold(pplayer,amount);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'change_gold'.",&tolua_err);
 return 0;
#endif
}

/* function: api_actions_give_technology */
static int tolua_api_give_technology00(lua_State* tolua_S)
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
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,1,0));
  Tech_Type* ptech = ((Tech_Type*)  tolua_tousertype(tolua_S,2,0));
  const char* reason = ((const char*)  tolua_tostring(tolua_S,3,0));
 {
  Tech_Type* tolua_ret = (Tech_Type*)  api_actions_give_technology(pplayer,ptech,reason);
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

/* function: api_actions_unleash_barbarians */
static int tolua_api_unleash_barbarians00(lua_State* tolua_S)
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
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
 {
  bool tolua_ret = (bool)  api_actions_unleash_barbarians(ptile);
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

/* function: api_actions_place_partisans */
static int tolua_api_place_partisans00(lua_State* tolua_S)
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
  Tile* ptile = ((Tile*)  tolua_tousertype(tolua_S,1,0));
  Player* pplayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  int sq_radius = ((int)  tolua_tonumber(tolua_S,4,0));
 {
  api_actions_place_partisans(ptile,pplayer,count,sq_radius);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'place_partisans'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_api (lua_State* tolua_S)
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Player",0);
 tolua_beginmodule(tolua_S,"Player");
 tolua_module(tolua_S,"properties",0);
 tolua_beginmodule(tolua_S,"properties");
 tolua_function(tolua_S,"id",tolua_api_Player_properties_id00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"num_cities",tolua_api_Player_num_cities00);
 tolua_function(tolua_S,"num_units",tolua_api_Player_num_units00);
 tolua_function(tolua_S,"has_wonder",tolua_api_Player_has_wonder00);
 tolua_function(tolua_S,"victory",tolua_api_Player_victory00);
 tolua_function(tolua_S,"civilization_score",tolua_api_Player_civilization_score00);
 tolua_function(tolua_S,"gold",tolua_api_Player_gold00);
 tolua_function(tolua_S,"knows_tech",tolua_api_Player_knows_tech00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"methods_private",0);
 tolua_beginmodule(tolua_S,"methods_private");
 tolua_module(tolua_S,"Player",0);
 tolua_beginmodule(tolua_S,"Player");
 tolua_function(tolua_S,"unit_list_head",tolua_api_methods_private_Player_unit_list_head00);
 tolua_function(tolua_S,"city_list_head",tolua_api_methods_private_Player_city_list_head00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"City","City","",NULL);
 tolua_beginmodule(tolua_S,"City");
 tolua_variable(tolua_S,"name",tolua_get_City_City_name,NULL);
 tolua_variable(tolua_S,"owner",tolua_get_City_City_owner_ptr,tolua_set_City_City_owner_ptr);
 tolua_variable(tolua_S,"original",tolua_get_City_City_original_ptr,tolua_set_City_City_original_ptr);
 tolua_variable(tolua_S,"tile",tolua_get_City_City_tile_ptr,tolua_set_City_City_tile_ptr);
 tolua_variable(tolua_S,"size",tolua_get_City_City_size,tolua_set_City_City_size);
 tolua_variable(tolua_S,"id",tolua_get_City_City_id,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"City",0);
 tolua_beginmodule(tolua_S,"City");
 tolua_function(tolua_S,"has_building",tolua_api_City_has_building00);
 tolua_function(tolua_S,"map_sq_radius",tolua_api_City_map_sq_radius00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Unit","Unit","",NULL);
 tolua_beginmodule(tolua_S,"Unit");
 tolua_variable(tolua_S,"utype",tolua_get_Unit_Unit_utype_ptr,tolua_set_Unit_Unit_utype_ptr);
 tolua_variable(tolua_S,"owner",tolua_get_Unit_Unit_owner_ptr,tolua_set_Unit_Unit_owner_ptr);
 tolua_variable(tolua_S,"homecity",tolua_get_Unit_Unit_homecity,tolua_set_Unit_Unit_homecity);
 tolua_variable(tolua_S,"tile",tolua_get_Unit_Unit_tile_ptr,tolua_set_Unit_Unit_tile_ptr);
 tolua_variable(tolua_S,"id",tolua_get_Unit_Unit_id,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Unit",0);
 tolua_beginmodule(tolua_S,"Unit");
 tolua_function(tolua_S,"is_on_possible_city_tile",tolua_api_Unit_is_on_possible_city_tile00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Tile","Tile","",NULL);
 tolua_beginmodule(tolua_S,"Tile");
 tolua_variable(tolua_S,"nat_x",tolua_get_Tile_Tile_nat_x,NULL);
 tolua_variable(tolua_S,"nat_y",tolua_get_Tile_Tile_nat_y,NULL);
 tolua_variable(tolua_S,"terrain",tolua_get_Tile_Tile_terrain_ptr,tolua_set_Tile_Tile_terrain_ptr);
 tolua_variable(tolua_S,"id",tolua_get_Tile_Tile_index,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Tile",0);
 tolua_beginmodule(tolua_S,"Tile");
 tolua_function(tolua_S,"city",tolua_api_Tile_city00);
 tolua_function(tolua_S,"city_exists_within_max_city_map",tolua_api_Tile_city_exists_within_max_city_map00);
 tolua_function(tolua_S,"num_units",tolua_api_Tile_num_units00);
 tolua_function(tolua_S,"sq_distance",tolua_api_Tile_sq_distance00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"methods_private",0);
 tolua_beginmodule(tolua_S,"methods_private");
 tolua_module(tolua_S,"Tile",0);
 tolua_beginmodule(tolua_S,"Tile");
 tolua_function(tolua_S,"next_outward_index",tolua_api_methods_private_Tile_next_outward_index00);
 tolua_function(tolua_S,"tile_for_outward_index",tolua_api_methods_private_Tile_tile_for_outward_index00);
 tolua_function(tolua_S,"unit_list_head",tolua_api_methods_private_Tile_unit_list_head00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Government","Government","",NULL);
 tolua_beginmodule(tolua_S,"Government");
 tolua_variable(tolua_S,"id",tolua_get_Government_Government_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Government",0);
 tolua_beginmodule(tolua_S,"Government");
 tolua_function(tolua_S,"rule_name",tolua_api_Government_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_api_Government_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Nation_Type","Nation_Type","",NULL);
 tolua_beginmodule(tolua_S,"Nation_Type");
 tolua_variable(tolua_S,"id",tolua_get_Nation_Type_Nation_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Nation_Type",0);
 tolua_beginmodule(tolua_S,"Nation_Type");
 tolua_function(tolua_S,"rule_name",tolua_api_Nation_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_api_Nation_Type_name_translation00);
 tolua_function(tolua_S,"plural_translation",tolua_api_Nation_Type_plural_translation00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Building_Type","Building_Type","",NULL);
 tolua_beginmodule(tolua_S,"Building_Type");
 tolua_variable(tolua_S,"build_cost",tolua_get_Building_Type_Building_Type_build_cost,tolua_set_Building_Type_Building_Type_build_cost);
 tolua_variable(tolua_S,"id",tolua_get_Building_Type_Building_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Building_Type",0);
 tolua_beginmodule(tolua_S,"Building_Type");
 tolua_function(tolua_S,"is_wonder",tolua_api_Building_Type_is_wonder00);
 tolua_function(tolua_S,"is_great_wonder",tolua_api_Building_Type_is_great_wonder00);
 tolua_function(tolua_S,"is_small_wonder",tolua_api_Building_Type_is_small_wonder00);
 tolua_function(tolua_S,"is_improvement",tolua_api_Building_Type_is_improvement00);
 tolua_function(tolua_S,"rule_name",tolua_api_Building_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_api_Building_Type_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Unit_Type","Unit_Type","",NULL);
 tolua_beginmodule(tolua_S,"Unit_Type");
 tolua_variable(tolua_S,"build_cost",tolua_get_Unit_Type_Unit_Type_build_cost,tolua_set_Unit_Type_Unit_Type_build_cost);
 tolua_variable(tolua_S,"id",tolua_get_Unit_Type_Unit_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Unit_Type",0);
 tolua_beginmodule(tolua_S,"Unit_Type");
 tolua_function(tolua_S,"has_flag",tolua_api_Unit_Type_has_flag00);
 tolua_function(tolua_S,"has_role",tolua_api_Unit_Type_has_role00);
 tolua_function(tolua_S,"rule_name",tolua_api_Unit_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_api_Unit_Type_name_translation00);
 tolua_function(tolua_S,"can_exist_at_tile",tolua_api_Unit_Type_can_exist_at_tile00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Tech_Type","Tech_Type","",NULL);
 tolua_beginmodule(tolua_S,"Tech_Type");
 tolua_variable(tolua_S,"id",tolua_get_Tech_Type_Tech_Type_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Tech_Type",0);
 tolua_beginmodule(tolua_S,"Tech_Type");
 tolua_function(tolua_S,"rule_name",tolua_api_Tech_Type_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_api_Tech_Type_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Terrain","Terrain","",NULL);
 tolua_beginmodule(tolua_S,"Terrain");
 tolua_variable(tolua_S,"id",tolua_get_Terrain_Terrain_item_number,NULL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Terrain",0);
 tolua_beginmodule(tolua_S,"Terrain");
 tolua_function(tolua_S,"rule_name",tolua_api_Terrain_rule_name00);
 tolua_function(tolua_S,"name_translation",tolua_api_Terrain_name_translation00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Unit_List_Link","Unit_List_Link","",NULL);
 tolua_beginmodule(tolua_S,"Unit_List_Link");
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"Unit_List_Link",0);
 tolua_beginmodule(tolua_S,"Unit_List_Link");
 tolua_function(tolua_S,"data",tolua_api_Unit_List_Link_data00);
 tolua_function(tolua_S,"next",tolua_api_Unit_List_Link_next00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"City_List_Link","City_List_Link","",NULL);
 tolua_beginmodule(tolua_S,"City_List_Link");
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"City_List_Link",0);
 tolua_beginmodule(tolua_S,"City_List_Link");
 tolua_function(tolua_S,"data",tolua_api_City_List_Link_data00);
 tolua_function(tolua_S,"next",tolua_api_City_List_Link_next00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Nonexistent","Nonexistent","",NULL);
 tolua_beginmodule(tolua_S,"Nonexistent");
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 66,117,105,108,100,
 105,110,103, 95, 84,121,112,101, 58, 98,117,105,108,100, 95,
 115,104,105,101,108,100, 95, 99,111,115,116, 40, 41, 10,114,
 101,116,117,114,110, 32,115,101,108,102, 46, 98,117,105,108,
 100, 95, 99,111,115,116, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32, 80,108, 97,121,101,114, 58,105,115, 95,
 104,117,109, 97,110, 40, 41, 10,114,101,116,117,114,110, 32,
 110,111,116, 32,115,101,108,102, 46, 97,105, 95, 99,111,110,
 116,114,111,108,108,101,100, 10,101,110,100, 10,100,111, 10,
 108,111, 99, 97,108, 32,112,114,105,118, 97,116,101, 32, 61,
  32,109,101,116,104,111,100,115, 95,112,114,105,118, 97,116,
 101, 10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,
 110, 32,118, 97,108,117,101, 95,105,116,101,114, 97,116,111,
 114, 40, 97,114,114, 97,121, 41, 10,108,111, 99, 97,108, 32,
 105, 32, 61, 32, 48, 10,108,111, 99, 97,108, 32,102,117,110,
  99,116,105,111,110, 32,105,116,101,114, 97,116,111,114, 40,
  41, 10,105, 32, 61, 32,105, 32, 43, 32, 49, 10,114,101,116,
 117,114,110, 32, 97,114,114, 97,121, 91,105, 93, 10,101,110,
 100, 10,114,101,116,117,114,110, 32,105,116,101,114, 97,116,
 111,114, 10,101,110,100, 10,108,111, 99, 97,108, 32,102,117,
 110, 99,116,105,111,110, 32,115, 97,102,101, 95,105,116,101,
 114, 97,116,101, 95,108,105,115,116, 40,108,105,110,107, 41,
  10,108,111, 99, 97,108, 32,111, 98,106,115, 32, 61, 32,123,
 125, 10,119,104,105,108,101, 32,108,105,110,107, 32,100,111,
  10,111, 98,106,115, 91, 35,111, 98,106,115, 32, 43, 32, 49,
  93, 32, 61, 32,108,105,110,107, 58,100, 97,116, 97, 40, 41,
  10,108,105,110,107, 32, 61, 32,108,105,110,107, 58,110,101,
 120,116, 40, 41, 10,101,110,100, 10,114,101,116,117,114,110,
  32,118, 97,108,117,101, 95,105,116,101,114, 97,116,111,114,
  40,111, 98,106,115, 41, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32, 80,108, 97,121,101,114, 58,117,110,105,
 116,115, 95,105,116,101,114, 97,116,101, 40, 41, 10,114,101,
 116,117,114,110, 32,115, 97,102,101, 95,105,116,101,114, 97,
 116,101, 95,108,105,115,116, 40,112,114,105,118, 97,116,101,
  46, 80,108, 97,121,101,114, 46,117,110,105,116, 95,108,105,
 115,116, 95,104,101, 97,100, 40,115,101,108,102, 41, 41, 10,
 101,110,100, 10,102,117,110, 99,116,105,111,110, 32, 80,108,
  97,121,101,114, 58, 99,105,116,105,101,115, 95,105,116,101,
 114, 97,116,101, 40, 41, 10,114,101,116,117,114,110, 32,115,
  97,102,101, 95,105,116,101,114, 97,116,101, 95,108,105,115,
 116, 40,112,114,105,118, 97,116,101, 46, 80,108, 97,121,101,
 114, 46, 99,105,116,121, 95,108,105,115,116, 95,104,101, 97,
 100, 40,115,101,108,102, 41, 41, 10,101,110,100, 10,102,117,
 110, 99,116,105,111,110, 32, 84,105,108,101, 58,117,110,105,
 116,115, 95,105,116,101,114, 97,116,101, 40, 41, 10,114,101,
 116,117,114,110, 32,115, 97,102,101, 95,105,116,101,114, 97,
 116,101, 95,108,105,115,116, 40,112,114,105,118, 97,116,101,
  46, 84,105,108,101, 46,117,110,105,116, 95,108,105,115,116,
  95,104,101, 97,100, 40,115,101,108,102, 41, 41, 10,101,110,
 100, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  84,105,108,101, 58, 99,105,116,121, 95,101,120,105,115,116,
 115, 95,119,105,116,104,105,110, 95, 99,105,116,121, 95,114,
  97,100,105,117,115, 40, 99,101,110,116,101,114, 41, 10,114,
 101,116,117,114,110, 32,115,101,108,102, 58, 99,105,116,121,
  95,101,120,105,115,116,115, 95,119,105,116,104,105,110, 95,
 109, 97,120, 95, 99,105,116,121, 95,109, 97,112, 40, 99,101,
 110,116,101,114, 41, 10,101,110,100, 10,100,111, 10,108,111,
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
 116,111,114, 10,101,110,100, 10,101,110,100, 10,102,117,110,
  99,116,105,111,110, 32, 67,105,116,121, 58,101,120,105,115,
 116,115, 40, 41, 10,114,101,116,117,114,110, 32,116,114,117,
 101, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  85,110,105,116, 58,101,120,105,115,116,115, 40, 41, 10,114,
 101,116,117,114,110, 32,116,114,117,101, 10,101,110,100, 10,
 102,117,110, 99,116,105,111,110, 32, 85,110,105,116, 58,103,
 101,116, 95,104,111,109,101, 99,105,116,121, 40, 41, 10,114,
 101,116,117,114,110, 32,102,105,110,100, 46, 99,105,116,121,
  40,115,101,108,102, 46,111,119,110,101,114, 44, 32,115,101,
 108,102, 46,104,111,109,101, 99,105,116,121, 41, 10,101,110,
 100, 10,102,117,110, 99,116,105,111,110, 32, 85,110,105,116,
  95, 84,121,112,101, 58, 98,117,105,108,100, 95,115,104,105,
 101,108,100, 95, 99,111,115,116, 40, 41, 10,114,101,116,117,
 114,110, 32,115,101,108,102, 46, 98,117,105,108,100, 95, 99,
 111,115,116, 10,101,110,100, 10,102,117,110, 99,116,105,111,
 110, 32, 78,111,110,101,120,105,115,116,101,110,116, 58,101,
 120,105,115,116,115, 40, 41, 10,114,101,116,117,114,110, 32,
 102, 97,108,115,101, 10,101,110,100, 10,109,101,116,104,111,
 100,115, 95,112,114,105,118, 97,116,101, 32, 61, 32,110,105,
 108,32
 };
 if (!luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code")) {
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 }
 } /* end of embedded lua code */


 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,100,111, 10,108,111, 99, 97,108, 32, 97,112,105, 95,116,
 121,112,101,115, 32, 61, 32,123, 10, 34, 80,108, 97,121,101,
 114, 34, 44, 10, 34, 85,110,105,116, 34, 44, 10, 34, 67,105,
 116,121, 34, 44, 10, 34, 84,105,108,101, 34, 44, 10, 34, 71,
 111,118,101,114,110,109,101,110,116, 34, 44, 10, 34, 78, 97,
 116,105,111,110, 95, 84,121,112,101, 34, 44, 10, 34, 66,117,
 105,108,100,105,110,103, 95, 84,121,112,101, 34, 44, 10, 34,
  85,110,105,116, 95, 84,121,112,101, 34, 44, 10, 34, 84,101,
  99,104, 95, 84,121,112,101, 34, 44, 10, 34, 84,101,114,114,
  97,105,110, 34, 44, 10, 34, 85,110,105,116, 95, 76,105,115,
 116, 95, 76,105,110,107, 34, 44, 10, 34, 67,105,116,121, 95,
  76,105,115,116, 95, 76,105,110,107, 34, 44, 10, 34, 78,111,
 110,101,120,105,115,116,101,110,116, 34, 44, 10,125, 10,108,
 111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,105,
 100, 95,101,113, 32, 40,111, 49, 44, 32,111, 50, 41, 10,114,
 101,116,117,114,110, 32,111, 49, 46,105,100, 32, 61, 61, 32,
 111, 50, 46,105,100, 32, 97,110,100, 32, 40,111, 49, 46,105,
 100, 32,126, 61, 32,110,105,108, 41, 10,101,110,100, 10,108,
 111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,115,
 116,114,105,110,103, 95,114,101,112, 40,115,101,108,102, 41,
  10,108,111, 99, 97,108, 32,105,100, 32, 61, 32,115,101,108,
 102, 46,105,100, 10,108,111, 99, 97,108, 32,110, 97,109,101,
  32, 61, 32,115,101,108,102, 46,114,117,108,101, 95,110, 97,
 109,101, 32, 97,110,100, 32,115,101,108,102, 58,114,117,108,
 101, 95,110, 97,109,101, 40, 41, 32,111,114, 32,115,101,108,
 102, 46,110, 97,109,101, 10,105,102, 32,110, 97,109,101, 32,
  97,110,100, 32,105,100, 32,116,104,101,110, 10,114,101,116,
 117,114,110, 32,115,116,114,105,110,103, 46,102,111,114,109,
  97,116, 40, 39, 60, 37,115, 32, 35, 37,100, 32, 37,115, 62,
  39, 44, 32,116,111,108,117, 97, 46,116,121,112,101, 40,115,
 101,108,102, 41, 44, 32,105,100, 44, 32,110, 97,109,101, 41,
  10,101,108,115,101,105,102, 32,105,100, 32,116,104,101,110,
  10,114,101,116,117,114,110, 32,115,116,114,105,110,103, 46,
 102,111,114,109, 97,116, 40, 39, 60, 37,115, 32, 35, 37,100,
  62, 39, 44, 32,116,111,108,117, 97, 46,116,121,112,101, 40,
 115,101,108,102, 41, 44, 32,105,100, 41, 10,101,108,115,101,
  10,114,101,116,117,114,110, 32,115,116,114,105,110,103, 46,
 102,111,114,109, 97,116, 40, 39, 60, 37,115, 62, 39, 44, 32,
 116,111,108,117, 97, 46,116,121,112,101, 40,115,101,108,102,
  41, 41, 10,101,110,100, 10,101,110,100, 10,102,111,114, 32,
 105,110,100,101,120, 44, 32,116,121,112,101,110, 97,109,101,
  32,105,110, 32,105,112, 97,105,114,115, 40, 97,112,105, 95,
 116,121,112,101,115, 41, 32,100,111, 10,108,111, 99, 97,108,
  32, 97,112,105, 95,116,121,112,101, 32, 61, 32, 95, 71, 91,
 116,121,112,101,110, 97,109,101, 93, 10, 97,112,105, 95,116,
 121,112,101, 91, 34, 46,101,113, 34, 93, 32, 61, 32,105,100,
  95,101,113, 10, 97,112,105, 95,116,121,112,101, 46, 95, 95,
 116,111,115,116,114,105,110,103, 32, 61, 32,115,116,114,105,
 110,103, 95,114,101,112, 10,108,111, 99, 97,108, 32, 97,112,
 105, 95,116,121,112,101, 95,105,110,100,101,120, 32, 61, 32,
  97,112,105, 95,116,121,112,101, 46, 95, 95,105,110,100,101,
 120, 10,108,111, 99, 97,108, 32,112,114,111,112,101,114,116,
 105,101,115, 32, 61, 32, 97,112,105, 95,116,121,112,101, 46,
 112,114,111,112,101,114,116,105,101,115, 10,108,111, 99, 97,
 108, 32,114, 97,119,101,113,117, 97,108, 32, 61, 32,114, 97,
 119,101,113,117, 97,108, 10,108,111, 99, 97,108, 32,115,116,
 114,105,110,103, 95,115,117, 98, 32, 61, 32,115,116,114,105,
 110,103, 46,115,117, 98, 10,108,111, 99, 97,108, 32,102,117,
 110, 99,116,105,111,110, 32,102,105,101,108,100, 95,103,101,
 116,116,101,114, 40,115,101,108,102, 44, 32,102,105,101,108,
 100, 41, 10,108,111, 99, 97,108, 32,103,101,116,116,101,114,
  32, 61, 32,112,114,111,112,101,114,116,105,101,115, 32, 97,
 110,100, 32,112,114,111,112,101,114,116,105,101,115, 91,102,
 105,101,108,100, 93, 10,105,102, 32,103,101,116,116,101,114,
  32,116,104,101,110, 10,114,101,116,117,114,110, 32,103,101,
 116,116,101,114, 40,115,101,108,102, 41, 10,101,108,115,101,
  10,108,111, 99, 97,108, 32,112,102,120, 32, 61, 32,115,116,
 114,105,110,103, 95,115,117, 98, 40,102,105,101,108,100, 44,
  32, 49, 44, 32, 49, 41, 10,105,102, 32,114, 97,119,101,113,
 117, 97,108, 40,112,102,120, 44, 32, 39, 46, 39, 41, 32,111,
 114, 32,114, 97,119,101,113,117, 97,108, 40,112,102,120, 44,
  32, 39, 95, 39, 41, 32,116,104,101,110, 10,114,101,116,117,
 114,110, 32,110,105,108, 10,101,108,115,101, 10,114,101,116,
 117,114,110, 32, 97,112,105, 95,116,121,112,101, 95,105,110,
 100,101,120, 40,115,101,108,102, 44, 32,102,105,101,108,100,
  41, 10,101,110,100, 10,101,110,100, 10,101,110,100, 10, 97,
 112,105, 95,116,121,112,101, 46, 95, 95,105,110,100,101,120,
  32, 61, 32,102,105,101,108,100, 95,103,101,116,116,101,114,
  10, 97,112,105, 95,116,121,112,101, 91, 34, 46,115,101,116,
  34, 93, 32, 61, 32,110,105,108, 10, 97,112,105, 95,116,121,
 112,101, 46, 95, 95,109,101,116, 97,116, 97, 98,108,101, 32,
  61, 32,102, 97,108,115,101, 10, 95, 71, 91,116,121,112,101,
 110, 97,109,101, 93, 32, 61, 32,110,105,108, 10,101,110,100,
  10,101,110,100, 10,116,111,108,117, 97, 32, 61, 32,123, 10,
 116,121,112,101, 61,116,111,108,117, 97, 46,116,121,112,101,
  44, 10,125,32
 };
 if (!luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code")) {
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 }
 } /* end of embedded lua code */

 tolua_module(tolua_S,"find",0);
 tolua_beginmodule(tolua_S,"find");
 tolua_function(tolua_S,"player",tolua_api_find_player00);
 tolua_function(tolua_S,"city",tolua_api_find_city00);
 tolua_function(tolua_S,"unit",tolua_api_find_unit00);
 tolua_function(tolua_S,"transport_unit",tolua_api_find_transport_unit00);
 tolua_function(tolua_S,"tile",tolua_api_find_tile00);
 tolua_function(tolua_S,"tile",tolua_api_find_tile01);
 tolua_function(tolua_S,"government",tolua_api_find_government00);
 tolua_function(tolua_S,"government",tolua_api_find_government01);
 tolua_function(tolua_S,"nation_type",tolua_api_find_nation_type00);
 tolua_function(tolua_S,"nation_type",tolua_api_find_nation_type01);
 tolua_function(tolua_S,"building_type",tolua_api_find_building_type00);
 tolua_function(tolua_S,"building_type",tolua_api_find_building_type01);
 tolua_function(tolua_S,"unit_type",tolua_api_find_unit_type00);
 tolua_function(tolua_S,"unit_type",tolua_api_find_unit_type01);
 tolua_function(tolua_S,"role_unit_type",tolua_api_find_role_unit_type00);
 tolua_function(tolua_S,"tech_type",tolua_api_find_tech_type00);
 tolua_function(tolua_S,"tech_type",tolua_api_find_tech_type01);
 tolua_function(tolua_S,"terrain",tolua_api_find_terrain00);
 tolua_function(tolua_S,"terrain",tolua_api_find_terrain01);
 tolua_function(tolua_S,"nonexistent",tolua_api_find_nonexistent00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 95,102,114,101,101,
  99,105,118, 95,115,116, 97,116,101, 95,100,117,109,112, 40,
  41, 10,108,111, 99, 97,108, 32,114,101,115, 32, 61, 32, 39,
  39, 10,102,111,114, 32,107, 44, 32,118, 32,105,110, 32,112,
  97,105,114,115, 40, 95, 71, 41, 32,100,111, 10,105,102, 32,
 107, 32, 61, 61, 32, 39, 95, 86, 69, 82, 83, 73, 79, 78, 39,
  32,116,104,101,110, 10,101,108,115,101,105,102, 32,116,121,
 112,101, 40,118, 41, 32, 61, 61, 32, 39, 98,111,111,108,101,
  97,110, 39, 10,111,114, 32,116,121,112,101, 40,118, 41, 32,
  61, 61, 32, 39,110,117,109, 98,101,114, 39, 32,116,104,101,
 110, 10,108,111, 99, 97,108, 32,114,118, 97,108,117,101, 32,
  61, 32,116,111,115,116,114,105,110,103, 40,118, 41, 10,114,
 101,115, 32, 61, 32,114,101,115, 32, 46, 46, 32,107, 32, 46,
  46, 32, 39, 61, 39, 32, 46, 46, 32,114,118, 97,108,117,101,
  32, 46, 46, 32, 39, 92,110, 39, 10,101,108,115,101,105,102,
  32,116,121,112,101, 40,118, 41, 32, 61, 61, 32, 39,115,116,
 114,105,110,103, 39, 32,116,104,101,110, 10,108,111, 99, 97,
 108, 32,114,118, 97,108,117,101, 32, 61, 32,115,116,114,105,
 110,103, 46,102,111,114,109, 97,116, 40, 39, 37,113, 39, 44,
  32,118, 41, 10,114,101,115, 32, 61, 32,114,101,115, 32, 46,
  46, 32,107, 32, 46, 46, 32, 39, 61, 39, 32, 46, 46, 32,114,
 118, 97,108,117,101, 32, 46, 46, 32, 39, 92,110, 39, 10,101,
 108,115,101,105,102, 32,116,121,112,101, 40,118, 41, 32, 61,
  61, 32, 39,117,115,101,114,100, 97,116, 97, 39, 32,116,104,
 101,110, 10,108,111, 99, 97,108, 32,109,101,116,104,111,100,
  32, 61, 32,115,116,114,105,110,103, 46,108,111,119,101,114,
  40,116,111,108,117, 97, 46,116,121,112,101, 40,118, 41, 41,
  10,114,101,115, 32, 61, 32,114,101,115, 32, 46, 46, 32,107,
  32, 46, 46, 32, 39, 61,102,105,110,100, 46, 39, 32, 46, 46,
  32,109,101,116,104,111,100, 10,105,102, 32,109,101,116,104,
 111,100, 32, 61, 61, 32, 39, 99,105,116,121, 39, 32,111,114,
  32,109,101,116,104,111,100, 32, 61, 61, 32, 39,117,110,105,
 116, 39, 32,116,104,101,110, 10,114,101,115, 32, 61, 32,114,
 101,115, 32, 46, 46, 32, 39, 40,110,105,108, 44, 39, 32, 46,
  46, 32,118, 46,105,100, 32, 46, 46, 32, 39, 41, 39, 10,101,
 108,115,101,105,102, 32,118, 46,105,100, 32,116,104,101,110,
  10,114,101,115, 32, 61, 32,114,101,115, 32, 46, 46, 32, 39,
  40, 39, 32, 46, 46, 32,118, 46,105,100, 32, 46, 46, 32, 39,
  41, 39, 10,101,108,115,101, 10,114,101,115, 32, 61, 32,114,
 101,115, 32, 46, 46, 32, 39, 40, 41, 39, 10,101,110,100, 10,
 114,101,115, 32, 61, 32,114,101,115, 32, 46, 46, 32, 39, 92,
 110, 39, 10,101,110,100, 10,101,110,100, 10,114,101,116,117,
 114,110, 32,114,101,115, 10,101,110,100,32
 };
 if (!luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code")) {
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 }
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
 if (!luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code")) {
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 }
 } /* end of embedded lua code */

 tolua_module(tolua_S,"signal",0);
 tolua_beginmodule(tolua_S,"signal");
 tolua_function(tolua_S,"connect",tolua_api_signal_connect00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"_",tolua_api__00);
 tolua_function(tolua_S,"N_",tolua_api_N_00);
 tolua_function(tolua_S,"Q_",tolua_api_Q_00);
 tolua_function(tolua_S,"PL_",tolua_api_PL_00);
 tolua_module(tolua_S,"notify",0);
 tolua_beginmodule(tolua_S,"notify");
 tolua_function(tolua_S,"embassies_msg",tolua_api_notify_embassies_msg00);
 tolua_function(tolua_S,"event_msg",tolua_api_notify_event_msg00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"E",0);
 tolua_beginmodule(tolua_S,"E");
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,110,111,116,105,102,
 121, 46, 97,108,108, 40, 46, 46, 46, 41, 10,110,111,116,105,
 102,121, 46,101,118,101,110,116, 95,109,115,103, 40,110,105,
 108, 44, 32,110,105,108, 44, 32, 69, 46, 83, 67, 82, 73, 80,
  84, 44, 32,115,116,114,105,110,103, 46,102,111,114,109, 97,
 116, 40,117,110,112, 97, 99,107, 40, 97,114,103, 41, 41, 41,
  10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,110,
 111,116,105,102,121, 46,112,108, 97,121,101,114, 40,112,108,
  97,121,101,114, 44, 32, 46, 46, 46, 41, 10,110,111,116,105,
 102,121, 46,101,118,101,110,116, 95,109,115,103, 40,112,108,
  97,121,101,114, 44, 32,110,105,108, 44, 32, 69, 46, 83, 67,
  82, 73, 80, 84, 44, 32,115,116,114,105,110,103, 46,102,111,
 114,109, 97,116, 40,117,110,112, 97, 99,107, 40, 97,114,103,
  41, 41, 41, 10,101,110,100, 10,102,117,110, 99,116,105,111,
 110, 32,110,111,116,105,102,121, 46,101,118,101,110,116, 40,
 112,108, 97,121,101,114, 44, 32,116,105,108,101, 44, 32,101,
 118,101,110,116, 44, 32, 46, 46, 46, 41, 10,110,111,116,105,
 102,121, 46,101,118,101,110,116, 95,109,115,103, 40,112,108,
  97,121,101,114, 44, 32,116,105,108,101, 44, 32,101,118,101,
 110,116, 44, 32,115,116,114,105,110,103, 46,102,111,114,109,
  97,116, 40,117,110,112, 97, 99,107, 40, 97,114,103, 41, 41,
  41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
 110,111,116,105,102,121, 46,101,109, 98, 97,115,115,105,101,
 115, 40,112,108, 97,121,101,114, 44, 32,112,116,105,108,101,
  44, 32,101,118,101,110,116, 44, 32, 46, 46, 46, 41, 10,110,
 111,116,105,102,121, 46,101,109, 98, 97,115,115,105,101,115,
  95,109,115,103, 40,112,108, 97,121,101,114, 44, 32,112,116,
 105,108,101, 44, 32,101,118,101,110,116, 44, 32,115,116,114,
 105,110,103, 46,102,111,114,109, 97,116, 40,117,110,112, 97,
  99,107, 40, 97,114,103, 41, 41, 41, 10,101,110,100,32
 };
 if (!luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code")) {
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 }
 } /* end of embedded lua code */

 tolua_module(tolua_S,"effects",0);
 tolua_beginmodule(tolua_S,"effects");
 tolua_function(tolua_S,"world_bonus",tolua_api_effects_world_bonus00);
 tolua_function(tolua_S,"player_bonus",tolua_api_effects_player_bonus00);
 tolua_function(tolua_S,"city_bonus",tolua_api_effects_city_bonus00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"random",tolua_api_random00);
 tolua_function(tolua_S,"error_log",tolua_api_error_log00);
 tolua_function(tolua_S,"debug_log",tolua_api_debug_log00);
 tolua_function(tolua_S,"create_unit",tolua_api_create_unit00);
 tolua_function(tolua_S,"create_unit_full",tolua_api_create_unit_full00);
 tolua_function(tolua_S,"create_city",tolua_api_create_city00);
 tolua_function(tolua_S,"create_base",tolua_api_create_base00);
 tolua_function(tolua_S,"create_player",tolua_api_create_player00);
 tolua_function(tolua_S,"change_gold",tolua_api_change_gold00);
 tolua_function(tolua_S,"give_technology",tolua_api_give_technology00);
 tolua_function(tolua_S,"unleash_barbarians",tolua_api_unleash_barbarians00);
 tolua_function(tolua_S,"place_partisans",tolua_api_place_partisans00);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_api_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_api);
 lua_pushstring(tolua_S, "api");
 lua_call(tolua_S, 1, 0);
 return 1;
}
