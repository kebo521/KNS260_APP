#include "communal.h"

/*
int APP_RSATest(char* pTitle)
{
	mbedtls_pk_context gctx;
	u8 buff[2048];
	int rlen =0;
	int Ret;

	APP_ShowSta(pTitle,"读密钥中...");
    rlen=APP_FileReadBuff("pri.key",0,buff,2048);
	if(rlen<=0)
	{
		return -1;
	}
    TRACE("sKeyLen=%d\r\n ",rlen);
	TRACE("pKey End2=[%x,%x]\r\n ",buff[rlen-1],buff[rlen]);
	buff[rlen]=0x00;
	pTlsFuntion->pk->pk_init(&gctx);
	 TRACE("*************** \r\n");
	Ret=pTlsFuntion->pk->pk_parse_key(&gctx,buff,rlen+1,NULL,0);
	TRACE("pk_parse_key[Ret:%d]\r\n",Ret);

	{
		mbedtls_rsa_context * rsa = (mbedtls_rsa_context *)gctx.pk_ctx;
		TRACE("padding[%d]padding[%d]\r\n",rsa->padding,rsa->hash_id);
	}
	
	if(Ret==0)
	{
		u8 sEncrypt[256] = {0},shaout[20]={0},decOut[256]={0};
		size_t sigLen = 256,decOlen=266; 
		APP_ShowSta(pTitle,"数据签名中...");
		for(rlen=0;rlen<sizeof(buff);rlen++)
			buff[rlen]=rlen;
		pTlsFuntion->hash->md(MBEDTLS_MD_SHA1,buff,rlen,shaout);
		TRACE_HEX("hash->md MBEDTLS_MD_SHA1",shaout,20);
		Ret =pTlsFuntion->pk->pk_sign(&gctx,MBEDTLS_MD_SHA1,MBEDTLS_RSA_PKCS_V15,buff,rlen,sEncrypt,&sigLen);
		TRACE("rsa_rsassa_pss_hash256_sign ret:%x\r\n", Ret);
		TRACE_HEX("encrypt data is ",sEncrypt,sigLen);

		{
			mbedtls_rsa_context * rsa = (mbedtls_rsa_context *)gctx.pk_ctx;
			TRACE("2 ->padding[%d]padding[%d]\r\n",rsa->padding,rsa->hash_id);
		}
		Ret =pTlsFuntion->pk->pk_decrypt(&gctx,sEncrypt,sigLen,decOut,&decOlen,sizeof(decOut));
		TRACE("pk_decrypt ret:%x\r\n", -Ret);
		TRACE_HEX("pk_decrypt decOut ",decOut,decOlen);

		
		Ret =pTlsFuntion->pk->pk_encrypt(&gctx,buff,sigLen-11,sEncrypt,&sigLen,sizeof(sEncrypt));
		TRACE("pk->pk_encrypt ret:%x\r\n", -Ret);
		TRACE_HEX("pk->pk_encrypt decOut ",sEncrypt,sigLen);

		
		Ret =pTlsFuntion->pk->pk_decrypt(&gctx,sEncrypt,sigLen,decOut,&decOlen,sizeof(decOut));
		TRACE("pk->pk_decrypt ret:%x\r\n", -Ret);
		TRACE_HEX("pk->pk_decrypt decOut ",decOut,decOlen);
		//Ret=APP_base64_encode(pOutData,512,&OutLen,(unsigned char *)sEncrypt,sigLen);
	}
	pTlsFuntion->pk->pk_free(&gctx);
	return 0;
}

*/


int APP_HardVesion(char* pTitle)
{
	char ShowMsg[512];
	char	buff[128]={0};
	int		ret,offset;
	offset=API_sprintf(ShowMsg,"Master:%s\n",APP_GetMasterVer());
	ret=WIFI_GetVersion(buff,sizeof(buff));
	if(ret>0)
	{
		buff[ret]='\0';
		API_sprintf(ShowMsg+offset,"WIFI:%s\n",buff);
	}
	return APP_ShowInfo(pTitle,ShowMsg,20*1000);
}




#if(0)


#if(0)
static NET_ADDR_DATA testNetAdd={
		NULL,        			/* ip address */
		8888,           		/* port number */
		{"113.105.146.93"},	/* 域名或IP名 */
		0,					/* SSL标记 */
		};
#else
static NET_ADDR_DATA testNetAdd={
		NULL,        			/* ip address */
		443,           			/* port number */
		{"pay.swiftpass.cn"},	/* 域名或IP名 */
		1,						/* SSL标记 */
		};
#endif


int APP_TestNetConnect(char *pTitle)
{
	char			pOriginal[128]={0};
	ULONG			newTimeMs,oldTimeMs;
	int				ret;
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"连接...\n");
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"%s %d\n",testNetAdd.sHost,testNetAdd.port);
	GetTickCount(&oldTimeMs);
	ret=APP_Network_Connect(testNetAdd.sHost,testNetAdd.port,testNetAdd.ENssL);
	GetTickCount(&newTimeMs);
	if(ret)
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"连接失败,耗时%d\n",newTimeMs-oldTimeMs);
	else
	{
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"连接成功,耗时%d\n",newTimeMs-oldTimeMs);
	}
	APP_WaitUiEvent(5000);
	return 0;
}

