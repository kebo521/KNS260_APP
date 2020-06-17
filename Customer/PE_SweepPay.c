#include "communal.h"


DfFlow_Link  pFlow={0};
QR_COL_Data  g_ColData;

//static pDataTable  pItemdata;

int CheckMchidIsNull()
{
	{	
	    return 0;
	}
	//APP_ShowMsg("��ʾ","���ȵ����̻���Ϣ",3000); 
	//return 1;
}
void DataInit()
{
	if(PE_SendBuf==NULL)
	{
		PE_SendBuf=malloc(BufSize);
	}
	PE_pSend = PE_SendBuf;	
	if(pFlow.pMd5Start==NULL)
	{
		pFlow.pMd5Start=malloc(BufSize);
	}
	PE_pMD5 = pFlow.pMd5Start;
}
void DataFree(void)
{
	PE_JsonFree();
}

int Full_CheckRecv(char *pRecv,int ReadLen)
{
	if(ReadLen > 0)
	{
		int		cycle;
		char	*pStrStart,*pEnd;
		pStrStart = pRecv;
		pEnd = pStrStart+ReadLen;
		//------------�ҵ����-----------------------
		while(pStrStart < pEnd)
		{
			if(*pStrStart++ == '{') break;
		}
		if(pStrStart >= pEnd) return 0;
		//------------�ҵ��յ�-----------------------
		cycle = 1;
		while(pStrStart < pEnd)
		{
			if(*pStrStart == '{')
				cycle++;
			else if(*pStrStart == '}')
				cycle--;
			if(cycle == 0) break;
			pStrStart++;
		}
		if(cycle) return 0;
		pStrStart++;
		return (pStrStart-pRecv);
	}
	//TRACE("RecvErrData[%s]\r\n",pRecv);
	return 0;	
}



int SuccessTradeProcess(void)
{
	char DisplayMoney[16];
	char sPayType[12],*payType;
	APP_ShowTradeOK(g_ColData.payAmount); 
	payType=PE_GetRecvIdPar("payType");
	/*
	wx_pay��΢��֧����
	ali_pay��֧������
	union_offline�����п���
	union_qrcode������ɨ�룻
	union_online������Ǯ����
	member_wallet����ԱǮ����
	cash���ֽ�
	*/
	if(API_strcmp(payType,"wx_pay")==0)
	{
		API_strcpy(sPayType,"΢���տ�");
	}
	else if(API_strcmp(payType,"ali_pay")==0)
	{
		API_strcpy(sPayType,"֧�����տ�");
	}
	else
	{
		API_strcpy(sPayType,"�տ�ɹ�");
	}	
	Conv_TmoneyToDmoney(DisplayMoney,g_ColData.payAmount);
    APP_TTS_PlayText("%s%sԪ",sPayType,DisplayMoney);
	//-------���±���ʱ��----------
	SetSysDateTime(PE_GetRecvIdPar("payTime"));
	return APP_WaitUiEvent(10*1000);
}

void Send_add_item(char* pID,char* pData)
{
	if(API_strlen(pData))
	{
		PE_pSend=Conv_SetPackageJson(PE_pSend,pID,pData);
		*PE_pSend++= ',';	//������һ��
		PE_pMD5=Conv_SetPackageHttpGET(PE_pMD5,pID,pData);
		*PE_pMD5++= '&';	//������һ��
	}
}

void Send_add_end_Sign(void)
{
	u32 len;
	u8 uMd5Out[20]; 
	PE_pMD5=Conv_SetPackageHttpGET(PE_pMD5,"key",g_ColData.signkey);
	len = PE_pMD5-pFlow.pMd5Start;
	md5((u8*)pFlow.pMd5Start,len,uMd5Out);
	Conv_BcdToStr(uMd5Out,16,g_ColData.sign);
	PE_pSend=Conv_SetPackageJson(PE_pSend,"sign",g_ColData.sign);
}



// ��1���ĸ�����Ϣ  Ҳ�Ǹ�ǰ��Լ�������ͣ����Ͳ�ͨ���Ӳ�ͬ
void TradeDataPacked_start(char *pTradeAddress)
{  
	DataInit();
	PE_sLenStart=Conv_Post_SetHead(pTradeAddress,"application/json",PE_pSend);
	//API_sprintf(pSendLenAddr[7], "% 3d\r\n\r\n",API_strlen(param)) Ԥ��7���ֽڿռ�
	PE_pSend=PE_sLenStart+7;
	*PE_pSend++ ='{';
}

