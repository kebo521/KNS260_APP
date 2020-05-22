#include "communal.h"



int Full_CheckRecv(char *pRecv,int ReadLen)
{
	if(ReadLen > 0)
	{
		pRecv[ReadLen]='\0';
		if(API_strstr(pRecv,"<xml>"))
		{
			if(API_strstr(pRecv,"</xml>"))
			{
				TRACE("Full_CheckRecv[%d] OK\r\n", ReadLen);
				return ReadLen;
			}
		}
	}
	TRACE("pRecvLen=%d nofull\r\n",ReadLen);
	return 0;
}


/**
 * socket 连接
 */

int PE_Connect(char *pShowLink,char *pAdderr,u16 uPort)
{
	int		ret;
	char	sHost[64+3];
	u8 		ENssL;
	ret=APP_GetNetState();
	if(ret == OPER_LOW_VOLTAGE)
	{//--------------电量低限制交易--------------------------
		APP_ShowTradeFA(STR_PLEASE_CHARGE,3000);
		return OPER_ERR;
	}
	else if(((ret&0xff)!=NET_WLAN_CntHost) && ((ret&STATE_NET_2G)==0))
	{
		APP_ShowNoSignel(STR_NET_NO_SERVICE,3000);
		return OPER_ERR;
	}
	if(pShowLink) APP_ShowWaitFor(pShowLink);//STR_NET_LINK_WLAN
	ENssL = Conv_HttpGetName(sHost,pAdderr);
	ret=APP_Network_Connect(sHost,uPort,ENssL);
	TRACE("PE Connect ret=[%d]\r\n",ret);
	if(ret < 0)
	{
		APP_ShowNoSignel(STR_NET_FAIL_LINK,3000);
		TRACE("PE Connect ERR[%s]\r\n",STR_NET_FAIL_LINK);
		return ret;
	}
	return 0;
}


/**
 * 收发数据、校验数据
 */
int PE_SocketData(char *pTitle, CHECK_DATA_FULL pCheckFull)
{	
	int ret;
	if (0 > (ret = APP_Network_Send(PE_SendBuf, pFlow.pMsgLen)))
	{
		if (ret != OPER_RET)
		{
			if(pTitle) APP_ShowMsg(STR_MESSAGE, STR_NET_FAIL_SEND, 10*1000);
		}
		return ret;
	}

	if (0 >= (ret = APP_Network_Recv(PE_SendBuf, BufSize,20*1000, Full_CheckRecv)))
	{
		if(pTitle) 
		{
			char message[128] = {0};
			if ( ret == OPER_RET )
			{
				API_sprintf(message, "[%s]\n%s", STR_USER_CONCELL, STR_TRADE_RESULT_UNKOWN);
			}
			else 
			{
				API_sprintf(message, "[%s]\n%s", STR_NET_FAIL_RECV, STR_TRADE_RESULT_UNKOWN);
			}
			APP_ShowMsg(STR_MESSAGE, message, 10*1000);
		}
		return ret;
	}

	// 校验数据
	PE_SendBuf[ret] = '\0';
	if (OPER_OK != PE_LoadRecvData(PE_SendBuf)){
		if(pTitle) APP_ShowTradeMsg(STR_DATA_FORMAT_ERR, 5000);
		return OPER_ERR;
	}

	if (OPER_CRCERR == Conv_Sign_Check(PE_RecvTable,"key",g_ColData.key)){
		if(pTitle) APP_ShowTradeMsg(STR_SIGN_ERR, 5000);
		return OPER_CRCERR;
	} 
	return 0;
}

int FPS_SocketSend(void)
{	
	int ret;
	if (0 > (ret = APP_Network_Send(PE_SendBuf, pFlow.pMsgLen)))
	{
		if (ret != OPER_RET)
		{
			APP_ShowMsg(STR_MESSAGE, STR_NET_FAIL_SEND, 10*1000);
		}
		return ret;
	}
	return 0;
}

int FPS_SocketRecv(CHECK_DATA_FULL pCheckFull)
{	
	int ret;
	char message[128] = {0};
	if (0 >= (ret = APP_Network_Recv(PE_SendBuf, BufSize,20*1000, Full_CheckRecv)))
	{
		if ( ret == OPER_RET )
		{
			API_sprintf(message, "[%s]\n%s", STR_USER_CONCELL, STR_TRADE_RESULT_UNKOWN);
		}
		else 
		{
			API_sprintf(message, "[%s]\n%s", STR_NET_FAIL_RECV, STR_TRADE_RESULT_UNKOWN);
		}
		APP_ShowMsg(STR_MESSAGE, message, 10*1000);
		return -1;
	}
	// 校验数据
	if ( 0 != FPS_CheckRecvData(PE_SendBuf, ret) )
	{
		return -1;
	}
	return ret;
}


// 扫码收款组包
void ScanPack(void)
{
	//生成的tag
	SetServiceElementValue("unified.trade.micropay");
	GenerateOutTradeNo();
	GenerateNonceStr();
	GenerateTimeStart();
	SetMchCreateIp();

	//组请求报文
	TradeGet_start(HTTP_TRADE_ADDERR);
	SEND_ADD_ITEM(attach);
	SEND_ADD_ITEM(auth_code);
	SEND_ADD_ITEM(body);
	SEND_ADD_ITEM(charset);
	Send_add_item("device_info", g_ColData.term_sn);
	SEND_ADD_ITEM(mch_create_ip);
	SEND_ADD_ITEM(mch_id);
	SEND_ADD_ITEM(nonce_str);
	Send_add_item("op_device_id", g_ColData.term_sn);
	SEND_ADD_ITEM(op_shop_id);
	SEND_ADD_ITEM(op_user_id);
	SEND_ADD_ITEM(out_trade_no);
	SEND_ADD_ITEM(service);
	SEND_ADD_ITEM(sign_type);
	SEND_ADD_ITEM(time_start);	
	SEND_ADD_ITEM(total_fee);
	SEND_ADD_ITEM(version);
	SEND_ADD_SIGN(sign);
	TradeGet_End();
}

// 二维码支付组包
void QRcodePack(void)
{
	GenerateOutTradeNo();
	GenerateNonceStr();
	SetMchCreateIp();
	GenerateTimeStart();

	TradeGet_start(HTTP_TRADE_ADDERR);
	SEND_ADD_ITEM(attach);
	SEND_ADD_ITEM(body);
	SEND_ADD_ITEM(charset);
	SEND_ADD_ITEM(device_info);
	SEND_ADD_ITEM(mch_create_ip);
	SEND_ADD_ITEM(mch_id);
	SEND_ADD_ITEM(nonce_str);
	SEND_ADD_ITEM(notify_url);
	SEND_ADD_ITEM(op_user_id);
	SEND_ADD_ITEM(out_trade_no);
	SEND_ADD_ITEM(service);
	SEND_ADD_ITEM(sign_type);
	SEND_ADD_ITEM(time_start);	
	SEND_ADD_ITEM(total_fee);
	SEND_ADD_ITEM(version);
	SEND_ADD_SIGN(sign);
	TradeGet_End();
}

// 订单查询
void  QueryPack(void)
{	
	SetServiceElementValue("unified.trade.query");
	
	GenerateNonceStr();	//更新随机数
	TradeGet_start(HTTP_TRADE_ADDERR);
	SEND_ADD_ITEM(charset);
	SEND_ADD_ITEM(mch_id);
	SEND_ADD_ITEM(nonce_str);
	SEND_ADD_ITEM(out_trade_no);
	SEND_ADD_ITEM(service);
	SEND_ADD_ITEM(sign_type);
	SEND_ADD_ITEM(transaction_id);
	SEND_ADD_ITEM(version);
	SEND_ADD_SIGN(sign);
	TradeGet_End();  
}

// 订单查询2
void SubQueryPack(void)
{
	GenerateNonceStr();
	TradeGet_start(HTTP_TRADE_ADDERR);
	SEND_ADD_ITEM(charset);
	SEND_ADD_ITEM(mch_id);
	SEND_ADD_ITEM(nonce_str);
	SEND_ADD_ITEM(out_trade_no);
	SEND_ADD_ITEM(service);
	SEND_ADD_ITEM(sign_type);
	SEND_ADD_ITEM(version);
	SEND_ADD_SIGN(sign);
	TradeGet_End();
}

