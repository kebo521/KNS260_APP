#ifndef _PE_UNIONPAY_H_
#define  _PE_UNIONPAY_H_

              
typedef struct	
{
	char* 			pSendCurr;
	char*			pSendLen;	//pSendLen7Addr
	char*           pMd5Start;
	char*           pMd5SCurr;
	char* 			pMsgData;
	u16				pMsgLen;			//DataLen[2];	��Ч���ݳ���
	u16				SendLen;
}DfFlow_Link;

extern   DfFlow_Link  pFlow;

#define    PE_SendBuf			pFlow.pMsgData
#define    PE_pSend 			pFlow.pSendCurr
#define    PE_pMD5 				pFlow.pMd5SCurr
#define    PE_sLenStart 		pFlow.pSendLen
#define    BufSize				2048


typedef struct
{
	char    developerId[16+1];// ������id  
	char	merchantId[12+1];			//Ʒ��id 
	char	merchantSecretKey[32+1];	//Ʒ����Կ 
	char	terminalType[1+1];	// �ն����ͣ�1���ŵ꣬��ʱshopId�ش� 2���նˣ���ʱsn�űش�	
	char	sn[32];			// �ն�sn��  
	char	shopId[12+1];		//�ŵ�Id
	char	userCode[12+1];		// �ŵ�Ա���˺�Id  
	char	payAmount[12+1];	//֧������λ�� 
	char	refundFee[12+1];	//�˿����λ�֣�����Ĭ��Ϊȫ���˿� 
	char	payType[12+1];		//֧����ʽ�����������ϵͳ��ͨ��authCode��ȡ��Ӧ��֧����ʽ wx_pay��΢��֧����ali_pay��֧������union_online������Ǯ����member_wallet����ԱǮ����
	char    tradeId[32+1];		//̫��ϵͳ��ˮId��tradeId��transactionId��outTradeId���ٴ���һ�������ȼ�tradeId > outTradeId > transactionId  
	char	outTradeId[31+1];		// �������ڲ���ˮ�ţ�tradeId��transactionId��outTradeId���ٴ���һ�������ȼ�tradeId > outTradeId > transactionId  
	char	transactionId[32+1];	//΢�Ż�֧�����������Ķ����ţ���̫���̻������ţ�tradeId��transactionId��outTradeId���ٴ���һ�������ȼ�tradeId > outTradeId > transactionId�����ڸ����������᷵�ظò���������п�����Ч	
	char	returnContent[1+1]; //  ������������ 1��������ϸ��Ϣ 2���������˿��� Ĭ��1 
	char	authCode[256+1];		//֧����Ȩ����Ա����̬�룬����ǻ�Ա����̬�������û�Ա���֧�� 
	char	code[128+1]; 		//�Ż�ȯ������
	char	body[32+1]; 		//��Ʒ���� 
	char    timestamp[12];	// ʱ���	
	char    nonceStr[32];	//  ����ַ���  
	char	nowPage[3+1]; 	//�����¼ҳ�룬��1��ʼ
	char	count[2+1]; 	//ÿҳ�ļ�¼���������10
	char	recordId[12+1]; //�����¼Id 
	char	sign[32+1]; 	//ǩ��
	char	signkey[32+1];	//ǩ����Կ
}QR_COL_Data;


extern QR_COL_Data  g_ColData;

extern void Send_add_item(char* pID,char* pData);
#define SEND_ADD_ITEM(s) 	Send_add_item(#s,g_ColData.##s) 

extern int MicroPay(char* pTitle);
extern  int OrderQuery(char* pTitle);
extern	int RefundFlow(char* pTitle);
extern	int ConsumeCard(char* pTitle);
extern	int ShiftMenu(char* pTitle);


#endif 
