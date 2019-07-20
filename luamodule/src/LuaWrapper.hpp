#ifndef LUA_WRAPPER_H
#define LUA_WRAPPER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "LuaModule.hpp"
#include "lua\lua.hpp"
#include "util\util.hpp"

#ifdef _WIN32
	#ifndef WIN_API
	#define WIN_API		__stdcall
	#endif
#else
	#define WIN_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int WIN_API luaopen_mLuaWrapper(lua_State *L);

#ifdef __cplusplus
}
#endif

#endif //LUA_WRAPPER_H