// 订单退款组包
void RefundedPack(void)
{  
	GenerateNonceStr();	//更新随机数
	GenerateOutRefundNo();
	SetServiceElementValue("unified.trade.refund");	

	TradeGet_start(HTTP_TRADE_ADDERR);
	SEND_ADD_ITEM(mch_id);
	SEND_ADD_ITEM(nonce_str);
	Send_add_item("op_user_id", g_ColData.mch_id); 
	SEND_ADD_ITEM(out_refund_no);
	SEND_ADD_ITEM(refund_fee);
	SEND_ADD_ITEM(service);
	SEND_ADD_ITEM(sign_type);
	SEND_ADD_ITEM(total_fee);
	SEND_ADD_ITEM(transaction_id);
	SEND_ADD_ITEM(version);
	SEND_ADD_SIGN(sign);
	TradeGet_End();
}

// 订单退款查询组包
void SUB_RefundedQueryPack(void)
{
	GenerateNonceStr();	//更新随机数
	TradeGet_start(HTTP_TRADE_ADDERR);
	SEND_ADD_ITEM(mch_id);
	SEND_ADD_ITEM(nonce_str);
	SEND_ADD_ITEM(out_refund_no);
//	SEND_ADD_ITEM(refund_id);
	SEND_ADD_ITEM(service);
	SEND_ADD_ITEM(sign_type);
	SEND_ADD_ITEM(transaction_id);
	SEND_ADD_SIGN(sign);
	TradeGet_End();
}

void CloseOrderPack(void)
{
	SetServiceElementValue("unified.trade.close");
	GenerateNonceStr();
	TradeGet_start(HTTP_TRADE_ADDERR);
	SEND_ADD_ITEM(charset);
	SEND_ADD_ITEM(mch_id);
	SEND_ADD_ITEM(nonce_str);
	SEND_ADD_ITEM(out_trade_no);
	SEND_ADD_ITEM(service);
	SEND_ADD_ITEM(sign_type);
	SEND_ADD_ITEM(version);
	SEND_ADD_SIGN(sign);
	TradeGet_End();
}


//===========PFS==============================
/*
<xml>
	<version>1.0</version>??
	<merchantId>181560000310</merchantId>??
	<orderRef>1020</orderRef>??
	<msgId>102340100</msgId>??
	<amount>1</amount>??
	<accessType>OFL</accessType>??
	<payMethod>FPS</payMethod>??
	<randStr>adf880d5c8986bd0deb6423c92c9d948</randStr>?
	<sign>1B5F7E3F8AFB2DFFD48D7EC0D69F5CC2178672A84EE1ACE98AAE88D40B88C479</sign>
	</xml>
*/
TrandInfoMsgQueue *PFS_ScanPack(const char *pTradeAddress)
{
	TrandInfoMsgQueue *pNode;
	pNode=CreateInfoMsgQueueNode();
	if(pNode == NULL) return NULL;
	//生成的tag
	GenerateOutTradeNo();
	GenerateNonceStr();
	//SetMchCreateIp();

	//组请求报文
	TradeGet_start(pTradeAddress);
	Send_add_item("accessType","OFL");
	Send_add_item("amount",g_ColData.total_fee);
	Send_add_item("merchantId",g_ColData.merchantId);
	Send_add_item("msgId",pNode->msgId);
	Send_add_item("orderRef",g_ColData.out_trade_no);
	Send_add_item("payMethod","FPS");
	Send_add_item("randStr",g_ColData.nonce_str);
	Send_add_item("version","1.0");
	Send_add_sha256sign("sign");
	TradeGet_End();
	return pNode;
}


void PFS_TradeQuery(const char *pTradeAddress,TrandInfoMsgQueue *pNode)
{
	GenerateNonceStr();
	//SetMchCreateIp();
	//组请求报文
	TradeGet_start(pTradeAddress);
	//Send_add_item("accessType","OFL");
	Send_add_item("merchantId",g_ColData.merchantId);
	Send_add_item("orderRef",pNode->orderRef);
	Send_add_item("payRef",pNode->payRef);
	Send_add_item("randStr",g_ColData.nonce_str);
	Send_add_item("version","1.0");
	Send_add_sha256sign("sign");
	TradeGet_End();
}



void PFS_FreePack(TrandInfoMsgQueue *pNode)
{
	if(pNode==NULL) return;
	FreeInfoMsgQueueNode(pNode);
}



int PE_PackData(int flow_tag)
{
	switch(flow_tag)
	{
		case FLOW_SCAN: 
			ScanPack();
			break;
		case FLOW_PAY: 
			QRcodePack();
			break;
		case FLOW_QUERY: 
			QueryPack();
			break;
		case FLOW_REFUND: 
			RefundedPack();
			break;
		case FLOW_CLOSE: 
			CloseOrderPack();
			break;
		default:
			return -1;
	}

	return 0;
}

int PE_CommProcess(char *pTitle, int flow_tag,  CHECK_DATA_FULL pCheckFull, char *msg)
{
	PE_PackData(flow_tag);
	if(0 != PE_SocketData(pTitle, Full_CheckRecv))
	{
		return -1;
	}
	return 0;
}

/*
void PE_ShowRefundAOK(char *pTradeMoney)
{
	UI_ShowBmpAndMoney(L"E:\\bmp\\RetOK.bin",pTradeMoney);
	API_GUI_Show();
}
*/
//--------收款 0，退款成功，1，退款提单成功 2----------------------
int SuccessTradeProcess(char *pStradeName)
{
	char sBuff[24];
	char *pDate,*pTmoney,*pTransaction_id,*pOut_refund_no=NULL;
	if(API_strcmp(pStradeName,ORDER_REFUND_APPLY)==0)
	{
		pTmoney=PE_GetRecvIdPar("refund_fee");
		APP_ShowRefundsOK(pTmoney);
		if(pTmoney==NULL) 
			return APP_WaitUiEvent(10*1000);
		pDate=PE_GetRecvIdPar("refund_time");
		pOut_refund_no=PE_GetRecvIdPar("out_refund_no");
	}
	else if(API_strstr(pStradeName,ORDER_REFUND))
	{
		pTmoney=PE_GetRecvIdPar("refund_fee_0");
		if(pTmoney==NULL)
			pTmoney=g_ColData.refund_fee;
		APP_ShowRefundsOK(pTmoney); 
		pDate=PE_GetRecvIdPar("refund_time_0");
		pOut_refund_no=PE_GetRecvIdPar("out_refund_no_0");
	}
	else	//--收款
	{
		pTmoney=PE_GetRecvIdPar("total_fee");
		if(pTmoney==NULL)
			pTmoney=g_ColData.total_fee;
		APP_ShowTradeOK(pTmoney);
		pDate=PE_GetRecvIdPar("time_end");
	}
	//---------------------------------------------
	Conv_TmoneyToDmoney(sBuff,pTmoney);
#ifdef INTERNATIONAL_VERSION
	APP_AudioDtmfPlay(DTMF_letterB, 2);
#else
	APP_TTS_PlayText("%s%s元",pStradeName,sBuff);
#endif
	if(pDate)
	{//--------自动更新时间-------
		//20180423112758
		API_memcpy(sBuff   ,pDate	,4);
		API_memcpy(sBuff+5 ,pDate+4 ,2);
		API_memcpy(sBuff+8 ,pDate+6 ,2);
		API_memcpy(sBuff+11,pDate+8 ,2);
		API_memcpy(sBuff+14,pDate+10,2);
		API_memcpy(sBuff+17,pDate+12,2);
		//2018 03 08 17 03 43
		sBuff[4]='-';
		sBuff[7]='-';
		sBuff[10]=' ';
		sBuff[13]=':';
		sBuff[16]=':';
		sBuff[19]='\0';
		SetSysDateTime(sBuff);
		//2018-03-08 17:03:43
		pDate=sBuff;
	}
	if(pDate==NULL)
	{
		GetSysDateTime(sBuff,"%04d-%02d-%02d %02d:%02d:%02d");
		pDate=sBuff;
	}
	pTransaction_id=PE_GetRecvIdPar("transaction_id");
	if(pTransaction_id==NULL)
		pTransaction_id=g_ColData.transaction_id;
	insertHeadNodes(pTmoney,pDate,pStradeName,pTransaction_id,pOut_refund_no);// 保存于本地明细查询
	return APP_WaitUiEvent(10*1000);
}