int APP_TestNetSend(char *pTitle)
{
	int 			ret;
	ULONG			newTimeMs,oldTimeMs;
	char			pOriginal[128]={0};
	char			pSendBuff[]={"\x50\x4F\x53\x54\x20\x2F\x67\x61\x74\x65\x77\x61\x79\x2F\x61\x70\x69\x2F\x62\x61\x63\x6B\x54\x72\x61\x6E\x73\x52\x65\x71\x2E\x64\x6F\x20\x48\x54\x54\x50\x2F\x31\x2E\x31\x0D\x0A\x55\x73\x65\x72\x2D\x41\x67\x65\x6E\x74\x3A\x20\x41\x70\x61\x63\x68\x65\x2D\x48\x74\x74\x70\x43\x6C\x69\x65\x6E\x74\x2F\x34\x2E\x34\x2E\x31\x20\x0D\x0A\x48\x6F\x73\x74\x3A\x20\x67\x61\x74\x65\x77\x61\x79\x2E\x74\x65\x73\x74\x2E\x39\x35\x35\x31\x36\x2E\x63\x6F\x6D\x0D\x0A\x43\x6F\x6E\x74\x65\x6E\x74\x2D\x54\x79\x70\x65\x3A\x20\x61\x70\x70\x6C\x69\x63\x61\x74\x69\x6F\x6E\x2F\x78\x2D\x77\x77\x77\x2D\x66\x6F\x72\x6D\x2D\x75\x72\x6C\x65\x6E\x63\x6F\x64\x65\x64\x3B\x20\x63\x68\x61\x72\x73\x65\x74\x3D\x55\x54\x46\x2D\x38\x0D\x0A\x43\x6F\x6E\x6E\x65\x63\x74\x69\x6F\x6E\x3A\x20\x4B\x65\x65\x70\x2D\x41\x6C\x69\x76\x65\x0D\x0A\x43\x6F\x6E\x74\x65\x6E\x74\x2D\x4C\x65\x6E\x67\x74\x68\x3A\x36\x31\x34\x0D\x0A\x0D\x0A\x61\x63\x63\x65\x73\x73\x54\x79\x70\x65\x3D\x30\x26\x62\x61\x63\x6B\x55\x72\x6C\x3D\x31\x32\x37\x2E\x30\x2E\x30\x2E\x31\x26\x62\x69\x7A\x54\x79\x70\x65\x3D\x30\x30\x30\x30\x30\x30\x26\x63\x65\x72\x74\x49\x64\x3D\x36\x38\x37\x35\x39\x36\x36\x33\x31\x32\x35\x26\x63\x68\x61\x6E\x6E\x65\x6C\x54\x79\x70\x65\x3D\x30\x38\x26\x63\x75\x72\x72\x65\x6E\x63\x79\x43\x6F\x64\x65\x3D\x31\x35\x36\x26\x65\x6E\x63\x6F\x64\x69\x6E\x67\x3D\x55\x54\x46\x2D\x38\x26\x6D\x65\x72\x49\x64\x3D\x37\x37\x37\x32\x39\x30\x30\x35\x38\x31\x31\x30\x30\x34\x38\x26\x6F\x72\x64\x65\x72\x49\x64\x3D\x32\x30\x31\x38\x30\x37\x31\x37\x32\x30\x31\x34\x32\x37\x26\x73\x69\x67\x6E\x4D\x65\x74\x68\x6F\x64\x3D\x30\x31\x26\x74\x78\x6E\x41\x6D\x74\x3D\x31\x26\x74\x78\x6E\x53\x75\x62\x54\x79\x70\x65\x3D\x30\x37\x26\x74\x78\x6E\x54\x69\x6D\x65\x3D\x32\x30\x31\x38\x30\x37\x31\x37\x32\x30\x31\x34\x32\x37\x26\x74\x78\x6E\x54\x79\x70\x65\x3D\x30\x31\x26\x76\x65\x72\x73\x69\x6F\x6E\x3D\x35\x2E\x31\x2E\x31\x26\x73\x69\x67\x6E\x61\x74\x75\x72\x65\x3D\x68\x30\x76\x47\x72\x77\x79\x68\x45\x73\x74\x42\x4B\x76\x62\x6F\x47\x4C\x68\x70\x4B\x6C\x37\x59\x69\x38\x53\x4F\x37\x79\x69\x25\x32\x66\x44\x58\x72\x43\x63\x32\x73\x46\x64\x4C\x4F\x49\x4E\x77\x43\x6F\x30\x39\x36\x77\x63\x4B\x59\x48\x6B\x37\x32\x74\x6C\x4A\x33\x41\x59\x25\x32\x62\x58\x56\x6A\x46\x45\x6D\x68\x4F\x78\x47\x6E\x6C\x57\x72\x25\x32\x66\x37\x61\x74\x62\x4C\x56\x34\x4F\x35\x32\x64\x4F\x47\x4D\x63\x69\x6D\x6C\x34\x38\x73\x52\x31\x77\x7A\x48\x39\x76\x6F\x32\x44\x78\x58\x6D\x44\x67\x68\x45\x37\x4B\x6B\x51\x25\x32\x66\x51\x37\x39\x6F\x59\x31\x64\x48\x76\x37\x45\x6D\x30\x63\x45\x51\x53\x70\x72\x4E\x79\x62\x68\x49\x64\x4E\x66\x6B\x4A\x43\x57\x72\x6E\x4F\x66\x67\x53\x62\x53\x25\x32\x62\x55\x58\x37\x62\x70\x41\x5A\x45\x4A\x54\x43\x57\x79\x58\x47\x63\x6E\x6F\x50\x32\x36\x6E\x56\x77\x38\x62\x30\x36\x39\x73\x47\x35\x4A\x48\x4E\x53\x42\x6A\x48\x4B\x4C\x6D\x4C\x4A\x31\x53\x51\x63\x36\x61\x46\x56\x35\x25\x32\x66\x42\x49\x76\x44\x4F\x62\x64\x63\x79\x6A\x6E\x4F\x37\x78\x6A\x44\x7A\x4C\x6D\x4F\x4B\x63\x4C\x6A\x72\x43\x6A\x43\x64\x57\x4A\x72\x34\x58\x63\x47\x7A\x37\x54\x34\x35\x67\x38\x6E\x6D\x6C\x50\x74\x70\x66\x67\x51\x64\x6D\x5A\x62\x50\x30\x4A\x34\x36\x6F\x4C\x64\x7A\x77\x53\x74\x7A\x71\x63\x66\x25\x32\x62\x63\x62\x7A\x6D\x56\x54\x43\x70\x73\x6E\x6A\x33\x41\x49\x55\x35\x35\x45\x33\x66\x71\x6A\x32\x58\x4E\x49\x43\x77\x36\x43\x74\x36\x58\x61\x49\x4D\x44\x77\x66\x47\x44\x6B\x72\x34\x4C\x6B\x63\x51\x62\x34\x77\x25\x33\x64\x25\x33\x64"};
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"发送数据..\n");
	GetTickCount(&oldTimeMs);
	ret=APP_Network_Send(pSendBuff,sizeof(pSendBuff));
	GetTickCount(&newTimeMs);
	if(ret<0)
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"失败,耗时%d\n",newTimeMs-oldTimeMs);
	else
	{
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"成功,耗时%d\n",newTimeMs-oldTimeMs);
	}
	APP_WaitUiEvent(5000);
	return 0;
}

