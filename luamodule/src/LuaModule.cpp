#include "LuaModule.hpp"

static lua_State** LUA_BASE; // Lua解释器起始位置
static int nThreadCount; // 总线程数
char* MODULE_ACTIONS[65536]; // 功能号与函数映射关系表
char* BEFORE_ACTIONS[65536]; // 
char* AFTER_ACTIONS[65536]; //

LPFN_GETPUSHCODE TztGetPushCode;
LPFN_SENDPUSH TztSendPush;
LPFN_ONANSWERCALLBACK TztCallBackReturnAsIs; // 原样返回的回调函数
LPFN_ONANSWERCALLBACK TztCallBackNoReturn; // 不返回任何结果的回调函数
LPFN_ONANSWERCALLBACK TztCallBack; // 自定义的回调函数

BOOL FUNCTION_CALL_MODE DoModuleInit( IModuleInterface& IModule )
{
	try
	{
		// step 1. 获取外部框架信息
		TZT_CommonInfo* lpInfo = IModule.GetTZT_CommonInfo();
		TztGetPushCode = (LPFN_GETPUSHCODE) (lpInfo->lpGetProcAddress("GetPushCode"));
		TztSendPush = (LPFN_SENDPUSH) (lpInfo->lpGetProcAddress("SendPush"));
		TztCallBackReturnAsIs = (LPFN_ONANSWERCALLBACK) OnAnswerCallBackReturnAsIs;
		TztCallBackNoReturn = (LPFN_ONANSWERCALLBACK) OnAnswerCallBackNoReturn;
		TztCallBack = (LPFN_ONANSWERCALLBACK) OnAnswerCallBack;
		if (TztGetPushCode == NULL || TztSendPush == NULL) return FALSE;
		
		/* 
		lpInfo->CurrPath
		lpInfo->ThreadCound
		尤其是 lpInfo->ThreadCound 做为线程总数,内部可据此创建出相应的配套资源
		*/
		nThreadCount = lpInfo->ThreadCound;
		/* 建立Lua运行环境 */
		LUA_BASE = (lua_State**) new lua_State*[nThreadCount+1];
		for (int i = 0; i <= nThreadCount; i++)
		{
			LUA_BASE[i] = luaL_newstate();
			luaL_openlibs(LUA_BASE[i]);
			//luaopen_base(LUA_BASE[i]);
			luaopen_mLuaWrapper(LUA_BASE[i]);
			luaopen_cjson(LUA_BASE[i]);
			luaopen_mime_core(LUA_BASE[i]);
			luaopen_socket_core(LUA_BASE[i]);
			luaopen_luasql_odbc(LUA_BASE[i]);
			luaL_dofile(LUA_BASE[i], "module\\scripts\\RegisterLuaModuleAction.lua");
			lua_getglobal(LUA_BASE[i], "LoadLuaFiles");
			if (lua_pcall(LUA_BASE[i], 0, 0, 0) != 0){
				return FALSE;
			};
		}

		// step 2. 设置本组件属性 显示在外壳EXE组件列表中的名字
		IModule.SetModuleProperty(0, "Lua组件 v7.00.001");

		// step 3. 添加功能项 只需调用其中一个Lua解释器即可
		//luaopen_mLuaWrapper(LUA_BASE[0]);
		luaL_dofile(LUA_BASE[0], "module\\scripts\\RegisterLuaModuleAction.lua");
		lua_getglobal(LUA_BASE[0], "RegisterModuleAction");
		lua_pushlightuserdata(LUA_BASE[0], &IModule);
		if (lua_pcall(LUA_BASE[0], 1, 0, 0) != 0){
			return FALSE;
		};

		// step 4. 种类初始化，例如内存池、数据库连接...

		//全部成功完成后返回TRUE
		return TRUE;
	}
	catch(...)
	{
	}
	return FALSE;
}

