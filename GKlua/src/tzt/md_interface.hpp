/*************************************************************
*	Copyright(c) 2012, ����������Ϣ�����ɷ����޹�˾
*	All rights reserved.
*
*	�ļ����ƣ�	md_interface.h
*	�ļ���ʶ��
*	ժ    Ҫ��	ҵ��̬��ӿ�
*
*	��ǰ�汾��	1.0
*	��    �ߣ�	xuwb
*	�������ڣ�	2012.05.30
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

//���ܺ�����(ActionNameType)��  Add by �ƽ���  2013.02.19
enum
{
	ANT_NoChange   = 0, //0 ����
	ANT_Digital    = 1, //1 ����
	ANT_Alphabet   = 2  //2 Ӣ��
};


//Э��ؼ��ֶ�Ӧ�Ŀ�������ֵ
enum _FastIndex
{
	T8Action = 1, //���ܺ�
	T8YybCode = 2, //Ӫҵ������
	T8account = 3, //�˺� ͨ�����ʽ��˺�
	T8AccountType = 4, //�˺�����
	T8PassWord = 5, //����
	T8MobileCode = 6, //�ֻ���
	T8CheckKEY = 7, //��֤��
	T8token = 8, //ʱ�������������ʹ�� //2013Э�鿪ʼ������Ϊ���ɷ����������ͻ��ˣ��ͻ��˲������ģ�ԭ�����ظ�������  Add by �ƽ���  2013.03.20
	T8reqno = 9, //�����ʶ��ÿ�������У����� //2013Э�鿪ʼ������Ϊ���ɿͻ��˷������������������������ģ�ԭ�����ظ��ͻ���  Add by �ƽ���  2013.03.20
	T8StartPos = 10, //�����¼��ʼλ��
	T8MaxCount = 11, //����������
	T8errorno = 12, //�����
	T8errormessage = 13, //������Ϣ
	T8Grid = 14, //2013.5.6 xuwb �Ժ�ֹͣʹ��
	T8BinData = 15, //2013.5.6 xuwb �Ժ�ֹͣʹ��
	T8StockIndex = 16, //��Ʊ����
	T8AccountIndex = 17, //�ʺ�����
	T8StockNumIndex = 18, //��Ʊ��������
	T8CellIndex = 19, //��ʵ��Ӫҵ����
	T8WTAccountType = 20, //ί�пͻ���ʶ���ͣ�����A����A��...�������֣��磺SHACCOUNT
	T8WTAccount = 21, //ί�пͻ���ʶ���ڻ�A����A��...�е��˺�
	T8StockCode = 22, //��Ʊ����
	T8Price = 23, //�۸�
	T8Volume = 24, //����
	T8Direction = 25, //�����磺����
	T8ContactID = 26, //��ͬ��
	T8NewPassword = 27, //������
	T8BeginDate = 28, //��ʼ���ڣ���ʽYYYYMMDD���磺20121031
	T8EndDate = 29, //�������ڣ���ʽYYYYMMDD���磺20121031
	T8CommBatchEntrustInfo = 30, //������ϸ��Ϣ
	T8BankIndent = 31, //���к�
	T8BankPassword = 32, //��������
	T8FetchPassword = 33, //ȡ������
	T8BankDirection = 35, //����ת�ʷ���
	T8CanCache = 36, //�Ƿ񻺴�
	T8BankVolume = 37, //����ת�ʷ�����
	T8BankLsh = 38, //������ˮ��
	T8Version = 39, //�汾��
	T8ContactIndex = 40, //�鳷��ʱ��ͬ������������,ͼƬ���
	T8DrawIndex = 41, //�ɳ���־,ͼƬ�߶�
	T8DeviceType = 42, //�豸����
	T8NeedCheck = 43, //��Ҫ��飬��Ʊ�����Ƿ���Ҫƥ��
	T8MobileType = 44, //�ֻ�����
	T8Server = 45, //������, ��ʵ��������ַ
	T8From = 46, //�ͻ���Դ�����ֻ����̣������̵�
	T8ComPassword = 47, //ͨѶ����
	T8PASSWORDTYPE = 48, //��������
	T8OnLineMessage = 49, //������Ϣ
	T8Title = 50, //����/�����б�
	T8BankMoney = 51, //�����б�
	T8ColorData = 52, //��ɫֵ
	T8AccountList = 53, //�ɶ��ʺ��б�
	T8BodyLineCount = 54, //�ֻ��ͻ���һ����ʾ��Ŀ
	T8stocktype = 55, //��Ʊ����
	//T8ID = 56,
	T8Tabconfirm_flag = 56, //�ڻ��˵�ȷ�ϱ�־ //���涨���������'tabconfirm_flag'������ǰδʹ��T8ID�����Ըĳɴ�����  Changed by �ƽ���  2012.10.08
	//T8Time = 57,
	T8Bank_trans_flag = 57, //����ת�������־ //���涨���������'bank_trans_flag'������ǰδʹ��T8Time�����Ըĳɴ�����  Changed by �ƽ���  2012.10.08
	T8buysell = 58, //��һ����һ
	T8iphoneKey = 59, //iPhone�ͻ��˱�ʶ
	T8ZLib = 60, //ѹ�����������ͻ��˻ᷢ���ֶ�
	T8Forward = 61, //����ת��
	T8filename = 62, //�ļ���
	T8HsString = 63,     //�����ֶ�,�����ַ�����ƴ���ں���
	T8Upto128 = 64, //�����־λ
	T8IMEI = 65, //IMEI
	T8IMSI = 66, //IMSI
	T8Action2 = 67, //���ܺŵ�2���ֽڣ������ֽ�
	T8Cfrom = 68, //��ʾ��Դ��Ͷ���õ�һ����tzt
	T8Tfrom = 69, //�ͻ��˰�������
	T8Hardno = 70, //�汾�� //ԭ��δʹ�ã�����Ϊ�ͻ��˱�ʶ����̨�ɼ�¼������ʶ�����ĸ��ͻ��˷��͵�����  Comment by �ƽ���  2013.01.29
	T8Level = 71,        //�����û��ļ��� ����Ȩ�޵�
	T8Lead = 72,         //���������������
	T8averprice = 73,    //����
	T8ChiCangL = 74,     //�ڻ��ֲ���
	T8Amount = 75,       //���ڴ��������
	T8ServerMr = 76,     //���ؾ����������ַ�б�
	T8UpdateSign = 77,   //������ʶ
	T8UpdateAddr = 78,   //������ַ
	T8Level2Bin = 79,    //���ڴ��LEVE2����
	T8RightSign = 80,    //Ȩ�ޱ�ʶ
	T8GateWayIp = 81,     //�ͻ�����ʵ��IP��ַ
	T8GRID0 = 82, //GRID0~GRID5 add by lisq  2012.09.29
	T8GRID1 = 83,
	T8GRID2 = 84,
	T8GRID3 = 85,
	T8GRID4 = 86,
	T8GRID5 = 87,
	T8FromAddress = 88, //Add by lisq  2012.10.08
	T8HandleSerialNo = 89, //Add by lisq  2012.10.08
	T8Identity_type = 90, //�����𣬱��ۻع�390..393���ܺ�����ʹ�ã������ṩ����̩�˽ӿڣ��������Ӵ��ֶΣ������Ǹĳ���������  Add by �ƽ���  2012.10.08
	T8AnswerNo = 91, //���ۻع��������381����ʹ�ã����ڲ���Ϊ��׼�ֶ�  Add by �ƽ���  2012.10.08
	//Logvolume: �û����������(�û�Ψһ�Կ���), ���û��ڴ˿ͻ��˵�¼ʱ�ļ�������¼ʱ���ظ��ͻ��ˣ��Ժ�ͻ�����������Ҫ��������Logvolume=15��
	//�����жϴ˿ͻ��˵ĵ�¼�Ƿ���Ч���磺���ڴ��û����ĵ�¼����Ϊ18������ͬʱ��¼2������ֻ��Logvolume=17��18�Ĳ�����Ȩ���û���
	//С����2�����Ļᱻ�ߵ�������ʱ��Ϊ����û�ʹ�á�
	//�ͻ���ÿ�ε�¼������û�����ȡ����¼����+1��
	T8Logvolume = 92, //�û����������(�û�Ψһ�Կ���)�����û��ڴ˿ͻ��˵�¼ʱ�ļ���  Add by �ƽ���  2012.10.15
	T8MaxLogin = 93, //�û�����ͬʱ��¼������(�û�Ψһ�Կ���)����¼�������µ�N���û���Ȩ�ޣ�֮ǰ��¼���ߵ�  Add by �ƽ���  2012.10.19
	T8MessageID = 94, //��ϢID����Ϣϵͳʹ��  Add by �ƽ���  2012.10.24
	T8Message = 95, //��Ϣ���ݣ���Ϣϵͳʹ��  Add by �ƽ���  2012.10.24
	T8ZxID = 96, //��ѶID����Ϣϵͳʹ��  Add by �ƽ���  2012.10.24
	T8Time = 97, //ʱ�䣬��Ϣϵͳ����ʹ��  Add by �ƽ���  2012.10.24
	T8VolumeInfo = 98, //MS��������ʶ����Ӳ�����к�  Add by �ƽ���  2012.12.06
	T8NewMarketNo = 99, //���г��ţ���NewKind  Add by �ƽ���  2013.01.11
	T8socket_id = 100, //�ͻ���Socketָ���ʮ�����ƴ�����Ϣϵͳʹ��  Add by �ƽ���  2013.02.06
	T8Grid9 = 101, //ԭGRID9����HsString�ֶ��У�2013Э�龡������HsString�ֶΣ����Զ������ֶ�  Add by �ƽ���  2013.03.27
	T8IntactToServer = 102, //�ɷ����������ͻ��ˣ��ͻ��˲������ģ�ԭ�����ظ���������2013Э�鿪ʼʹ��  Add by �ƽ���  2013.03.20
	T8ConnectType = 103, //�������ͣ����������MS���������������ת��ʱ����ConnectType=5�Ҳ������ֽ��룬��MS���ٶ����������ֱ���  Add by �ƽ���  2013.04.22
	T8ClientInfo = 104, //�ͻ�����Ϣ�����ںܶ��̨Ҫ���¼�ͻ��˵�һЩ��Ϣ���磺 վ����Ϣ,�ֻ�����,�ֻ�MAC������,�ֻ��ͺ�,����ϵͳ���ͼ��汾��,�ͻ��˰汾�ţ��ͻ��������������  Add by �ƽ���  2013.10.18
	T8StockProp = 105, //��Ʊ���ԣ����У��۹�ͨ���ȯ�����򡢿��������ʱ�ģ���ȯ��ġ����ֶβ�Ҫ����������;  Add by �ƽ���  2015.03.02
	T8CommMode = 106 //ͨѶģʽ��0-ͬ�� 1-·�� 2-�첽  Add by �ƽ���  2015.08.03
};

//ͨ�����ݽӿ�
struct IDataSet
{
	/* ����:����(������'\0')
	 * ����:���ݿ�������ȡ��������
	 * @param  const _FastIndex [IN]  ��������
 	 * @param  int&             [OUT] ����������Ӧ���������ݳ���
	 * @return char*            ����  ����������Ӧ����������
 	 */
	virtual char* FUNCTION_CALL_MODE GetRaw( const _FastIndex nIndex, int& RawLen ) = 0;

	/* ����:����(������'\0')
	 * ����:��ָ����������������������
	 * @param  const _FastIndex [IN] ��������
	 * @param  const char*      [IN] ���ȥ����������
 	 * @param  const int        [IN] ���ȥ���������ݳ���
 	 */
	virtual void  FUNCTION_CALL_MODE SetRaw( const _FastIndex nIndex, const char* lpIn, const int RawLen) = 0;


	/* ����:�ַ���(����'\0')
	 * ����:���ݿ�������ȡ��������
	 * @param  const _FastIndex [IN] ��������
	 * @return char*            ���� ����������Ӧ����������
 	 */
	virtual char* FUNCTION_CALL_MODE GetStr( const _FastIndex nIndex) = 0;

	/* ����:�ַ���(����'\0')
	 * ����:��ָ����������������������
	 * @param  const _FastIndex [IN] ��������
	 * @param  const char*      [IN] ���ȥ����������
 	 */
	virtual void  FUNCTION_CALL_MODE SetStr( const _FastIndex nIndex, const char* lpIn) = 0;


	/**
	 * ����:���ݿ�������ȡ����(��������)
	 * @param  const _FastIndex [IN] ��������
	 * @return int              ���� ����������Ӧ������(��������)
 	 */
	virtual int   FUNCTION_CALL_MODE GetInt( const _FastIndex nIndex) = 0;

	/**
	 * ����:��ָ������������������(��������)
	 * @param  const _FastIndex [IN] ��������
	 * @param  const int        [IN] ���ȥ������(��������)
 	 */
	virtual void  FUNCTION_CALL_MODE SetInt( const _FastIndex nIndex, const int Value) = 0;


	/* ����:����(������'\0')
	 * ����:��������ȡ��������
	 * @param  const char*      [IN]  ����
 	 * @param  int&             [OUT] ���ƶ�Ӧ���������ݳ���
	 * @return char*            ����  ���ƶ�Ӧ����������
 	 */
	virtual char* FUNCTION_CALL_MODE GetRawByName( const char* lpName, int& RawLen) = 0;

	/* ����:����(������'\0')
	 * ����:��ָ������������������
	 * @param  const char*      [IN] ����
	 * @param  const char*      [IN] ���ȥ����������
 	 * @param  const int        [IN] ���ȥ���������ݳ���
 	 */
	virtual void  FUNCTION_CALL_MODE SetRawByName( const char* lpName, const char* lpIn, const int RawLen ) = 0;


	/* ����:�ַ���(����'\0')
	 * ����:��������ȡ��������
	 * @param  const char*      [IN]  ����
	 * @return char*            ����  ���ƶ�Ӧ����������
 	 */
	virtual char* FUNCTION_CALL_MODE GetStrByName( const char* lpName) = 0;

	/* ����:�ַ���(����'\0')
	 * ����:��ָ������������������
	 * @param  const char*      [IN] ����
	 * @param  const char*      [IN] ���ȥ����������
 	 */
	virtual void  FUNCTION_CALL_MODE SetStrByName( const char* lpName, const char* lpIn) = 0;


	/**
	 * ����:��������ȡ����(��������)
	 * @param  const char*      [IN]  ����
	 * @return int              ����  ���ƶ�Ӧ������(��������)
 	 */
	virtual int   FUNCTION_CALL_MODE GetIntByName( const char* lpName) = 0;

	/**
	 * ����:��ָ��������������(��������)
	 * @param  const char*      [IN] ����
	 * @param  const int        [IN] ���ȥ������(��������)
 	 */
	virtual void  FUNCTION_CALL_MODE SetIntByName( const char* lpName, const int Value) = 0;


	/* ����:�ַ���(����'\0')
	 * ����:ȡ������ͨ���ı����� --ͨ���յ���ȫ������
	 * @return char*            ����  ���ƶ�Ӧ����������
 	 */
	virtual char* FUNCTION_CALL_MODE GetText() = 0;

	/* ����:�ַ���(����'\0')
	 * ����:�����������͵��ı����� --Ҫ���͵�ȫ������
	 * @param  const char*      [IN] ���ȥ���ı�����
 	 */
	virtual void  FUNCTION_CALL_MODE SetText( const char* lpText ) = 0;

	/**
	 * ����:�������ֶ����ƺ�����ת�ɴ��ַ�������ת�����ܺ�Ϊָ������
	 * @param  int              [IN]  ���ܺ�����
	 * @return BOOL             ����  
	*/
	virtual BOOL FUNCTION_CALL_MODE GetTextIncGrid( int ActionNameType ) = 0;

	/**
	* ����:���������ı�(�ı��м䲻�ܺ�#0)����GRIDҲ�����õ���Ӧ�ֶ�
	* @param  const char*      [IN] ���ȥ���ı�����
	* @param  int              [IN]  ���ܺ�����
	* @return BOOL             ����  
	*/
	virtual BOOL FUNCTION_CALL_MODE SetTextIncGrid( const char* lpText, int ActionNameType ) = 0;
	
	/**
	* ����:��ȡ�ֶ���
	* @param  const _FastIndex [IN] ��������
	* @return char*            ���� ������Ӧ���ֶ���
	*/
	virtual char* FUNCTION_CALL_MODE GetFieldName( const _FastIndex nIndex ) = 0;
	
	/**
	* ����:�����ֶ���
	* @param  const _FastIndex [IN] ��������
	* @param  char*            [IN] �ֶ���
	*/
	virtual void FUNCTION_CALL_MODE SetFieldName( const _FastIndex nIndex, char* lpFieldName ) = 0;
	
	/**
	* ����:��ȡ��׼�ֶ�����
	* @return int              ���� ��׼�ֶ�����
	*/
	virtual int FUNCTION_CALL_MODE GetStandardFieldCount() = 0;
	
	/**
	* ����:��ȡ�ֶ�����, �����Ǳ�׼�ֶ�
	* @return int              ���� �ֶ�����
	*/
	virtual int FUNCTION_CALL_MODE GetFieldCount() = 0;
	
	virtual void FUNCTION_CALL_MODE SetBuffer( const char* lpRc4Buff, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetPBuffer( int& nLen ) = 0;

	virtual void FUNCTION_CALL_MODE SetPackBuffer( const char* lpPackBuf, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetPackPBuffer( int& nLen ) = 0;

	//��ȡ������Cookie���ݣ�����ֱ�Ӳ���IntactToServer(ֱ�Ӳ����ụ���ͻ) Add by lisq  2015.11.05
	virtual char* FUNCTION_CALL_MODE GetCookie( const char* lpCookieName ) = 0;

	virtual void FUNCTION_CALL_MODE SetCookie( const char* lpCookieName, const char* lpValue ) = 0;

	//�Ѷ���������ݱ���������㵼��͵�������
	virtual void FUNCTION_CALL_MODE SetNameValueBuffer( const char* lpBuf, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetNameValuePBuffer( int& nLen ) = 0;

	virtual void FUNCTION_CALL_MODE SetNameValueBufferUtf8( const char* lpBuffer, int BufSize, bool bClearOldData = false ) = 0;

	virtual char* FUNCTION_CALL_MODE GetNameValuePBufferUtf8( int& nLen ) = 0;
};


//��չ�ӿ�
struct IExpandInterface
{
	/**
	 * ����:ȡ�����̱߳�ʶ
	 * @return int              ����  �̺߳�
 	 */
	virtual int   FUNCTION_CALL_MODE ThreadTag() = 0;

	/* ����:�ַ���(����'\0')
	 * ����:�����ݿ��м�����ı�����(�ı��м䲻�ܺ�'\0')
	 * @param  const char*      [IN]  ����
	 * @return char*            ����  Ӧ������
 	 */
	//virtual char* FUNCTION_CALL_MODE RequestUm( const char* lpText ) = 0;

	/* ����:�ַ���(����'\0')
	 * ����:���������(���׽ӿ�)���ı�����(�ı��м䲻�ܺ�'\0')
	 * @param  const char*      [IN]  ����
	 * @return char*            ����  Ӧ������
 	 */
	//virtual char* FUNCTION_CALL_MODE RequestJY( const char* lpText ) = 0;

	/**
	* ����:�첽�����������
	* @param  void*             [IN]  �첽�ص�����
	* @param  IDataSet          [IN]  ����IDataSet����
	* @param  IDataSet          [IN]  Ӧ��IDataSet����
	* @return BOOL              ����  ת���Ƿ�ɹ�
	*/
	virtual BOOL FUNCTION_CALL_MODE CallModuleActionCallBack(void* OnAnswerCallBack, IDataSet& IReq, IDataSet& IAns) = 0;

	/**
	* ����:�첽����·�ɹ���
	* @param  pszForwardName    [IN]  ·������
	* @param  void*             [IN]  �첽�ص�����
	* @param  IDataSet          [IN]  ����IDataSet����
	* @param  IDataSet          [IN]  Ӧ��IDataSet����
	* @return BOOL              ����  ת���Ƿ�ɹ�
	*/
	virtual BOOL FUNCTION_CALL_MODE CallForwardActionCallBack(char* pszForwardName, void* OnAnswerCallBack, IDataSet& IReq, IDataSet& IAns) = 0;

	/**
	 * ����:���ݴ����ȡ������Ϣ
	 * @param  const int        [IN]  �����
	 * @return char*            ����  ����Ŷ�Ӧ����������
 	 */
	virtual char* FUNCTION_CALL_MODE GetErrorMsg( const int ErrorNO ) = 0;

	/**
	* ����:ȡ��ʵӪҵ����
	* @param  const char        [IN]  Ӫҵ����
	* @return char*             ����  ��ʵӪҵ������������
	*/
	//virtual char* FUNCTION_CALL_MODE GetYybRealCellIndex(const char* lpText) = 0;

	/**
	* ȡЭ������
	* @return int               ����  Э������
	*/
	virtual int FUNCTION_CALL_MODE GetCVTType() = 0;

	/**
	* ����:����IDataSet����
	* @return IDataSet          ����  IDataSet����
	*/
	virtual IDataSet* FUNCTION_CALL_MODE CreateTableStringsBase() = 0;
	/**
	* ����:����IDataSet����
	* @return IDataSet          ����  IDataSet����
	*/
	virtual void FUNCTION_CALL_MODE FreeTableStringsBase(IDataSet& IReq) = 0; 

	/**
	* ����:���׼���Ƿ��¼
	* @param  IDataSet          [IN]  IDataSet����
	*/
	//virtual int FUNCTION_CALL_MODE CheckJyToken(IDataSet& IReq)=0;

	/**
	* ����:ʹ��ָ��·��ת������
	* @param  pszForwardName    [IN]  ·������
	* @param  bAsync            [IN]  �Ƿ��첽����
	* @param  IDataSet          [IN]  ����IDataSet����
	* @param  IDataSet          [IN]  Ӧ��IDataSet����
	* @return BOOL              ����  ת���Ƿ�ɹ�
	*/
	virtual BOOL FUNCTION_CALL_MODE CallForwardAction(char* pszForwardName, BOOL bAsync, IDataSet& ReqTSB, IDataSet& AnsTSB) = 0;

	/**
	* ����:������������
	* @param  IDataSet          [IN]  IDataSet����
	* @return BOOL             ����  
	*/
	virtual BOOL FUNCTION_CALL_MODE CallModuleAction(IDataSet& IReq, IDataSet& IAns ) = 0;

	/**
	* ����:���ϼ��м�����ı�����
	* @param  IDataSet          [IN]  IDataSet����
	* @return BOOL             ����  
	*/
	virtual void FUNCTION_CALL_MODE RequestUmTSB(IDataSet& IReq, IDataSet& IAns ) = 0;

};

typedef void* (FUNCTION_CALL_MODE *LPFN_GETPROCADDRESS)(const char* lpProcName);

//�ⲿ����ṩ����Ϣ�ṹ
struct TZT_CommonInfo
{
	int   ThreadCound;   //�����߳�����
	char  CurrPath[256]; //��������·��
	void* lpClientInfo;  //�û���Ϣ���ָ�룬��ʼ��ʱ��MsJy.dll���ظ�MS  Add by �ƽ���  2013.03.29
	void* lpfnSendAnswerToClient; //ָ�����ݰ����ͻ��˵ĺ�����function SendAnswerToClient
	LPFN_GETPROCADDRESS lpGetProcAddress; //��չ���������ӿ�
	int   MaxUserNums;   //ϵͳ��������������
	int   VersionI;      //��ǳ���İ汾�ţ������ڼ����Լ�飩
};


typedef BOOL (FUNCTION_CALL_MODE *LPFN_MODULEPTR)( IDataSet& IReq, IDataSet& IAns, IExpandInterface& IExp );


//���ⲿ��ܳ��򽻻��ӿ�
struct IModuleInterface
{
	/* step 1
	 * ����:��ѯ�����������Ϣ
	 * @return TZT_CommonInfo*  ����  �ⲿ����ṩ����Ϣ
 	 */
	virtual TZT_CommonInfo* FUNCTION_CALL_MODE GetTZT_CommonInfo() = 0;

	/* step 2
	 * ����:���ñ��������
	 * @param  int              [IN]  �������(Ŀǰ����0)
	 * @param  char*            [IN]  ������� -��ʾ���ⲿ����ϱ�dll������(����)
 	 */
	virtual void  FUNCTION_CALL_MODE SetModuleProperty(int iModuleType, char* sModuleNickName) = 0;

	/* step 3
	 * ����:���ⲿ�����ӱ�dll��������б�
	 * @param  int              [IN]  ���ܺ�   -���ܺ�������������
	 * @param  char*            [IN]  �������� -���ܺ������ַ�����
	 * @param  char*            [IN]  �汾��
	 * @param  LPFN_MODULEPTR   [IN]  ���ܺ���
 	 */
	virtual void  FUNCTION_CALL_MODE AddModuleAction(int action, char* name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;
	
	/* step 4
	 * ����:����·��֮��Ӧ�������
	 * @param  int              [IN]  ���ܺ�   -���ܺ�������������
	 * @param  char*            [IN]  �������� -���ܺ������ַ�����
	 * @param  char*            [IN]  �汾��
	 * @param  LPFN_MODULEPTR   [IN]  ���ܺ���
 	 */
	virtual void  FUNCTION_CALL_MODE AddAnswerAction(int action, char* Name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;

	/* step 5
	 * ����:����·��֮ǰ���������
	 * @param  int              [IN]  ���ܺ�   -���ܺ�������������
	 * @param  char*            [IN]  �������� -���ܺ������ַ�����
	 * @param  char*            [IN]  �汾��
	 * @param  LPFN_MODULEPTR   [IN]  ���ܺ���
 	 */
	virtual void  FUNCTION_CALL_MODE AddRequestAction(int action, char* Name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;

	/* step 6
	 * ����:������ͨ���֮ǰ���������
	 * @param  int              [IN]  ���ܺ�   -���ܺ�������������
	 * @param  char*            [IN]  �������� -���ܺ������ַ�����
	 * @param  char*            [IN]  �汾��
	 * @param  LPFN_MODULEPTR   [IN]  ���ܺ���
 	 */
	virtual void  FUNCTION_CALL_MODE AddBeforeAction(int action, char* Name, char* Version, LPFN_MODULEPTR lpModuleAction ) = 0;

	/* step 7
	 * ����:������ͨ���֮��Ӧ�������
	 * @param  int              [IN]  ���ܺ�   -���ܺ�������������
	 * @param  char*            [IN]  �������� -���ܺ������ַ�����
	 * @param  char*            [IN]  �汾��
	 * @param  LPFN_MODULEPTR   [IN]  ���ܺ���
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

//һ��AnsObjectָ��Ľṹ�Ǳ��������
typedef void (FUNCTION_CALL_MODE *LPFN_ONANSPROCESS)(TAnsObject* lpAnsObj, IExpandInterface& IExp);

//�첽·�ɵõ�Ӧ���Ļص����� ����ֵ:false��ʾ��������ִ�У�true��ʾ��ֹ
typedef BOOL (FUNCTION_CALL_MODE *LPFN_ONANSWERCALLBACK)(IDataSet& IAns, IExpandInterface& IExp);



//��̬����Ⱪ¶�Ľӿ�
extern "C"
{
	//�����ʼ������(��DLL����DoModuleInit),����true��ʾ��ʼ���ɹ��������ʼ��ʧ��
	BOOL FUNCTION_CALL_MODE DoModuleInit(IModuleInterface & IModule);
	//�������������(��DLL����DoModuleFree),����true��ʾ���ɹ�������ʧ��
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