int SuccessTradeSaveFPS(char *pStradeName)
{
	char sBuff[24];
	char *pDate,*pTmoney,*pTransaction_id;
	//--------------交易成功提示---------------------
	pTmoney=PE_GetRecvIdPar("amount");								
	if(pTmoney==NULL)
		pTmoney=g_ColData.total_fee;
	APP_ShowTradeOK(pTmoney);
	//---------------------------------------------
	Conv_TmoneyToDmoney(sBuff,pTmoney);
#ifdef INTERNATIONAL_VERSION
	APP_AudioDtmfPlay(DTMF_letterB, 2);
#else
	APP_TTS_PlayText("%s%s元",pStradeName,sBuff);
#endif
	pDate=PE_GetRecvIdPar("sysTransTime");
	if(pDate)
	{//--------自动更新时间-------
		//20180423112758
		API_memcpy(sBuff   ,pDate	,4);
		API_memcpy(sBuff+5 ,pDate+4 ,2);
		API_memcpy(sBuff+8 ,pDate+6 ,2);
		API_memcpy(sBuff+11,pDate+8 ,2);
		API_memcpy(sBuff+14,pDate+10,2);
		API_memcpy(sBuff+17,pDate+12,2);
		//2018 03 08 17 03 43
		sBuff[4]='-';
		sBuff[7]='-';
		sBuff[10]=' ';
		sBuff[13]=':';
		sBuff[16]=':';
		sBuff[19]='\0';
		//2018-03-08 17:03:43
		pDate=sBuff;
	}
	if(pDate==NULL)
	{
		GetSysDateTime(sBuff,"%04d-%02d-%02d %02d:%02d:%02d");
		pDate=sBuff;
	}
	pTransaction_id=PE_GetRecvIdPar("orderRef");
	if(pTransaction_id==NULL)
		pTransaction_id=g_ColData.transaction_id;
	insertHeadNodes(pTmoney,pDate,pStradeName,pTransaction_id,NULL);// 保存于本地明细查询
	return APP_WaitUiEvent(10*1000);
}


int FailedTradeProcess(char* pCode)
{
	int retlen;
	char msg[128];
	retlen=API_sprintf(msg,"%s[ %s ]\n",STR_RUTURN_CODE, pCode);
	if(NULL!=(pCode=PE_GetRecvIdPar("err_msg")))
	{
		API_Utf8ToGbk(msg+retlen,sizeof(msg)-retlen,pCode);
	}
	return APP_ShowTradeMsg(msg,20*1000); 
}


int CUP_QueryResult(int timeOutMs)
{
	u32 event;
	int ret=PAY_TIMEOUTS;
	int CruTimeMs=API_TimeCurrMS();
	timeOutMs += CruTimeMs;
	event=API_WaitEvent(5000,EVENT_UI,EVENT_NONE);
	if(event == EVENT_CANCEL)
	{
		return OPER_RET;
	}
	
	SetServiceElementValue("unified.trade.query");
	APP_SetKeyAccept(0x03);
	while(CruTimeMs < timeOutMs)
	{
		event=API_WaitEvent(1000,EVENT_UI,EVENT_NONE);
		if(event == EVENT_CANCEL)
		{
			ret=OPER_RET;
			break;
		}
		SubQueryPack();
		ret=PE_SocketData(NULL, Full_CheckRecv);
		if (ret < 0)
		{
			TRACE("->>>>>PE_SocketData[%d]>>>>#####ERR\r\n",ret);
			Tcp_Close(NULL);
			ret=Tcp_Link(NULL);
			TRACE("->>>>>Re Tcp_Link>>>>[%d]\r\n",ret);
			if(ret < 0)
				break;
		}
		if(IsStatusSucceed())
		{	
			if(PE_CheckRecvIdPar("result_code","0") == 0)
			{
				char *trade_state;
				trade_state=PE_GetRecvIdPar("trade_state");
				if(trade_state)
				{
					TRACE("----->>>>>trade_state>>>>[%s]\r\n",trade_state);
					if(API_strcmp(trade_state,"SUCCESS")==0)
					{
						ret=PAY_SUCCESS;
						break;
					}
					if(API_strcmp(trade_state,"PAYERROR")==0)
					{
						ret=PAY_FAILED;
						break;
					}					
				}
			}
		}	
		CruTimeMs=API_TimeCurrMS();
	}
	APP_SetKeyAccept(0x00);
	return ret;	
}

//===================二维码显示====================================
void PE_ShowQRcodeDis(char *pQRcode,char *pTradeMoney)
{
	RECTL	Rect;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	UI_ShowPictureFile(&Rect,"QRcode.clz");

	Rect.left	= UI_QR_CODE_X;
	Rect.top	= UI_QR_CODE_Y;
	Rect.width	= UI_QR_CODE_W;
	Rect.height = UI_QR_CODE_H;
	API_GUI_Draw565QRcode(&Rect,pQRcode,RGB565_BLACK);
	if(pTradeMoney)
	{
		POINT tFontXY;
		u16 width;
		char sShowStr[14];
		API_strcpy(sShowStr,"HK$");
		width=Conv_TmoneyToDmoney(sShowStr+3,pTradeMoney);
		width=(width+3)*FONT_SIZE/2;
		tFontXY.left =UI_QR_MONEY_X+ (UI_QR_MONEY_W-width)/2;
		tFontXY.top =UI_QR_MONEY_Y;
		UI_SetColorRGB565(RGB565_BLACK,RGB565_PARENT);
		UI_DrawString(&tFontXY,sShowStr);
	}
	API_GUI_Show();
}

int ShowResultFailMsg(int timeOutMs)
{
	API_GUI_CreateWindow("Transaction",TOK,TCANCEL,0);
	API_GUI_OprInfo("Query again?if \'No\',please visit international Mobile Payment Platform to search result","Yes or No");
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_BORDER,"again");
	API_GUI_Show();
	return APP_WaitUiEvent(timeOutMs);
}
/**
 * <定时查询订单结果>
 * 
 * @param tTimeOutMS 查询超时时间
 * 
 * @return 0 查询成功, -1 通讯异常， -2查询超时
 */
 /*
int QueryTradeOrder(int tTimeOutMS)
{      
	int ret;
	ret=CUP_QueryResult(tTimeOutMS);
	if(ret== PAY_SUCCESS)
	{
		ShowSucceedTrade();
	}
	else if(ret!= OPER_RET)
	{
		if(EVENT_OK == ShowResultFailMsg('P',20*1000))
		{
			ret=PAY_QUERY;
		}
		//ShowReturnMessage();
	}
	return ret;
}	
*/
	

/**
 * <关闭订单>
 * 二维码支付流程，支付超时，调用关单接口
 * 
 */
int CloseOrderFlow(int LinkFlag)
{
	if(LinkFlag)
	{
		if (0 != PE_Connect(STR_CLOSE_ORDER,HTTP_TRADE_ADDERR,HTTP_TRADE_PORT)){
			return -1;
		}
		DataInit();
	}
	CloseOrderPack(); // 组建数据包,发送请求
	if (0 == PE_SocketData(" ", Full_CheckRecv))
	{
		PE_ReadRecvIdPar("transaction_id",g_ColData.transaction_id,
					sizeof(g_ColData.transaction_id));
		/*
		if(!IsTradeSucceed())
		{
			ShowReturnMessage(); // 保存订单号,检查交易结果
		}*/
	}
	if(LinkFlag)
	{
		DataFree();
		Tcp_Close(NULL);
	}
	return 0;
}

/**
 * <流程开始检查终端参数>
 *
 * @return 0 参数正常， -1 参数异常
 */
int CheckParamPreFlow(void)
{
	if (0 != GetTermSN())
	{
		APP_ShowMsg(STR_MESSAGE, STR_NO_WRITE_SN, 5*1000);
		return -1;
	}

	if(CheckMchidIsNull())
	{
		APP_ShowMsg(STR_MESSAGE, STR_INPUT_MERCHANT_INFO, 5*1000); 
		return -1;
	}

	return 0;
}


/**
 * <扫码收款>
 *. 
 * @author  pangrenxuan
 * @date  20180425
 */
