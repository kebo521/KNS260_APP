#include "communal.h"




void APP_GUI_Win(const char* pTitle,const char* pOk,const char* pCancel)
{
	pGuiFun->CreateShowWindow(pTitle,pOk,pCancel);
}
	

int APP_WaitUiEvent(int tTimeOutMS)
{
	return pEventFun->WaitEvent(tTimeOutMS,EVENT_UI,EVENT_NONE);
}

int APP_Edit(EDIT_DATA *pEdit,char* pOutStr)
{
	u32 Event;
	while(1)
	{
		pGuiFun->CreateShowWindow(pEdit->pTitle,TOK,TCANCEL);
		pGuiFun->Edit_Prompt(SIZE_NORMAL,pEdit->pFrontText,SIZE_NORMAL,pEdit->pAfterText);
		pGuiFun->Edit_Control(SIZE_NORMAL,pOutStr,pEdit->Max,pEdit->Way,pEdit->Limit);
		pGuiFun->GUI_Show();
		Event=APP_WaitUiEvent(pEdit->timeOutMs);
		if(Event==EVENT_OK) //��ȡ���뿨������
		{
			int ret;
			ret=pGuiFun->Edit_GetText(pOutStr,33);
			if(ret >= pEdit->Min)
				return ret;
			APP_ShowMsg(pEdit->pTitle,STR_LACK_INPUT,2000);
		}
		if(Event==EVENT_TIMEOUT)
			return OPER_TIMEOUT;
		else if(Event==EVENT_CANCEL)
			return OPER_RET;
	}
}

int APP_InputNum(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinLen,int InputMaxlen)
{
	int 	ret;
	EDIT_DATA	EditData;	
	CLEAR(EditData);
	EditData.pTitle	      =pTitle;
	EditData.pFrontText	=pFrontTextBuf;
	EditData.pAfterText      =pAfterTextBuf;

	EditData.Min		=InputMinLen;
	EditData.Max		=InputMaxlen;
	EditData.Way		=IME_NUM;
	EditData.Limit		=IME_NUM;
	EditData.timeOutMs=30*1000;

	ret =APP_Edit(&EditData,pInputDef);
	if(ret>=0)
		return 0;
	else
		return 1;
}
//��������+��ĸ
int APP_InputAbc(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinlen,int InputMaxlen)
{
	int 	ret;
	EDIT_DATA	EditData;		
	CLEAR(EditData);
	EditData.pTitle	     =pTitle;
	EditData.pFrontText    =pFrontTextBuf;
	EditData.pAfterText     =pAfterTextBuf;

	EditData.Min		=InputMinlen;
	EditData.Max		=InputMaxlen;
	EditData.Way		=IME_NUM;
	EditData.Limit		=IME_NUM|IME_ABC|IME_abc;
	EditData.timeOutMs=30*1000;

	ret =APP_Edit(&EditData,pInputDef);
	if(ret>=0)
		return 0;
	else
		return 1;
}

int APP_InputPin(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pkey)
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

		APP_ShowMsg(pTitle,STR_PASSu16_ERR,3000);	
	}
	return -1;
}

//====================================================================
//����:    ����������ļ�ϵͳ
//��������:pfilePath(�ļ���),pBuff(����������),Inlen(�ļ�����)
//�������:д���� 0 Ϊ�ɹ�
//����:     �˹���	---	
//����ʱ��:  20150916
//---------------------------------------------------------------
int APP_FileSaveBuff(const char * pfilePath,u32 offset,void* pBuff,u32 Inlen)
{
	void*	fb;
	int 	ret;
	fb = API_fopen(pfilePath,F_WRONLY|F_CREAT);
	if(fb == NULL)
	{
		LOG(LOG_ERROR,"APP FileSaveBuff Open[%s] fail\r\n",pfilePath);
		return -1;
	}
	if(offset)
	{
		API_fseek(fb,offset,F_SEEK_SET);
	}
	ret=API_fwrite(fb,pBuff,Inlen);
	API_fclose(fb);
	if(Inlen != ret)
	{
		LOG(LOG_ERROR,"APP FileSaveBuff WriteFile[%s] Err ret[%d != %d]\r\n",pfilePath,Inlen,ret);
		return -2;
	}
	return ret;
}

