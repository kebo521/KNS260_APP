#ifndef _TRADE_PROCESS_
#define _TRADE_PROCESS_

typedef char* (*TRADE_GetData)(char*); 

typedef struct	
{
	char* 			pSendCurr;
	sIdDataTable*	pRecvTable;
	char* 			pMd5Curr;
	char* 			pMsgData;
	u16				pMsgLen;			//DataLen[2];	��Ч���ݳ���
}DfFlow_Link;

extern   DfFlow_Link  pFlow;

#define    PE_RecvTable 		pFlow.pRecvTable
#define    PE_SendBuf			pFlow.pMsgData
#define    PE_pSend 			pFlow.pSendCurr
#define    PE_pMD5				pFlow.pMd5Curr
#define    BufSize				(6*1024)



typedef struct
{
	char mch_id[32+1];						//�̻���
	char mch_key[32+1];						//��Կ
	char serverIP[64+1];					//������IP��ַ	
	char notify_url[200+1];					//֪ͨ��ַ
	char spbill_create_ip[15+1];			//�ն�IP
	char device_info[32+1];					//�豸��
	char store_id[32+1];					//����ID
	char cashier_id[32+1];					//����ԱID
}DefTerminalPar;

// ����
typedef struct
{
	char	pay_type;
	char	start_date[12];
	char	end_date[12];
	char	mch_id[32+1];					// �̻�id
	char	notify_url[200];				// ֪ͨ��ַ
	char	out_trade_no[32];				// �̻�������
	char	total_fee[12];					// �ܽ��
	char	refund_fee[12];					// �˿���
	char	auth_code[256];					// ��Ȩ��
	char	body[50];						// ��Ʒ��Ϣ
	char	spbill_create_ip[16];			// �ն�IP
	char	nonce_str[32+1];				// ����ַ���
	char	device_info[32];				// �豸��
	char	sign[32+1];						// ǩ��
	char	sub_openid[100];				// �û�����ʶ
	char	store_id[32];					// ������ID
	char	cashier_id[32];					// ����Աid
	char	limit_pay[20];					// ָ��֧����ʽ
	char	key[32+1];						// ��Կ

	char	transaction_id[32+1];			// ƽ̨�·��̻�������
	char	out_refund_no[32+1];			// �˿����
	char	getBrandWCPayRequest[32+1]; 
	char	refund_no[32+1];				// ƽ̨�˵���
	char	refund_id[32+1];				// ƽ̨�˿��
	
	char	attach[32+1];					// attach
	char	charset[16+1];					// �ַ���
	char	service[64+1];					// ҵ��
	char	sign_type[16+1];				// ǩ������
	char	version[16+1];					// �汾��
	char	mch_create_ip[16];				// �ն�IP

	char	time_start[14+1];				// ��������ʱ��
	char 	expire_time[14+1];				// ������ʱʱ��
	char	op_shop_id[32+1];				// �ŵ���
	char	op_user_id[32+1];				// ����Ա
	char	goods_tag[32+1];				// ��Ʒ���

	char    term_sn[32+1];					// �ն����к�
	char    merchantId[32+1];				//FPS�����ն˺�
	char	keyFPS[32+1];					//FPS��������Կ
}CoL_Data;
extern CoL_Data   g_ColData;


typedef struct _TrandInfoMsgQueue
{
	struct _TrandInfoMsgQueue *pPrevious;	//����ָ��
	char	msgId[32+1];					//Mid��Ϣ,�ڲ�����
	char	payRef[32+1];					//ƽ̨���ؽ���
	char	orderRef[32+1];					//�̻������ο����
	char	amount[12+2];					//ƽ̨���ؽ��
}TrandInfoMsgQueue;



extern void Send_add_item(char* pID,char* pData);
extern void Send_add_sign(char* pID,char* pData);
extern void Send_add_sha256sign(char* pID);

#define SEND_ADD_ITEM(s) 	Send_add_item(#s,g_ColData.##s) 
#define SEND_ADD_SIGN(s) 	Send_add_sign(#s,g_ColData.##s) 
#define SAVE_DATA_ITEM(s) 	PE_ReadRecvIdPar(#s,g_ColData.##s,sizeof(g_ColData.##s)) 


//=========xml���ݴ��������������========================
extern int PE_CheckRecvData(char* pRecv,int Len);

extern void PE_FreeRecvData(void);
extern char* PE_GetRecvIdPar(char* pPostID);
extern BOOL PE_ReadRecvIdPar(char* pPostID,char *pOutData,int OutSize);
extern int PE_CheckRecvIdPar(char* pPostID,char *pCheck);
extern int FPS_CheckRecvData(char* pRecv,int Len);

extern int PE_LoadRecvData(char *pInRecv);
//====================���ײ�������=======================
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