int APP_TestNetRecv(char *pTitle)
{
	int 			ret;
	ULONG			newTimeMs,oldTimeMs;
	char			pOriginal[128]={0};
	char			sRecvBuff[1024]={0};
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"接收数据..\n");
	GetTickCount(&oldTimeMs);
	ret=APP_Network_Recv(sRecvBuff,sizeof(sRecvBuff),20*1000,NULL);
	GetTickCount(&newTimeMs);
	if(ret<=0)
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"失败,耗时%d\n",newTimeMs-oldTimeMs);
	else
	{
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"成功,耗时%d\n",newTimeMs-oldTimeMs);
		TRACE_HEX("RecvBuff",sRecvBuff,ret);
	}
	APP_WaitUiEvent(5000);
	return 0;
}

int APP_TestNetDisconnect(char *pTitle)
{
	char			pOriginal[128]={0};
	ULONG			newTimeMs,oldTimeMs;
	int 			ret;
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"断开连接..\n");
	GetTickCount(&oldTimeMs);
	ret=APP_Network_Disconnect(10*1000);
	GetTickCount(&newTimeMs);
	if(ret)
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"断开失败,耗时%d\n",newTimeMs-oldTimeMs);
	else
	{
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"断开成功,耗时%d\n",newTimeMs-oldTimeMs);
	}
	APP_WaitUiEvent(5000);
	return 0;
}


int APP_TestTcpConnect(char *pTitle)
{
	char			pOriginal[128]={0};
	ULONG			newTimeMs,oldTimeMs;
	int 			ret;
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"TCP连接网络..\n");
	GetTickCount(&oldTimeMs);
	ret=Tcp_Link(pTitle);
	GetTickCount(&newTimeMs);
	if(ret)
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"连接失败,耗时%d\n",newTimeMs-oldTimeMs);
	else
	{
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"连接成功,耗时%d\n",newTimeMs-oldTimeMs);
	}
	APP_WaitUiEvent(5000);
	return 0;
}

int APP_TestTcpSendRecv(char *pTitle)
{
	char			pOriginal[128]={0};
	ULONG			newTimeMs,oldTimeMs;
	int 			ret;
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"TCP收发数据..\n");
	PE_SendBuf=(char*)malloc(BufSize);
	pFlow.pMsgLen=128;
	GetTickCount(&oldTimeMs);
	ret=Tcp_SocketData(pTitle,NULL);
	GetTickCount(&newTimeMs);
	free(PE_SendBuf);
	if(ret)
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"发收失败,耗时%d\n",newTimeMs-oldTimeMs);
	else
	{
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"发收成功,耗时%d\n",newTimeMs-oldTimeMs);
	}
	APP_WaitUiEvent(5000);
	return 0;
}

int APP_TestTcpDisConnect(char *pTitle)
{
	char			pOriginal[128]={0};
	ULONG			newTimeMs,oldTimeMs;
	int 			ret;
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"TCP断开网络..\n");
	GetTickCount(&oldTimeMs);
	ret=Tcp_Close(pTitle);
	GetTickCount(&newTimeMs);
	if(ret)
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"断开失败,耗时%d\n",newTimeMs-oldTimeMs);
	else
	{
		APP_ShowChangeInfo(pOriginal,sizeof(pOriginal),"断开成功,耗时%d\n",newTimeMs-oldTimeMs);
	}
	APP_WaitUiEvent(5000);
	return 0;
}




int APP_TestNet(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		"连接网络",		APP_TestNetConnect,
		"发送数据",		APP_TestNetSend,
		"接收数据",		APP_TestNetRecv,
		"关闭网络",		APP_TestNetDisconnect,

		"TCP连接",		APP_TestTcpConnect,
		"TCP发收",		APP_TestTcpSendRecv,
		"TCP断开",		APP_TestNetDisconnect,
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
}

#endif


