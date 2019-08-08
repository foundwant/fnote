/*************************************************************
*	Copyright(c) 2012, 杭州中焯信息技术股份有限公司
*	All rights reserved.
*
*	文件名称：	md_interface.h
*	文件标识：
*	摘    要：	业务动态库接口
*
*	当前版本：	1.0
*	作    者：	xuwb
*	创建日期：	2012.05.30
****************************************************************/
#include <stdlib.h>
#include "windows.h"

#ifndef _MD_INTERFACE_H__
#define _MD_INTERFACE_H__

#ifdef _WIN32
	#if !defined( FUNCTION_CALL_MODE )
	#define FUNCTION_CALL_MODE		__stdcall
	#endif
#else
	#define FUNCTION_CALL_MODE
#endif

//功能号类型(ActionNameType)：  Add by 唐建新  2013.02.19
enum
{
	ANT_NoChange   = 0, //0 不变
	ANT_Digital    = 1, //1 数字
	ANT_Alphabet   = 2  //2 英文
};


//协议关键字对应的快速索引值
enum _FastIndex
{
	T8Action = 1, //功能号
	T8YybCode = 2, //营业部代码
	T8account = 3, //账号 通常是资金账号
	T8AccountType = 4, //账号类型
	T8PassWord = 5, //密码
	T8MobileCode = 6, //手机号
	T8CheckKEY = 7, //验证码
	T8token = 8, //时间戳，交易请求使用 //2013协议开始，意义为：由服务器发给客户端，客户端不做更改，原样返回给服务器  Add by 唐建新  2013.03.20
	T8reqno = 9, //请求标识，每个请求都有，递增 //2013协议开始，意义为：由客户端发给服务器，服务器不做更改，原样返回给客户端  Add by 唐建新  2013.03.20
	T8StartPos = 10, //请求记录起始位置
	T8MaxCount = 11, //共请求行数
	T8errorno = 12, //错误号
	T8errormessage = 13, //错误信息
	T8Grid = 14, //2013.5.6 xuwb 以后停止使用
	T8BinData = 15, //2013.5.6 xuwb 以后停止使用
	T8StockIndex = 16, //股票索引
	T8AccountIndex = 17, //帐号索引
	T8StockNumIndex = 18, //股票数量索引
	T8CellIndex = 19, //真实的营业部号
	T8WTAccountType = 20, //委托客户标识类型，按沪A、深A、...这样区分，如：SHACCOUNT
	T8WTAccount = 21, //委托客户标识，在沪A、深A、...中的账号
	T8StockCode = 22, //股票代码
	T8Price = 23, //价格
	T8Volume = 24, //数量
	T8Direction = 25, //方向，如：买、卖
	T8ContactID = 26, //合同号
	T8NewPassword = 27, //新密码
	T8BeginDate = 28, //开始日期，格式YYYYMMDD，如：20121031
	T8EndDate = 29, //结束日期，格式YYYYMMDD，如：20121031
	T8CommBatchEntrustInfo = 30, //批量详细信息
	T8BankIndent = 31, //银行号
	T8BankPassword = 32, //银行密码
	T8FetchPassword = 33, //取款密码
	T8BankDirection = 35, //银行转帐方向
	T8CanCache = 36, //是否缓存
	T8BankVolume = 37, //银行转帐发生额
	T8BankLsh = 38, //银行流水号
	T8Version = 39, //版本号
	T8ContactIndex = 40, //查撤单时合同号所在列索引,图片宽度
	T8DrawIndex = 41, //可撤标志,图片高度
	T8DeviceType = 42, //设备类型
	T8NeedCheck = 43, //需要检查，股票代码是否需要匹配
	T8MobileType = 44, //手机类型
	T8Server = 45, //服务器, 真实服务器地址
	T8From = 46, //客户来源，如手机厂商，合作商等
	T8ComPassword = 47, //通讯密码
	T8PASSWORDTYPE = 48, //密码类型
	T8OnLineMessage = 49, //在线信息
	T8Title = 50, //标题/银行列表
	T8BankMoney = 51, //币种列表
	T8ColorData = 52, //颜色值
	T8AccountList = 53, //股东帐号列表
	T8BodyLineCount = 54, //手机客户端一屏显示数目
	T8stocktype = 55, //股票类型
	//T8ID = 56,
	T8Tabconfirm_flag = 56, //期货账单确认标志 //后面定义的名称是'tabconfirm_flag'，且以前未使用T8ID，所以改成此名称  Changed by 唐建新  2012.10.08
	//T8Time = 57,
	T8Bank_trans_flag = 57, //银行转账允许标志 //后面定义的名称是'bank_trans_flag'，且以前未使用T8Time，所以改成此名称  Changed by 唐建新  2012.10.08
	T8buysell = 58, //买一，卖一
	T8iphoneKey = 59, //iPhone客户端标识
	T8ZLib = 60, //压缩方法，大多客户端会发此字段
	T8Forward = 61, //交易转发
	T8filename = 62, //文件名
	T8HsString = 63,     //特殊字段,其它字符串会拼接在后面
	T8Upto128 = 64, //升域标志位
	T8IMEI = 65, //IMEI
	T8IMSI = 66, //IMSI
	T8Action2 = 67, //功能号第2个字节，即高字节
	T8Cfrom = 68, //表示来源，投资堂的一律用tzt
	T8Tfrom = 69, //客户端包的类型
	T8Hardno = 70, //版本号 //原本未使用，现作为客户端标识，柜台可记录，用于识别是哪个客户端发送的请求  Comment by 唐建新  2013.01.29
	T8Level = 71,        //保存用户的级别 或者权限等
	T8Lead = 72,         //保存大盘领先数据
	T8averprice = 73,    //均价
	T8ChiCangL = 74,     //期货持仓量
	T8Amount = 75,       //用于存放数量等
	T8ServerMr = 76,     //负载均衡服务器地址列表
	T8UpdateSign = 77,   //升级标识
	T8UpdateAddr = 78,   //升级地址
	T8Level2Bin = 79,    //用于存放LEVE2数据
	T8RightSign = 80,    //权限标识
	T8GateWayIp = 81,     //客户端真实的IP地址
	T8GRID0 = 82, //GRID0~GRID5 add by lisq  2012.09.29
	T8GRID1 = 83,
	T8GRID2 = 84,
	T8GRID3 = 85,
	T8GRID4 = 86,
	T8GRID5 = 87,
	T8FromAddress = 88, //Add by lisq  2012.10.08
	T8HandleSerialNo = 89, //Add by lisq  2012.10.08
	T8Identity_type = 90, //身份类别，报价回购390..393功能号首先使用，因已提供给华泰此接口，所以增加此字段，而不是改成其他名称  Add by 唐建新  2012.10.08
	T8AnswerNo = 91, //报价回购可用余额381首先使用，现在补加为标准字段  Add by 唐建新  2012.10.08
	//Logvolume: 用户登入控制量(用户唯一性控制), 该用户在此客户端登录时的计数，登录时返回给客户端，以后客户端所有请求都要加上类似Logvolume=15，
	//用于判断此客户端的登录是否有效。如：现在此用户最大的登录计数为18，允许同时登录2个，则只有Logvolume=17或18的才是有权限用户，
	//小于这2个数的会被踢掉，可暂时作为免费用户使用。
	//客户端每次登录都会从用户中心取最大登录计数+1。
	T8Logvolume = 92, //用户登入控制量(用户唯一性控制)，该用户在此客户端登录时的计数  Add by 唐建新  2012.10.15
	T8MaxLogin = 93, //用户允许同时登录的数量(用户唯一性控制)，登录计数最新的N个用户有权限，之前登录的踢掉  Add by 唐建新  2012.10.19
	T8MessageID = 94, //消息ID，消息系统使用  Add by 唐建新  2012.10.24
	T8Message = 95, //消息内容，消息系统使用  Add by 唐建新  2012.10.24
	T8ZxID = 96, //资讯ID，消息系统使用  Add by 唐建新  2012.10.24
	T8Time = 97, //时间，消息系统首先使用  Add by 唐建新  2012.10.24
	T8VolumeInfo = 98, //MS服务器标识，即硬盘序列号  Add by 唐建新  2012.12.06
	T8NewMarketNo = 99, //新市场号，即NewKind  Add by 唐建新  2013.01.11
	T8socket_id = 100, //客户端Socket指针的十六进制串，消息系统使用  Add by 唐建新  2013.02.06
	T8Grid9 = 101, //原GRID9放在HsString字段中，2013协议尽量不用HsString字段，所以独立成字段  Add by 唐建新  2013.03.27
	T8IntactToServer = 102, //由服务器发给客户端，客户端不做更改，原样返回给服务器，2013协议开始使用  Add by 唐建新  2013.03.20
	T8ConnectType = 103, //连接类型，用于组件与MS交互，交易组件中转发时加上ConnectType=5且不做汉字解码，而MS不再对内容做汉字编码  Add by 唐建新  2013.04.22
	T8ClientInfo = 104, //客户端信息，现在很多柜台要求记录客户端的一些信息，如： 站点信息,手机号码,手机MAC，厂家,手机型号,操作系统类型及版本号,客户端版本号，客户端最近更新日期  Add by 唐建新  2013.10.18
	T8StockProp = 105, //股票属性，现有：港股通标的券、可买、可卖，融资标的，融券标的。此字段不要用作其他用途  Add by 唐建新  2015.03.02
	T8CommMode = 106 //通讯模式：0-同步 1-路由 2-异步  Add by 唐建新  2015.08.03
};

