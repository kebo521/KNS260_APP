#ifndef _APP_SDK_
#define _APP_SDK_

#define		OPER_OK				0
	
#define	 	OPER_RET			-1
#define	 	OPER_QUIT			-2
#define	 	OPER_TIMEOUT		-3
#define    	OPER_RDMagERR     	-4 		//读卡错
#define    	OPER_CRCERR     	-5 		//校验失败
#define		OPER_ERR			-6		//操作失败
#define 	OPER_SYSTEM_ERROR	-7		//操作失败
#define 	OPER_TRANS_OVER		-8	    //返回数据正确，显示失败msg
#define		OPER_OFFLINE		-11		//下级
#define		OPER_LOW_VOLTAGE	-15		//电压过低
#define		OPER_HARD_Err		-16		//硬件错误
#define		OPER_SEND_ERR		-1000	//发送数据失败
#define		OPER_RECV_ERR		-2000	//发送数据失败


#define		OPER_NO_CHECK		15		//无签名数据
#define		OPER_NoEND 			6		//成功，但未结束	
#define		OPER_NoHEAD  		5		//未找到头部
#define		OPER_HARD			4		//手工输入
#define		OPER_NEW			3		//进入新流程
#define		OPER_PAY			1		//确认支付

#define		SOCKET_UN_APN			-101		//未打开APN
#define		SOCKET_UN_IP			-102		//未连接IP

#define	SIZE_NORMAL		24

		
enum TYPE_TERM_HARD_INFO
{
	TYPE_TERM_HARD_LIFE			=0x01,
	TYPE_TERM_HARD_SN			=0x02,
	TYPE_TERM_HARD_TMK			=0x04,
	TYPE_TERM_HARD_ALL			=0x07,
};

typedef struct 
{
	u32		Way;		//输入法,IME_TYPE(其中之一)
	u32		Limit;		//控制不要输入法切换,IME_TYPE(多选)
	u16		Min,Max;	//最小最大输入范围
	char*	pTitle;		//显示标题
	char*	pFrontText;	//提示信息的指针
	char*	pAfterText;	//最后一行提示信息
	//char*	pVoice;		//播放语音
	int		timeOutMs;	//超时控制
	//u8 FcChar;	//帐号输入时的分隔字符	2006/09/25 zhou  added
	//u8 SanMag;	//扫描磁卡控制2006/11/08 zhou added
	//u8 ScanInput;	//刷卡输入20080629 added
}EDIT_DATA;



extern void APP_GUI_Win(const char* pTitle,const char* pOk,const char* pCancel);

extern int APP_WaitUiEvent(int tTimeOutMS);

extern int APP_InputNum(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinLen,int InputMaxlen);
extern int APP_InputAbc(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinlen,int InputMaxlen);
extern int APP_InputPin(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pkey);
extern int APP_FileSaveBuff(const char* pfilePath,u32 offset,void* pBuff,u32 Inlen);
extern int APP_FileReadBuff(const char* pfilePath,u32 offset,void* pBuff,u32 buffSize);
extern void APP_ShowNoSignel(char *pShowMsg,int tTimeOutMS);
extern void APP_ShowWaitFor(char *pShowMsg);
extern void APP_ShowWaitRef(char *pTradeMoney);
extern void APP_ShowTradeOK(char *pTradeMoney);
extern int APP_ShowTradeFA(char *pShowMsg,int tTimeOutMS);
extern void APP_ShowRefundsOK(char *pTradeMoney);
extern int APP_ShowTradeMsg(char *pShowMsg,int tTimeOutMS);
extern void APP_ShowQRcodeDis(char *pQRcode,char *pTradeMoney);
extern int APP_ShowEnquiriesMsg(char *pTmoney,char* pTradeType,char* pDate,char* pTime,char* pOrderNo);
extern int APP_OnlyCamScan(char flagKey,int MinLen,int MaxLen,char* pOutCode,int msTimeOut);
extern char* APP_GetMasterVer(void);

extern int APP_Edit(EDIT_DATA *pEdit,char* pOutStr);
//=========flagd:D为"二维码收款",R为"订单退款",S为"扫码收款",Q为"交易查询"=========
extern int APP_CamScan(char flagd,char* pHintOrTMoney,char *pOutCode,int MinLen,int MaxLen,int timeOutMs);
extern int APP_EditSum(char* pTitle,char flagd,char* pOutStr,int timeOutMs);

//=========操作员登录(包含ID与密码)=======================================
extern int APP_OperEdit(char* pTitle,char* pOutStr,int Min,int Max,int timeOutMs);
//extern int APP_GUI_SetVolume(char *pTitle);

extern int APP_EDIT_SetDateTime(char* title);
extern int APP_Check_DateTime(char* title);
extern int APP_InputMerchSN(char flagd,char* pOutStr,int MinLen,int Maxlen,int timeOutMs);

/**
 * 获取当前毫秒数,单位:豪秒
 * 
 * @return 系统当前毫秒数
 */	
extern int  API_TimeCurrMS(void);	
extern int OsSetTime(ST_TIME *Time);
extern void OsGetTime(ST_TIME *Time);
extern void OsSleep(unsigned int Ms);

extern void APP_ScreenSleep(u8 En);
extern int APP_GetHardMsg(u8 type,void *pOut,int OutSize);
extern int APP_SetHardMsg(u8 type,void *pOut,int OutSize);

extern void API_SetLanguage(int language);

//=================对语音播放增加参数控制，解决互斥问题=========================

//#define 	APP_TTS_PlayText 	pSdkFun->sdk->TtsPlay
//#define 	APP_AudioDtmfPlay 	pSdkFun->sdk->DtmfPlay

extern int AudioSetVolume(int volume);
extern int AudioGetVolume(void);
extern int APP_TTS_PlayText(const char *format,...);
extern int APP_AudioDtmfPlay(u8 tone,u8 time100Ms);

//AudioSetVolume


#endif