/*
int APP_rsa_SignTest(char* title)
{
	int sKeyLen =0,ret;
	//int Ret;
	mbedtls_pk_context ctxPk;
	ULONG timeMs1S,timeMs1E,timeMs2S,timeMs2E;
	
	
    char* pKey=malloc(2048);
    
	sKeyLen=APP_FileReadBuff(Private_keyPath,0,pKey,2048);
	if(sKeyLen > 0)
	{
		pKey[sKeyLen++]='\0';			//送进去的长度要包含'\0'
		pTlsFuntion->rsa->pk_init(&ctxPk);
		GetTickCount(&timeMs1S);
		ret=pTlsFuntion->rsa->pk_parse_key(&ctxPk,(u8*)pKey,sKeyLen,NULL,0);
		GetTickCount(&timeMs1E);
		TRACE("pk_parse_key timeMs:%d\r\n ",timeMs1E-timeMs1S);
		if(0 == ret)
		{
			size_t retLen=0;
			TRACE("pk_parse_key pKey:%x\r\n ",pKey);
			memset(pKey,0,2048);
			GetTickCount(&timeMs2S);
			ret=pTlsFuntion->rsa->pk_sign(&ctxPk,MBEDTLS_MD_SHA256,MBEDTLS_RSA_PKCS_V21,(u8*)pKey,1024,(u8*)pKey+1024,&retLen);
			GetTickCount(&timeMs2E);
			TRACE("pk_rsa_sign ret[%d] retlen[%d] timeMs:%d\r\n ",ret,retLen,timeMs2E-timeMs2S);
			if(ret==0)
			{
				TRACE_HEX("OutSignBuff",pKey+1024,retLen);
			}
		}
		pTlsFuntion->rsa->pk_free(&ctxPk);
	}
    free(pKey);
	return 0;
}

int APP_testInterface(char *pTitle)
{
	char	showMsgBuff[64];
	ULONG time1s,time1e;
	ULONG time2s,time2e;
	int ret=12,i,max=1000000;
	GetTickCount(&time1s);
	for(i=0;i<max;i++)
	{
		ret=pSdkFun->sdk->InterfaceTest(ret);
	}
	GetTickCount(&time1e);
		

	GetTickCount(&time2s);
	for(i=0;i<max;i++)
	{
		ret=APP_InterfaceTest(ret);
	}
	GetTickCount(&time2e);

	API_sprintf(showMsgBuff,"[%d][%d]",time1e-time1s,time2e-time2s);
	return APP_ShowMsg(pTitle,showMsgBuff,30*1000);
}
*/
/*
int APP_testMD(char *pTitle)
{
	u32 buff[1024/4];
	u8 OutBuff1[64];
	u8 KeyBuff[32];
	u16 i,max;
	u8* pIndata;
	u32	Inlen;
	int timeMs;
	APP_ShowSta(pTitle,"测试MD...");
	timeMs=API_TimeCurrMS();
	srand_m(timeMs);
	max=sizeof(buff)/sizeof(buff[0]);
	for(i=0;i<max;i++)
	{
		buff[i]=rand_m();
	}
	pIndata=(u8*)buff;
	Inlen=i*4;
	pTlsFuntion->hash->md(MBEDTLS_MD_MD5,pIndata,Inlen,OutBuff1);
	TRACE_HEX("md5 OutBuff1",OutBuff1,20);

	pTlsFuntion->hash->md(MBEDTLS_MD_SHA1,pIndata,Inlen,OutBuff1);
	TRACE_HEX("sha1 OutBuff1",OutBuff1,20);

	pTlsFuntion->hash->md(MBEDTLS_MD_SHA256,pIndata,Inlen,OutBuff1);
	TRACE_HEX("sha256 OutBuff1",OutBuff1,32);
	API_memcpy(KeyBuff,OutBuff1,32);
	pTlsFuntion->hash->md_hmac(MBEDTLS_MD_SHA256,KeyBuff,32,pIndata,Inlen,OutBuff1);

	TRACE_HEX("md_hmac OutBuff1",OutBuff1,32);
	return APP_ShowMsg(pTitle,"测试MD完成",3000);
}
*/
int TEST_InputFee(char *pTitle)
{
    int ret=0;
	char total_fee[12];
	EDIT_DATA	EditData;	
	API_strcpy(total_fee,"1");

	
	CLEAR(EditData);
	EditData.pTitle	      =pTitle;
	EditData.pFrontText	="请输入金额";
	EditData.pAfterText    ="按[确认]键继续";

	EditData.Min		=1;
	EditData.Max		=12;
	EditData.Way		=IME_SUM;
	EditData.Limit		=IME_SUM;
	EditData.timeOutMs =30*1000;

	ret =APP_Edit(&EditData,total_fee);
	if(ret>0)
		APP_ShowMsg(pTitle,total_fee,5000);
	else
		return 1;

	API_strcpy(total_fee,"1");

	EditData.Way		=IME_SUM|IME_NUM;
	EditData.Limit		=IME_SUM|IME_NUM;
	EditData.timeOutMs =30*1000;

	ret =APP_Edit(&EditData,total_fee);
	if(ret>0)
		APP_ShowMsg(pTitle,total_fee,5000);
	else
		return 1;

	API_strcpy(total_fee,"1");
	ret=APP_EditSum(pTitle,'S',total_fee,60*1000);
	if(0>ret) 
		return ret;	
	return APP_ShowMsg(pTitle,total_fee,5000);
}

