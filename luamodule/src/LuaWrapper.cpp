#include "LuaWrapper.hpp"

static int IModule_AddModuleAction(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 5) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 5, n);
	// 1. 注册中焯功能号
	IModuleInterface* module = (IModuleInterface*)lua_touserdata(L, 1);
	if (module == NULL) return luaL_error(L, "iModule is nil");
	lua_Integer actionId = lua_tointeger(L, 2);
	if (actionId <= 0 || actionId > 65535) return luaL_error(L, "action %d is out of scope 1~65535", actionId);
	const char* actionDesc = lua_tostring(L, 3);
	const char* actionVer = lua_tostring(L, 4);
	module->AddModuleAction((int)actionId, (char*) actionDesc, (char*)actionVer, DoModuleAction);
	// 2. 注册功能号与Lua函数映射关系
	const char* actionLuaFunc = lua_tostring(L, 5);
	if (actionLuaFunc == NULL) return luaL_error(L, "lua function of Action %d is undefined", actionId);
	MODULE_ACTIONS[actionId] = (char *)actionLuaFunc;
	return 0; // 返回0个值
}

static int IModule_AddBeforeAction(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 5) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 5, n);
	// 1. 注册中焯功能号
	IModuleInterface* module = (IModuleInterface*)lua_touserdata(L, 1);
	if (module == NULL) return luaL_error(L, "iModule is nil");
	lua_Integer actionId = lua_tointeger(L, 2);
	if (actionId <= 0 || actionId > 65535) return luaL_error(L, "action %d is out of scope 1~65535", actionId);
	const char* actionDesc = lua_tostring(L, 3);
	const char* actionVer = lua_tostring(L, 4);
	module->AddBeforeAction((int)actionId, (char*) actionDesc, (char*)actionVer, DoBeforeAction);
	// 2. 注册功能号与Lua函数映射关系
	const char* actionLuaFunc = lua_tostring(L, 5);
	if (actionLuaFunc == NULL) return luaL_error(L, "lua function of Action %d is undefined", actionId);
	BEFORE_ACTIONS[actionId] = (char *)actionLuaFunc;
	return 0; // 返回0个值
}

static int IModule_AddAfterAction(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 5) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 5, n);
	// 1. 注册中焯功能号
	IModuleInterface* module = (IModuleInterface*)lua_touserdata(L, 1);
	if (module == NULL) return luaL_error(L, "iModule is nil");
	lua_Integer actionId = lua_tointeger(L, 2);
	if (actionId <= 0 || actionId > 65535) return luaL_error(L, "action %d is out of scope 1~65535", actionId);
	const char* actionDesc = lua_tostring(L, 3);
	const char* actionVer = lua_tostring(L, 4);
	module->AddAfterAction((int)actionId, (char*) actionDesc, (char*)actionVer, DoAfterAction);
	// 2. 注册功能号与Lua函数映射关系
	const char* actionLuaFunc = lua_tostring(L, 5);
	if (actionLuaFunc == NULL) return luaL_error(L, "lua function of Action %d is undefined", actionId);
	AFTER_ACTIONS[actionId] = (char *)actionLuaFunc;
	return 0; // 返回0个值
}

static int Lua_LoadLuaFile(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	// 1. 加载Lua文件
	for (int i = 1; i <= n; i++)
	{
		luaL_dofile(L, lua_tostring(L, i));
	}
	return 0; // 返回0个值
}

static int IDataSet_GetIntByName(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 2) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 2, n);
	// 1. 入参出栈
	IDataSet* data = (IDataSet*)lua_touserdata(L, 1);
	if (data == NULL) return luaL_error(L, "IDataSet is nil");
	const char* key = lua_tostring(L, 2);
	// 2. 调用中焯功能
	int value = data->GetIntByName(key);
	// 3. 出参入栈
	lua_pushinteger(L, value);
	return 1; // 返回1个值
}

static int IDataSet_SetIntByName(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 3) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 3, n);
	// 1. 入参出栈
	IDataSet* data = (IDataSet*)lua_touserdata(L, 1);
	if (data == NULL) return luaL_error(L, "IDataSet is nil");
	const char* key = lua_tostring(L, 2);
	lua_Integer value = lua_tointeger(L, 3);
	// 2. 调用中焯功能
	data->SetIntByName(key, (int)value);
	// 3. 出参入栈
	return 0; // 返回0个值
}

static int IDataSet_GetStrByName(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 2) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 2, n);
	// 1. 入参出栈
	IDataSet* data = (IDataSet*)lua_touserdata(L, 1);
	if (data == NULL) return luaL_error(L, "IDataSet is nil");
	const char* key = lua_tostring(L, 2);
	// 2. 调用中焯功能
	char * value = data->GetStrByName(key);
	// 3. 出参入栈
	lua_pushstring(L, value);
	return 1; // 返回1个值
}

