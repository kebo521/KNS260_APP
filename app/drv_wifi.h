#ifndef _DRV_WIFI_
#define _DRV_WIFI_
//-------------------高8位命令成功与失败区分-------------
#define	WIFI_CMD_SUSS		0x00
#define	WIFI_CMD_FAIL		0x80
#define	WIFI_CMD_STOP		0x40

typedef enum
{
	WIFI_RET_OK =0,

	WIFI_RET_NULL		=0x10,
	WIFI_RET_DISCONNECT	=0x11,
	WIFI_RET_CONNECT	=0x12,
	WIFI_RET_SEND		=0x13,
	WIFI_RET_RECV		=0x14,
		
	WIFI_ERR_HARD	=-101,
	WIFI_NO_HEAD	=-102,
	WIFI_NO_DATA	=-103,
	WIFI_NO_OPEN	=-104,
	WIFI_NO_INIT	=-105,
	
	WIFI_ERR_ERROR	=-304,
	WIFI_ERR_FAIL	=-305,
	WIFI_ERR_BUSS_P =-306,
	WIFI_ERR_NULL 	=-307,
	
	WIFI_DISCONNECT =-405,
	
}WIFI_ERR_RETURN;

typedef struct
{
	char ssid[32+1];
	char password[32+1];
	u8	sec_type,Index;
}Wifi_file;

typedef struct
{
	u16 Total;
	u16 curr;
	Wifi_file item[1];		//多出一个空间用于临时存放1条信息。
}Wifi_FileTable;
//---------------------------------------

typedef struct
{
	char sectype;//加密类型
	char ssid[32+1];
	s8 	rssi;
	char mac[18];
	char channel;
	short freq_offset;
}Wifi_ItemMsg;

typedef struct
{
	u16 readTotal;
	u16 writeTotal;
	Wifi_ItemMsg item[1];	
}Wifi_listTable;

typedef struct
{
	Wifi_FileTable *pFile;	//已经存密码
	Wifi_listTable *plist; //热点列表
	Wifi_ItemMsg *pCurrent; //当前热点
}Wifi_MsgTable;


extern int WIFI_GetVersion(char* sVersion,int sizeVer);
extern void WIFI_Sleep(int en);
extern int WIFI_Connet(u8 Enssl,char* pHost,u16 port);
extern int WIFI_DisConnet(int timeoutMs);
extern int WIFI_SendBuff(char* pSend,int sLen);
extern int WIFI_RecvBuff(char* pRecv,int RecvSize,int timeOutMs,CHECK_DATA_FULL pCheckFull);
extern int Wifi_NetAddrGet(char *pszIp);


extern int APP_WIFI_SetKey(char *pTitle);
//extern int APP_WIFI_ScanKey(char *pTitle);
extern int APP_WIFI_EN(char* title);


typedef struct	
{
	char Mask[4]; 	// "WIFI"
	int (*GetVersion)(char*,int);
	int (*Connet)(u8,char*,u16);
	int (*DisConnet)(int);
	int (*SendBuff)(char*,int);
	int (*RecvBuff)(char*,int,int,CHECK_DATA_FULL);
	int (*NetAddrGet)(char*);
	void (*Sleep)(int);
	int (*EN)(char*);
	int (*SetKey)(char*);
	int (*ScanKey)(char*);
	int (*Rest)(void);

	int (*get_status)(void);
	int (*open)(void);
	int (*close)(void);
	int (*set_key)(char *,char *,u8);
	int (*get_host)(Wifi_MsgTable *,int);
	int (*AutoRun)(void);

	int (*ConfigMode)(int);	//配网模式
	int(*GetNetMsg)(int,char*,int);	//获得wifi模块信息 type(WIFI_MSG_TYPE),pOut,outSize
}API_WIFI_Def;

#endif