void TradeDataPacked_end(void)
{	
	char sendLen[8];
	*PE_pSend++ = '}';
	//----------------��3���ֽڹ̶�����д��buff��---------------------
	API_sprintf(sendLen,"%3d\r\n\r\n",PE_pSend-PE_sLenStart-7); //Ԥ��7���ֽڿռ�
	API_memcpy(PE_sLenStart,sendLen,7);
	*PE_pSend++ = '0';
	*PE_pSend = '\0';
	pFlow.pMsgLen=PE_pSend-PE_SendBuf;
	TRACE("->PE_SendBuf:\r\n%s\r\n", PE_SendBuf);
}

void UpData_timestampAndNoncestr(int GenId)
{
	u32 timeStamp;
	ST_TIME tTime;
	OsGetTime(&tTime);
	Conv_DateToTimestamp(&tTime,8,&timeStamp);
	sprintf(g_ColData.timestamp,"%d",timeStamp);
	memcpy(g_ColData.nonceStr,g_ColData.sn+2,8);
	sprintf(g_ColData.nonceStr+8,"%s",g_ColData.timestamp);
	if(GenId)
		sprintf(g_ColData.outTradeId,"%s%s",g_ColData.shopId,g_ColData.timestamp);
}


void SweepPackData_V2(void)
{
	UpData_timestampAndNoncestr(1);
	SEND_ADD_ITEM(authCode);
	SEND_ADD_ITEM(developerId);
	SEND_ADD_ITEM(nonceStr);
	SEND_ADD_ITEM(outTradeId);
	SEND_ADD_ITEM(payAmount);
	SEND_ADD_ITEM(returnContent);
	SEND_ADD_ITEM(shopId);
	SEND_ADD_ITEM(sn);
	SEND_ADD_ITEM(terminalType);
	SEND_ADD_ITEM(timestamp);
	Send_add_end_Sign();
}

/*
//-------------����һ----------------
SEND_ADD_ITEM(tradeId);
SEND_ADD_ITEM(outTradeId);
SEND_ADD_ITEM(transactionId);

*/
void PackData_OrderQuery(void)
{
	//g_ColData.payType; 
	UpData_timestampAndNoncestr(0);
	SEND_ADD_ITEM(developerId);
	SEND_ADD_ITEM(nonceStr);
	SEND_ADD_ITEM(outTradeId);
	SEND_ADD_ITEM(shopId);
	SEND_ADD_ITEM(sn);
	SEND_ADD_ITEM(terminalType);
	SEND_ADD_ITEM(timestamp);
	SEND_ADD_ITEM(tradeId);
	SEND_ADD_ITEM(transactionId);
	Send_add_end_Sign();
}

//   /open/Pay/refund
void PackData_refund(void)
{
	//g_ColData.payType; 
	UpData_timestampAndNoncestr(0);
	SEND_ADD_ITEM(developerId);
	SEND_ADD_ITEM(nonceStr);

	if(g_ColData.terminalType[0] == '2')
	{
		//SEND_ADD_ITEM(outTradeId);
		SEND_ADD_ITEM(refundFee);
		SEND_ADD_ITEM(returnContent);
		SEND_ADD_ITEM(sn);
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
		SEND_ADD_ITEM(tradeId);
		SEND_ADD_ITEM(transactionId);
	}
	else if(g_ColData.terminalType[0] == '1')
	{
		//SEND_ADD_ITEM(outTradeId);
		SEND_ADD_ITEM(refundFee);
		SEND_ADD_ITEM(returnContent);
		SEND_ADD_ITEM(shopId);		
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
		SEND_ADD_ITEM(tradeId);
		SEND_ADD_ITEM(transactionId);
		SEND_ADD_ITEM(userCode);
	}
	Send_add_end_Sign();
}


void PackData_ConsumeCard(void)
{
	//g_ColData.payType; 
	UpData_timestampAndNoncestr(0);
	SEND_ADD_ITEM(code);
	SEND_ADD_ITEM(developerId);
	SEND_ADD_ITEM(nonceStr);
	SEND_ADD_ITEM(shopId);
	SEND_ADD_ITEM(sn);
	SEND_ADD_ITEM(terminalType);
	SEND_ADD_ITEM(timestamp);
	SEND_ADD_ITEM(transactionId);
	Send_add_end_Sign();
}


