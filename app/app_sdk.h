#ifndef _APP_SDK_
#define _APP_SDK_

#define		OPER_OK				0
	
#define	 	OPER_RET			-1
#define	 	OPER_QUIT			-2
#define	 	OPER_TIMEOUT		-3
#define    	OPER_RDMagERR     	-4 		//������
#define    	OPER_CRCERR     	-5 		//У��ʧ��
#define		OPER_ERR			-6		//����ʧ��
#define 	OPER_SYSTEM_ERROR	-7		//����ʧ��
#define 	OPER_TRANS_OVER		-8	    //����������ȷ����ʾʧ��msg
#define		OPER_OFFLINE		-11		//�¼�
#define		OPER_LOW_VOLTAGE	-15		//��ѹ����
#define		OPER_HARD_Err		-16		//Ӳ������
#define		OPER_SEND_ERR		-1000	//��������ʧ��
#define		OPER_RECV_ERR		-2000	//��������ʧ��


#define		OPER_NO_CHECK		15		//��ǩ������
#define		OPER_NoEND 			6		//�ɹ�����δ����	
#define		OPER_NoHEAD  		5		//δ�ҵ�ͷ��
#define		OPER_HARD			4		//�ֹ�����
#define		OPER_NEW			3		//����������
#define		OPER_PAY			1		//ȷ��֧��

#define		SOCKET_UN_APN			-101		//δ��APN
#define		SOCKET_UN_IP			-102		//δ����IP

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
	u32		Way;		//���뷨,IME_TYPE(����֮һ)
	u32		Limit;		//���Ʋ�Ҫ���뷨�л�,IME_TYPE(��ѡ)
	u16		Min,Max;	//��С������뷶Χ
	char*	pTitle;		//��ʾ����
	char*	pFrontText;	//��ʾ��Ϣ��ָ��
	char*	pAfterText;	//���һ����ʾ��Ϣ
	//char*	pVoice;		//��������
	int		timeOutMs;	//��ʱ����
	//u8 FcChar;	//�ʺ�����ʱ�ķָ��ַ�	2006/09/25 zhou  added
	//u8 SanMag;	//ɨ��ſ�����2006/11/08 zhou added
	//u8 ScanInput;	//ˢ������20080629 added
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
//=========flagd:DΪ"��ά���տ�",RΪ"�����˿�",SΪ"ɨ���տ�",QΪ"���ײ�ѯ"=========
extern int APP_CamScan(char flagd,char* pHintOrTMoney,char *pOutCode,int MinLen,int MaxLen,int timeOutMs);
extern int APP_EditSum(char* pTitle,char flagd,char* pOutStr,int timeOutMs);

//=========����Ա��¼(����ID������)=======================================
extern int APP_OperEdit(char* pTitle,char* pOutStr,int Min,int Max,int timeOutMs);
//extern int APP_GUI_SetVolume(char *pTitle);

extern int APP_EDIT_SetDateTime(char* title);
extern int APP_Check_DateTime(char* title);
extern int APP_InputMerchSN(char flagd,char* pOutStr,int MinLen,int Maxlen,int timeOutMs);

/**
 * ��ȡ��ǰ������,��λ:����
 * 
 * @return ϵͳ��ǰ������
 */	
extern int  API_TimeCurrMS(void);	
extern int OsSetTime(ST_TIME *Time);
extern void OsGetTime(ST_TIME *Time);
extern void OsSleep(unsigned int Ms);

extern void APP_ScreenSleep(u8 En);
extern int APP_GetHardMsg(u8 type,void *pOut,int OutSize);
extern int APP_SetHardMsg(u8 type,void *pOut,int OutSize);

extern void API_SetLanguage(int language);

//=================�������������Ӳ������ƣ������������=========================

//#define 	APP_TTS_PlayText 	pSdkFun->sdk->TtsPlay
//#define 	APP_AudioDtmfPlay 	pSdkFun->sdk->DtmfPlay

extern int AudioSetVolume(int volume);
extern int AudioGetVolume(void);
extern int APP_TTS_PlayText(const char *format,...);
extern int APP_AudioDtmfPlay(u8 tone,u8 time100Ms);

//AudioSetVolume


#endif