//通信数据接口
struct IDataSet
{
	/* 特性:数组(不区分'\0')
	 * 功能:根据快速索引取数据内容
	 * @param  const _FastIndex [IN]  快速索引
 	 * @param  int&             [OUT] 快速索引对应的数据内容长度
	 * @return char*            返回  快速索引对应的数据内容
 	 */
	virtual char* FUNCTION_CALL_MODE GetRaw( const _FastIndex nIndex, int& RawLen ) = 0;

	/* 特性:数组(不区分'\0')
	 * 功能:对指定快速索引设置数据内容
	 * @param  const _FastIndex [IN] 快速索引
	 * @param  const char*      [IN] 设进去的数据内容
 	 * @param  const int        [IN] 设进去的数据内容长度
 	 */
	virtual void  FUNCTION_CALL_MODE SetRaw( const _FastIndex nIndex, const char* lpIn, const int RawLen) = 0;


	/* 特性:字符串(区分'\0')
	 * 功能:根据快速索引取数据内容
	 * @param  const _FastIndex [IN] 快速索引
	 * @return char*            返回 快速索引对应的数据内容
 	 */
	virtual char* FUNCTION_CALL_MODE GetStr( const _FastIndex nIndex) = 0;

	/* 特性:字符串(区分'\0')
	 * 功能:对指定快速索引设置数据内容
	 * @param  const _FastIndex [IN] 快速索引
	 * @param  const char*      [IN] 设进去的数据内容
 	 */
	virtual void  FUNCTION_CALL_MODE SetStr( const _FastIndex nIndex, const char* lpIn) = 0;