void PackData_shiftStatV2(void)
{
	UpData_timestampAndNoncestr(0);
	SEND_ADD_ITEM(developerId);
	SEND_ADD_ITEM(nonceStr);
	if(g_ColData.terminalType[0] == '2')
	{
		SEND_ADD_ITEM(sn);
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
	}
	else if(g_ColData.terminalType[0] == '1')
	{
		SEND_ADD_ITEM(shopId);
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
		SEND_ADD_ITEM(userCode);
	}
	Send_add_end_Sign();
}

void PackData_shiftRecordV2(void)
{
	UpData_timestampAndNoncestr(0);
	SEND_ADD_ITEM(count);
	SEND_ADD_ITEM(developerId);
	SEND_ADD_ITEM(nonceStr);
	SEND_ADD_ITEM(nowPage);
	if(g_ColData.terminalType[0] == '2')
	{
		SEND_ADD_ITEM(sn);
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
	}
	else if(g_ColData.terminalType[0] == '1')
	{
		SEND_ADD_ITEM(shopId);
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
		SEND_ADD_ITEM(userCode);
	}
	Send_add_end_Sign();
}

void PackData_shiftConfirm(void)
{
	UpData_timestampAndNoncestr(0);
	SEND_ADD_ITEM(developerId);
	SEND_ADD_ITEM(nonceStr);
	SEND_ADD_ITEM(recordId);
	if(g_ColData.terminalType[0] == '2')
	{
		SEND_ADD_ITEM(sn);
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
	}
	else if(g_ColData.terminalType[0] == '1')
	{
		SEND_ADD_ITEM(shopId);
		SEND_ADD_ITEM(terminalType);
		SEND_ADD_ITEM(timestamp);
		SEND_ADD_ITEM(userCode);
	}
	Send_add_end_Sign();
}


int PE_ShowQRcodeDis(char* pQRcode)
{
	RECTL	Rect;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	UI_ShowPictureFile(&Rect,"QRcode.clz");

	Rect.left	= UI_QR_CODE_X;
	Rect.top	= UI_QR_CODE_Y+5;
	Rect.width	= UI_QR_CODE_W;
	Rect.height = UI_QR_CODE_H;
	API_GUI_Draw565QRcode(&Rect,pQRcode,RGB565_BLACK);
	{
		POINT tFontXY;
		u16 width;
		char sShowStr[32];
		API_strcpy(sShowStr,"���:��");
		Conv_TmoneyToDmoney(sShowStr+API_strlen(sShowStr),g_ColData.payAmount);
		width=API_strlen(sShowStr)*FONT_SIZE/2;
		tFontXY.left =UI_QR_MONEY_X+ (UI_QR_MONEY_W-width)/2;
		tFontXY.top =UI_QR_MONEY_Y;
		UI_SetColorRGB565(RGB565_BLACK,RGB565_PARENT);
		UI_DrawString(&tFontXY,sShowStr);
	}
	API_GUI_Show();
	return 0;
}


void PE_ShowfailMsg(char* pCode)
{
	char codeInfo[32]={0};
	char GbkMsg[128]={0};
	API_sprintf(codeInfo,"Ӧ����[%s]",pCode);
	API_Utf8ToGbk(GbkMsg,sizeof(GbkMsg),PE_GetRecvIdPar("errMsg"));
	PE_ShowMsg("��ʾ",codeInfo,GbkMsg,NULL,10*1000);
 }


int inside_OrderQuery(BOOL notDisplay)
{
	TCP_SetInterNotDisplay(notDisplay);
	// �齨���ݰ�,��������
	if(Tcp_Link("��������..")) 
		return -1;
	// �齨���ݰ�,��������
	TradeDataPacked_start(HTTP_TRADE_ADDERR"/open/Pay/orderQuery");
	PackData_OrderQuery();
	TradeDataPacked_end();
	// ���ͽ�������
	if(Tcp_SocketData("���ݽ���",Full_CheckRecv)) 
		return -2;
	Tcp_Close(NULL);
	return 0;
}