static int IDataSet_SetStrByName(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 3) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 3, n);
	// 1. 入参出栈
	IDataSet* data = (IDataSet*)lua_touserdata(L, 1);
	if (data == NULL) return luaL_error(L, "IDataSet is nil");
	const char* key = lua_tostring(L, 2);
	const char* value = lua_tostring(L, 3);
	// 2. 调用中焯功能
	data->SetStrByName(key, value);
	// 3. 出参入栈
	return 0; // 返回0个值
}

static int IExpandInterface_CreateIDataSet(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 1) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 1, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*)lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	// 2. 调用中焯功能
	IDataSet* data = expandInterface->CreateTableStringsBase();
	// 3. 出参入栈
	lua_pushlightuserdata(L, data);
	return 1; // 返回1个值
}

static int IExpandInterface_DeepCopyIDataSet(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 2) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 2, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*) lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	IDataSet* dataFrom = (IDataSet*) lua_touserdata(L, 2);
	// 2. 调用中焯功能
	IDataSet* dataTo = expandInterface->CreateTableStringsBase();
	if (dataFrom != nullptr) dataTo->SetText(dataFrom->GetText());
	// 3. 出参入栈
	lua_pushlightuserdata(L, dataTo);
	return 1; // 返回1个值
}

static int IExpandInterface_FreeIDataSet(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 2) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 2, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*) lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	IDataSet* data = (IDataSet*) lua_touserdata(L, 2);
	// 2. 调用中焯功能
	expandInterface->FreeTableStringsBase(*data);
	// 3. 出参入栈
	return 0; // 返回1个值
}

static int IExpandInterface_CallForwardAction(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 4) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 4, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*)lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	const char* forward = lua_tostring(L, 2); // 路由名称
	IDataSet* req = (IDataSet*)lua_touserdata(L, 3);
	IDataSet* ans = (IDataSet*)lua_touserdata(L, 4);
	// 2. 调用中焯功能
	expandInterface->CallForwardAction((char*)forward, FALSE, *req, *ans);
	// 3. 出参入栈
	return 0; // 返回0个值
}

static int IExpandInterface_CallModuleAction(lua_State *L)
{
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 3) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 3, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*)lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	IDataSet* req = (IDataSet*)lua_touserdata(L, 2);
	IDataSet* ans = (IDataSet*)lua_touserdata(L, 3);
	// 2. 调用中焯功能
	expandInterface->CallModuleAction(*req,*ans);
	// 3. 出参入栈
	return 0; // 返回0个值
}

/* 异步调用中焯功能号，通过指定路由 */
static int IExpandInterface_CallForwardActionAsync(lua_State *L)
{
	extern LPFN_ONANSWERCALLBACK TztCallBackReturnAsIs;
	extern LPFN_ONANSWERCALLBACK TztCallBackNoReturn;
	extern LPFN_ONANSWERCALLBACK TztCallBack;
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 6) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 6, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*)lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	const char* forward = lua_tostring(L, 2); // 路由名称
	lua_Integer actionId = lua_tointeger(L, 3); // 异步调用的功能号
	const char* callback = lua_tostring(L, 4); // 回调函数名
	IDataSet* req = (IDataSet*) lua_touserdata(L, 5);
	IDataSet* ans = (IDataSet*) lua_touserdata(L, 6);
	// 2.1 回调函数加入调用栈
	int originActionId = req->GetIntByName("Action");
	char* handleSerialNo = req->GetStrByName("HandleSerialNo");
	char* newSerialNo = new char[1024];
	sprintf_s(newSerialNo, 1024, "%s%s%d%s%s", handleSerialNo, "|", originActionId, "#", callback); 
	req->SetStrByName("HandleSerialNo", newSerialNo);
	req->SetIntByName("Action", (const int)actionId);
	// 2.2 调用中焯功能
	if (_stricmp(callback, "NoReturn") == 0)
		expandInterface->CallForwardActionCallBack((char*)forward, TztCallBackNoReturn, *req, *ans);
	else if (_stricmp(callback, "ReturnAsIs") == 0)
		expandInterface->CallForwardActionCallBack((char*)forward, TztCallBackReturnAsIs, *req, *ans);
	else
		expandInterface->CallForwardActionCallBack((char*)forward, TztCallBack, *req, *ans);
	// 3. 出参入栈
	return 0; // 返回0个值
}

