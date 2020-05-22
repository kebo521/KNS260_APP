
#ifndef _CUSTOMER_
#define _CUSTOMER_


/*
 *	�汾������Ϣ
 */
#define	TermModel			"KS8312"				//�ն��ͺ�
#define	Version				"V2.02.026"				//����汾 
#define	ReleaseTime			"2019-06-26"			//����汾����
#define	CustomerVersion		"swiftpass"	


/*
 *	ģ��ѡ��
 */
//#define 					HARD_SCAN_EM3086		//EM3086Ӳ��ɨ��ͷ
#define 					HARD_WIFI				//WIFIģ��

#ifdef HARD_WIFI
	#define	NetworkSupport		"WIFI"				//�ͻ��汾
#else
	#define	NetworkSupport		"GSM"				//�ͻ��汾
#endif

/* ������ֱ��ѡ�� */
#define 	CONNECT_MYSELF							//ֱ��������ƽ̨


/*
 * 	������汾ѡ��
 */
//#define DOMESTIC_BANK_VERION 						// �������а�
//#define INTERNATIONAL_VERSION						// ���ʰ汾������棩

#if(defined INTERNATIONAL_VERSION)
	#define 	HTTP_BASE_ADDERR		"https://pay.wepayez.com/pay"	//"https://payintl-test.wepayez.com/pay"	//
#else
	#define 	HTTP_BASE_ADDERR		"https://pay.swiftpass.cn/pay"	
#endif

#define 	HTTP_TRADE_ADDERR			HTTP_BASE_ADDERR"/gateway"	
#define 	HTTP_TRADE_PORT 			443 	  

#define 	HTTP_TRADE_PFS_ADDERR		HTTP_BASE_ADDERR
#define 	HTTP_TRADE_PFS_PORT			443		

/*
 * 	���Ժ궨��
 */
#undef 		_LANG_ID_						//���¶�������ID
#ifdef INTERNATIONAL_VERSION
	#define _LANG_ID_		(0)				//0ΪӢ��	1Ϊ����
#else
	#define _LANG_ID_		(1)	
#endif


/*
 * 	����������̻�����
 */
typedef struct
{
	/* ������� */
	char	ServerIp[32];
	char	ServerPort[8];
	char	Apn[16];

	/* �̻����� */
	char	sign_agentno[32+1];		// �����̺�
	char	mch_id[32+1];			// �̻���
	char	mch_key[32+1];			// ��Կ
	char	op_shop_id[32+1];		// �ŵ���
	char	op_user_id[32+1];		// ����Ա
	char	language_flag;			// ���԰汾���, 0���ģ�1Ӣ��
	char	WifiOpen[1+1];
	char 	CustVer[32+1];
	char	password[12+1];
	char	volume;
	char	payMethod[1+1];
	
//	char	FPS_id[32+1];			// �̻���
//	char	FPS_key[32+1];			// ��Կ
}TERM_PAR;
extern TERM_PAR    Term_Par;
extern void TermParSetDefault(void);


/*
 * 	���׼�¼
 */
typedef struct
{
	char		 money[12+1];
	char         date[10+1];
	char         time[8+1];
	char         type[20+1];		// ��������,���ܳ���һ��
	char         order[32+1];		// ������32�ֽ�
	char		 out_refund_no[32+1];
}TradeRecordItem; 					// �����ṹ���ֽ���Ϊ4��������
#define TRADE_RECORD_MAX   	40		// TradeRecordItem �ܽ��׼�¼��


extern void MachDatainit(void);
extern int APP_TermMenu(char* title);
extern int APP_TradeMainMenu(char* title);
extern int customer_MainMenu(char* title);
extern void customer_main(unsigned long argc,void* lpThreadParameter);
extern void EntranceTrade_KS8613(void);

#include "PE_TradeProcess.h"
#include "PE_SweepPay.h"
#include "PE_TermParSet.h"

#endif

