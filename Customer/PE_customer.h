
#ifndef _CUSTOMER_
#define _CUSTOMER_


/*
 *	版本基本信息
 */
#define	TermModel			"KS8312"				//终端型号
#define	Version				"V2.02.026"				//软件版本 
#define	ReleaseTime			"2019-06-26"			//软件版本日期
#define	CustomerVersion		"swiftpass"	


/*
 *	模块选择
 */
//#define 					HARD_SCAN_EM3086		//EM3086硬件扫码头
#define 					HARD_WIFI				//WIFI模块

#ifdef HARD_WIFI
	#define	NetworkSupport		"WIFI"				//客户版本
#else
	#define	NetworkSupport		"GSM"				//客户版本
#endif

/* 间连、直连选择 */
#define 	CONNECT_MYSELF							//直接连交易平台


/*
 * 	国内外版本选择
 */
//#define DOMESTIC_BANK_VERION 						// 国内银行版
//#define INTERNATIONAL_VERSION						// 国际版本（海外版）

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
 * 	语言宏定义
 */
#undef 		_LANG_ID_						//重新定义语言ID
#ifdef INTERNATIONAL_VERSION
	#define _LANG_ID_		(0)				//0为英文	1为中文
#else
	#define _LANG_ID_		(1)	
#endif


/*
 * 	网络参数、商户参数
 */
typedef struct
{
	/* 网络参数 */
	char	ServerIp[32];
	char	ServerPort[8];
	char	Apn[16];

	/* 商户参数 */
	char	sign_agentno[32+1];		// 代理商号
	char	mch_id[32+1];			// 商户号
	char	mch_key[32+1];			// 密钥
	char	op_shop_id[32+1];		// 门店编号
	char	op_user_id[32+1];		// 操作员
	char	language_flag;			// 语言版本标记, 0中文，1英文
	char	WifiOpen[1+1];
	char 	CustVer[32+1];
	char	password[12+1];
	char	volume;
	char	payMethod[1+1];
	
//	char	FPS_id[32+1];			// 商户号
//	char	FPS_key[32+1];			// 密钥
}TERM_PAR;
extern TERM_PAR    Term_Par;
extern void TermParSetDefault(void);


/*
 * 	交易记录
 */
typedef struct
{
	char		 money[12+1];
	char         date[10+1];
	char         time[8+1];
	char         type[20+1];		// 交易类型,不能超过一行
	char         order[32+1];		// 订单号32字节
	char		 out_refund_no[32+1];
}TradeRecordItem; 					// 整个结构总字节数为4的整数倍
#define TRADE_RECORD_MAX   	40		// TradeRecordItem 总交易记录数


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

