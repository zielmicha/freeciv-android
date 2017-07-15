/*
** Lua binding: common_a
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
TOLUA_API int tolua_common_a_open (lua_State* tolua_S);
LUALIB_API int luaopen_common_a (lua_State* tolua_S);

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif
#include "api_common_intl.h"
#include "api_common_utilities.h"
#include "luascript.h"
#include "luascript_types.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Nonexistent");
}

/* function: api_intl__ */
static int tolua_common_a__00(lua_State* tolua_S)
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
  const char* untranslated = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_intl__(L,untranslated);
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
static int tolua_common_a_N_00(lua_State* tolua_S)
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
  const char* untranslated = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_intl_N_(L,untranslated);
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
static int tolua_common_a_Q_00(lua_State* tolua_S)
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
  const char* untranslated = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_intl_Q_(L,untranslated);
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
static int tolua_common_a_PL_00(lua_State* tolua_S)
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
  lua_State* L =  tolua_S;
  const char* singular = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* plural = ((const char*)  tolua_tostring(tolua_S,2,0));
  int n = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  const char* tolua_ret = (const char*)  api_intl_PL_(L,singular,plural,n);
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

/* function: api_utilities_log_base */
static int tolua_common_a_log_base00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  int log_level = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  api_utilities_log_base(L,log_level,message);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'base'.",&tolua_err);
 return 0;
#endif
}

/* function: api_utilities_random */
static int tolua_common_a_random00(lua_State* tolua_S)
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
  int min = ((int)  tolua_tonumber(tolua_S,1,0));
  int max = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  api_utilities_random(L,min,max);
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