int MicroPay(char* title)
{    
	char *pCode;
	do{
		if(CheckMchidIsNull())return -1;
		if(0 != InputTotalFee(title)){
			return -1;
		}
		
		if(0 != InputAuthcodeByCamScan())
		{
			return -1;
		}
		TCP_SetInterNotDisplay(FALSE);
		if(Tcp_Link("��������..")) break;
		// �齨���ݰ�,��������
		TradeDataPacked_start(HTTP_TRADE_ADDERR"/open/Pay/microPayV2");
		SweepPackData_V2();
		TradeDataPacked_end();
		// ���ͽ�������
		if(Tcp_SocketData("���ݽ���",Full_CheckRecv)) break;
	RE_QUERY_ADDER:
		pCode=PE_GetRecvIdPar("errCode");
		TRACE("reCode:%s",pCode); 
		if(pCode[0] == '0') //���سɹ������Խ�����һ�� ���ݡ�
		{
			char *tradeInfo;
			tradeInfo = PE_GetRecvIdPar("tradeInfo");
			if(tradeInfo)
			{
				if(!PE_JsonDataParse(tradeInfo,API_strlen(tradeInfo)))
				{
					char *payStatus;
					payStatus = PE_GetRecvIdPar("payStatus");
					if(API_strcmp(payStatus,"SUCCESS")==0)
					{
						PE_ReadRecvIdPar("incomeAmount",g_ColData.payAmount);
						SuccessTradeProcess();	
					}
					else if(API_strcmp(payStatus,"CLOSE")==0)
					{
						APP_ShowTradeMsg("�����ѹر�",10000);
					}
					else if(API_strcmp(payStatus,"PAYERROR")==0)
					{
						APP_ShowTradeFA("֧��ʧ��",10000);
					}
					else if(API_strcmp(payStatus,"NOTPAY")==0)
					{
						APP_ShowTradeMsg("δ֧��",10000);
					}
					else if(API_strcmp(payStatus,"REVOKED")==0)
					{
						APP_ShowTradeMsg("�����ѳ���",10000);
					}
					else if(API_strcmp(payStatus,"USERPAYING")==0)
					{
						PE_ReadRecvIdPar("tradeId",g_ColData.tradeId);
						PE_ReadRecvIdPar("outTradeId",g_ColData.outTradeId);
						
						Tcp_Close(NULL);
						PE_JsonFree();
						API_WaitEvent(2*1000);
						if(0 == inside_OrderQuery(TRUE))
							goto RE_QUERY_ADDER; 
						APP_ShowTradeMsg("����֧����,�Ժ��ѯȷ��",10000);
					}
					PE_JsonFree();
				}
			}
			//pSdkFun->net->KeyAccept(0x00);
			break;
		}
		else //if(API_strcmp(code,"500"))
		{
			PE_ShowfailMsg(pCode);
		 }
	}while(0);
    DataFree();
	Tcp_Close(NULL);
	return 0;	
}

