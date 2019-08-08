#include "util.hpp"

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
    pOut[j] ='\0';      //返回结果
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
            UTF_8ToUnicode(&Wtemp, pText + i);
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
int utf8togb2312(lua_State *L) {
	if (!lua_isstring(L,1)) {
		return luaL_error(L, "param 1 is not string.");
	}
	const char *pin = lua_tostring(L, 1);
	int plen = strlen(pin)+1;
	int nLen = plen + 1;
	char *out = new char[nLen];
	memset(out, 0, nLen);

	UTF_8ToGB2312(out, pin, plen);
	lua_pushstring(L, out);

	return 1;
}

//gb23112 -> utf8
int gb2312toutf8(lua_State *L)
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
	uint32_t  h, k;

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

int mmh(lua_State *L) {
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
}