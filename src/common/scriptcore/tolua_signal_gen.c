/*
** Lua binding: signal
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
TOLUA_API int tolua_signal_open (lua_State* tolua_S);
LUALIB_API int luaopen_signal (lua_State* tolua_S);

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif
#include "api_signal_base.h"
#include "luascript_types.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: api_signal_connect */
static int tolua_signal_signal_connect00(lua_State* tolua_S)
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
  lua_State* L =  tolua_S;
  const char* signal_name = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* callback_name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  api_signal_connect(L,signal_name,callback_name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}

/* function: api_signal_remove */
static int tolua_signal_signal_remove00(lua_State* tolua_S)
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
  lua_State* L =  tolua_S;
  const char* signal_name = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* callback_name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  api_signal_remove(L,signal_name,callback_name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}

/* function: api_signal_defined */
static int tolua_signal_signal_defined00(lua_State* tolua_S)
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
  lua_State* L =  tolua_S;
  const char* signal_name = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* callback_name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  api_signal_defined(L,signal_name,callback_name);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'defined'.",&tolua_err);
 return 0;
#endif
}

/* function: api_signal_by_index */
static int tolua_signal_find_signal00(lua_State* tolua_S)
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
  int index = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  api_signal_by_index(L,index);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'signal'.",&tolua_err);
 return 0;
#endif
}

/* function: api_signal_callback_by_index */
static int tolua_signal_find_signal_callback00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  const char* signal_name = ((const char*)  tolua_tostring(tolua_S,1,0));
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  const char* tolua_ret = (const char*)  api_signal_callback_by_index(L,signal_name,index);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'signal_callback'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_signal (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"signal",0);
 tolua_beginmodule(tolua_S,"signal");
 tolua_function(tolua_S,"connect",tolua_signal_signal_connect00);
 tolua_function(tolua_S,"remove",tolua_signal_signal_remove00);
 tolua_function(tolua_S,"defined",tolua_signal_signal_defined00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,115,105,103,110, 97,
 108, 46,108,105,115,116, 40, 41, 10,108,111, 99, 97,108, 32,
 115,105,103,110, 97,108, 95,105,100, 32, 61, 32, 48, 59, 10,
 108,111, 99, 97,108, 32,115,105,103,110, 97,108, 95,110, 97,
 109,101, 32, 61, 32,110,105,108, 59, 10,108,111,103, 46,110,
 111,114,109, 97,108, 40, 34, 76,105,115,116, 32,111,102, 32,
 115,105,103,110, 97,108,115, 58, 34, 41, 59, 10,114,101,112,
 101, 97,116, 10,108,111, 99, 97,108, 32,115,105,103,110, 97,
 108, 95,110, 97,109,101, 32, 61, 32,102,105,110,100, 46,115,
 105,103,110, 97,108, 40,115,105,103,110, 97,108, 95,105,100,
  41, 59, 10,105,102, 32, 40,115,105,103,110, 97,108, 95,110,
  97,109,101, 41, 32,116,104,101,110, 10,108,111, 99, 97,108,
  32, 99, 97,108,108, 98, 97, 99,107, 95,105,100, 32, 61, 32,
  48, 59, 10,108,111, 99, 97,108, 32, 99, 97,108,108, 98, 97,
  99,107, 95,110, 97,109,101, 32, 61, 32,110,105,108, 59, 10,
 108,111,103, 46,110,111,114,109, 97,108, 40, 34, 45, 32, 99,
  97,108,108, 98, 97, 99,107,115, 32,102,111,114, 32,115,105,
 103,110, 97,108, 32, 39, 37,115, 39, 58, 34, 44, 32,115,105,
 103,110, 97,108, 95,110, 97,109,101, 41, 59, 10,114,101,112,
 101, 97,116, 10,108,111, 99, 97,108, 32, 99, 97,108,108, 98,
  97, 99,107, 95,110, 97,109,101, 32, 61, 32,102,105,110,100,
  46,115,105,103,110, 97,108, 95, 99, 97,108,108, 98, 97, 99,
 107, 40,115,105,103,110, 97,108, 95,110, 97,109,101, 44, 32,
  99, 97,108,108, 98, 97, 99,107, 95,105,100, 41, 59, 10,105,
 102, 32, 40, 99, 97,108,108, 98, 97, 99,107, 95,110, 97,109,
 101, 41, 32,116,104,101,110, 10,108,111,103, 46,110,111,114,
 109, 97,108, 40, 34, 32, 91, 37, 51,100, 93, 32, 39, 37,115,
  39, 34, 44, 32, 99, 97,108,108, 98, 97, 99,107, 95,105,100,
  44, 32, 99, 97,108,108, 98, 97, 99,107, 95,110, 97,109,101,
  41, 59, 10,101,110,100, 10, 99, 97,108,108, 98, 97, 99,107,
  95,105,100, 32, 61, 32, 99, 97,108,108, 98, 97, 99,107, 95,
 105,100, 32, 43, 32, 49, 59, 10,117,110,116,105,108, 32, 40,
  99, 97,108,108, 98, 97, 99,107, 95,110, 97,109,101, 32, 61,
  61, 32,110,105,108, 41, 59, 10,115,105,103,110, 97,108, 95,
 105,100, 32, 61, 32,115,105,103,110, 97,108, 95,105,100, 32,
  43, 32, 49, 59, 10,101,110,100, 10,117,110,116,105,108, 32,
  40,115,105,103,110, 97,108, 95,110, 97,109,101, 32, 61, 61,
  32,110,105,108, 41, 59, 10,101,110,100, 10,102,117,110, 99,
 116,105,111,110, 32,115,105,103,110, 97,108, 46,114,101,112,
 108, 97, 99,101, 40,115,105,103,110, 97,108, 95,110, 97,109,
 101, 44, 32, 99, 97,108,108, 98, 97, 99,107, 95,110, 97,109,
 101, 41, 10,105,102, 32,115,105,103,110, 97,108, 46,100,101,
 102,105,110,101,100, 40,115,105,103,110, 97,108, 95,110, 97,
 109,101, 44, 32, 99, 97,108,108, 98, 97, 99,107, 95,110, 97,
 109,101, 41, 32,116,104,101,110, 10,115,105,103,110, 97,108,
  46,114,101,109,111,118,101, 40,115,105,103,110, 97,108, 95,
 110, 97,109,101, 44, 32, 99, 97,108,108, 98, 97, 99,107, 95,
 110, 97,109,101, 41, 10,101,110,100, 10,115,105,103,110, 97,
 108, 46, 99,111,110,110,101, 99,116, 40,115,105,103,110, 97,
 108, 95,110, 97,109,101, 44, 32, 99, 97,108,108, 98, 97, 99,
 107, 95,110, 97,109,101, 41, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"find",0);
 tolua_beginmodule(tolua_S,"find");
 tolua_function(tolua_S,"signal",tolua_signal_find_signal00);
 tolua_function(tolua_S,"signal_callback",tolua_signal_find_signal_callback00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_signal_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_signal);
 lua_pushstring(tolua_S, "signal");
 lua_call(tolua_S, 1, 0);
 return 1;
}
