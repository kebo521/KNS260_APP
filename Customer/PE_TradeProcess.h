#ifndef _TRADE_PROCESS_
#define _TRADE_PROCESS_

typedef char* (*TRADE_GetData)(char*); 

typedef struct	
{
	char* 			pSendCurr;
	sIdDataTable*	pRecvTable;
	char* 			pMd5Curr;
	char* 			pMsgData;
	u16				pMsgLen;			//DataLen[2];	有效数据长度
}DfFlow_Link;

extern   DfFlow_Link  pFlow;

#define    PE_RecvTable 		pFlow.pRecvTable
#define    PE_SendBuf			pFlow.pMsgData
#define    PE_pSend 			pFlow.pSendCurr
#define    PE_pMD5				pFlow.pMd5Curr
#define    BufSize				(6*1024)



typedef struct
{
	char mch_id[32+1];						//商户号
	char mch_key[32+1];						//密钥
	char serverIP[64+1];					//服务器IP地址	
	char notify_url[200+1];					//通知地址
	char spbill_create_ip[15+1];			//终端IP
	char device_info[32+1];					//设备号
	char store_id[32+1];					//店铺ID
	char cashier_id[32+1];					//收银员ID
}DefTerminalPar;

// 数据
typedef struct
{
	char	pay_type;
	char	start_date[12];
	char	end_date[12];
	char	mch_id[32+1];					// 商户id
	char	notify_url[200];				// 通知地址
	char	out_trade_no[32];				// 商户订单号
	char	total_fee[12];					// 总金额
	char	refund_fee[12];					// 退款金额
	char	auth_code[256];					// 授权码
	char	body[50];						// 商品信息
	char	spbill_create_ip[16];			// 终端IP
	char	nonce_str[32+1];				// 随机字符串
	char	device_info[32];				// 设备号
	char	sign[32+1];						// 签名
	char	sub_openid[100];				// 用户名标识
	char	store_id[32];					// 店铺邋ID
	char	cashier_id[32];					// 收银员id
	char	limit_pay[20];					// 指定支付方式
	char	key[32+1];						// 密钥

	char	transaction_id[32+1];			// 平台下方商户订单号
	char	out_refund_no[32+1];			// 退款订单号
	char	getBrandWCPayRequest[32+1]; 
	char	refund_no[32+1];				// 平台退单号
	char	refund_id[32+1];				// 平台退款单号
	
	char	attach[32+1];					// attach
	char	charset[16+1];					// 字符集
	char	service[64+1];					// 业务
	char	sign_type[16+1];				// 签名类型
	char	version[16+1];					// 版本号
	char	mch_create_ip[16];				// 终端IP

	char	time_start[14+1];				// 订单生成时间
	char 	expire_time[14+1];				// 订单超时时间
	char	op_shop_id[32+1];				// 门店编号
	char	op_user_id[32+1];				// 操作员
	char	goods_tag[32+1];				// 商品标记

	char    term_sn[32+1];					// 终端序列号
	char    merchantId[32+1];				//FPS交易终端号
	char	keyFPS[32+1];					//FPS交易密密钥
}CoL_Data;
extern CoL_Data   g_ColData;


typedef struct _TrandInfoMsgQueue
{
	struct _TrandInfoMsgQueue *pPrevious;	//回退指针
	char	msgId[32+1];					//Mid消息,内部产生
	char	payRef[32+1];					//平台返回交易
	char	orderRef[32+1];					//商户订单参考编号
	char	amount[12+2];					//平台返回金额
}TrandInfoMsgQueue;



extern void Send_add_item(char* pID,char* pData);
extern void Send_add_sign(char* pID,char* pData);
extern void Send_add_sha256sign(char* pID);

#define SEND_ADD_ITEM(s) 	Send_add_item(#s,g_ColData.##s) 
#define SEND_ADD_SIGN(s) 	Send_add_sign(#s,g_ColData.##s) 
#define SAVE_DATA_ITEM(s) 	PE_ReadRecvIdPar(#s,g_ColData.##s,sizeof(g_ColData.##s)) 


//=========xml数据处理，处理接收数据========================
extern int PE_CheckRecvData(char* pRecv,int Len);

extern void PE_FreeRecvData(void);
extern char* PE_GetRecvIdPar(char* pPostID);
extern BOOL PE_ReadRecvIdPar(char* pPostID,char *pOutData,int OutSize);
extern int PE_CheckRecvIdPar(char* pPostID,char *pCheck);
extern int FPS_CheckRecvData(char* pRecv,int Len);

extern int PE_LoadRecvData(char *pInRecv);
//====================交易参数交互=======================
extern void DataInit(void);
extern void DataFree(void);

extern void TradeGet_start(const char *pTradeAddress);
extern void TradeGet_End(void);

extern void InitElementValue(void);
extern void GenerateOutTradeNo(void);
extern void GenerateNonceStr(void);
extern void GenerateOutRefundNo(void);
extern TrandInfoMsgQueue *CreateInfoMsgQueueNode(void);
extern void FreeInfoMsgQueueNode(TrandInfoMsgQueue *pNode);
extern void GenerateTimeStart(void);
extern void SetServiceElementValue(char *value);
extern void SetMchCreateIp(void);
extern int InputTotalFee(char *pTitle);
extern int ScanAuthCode(void);

#endif
