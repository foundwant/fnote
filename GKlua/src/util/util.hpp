#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <random>
#include <windows.h>
#include <wchar.h>
#include "..\LuaModule.hpp"
#include "..\lua\lua.hpp"

//utf8 -> gb2312
int utf8togb2312(lua_State *L);

//gb23112 -> utf8
int gb2312toutf8(lua_State *L);

//murmurhash2Ëæ»úÊý
int mmh(lua_State *L);