int OrderQuery(char* pTitle)
{
	char* pCode;
	int ret;
	do{
		if(CheckMchidIsNull())return -1;
		ret=APP_CamScan('Q',NULL,g_ColData.transactionId,8,32,30*1000);
		if(ret<0) return -1;
		if(ret==OPER_HARD)
		{
		    if(APP_ScanInput(pTitle,"�������붩����",NULL,g_ColData.transactionId,10,32)) 
				return -1;
		}
		g_ColData.tradeId[0]=0;
		g_ColData.outTradeId[0]=0;
		if(inside_OrderQuery(FALSE))
			break;
		pCode=PE_GetRecvIdPar("errCode");
	    TRACE("reCode:%s",pCode); 
	    if(pCode[0] == '0') 
	    {
			char *tradeInfo;
			tradeInfo = PE_GetRecvIdPar("tradeInfo");
			if(tradeInfo)
			{
				if(!PE_JsonDataParse(tradeInfo,API_strlen(tradeInfo)))
				{
					char *pPar,*pShow;
					char showBuff[256];
					pShow=showBuff;
					pPar=PE_GetRecvIdPar("id");
					if(pPar)
					{
						pShow += sprintf(pShow,"̫����ˮ:%s\n",pPar);
					}
					pPar=PE_GetRecvIdPar("outTradeId");
					if(pPar)
					{
						pShow += sprintf(pShow,"������ˮ:%s\n",pPar);
					}
					
					pPar=PE_GetRecvIdPar("transactionId");
					if(pPar)
					{
						pShow += sprintf(pShow,"������ˮ:%s\n",pPar);
					}
					pPar=PE_GetRecvIdPar("orderNum");
					if(pPar)
					{
						pShow += sprintf(pShow,"�̻�������:%s\n",pPar);
					}
					pPar=PE_GetRecvIdPar("module");
					if(pPar)
					{
						pShow += sprintf(pShow,"module:%s\n",pPar);
					}
					pPar=PE_GetRecvIdPar("shopId");
					if(pPar)
					{
						pShow += sprintf(pShow,"�ŵ��:%s  ",pPar);
					}
					pPar=PE_GetRecvIdPar("merchantUserId");
					if(pPar)
					{
						pShow += sprintf(pShow,"��Ա��:%s\n",pPar);
					}



					pPar=PE_GetRecvIdPar("orderAmount");
					if(pPar)
					{
						char DisplayMoney[16];
						Conv_TmoneyToDmoney(DisplayMoney,pPar);
						pShow += sprintf(pShow,"�����ܶ�:%s\n",DisplayMoney);
					}
					pPar=PE_GetRecvIdPar("incomeAmount");
					if(pPar)
					{
						char DisplayMoney[16];
						Conv_TmoneyToDmoney(DisplayMoney,pPar);
						pShow += sprintf(pShow,"ʵ�ս��:%s\n",DisplayMoney);
					}
					pPar=PE_GetRecvIdPar("payTime");
					if(pPar)
					{
						pShow += sprintf(pShow,"֧��ʱ��:\n%s\n",pPar);
					}
					APP_ShowInfo(pTitle,showBuff,30*1000);
					PE_JsonFree();
				}
			}
			//pSdkFun->net->KeyAccept(0x00);
			break;
		}
		else 
		{
			PE_ShowfailMsg(pCode);
	 	} 
	}while(0);
    DataFree();
	Tcp_Close(NULL);
	return 0;	
}
int RefundFlow(char* pTitle)
{
	int ret=1;
	char* pCode;
	do{
		if(CheckMchidIsNull())return -1;
		//if(APP_InputPin(title,"���������Ա����:","�밴���ּ�����", "888888")) return -1;
		ret=APP_CamScan('R',NULL,g_ColData.transactionId,10,32,20*1000);
		if(ret<0) return -1;
		if(ret == OPER_HARD)
		{
		    if(APP_ScanInput(pTitle,"�������붩����",NULL,g_ColData.transactionId,10,32)) 
				return -1;
		}
		if(inside_OrderQuery(FALSE))
			break;
		g_ColData.tradeId[0]='\0';	//��� ̫��ID
		pCode=PE_GetRecvIdPar("errCode");
		if(pCode[0] == '0') 
		{
			char *tradeInfo = PE_GetRecvIdPar("tradeInfo");
			if(tradeInfo!=NULL && 0==PE_JsonDataParse(tradeInfo,API_strlen(tradeInfo)))
			{
				char *pPar;
				u32 income=0,refund;
				pPar=PE_GetRecvIdPar("id");
				if(pPar)
					API_strcpy(g_ColData.tradeId,pPar);
				pPar=PE_GetRecvIdPar("incomeAmount");
				if(pPar)
					income = API_atoi(pPar);
				pPar=PE_GetRecvIdPar("refundAmount");
				if(pPar)
				{
					refund=API_atoi(pPar);
					if(income < refund)
						income = 0;
					else income -= refund;
				}
				if(income == 0)
				{
					APP_ShowTradeMsg("�޿��˽��",10*1000);
                       break;
				}
				sprintf(g_ColData.refundFee,"%d",income);
				PE_JsonFree();
			}
			else
			{
				APP_ShowTradeMsg("���޴˶�����Ϣ",10*1000);
                break;
			}
		}
		else 
		{
			PE_ShowfailMsg(pCode);
			break;
		} 
		PE_JsonFree();
		
		if(0>APP_EditSum(pTitle,'R',g_ColData.refundFee,60*1000))
		{
			return -1;
		}
		if(Tcp_Link("��������..")) break;
		// �齨���ݰ�,��������
		TradeDataPacked_start(HTTP_TRADE_ADDERR"/open/Pay/refund");
		PackData_refund();
		TradeDataPacked_end();
		// ���ͽ�������
		if(Tcp_SocketData("���ݽ���",Full_CheckRecv)) break;
		
		pCode=PE_GetRecvIdPar("errCode");
		if(pCode[0] == '0') 
		{
			APP_ShowRefundsOK(g_ColData.refundFee);
			APP_WaitUiEvent(10*1000);
		}
		else //if(API_strcmp(code,"500"))
		{
			PE_ShowfailMsg(pCode);
		 }
	}while(0);
	DataFree();
	APP_Network_Disconnect(50);
	return 0;		
}

