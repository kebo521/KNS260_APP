#ifndef _SWEEP_PAY_
#define _SWEEP_PAY_


//交易提示信息
#define SRT_TRADING						DS("Processing",									"正在交易")
#define STR_REVERSE 					DS("Canceling",										"正在撤销订单")
#define STR_CLOSE_ORDER					DS("Closing",										"正在关闭订单")
#define STR_REVERSE_SUCCEED				DS("Cancelled Successfully",						"撤销订单成功")
#define STR_CLOSE_SUCCEED				DS("Closed Successfully",							"关闭订单成功")
#define STR_CHECKING_ORDER				DS("Checking Order",								"正在查询订单")
#define STR_INPUT_MERCHANT_INFO			DS("Please enter merchant number and key first",	"请先输入商户号和密钥")
#define STR_DETAILS_QUERY_ENTRY			DS("Press [Function] to query details",				"按[功能]键查明细")
#define STR_WECHAT						DS("WeChat Pay",									"微信收款")
#define STR_ALIPAY						DS("Alipay",										"支付宝收款")
#define STR_JDPAY						DS("jdpay",											"京东钱包收款")
#define STR_QQ							DS("qqpay",											"QQ钱包收款")
#define STR_SHIMING						DS("shiming",										"会员卡收款")
#define STR_UNIONPAY					DS("unionpay",										"银联收款")
#define STR_BESTPAY						DS("bestpay",										"翼支付收款")
#define STR_MENU_ALIPAY					DS("Alipay",										"支付宝")
#define STR_MENU_WECHAT					DS("WeChat Pay",									"微信")
#define STR_MENU_UNIONPAY				DS("unionpay",										"银联")
#define STR_MENU_FPS					DS("FPS",											"FPS")

#define STR_ORDER_RERUNDED				DS("Order Refunded",								"订单已退款")
#define STR_ORDER_RERUND_PROCESSING		DS("Order refunding",								"退款处理中")
#define STR_ORDER_RERUND_FAILED			DS("Order refund failed",							"退款失败")
#define STR_CONTACT_WORKER				DS("Please contact with\nthe After-sales\nSevrvice worker",	"请联系售后服务人员")
#define STR_REFUND_STATE_UNKOWNED		DS("Refund status is not confirmed",				"退款状态未确定")
#define STR_DATA_FORMAT_ERR				DS("Received data format error",					"接收数据格式错")
#define STR_RESULT_CODE					DS("Result code",									"返回码")
#define STR_QUERY_TIMEOUTS				DS("Query timeouts",								"查询超时")
#define STR_SIGN_ERR					DS("Sign failed",									"签名错")	
#define STR_RUTURN_CODE					DS("Return",										"返回码")
#define STR_MESSAGE						DS("Message",										"信息")		
							
#define STR_DEVICE_INFORMATION			DS("About",											"设备信息")							
#define STR_VERSION						DS("Version",										"软件版本")
#define STR_PARAM_SETTINGS				DS("Param Settings",								"参数设置")
#define WIFI_FUNTION					DS("WIFI",											"WIFI")
#define WIFI_SWITCH						DS("Wifi On/Off",									"WIFI开关")
#define WIFI_PASSWORD					DS("Wifi Connect", 									"WIFI连接")
#define STR_SET_VOLUME					DS("Set Volume",									"设置音量")
//#define WIFI_SCAN_QRCODE				DS("Scan Wifi QRcode", 								"扫WIFI二维码")

#define STR_SET_PAY_METHOD				DS("PayMethod Select", 								"付款方式选择")
#define	ORDER_REFUND_APPLY				DS("Refund apply",									"订单退款申请")

#define STR_TRADE_MENU					DS("Trade Menu",									"交易菜单")
#define SCAVENGING_RECEIPT				DS("Scan", 											"扫码收款")
#define QRCODE_RECEIPT					DS("Pay",											"二维码收款")
#define	ORDER_REFUND					DS("Refund",										"订单退款")
#define ORDER_QUERY						DS("Enquiry",										"订单查询")
#define ORDER_QUERY_REFUND				DS("Refund Enquiry",								"退款查询")
#define ORDER_FPS_QUERY					DS("FPS Enquiry",									"FPS订单查询")
#define ORDER_RECORD					DS("Tx Record",										"订单记录")
#define STR_MERCHANT_INFO				DS("Merchant Info",									"商户信息")
#define STR_SET_ADMIN_PASSWORD          DS("Reset access code",								"设置许可码")
#define STR_ENTER_ACCESS_CODE    		DS("Please enter access code",						"请输入许可码")
#define STR_ACCESS_CODE_ERR				DS("access code error",								"许可码错误")
	
#define STR_TERM_MODEL					DS("Model",                 						"设备型号")
#define STR_RELEASE_TIME				DS("Release Date",          						"版本日期")
#define STR_TERM_CHANNEL				DS("Channel",               						"渠道商")
#define STR_NETWORK_SUPPORT				DS("Net",                   						"支持网络")
#define STR_TRADE_RESULT_UNKOWN			DS("Unknown trading results, please check transaction status", "交易结果未知,请查询交易状态")
#define STR_USER_CONCELL				DS("User canceled", 								"用户取消")

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