/* 异步调用中焯功能号，不指定路由 */
static int IExpandInterface_CallModuleActionAsync(lua_State *L)
{
	extern LPFN_ONANSWERCALLBACK TztCallBackReturnAsIs;
	extern LPFN_ONANSWERCALLBACK TztCallBackNoReturn;
	extern LPFN_ONANSWERCALLBACK TztCallBack;
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 5) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 5, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*)lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	lua_Integer actionId = lua_tointeger(L, 2); // 异步调用的功能号
	const char* callback = lua_tostring(L, 3); // 回调函数名
	IDataSet* req = (IDataSet*) lua_touserdata(L, 4);
	IDataSet* ans = (IDataSet*) lua_touserdata(L, 5);
	// 2.1 回调函数加入调用栈
	int originActionId = req->GetIntByName("Action");
	char* handleSerialNo = req->GetStrByName("HandleSerialNo");
	char* newSerialNo = new char[1024];
	sprintf_s(newSerialNo, 1024, "%s%s%d%s%s", handleSerialNo, "|", originActionId, "#", callback); 
	req->SetStrByName("HandleSerialNo", newSerialNo);
	req->SetIntByName("Action", (const int)actionId);
	// 2.2 调用中焯功能
	if (_stricmp(callback, "NoReturn") == 0)
		expandInterface->CallModuleActionCallBack(TztCallBackNoReturn, *req, *ans);
	else if (_stricmp(callback, "ReturnAsIs") == 0)
		expandInterface->CallModuleActionCallBack(TztCallBackReturnAsIs, *req, *ans);
	else
		expandInterface->CallModuleActionCallBack(TztCallBack, *req, *ans);
	// 3. 出参入栈
	return 0; // 返回0个值
}

/* 取得当前发起请求用户的PushCode */
static int IExpandInterface_GetPushCode(lua_State *L)
{
	extern LPFN_GETPUSHCODE TztGetPushCode;
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 1) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 1, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*)lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	// 2. 调用中焯功能
	char* pushCode = new char[100];
	TztGetPushCode(*expandInterface, pushCode, 100);
	// 3. 出参入栈
	lua_pushstring(L, pushCode);
	return 1; // 返回1个值
}

/* 通过PushCode发送返回结果 */
static int IExpandInterface_SendPush(lua_State *L)
{
	extern LPFN_SENDPUSH TztSendPush;
	// n是Lua程序压栈的参数数量
	int n = lua_gettop(L);
	if (n != 3) return luaL_error(L, "expected number of params %d does not equal to actual number %d", 3, n);
	// 1. 入参出栈
	IExpandInterface* expandInterface = (IExpandInterface*)lua_touserdata(L, 1);
	if (expandInterface == NULL) return luaL_error(L, "IExpandInterface is nil");
	const char* pushCode = lua_tostring(L, 2);
	IDataSet* ans = (IDataSet*)lua_touserdata(L, 3);
	// 2. 调用中焯功能
	TztSendPush(pushCode, strlen(pushCode), *ans);
	// 3. 出参入栈
	return 0; // 返回0个值
}
/*
void UTF_8ToUnicode(wchar_t* pOut, const char *pText)
{
	char* uchar = (char *)pOut;
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
}

void UnicodeToUTF_8(char* pOut, wchar_t* pText)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char *)pText;
	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));
}

void UnicodeToGB2312(char* pOut,wchar_t uData)
{
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
}

void Gb2312ToUnicode(wchar_t* pOut, const char *gbBuffer)
{
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
}

void GB2312ToUTF_8(char* pOut, const char *pText, int pLen)
{
	char buf[4] = {0};
	int i = 0 ,j = 0;
	while(i < pLen)
	{
		//如果是英文直接复制就可以
		if( *(pText + i) >= 0)
		{
			pOut[j++] = pText[i++];
		}
		else
		{
			wchar_t pbuffer;
			Gb2312ToUnicode(&pbuffer, pText+i);
			UnicodeToUTF_8(buf,&pbuffer);
			pOut[j] = buf[0];
			pOut[j+1] = buf[1];
			pOut[j+2] = buf[2];
			j += 3;
			i += 2;
		}
	}
	pOut[j] ='\0';	//返回结果
	return;
}

void UTF_8ToGB2312(char* pOut, const char *pText, int pLen)
{
	char Ctemp[4];
	memset(Ctemp,0,4);
	int i =0 ,j = 0;
	while(i < pLen)
	{
		if(pText[i] >= 0)
		{
			pOut[j++] = pText[i++];
		}
		else
		{
			WCHAR Wtemp;
			UTF_8ToUnicode(&Wtemp,pText + i);
			UnicodeToGB2312(Ctemp,Wtemp);
			pOut[j] = Ctemp[0];
			pOut[j + 1] = Ctemp[1];
			i += 3;
			j += 2;
		}
	}
	pOut[j] ='\0';
	return;
}

//utf8 -> gb2312
static int utf8togb2312(lua_State *L) {
	if (!lua_isstring(L,1)) {
		return luaL_error(L, "param 1 is not string.");
	}
	const char *pin = lua_tostring(L, 1);
	int plen = strlen(pin)+1;
	int nLen = plen / 2 + 1;
	char *out = new char[nLen];
	memset(out, 0, nLen);

	UTF_8ToGB2312(out, pin, plen);
	lua_pushstring(L, out);

	return 1;
}

//gb23112 -> utf8
static int gb2312toutf8(lua_State *L)
{
	if (!lua_isstring(L, 1)) {
		return luaL_error(L, "param 1 is not string.");
	}
	const char *pin = lua_tostring(L, 1);
	int plen = strlen(pin)+1;
	int nLen = plen * 3;
	char *out = new char[nLen];
	memset(out, 0, nLen);

	GB2312ToUTF_8(out, pin, plen);
	lua_pushstring(L, out);

	return 1;
}

uint32_t ngx_murmur_hash2(u_char *data, size_t len)
{
	uint32_t h, k;

	h = 0 ^ len;

	while (len >= 4) {
		k = data[0];
		k |= data[1] << 8;
		k |= data[2] << 16;
		k |= data[3] << 24;

		k *= 0x5bd1e995;
		k ^= k >> 24;
		k *= 0x5bd1e995;

		h *= 0x5bd1e995;
		h ^= k;

		data += 4;
		len -= 4;
	}

	switch (len) {
	case 3:
		h ^= data[2] << 16;
	case 2:
		h ^= data[1] << 8;
	case 1:
		h ^= data[0];
		h *= 0x5bd1e995;
	}

	h ^= h >> 13;
	h *= 0x5bd1e995;
	h ^= h >> 15;

	return h;
}

static int mmh(lua_State *L) {
	//带入参数,根据特征随机
	if (lua_gettop(L) == 1) {
		if (!lua_isstring(L, 1))
		{
			return luaL_error(L, "param is not string.");
		}
		const char * seed = lua_tostring(L, 1);
		uint32_t hash = ngx_murmur_hash2((u_char*)seed, strlen(seed));
		lua_pushinteger(L, hash);
	}

	//不带入参数,完全随机
	if (lua_gettop(L) == 0)
	{
		unsigned long long BIG_NUM = 4294967295;
		std::random_device rd;
		std::uniform_int_distribution<unsigned long long> dist(1, BIG_NUM);
		std::mt19937 mt(rd());
		unsigned long long seed = dist(mt);

		char str[12];
		sprintf(str, "%llu", seed);

		uint32_t hash = ngx_murmur_hash2((u_char*)str, strlen(str));
		lua_pushinteger(L, hash);
	}

	return 1;
}*/