int ConsumeCard(char* pTitle)
{
	char* pCode;
	int ret;
	do{
		if(CheckMchidIsNull())return -1;
		APP_ShowSta(pTitle,"��ɨ�Ż�ȯ������");
		ret=APP_OnlyCamScan(0x03,8,sizeof(g_ColData.code)-1,g_ColData.code,30*1000);
		if(ret<0) return -1;
		if(ret==OPER_HARD)
		{
			if(APP_ScanInput(pTitle,"�������붩����",NULL,g_ColData.code,10,32)) 
				return -1;
		}
		TCP_SetInterNotDisplay(FALSE);
		// �齨���ݰ�,��������
		if(Tcp_Link("��������..")) break;
		// �齨���ݰ�,��������
		TradeDataPacked_start(HTTP_TRADE_ADDERR"/open/Card/consumeCard");
		PackData_OrderQuery();
		TradeDataPacked_end();
		// ���ͽ�������
		if(Tcp_SocketData("���ݽ���",Full_CheckRecv)) break;
		pCode=PE_GetRecvIdPar("errCode");
		TRACE("reCode:%s",pCode); 
		if(pCode[0] == '0') 
		{
			APP_ShowTradeOK(NULL);
			APP_WaitUiEvent(10*1000);
			break;
		}
		else 
		{
			PE_ShowfailMsg(pCode);
		} 
	}while(0);
	DataFree();
	Tcp_Close(NULL);
	return 0;	
}

int shiftStatV2(char* pTitle)
{
	char* pCode;
	do{
		if(CheckMchidIsNull())return -1;
		// �齨���ݰ�,��������
		TCP_SetInterNotDisplay(FALSE);
		if(Tcp_Link("��������..")) break;
		// �齨���ݰ�,��������
		TradeDataPacked_start(HTTP_TRADE_ADDERR"/open/Staff/shiftStatV2");
		PackData_shiftStatV2();
		TradeDataPacked_end();
		// ���ͽ�������
		if(Tcp_SocketData("���ݽ���",Full_CheckRecv)) break;
		pCode=PE_GetRecvIdPar("errCode");
		TRACE("reCode:%s",pCode); 
		if(pCode[0] == '0') 
		{
			char *stat=PE_GetRecvIdPar("stat");
			PE_ReadRecvIdPar("recordId",g_ColData.recordId); 
			if((stat!= NULL) && (API_strlen(stat)>8))
			{	
				char showbuff[1024],*pshow;
				char IndexBuff[64],*pPar;
				int i,total;
				dfJsonTable *pJsonData,*pStartJson = Conv_JSON_GetMsg(stat,stat+API_strlen(stat));
				pJsonData = pStartJson;
				showbuff[0] = '\0';
				pshow = showbuff;
				while(pJsonData)
				{
					pPar=Conv_GetJsonValue(pJsonData,"title",NULL);
					API_Utf8ToGbk(IndexBuff,sizeof(IndexBuff),pPar);
					pshow=eStrcpy(pshow,IndexBuff);
					*pshow++ =':';
					*pshow++ ='\n';
					pPar=Conv_GetJsonValue(pJsonData,"totalAmount",NULL);
					sprintf(IndexBuff,"�ܽ��:%s",pPar);
					pshow=eStrcpy(pshow,IndexBuff);
					pshow=eStrcpy(pshow,"Ԫ");
					*pshow++ =' ';
					*pshow++ =' ';
					pPar=Conv_GetJsonValue(pJsonData,"totalCount",NULL);
					total=API_atoi(pPar);
					sprintf(IndexBuff,"����:%s",pPar);
					pshow=eStrcpy(pshow,IndexBuff);
					*pshow++ ='\n';
					for(i=0;i<total;i++)
					{
						sprintf(IndexBuff,"module[%d]/payType",i);
						pPar=Conv_GetJsonValue(pJsonData,IndexBuff,NULL);
						if(pPar == NULL) break;
						API_Utf8ToGbk(IndexBuff,sizeof(IndexBuff),pPar);
						pshow=eStrcpy(pshow,IndexBuff);
						*pshow++ =':';
						*pshow++ =' ';
						sprintf(IndexBuff,"module[%d]/count",i);
						pPar=Conv_GetJsonValue(pJsonData,IndexBuff,NULL);
						sprintf(IndexBuff,"%s��",pPar);
						pshow=eStrcpy(pshow,IndexBuff);
						*pshow++ = ',';
						sprintf(IndexBuff,"module[%d]/amount",i);
						pPar=Conv_GetJsonValue(pJsonData,IndexBuff,NULL);
						sprintf(IndexBuff,"%sԪ",pPar);
						pshow=eStrcpy(pshow,IndexBuff);
						*pshow++ = '\n';
					}
					pJsonData = pJsonData->pNext;
					*pshow++ = '\n';
				}
				*pshow='\0';
				APP_ShowInfo(pTitle,showbuff,10*1000);
				Conv_JSON_free(pStartJson);
			}
			else
			{
				APP_ShowMsg(pTitle,"�޽��׼�¼",5000);
			}
		}
		else 
		{
			PE_ShowfailMsg(pCode);
		} 
	}while(0);
	DataFree();
	Tcp_Close(NULL);
	return 0;	
}


