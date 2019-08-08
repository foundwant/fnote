#ifndef LUACJSON_H
#define LUACJSON_H
/*=========================================================================*\
\*=========================================================================*/
#include "..\lua\lua.h"

/*-------------------------------------------------------------------------*\
* Current socket library version
\*-------------------------------------------------------------------------*/
#define CJSON_VERSION    "cjson 2.1-devel"

/*-------------------------------------------------------------------------*\
* This macro prefixes all exported API functions
\*-------------------------------------------------------------------------*/
#ifndef CJSON_EXPORT
#ifdef _WIN32
#define CJSON_EXPORT __declspec(dllexport)
#else
#define CJSON_EXPORT __attribute__ ((visibility ("default")))
#endif
#endif

/*-------------------------------------------------------------------------*\
* Initializes the library.
\*-------------------------------------------------------------------------*/
CJSON_EXPORT int luaopen_cjson(lua_State *l);

#endif /* LUACJSON_H */