int SweepFlow(char *pTitle)
{
	int ret=0;
	if(0 != InputTotalFee(pTitle)){
		return -1;
	}

	if(0 != CheckParamPreFlow())
	{
		return -1;
	}

	if(0 != ScanAuthCode())
	{
		return -1;
	}
	
	if (0 != PE_Connect(" ",HTTP_TRADE_ADDERR,HTTP_TRADE_PORT))
	{
		return -1;
	}
	
	DataInit();
	
	while(0 == PE_CommProcess(pTitle, FLOW_SCAN, Full_CheckRecv, NULL))
	{
		// 保存订单号,检查交易结果
		PE_ReadRecvIdPar("transaction_id", g_ColData.transaction_id, sizeof(g_ColData.transaction_id));

		if(API_memcmp(PE_GetRecvIdPar("status"),"0",1)==0)
		{    
			if(API_memcmp(PE_GetRecvIdPar("result_code"),"0",1)==0)
			{    
				ShowSucceedTrade();
			}
			else if(IsTradeNeedQuerry())
			{
				ret=CUP_QueryResult(60*1000);
				if(ret== PAY_SUCCESS)
				{
					ShowSucceedTrade();
				}
				else if(ret== PAY_FAILED)
				{
					APP_ShowTradeFA(NULL,10*1000);
					//CloseOrderFlow();
				}
				else if(ret!= OPER_RET)
				{
					if(EVENT_OK == ShowResultFailMsg(20*1000))
					{
						//ret=PAY_QUERY;
						APP_ShowWaitFor("Query again");
						continue;
					}
				}
			}
			else
				ShowReturnMessage();
		}
		else
		{
			ShowReturnMessage();
		}
	/*
		if(0==IsTradeSucceed())
		{	
			ShowSucceedTrade();
		}
		else
		{
			if(IsTradeNeedQuerry())
			{
				ret=CUP_QueryResult(60*1000);
				if(ret== PAY_SUCCESS)
				{
					ShowSucceedTrade();
				}
				else if(ret== PAY_FAILED)
				{
					APP_ShowTradeFA(NULL,10*1000);
					//CloseOrderFlow();
				}
				else if(ret!= OPER_RET)
				{
					if(EVENT_OK == ShowResultFailMsg('P',20*1000))
					{
						//ret=PAY_QUERY;
						APP_ShowWaitFor("Query again");
						continue;
					}
				}
			}
			else
				ShowReturnMessage();
		}
		*/
		break;
	}

	DataFree();
	Tcp_Close(pTitle);
	/*
	if(ret==PAY_QUERY)
	{
		QueryFlow(ORDER_QUERY);
	}
	*/
	return 0;
}

// 二维码收款 
int QRcodeFlow(char*  pTitle)
{      
	if(0 != CheckParamPreFlow())
	{
		return -1;
	}
	if (0 != PE_Connect(" ",HTTP_TRADE_ADDERR,HTTP_TRADE_PORT))
	{
		return -1;
	}
	DataInit();
	if(0 == PE_CommProcess(pTitle, FLOW_PAY, Full_CheckRecv, NULL))
	{
		//判断二维码报文获取是否成功
		if (0==IsTradeSucceed())
		{
			if(0 == ShowQRCode()){
				PE_ReadRecvIdPar("transaction_id", g_ColData.transaction_id, sizeof(g_ColData.transaction_id));
				if(PAY_SUCCESS == CUP_QueryResult(60*1000))
				{
					ShowSucceedTrade();
				}
				else //if (0 > QueryTradeOrder(60*1000))
				{
					CloseOrderFlow(0);
				}
			}
		}
		else
		{
			ShowReturnMessage();
		}
	}
	DataFree();
	Tcp_Close(pTitle);
	return 0;
}	

// 二维码收款 (微信被扫)
int QrTypeWX(char*  pTitle)
{
#ifndef INTERNATIONAL_VERSION
	SetServiceElementValue("pay.weixin.native");
#else
	SetServiceElementValue("pay.weixin.native.intl");
#endif
	QRcodeFlow(pTitle);
	return 0;
}


// 二维码收款 (支付宝被扫)
int QrTypeZFB(char*  pTitle)
{
#ifndef INTERNATIONAL_VERSION
	SetServiceElementValue("pay.alipay.native");
#else
	SetServiceElementValue("pay.alipay.native.intl");
#endif
	QRcodeFlow(pTitle);
	return 0;
}

// 二维码收款 (银联被扫)
int QrTypeUN(char*  pTitle)
{
#ifndef INTERNATIONAL_VERSION
	SetServiceElementValue("pay.unionpay.native");
#else
	SetServiceElementValue("pay.upi.native.intl");
#endif
	QRcodeFlow(pTitle);
	return 0;
}

char* SubPfsTradeQuery(char* pOrderRef)
{
	TrandInfoMsgQueue *pTrandNode;
	char *respCode=NULL;
	char *AddressHttp=HTTP_TRADE_PFS_ADDERR"/unifiedQuery";
	APP_Network_Disconnect(5*1000);
	DataFree();
	if (0 != PE_Connect(NULL,AddressHttp,HTTP_TRADE_PFS_PORT)) return NULL;
	DataInit();
	pTrandNode=CreateInfoMsgQueueNode();
	while(pTrandNode)
	{
		API_strcpy(pTrandNode->orderRef,pOrderRef);
		//------------------------------------
		PFS_TradeQuery(AddressHttp,pTrandNode);
		if(FPS_SocketSend() < 0)
		{
			APP_ShowTradeMsg(STR_NET_CENTER_FAIL,3*1000); 
			break;
		}
		if(FPS_SocketRecv(Full_CheckRecv) <= 0)
		{
			APP_ShowTradeMsg(STR_NET_CENTER_FAIL,20*1000);
			break;
		}
		respCode=PE_GetRecvIdPar("respCode");	
		break;
	}
	PFS_FreePack(pTrandNode);
	
	return respCode;
}
int QrTypeFPS(char*  pTitle)
{	  
	TrandInfoMsgQueue *pTrandNode;
	char *AddressHttp = HTTP_TRADE_PFS_ADDERR"/unifiedPrePay";
	int timeOutMs=2*60*1000;
	u16	TrandType,RecvErrTimes=0;
	//https://pay.wepayez.com/pay/unifiedQuery
	if (0 == API_strlen(g_ColData.merchantId))
	{
		APP_ShowMsg(STR_MESSAGE, STR_INPUT_MERCHANT_INFO, 5*1000); 
		return -1;
	}
	if (0 != PE_Connect("",AddressHttp,HTTP_TRADE_PFS_PORT)){
	 	return -1;
	}
	DataInit();
	pTrandNode=PFS_ScanPack(AddressHttp);
	TrandType=0;
	APP_ScreenSleep(FALSE);
	while(1)	
	{
		if(timeOutMs < 0)
		{//---超时退出---------------
			APP_ShowTradeMsg(STR_QUERY_TIMEOUTS,10*1000); 
			break;
		}
		if(TrandType)
		{
			u32 event;
			//-------断开前面的连接--------------------
			Tcp_Close(pTitle);
			if(TrandType==1)
			{
				PE_ReadRecvIdPar("orderRef",pTrandNode->orderRef, sizeof(pTrandNode->orderRef));
				PE_ReadRecvIdPar("payRef",pTrandNode->payRef, sizeof(pTrandNode->payRef));
				//--------切换地址重连--------------
				AddressHttp=HTTP_TRADE_PFS_ADDERR"/unifiedQuery";

				event=API_WaitEvent(5*1000,EVENT_UI,EVENT_NONE);
				timeOutMs -= 5*1000;
			}
			else
			{
				event=API_WaitEvent(1000,EVENT_UI,EVENT_NONE);
				timeOutMs -= 1000;
			}
			if(event == EVENT_CANCEL) break;
			
			//------连接查询地址--------------------------
			if (0 != PE_Connect(NULL,AddressHttp,HTTP_TRADE_PFS_PORT)) break;
			//------------------------------------
			PFS_TradeQuery(AddressHttp,pTrandNode);
			TrandType++;
		}

		if(FPS_SocketSend() < 0)
		{
			APP_ShowTradeMsg(STR_NET_CENTER_LINK,3*1000); 
			break;
		}
		if(FPS_SocketRecv(Full_CheckRecv) <= 0)
		{
			RecvErrTimes++;
			if(RecvErrTimes>2) 
			{
				APP_ShowTradeMsg("Not receive the transaction result\nplease confirm by querying the transaction",20*1000);
				break;
			}
		}
		else 
		{
			RecvErrTimes=0;
		}
		//判断二维码报文获取是否成功
		{
			char *respCode;
			if(NULL != (respCode=PE_GetRecvIdPar("respCode")))
			{
				if(API_memcmp(respCode,"0000",4)==0)
				{//交易成功
					if(TrandType == 0)
					{//--------获取二维码--------------------
						char *msgId;	
						msgId = PE_GetRecvIdPar("msgId");
						if(API_strcmp(msgId,pTrandNode->msgId)==0)
						{
							char *qrCode;
							if(NULL != (qrCode=PE_GetRecvIdPar("qrCode")))
							{
								PE_ShowQRcodeDis(qrCode, g_ColData.total_fee);
								TRACE("code_url:%s \r\n",qrCode);
								TrandType++;
								continue;
							}
							else 
							{
								APP_ShowTradeMsg(STR_DATA_FORMAT_ERR,10*1000); 
								break;
							}
						}
						else
						{
							//FPS_SocketRecv(Full_CheckRecv);
							TRACE("-->>交易中msgId对应不上\r\n");
							continue;
						}	
					}
					else
					{//-----------查结果---------------------------------
						char *msgId;
						char *pTradeState;
						pTradeState = PE_GetRecvIdPar("tradeState");
						if(API_memcmp(pTradeState,"NOTPAY",6)==0)
							continue;
						
						msgId = PE_GetRecvIdPar("msgId");
						if(API_strcmp(msgId,pTrandNode->msgId)==0)
						{
							if(API_memcmp(pTradeState,"SUCCESS",7)==0)
							{
								SuccessTradeSaveFPS("FPS Pay");
							}
							else 
							{
								APP_ShowTradeMsg(pTradeState,5*1000); 
							}
						/*
							char *pAmount,*pCurrCode; 
							pAmount=PE_GetRecvIdPar("amount");
							pCurrCode=PE_GetRecvIdPar("currCode");
							if(pAmount!=NULL)
							{
								if(pCurrCode!=NULL)
								{
									char buffamout[24];
									char sShowStr[12];
									Conv_TmoneyToDmoney(sShowStr,pAmount);
									API_sprintf(buffamout,"%s %s",pCurrCode,sShowStr);
									APP_ShowTradeOK(buffamout);
								}
								else
								{
									APP_ShowTradeOK(pAmount);
								}
								APP_WaitUiEvent(10*1000);
							}
							else 
							{
								APP_ShowTradeMsg("结果无交易金额",5*1000); 
							}
							*/
						}
						else
						{
							//FPS_SocketRecv(Full_CheckRecv);
							TRACE("-->>查msgId对应不上\r\n");
							continue;
						}		
					}
				}
				else
				{
					char msg[256];
					int len;
					char *errorDetail;
					len = API_sprintf(msg, "返回码[%s]\n", respCode);
					errorDetail = PE_GetRecvIdPar("errorDetail");
					if ( errorDetail )
						API_Utf8ToGbk(msg + len, sizeof(msg)-len, errorDetail);
					APP_ShowMsg(STR_MESSAGE, msg,10*1000);
					break;
				}
			}
		}
		break;
	}
	APP_ScreenSleep(TRUE);
	PFS_FreePack(pTrandNode);
	DataFree();
	Tcp_Close(pTitle);
	return 0;
}