/*
#define WW_PORT				18687
#define WW_IP				"218.17.164.124"

int TEST_AsynNet(char *pTitle)
{
	int ret,NetFlow;
 	u16 t1,t2;
	char buff[1024],sBuff[512];
	u32 readLen,sendLen;
 //  TRACE("epson api: %s\n", pSdkFun->epson->Mask);
	 //epson_tester();
	if(pSdkFun->net->Mask[3]<12)
	{
		 APP_ShowMsg(pTitle,"主控版本不支持",3000);
		 return 1;
	 }
	 APP_ScreenSleep(0);

	if(pSdkFun->scan->Open())
	{
		APP_ShowMsg(NULL,STR_SCAN_ERR_INIT,5*1000);
		return -1;
	}

	
	APP_ShowSta(pTitle,"连接网络");
	APP_Network_Connect(WW_IP, WW_PORT,0);
	API_strcpy(buff,"1234567890");
	sendLen=10;
	
	pSdkFun->scan->Start(BARSCAN_MODE_CONTINUE,1);
	Set_WaitEvent(15*1000, EVENT_NET);
	NetFlow=0;
	while(1)
	{
		if(FIFO_OperatPeekGetMsg(&t1, &t2))
		{
			if(t1 == EVEN_ID_TIME_OUT)
			{
				if(NetFlow==1)
				{
					APP_ShowSta(pTitle,"结束网络");
					pSdkFun->net->EndCurrWork();
					Set_WaitEvent(-1, EVENT_NET);
					NetFlow=2;
				}
				if(NetFlow==4)
				{
					APP_ShowSta(pTitle,"重新连接网络");
					Sleep(2000);
					pSdkFun->net->Set_Connet(0,WW_IP, WW_PORT);
					Set_WaitEvent(15*1000, EVENT_NET);
					NetFlow=0;
				}
			}
			else
			{
				ret = pSdkFun->net->Msg_Process(t1, t2);
				TRACE("MsgProcess ret=(%X),t1=%d,t1=%d\r\n",ret,t1,t2);
				switch(ret)
				{
					case NET_MSG_CONNECT:
						//APP_TTS_PlayText("服务器连接成功");
						NetFlow=1;
						APP_ShowSta(pTitle,"发送数据");
						APP_Network_Send(buff,sendLen);
						Set_WaitEvent(7*1000, EVENT_NET);
						break;
					case NET_MSG_DISCONNECT :
					case NET_MSG_FAIL | NET_MSG_DISCONNECT:
						APP_ShowSta(pTitle,"网络关闭成功");
						Set_WaitEvent(5*1000, EVENT_NET);
						NetFlow=4;
						break;
					case NET_MSG_RECV:
						APP_ShowSta(pTitle,"再发送数据");
						APP_Network_Send(buff,sendLen);
						Set_WaitEvent(7*1000, EVENT_NET);
						break;
					case NET_MSG_SEND:
						APP_ShowSta(pTitle,"接收数据");
						readLen=sizeof(buff);
						pSdkFun->net->Set_RecvBuff(buff,&readLen,NULL);
						Set_WaitEvent(20*1000, EVENT_NET);
						break;
					case NET_MSG_END:
						APP_ShowSta(pTitle,"断开网络");
						pSdkFun->net->Set_DisConnet();
						Set_WaitEvent(15*1000, EVENT_NET);
						NetFlow=3;
						break;
					default:
						//pSdkFun->net->Set_DisConnet();
						break;
				}
			}
		}
		else 
		{	
			int Ret;
			Ret=pSdkFun->scan->CheakRecv(sBuff,4,512);
			if(Ret < 0) continue;
			if(Ret > 0) 
			{
				if(Ret > 0)
				API_memcpy(buff,sBuff,Ret);
				sendLen = Ret;
			}
			pSdkFun->scan->Continue();
		}
		// 	 Sleep(500);
	}
 
}
*/
/*
{"head":{"retStatus":"S","retCode":"000000","retMsg":"浜ゆ槗鎴愬姛","serviceCode":"000300860006"},
"body":{"response":{"zjhm":"430621198901280443","zjlx":"201","xm":"鍚翠笁杈?,"djxh":"20124300910036951071",
					"cbdjxxlist":{"v":[
									   {"sbjbjgdm":"4306024306003100390","rybm":"5800203990","zgswjgdm":"14306020000","jfrlx":"0","jfxzxxlist":{"v":{"ksjfny":"201712","zzjfny":"999912","zsxmdm":"10212","zsxmmc":"鍩庝埂灞呮皯鍩烘湰鍖荤枟淇濋櫓璐?,"zspmdm":"102120001","zspmmc":"鍩庝埂灞呮皯鍩烘湰鍖荤枟淇濋櫓璐?,"zszmdm":"1021200014390002","zszmmc":"鏍囧噯-鍩庝埂灞呮皯鍖荤枟"}}}
									  ,{"sbjbjgdm":"4306024399001700170","rybm":"2101546122","zgswjgdm":"14306020000","jfrlx":"0","jfxzxxlist":{"v":{"ksjfny":"201610","zzjfny":"999912","zsxmdm":"10210","zsxmmc":"鍩庝埂灞呮皯鍩烘湰鍏昏�佷繚闄╄垂","zspmdm":"102100100","zspmmc":"鍩庝埂灞呮皯鍩烘湰鍏昏�佷繚闄╄垂","zszmdm":"1021001004330007","zszmmc":"鏅�氬弬淇濅汉鍛?鍩庝埂灞呮皯鍩烘湰鍏昏�佷繚闄?}}}
									  ]
								 }
					}
		}
}
*/
int TEST_JSON(char *pTitle)
{
	char *pInMsg="\x7B\x22\x68\x65\x61\x64\x22\x3A\x7B\x22\x72\x65\x74\x53\x74\x61\x74\x75\x73\x22\x3A\x22\x53\x22\x2C\x22\x72\x65\x74\x43\x6F\x64\x65\x22\x3A\x22\x30\x30\x30\x30\x30\x30\x22\x2C\x22\x72\x65\x74\x4D\x73\x67\x22\x3A\x22\xE4\xBA\xA4\xE6\x98\x93\xE6\x88\x90\xE5\x8A\x9F\x22\x2C\x22\x73\x65\x72\x76\x69\x63\x65\x43\x6F\x64\x65\x22\x3A\x22\x30\x30\x30\x33\x30\x30\x38\x36\x30\x30\x30\x36\x22\x7D\x2C\x22\x62\x6F\x64\x79\x22\x3A\x7B\x22\x72\x65\x73\x70\x6F\x6E\x73\x65\x22\x3A\x7B\x22\x7A\x6A\x68\x6D\x22\x3A\x22\x34\x33\x30\x36\x32\x31\x31\x39\x38\x39\x30\x31\x32\x38\x30\x34\x34\x33\x22\x2C\x22\x7A\x6A\x6C\x78\x22\x3A\x22\x32\x30\x31\x22\x2C\x22\x78\x6D\x22\x3A\x22\xE5\x90\xB4\xE4\xB8\x89\xE8\xBE\x89\x22\x2C\x22\x64\x6A\x78\x68\x22\x3A\x22\x32\x30\x31\x32\x34\x33\x30\x30\x39\x31\x30\x30\x33\x36\x39\x35\x31\x30\x37\x31\x22\x2C\x22\x63\x62\x64\x6A\x78\x78\x6C\x69\x73\x74\x22\x3A\x7B\x22\x76\x22\x3A\x5B\x7B\x22\x73\x62\x6A\x62\x6A\x67\x64\x6D\x22\x3A\x22\x34\x33\x30\x36\x30\x32\x34\x33\x30\x36\x30\x30\x33\x31\x30\x30\x33\x39\x30\x22\x2C\x22\x72\x79\x62\x6D\x22\x3A\x22\x35\x38\x30\x30\x32\x30\x33\x39\x39\x30\x22\x2C\x22\x7A\x67\x73\x77\x6A\x67\x64\x6D\x22\x3A\x22\x31\x34\x33\x30\x36\x30\x32\x30\x30\x30\x30\x22\x2C\x22\x6A\x66\x72\x6C\x78\x22\x3A\x22\x30\x22\x2C\x22\x6A\x66\x78\x7A\x78\x78\x6C\x69\x73\x74\x22\x3A\x7B\x22\x76\x22\x3A\x7B\x22\x6B\x73\x6A\x66\x6E\x79\x22\x3A\x22\x32\x30\x31\x37\x31\x32\x22\x2C\x22\x7A\x7A\x6A\x66\x6E\x79\x22\x3A\x22\x39\x39\x39\x39\x31\x32\x22\x2C\x22\x7A\x73\x78\x6D\x64\x6D\x22\x3A\x22\x31\x30\x32\x31\x32\x22\x2C\x22\x7A\x73\x78\x6D\x6D\x63\x22\x3A\x22\xE5\x9F\x8E\xE4\xB9\xA1\xE5\xB1\x85\xE6\xB0\x91\xE5\x9F\xBA\xE6\x9C\xAC\xE5\x8C\xBB\xE7\x96\x97\xE4\xBF\x9D\xE9\x99\xA9\xE8\xB4\xB9\x22\x2C\x22\x7A\x73\x70\x6D\x64\x6D\x22\x3A\x22\x31\x30\x32\x31\x32\x30\x30\x30\x31\x22\x2C\x22\x7A\x73\x70\x6D\x6D\x63\x22\x3A\x22\xE5\x9F\x8E\xE4\xB9\xA1\xE5\xB1\x85\xE6\xB0\x91\xE5\x9F\xBA\xE6\x9C\xAC\xE5\x8C\xBB\xE7\x96\x97\xE4\xBF\x9D\xE9\x99\xA9\xE8\xB4\xB9\x22\x2C\x22\x7A\x73\x7A\x6D\x64\x6D\x22\x3A\x22\x31\x30\x32\x31\x32\x30\x30\x30\x31\x34\x33\x39\x30\x30\x30\x32\x22\x2C\x22\x7A\x73\x7A\x6D\x6D\x63\x22\x3A\x22\xE6\xA0\x87\xE5\x87\x86\x2D\xE5\x9F\x8E\xE4\xB9\xA1\xE5\xB1\x85\xE6\xB0\x91\xE5\x8C\xBB\xE7\x96\x97\x22\x7D\x7D\x7D\x2C\x7B\x22\x73\x62\x6A\x62\x6A\x67\x64\x6D\x22\x3A\x22\x34\x33\x30\x36\x30\x32\x34\x33\x39\x39\x30\x30\x31\x37\x30\x30\x31\x37\x30\x22\x2C\x22\x72\x79\x62\x6D\x22\x3A\x22\x32\x31\x30\x31\x35\x34\x36\x31\x32\x32\x22\x2C\x22\x7A\x67\x73\x77\x6A\x67\x64\x6D\x22\x3A\x22\x31\x34\x33\x30\x36\x30\x32\x30\x30\x30\x30\x22\x2C\x22\x6A\x66\x72\x6C\x78\x22\x3A\x22\x30\x22\x2C\x22\x6A\x66\x78\x7A\x78\x78\x6C\x69\x73\x74\x22\x3A\x7B\x22\x76\x22\x3A\x7B\x22\x6B\x73\x6A\x66\x6E\x79\x22\x3A\x22\x32\x30\x31\x36\x31\x30\x22\x2C\x22\x7A\x7A\x6A\x66\x6E\x79\x22\x3A\x22\x39\x39\x39\x39\x31\x32\x22\x2C\x22\x7A\x73\x78\x6D\x64\x6D\x22\x3A\x22\x31\x30\x32\x31\x30\x22\x2C\x22\x7A\x73\x78\x6D\x6D\x63\x22\x3A\x22\xE5\x9F\x8E\xE4\xB9\xA1\xE5\xB1\x85\xE6\xB0\x91\xE5\x9F\xBA\xE6\x9C\xAC\xE5\x85\xBB\xE8\x80\x81\xE4\xBF\x9D\xE9\x99\xA9\xE8\xB4\xB9\x22\x2C\x22\x7A\x73\x70\x6D\x64\x6D\x22\x3A\x22\x31\x30\x32\x31\x30\x30\x31\x30\x30\x22\x2C\x22\x7A\x73\x70\x6D\x6D\x63\x22\x3A\x22\xE5\x9F\x8E\xE4\xB9\xA1\xE5\xB1\x85\xE6\xB0\x91\xE5\x9F\xBA\xE6\x9C\xAC\xE5\x85\xBB\xE8\x80\x81\xE4\xBF\x9D\xE9\x99\xA9\xE8\xB4\xB9\x22\x2C\x22\x7A\x73\x7A\x6D\x64\x6D\x22\x3A\x22\x31\x30\x32\x31\x30\x30\x31\x30\x30\x34\x33\x33\x30\x30\x30\x37\x22\x2C\x22\x7A\x73\x7A\x6D\x6D\x63\x22\x3A\x22\xE6\x99\xAE\xE9\x80\x9A\xE5\x8F\x82\xE4\xBF\x9D\xE4\xBA\xBA\xE5\x91\x98\x2D\xE5\x9F\x8E\xE4\xB9\xA1\xE5\xB1\x85\xE6\xB0\x91\xE5\x9F\xBA\xE6\x9C\xAC\xE5\x85\xBB\xE8\x80\x81\xE4\xBF\x9D\xE9\x99\xA9\x22\x7D\x7D\x7D\x5D\x7D\x7D\x7D\x7D";
	
	TRACE("pInMsg[%s]\r\n",pInMsg);
	/*
	APP_ShowSta(pTitle,"分层JSON处理中...");
	TRACE("====分层JSON多次处理(旧)======\r\n");
	{
		sIdDataTable *pFtable;
		pFtable=Conv_SingleJSON_GetMsg(pInMsg,pInMsg+API_strlen(pInMsg));
		if(pFtable)
		{
			char *phead;
			phead=Conv_GetParFindID(pFtable,"head");
			if(phead)
			{
				sIdDataTable *pThead;
				TRACE("phead[%s]\r\n",phead);
				pThead=Conv_SingleJSON_GetMsg(phead,phead+API_strlen(phead));
				if(pThead)
				{
					char *retCode,*retMsg,*body;
					sIdDataTable *pTbody;
					retCode=Conv_GetParFindID(pThead,"retCode");
					retMsg=Conv_GetParFindID(pThead,"retMsg");
					TRACE("Thead->retCode[%s]\r\n",retCode);
					TRACE("Thead->retMsg[%s]\r\n",retMsg);
					body=Conv_GetParFindID(pThead,"body");
					if(body)
					{
						//sIdDataTable *response;
						TRACE("Thead->body[%s]\r\n",body);
						pTbody=Conv_SingleJSON_GetMsg(body,body+API_strlen(body));
						if(pTbody)
						{
							//char *retCode,*retMsg;
							free(pTbody);
						}

					}
					free(pThead);
				}
			}
			free(pFtable);
		}
	}
	*/
	APP_ShowSta(pTitle,"多层JSON处理中...");
	TRACE("====多层JSON单次处理(新)======\r\n");
	{
		dfJsonTable *pFtable;
		char buff[1024];
		API_strcpy(buff,pInMsg);
		pFtable=Conv_JSON_GetMsg(buff,buff+API_strlen(buff));
		if(pFtable)
		{
			char *head,*retCode,*xm;
			char *body,*response,*pBRCV;
			u8 type;
			//-------------调用方法1-(路径法,一部到位)----------------
			TRACE("-------------调用方法1-(路径法,一次取出)----------------\r\n");
			head=Conv_GetJsonValue(pFtable,"head",NULL);	//一次取出第一层参数
			TRACE("phead[%x]\r\n",head);
			retCode=Conv_GetJsonValue(pFtable,"head/retCode",NULL);//一次取出第一层参数
			TRACE("pretCode[%s]\r\n",retCode);
			body=Conv_GetJsonValue(pFtable,"body",&type); //一次取出第二层参数
			TRACE("body[%d][%x]\r\n",type,body);
			response=Conv_GetJsonValue(pFtable,"body/response",&type); //一次取出第二层参数
			TRACE("body/response[%d][%x]\r\n",type,response);

			xm=Conv_GetJsonValue(pFtable,"body/response/xm",NULL);
			if(xm)
			{
				char GbkBuff[32];
				API_Utf8ToGbk(GbkBuff,sizeof(GbkBuff),xm);
				TRACE("body/response/xm[%d][%s]\r\n",type,GbkBuff);
			}
			//------------------取表法------------------
			pBRCV=Conv_GetJsonValue(pFtable,"body/response/cbdjxxlist/v",&type);
			if(pBRCV)
			{
				char *sbjbjgdm;
				dfJsonTable *pV=(dfJsonTable *)pBRCV;
				TRACE("body/response/cbdjxxlist/v[%d][%x]\r\n",type,pBRCV);
				sbjbjgdm=Conv_GetJsonValue(pV,"sbjbjgdm",&type);
				TRACE("body/response/cbdjxxlist/v/sbjbjgdm1[%d][%s]\r\n",type,sbjbjgdm);
				sbjbjgdm=Conv_GetJsonValue(pV->pNext,"sbjbjgdm",&type);
				TRACE("body/response/cbdjxxlist/v/sbjbjgdm2[%d][%s]\r\n",type,sbjbjgdm);
			}
			//---------------直接下标取值-------------------------
			pBRCV=Conv_GetJsonValue(pFtable,"body/response/cbdjxxlist/v[0]/sbjbjgdm",NULL);
			TRACE("body/response/cbdjxxlist/v[0]/sbjbjgdm1[%s]\r\n",pBRCV);
			pBRCV=Conv_GetJsonValue(pFtable,"body/response/cbdjxxlist/v[1]/sbjbjgdm",NULL);
			TRACE("body/response/cbdjxxlist/v[1]/sbjbjgdm2[%s]\r\n",pBRCV);

			pBRCV=Conv_GetJsonValue(pFtable,"body/response/cbdjxxlist/v[0]/jfxzxxlist/v/ksjfny",NULL);
			TRACE("body/response/cbdjxxlist/v[0]/jfxzxxlist/v/ksjfny[%s]\r\n",pBRCV);
			pBRCV=Conv_GetJsonValue(pFtable,"body/response/cbdjxxlist/v[1]/jfxzxxlist/v/zzjfny",NULL);
			TRACE("body/response/cbdjxxlist/v[1]/jfxzxxlist/v/zzjfny[%s]\r\n",pBRCV);
		
			//-------------调用方法2-(分部法,一层层的解)----------------
			TRACE("-------------调用方法2-(分部法,一层层的取)----------------\r\n");
			body=Conv_GetJsonValue(pFtable,"body",&type);
			TRACE("head[%d][%x]\r\n",type,body);
			if(body)
			{
				char *zjhm,*cbdjxxlist;
				response=Conv_GetJsonValue((dfJsonTable *)body,"response",&type); //第一次取出第一层结构
				TRACE("retCode[%d][%x]\r\n",type,response);
				if(response)
				{
					zjhm=Conv_GetJsonValue((dfJsonTable *)response,"zjhm",&type);
					TRACE("body/response/zjhm[%d][%s]\r\n",type,zjhm);
					cbdjxxlist=Conv_GetJsonValue((dfJsonTable *)response,"cbdjxxlist",&type);
					TRACE("body/response/cbdjxxlist[%d][%x]\r\n",type,cbdjxxlist);
					if(cbdjxxlist)
					{
						char *v;
						v=Conv_GetJsonValue((dfJsonTable *)cbdjxxlist,"v",&type);
						TRACE("body/response/cbdjxxlist/v[%d][%x]\r\n",type,v);
						if(v)
						{
							char *sbjbjgdm;
							dfJsonTable *pV=(dfJsonTable *)v;
							sbjbjgdm=Conv_GetJsonValue(pV,"sbjbjgdm",&type);
							TRACE("body/response/cbdjxxlist/v/sbjbjgdm1[%d][%s]\r\n",type,sbjbjgdm);
							sbjbjgdm=Conv_GetJsonValue(pV,"sbjbjgdm[1]",&type);
							TRACE("body/response/cbdjxxlist/v/sbjbjgdm2[%d][%s]\r\n",type,sbjbjgdm);
						}
					}
				}
			}
			
			Conv_JSON_free(pFtable);
		}
		else
		{
			TRACE("Conv_JSON_GetMsg Err\r\n");
		}
	}
	return 0;
}	