//====================================================================
//����:    ���ļ�ϵͳ������
//��������:pfilePath(�ļ���),pBuff(����������),pOutlen(�����ļ�����)
//�������:��ȡ��� 0 Ϊ�ɹ�
//����:     �˹���	---	
//����ʱ��:  20150916
//---------------------------------------------------------------
int APP_FileReadBuff(const char * pfilePath,u32 offset,void* pBuff,u32 buffSize)
{
	void*	fd;
	int 	ret=0;
	fd = API_fopen(pfilePath,F_RDONLY);
	if(fd == NULL)
	{
		LOG(LOG_ERROR,"APP FileReadBuff Open[%s]fail, \r\n",pfilePath);
		return -1;
	}
	if(pBuff)
	{
		if(offset)
		{
			API_fseek(fd,offset,F_SEEK_SET);
		}
		ret=API_fread(fd, pBuff, buffSize);
		if(buffSize != ret)
		{
			LOG(LOG_ERROR,"APP FileReadBuff Read[%s] Err nReadSize[%d,%d]\r\n",pfilePath,ret,buffSize);
		}
	}
	else 
	{
		ret = API_fgsize(fd);
	}
	API_fclose(fd);
	return ret;
}



//======���׷�ʽ(1֧������2΢��)====================
void APP_ShowNoSignel(char *pShowMsg,int tTimeOutMS)
{
	UI_ShowScreenBmp("NoSign.clz",pShowMsg,UI_NOSIGNEL_TEXT_Y);
	APP_WaitUiEvent(tTimeOutMS);
}

void APP_ShowWaitFor(char *pShowMsg)
{
	UI_ShowScreenBmp("WaitFor.clz",pShowMsg,UI_WAITFOR_TEXT_Y);
}

void APP_ShowWaitRef(char *pTradeMoney)
{
	RECTL	Rect;
	Rect.left	= UI_MAP_TITLE_X;
	Rect.top	= UI_MAP_TITLE_Y;
	Rect.width	= UI_MAP_TITLE_W;
	Rect.height = UI_MAP_TITLE_H;
	UI_ShowPictureFile(&Rect,"InSumTr.clz");
	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	UI_ShowPictureFile(&Rect,"WaitRef.clz");
	if(pTradeMoney)
	{
		char		sShowStr[12];
		Rect.left	= UI_EDIT_sMONEY_X;
		Rect.top	= UI_EDIT_sMONEY_Y;
		Rect.width	= UI_EDIT_sMONEY_W;
		Rect.height = UI_EDIT_sMONEY_H;
		Conv_TmoneyToDmoney(sShowStr,pTradeMoney);
		UI_ShowSmallNum(&Rect,1,sShowStr);
	}
	API_GUI_Show();
}

void APP_ShowTradeOK(char *pTradeMoney)
{
	UI_ShowBmpAndMoney("TradeOK.clz",pTradeMoney);
	API_GUI_Show();
}


int APP_ShowTradeFA(char *pShowMsg,int tTimeOutMS)
{
	RECTL	Rect;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	UI_ShowPictureFile(&Rect,"TradeFA.clz");
	if(pShowMsg)
	{
		u16 width;
		width=API_strlen(pShowMsg)*FONT_SIZE/2;
		if(width < UI_TRADE_FA_MSG_W)
		{
			Rect.top	= UI_TRADE_FA_MSG_Y+FONT_SIZE;
			Rect.left	= UI_TRADE_FA_MSG_X+(UI_TRADE_FA_MSG_W-width)/2;
			Rect.width	= width;
			Rect.height = FONT_SIZE;
		}
		else 
		{
			Rect.top	= UI_TRADE_FA_MSG_Y;
			Rect.left	= UI_TRADE_FA_MSG_X;
			Rect.width	= UI_TRADE_FA_MSG_W;
			Rect.height = UI_TRADE_FA_MSG_H;
		}
		UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
		UI_DrawRectString(&Rect,pShowMsg);
	}
	API_GUI_Show();
	return APP_WaitUiEvent(tTimeOutMS);
}