// 二维码收款 (支付宝被扫)
int QrCodePaymentAlipay(char*  pTitle)
{
	int ret;
	if(OpenAPN(pTitle))	{
		APP_ShowNoSignel(NULL, 3*1000);
		return -1;
	}
	CLEAR(g_ColData.total_fee);
	ret=APP_EditSum(pTitle,'D',g_ColData.total_fee,30*1000);
	if(ret <= 0) return ret;
	if(Tcp_Link(pTitle)) 
	{
		APP_ShowMsg(STR_MESSAGE, STR_NET_ERR_LINK, 10*1000);
		return -1;
	}
	return QrTypeZFB(pTitle);
}

// 二维码收款 (微信被扫)
int QrCodePaymentWechat(char*  pTitle)
{
	int ret;
	if(OpenAPN(pTitle)) 
	{
		APP_ShowNoSignel(NULL, 3*1000);
		return -1;
	}
	CLEAR(g_ColData.total_fee);
	ret=APP_EditSum(pTitle,'D',g_ColData.total_fee,30*1000);
	if(ret <= 0) return ret;
	if(Tcp_Link(pTitle))  
	{
		APP_ShowMsg(STR_MESSAGE, STR_NET_ERR_LINK, 10*1000);
		return -1;
	}
	return QrTypeWX(pTitle);
}

int PE_CamScan(char * pTitle,char* pHintOrTMoney,char *pOutCode,int MinLen,int MaxLen,int timeOutMs)
{
	u16 	flagKey=0x00,Width;
	char 	sShowStr[12];
	RECTL	Rect;
	
	Rect.left	= UI_MAP_TITLE_X;
	Rect.top	= UI_MAP_TITLE_Y;
	Rect.width	= UI_MAP_TITLE_W;
	Rect.height = UI_MAP_TITLE_H;

	{
		POINT	rclTrg;
		pGuiFun->FillRect(&Rect,RGB565(35,35,35));
		Width = API_strlen(pTitle)*FONT_SIZE/2;
		rclTrg.left	= Rect.left;
		rclTrg.top	= Rect.top;
		if(Width < Rect.width)
			rclTrg.left=Rect.left+(Rect.width-Width)/2;
		else rclTrg.left=Rect.left;
		rclTrg.top =Rect.top+(Rect.height-FONT_SIZE)/2;
		UI_SetColorRGB565(RGB565_WITHE,RGB565(35,35,35));
		UI_DrawString(&rclTrg,pTitle);
	}
	
	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	
	UI_ShowPictureFile(&Rect,"ScanIpt.clz");
	//UI_ShowPictureFile(&Rect,L"E:\\bmp\\ScanCod.bin");
	Rect.top	= UI_SCAN_TEXT_Y;
	flagKey	= 0x02;
	
	if(pHintOrTMoney)
	{
		Rect.left	= UI_EDIT_sMONEY_X;
		Rect.width	= UI_EDIT_sMONEY_W;
		Rect.height = UI_EDIT_sMONEY_H;
		if(pHintOrTMoney[0]>='0' && pHintOrTMoney[0]<='9')
		{
			Conv_TmoneyToDmoney(sShowStr,pHintOrTMoney);
			UI_ShowSmallNum(&Rect,1,sShowStr);
		}
		else
		{
			POINT rclTrg;
			Width = API_strlen(pHintOrTMoney)*FONT_SIZE/2;
			if(Width < Rect.width)
				rclTrg.left=Rect.left+(Rect.width-Width)/2;
			else rclTrg.left=Rect.left;
			rclTrg.top =Rect.top;
			UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
			UI_DrawString(&rclTrg,pHintOrTMoney);
		}
	}
	API_GUI_Show();	
	return APP_OnlyCamScan(flagKey,MinLen,MaxLen,pOutCode,timeOutMs);
}


// 查询
int QueryFlow(char* pTitle)
{
	int	ret;

	ret=PE_CamScan(pTitle, NULL, g_ColData.transaction_id, 10, 32, 20*1000);
	if(ret<0) return -1;
	if(ret == OPER_HARD || ret == OPER_NEW)
	{
		g_ColData.transaction_id[0]='\0';	//不能将上面的结果带下来。
		ret = APP_InputMerchSN('Q', g_ColData.transaction_id, 10, 32, 20*1000);
		if(ret<0) return -1;
	}
	if (0 != PE_Connect(" ",HTTP_TRADE_ADDERR,HTTP_TRADE_PORT))
	{
		return -1;
	}
	DataInit();
	if(0 == PE_CommProcess(pTitle, FLOW_QUERY, Full_CheckRecv, NULL))
	{
		ShowOrderInfo();
	}
	Tcp_Close(pTitle);
	DataFree();
	
	return 0;
}
int QueryRefundResult(char* pTitle)
{      
	int ret=PAY_TIMEOUTS;
	ret=PE_CamScan(pTitle,NULL,g_ColData.transaction_id,8,32,20*1000);
	if(ret<0) return -1;
	if(ret==OPER_HARD)
	{
		g_ColData.transaction_id[0]='\0';	//不能将上面的结果带下来。
		ret=APP_InputMerchSN('R',g_ColData.transaction_id,10,32,20*1000);
		if(ret<0) return -1;
	}
	if(0 != PE_Connect(" ",HTTP_TRADE_ADDERR,HTTP_TRADE_PORT))
	{
		return -1;
	}
	DataInit();
	{
		int i=1;
		TradeRecordItem* pItem;
		g_ColData.out_refund_no[0]='\0';
		while(1)
		{//避免想同编号存入其中
			pItem=GetTradeRecord(i++);
			if(pItem==NULL) break;
			if(API_strcmp(pItem->order,g_ColData.transaction_id)==0)
			{
				API_strcpy(g_ColData.out_refund_no,pItem->out_refund_no);
				break;
			}
		}
	}
	SetServiceElementValue("unified.trade.refundquery");	
	SUB_RefundedQueryPack();
	ret=PE_SocketData(pTitle, Full_CheckRecv);
	if (ret >= 0)
	{
		if(IsTradeSucceed() == 0)
		{	
			char *prefund_status_0 = PE_GetRecvIdPar("refund_status_0");
			ret= PAY_NOTSURE;
			if(prefund_status_0)
			{
				if (API_strcmp(prefund_status_0, "SUCCESS") == 0)
				{
					SuccessTradeProcess(ORDER_REFUND);
					ret= PAY_SUCCESS;
				}
				else if(API_strcmp(prefund_status_0, "FAILED") == 0 )
				{	
					APP_ShowMsg(STR_ORDER_RERUND_FAILED,STR_CONTACT_WORKER,10*1000);
					//APP_ShowTradeFA(STR_ORDER_RERUND_FAILED##"\n\n"##STR_CONTACT_WORKER,10*1000);
					ret= PAY_FAILED;
				}
				else if(API_strcmp(prefund_status_0, "PROCESSING") == 0 )
				{
					TRACE("Query RefundStatus->PAY_PROCESSING\r\n");
					//APP_ShowMsg(STR_ORDER_RERUND_PROCESSING,STR_CONTACT_WORKER,10*1000);
					APP_ShowTradeMsg(STR_ORDER_RERUND_PROCESSING,10*1000);
					ret=PAY_PROCESSING;
				}
				else
				{	
					TRACE("Query RefundStatus->%s\r\n",prefund_status_0);
					APP_ShowTradeMsg(prefund_status_0,10*1000);
					ret=PAY_NOTSURE;
				}
			}
		}
		else 
		{// 交易错误提示
			FailedTradeProcess(PE_GetRecvIdPar("result_code"));
		}
	}
	DataFree();
	Tcp_Close(pTitle);
	return ret;
}

