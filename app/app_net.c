#include "communal.h"

//============================================================================
int APP_GetNetState(void)
{
	return pSdkFun->net->GetNetState();
}

//bit0=1连接时受理按键，bit1=1接收时受理按键======
void APP_SetKeyAccept(u32 Setbit)
{
	pSdkFun->net->KeyAccept(Setbit);
}



//============================================================================
int APP_Network_Connect(char* pHostIp,u16 port,int ENssl)
{
	return pSdkFun->net->Connect(pHostIp,port,ENssl);
}

//=======================网络发送=========================================================
int  APP_Network_Send(char* pBuff,int len)
{
	return pSdkFun->net->Send(pBuff,len);
}

//=======================网络接收=========================================================
int  APP_Network_Recv(char* pBuff,int BuffSize,int timeoutMs,CHECK_DATA_FULL pCheckFull)
{
	return pSdkFun->net->Recv(pBuff,BuffSize,timeoutMs,pCheckFull);
}

int APP_Network_Disconnect(int timeOutMs)
{
	return pSdkFun->net->Disconnect(timeOutMs);
}


static NET_ADDR_DATA TcpSaveFlag={0};

//====内部信息显示控制，默认为FALSE 有显示,uDisplay设成TRUE不显示===
void TCP_SetInterNotDisplay(BOOL uDisplay)
{
	TcpSaveFlag.NotDisplay=uDisplay;
}


int OpenAPN(char* pTitle)
{
	return 0;
}

int Tcp_Link(char* pTitle)
{
	int 		ret;
	ret=pSdkFun->net->GetNetState();
	if(ret == OPER_LOW_VOLTAGE)
	{
		if(!TcpSaveFlag.NotDisplay) 
			APP_ShowTradeFA(STR_PLEASE_CHARGE,3000);
		return OPER_ERR;
	}
	else if(((ret&0xff)!=NET_WLAN_CntHost) && ((ret&STATE_NET_2G)==0))
	{
		if(!TcpSaveFlag.NotDisplay) 
			APP_ShowNoSignel(STR_NET_NO_SERVICE,3000);
		return OPER_ERR;
	}
	if(!TcpSaveFlag.NotDisplay) 
		APP_ShowWaitFor(NULL);//STR_NET_LINK_WLAN
	if(TcpSaveFlag.port==0)
	{
		TcpSaveFlag.port = HTTP_TRADE_PORT;
		TcpSaveFlag.ENssL = Conv_HttpGetName(TcpSaveFlag.sHost,HTTP_TRADE_ADDERR);
	}
	ret=pSdkFun->net->Connect(TcpSaveFlag.sHost,TcpSaveFlag.port,TcpSaveFlag.ENssL);
	//--------------电量低限制交易--------------------------
	if(ret < 0)
	{
		if(!TcpSaveFlag.NotDisplay) 
			APP_ShowNoSignel(STR_NET_FAIL_LINK,3000);
	}
	return ret;
}
int  Tcp_SocketData(char* pTitle,CHECK_DATA_FULL pCheckFull)
{
	int ret;
	ret=pSdkFun->net->Send(PE_SendBuf,pFlow.pMsgLen);
	if(ret<0)
	{
		if(!TcpSaveFlag.NotDisplay)
			APP_ShowNoSignel(STR_NET_FAIL_SEND,3000);
		return OPER_SEND_ERR;
	}
	ret=pSdkFun->net->Recv(PE_SendBuf,BufSize,30*1000,pCheckFull);
	if(ret <= 0)
	{
		if(ret == OPER_RET)
			return OPER_RET;
		if(!TcpSaveFlag.NotDisplay)
			APP_ShowNoSignel(STR_NET_FAIL_RECV,3000);
		return OPER_RECV_ERR;
	}
	//---------------------------------------------------------
	return PE_CheckRecvData(PE_SendBuf,ret);
}
int Tcp_Close(char* pTitle)
{
	return pSdkFun->net->Disconnect(0);
}


void Tcp_LoadMsg(const char* pHttpAdderr,u16 port)
{
	TcpSaveFlag.port = port;
	TcpSaveFlag.ENssL = Conv_HttpGetName(TcpSaveFlag.sHost,pHttpAdderr);
}