void APP_ShowRefundsOK(char *pTradeMoney)
{
	UI_ShowBmpAndMoney("RetOK.clz",pTradeMoney);
	API_GUI_Show();
}

int APP_ShowTradeMsg(char *pShowMsg,int tTimeOutMS)
{
	RECTL	Rect;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	UI_ShowPictureFile(&Rect,"Empty.clz");
	if(pShowMsg)
	{
		Rect.left	= UI_TRADE_MSG_X;
		Rect.top	= UI_TRADE_MSG_Y;
		Rect.width	= UI_TRADE_MSG_W;
		Rect.height = UI_TRADE_MSG_H;
		UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
		UI_DrawRectString(&Rect,pShowMsg);
	}
	API_GUI_Show();
	return APP_WaitUiEvent(tTimeOutMS);
}


void APP_ShowQRcodeDis(char *pQRcode,char *pTradeMoney)
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
		API_strcpy(sShowStr,STR_SUM_SIGN);
		Conv_TmoneyToDmoney(sShowStr+2,pTradeMoney);
		width=API_strlen(sShowStr)*FONT_SIZE/2;
		tFontXY.left =UI_QR_MONEY_X+ (UI_QR_MONEY_W-width)/2;
		tFontXY.top =UI_QR_MONEY_Y;
		UI_SetColorRGB565(RGB565_BLACK,RGB565_PARENT);
		UI_DrawString(&tFontXY,sShowStr);
	}
	API_GUI_Show();
}


int APP_ShowEnquiriesMsg(char *pTmoney,char* pTradeType,char* pDate,char* pTime,char* pOrderNo)
{
	u32		Event;
	RECTL	Rect;
	char 	sBuff[22];
	u16		sLen;
	POINT 	rclTrg;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	UI_ShowPictureFile(&Rect,"Empty.clz");
	//-------��ʾ���----------------
	Rect.left	= UI_ENQU_MONEY_X;
	Rect.top	= UI_ENQU_MONEY_Y+UI_ENQU_SPACING_H;
	Rect.width	= UI_ENQU_MONEY_W;
	Rect.height = UI_ENQU_MONEY_H;
	Conv_TmoneyToDmoney(sBuff,pTmoney);
	UI_ShowSmallNum(&Rect,1,sBuff);
	//---------------------------------------------------
	UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
	//-------��ʾ��������---������ʾ-------------
	Rect.top += FONT_SIZE+UI_ENQU_SPACING_H;
	sLen=API_strlen(pTradeType);
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,pTradeType);
	//-------��ʾ��������ʱ��---������ʾ-------------
	Rect.top += FONT_SIZE+UI_ENQU_SPACING_H+UI_ENQU_SPACING_H;
	API_strcpy(sBuff,STR_TRAND_TIME);
	sLen=API_strlen(sBuff);
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,sBuff);
	Rect.top += FONT_SIZE+UI_ENQU_SPACING_H;
	sLen=API_strlen(pTime);
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,pTime);
	Rect.top += FONT_SIZE;
	sLen=API_strlen(pDate);
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,pDate);
	//-------��ʾ�̻�����---������ʾ-------------
	Rect.top += FONT_SIZE+UI_ENQU_SPACING_H+UI_ENQU_SPACING_H;
	API_strcpy(sBuff,STR_TRAND_ORDER);
	sLen=API_strlen(sBuff);
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,sBuff);
	
	Rect.top += FONT_SIZE+UI_ENQU_SPACING_H;
	sLen=16;
	API_memcpy(sBuff,pOrderNo,sLen); 
	sBuff[sLen]='\0';
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,sBuff);
	Rect.top += FONT_SIZE;
	sLen=API_strlen(pOrderNo+16);
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,(pOrderNo+16));
	API_GUI_Show();
	//--------------------------------------------------------
	Event=API_WaitEvent(10*1000,EVENT_KEY,EVENT_NONE);
	if(Event&EVENT_KEY)
	{
		if((Event&EVENT_INDEX) == K_FUNC)
			return OPER_NEW;
		if((Event&EVENT_INDEX) == K_OK)
			return OPER_OK;
		return OPER_RET;
	}
	return OPER_TIMEOUT;
}