int FPS_QueryFlow(char* pTitle)
{
	int	ret;
	TrandInfoMsgQueue TrandNode={0};
	char showBuff[1024];
	char *respCode;
	do{
		ret=PE_CamScan(pTitle, NULL, TrandNode.orderRef, 10, 32, 20*1000);
		if(ret<0) return -1;
		if(ret == OPER_HARD || ret == OPER_NEW)
		{
			TrandNode.orderRef[0]='\0';	//不能将上面的结果带下来。
			ret = APP_InputMerchSN('Q', TrandNode.orderRef, 10, 32, 20*1000);
			if(ret<0) return -1;
		}
		//------连接查询地址--------------------------
		if (0 != PE_Connect("",HTTP_TRADE_PFS_ADDERR"/unifiedQuery",HTTP_TRADE_PFS_PORT))
			return -1;

		DataInit();
		//------------------------------------
		PFS_TradeQuery(HTTP_TRADE_PFS_ADDERR"/unifiedQuery",&TrandNode);

		if(FPS_SocketSend() < 0)
		{
			APP_ShowTradeMsg(STR_NET_CENTER_LINK,3*1000); 
			break;
		}
		if(FPS_SocketRecv(Full_CheckRecv) <= 0)
			break;
		
		if(NULL != (respCode=PE_GetRecvIdPar("respCode")))
		{
			if(API_memcmp(respCode,"0000",4)==0)
			{//交易成功
				//-----------查结果---------------------------------
				char *pData,*pType; 
				int offset=0;
				pData = PE_GetRecvIdPar("tradeState");
				if(pData)
				{
					offset += API_sprintf(showBuff+offset,"tradeState:%s\n",pData);
				}
				pData = PE_GetRecvIdPar("payMethod");
				if(pData)
				{
					offset += API_sprintf(showBuff+offset,"payMethod:%s\n",pData);
				}
				pData = PE_GetRecvIdPar("amount");
				pType = PE_GetRecvIdPar("currCode");
				if(pData)
				{
					offset += API_sprintf(showBuff+offset,"amount:%s %s\n",pType,pData);
				}
				
				if(NULL != (pData = PE_GetRecvIdPar("accessType")))
					offset += API_sprintf(showBuff+offset,"accessType:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("channelOrderRef")))
					offset += API_sprintf(showBuff+offset,"channelOrderRef:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("payerCurrency")))
					offset += API_sprintf(showBuff+offset,"payerCurrency:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("payerCurrencyAmt")))
					offset += API_sprintf(showBuff+offset,"payerCurrencyAmt:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("payerCurrencyExchangeRate")))
					offset += API_sprintf(showBuff+offset,"payerCurrencyExchangeRate:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("convTransAmt")))
					offset += API_sprintf(showBuff+offset,"convTransAmt:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("convTransCurrency")))
					offset += API_sprintf(showBuff+offset,"convTransCurrency:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("convTransExchangeRate")))
					offset += API_sprintf(showBuff+offset,"convTransExchangeRate:%s\n",pData);
				if(NULL != (pData = PE_GetRecvIdPar("conRateDate")))
					offset += API_sprintf(showBuff+offset,"conRateDate:%s\n",pData);
			}
			else
			{
				int len;
				char *errorDetail;
				len = API_sprintf(showBuff, "返回码[%s]\n", respCode);
				errorDetail = PE_GetRecvIdPar("errorDetail");
				if ( errorDetail )
					API_Utf8ToGbk(showBuff + len, sizeof(showBuff)-len, errorDetail);
			}
			APP_ShowInfo(pTitle,showBuff,30*1000);
		}
		else 
		{
			APP_ShowMsg(STR_MESSAGE, "No respCode",5*1000);
		}
	}while(0);
	DataFree();
	Tcp_Close(pTitle);
	return 0;
}

/**
 * <退款查询>
 *
 * @return  0 查询成功, 1 需再次查询,  -1 其他

int RefundQueryFlow(char* pTitle)
{
	char *prefund_status_0 = NULL;
	SetServiceElementValue("unified.trade.refundquery");
	do {
		SUB_RefundedQueryPack();
		if(PE_SocketData(pTitle,Full_CheckRecv)) 
		{
			return -1;
		}

		if(IsTradeSucceed())
		{	
			prefund_status_0 = PE_GetRecvIdPar("refund_status_0");
			TRACE_HEX("prefund_status_0", prefund_status_0, 64);
			if (API_strcmp(prefund_status_0, "SUCCESS") == 0)
			{
				SuccessTradeProcess(ORDER_REFUND);
			}
			else if (API_strcmp(prefund_status_0, "PROCESSING") == 0)
			{	
				APP_ShowMsg(STR_MESSAGE, STR_ORDER_RERUND_PROCESSING, 10*1000);
			}
			else if(API_strcmp(prefund_status_0, "NOTSURE") == 0)
			{
				return 1;
			}
		}
		else 
		{	
			ShowReturnMessage();
		}
	}while(0);

	return 0;
}
*/ 

int SubRefundTrade(char* pTitle,char* ptransaction_id,char* pMoney)
{
	CLEAR(g_ColData.refund_fee);
	do{
		if(ptransaction_id)
		{
			if(ptransaction_id != g_ColData.transaction_id)
			API_strcpy(g_ColData.transaction_id,ptransaction_id);
		}

		if(pMoney)
		{
			API_strcpy(g_ColData.total_fee,  pMoney);
			API_strcpy(g_ColData.refund_fee,  pMoney);
		}
	
		// 请输入退款金额
		if(0 > APP_EditSum(pTitle,'R', g_ColData.refund_fee, 10*1000)) 
		{
			return OPER_RET;
		}	
		APP_ShowWaitRef(g_ColData.refund_fee);
		DataInit();
		RefundedPack();
		if (0 != PE_SocketData(pTitle, Full_CheckRecv) )
		{
			break;
		}
		if(0==IsTradeSucceed())
		{
			if (PE_CheckRecvIdPar("refund_status","SUCCESS") == OPER_OK)
			{
				SuccessTradeProcess(ORDER_REFUND);
			}
			else
			{
				SuccessTradeProcess(ORDER_REFUND_APPLY);
				//PE_ShowRefundAOK(PE_GetRecvIdPar("refund_fee"),10*1000);
				//APP_ShowTradeMsg("Refund apply success",10*1000);
			}
			//APP_ShowRefundsOK("Refund apply success"); 
		//	SuccessTradeProcess(ORDER_REFUND);
		}
		else
		{
			ShowReturnMessage();
		}
		// 找到应答码
		/*
		pCode=PE_GetRecvIdPar("result_code");
		if(pCode && API_memcmp(pCode, "0", 1) == 0)
		{	
			SAVE_DATA_ITEM(refund_id);
			SAVE_DATA_ITEM(out_refund_no);
			return QueryRefundStatus(60*1000);
		}
		ShowReturnMessage();
		*/
		
	}while(0);
	return PAY_SUCCESS;
}

int PE_InputAccessCode(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pkey)
{
	char pOutMsg[40]={0};
	EDIT_DATA tEdit;
	int ret;

	tEdit.pTitle		=pTitle;
	tEdit.pFrontText	=pFrontTextBuf;
	tEdit.pAfterText	=pAfterTextBuf;
	tEdit.Way			=IME_NUM|IME_PIN_MODE;
	tEdit.Limit			=IME_NUM|IME_PIN_MODE;
	tEdit.Min			=1;
	tEdit.Max			=32;
	tEdit.timeOutMs=20*1000;
	ret=APP_Edit(&tEdit,pOutMsg);
	if(ret>=  tEdit.Min)
	{
		if(API_strcmp(pOutMsg,pkey)==0) return 0;

		APP_ShowMsg(pTitle,STR_ACCESS_CODE_ERR,3000);	
	}
	return -1;
}

// 退款 先查询得到退款号，再退款
int RefundFlow(char* pTitle)	
{
	int ret;

	if(0 != CheckParamPreFlow())
	{
		return -1;
	}

	if(PE_InputAccessCode(ORDER_REFUND, STR_ENTER_ACCESS_CODE,  STR_KEY_INPUT_NUMBER, Term_Par.password))
	{
		return -1;
	}
	ret=APP_CamScan('R',NULL,g_ColData.transaction_id,10,32,20*1000);
	if(ret<0) return -1;
	if(ret==OPER_HARD)
	{
		g_ColData.transaction_id[0]='\0';	//不能将上面的结果带下来。
		ret=APP_InputMerchSN('R',g_ColData.transaction_id,10,32,20*1000);
		if(ret<0) return -1;
	}
	if(0 != PE_Connect(" ",HTTP_TRADE_ADDERR,HTTP_TRADE_PORT))
	{
		return -1;
	}
	DataInit();
	if(0 == PE_CommProcess(pTitle, FLOW_QUERY, Full_CheckRecv, STR_CHECKING_ORDER))
	{
        if(IsOrderStateSucceed() || IsOrderStateRefund())
		{
			//---执行退款操作-------
			PE_ReadRecvIdPar("total_fee", g_ColData.total_fee, sizeof(g_ColData.total_fee));
			ret=SubRefundTrade(pTitle,g_ColData.transaction_id, g_ColData.total_fee);
		}
		else
		{
			if(0 == PE_CheckRecvIdPar("result_code","1"))
			{
				char presult_code[8],perr_msg[64]={0};
				char *pfsRetCode;
				PE_ReadRecvIdPar("result_code",presult_code,sizeof(presult_code));
				PE_ReadRecvIdPar("err_msg",perr_msg,sizeof(perr_msg));
				pfsRetCode=SubPfsTradeQuery(g_ColData.transaction_id);
				if(pfsRetCode != NULL && (API_memcmp(pfsRetCode,"0000",4)==0))
				{
					 APP_ShowTradeMsg("No refund function",20*1000);
				}
				else
				{
					char msg[64+20];
					int len;
					if(pfsRetCode) 
					{
						API_strcpy(presult_code,pfsRetCode);
						PE_ReadRecvIdPar("errorDetail",perr_msg,sizeof(perr_msg));
						TRACE("SubPfsTradeQuery->pfsRetCode[%s]\r\n",pfsRetCode);
					}
					len=API_sprintf(msg,"%s[ %s ]\n",STR_RUTURN_CODE, presult_code);
					if(perr_msg[0])
					{
						API_Utf8ToGbk(msg+len, sizeof(msg)-len, perr_msg);
					}
					APP_ShowTradeMsg(msg,20*1000);
				}
			}
			else
			{
				ShowOrderInfo();
			}
		}
	}
	DataFree();
	Tcp_Close(pTitle);
	return 0;
}

/**
 * <调用显示二维码>
 *
 * @return 0 成功, -1 失败
 */	
int ShowQRCode(void)
{
	char *qrcode;

	//展示二维码
	if(NULL != (qrcode=PE_GetRecvIdPar("code_url")))
	{
		PE_ShowQRcodeDis(qrcode, g_ColData.total_fee);
		TRACE("code_url:%s \r\n",qrcode);
	}
	else 
	{
		APP_ShowTradeMsg(STR_DATA_FORMAT_ERR,10*1000); 
		return -1;
	}

	return 0;
}


/**
 * <返回状态码 是否成功>
 *
 * 0表示成功，非0表示失败此字段是通信标识，非交易标识
 *
 * @return 1 成功, 0 失败或未知 
 */	
int IsStatusSucceed(void)
{
	char *status  = PE_GetRecvIdPar("status");

	TRACE("status:%s \r\n",status);
	if( status ) 
	{
		if ( API_memcmp(status, "0", 1) == 0 )
		{
			return 1;
		}
	}

	return 0;
}

/**
 * <是否已经支付>
 *
 * @return  1 是, 0 否
 */	
int IsNotPay( void )
{
	if(PE_CheckRecvIdPar("result_code","0") == 0 )
	{
		if ((PE_CheckRecvIdPar("trade_state", "NOTPAY") == 0)
			|| (PE_CheckRecvIdPar("trade_state", "USERPAYING") == 0))
		{
			return 1;
		}
	}

	return 0;
}

/**
 * <检查交易结果是否成功>
 *
 * status和result_code字段返回都为0时，判定订单支付成功；
 *
 * @return 0 成功, 1 失败,-1 未知 
 */	
int IsTradeSucceed(void)
{
	char *pstatus      = PE_GetRecvIdPar("status");
	char *presult_code = PE_GetRecvIdPar("result_code");

	if(pstatus==NULL || presult_code==NULL) {
		return -1;
	}
	if((API_memcmp(pstatus,"0",1)==0) && (API_memcmp(presult_code,"0",1)==0))
	{    
		return 0;	
	}

	return 1;
}


/**
 * <订单交易状态是否成功>
 *  查询、退款查询接口后使用，
 *  status、result_code都为0, trade_state 为SUCCESS，判定订单支付成功（ 或订单退款成功 ）；
 * 
 *  @return 1 成功状态, 0 其他
 */
int IsOrderStateSucceed(void)
{
	if((0==IsTradeSucceed())
		&& (PE_CheckRecvIdPar("trade_state", "SUCCESS") == 0))
	{
		return 1;
	}

	return 0;
}

int IsOrderStateRefund(void)
{
	if ((0==IsTradeSucceed())
		&& (PE_CheckRecvIdPar("trade_state", "REFUND") == 0))
	{
		return 1;
	}

	return 0;
}


/**
 * <检查交易状态是否需要查询>
 *
 * 返回的参数need_query为Y或没有该参数返回时，必须调用订单查询接口进行支付结果确认
 *
 * @return  1 需要查询, 0 不需要查询
 */	
int IsTradeNeedQuerry(void)
{
	char *pneed_query;
	char *perr_code;
	/*
	<charset><![CDATA[UTF-8]]></charset>
	<mch_id><![CDATA[300540000001]]></mch_id>
	<message><![CDATA[鍙楃悊鍏崇郴涓嶅瓨鍦╙]></message>
	<nonce_str><![CDATA[7439CE2D62804F4128107A7C4EF30464]]></nonce_str>
	<sign><![CDATA[97E677C56904908079FBF2EDDB81CDB5]]></sign>
	<sign_type><![CDATA[MD5]]></sign_type>
	<status><![CDATA[410]]></status>
	<version><![CDATA[2.0]]></version>
*/
	pneed_query = PE_GetRecvIdPar("need_query");

	if (!pneed_query ) 
	{	
		// 特殊处理,
		// 当前支付金额超限时，平台不返回need_query参数，但不需继续查询
		perr_code= PE_GetRecvIdPar("err_code");
		if(perr_code)
		{
			if(API_strstr(perr_code, "Auth"))
				return 0;
			if(API_strstr(perr_code, "fail"))
				return 0;
			if(API_strstr(perr_code, "invalid"))
				return 0;
		}
		return 1;
	}

	if ( 0 != API_strcmp(pneed_query, "N"))
	{
		return 1;
	}


	if ( IsTradeResultUnkown() )
	{
		return 1;
	}

	return 0;
}


/**
 * <检查交易结果是否未知>
 *
 * @return	1 交易结果未知, 0 已知
 */	
int IsTradeResultUnkown(void)
{	
	int index, count;
	char *err_code;
	char err_codes[][64]=
	{
		"USERPAYING", 				\
		"Internal error", 			\
		"BANKERROR",				\
		"10003",					\
		"USERPAYING",				\
		"System error",				\
		"aop.ACQ.SYSTEM_ERROR"	,	\
		"ACQ.SYSTEM_ERROR",			\
		"SYSTEMERROR",				\
		"aop.unknow-error"					 
	 };

	err_code=PE_GetRecvIdPar("err_code");
	if ( NULL == err_code ){
		return 0;
	}

	count = sizeof(err_codes)/sizeof(err_codes[1]);
	for(index = 0 ;index < count; index++){
		if (API_strcmp(err_code, err_codes[index])==0)
		{
			return 1;
		}
	}

	return 0;
}

/**
 * <获取交易类型名称>
 */	
void GetTradeTypeName(char type, char* trade_type)
{
	switch(type)
	{
		case 'W':
			API_strcpy(trade_type, STR_WECHAT);
			break;
		case 'A':
			API_strcpy(trade_type, STR_ALIPAY);
			break;
		case 'J':
			API_strcpy(trade_type, STR_JDPAY);
			break;
		case 'Q':
			API_strcpy(trade_type, STR_QQ);
			break;
		case 'S':
			API_strcpy(trade_type, STR_SHIMING);
			break;
		case 'U':
			API_strcpy(trade_type, STR_UNIONPAY);
			break;
		case 'B':
			API_strcpy(trade_type, STR_BESTPAY);
			break;
	}
}


/**
 * <交易成功提示>
 *
 */	
void ShowSucceedTrade(void)
{
	char trade_type[32+1] = {0};
	char *ptrade_type;

	ptrade_type = PE_GetRecvIdPar("trade_type");
	if(ptrade_type == NULL)
	{
		APP_ShowMsg(STR_MESSAGE, STR_DATA_FORMAT_ERR,10*1000);
		return;
	}

	g_ColData.pay_type = (~0x20) & ptrade_type[4];
	GetTradeTypeName(g_ColData.pay_type, trade_type);
	TRACE("ShowSucceedTrade = [%s]", trade_type);
	SuccessTradeProcess(trade_type);
}

/**
 * <显示订单查询结果>
 * 
 * @date  201806014
 */
void ShowQuerryResult( void )
{
	if(PE_CheckRecvIdPar("result_code", "0") != 0)
	{
		ShowReturnMessage();
		return;
	}

	if(PE_CheckRecvIdPar("trade_state", "SUCCESS") == 0)
	{
		ShowSucceedTrade();
		return;
	}
	ShowReturnMessage();
}

/*
void ShowRefundOrder(void)
{
	// 显示明细
	char time[12]={0};
	char Date[12]={0};
	char *pTime_end;
	char *pTrade_type;
	char *pTotal_fee,*pCash_fee;
	char *pTransaction_id;
	char trade_type[32];

	pTrade_type=PE_GetRecvIdPar("trade_type");
	if(pTrade_type==NULL)
	{
		APP_ShowMsg(STR_MESSAGE, STR_DATA_FORMAT_ERR,10*1000);
		return;
	}
	g_ColData.pay_type = (~0x20)&pTrade_type[4];
	pTransaction_id    = PE_GetRecvIdPar("transaction_id");  //小写转大写
	pTotal_fee         = PE_GetRecvIdPar("total_fee");
	pCash_fee		   = PE_GetRecvIdPar("total_fee");
	pTime_end          = PE_GetRecvIdPar("time_end");

	//时间格式：20180423162735
	API_memcpy(Date  ,pTime_end  ,4);		Date[4]='-';
	API_memcpy(Date+5,pTime_end+4,2);		Date[7]='-';
	API_memcpy(Date+8,pTime_end+6,2);		Date[10]='\0';
	API_memcpy(time  ,pTime_end+8,2);		time[2]=':';
	API_memcpy(time+3,pTime_end+10,2);		time[5]=':';
	API_memcpy(time+6,pTime_end+12,2);		time[8]='\0';

	GetTradeTypeName(g_ColData.pay_type, trade_type);
	APP_ShowEnquiriesMsg(pTotal_fee, trade_type, Date, time, pTransaction_id);
}
*/
/**
 * <查询订单结果显示>
 *
 * @return  
 */	
void ShowOrderInfo(void)
{	
	char *ptrade_state = NULL;

	if(0==IsTradeSucceed())
	{
		// 显示明细
		if(NULL != (ptrade_state = PE_GetRecvIdPar("trade_state")))// 交易的状态
		{	
			if(API_memcmp(ptrade_state, "SUCCESS", 6)==0)
			{
				// 显示明细
				ShowOrderDetails();
				return;
			}
			else if(API_memcmp(ptrade_state, "REFUND", 6)==0)
			{
				APP_ShowTradeMsg(STR_ORDER_RERUNDED,10*1000);
				//APP_ShowMsg(STR_MESSAGE ,STR_ORDER_RERUND,10*1000); 
				return;
			}
		}
	}

	ShowReturnMessage();
	return;
}


/**
 * <订单明细显示>
 */	
void ShowOrderDetails(void)
{
	// 显示明细
	char time[12]={0};
	char Date[12]={0};
	char *pTime_end;
	char *pTrade_type;
	char *pTotal_fee;
	char *pTransaction_id;
	char trade_type[32];

	pTrade_type=PE_GetRecvIdPar("trade_type");
	if(pTrade_type==NULL)
	{
		APP_ShowMsg(STR_MESSAGE, STR_DATA_FORMAT_ERR,10*1000);
		return;
	}
	g_ColData.pay_type = (~0x20)&pTrade_type[4];
	pTransaction_id    = PE_GetRecvIdPar("transaction_id");  //小写转大写
	pTotal_fee         = PE_GetRecvIdPar("total_fee");
	pTime_end          = PE_GetRecvIdPar("time_end");

	//时间格式：20180423162735
	API_memcpy(Date  ,pTime_end  ,4);		Date[4]='-';
	API_memcpy(Date+5,pTime_end+4,2);		Date[7]='-';
	API_memcpy(Date+8,pTime_end+6,2);		Date[10]='\0';
	API_memcpy(time  ,pTime_end+8,2);		time[2]=':';
	API_memcpy(time+3,pTime_end+10,2);		time[5]=':';
	API_memcpy(time+6,pTime_end+12,2);		time[8]='\0';

	GetTradeTypeName(g_ColData.pay_type, trade_type);
	APP_ShowEnquiriesMsg(pTotal_fee, trade_type, Date, time, pTransaction_id);
}


/**
 * <显示交易提示信息>
 */	
int ShowReturnMessage(void)
{
	char msg[128];
	char *pstatus;
	char *pmessage;
	char *perr_msg;
	char *presult_code;
	char *ptrade_state_desc;
	int len;

	API_memset(msg, 0, sizeof(msg));

	// 通讯失败, 提示message消息
	pstatus  = PE_GetRecvIdPar("status");
	pmessage = PE_GetRecvIdPar("message");
	if(pstatus)
	{
		if (0 != API_strcmp(pstatus, "0"))
		{
			API_sprintf(msg, "返回状态码[%s]\n", pstatus);
			len = API_strlen(msg);
			if ( pmessage )
				API_Utf8ToGbk(msg + len, sizeof(msg)-len, pmessage);
			return APP_ShowTradeMsg(msg,10*1000);
			//return APP_ShowMsg(STR_MESSAGE, msg,10*1000);
		}
	}

	// 交易错误提示
	presult_code = PE_GetRecvIdPar("result_code");
	perr_msg     = PE_GetRecvIdPar("err_msg");
	if(presult_code)
	{
		API_sprintf(msg,"%s[ %s ]\n",STR_RUTURN_CODE, presult_code);
	}
	if(perr_msg)
	{
		len = API_strlen(msg);
		API_Utf8ToGbk(msg+len, sizeof(msg)-len, perr_msg);
	}
	else 
	{
		ptrade_state_desc = PE_GetRecvIdPar("trade_state_desc");
		if (ptrade_state_desc)
		{
			len = API_strlen(msg);
			API_Utf8ToGbk(msg+len, sizeof(msg)-len, ptrade_state_desc);
		}
	}
	return APP_ShowTradeMsg(msg,20*1000);
	//return APP_ShowMsg(STR_MESSAGE, msg,10*1000); 
}



