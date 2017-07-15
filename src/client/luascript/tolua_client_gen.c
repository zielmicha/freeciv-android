/*
** Lua binding: client
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
TOLUA_API int tolua_client_open (lua_State* tolua_S);
LUALIB_API int luaopen_client (lua_State* tolua_S);

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif
#include "luascript_types.h"
#include "api_client_base.h"
#include "script_client.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: api_client_chat_base */
static int tolua_client_chat_base00(lua_State* tolua_S)
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
  const char* message = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  api_client_chat_base(L,message);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'base'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_client (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"chat",0);
 tolua_beginmodule(tolua_S,"chat");
 tolua_function(tolua_S,"base",tolua_client_chat_base00);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
 static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32, 99,104, 97,116, 46,
 109,115,103, 40,102,109,116, 44, 32, 46, 46, 46, 41, 10, 99,
 104, 97,116, 46, 98, 97,115,101, 40,115,116,114,105,110,103,
  46,102,111,114,109, 97,116, 40,102,109,116, 44, 32, 46, 46,
  46, 41, 41, 10,101,110,100,32
 };
 if (luaL_loadbuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code") == LUA_OK)
 lua_pcall(tolua_S,0,LUA_MULTRET,0);
 } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_client_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_client);
 lua_pushstring(tolua_S, "client");
 lua_call(tolua_S, 1, 0);
 return 1;
}