int WIN_API luaopen_mLuaWrapper(lua_State *L)
{
	lua_register(L, "IModule_AddModuleAction", IModule_AddModuleAction);
	lua_register(L, "IModule_AddBeforeAction", IModule_AddBeforeAction);
	lua_register(L, "IModule_AddAfterAction", IModule_AddAfterAction);
	lua_register(L, "Lua_LoadLuaFile", Lua_LoadLuaFile);
	lua_register(L, "IDataSet_GetIntByName", IDataSet_GetIntByName);
	lua_register(L, "IDataSet_SetIntByName", IDataSet_SetIntByName);
	lua_register(L, "IDataSet_GetStrByName", IDataSet_GetStrByName);
	lua_register(L, "IDataSet_SetStrByName", IDataSet_SetStrByName);
	lua_register(L, "IExpandInterface_CreateIDataSet", IExpandInterface_CreateIDataSet);
	lua_register(L, "IExpandInterface_DeepCopyIDataSet", IExpandInterface_DeepCopyIDataSet);
	lua_register(L, "IExpandInterface_FreeIDataSet", IExpandInterface_FreeIDataSet);
	lua_register(L, "IExpandInterface_CallForwardAction", IExpandInterface_CallForwardAction);
	lua_register(L, "IExpandInterface_CallModuleAction", IExpandInterface_CallModuleAction);
	lua_register(L, "IExpandInterface_CallForwardActionAsync", IExpandInterface_CallForwardActionAsync);
	lua_register(L, "IExpandInterface_CallModuleActionAsync", IExpandInterface_CallModuleActionAsync);
	lua_register(L, "IExpandInterface_GetPushCode", IExpandInterface_GetPushCode);
	lua_register(L, "IExpandInterface_SendPush", IExpandInterface_SendPush);
	lua_register(L, "mmh", mmh);
	lua_register(L, "utf8togb2312", utf8togb2312);
	lua_register(L, "gb2312toutf8", gb2312toutf8);
	return 0;
}