int APP_CountdownDemo(char* title)
{
	if(pGuiFun->Mask[3] < 26)
		return APP_ShowMsg("主控版本太低","不支持该功能",3000);
	
	APP_ShowSta(title,"从100到000");
	pGuiFun->Countdown_ShowInit(TEXT_ALIGN_CENTER|TEXT_VALIGN_BOTTOM,3,100);
	while(1)
	{
		OsSleep(1000);
		if(EVENT_TIMEOUT == pGuiFun->Countdown_ShowGet())
			break;
	}
	APP_ShowSta(title,"结束演示");
	return 0;
}


int APP_SystemMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		"恢复出厂设置",     APP_ParFacInit,
		"硬件版本",			APP_HardVesion,
		//"接口耗时测试",		APP_testInterface,
		//"网络测试",			APP_TestNet,
		//"RSA签名测试",		APP_rsa_SignTest,
//		"MD算法测试",		APP_testMD,
//		"PK接口测试",		APP_RSATest,

		"输入金额测试",		TEST_InputFee,
//		"异步网络测试",		TEST_AsynNet,
//		"JSON测试",			TEST_JSON,
//		"倒计时显示测试",	APP_CountdownDemo,
	};
	//--------输入密码验证-------------
//	if(APP_InputPin(title,STR_ENTER_THE_ADMIN_PASSu16,  STR_PRESS_NUBER_KEYS_ENTER, "20060101"))
//		return 1;
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
}





//=====二维码生成网址===
//http://www.liantu.com/



