#ifndef _SWEEP_PAY_
#define _SWEEP_PAY_


//������ʾ��Ϣ
#define SRT_TRADING						DS("Processing",									"���ڽ���")
#define STR_REVERSE 					DS("Canceling",										"���ڳ�������")
#define STR_CLOSE_ORDER					DS("Closing",										"���ڹرն���")
#define STR_REVERSE_SUCCEED				DS("Cancelled Successfully",						"���������ɹ�")
#define STR_CLOSE_SUCCEED				DS("Closed Successfully",							"�رն����ɹ�")
#define STR_CHECKING_ORDER				DS("Checking Order",								"���ڲ�ѯ����")
#define STR_INPUT_MERCHANT_INFO			DS("Please enter merchant number and key first",	"���������̻��ź���Կ")
#define STR_DETAILS_QUERY_ENTRY			DS("Press [Function] to query details",				"��[����]������ϸ")
#define STR_WECHAT						DS("WeChat Pay",									"΢���տ�")
#define STR_ALIPAY						DS("Alipay",										"֧�����տ�")
#define STR_JDPAY						DS("jdpay",											"����Ǯ���տ�")
#define STR_QQ							DS("qqpay",											"QQǮ���տ�")
#define STR_SHIMING						DS("shiming",										"��Ա���տ�")
#define STR_UNIONPAY					DS("unionpay",										"�����տ�")
#define STR_BESTPAY						DS("bestpay",										"��֧���տ�")
#define STR_MENU_ALIPAY					DS("Alipay",										"֧����")
#define STR_MENU_WECHAT					DS("WeChat Pay",									"΢��")
#define STR_MENU_UNIONPAY				DS("unionpay",										"����")
#define STR_MENU_FPS					DS("FPS",											"FPS")

#define STR_ORDER_RERUNDED				DS("Order Refunded",								"�������˿�")
#define STR_ORDER_RERUND_PROCESSING		DS("Order refunding",								"�˿����")
#define STR_ORDER_RERUND_FAILED			DS("Order refund failed",							"�˿�ʧ��")
#define STR_CONTACT_WORKER				DS("Please contact with\nthe After-sales\nSevrvice worker",	"����ϵ�ۺ������Ա")
#define STR_REFUND_STATE_UNKOWNED		DS("Refund status is not confirmed",				"�˿�״̬δȷ��")
#define STR_DATA_FORMAT_ERR				DS("Received data format error",					"�������ݸ�ʽ��")
#define STR_RESULT_CODE					DS("Result code",									"������")
#define STR_QUERY_TIMEOUTS				DS("Query timeouts",								"��ѯ��ʱ")
#define STR_SIGN_ERR					DS("Sign failed",									"ǩ����")	
#define STR_RUTURN_CODE					DS("Return",										"������")
#define STR_MESSAGE						DS("Message",										"��Ϣ")		
							
#define STR_DEVICE_INFORMATION			DS("About",											"�豸��Ϣ")							
#define STR_VERSION						DS("Version",										"����汾")
#define STR_PARAM_SETTINGS				DS("Param Settings",								"��������")
#define WIFI_FUNTION					DS("WIFI",											"WIFI")
#define WIFI_SWITCH						DS("Wifi On/Off",									"WIFI����")
#define WIFI_PASSWORD					DS("Wifi Connect", 									"WIFI����")
#define STR_SET_VOLUME					DS("Set Volume",									"��������")
//#define WIFI_SCAN_QRCODE				DS("Scan Wifi QRcode", 								"ɨWIFI��ά��")

#define STR_SET_PAY_METHOD				DS("PayMethod Select", 								"���ʽѡ��")
#define	ORDER_REFUND_APPLY				DS("Refund apply",									"�����˿�����")

#define STR_TRADE_MENU					DS("Trade Menu",									"���ײ˵�")
#define SCAVENGING_RECEIPT				DS("Scan", 											"ɨ���տ�")
#define QRCODE_RECEIPT					DS("Pay",											"��ά���տ�")
#define	ORDER_REFUND					DS("Refund",										"�����˿�")
#define ORDER_QUERY						DS("Enquiry",										"������ѯ")
#define ORDER_QUERY_REFUND				DS("Refund Enquiry",								"�˿��ѯ")
#define ORDER_FPS_QUERY					DS("FPS Enquiry",									"FPS������ѯ")
#define ORDER_RECORD					DS("Tx Record",										"������¼")
#define STR_MERCHANT_INFO				DS("Merchant Info",									"�̻���Ϣ")
#define STR_SET_ADMIN_PASSWORD          DS("Reset access code",								"���������")
#define STR_ENTER_ACCESS_CODE    		DS("Please enter access code",						"�����������")
#define STR_ACCESS_CODE_ERR				DS("access code error",								"��������")
	
#define STR_TERM_MODEL					DS("Model",                 						"�豸�ͺ�")
#define STR_RELEASE_TIME				DS("Release Date",          						"�汾����")
#define STR_TERM_CHANNEL				DS("Channel",               						"������")
#define STR_NETWORK_SUPPORT				DS("Net",                   						"֧������")
#define STR_TRADE_RESULT_UNKOWN			DS("Unknown trading results, please check transaction status", "���׽��δ֪,���ѯ����״̬")
#define STR_USER_CONCELL				DS("User canceled", 								"�û�ȡ��")

extern int SubRefundTrade(char* pTitle,char* ptransaction_id,char* pMoney);
extern int SweepFlow(char *pTitle);
extern int QrTypeWX(char*  pTitle);
extern int QrTypeZFB(char*  pTitle);
extern int QrTypeUN(char*  pTitle);
extern char* SubPfsTradeQuery(char* pOrderRef);
extern int QrTypeFPS(char*  pTitle);
extern int PE_InputAccessCode(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pkey);
extern int RefundFlow(char* pTitle);
extern int QueryFlow(char* pTitle);
extern int QueryRefundResult(char* pTitle);

extern int FPS_QueryFlow(char* pTitle);

extern int QrCodePaymentAlipay(char*  pTitle);
extern int QrCodePaymentWechat(char*  pTitle);

extern int CheckParamPreFlow(void);
extern int CheckQueryFlowResult(void);
extern void QueryProcess(int TradeType);

extern int IsNeedCloseOrder(void);
extern int IsTradeSucceed(void);
extern int IsTradeNeedQuerry(void);
extern int IsTradeResultUnkown(void);
extern int IsOrderStateSucceed(void);
extern int IsStatusSucceed(void);
extern int IsNotPay( void );
extern int IsOrderStateRefund(void);

extern int ShowQRCode(void);
extern void ShowQuerryResult( void );
extern void ShowSucceedTrade(void);
extern void ShowOrderInfo(void);
extern int ShowReturnMessage(void);
extern void ShowOrderDetails(void);

enum FLOW_TAG
{
	FLOW_SCAN,
	FLOW_PAY,
	FLOW_QUERY,
	FLOW_REFUND,
	FLOW_CLOSE,
};

enum ORDER_STATE
{
	ORDER_SUCCESS,
	ORDER_ERR,
	ORDER_CLOSED,
	ORDER_REVOKED,
	ORDER_PAYERROR,
	ORDER_NOTPAY,
	ORDER_USERPAYING
};

enum QUERY_STATE
{
	PAY_SUCCESS=0x4F4B, 	//OK	
	PAY_FAILED,
	PAY_QUERY,
	PAY_TIMEOUTS,	
	PAY_NOTSURE,
	PAY_CENTRAL_ERR,
	PAY_PROCESSING,
};

enum TRADE_TYPE
{
	SWEEP_PAY,		
	QR_PAY			
};

#endif 