	/**
	 * 功能:根据快速索引取整数(数据内容)
	 * @param  const _FastIndex [IN] 快速索引
	 * @return int              返回 快速索引对应的整数(数据内容)
 	 */
	virtual int   FUNCTION_CALL_MODE GetInt( const _FastIndex nIndex) = 0;

	/**
	 * 功能:对指定快速索引设置整数(数据内容)
	 * @param  const _FastIndex [IN] 快速索引
	 * @param  const int        [IN] 设进去的整数(数据内容)
 	 */
	virtual void  FUNCTION_CALL_MODE SetInt( const _FastIndex nIndex, const int Value) = 0;


	/* 特性:数组(不区分'\0')
	 * 功能:根据名称取数据内容
	 * @param  const char*      [IN]  名称
 	 * @param  int&             [OUT] 名称对应的数据内容长度
	 * @return char*            返回  名称对应的数据内容
 	 */
	virtual char* FUNCTION_CALL_MODE GetRawByName( const char* lpName, int& RawLen) = 0;

	/* 特性:数组(不区分'\0')
	 * 功能:对指定名称设置数据内容
	 * @param  const char*      [IN] 名称
	 * @param  const char*      [IN] 设进去的数据内容
 	 * @param  const int        [IN] 设进去的数据内容长度
 	 */
	virtual void  FUNCTION_CALL_MODE SetRawByName( const char* lpName, const char* lpIn, const int RawLen ) = 0;