int shiftRecordV2(char* pTitle)
{
	char* pCode;
	int recordMax;
	u16 count,nowPage;
	if(CheckMchidIsNull())return -1;
	// �齨���ݰ�,��������
	TCP_SetInterNotDisplay(FALSE);
	nowPage=0;
	count = 4;
	do{
	RETURN_DISPLAY_PAGE:
		if(Tcp_Link("��������..")) break;
		// �齨���ݰ�,��������
		TradeDataPacked_start(HTTP_TRADE_ADDERR"/open/Staff/shiftRecordV2");
		sprintf(g_ColData.nowPage,"%d",nowPage);
		sprintf(g_ColData.count,"%d",count);
		PackData_shiftRecordV2();
		TradeDataPacked_end();
		// ���ͽ�������
		if(Tcp_SocketData("���ݽ���",Full_CheckRecv)) break;
		Tcp_Close(0);
		pCode=PE_GetRecvIdPar("errCode");
		TRACE("reCode:%s",pCode); 
		if(pCode[0] == '0') 
		{
			char *recordCount=PE_GetRecvIdPar("recordCount");
			if(recordCount!=NULL && (recordMax=API_atoi(recordCount))>0)
			{
				char *recordList=PE_GetRecvIdPar("recordList");
				if((recordList!= NULL) && (API_strlen(recordList)>8))
				{	
					u8 type;
					char showbuff[1023];
					char IndexBuff[64];
					char *pshow,*pPar;
					int i,total;
					dfJsonTable *pStat;
					dfJsonTable *pJsonData,*pStartJson = Conv_JSON_GetMsg(recordList,recordList+API_strlen(recordList));
					pJsonData = pStartJson;
					showbuff[0] = '\0';
					pshow = showbuff;
					while(pJsonData)
					{
						pPar=Conv_GetJsonValue(pJsonData,"recordId",NULL);
						pshow += sprintf(pshow,"�����¼id:%s\n",pPar);
						pPar=Conv_GetJsonValue(pJsonData,"startTime",NULL);
						pshow += sprintf(pshow,"�ϰ�ʱ��:\n%s\n",pPar);
						pPar=Conv_GetJsonValue(pJsonData,"endTime",NULL);
						pshow += sprintf(pshow,"�°�ʱ��:\n%s\n",pPar);
						pPar=Conv_GetJsonValue(pJsonData,"staff",NULL);
						if(g_ColData.terminalType[0] == '2')
							pshow += sprintf(pshow,"�ն�:%s\n",pPar);
						else if(g_ColData.terminalType[0] == '1')
							pshow += sprintf(pshow,"Ա��:%s\n",pPar);
						type = 0;
						pStat=(dfJsonTable *)Conv_GetJsonValue(pJsonData,"stat",&type);
						if(type >= ITEM_STRUCT)
						{
							while(pStat)
							{
								pPar=Conv_GetJsonValue(pStat,"title",NULL);
								API_Utf8ToGbk(IndexBuff,sizeof(IndexBuff),pPar);
								pshow=eStrcpy(pshow,IndexBuff);
								*pshow++ =':';
								*pshow++ ='\n';
								pPar=Conv_GetJsonValue(pStat,"totalAmount",NULL);
								sprintf(IndexBuff,"�ܽ��:%s",pPar);
								pshow=eStrcpy(pshow,IndexBuff);
								pshow=eStrcpy(pshow,"Ԫ");
								*pshow++ =' ';
								*pshow++ =' ';
								pPar=Conv_GetJsonValue(pStat,"totalCount",NULL);
								total=API_atoi(pPar);
								sprintf(IndexBuff,"����:%s",pPar);
								pshow=eStrcpy(pshow,IndexBuff);
								*pshow++ ='\n';
								for(i=0;i<total;i++)
								{
									sprintf(IndexBuff,"module[%d]/payType",i);
									pPar=Conv_GetJsonValue(pStat,IndexBuff,NULL);
									if(pPar == NULL) break;
									API_Utf8ToGbk(IndexBuff,sizeof(IndexBuff),pPar);
									pshow=eStrcpy(pshow,IndexBuff);
									*pshow++ =':';
									*pshow++ =' ';
									sprintf(IndexBuff,"module[%d]/count",i);
									pPar=Conv_GetJsonValue(pStat,IndexBuff,NULL);
									sprintf(IndexBuff,"%s��",pPar);
									pshow=eStrcpy(pshow,IndexBuff);
									*pshow++ = ',';
									sprintf(IndexBuff,"module[%d]/amount",i);
									pPar=Conv_GetJsonValue(pStat,IndexBuff,NULL);
									sprintf(IndexBuff,"%sԪ",pPar);
									pshow=eStrcpy(pshow,IndexBuff);
									*pshow++ = '\n';
								}
								pStat = pStat->pNext;
								*pshow++ = '\n';
							}
						}
						*pshow++ = '\n';
						pJsonData = pJsonData->pNext;
					}
					*pshow='\0';
					APP_ShowInfoSta(pTitle,showbuff,NULL);
					while(1)
					{
						int evet;
						evet=API_WaitEvent(30*1000,EVENT_KEY);
						if(evet & EVENT_KEY)
						{
							evet &= EVENT_NONE;
							if(evet == K_DOWN)
							{
								if((nowPage+count) < recordMax)
								{
									nowPage += count;
									goto RETURN_DISPLAY_PAGE;
								}
							}
							else if(evet == K_UP)
							{
								if(nowPage > 0)
								{
									if(nowPage > count)
										nowPage -= count;
									else
										nowPage = 0;
									goto RETURN_DISPLAY_PAGE;
								}
							}
							if(evet == K_CANCEL)
							{
								break;
							}
						}
						else break;
					}
					Conv_JSON_free(pStartJson);
				}
			}
			else
			{
				APP_ShowTradeMsg("�޽��׼�¼",5000);
			}
		}
		else 
		{
			PE_ShowfailMsg(pCode);
		} 
	}while(0);
	DataFree();
	Tcp_Close(NULL);
	return 0;	
}


