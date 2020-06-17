#ifndef _CUSTOMER_
#define _CUSTOMER_



#define 	CONNECT_MYSELF							//ֱ��������ƽ̨
#define  	HTTP_TRADE_ADDERR   			"https://pos.weixincore.com"	//https://pos.weixincore.com/merchant/User/login
#define 	HTTP_TRADE_PORT					443	

#define		DEVELOPER_ID					"100001"		//developerId
#define		TM_SIGNKEY						"ac6d97e67b444b7a43edfc9182634786"		//signKey

#define	TermModel			"KNS260"			//�ն��ͺ�
#define	Version				"V2.01.004"			//����汾 
//============�й�����
#define	CustomerVersion		"̫��-WIFI"			//�ͻ��汾

#define	VersionDate			"2020-06-08"		//����汾����


typedef struct
{
	/* ������� */
	char	CustVer[32+1];//
	char    ServerIp[64];
	char    ServerPort[16];
	//==============
	char	developerId[16+1];	//ϵͳ����������ߵ�Ψһid
	char	terminalType[1+1];	//�ն����� 1���ŵ꣬��ʱshopId�ش� ,2���նˣ���ʱsn�űش�
	char	merchantId[12+1];			//Ʒ��id 
	char	merchantSecretKey[32+1];	//Ʒ����Կ 
	char	sn[32];				//�ն�SN��
	char	shopId[12+1];		//�ŵ�Id
	u8		userNum,userIndex;	//Ա������,��ǰԱ��
	char	userCode[8][12+1];	//�ŵ�Ա���˺�Id  
}TERM_PAR;
extern TERM_PAR    Term_Par;

//=================���׼�¼����  Termfile�ļ�����Ҫ�ͻ�����==========================
typedef struct
{
	char		 money[9+1];
	char         date[10+1];
	char         time[8+1];
	char         type[20+1];// ��������,���ܳ���һ��
	char         order[32+1];// ������32�ֽ�
}TradeRecordItem; //�����ṹ���ֽ���Ϊ4��������
#define TRADE_RECORD_MAX   	8		// TradeRecordItem �ܽ��׼�¼��


extern void TermParSetDefault(void);
extern void MachDatainit(void);
extern void customer_main(unsigned long argc,void* lpThreadParameter);
extern int WifiInfoMenu(char* title);
extern int customer_MainMenu(char* title);
extern int APP_TradeMainMenu(char* title);


#include "PE_SweepPay.h"
#include "PE_sdk.h"



#endif