	/* 特性:字符串(区分'\0')
	 * 功能:根据名称取数据内容
	 * @param  const char*      [IN]  名称
	 * @return char*            返回  名称对应的数据内容
 	 */
	virtual char* FUNCTION_CALL_MODE GetStrByName( const char* lpName) = 0;

	/* 特性:字符串(区分'\0')
	 * 功能:对指定名称设置数据内容
	 * @param  const char*      [IN] 名称
	 * @param  const char*      [IN] 设进去的数据内容
 	 */
	virtual void  FUNCTION_CALL_MODE SetStrByName( const char* lpName, const char* lpIn) = 0;


	/**
	 * 功能:根据名称取整数(数据内容)
	 * @param  const char*      [IN]  名称
	 * @return int              返回  名称对应的整数(数据内容)
 	 */
	virtual int   FUNCTION_CALL_MODE GetIntByName( const char* lpName) = 0;

	/**
	 * 功能:对指定名称设置整数(数据内容)
	 * @param  const char*      [IN] 名称
	 * @param  const int        [IN] 设进去的整数(数据内容)
 	 */
	virtual void  FUNCTION_CALL_MODE SetIntByName( const char* lpName, const int Value) = 0;


	/* 特性:字符串(区分'\0')
	 * 功能:取完整的通信文本内容 --通信收到的全部内容
	 * @return char*            返回  名称对应的数据内容
 	 */
	virtual char* FUNCTION_CALL_MODE GetText() = 0;

	/* 特性:字符串(区分'\0')
	 * 功能:设置整个发送的文本内容 --要发送的全部内容
	 * @param  const char*      [IN] 设进去的文本内容
 	 */
	virtual void  FUNCTION_CALL_MODE SetText( const char* lpText ) = 0;

	/**
	 * 功能:将所有字段名称和内容转成大字符串，并转换功能号为指定类型
	 * @param  int              [IN]  功能号类型
	 * @return BOOL             返回  
	*/
	virtual BOOL FUNCTION_CALL_MODE GetTextIncGrid( int ActionNameType ) = 0;

	/**
	* 功能:设置整串文本(文本中间不能含#0)，各GRID也会设置到相应字段
	* @param  const char*      [IN] 设进去的文本内容
	* @param  int              [IN]  功能号类型
	* @return BOOL             返回  
	*/
	virtual BOOL FUNCTION_CALL_MODE SetTextIncGrid( const char* lpText, int ActionNameType ) = 0;
	
	/**
	* 功能:获取字段名
	* @param  const _FastIndex [IN] 快速索引
	* @return char*            返回 索引对应的字段名
	*/
	virtual char* FUNCTION_CALL_MODE GetFieldName( const _FastIndex nIndex ) = 0;
	
	/**
	* 功能:设置字段名
	* @param  const _FastIndex [IN] 快速索引
	* @param  char*            [IN] 字段名
	*/
	virtual void FUNCTION_CALL_MODE SetFieldName( const _FastIndex nIndex, char* lpFieldName ) = 0;
	
	/**
	* 功能:获取标准字段数量
	* @return int              返回 标准字段数量
	*/
	virtual int FUNCTION_CALL_MODE GetStandardFieldCount() = 0;
	
	/**
	* 功能:获取字段数量, 包括非标准字段
	* @return int              返回 字段数量
	*/
	virtual int FUNCTION_CALL_MODE GetFieldCount() = 0;
	