int shiftConfirm(char* pTitle)
{
	char* pCode;
	if(CheckMchidIsNull())return -1;
	if(API_strlen(g_ColData.recordId) == 0)
	{
		APP_ShowTradeFA("����������ͳ��",3000);
		return 0;
	}
	// �齨���ݰ�,��������
	TCP_SetInterNotDisplay(FALSE);
	do{
		if(Tcp_Link("��������..")) break;
		// �齨���ݰ�,��������
		TradeDataPacked_start(HTTP_TRADE_ADDERR"/open/Staff/shift");
		PackData_shiftConfirm();
		TradeDataPacked_end();
		// ���ͽ�������
		if(Tcp_SocketData("���ݽ���",Full_CheckRecv)) break;
		pCode=PE_GetRecvIdPar("errCode");
		TRACE("reCode:%s",pCode); 
		if(pCode[0] == '0') 
		{
			APP_ShowTradeOK("����ɹ�");
			g_ColData.recordId[0]='\0';
			APP_WaitUiEvent(5*1000);
		}
		else 
		{
			PE_ShowfailMsg(pCode);
		} 
	}while(0);
	DataFree();
	Tcp_Close(NULL);
	return 0;	
}


int ShiftMenu(char* pTitle)
{
	CMenuItemStru MenuStruPar[]=
	{
		"����ͳ��",		shiftStatV2,
		"ȷ�Ͻ���",		shiftConfirm,
		"�鿴�����¼",	shiftRecordV2,
	};
	APP_CreateNewMenuByStruct(pTitle,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
	APP_AddCurrentMenuOtherFun(MENU_BACK_MAP,NULL,"shift.clz");
	return 0;
}