//=======================ɨ����ƺ���================================
int APP_OnlyCamScan(char flagKey,int MinLen,int MaxLen,char* pOutCode,int msTimeOut)
{
	return pSdkFun->scan->OnlyScan(flagKey,MinLen,MaxLen,pOutCode,msTimeOut);
}
int APP_GetScanVer(char *pVer)
{
	return pSdkFun->scan->GetVer(pVer);
}



//=========flagd:DΪ"��ά���տ�",RΪ"�����˿�",SΪ"ɨ���տ�",QΪ"���ײ�ѯ"=========
int APP_CamScan(char flagd,char* pHintOrTMoney,char *pOutCode,int MinLen,int MaxLen,int timeOutMs)
{
	u16 	flagKey=0x00;
	char 	sShowStr[12];
	RECTL	Rect;
	Rect.left	= UI_MAP_TITLE_X;
	Rect.top	= UI_MAP_TITLE_Y;
	Rect.width	= UI_MAP_TITLE_W;
	Rect.height = UI_MAP_TITLE_H;
	if(flagd=='D')
		UI_ShowPictureFile(&Rect,"InSumTd.clz");
	else if(flagd=='R')
		UI_ShowPictureFile(&Rect,"InSumTr.clz");
	else if(flagd=='S')
		UI_ShowPictureFile(&Rect,"InSumTs.clz");
	else if(flagd=='Q')
		UI_ShowPictureFile(&Rect,"InSumTq.clz");
	
	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	if(flagd=='R' || flagd=='Q')
	{
		UI_ShowPictureFile(&Rect,"ScanIpt.clz");
		Rect.top	= UI_SCAN_TEXT_Y;
		if(flagd=='R')	// "�����˿�"
			flagKey	= 0x02;
		else			// "���ײ�ѯ"
			flagKey	= 0x03;
	}
	else
	{
		UI_ShowPictureFile(&Rect,"ScanCod.clz");
		Rect.top	= UI_SCAN_MONEY_Y;
	}
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
			u16		Width;
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


//=========flagd:DΪ"��ά���տ�",RΪ"�����˿�",SΪ"ɨ���տ�",QΪ"���ײ�ѯ"=========
int APP_EditSum(char* pTitle,char TitleFlag,char* pOutStr,int timeOutMs)
{
	RECTL	Rect;
	u32 	Event;
	int 	ret;
	Rect.left	= UI_MAP_TITLE_X;
	Rect.top	= UI_MAP_TITLE_Y;
	Rect.width	= UI_MAP_TITLE_W;
	Rect.height = UI_MAP_TITLE_H;
	if(TitleFlag=='D')
		UI_ShowPictureFile(&Rect,"InSumTd.clz");
	else if(TitleFlag=='R')
		UI_ShowPictureFile(&Rect,"InSumTr.clz");
	else if(TitleFlag=='S')
		UI_ShowPictureFile(&Rect,"InSumTs.clz");
	else if(TitleFlag=='Q')
		UI_ShowPictureFile(&Rect,"InSumTq.clz");

	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	UI_ShowPictureFile(&Rect,"InSumE.clz");
	API_GUI_InputEdit(pOutStr,7,IME_SUM,UI_EditShowMoney);
	API_GUI_Show();
	while(1)
	{
		Event=API_WaitEvent(timeOutMs,EVENT_UI,EVENT_NONE);
		if(Event==EVENT_OK) //��ȡ���뿨������
		{
			ret=API_GUI_Edit_GetText(pOutStr,12);
			if(ret>7)
				APP_HitMsg(STR_EDIT_AMOUNT_INVALID,1500);
			else if(ret >= 1)
				return ret;
			else
				APP_HitMsg(STR_EDIT_AMOUNT_NULL,1500);
			API_GUI_InputEdit(pOutStr,7,0,UI_EditShowMoney);
			continue;
		}
		if(Event==EVENT_TIMEOUT)
		{
			return OPER_TIMEOUT;
		}
		return OPER_RET;
	}
}



int APP_OperEdit(char* pTitle,char* pOutStr,int Min,int Max,int timeOutMs)
{
	RECTL	Rect;
	u32 	Event,Way;
	int 	ret;
	Rect.left	= UI_MAP_TITLE_X;
	Rect.top	= UI_MAP_TITLE_Y;
	Rect.width	= UI_MAP_TITLE_W;
	Rect.height = UI_MAP_TITLE_H;
	UI_ShowPictureFile(&Rect,"operTi.clz");

	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	if(pTitle!=NULL && NULL!=API_strstr(pTitle,"����"))
	{
		UI_ShowPictureFile(&Rect,"operPs.clz");
		Way=IME_NUM|IME_PIN_MODE;
	}
	else
	{
		UI_ShowPictureFile(&Rect,"operId.clz");
		Way=IME_NUM;
	}
	API_GUI_InputEdit(pOutStr,Max,Way,UI_ImgShowNum);
	API_GUI_Show();
	while(1)
	{
		Event=API_WaitEvent(timeOutMs,EVENT_UI,EVENT_NONE);
		if(Event==EVENT_OK) //��ȡ���뿨������
		{
			ret=API_GUI_Edit_GetText(pOutStr,12);
			if(ret >= Min)
				return ret;
			APP_HitMsg("��Ч����",1500);
			API_GUI_InputEdit(pOutStr,Max,0,UI_ImgShowNum);
			continue;
		}
		if(Event==EVENT_TIMEOUT)
		{
			return OPER_TIMEOUT;
		}
		return OPER_RET;
	}
}

/*
//======��������======================
int APP_GUI_SetVolume(char *pTitle)
{
	u16 MessageID,Message;
	int volume,Ret=OPER_TIMEOUT;
	API_GUI_CreateWindow(pTitle,TOK,TCANCEL,0);
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM,"��[1]����,��[7]����");
	API_GUI_Show();
	volume=AudioGetVolume();
	UI_ShowParMiddleSlide(volume,volume*10);
	Set_WaitEvent(30*1000,EVENT_KEY);
	while(1)
	{
		if(FIFO_OperatGetMsg(&MessageID,&Message))
		{
			if(MessageID == EVEN_ID_KEY_DOWN)
			{
				if(Message==K_OK)
				{
					Ret=AudioSetVolume(volume);
					TRACE("AudioSetVolume-[%d]\r\n",Ret);
					if(Ret<0)
					{
						TRACE("AudioSetVolume-[%d][%x]\r\n",Ret,GetLastError());
					}
					Sleep(150);
					APP_TTS_PlayText("������Ϊ%d",volume);
					Ret=OPER_OK;
					break;
				}
				if(Message==K_CANCEL)
				{
					Ret=OPER_RET;
					break;
				}
				Rewrite_WaitTime(30*1000);
				if(Message==K_1)
				{
					if(volume<9)
					{//InCode
						volume++;
						UI_ShowParMiddleSlide(volume,volume*10);
					}
				}
				else if(Message==K_7)
				{
					if(volume>1)
					{//InCode
						volume--;
						UI_ShowParMiddleSlide(volume,volume*10);
					}
				}
			}
			else if(MessageID == EVEN_ID_TIME_OUT)
			{
				Ret=OPER_TIMEOUT;
				break;
			}
		}
	}
	Set_WaitEvent(TIME_INFINE,EVENT_NONE);
	return Ret;
}
//=========flagd:DΪ"��ά���տ�",RΪ"�����˿�",SΪ"ɨ���տ�",QΪ"���ײ�ѯ"=========
int APP_EditSum(char* pTitle,char TitleFlag,char* pOutStr,int timeOutMs)
{
	u16		MessageID,Message,Index;
	u16	OldLen,InPutFlag=0;
	char	pEditBuff[12];
	int		mCentInt,ret;
	RECTL	Rect;
	Rect.left	= UI_MAP_TITLE_X;
	Rect.top	= UI_MAP_TITLE_Y;
	Rect.width	= UI_MAP_TITLE_W;
	Rect.height = UI_MAP_TITLE_H;
	if(TitleFlag=='D')
		UI_ShowPictureFile(&Rect,L"E:\\bmp\\InSumTd.bin");
	else if(TitleFlag=='R')
		UI_ShowPictureFile(&Rect,L"E:\\bmp\\InSumTr.bin");
	else if(TitleFlag=='S')
		UI_ShowPictureFile(&Rect,L"E:\\bmp\\InSumTs.bin");
	else if(TitleFlag=='Q')
		UI_ShowPictureFile(&Rect,L"E:\\bmp\\InSumTq.bin");

	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	UI_ShowPictureFile(&Rect,L"E:\\bmp\\InSumE.bin");
	Conv_TmoneyToDmoney(pEditBuff,pOutStr);
	UI_EditShowMoney(TRUE,pEditBuff);
	DisplayPaintEnd();	
	Index=0;//��ʼ����
	pEditBuff[Index]='\0'; //��ʼ����
	Set_WaitEvent(timeOutMs,EVENT_KEY);
	ret=OPER_TIMEOUT;
	while(1)
	{
		if(FIFO_OperatGetMsg(&MessageID,&Message))
		{
			if(MessageID == EVEN_ID_KEY_DOWN)
			{
				Rewrite_WaitTime(timeOutMs);
				if(Message==K_OK)
				{
					if(InPutFlag)
					{
						mCentInt=Conv_MoneyToCentInt(pEditBuff);
						if(mCentInt>0 && mCentInt<=1000000)
						{
							return Conv_DmoneyToTmoney(pOutStr,pEditBuff);
						}
						APP_HitMsg(STR_EDIT_AMOUNT_INVALID,1500);
					}
					else	//δ����ֱ�Ӱ�ȷ�ϼ�
					{
						OldLen=API_strlen(pOutStr);
						if(OldLen>0)
						{
							ret=OldLen;
							break;
						}
						APP_HitMsg(STR_EDIT_AMOUNT_NULL,1500);
					}
				}
				else if(Message==K_CANCEL)
				{
					ret=OPER_RET;
					break;
				}
				else if(Message==K_DEL)
				{
					Index=0;
					pEditBuff[Index]='\0';
					UI_EditShowMoney(FALSE,pEditBuff);
					DisplayPaintEnd();
					InPutFlag=1;
				}
				else if((Message>=K_0 && Message<=K_9)||(Message == K_D))
				{
					if(Index>6)
						continue;
					pEditBuff[Index++]=Message;
					pEditBuff[Index]='\0';
					mCentInt=Conv_MoneyToCentInt(pEditBuff);
					if(mCentInt<0)
					{
						pEditBuff[--Index]='\0';
						continue;
					}
					UI_EditShowMoney(FALSE,pEditBuff);
					DisplayPaintEnd();
					InPutFlag=1;
				}
			}
			else if(MessageID == EVEN_ID_TIME_OUT)
			{
				ret=OPER_TIMEOUT;
				break;
			}
		}
	}
	Set_WaitEvent(TIME_INFINE,EVENT_NONE);
	return ret;
}
*/
int APP_EDIT_SetDateTime(char* title)
{
	char str[10];
	u16	 MaxDay;  
	SYSTEMTIME	dtime;
	GetLocalTime(&dtime);	
	API_sprintf(str,"%04d%02d%02d",dtime.wYear,dtime.wMonth,dtime.wDay); 
    if(0 == APP_InputNum(title,"��������[������]:","[8λ]���ְ�������", str, 8,8))
	{
		dtime.wDay  =API_atoi(str+6);
		str[6]='\0';
		dtime.wMonth=API_atoi(str+4);
		str[4]='\0';
		dtime.wYear=API_atoi(str);
		//MercuryTrace("DateTime:[%s] [%02d:%02d:%02d]",str,dtime.wHour,dtime.wMinute,dtime.wSecond);
		MaxDay=30+(((dtime.wMonth&1)^(dtime.wMonth&8)>>3)!=0)-(dtime.wMonth==2)*2+(!(dtime.wYear%4)&&(dtime.wYear%100)&&(dtime.wMonth==2)||!(dtime.wYear%400));
		if( (dtime.wYear<1900 || dtime.wYear>2100) || (dtime.wMonth<1 || dtime.wMonth>12) || (dtime.wDay<1 || dtime.wDay>MaxDay))
		{
			APP_ShowMsg(title,"���ڸ�ʽ����",3000);
			return -4;
		}
		SetLocalTime(&dtime);
		API_sprintf(str,"%02d%02d",dtime.wHour,dtime.wMinute); 
		if(0 == APP_InputNum(title,"����ʱ��[ʱ��]:","[4λ]���ְ�������",str,4,4))
		{
			dtime.wMinute=API_atoi(str+2);
			str[2]='\0';
			dtime.wHour=API_atoi(str);
			if(( dtime.wHour>23) || ( dtime.wMinute>59))
			{
				APP_ShowMsg(title,"ʱ���ʽ����",3000);
				return -4;
			}
			SetLocalTime(&dtime);
			APP_ShowMsg(title,"�������",3000);
		}
		return 0;
    }
    return -1;
}



int APP_Check_DateTime(char* title)
{
	int ret=0;
	SYSTEMTIME	dtime;
	GetLocalTime(&dtime);
	if(dtime.wYear < 2018)
	{
		ret=APP_EDIT_SetDateTime(title);
	}
	if(ret < 0)
	{
		ret=pSdkFun->sdk->tmsSyn(title);
	}
	return 0;
}

//=========flagd:RΪ"�����˿�",QΪ"���ײ�ѯ"=========
int APP_InputMerchSN(char flagd,char* pOutStr,int MinLen,int Maxlen,int timeOutMs)
{
	RECTL	Rect;
	u32 	Event;
	int 	ret;
	Rect.left	= UI_MAP_TITLE_X;
	Rect.top	= UI_MAP_TITLE_Y;
	Rect.width	= UI_MAP_TITLE_W;
	Rect.height = UI_MAP_TITLE_H;
	if(flagd=='R')
		UI_ShowPictureFile(&Rect,"InSumTr.clz");
	else if(flagd=='Q')
		UI_ShowPictureFile(&Rect,"InSumTq.clz");

	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	UI_ShowPictureFile(&Rect,"InCode.clz");
	API_GUI_InputEdit(pOutStr,Maxlen,IME_NUM|IME_ABC|IME_abc,UI_EditShowStr);
	API_GUI_Show();
	while(1)
	{
		Event=API_WaitEvent(timeOutMs,EVENT_UI,EVENT_NONE);
		if(Event==EVENT_OK) //��ȡ���뿨������
		{
			ret=API_GUI_Edit_GetText(pOutStr,Maxlen+1);
			if(ret >= MinLen)
				return ret;
			else
				APP_HitMsg(STR_LACK_INPUT,1500);
			API_GUI_InputEdit(pOutStr,Maxlen,0,UI_EditShowStr);
			continue;
		}
		if(Event==EVENT_TIMEOUT)
		{
			return OPER_TIMEOUT;
		}
		return OPER_RET;
	}
}




/**
 * ��ȡ��ǰ������,��λ:����
 * 
 * @return ϵͳ��ǰ������
 */	
int  API_TimeCurrMS(void)
{
	return pSysFun->GetTickCount();
}

void APP_ScreenSleep(u8 En)
{
	
	pSdkFun->sdk->ScreenSleep(En);
}

int APP_GetHardMsg(u8 type,void *pOut,int OutSize)
{
	return pSdkFun->sdk->GetHardMsg(type,pOut,OutSize);
}

int APP_SetHardMsg(u8 type,void *pOut,int OutSize)
{
	return pSdkFun->sdk->SetHardMsg(type,pOut,OutSize);
}

int TMS_GetParVersion(char* pParVer,int sizeVer)
{
	return pSdkFun->sdk->tmsVer(pParVer,sizeVer);
}