/* function: api_utilities_fc_version */
static int tolua_common_a_fc_version00(lua_State* tolua_S)
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
  const char* tolua_ret = (const char*)  api_utilities_fc_version(L);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fc_version'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_common_a (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"Nonexistent","Nonexistent","",NULL);
 tolua_beginmodule(tolua_S,"Nonexistent");
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 78,111,110,101,120,
 105,115,116,101,110,116, 58,101,120,105,115,116,115, 40, 41,
  10,114,101,116,117,114,110, 32,102, 97,108,115,101, 10,101,
 110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_function(tolua_S,"_",tolua_common_a__00);
 tolua_function(tolua_S,"N_",tolua_common_a_N_00);
 tolua_function(tolua_S,"Q_",tolua_common_a_Q_00);
 tolua_function(tolua_S,"PL_",tolua_common_a_PL_00);
 tolua_module(tolua_S,"log",0);
 tolua_beginmodule(tolua_S,"log");
 tolua_module(tolua_S,"level",0);
 tolua_beginmodule(tolua_S,"level");
 tolua_constant(tolua_S,"FATAL",LOG_FATAL);
 tolua_constant(tolua_S,"ERROR",LOG_ERROR);
 tolua_constant(tolua_S,"NORMAL",LOG_NORMAL);
 tolua_constant(tolua_S,"VERBOSE",LOG_VERBOSE);
 tolua_constant(tolua_S,"DEBUG",LOG_DEBUG);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"base",tolua_common_a_log_base00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,108,111,103, 46,102,
  97,116, 97,108, 40,102,109,116, 44, 32, 46, 46, 46, 41, 10,
 108,111,103, 46, 98, 97,115,101, 40,108,111,103, 46,108,101,
 118,101,108, 46, 70, 65, 84, 65, 76, 44, 32,115,116,114,105,
 110,103, 46,102,111,114,109, 97,116, 40,102,109,116, 44, 32,
  46, 46, 46, 41, 41, 10,101,110,100, 10,102,117,110, 99,116,
 105,111,110, 32,108,111,103, 46,101,114,114,111,114, 40,102,
 109,116, 44, 32, 46, 46, 46, 41, 10,108,111,103, 46, 98, 97,
 115,101, 40,108,111,103, 46,108,101,118,101,108, 46, 69, 82,
  82, 79, 82, 44, 32,115,116,114,105,110,103, 46,102,111,114,
 109, 97,116, 40,102,109,116, 44, 32, 46, 46, 46, 41, 41, 10,
 101,110,100, 10,102,117,110, 99,116,105,111,110, 32,108,111,
 103, 46,110,111,114,109, 97,108, 40,102,109,116, 44, 32, 46,
  46, 46, 41, 10,108,111,103, 46, 98, 97,115,101, 40,108,111,
 103, 46,108,101,118,101,108, 46, 78, 79, 82, 77, 65, 76, 44,
  32,115,116,114,105,110,103, 46,102,111,114,109, 97,116, 40,
 102,109,116, 44, 32, 46, 46, 46, 41, 41, 10,101,110,100, 10,
 102,117,110, 99,116,105,111,110, 32,108,111,103, 46,118,101,
 114, 98,111,115,101, 40,102,109,116, 44, 32, 46, 46, 46, 41,
  10,108,111,103, 46, 98, 97,115,101, 40,108,111,103, 46,108,
 101,118,101,108, 46, 86, 69, 82, 66, 79, 83, 69, 44, 32,115,
 116,114,105,110,103, 46,102,111,114,109, 97,116, 40,102,109,
 116, 44, 32, 46, 46, 46, 41, 41, 10,101,110,100, 10,102,117,
 110, 99,116,105,111,110, 32,108,111,103, 46,100,101, 98,117,
 103, 40,102,109,116, 44, 32, 46, 46, 46, 41, 10,108,111,103,
  46, 98, 97,115,101, 40,108,111,103, 46,108,101,118,101,108,
  46, 68, 69, 66, 85, 71, 44, 32,115,116,114,105,110,103, 46,
 102,111,114,109, 97,116, 40,102,109,116, 44, 32, 46, 46, 46,
  41, 41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110,
  32,101,114,114,111,114, 95,108,111,103, 40,109,115,103, 41,
  10,108,111,103, 46,101,114,114,111,114, 40,109,115,103, 41,
  10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,100,
 101, 98,117,103, 95,108,111,103, 40,109,115,103, 41, 10,108,
 111,103, 46,100,101, 98,117,103, 40,109,115,103, 41, 10,101,
 110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_function(tolua_S,"random",tolua_common_a_random00);
 tolua_function(tolua_S,"fc_version",tolua_common_a_fc_version00);

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
 114,110, 32,114,101,115, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32,108,105,115,116,101,110,118, 40, 41, 10,
 108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,
  95,108,105,115,116,101,110,118, 95,108,111,111,112, 40,111,
 102,102,115,101,116, 44, 32,100, 97,116, 97, 41, 10,108,111,
  99, 97,108, 32,110, 97,109,101, 10,108,111, 99, 97,108, 32,
 118, 97,108,117,101, 10,102,111,114, 32,110, 97,109,101, 44,
 118, 97,108,117,101, 32,105,110, 32,112, 97,105,114,115, 40,
 100, 97,116, 97, 41, 32,100,111, 10,105,102, 32,110, 97,109,
 101, 32,126, 61, 32, 34,108,111, 97,100,101,100, 34, 32, 97,
 110,100, 32,110, 97,109,101, 32,126, 61, 32, 34, 95, 71, 34,
  32, 97,110,100, 32,110, 97,109,101, 58,115,117, 98, 40, 48,
  44, 50, 41, 32,126, 61, 32, 34, 95, 95, 34, 32,116,104,101,
 110, 10,108,111,103, 46,110,111,114,109, 97,108, 40, 34, 37,
 115, 45, 32, 37,115, 58, 32, 37,115, 34, 44, 32,111,102,102,
 115,101,116, 44, 32,116,121,112,101, 40,118, 97,108,117,101,
  41, 44, 32,110, 97,109,101, 41, 10,105,102, 32,116,121,112,
 101, 40,118, 97,108,117,101, 41, 32, 61, 61, 32, 34,116, 97,
  98,108,101, 34, 32,116,104,101,110, 10, 95,108,105,115,116,
 101,110,118, 95,108,111,111,112, 40,111,102,102,115,101,116,
  32, 46, 46, 32, 34, 32, 34, 44, 32,118, 97,108,117,101, 41,
  10,101,110,100, 10,101,110,100, 10,101,110,100, 10,101,110,
 100, 10, 95,108,105,115,116,101,110,118, 95,108,111,111,112,
  40, 34, 34, 44, 32, 95, 71, 41, 10,101,110,100, 10, 99,111,
 110,115,116, 32, 61, 32,123,125, 10,108,111, 99, 97,108, 32,
 100, 97,116, 97, 32, 61, 32,123,125, 10, 99,111,110,115,116,
  95,109,116, 32, 61, 32,123, 10, 95, 95,110,101,119,105,110,
 100,101,120, 32, 61, 32,102,117,110, 99,116,105,111,110, 40,
  97, 44, 98, 44, 99, 41, 10,105,102, 32,100, 97,116, 97, 91,
  98, 93, 32, 61, 61, 32,110,105,108, 32,116,104,101,110, 10,
 105,102, 32,116,121,112,101, 40, 99, 41, 32, 61, 61, 32, 39,
 116, 97, 98,108,101, 39, 32,116,104,101,110, 10,108,111, 99,
  97,108, 32,112,114,111,120,121, 32, 61, 32,123,125, 10,108,
 111, 99, 97,108, 32,109,116, 32, 61, 32,123, 10, 95, 95,105,
 110,100,101,120, 32, 61, 32, 99, 44, 10, 95, 95,110,101,119,
 105,110,100,101,120, 32, 61, 32,102,117,110, 99,116,105,111,
 110, 32, 40,116, 44,107, 44,118, 41, 10,108,111,103, 46,101,
 114,114,111,114, 40, 91, 91, 34, 65,116,116,101,109,112,116,
  32,116,111, 32,117,112,100, 97,116,101, 32,114,101, 97,100,
  45,111,110,108,121, 32,116, 97, 98,108,101, 32, 39, 37,115,
  39, 32,105,110,100,101,120, 32, 39, 37,115, 39, 32, 34, 10,
  34,119,105,116,104, 32, 39, 37,115, 39, 46, 34, 93, 93, 44,
  32, 98, 44, 32,116,111,115,116,114,105,110,103, 40,107, 41,
  44, 32,116,111,115,116,114,105,110,103, 40,118, 41, 41, 10,
 101,110,100, 10,125, 10,115,101,116,109,101,116, 97,116, 97,
  98,108,101, 40,112,114,111,120,121, 44, 32,109,116, 41, 10,
 100, 97,116, 97, 91, 98, 93, 32, 61, 32,112,114,111,120,121,
  10,101,108,115,101, 10,100, 97,116, 97, 91, 98, 93, 32, 61,
  32, 99, 10,101,110,100, 10,101,108,115,101, 10,108,111,103,
  46,101,114,114,111,114, 40, 34, 73,108,108,101,103, 97,108,
  32, 97,115,115,105,103,110,109,101,110,116, 32,116,111, 32,
  99,111,110,115,116, 97,110,116, 32, 39, 37,115, 39, 46, 34,
  44, 32,116,111,115,116,114,105,110,103, 40, 98, 41, 41, 10,
 101,110,100, 10,101,110,100, 44, 10, 95, 95,105,110,100,101,
 120, 32, 61, 32,102,117,110, 99,116,105,111,110, 40, 97, 44,
  98, 41, 10,114,101,116,117,114,110, 32,100, 97,116, 97, 91,
  98, 93, 10,101,110,100, 10,125, 10,115,101,116,109,101,116,
  97,116, 97, 98,108,101, 40, 99,111,110,115,116, 44, 32, 99,
 111,110,115,116, 95,109,116, 41,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_common_a_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_common_a);
 lua_pushstring(tolua_S, "common_a");
 lua_call(tolua_S, 1, 0);
 return 1;
}