BOOL FUNCTION_CALL_MODE DoModuleAction(IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State *L = LUA_BASE[threadTag];
	int actionId = IReq.GetIntByName("Action");
	if (actionId <= 0) {
		IAns.SetIntByName("ErrorNo", -1);
		IAns.SetStrByName("ErrorMessage", "actionId should be positive integer");
		 return FALSE;
	}
	const char* actionLuaFunc = MODULE_ACTIONS[actionId];
	if (actionLuaFunc == NULL) {
		IAns.SetIntByName("ErrorNo", -actionId);
		IAns.SetStrByName("ErrorMessage", "lua function is undefined");
		return FALSE;
	}
	lua_getglobal(L, MODULE_ACTIONS[actionId]);
	lua_pushlightuserdata(L, &IReq);
	lua_pushlightuserdata(L, &IAns);
	lua_pushlightuserdata(L, &IExp);
	if (lua_pcall(L, 3, 1, 0) == 0)	{
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", 0);
			IAns.SetStrByName("ErrorMessage", "ok");
		}
		if (lua_isboolean(L, -1))
			return lua_toboolean(L, -1); // return as Lua function is
		else
			return FALSE;
	} else {
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", -actionId);
			IAns.SetStrByName("ErrorMessage", lua_tostring(L, -1)); // error message
		}
		return FALSE;
	};
}

BOOL FUNCTION_CALL_MODE DoBeforeAction(IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State *L = LUA_BASE[threadTag];
	int actionId = IReq.GetIntByName("Action");
	if (actionId <= 0) {
		IAns.SetIntByName("ErrorNo", -1);
		IAns.SetStrByName("ErrorMessage", "actionId should be positive integer");
		 return FALSE;
	}
	const char* actionLuaFunc = BEFORE_ACTIONS[actionId];
	if (actionLuaFunc == NULL) {
		IAns.SetIntByName("ErrorNo", -actionId);
		IAns.SetStrByName("ErrorMessage", "lua function is undefined");
		return FALSE;
	}
	lua_getglobal(L, BEFORE_ACTIONS[actionId]);
	lua_pushlightuserdata(L, &IReq);
	lua_pushlightuserdata(L, &IAns);
	lua_pushlightuserdata(L, &IExp);
	if (lua_pcall(L, 3, 1, 0) == 0)	{
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", 0);
			IAns.SetStrByName("ErrorMessage", "ok");
		}
		if (lua_isboolean(L, -1))
			return lua_toboolean(L, -1); // return as Lua function is
		else
			return FALSE;
	} else {
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", -actionId);
			IAns.SetStrByName("ErrorMessage", lua_tostring(L, -1)); // error message
		}
		return FALSE;
	};
}

BOOL FUNCTION_CALL_MODE DoAfterAction(IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State *L = LUA_BASE[threadTag];
	int actionId = IReq.GetIntByName("Action");
	if (actionId <= 0) {
		IAns.SetIntByName("ErrorNo", -1);
		IAns.SetStrByName("ErrorMessage", "actionId should be positive integer");
		 return FALSE;
	}
	const char* actionLuaFunc = AFTER_ACTIONS[actionId];
	if (actionLuaFunc == NULL) {
		IAns.SetIntByName("ErrorNo", -actionId);
		IAns.SetStrByName("ErrorMessage", "lua function is undefined");
		return FALSE;
	}
	lua_getglobal(L, AFTER_ACTIONS[actionId]);
	lua_pushlightuserdata(L, &IReq);
	lua_pushlightuserdata(L, &IAns);
	lua_pushlightuserdata(L, &IExp);
	if (lua_pcall(L, 3, 1, 0) == 0)	{
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", 0);
			IAns.SetStrByName("ErrorMessage", "ok");
		}
		if (lua_isboolean(L, -1))
			return lua_toboolean(L, -1); // return as Lua function is
		else
			return FALSE;
	} else {
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", -actionId);
			IAns.SetStrByName("ErrorMessage", lua_tostring(L, -1)); // error message
		}
		return FALSE;
	};
}

