#include "LuaModule.hpp"

static lua_State** LUA_BASE; // Lua��������ʼλ��
static int nThreadCount; // ���߳���
char* MODULE_ACTIONS[65536]; // ���ܺ��뺯��ӳ���ϵ��
char* BEFORE_ACTIONS[65536]; // 
char* AFTER_ACTIONS[65536]; //

LPFN_GETPUSHCODE TztGetPushCode;
LPFN_SENDPUSH TztSendPush;
LPFN_ONANSWERCALLBACK TztCallBackReturnAsIs; // ԭ�����صĻص�����
LPFN_ONANSWERCALLBACK TztCallBackNoReturn; // �������κν���Ļص�����
LPFN_ONANSWERCALLBACK TztCallBack; // �Զ���Ļص�����

BOOL FUNCTION_CALL_MODE DoModuleInit( IModuleInterface& IModule )
{
	try
	{
		// step 1. ��ȡ�ⲿ�����Ϣ
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
		������ lpInfo->ThreadCound ��Ϊ�߳�����,�ڲ��ɾݴ˴�������Ӧ��������Դ
		*/
		nThreadCount = lpInfo->ThreadCound;
		/* ����Lua���л��� */
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

		// step 2. ���ñ�������� ��ʾ�����EXE����б��е�����
		IModule.SetModuleProperty(0, "Lua��� v7.00.001");

		// step 3. ��ӹ����� ֻ���������һ��Lua����������
		//luaopen_mLuaWrapper(LUA_BASE[0]);
		luaL_dofile(LUA_BASE[0], "module\\scripts\\RegisterLuaModuleAction.lua");
		lua_getglobal(LUA_BASE[0], "RegisterModuleAction");
		lua_pushlightuserdata(LUA_BASE[0], &IModule);
		if (lua_pcall(LUA_BASE[0], 1, 0, 0) != 0){
			return FALSE;
		};

		// step 4. �����ʼ���������ڴ�ء����ݿ�����...

		//ȫ���ɹ���ɺ󷵻�TRUE
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
	/* ����Lua���л��� */
	for (int i = 0; i <= nThreadCount; i++)
	{
		lua_close(LUA_BASE[i]);
	}
	delete []LUA_BASE;
	return TRUE;
}

/* ����ͻ��˷���Ӧ�� */
BOOL FUNCTION_CALL_MODE OnAnswerCallBackNoReturn(IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State* L = LUA_BASE[threadTag];

	char* handleSerialNo = IAns.GetStrByName("HandleSerialNo");
	char* sharp = strrchr(handleSerialNo, '#'); // ���Ҳ���ǵ�ǰ�ص�����
	char* column = strrchr(handleSerialNo, '|'); // ���Ҳ���ǵ�ǰ���ܺ�
	//IAns.SetStrByName("CurrentCallback", currentCallback);
	char* currentAction = new char[10];
	strncpy_s(currentAction, 100, column + 1, sharp - column -1);
	int actionId = atoi(currentAction);
	char* newSerialNo = new char[1024]; // ��ջ�������ǰ���ܺź͵�ǰ�ص�����
	strncpy_s(newSerialNo, 1024, handleSerialNo, column - handleSerialNo);

	IAns.SetStrByName("HandleSerialNo", newSerialNo);
	IAns.SetStrByName("Action", currentAction);

	return TRUE;
}

/* �յ�ʲô�ͷ��ؿͻ���ʲô */
BOOL FUNCTION_CALL_MODE OnAnswerCallBackReturnAsIs(IDataSet& IAns, IExpandInterface& IExp)
{
	int threadTag = IExp.ThreadTag();
	lua_State* L = LUA_BASE[threadTag];

	char* handleSerialNo = IAns.GetStrByName("HandleSerialNo");
	char* sharp = strrchr(handleSerialNo, '#'); // ���Ҳ���ǵ�ǰ�ص�����
	char* column = strrchr(handleSerialNo, '|'); // ���Ҳ���ǵ�ǰ���ܺ�
	//IAns.SetStrByName("CurrentCallback", currentCallback);
	char* currentAction = new char[10];
	strncpy_s(currentAction, 100, column + 1, sharp - column -1);
	int actionId = atoi(currentAction);
	char* newSerialNo = new char[1024]; // ��ջ�������ǰ���ܺź͵�ǰ�ص�����
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
	char* sharp = strrchr(handleSerialNo, '#'); // ���Ҳ���ǵ�ǰ�ص�����
	char* column = strrchr(handleSerialNo, '|'); // ���Ҳ���ǵ�ǰ���ܺ�
	char* currentCallback = new char[100];
	strncpy_s(currentCallback, 100, sharp + 1, 100);
	//IAns.SetStrByName("CurrentCallback", currentCallback);
	char* currentAction = new char[10];
	strncpy_s(currentAction, 100, column + 1, sharp - column -1);
	int actionId = atoi(currentAction);
	char* newSerialNo = new char[1024]; // ��ջ�������ǰ���ܺź͵�ǰ�ص�����
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