	virtual void FUNCTION_CALL_MODE SetBuffer( const char* lpRc4Buff, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetPBuffer( int& nLen ) = 0;

	virtual void FUNCTION_CALL_MODE SetPackBuffer( const char* lpPackBuf, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetPackPBuffer( int& nLen ) = 0;

	//获取和设置Cookie数据，代替直接操作IntactToServer(直接操作会互相冲突) Add by lisq  2015.11.05
	virtual char* FUNCTION_CALL_MODE GetCookie( const char* lpCookieName ) = 0;

	virtual void FUNCTION_CALL_MODE SetCookie( const char* lpCookieName, const char* lpValue ) = 0;

	//把对象里的数据变成流，方便导入和导出操作
	virtual void FUNCTION_CALL_MODE SetNameValueBuffer( const char* lpBuf, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetNameValuePBuffer( int& nLen ) = 0;

	virtual void FUNCTION_CALL_MODE SetNameValueBufferUtf8( const char* lpBuffer, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetNameValuePBufferUtf8( int& nLen ) = 0;
};


//扩展接口
struct IExpandInterface
{
	/**
	 * 功能:取工作线程标识
	 * @return int              返回  线程号
 	 */
	virtual int   FUNCTION_CALL_MODE ThreadTag() = 0;

	/* 特性:字符串(区分'\0')
	 * 功能:向数据库中间件发文本请求(文本中间不能含'\0')
	 * @param  const char*      [IN]  请求串
	 * @return char*            返回  应答内容
 	 */
	//virtual char* FUNCTION_CALL_MODE RequestUm( const char* lpText ) = 0;

	/* 特性:字符串(区分'\0')
	 * 功能:向事务处理机(交易接口)发文本请求(文本中间不能含'\0')
	 * @param  const char*      [IN]  请求串
	 * @return char*            返回  应答内容
 	 */
	//virtual char* FUNCTION_CALL_MODE RequestJY( const char* lpText ) = 0;

	/**
	* 功能:异步调用组件功能
	* @param  void*             [IN]  异步回调函数
	* @param  IDataSet          [IN]  请求IDataSet对象
	* @param  IDataSet          [IN]  应答IDataSet对象
	* @return BOOL              返回  转发是否成功
	*/
	virtual BOOL FUNCTION_CALL_MODE CallModuleActionCallBack(void* OnAnswerCallBack, IDataSet& IReq, IDataSet& IAns) = 0;

	/**
	* 功能:异步调用路由功能
	* @param  pszForwardName    [IN]  路由名称
	* @param  void*             [IN]  异步回调函数
	* @param  IDataSet          [IN]  请求IDataSet对象
	* @param  IDataSet          [IN]  应答IDataSet对象
	* @return BOOL              返回  转发是否成功
	*/
	virtual BOOL FUNCTION_CALL_MODE CallForwardActionCallBack(char* pszForwardName, void* OnAnswerCallBack, IDataSet& IReq, IDataSet& IAns) = 0;

	/**
	 * 功能:根据错误号取错误信息
	 * @param  const int        [IN]  错误号
	 * @return char*            返回  错误号对应的数据内容
 	 */
	virtual char* FUNCTION_CALL_MODE GetErrorMsg( const int ErrorNO ) = 0;

	/**
	* 功能:取真实营业部号
	* @param  const char        [IN]  营业部号
	* @return char*             返回  真实营业部号数据内容
	*/
	//virtual char* FUNCTION_CALL_MODE GetYybRealCellIndex(const char* lpText) = 0;

	/**
	* 取协议类型
	* @return int               返回  协议类型
	*/
	virtual int FUNCTION_CALL_MODE GetCVTType() = 0;

	/**
	* 功能:创建IDataSet对象
	* @return IDataSet          返回  IDataSet对象
	*/
	virtual IDataSet* FUNCTION_CALL_MODE CreateTableStringsBase() = 0;
	/**
	* 功能:析放IDataSet对象
	* @return IDataSet          返回  IDataSet对象
	*/
	virtual void FUNCTION_CALL_MODE FreeTableStringsBase(IDataSet& IReq) = 0; 

	/**
	* 功能:交易检查是否登录
	* @param  IDataSet          [IN]  IDataSet对象
	*/
	//virtual int FUNCTION_CALL_MODE CheckJyToken(IDataSet& IReq)=0;

	/**
	* 功能:使用指定路由转发功能
	* @param  pszForwardName    [IN]  路由名称
	* @param  bAsync            [IN]  是否异步请求
	* @param  IDataSet          [IN]  请求IDataSet对象
	* @param  IDataSet          [IN]  应答IDataSet对象
	* @return BOOL              返回  转发是否成功
	*/
	virtual BOOL FUNCTION_CALL_MODE CallForwardAction(char* pszForwardName, BOOL bAsync, IDataSet& ReqTSB, IDataSet& AnsTSB) = 0;

	/**
	* 功能:调用其它功能
	* @param  IDataSet          [IN]  IDataSet对象
	* @return BOOL             返回  
	*/
	virtual BOOL FUNCTION_CALL_MODE CallModuleAction(IDataSet& IReq, IDataSet& IAns ) = 0;

	/**
	* 功能:向上级中间件发文本请求
	* @param  IDataSet          [IN]  IDataSet对象
	* @return BOOL             返回  
	*/
	virtual void FUNCTION_CALL_MODE RequestUmTSB(IDataSet& IReq, IDataSet& IAns ) = 0;

};

typedef void* (FUNCTION_CALL_MODE *LPFN_GETPROCADDRESS)(const char* lpProcName);

//外部框架提供的信息结构
struct TZT_CommonInfo
{
	int   ThreadCound;   //工作线程总数
	char  CurrPath[256]; //程序所在路径
	void* lpClientInfo;  //用户信息表的指针，初始化时从MsJy.dll返回给MS  Add by 唐建新  2013.03.29
	void* lpfnSendAnswerToClient; //指向发数据包给客户端的函数：function SendAnswerToClient
	LPFN_GETPROCADDRESS lpGetProcAddress; //扩展函数导出接口
	int   MaxUserNums;   //系统允许的最大连接数
	int   VersionI;      //外壳程序的版本号（可用于兼容性检查）
};


typedef BOOL (FUNCTION_CALL_MODE *LPFN_MODULEPTR)( IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp );


//与外部框架程序交互接口
struct IModuleInterface
{
	/* step 1
	 * 功能:查询主程序相关信息
	 * @return TZT_CommonInfo*  返回  外部框架提供的信息
 	 */
	virtual TZT_CommonInfo* FUNCTION_CALL_MODE GetTZT_CommonInfo() = 0;

	/* step 2
	 * 功能:设置本组件属性
	 * @param  int              [IN]  组件类型(目前都用0)
	 * @param  char*            [IN]  组件名称 -显示于外部框架上本dll的名称(别名)
 	 */
	virtual void  FUNCTION_CALL_MODE SetModuleProperty(int iModuleType, char* sModuleNickName) = 0;

	/* step 3
	 * 功能:给外部框架添加本dll组件功能列表
	 * @param  int              [IN]  功能号   -功能函数的整数别名
	 * @param  char*            [IN]  功能名称 -功能函数的字符别名
	 * @param  char*            [IN]  版本号
	 * @param  LPFN_MODULEPTR   [IN]  功能函数
 	 */
	virtual void  FUNCTION_CALL_MODE AddModuleAction(int action, char* name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;
	
	/* step 4
	 * 功能:增加路由之后应答处理组件
	 * @param  int              [IN]  功能号   -功能函数的整数别名
	 * @param  char*            [IN]  功能名称 -功能函数的字符别名
	 * @param  char*            [IN]  版本号
	 * @param  LPFN_MODULEPTR   [IN]  功能函数
 	 */
	virtual void  FUNCTION_CALL_MODE AddAnswerAction(int action, char* Name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;

	/* step 5
	 * 功能:增加路由之前请求处理组件
	 * @param  int              [IN]  功能号   -功能函数的整数别名
	 * @param  char*            [IN]  功能名称 -功能函数的字符别名
	 * @param  char*            [IN]  版本号
	 * @param  LPFN_MODULEPTR   [IN]  功能函数
 	 */
	virtual void  FUNCTION_CALL_MODE AddRequestAction(int action, char* Name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;

	/* step 6
	 * 功能:增加普通组件之前请求处理组件
	 * @param  int              [IN]  功能号   -功能函数的整数别名
	 * @param  char*            [IN]  功能名称 -功能函数的字符别名
	 * @param  char*            [IN]  版本号
	 * @param  LPFN_MODULEPTR   [IN]  功能函数
 	 */
	virtual void  FUNCTION_CALL_MODE AddBeforeAction(int action, char* Name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;

	/* step 7
	 * 功能:增加普通组件之后应答处理组件
	 * @param  int              [IN]  功能号   -功能函数的整数别名
	 * @param  char*            [IN]  功能名称 -功能函数的字符别名
	 * @param  char*            [IN]  版本号
	 * @param  LPFN_MODULEPTR   [IN]  功能函数
 	 */
	virtual void  FUNCTION_CALL_MODE AddAfterAction(int action, char* Name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;
};

#pragma pack(1)
struct TAnsObject
{
	int   AnsType;
	void* OnAnsProcess;
};
#pragma pack()

//一般AnsObject指向的结构是被扩充过的
typedef void (FUNCTION_CALL_MODE *LPFN_ONANSPROCESS)(TAnsObject* lpAnsObj, IExpandInterface& IExp);

//异步路由得到应答后的回调函数 返回值:false表示继续往后执行，true表示中止
typedef BOOL (FUNCTION_CALL_MODE *LPFN_ONANSWERCALLBACK)(IDataSet& IAns, IExpandInterface& IExp);



//动态库对外暴露的接口
extern "C"
{
	//组件初始化函数(需DLL导出DoModuleInit),返回true表示初始化成功，否则初始化失败
	BOOL FUNCTION_CALL_MODE DoModuleInit(IModuleInterface & IModule);
	//组件结束清理函数(需DLL导出DoModuleFree),返回true表示初成功，否则失败
	BOOL FUNCTION_CALL_MODE DoModuleFree();
}

typedef bool  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_SENDANSWERTEXT)(void* pUserSocket, const char* pszAns, const int iLen, const int iCVTType);
typedef bool  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_SENDANSWERTSB)(void* pUserSocket, IDataSet& IAns, const int iCVTType);
typedef bool  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_CHECKUSERTAG)(void *pUserSocket, long iUserTag);
typedef long  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_GETUSERTAG)(void* pUserSocket);
typedef int   (FUNCTION_CALL_MODE *LPFN_USERSOCKET_GETUSERPOSI)(void* pUserSocket);
typedef int   (FUNCTION_CALL_MODE *LPFN_USERSOCKET_GETCVTTYPE)(void* pUserSocket);
typedef void  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_BEGINDATAPROCESS)(void* pUserSocket);
typedef void  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_ENDDATAPROCESS)(void* pUserSocket);
typedef void  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_SETACTIONNAME)(void* pUserSocket, char* pszActionName);
typedef void  (FUNCTION_CALL_MODE *LPFN_USERSOCKET_SETLASTACCESSTIMECOUNT)(void* pUserSocket, int iLastAccessTimeCount);
typedef void  (FUNCTION_CALL_MODE *LPFN_ADDTOWORKLIST)(TAnsObject* pAnsObject);
typedef void* (FUNCTION_CALL_MODE *LPFN_GETUSERSOCKET)(IExpandInterface& IExp);
typedef char* (FUNCTION_CALL_MODE *LPFN_USERSOCKET_GETFROMADDRESS)(void* pVoid);
typedef int   (FUNCTION_CALL_MODE *LPFN_GETPUSHCODE)(IExpandInterface& IExp, const char* pszPushCode, const int iLen);
typedef bool  (FUNCTION_CALL_MODE *LPFN_SENDPUSH)(const char* pszPushCode, const int iLen, IDataSet& IReq);

#endif