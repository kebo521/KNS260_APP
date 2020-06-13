#ifndef _PE_NET_
#define _PE_NET_

enum NET_STATE
{
	NET_NULL			=0x0000,
		
	NET_WLAN_CLOSE		=0x0000,
	NET_WLAN_DisHost	=0x0010,	//DIS Connect
	NET_WLAN_CntHost	=0x0001,
	NET_WLAN_cetCenter	=0x0003,

	STATE_NET_2G		=0x2000,
	STATE_NET_3G		=0x3000,
	STATE_NET_4G		=0x4000,
	STATE_NET_5G		=0x5000,

	STATE_NET_CLOSE		=0x0000,
	STATE_NET_CntPDP	=0x0100,
	STATE_NET_CntCenter	=0x0300,
};	

typedef struct
{
	u16  			port;           /* port number */
	char 			sHost[32];		/* ������IP�� */
	u8				ENssL;			/* SSL��� */
	u8				NotDisplay;		/* �ԷǱ�� */
}NET_ADDR_DATA;

typedef enum
{
	SR_STAIP=1,	//<Station	IP	address>
	SR_STAMAC=2,	//<Station	MAC	address>
}APP_MSG_TYPE;

extern int APP_GetNetState(void);
extern void APP_SetKeyAccept(u32 Setbit);
//=======================================================================================
extern int APP_Network_Connect(char* pHostIp,u16 port,int ENssl);
extern int APP_Network_Send(char* pBuff,int len);
extern int APP_Network_Recv(char* pBuff,int BuffSize,int timeoutMs,CHECK_DATA_FULL pCheckFull);
extern int APP_Network_Disconnect(int timeOutMs);

//====�ڲ���Ϣ��ʾ���ƣ�Ĭ��ΪFALSE ����ʾ,uDisplay���TRUE����ʾ===
extern void TCP_SetInterNotDisplay(BOOL uDisplay);
extern int OpenAPN(char* pTitle);
extern  int Tcp_Link(char* pTitle);
extern int  Tcp_SocketData(char* pTitle,CHECK_DATA_FULL pCheckFull);
extern int Tcp_Close(char* pTitle);
extern void Tcp_LoadMsg(const char* pHttpAdderr,u16 port);


typedef struct	
{
	char Mask[4]; 	// "Net"
	int (*GetNetState)(void);
	int (*Connect)(char*,u16,int);
	int (*Send)(char*,int);
	int (*Recv)(char*,int,int,CHECK_DATA_FULL);
	int (*Disconnect)(int);
	void (*KeyAccept)(u32);	//bit0=1����ʱ��������bit1=1����ʱ������======
	int (*GetLocalIP)(char*);	//�������Ҫ��Connect ֮��ʹ�ã�����0�ɹ�

	int(*GetNetMsg)(int,char*,int);	//���NETģ����Ϣ type(APP_MSG_TYPE),pOut,outSize
}API_NetWork_Def;

#endif