BOOL FUNCTION_CALL_MODE DoModuleFree()
{
	/* 销毁Lua运行环境 */
	for (int i = 0; i <= nThreadCount; i++)
	{
		lua_close(LUA_BASE[i]);
	}
	delete []LUA_BASE;
	return TRUE;
}

/* 不向客户端返回应答 */
BOOL FUNCTION_CALL_MODE OnAnswerCallBackNoReturn(IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State* L = LUA_BASE[threadTag];

	char* handleSerialNo = IAns.GetStrByName("HandleSerialNo");
	char* sharp = strrchr(handleSerialNo, '#'); // 最右侧的是当前回调函数
	char* column = strrchr(handleSerialNo, '|'); // 次右侧的是当前功能号
	//IAns.SetStrByName("CurrentCallback", currentCallback);
	char* currentAction = new char[10];
	strncpy_s(currentAction, 100, column + 1, sharp - column -1);
	int actionId = atoi(currentAction);
	char* newSerialNo = new char[1024]; // 从栈中清除当前功能号和当前回调函数
	strncpy_s(newSerialNo, 1024, handleSerialNo, column - handleSerialNo);

	IAns.SetStrByName("HandleSerialNo", newSerialNo);
	IAns.SetStrByName("Action", currentAction);

	return TRUE;
}

/* 收到什么就返回客户端什么 */
BOOL FUNCTION_CALL_MODE OnAnswerCallBackReturnAsIs(IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State* L = LUA_BASE[threadTag];

	char* handleSerialNo = IAns.GetStrByName("HandleSerialNo");
	char* sharp = strrchr(handleSerialNo, '#'); // 最右侧的是当前回调函数
	char* column = strrchr(handleSerialNo, '|'); // 次右侧的是当前功能号
	//IAns.SetStrByName("CurrentCallback", currentCallback);
	char* currentAction = new char[10];
	strncpy_s(currentAction, 100, column + 1, sharp - column -1);
	int actionId = atoi(currentAction);
	char* newSerialNo = new char[1024]; // 从栈中清除当前功能号和当前回调函数
	strncpy_s(newSerialNo, 1024, handleSerialNo, column - handleSerialNo);

	IAns.SetStrByName("HandleSerialNo", newSerialNo);
	IAns.SetStrByName("Action", currentAction);

	return FALSE;
}

BOOL FUNCTION_CALL_MODE OnAnswerCallBack(IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State* L = LUA_BASE[threadTag];

	char* handleSerialNo = IAns.GetStrByName("HandleSerialNo");
	char* sharp = strrchr(handleSerialNo, '#'); // 最右侧的是当前回调函数
	char* column = strrchr(handleSerialNo, '|'); // 次右侧的是当前功能号
	char* currentCallback = new char[100];
	strncpy_s(currentCallback, 100, sharp + 1, 100);
	//IAns.SetStrByName("CurrentCallback", currentCallback);
	char* currentAction = new char[10];
	strncpy_s(currentAction, 100, column + 1, sharp - column -1);
	int actionId = atoi(currentAction);
	char* newSerialNo = new char[1024]; // 从栈中清除当前功能号和当前回调函数
	strncpy_s(newSerialNo, 1024, handleSerialNo, column - handleSerialNo);
	IAns.SetStrByName("HandleSerialNo", newSerialNo);
	lua_getglobal(L, currentCallback);
	lua_pushlightuserdata(L, &IAns);
	lua_pushlightuserdata(L, &IExp);
	if (lua_pcall(L, 2, 1, 0) == 0)	{
		IAns.SetStrByName("Action", currentAction);
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", 0);
			IAns.SetStrByName("ErrorMessage", "ok");
		}
		if (lua_isboolean(L, -1))
			return lua_toboolean(L, -1); // return as Lua function is
		else
			return FALSE;
	} else {
		if (strlen(IAns.GetStrByName("ErrorNo")) == 0) {
			IAns.SetIntByName("ErrorNo", -1);
			IAns.SetStrByName("ErrorMessage", lua_tostring(L, -1)); // error message
		}
		return FALSE;
	};
}