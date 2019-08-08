#ifndef LUA_MODULE_H
#define LUA_MODULE_H

#define __EXPORTING
#define LUASOCKET_API

#include "tzt\md_interface.hpp"   // �ӿ��ļ�
#include "lua\lua.hpp"
#include "LuaWrapper.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "luasocket\luasocket.h"
#include "luasocket\mime.h"
#include "cjson\lua_cjson.h"
#include "luasql\luasql.h"

extern lua_State** LUA_BASE; // Lua��������ʼλ��
extern int nThreadCount; // ���߳���
extern char* MODULE_ACTIONS[65536];
extern char* BEFORE_ACTIONS[65536];
extern char* AFTER_ACTIONS[65536];

//��ں���
extern BOOL FUNCTION_CALL_MODE DoModuleInit( IModuleInterface & IModule);
extern BOOL FUNCTION_CALL_MODE DoModuleFree();

//ҵ���ܺ���
extern BOOL FUNCTION_CALL_MODE DoModuleAction(IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp);
extern BOOL FUNCTION_CALL_MODE DoBeforeAction(IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp);
extern BOOL FUNCTION_CALL_MODE DoAfterAction(IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp);
//ҵ���ܻص�
extern BOOL FUNCTION_CALL_MODE OnAnswerCallBackReturnAsIs(IDataSet& IAns, IExpandInterface& IExp);
extern BOOL FUNCTION_CALL_MODE OnAnswerCallBackNoReturn(IDataSet& IAns, IExpandInterface& IExp);
extern BOOL FUNCTION_CALL_MODE OnAnswerCallBack(IDataSet& IAns, IExpandInterface& IExp);

#ifdef __cplusplus
}
#endif

#endif //LUA_MODULE_H

