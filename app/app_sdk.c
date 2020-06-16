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
		pGuiFun->Show();
		Event=APP_WaitUiEvent(pEdit->timeOutMs);
		if(Event==EVENT_OK) //获取输入卡号数据
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
//输入数字+字母
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
		APP_ShowMsg(pTitle,STR_PASSWORD_ERR,3000);	
	}
	return -1;
}

//====================================================================
//功能:    保存参数到文件系统
//输入数据:pfilePath(文件名),pBuff(参数缓冲区),Inlen(文件长度)
//输出数据:写入结果 0 为成功
//作者:     邓国祖	---	
//创作时间:  20150916
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
//功能:    从文件系统读参数
//输入数据:pfilePath(文件名),pBuff(参数缓冲区),pOutlen(输入文件长度)
//输出数据:读取结果 0 为成功
//作者:     邓国祖	---	
//创作时间:  20150916
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



//======交易方式(1支付宝、2微信)====================
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
			Rect.top	= UI_TRADE_FA_MSG_Y;
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
	if(UI_ShowPictureFile(&Rect,"Empty.clz"))
	{
		return APP_ShowMsg("交易信息",pShowMsg,tTimeOutMS);
	}
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
	//-------显示金额----------------
	Rect.left	= UI_ENQU_MONEY_X;
	Rect.top	= UI_ENQU_MONEY_Y+UI_ENQU_SPACING_H;
	Rect.width	= UI_ENQU_MONEY_W;
	Rect.height = UI_ENQU_MONEY_H;
	Conv_TmoneyToDmoney(sBuff,pTmoney);
	UI_ShowSmallNum(&Rect,1,sBuff);
	//---------------------------------------------------
	UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
	//-------显示交易类型---居中显示-------------
	Rect.top += FONT_SIZE+UI_ENQU_SPACING_H;
	sLen=API_strlen(pTradeType);
	rclTrg.left=Rect.left+(Rect.width - sLen*FONT_SIZE/2)/2;
	rclTrg.top=Rect.top;
	UI_DrawString(&rclTrg,pTradeType);
	//-------显示交易日期时间---居中显示-------------
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
	//-------显示商户单号---居中显示-------------
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

//=======================扫码控制函数================================
int APP_OnlyCamScan(char flagKey,int MinLen,int MaxLen,char* pOutCode,int msTimeOut)
{
	return pSdkFun->app->OnlyCamScan(flagKey,MinLen,MaxLen,pOutCode,msTimeOut);
}
char* APP_GetMasterVer(void)
{
	return pSdkFun->app->GetMasterVersion();
}



//=========flagd:D为"二维码收款",R为"订单退款",S为"扫码收款",Q为"交易查询"=========
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
		if(flagd=='R')	// "订单退款"
			flagKey	= 0x02;
		else			// "交易查询"
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


//=========flagd:D为"二维码收款",R为"订单退款",S为"扫码收款",Q为"交易查询"=========
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
		ret=UI_ShowPictureFile(&Rect,"InSumTd.clz");
	else if(TitleFlag=='R')
		ret=UI_ShowPictureFile(&Rect,"InSumTr.clz");
	else if(TitleFlag=='S')
		ret=UI_ShowPictureFile(&Rect,"InSumTs.clz");
	else if(TitleFlag=='Q')
		ret=UI_ShowPictureFile(&Rect,"InSumTq.clz");
	if(ret) return -1;	//没有图片返回

	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	ret=UI_ShowPictureFile(&Rect,"InSumE.clz");
	if(ret) return -1;	//没有图片返回
	API_GUI_InputEdit(pOutStr,7,IME_SUM,UI_EditShowMoney);
	API_GUI_Show();
	while(1)
	{
		Event=API_WaitEvent(timeOutMs,EVENT_UI,EVENT_NONE);
		if(Event==EVENT_OK) //获取输入卡号数据
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
	ret=UI_ShowPictureFile(&Rect,"operTi.clz");
	if(ret) return -1;	//没有图片返回

	Rect.top	= UI_MAP_CONT_Y;
	Rect.height = UI_MAP_CONT_H;
	if(pTitle!=NULL && NULL!=API_strstr(pTitle,"密码"))
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
		if(Event==EVENT_OK) //获取输入卡号数据
		{
			ret=API_GUI_Edit_GetText(pOutStr,12);
			if(ret >= Min)
				return ret;
			APP_HitMsg("无效输入",1500);
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
//======音量设置======================
int APP_GUI_SetVolume(char *pTitle)
{
	u16 MessageID,Message;
	int volume,Ret=OPER_TIMEOUT;
	API_GUI_CreateWindow(pTitle,TOK,TCANCEL,0);
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM,"按[1]键加,按[7]键减");
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
					APP_TTS_PlayText("音量设为%d",volume);
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
//=========flagd:D为"二维码收款",R为"订单退款",S为"扫码收款",Q为"交易查询"=========
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
	Index=0;//初始长度
	pEditBuff[Index]='\0'; //初始参数
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
					else	//未输入直接按确认键
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
	u16  MaxDay; 
	ST_TIME tTime;
	OsGetTime(&tTime);
	API_sprintf(str,"%04d%02d%02d",tTime.Year,tTime.Month,tTime.Day); 
	if(0 == APP_InputNum(title,"输入日期[年月日]:","[8位]数字按键输入", str, 8,8))
	{
		tTime.Day  =API_atoi(str+6);
		str[6]='\0';
		tTime.Month=API_atoi(str+4);
		str[4]='\0';
		tTime.Year=API_atoi(str);
		//MercuryTrace("DateTime:[%s] [%02d:%02d:%02d]",str,dtime.wHour,dtime.wMinute,dtime.wSecond);
		MaxDay = 30+(((tTime.Month&1)^(tTime.Month&8)>>3)!=0)-(tTime.Month==2)*2+((tTime.Month==2) \
		&&((((tTime.Year&0x03)==0)&&((tTime.Year%100)!=0))||((tTime.Year%400)==0)));
		if( (tTime.Year<1900 || tTime.Year>2100) || (tTime.Month<1 || tTime.Month>12) || (tTime.Day<1 || tTime.Day>MaxDay))
		{
			APP_ShowMsg(title,"日期格式错误",3000);
			return EVENT_NONE;
		}
		OsSetTime(&tTime);
		API_sprintf(str,"%02d%02d",tTime.Hour,tTime.Minute); 
		if(0 == APP_InputNum(title,"输入时间[时分]:","[4位]数字按键输入",str,4,4))
		{
			tTime.Minute=API_atoi(str+2);
			str[2]='\0';
			tTime.Hour=API_atoi(str);
			if(( tTime.Hour>23) || ( tTime.Minute>59))
			{
				APP_ShowMsg(title,"时间格式错误",3000);
				return EVENT_NONE;
			}
			OsSetTime(&tTime);
			APP_ShowMsg(title,"设置完成",3000);
		}
		return EVENT_NONE;
	}
	return EVENT_NONE;
}


int APP_Check_DateTime(char* title)
{
	int ret=0;
	ST_TIME	dtime;
	OsGetTime(&dtime);
	if(dtime.Year < 2018)
	{
		ret=APP_EDIT_SetDateTime(title);
	}
	if(ret < 0)
	{
	//	ret=pSdkFun->sdk->tmsSyn(title);
	}
	return 0;
}

//=========flagd:R为"订单退款",Q为"交易查询"=========
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
		if(Event==EVENT_OK) //获取输入卡号数据
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
 * 获取当前毫秒数,单位:豪秒
 * 
 * @return 系统当前毫秒数
 */	
int  API_TimeCurrMS(void)
{
	return api_SysFun.GetTickCount();
}

u32 OsGetTimeStamp(void)
{
	return 12312312;
}


void OsSleep(unsigned int Ms)
{
	 api_SysFun.Sleep(Ms);
}

int OsSetTime(ST_TIME *Time)
{
	return api_SysFun.SetTime(Time);
}
void OsGetTime(ST_TIME *Time)
{
	api_SysFun.GetTime(Time);
}

void APP_ScreenSleep(u8 En)
{
	pSdkFun->app->SetSleep(En);
}

int APP_GetHardMsg(u8 type,void *pOut,int OutSize)
{
	return pSdkFun->app->GetHardMsg(type,pOut,OutSize);
}

int APP_SetHardMsg(u8 type,void *pOut,int OutSize)
{
	return pSdkFun->app->SetHardMsg(type,pOut,OutSize);
}

void API_SetLanguage(int language)
{
	pGuiFun->SetLanguage(language);
}


int APP_AudioDtmfPlay(u8 tone,u8 time100Ms)
{
	return pSdkFun->app->Dtmf_Play(tone,time100Ms*10);
}

void AudioSetVolume(int volume)
{
	pSdkFun->app->AudioSetVolume(volume);
}
int AudioGetVolume(void)
{
	return pSdkFun->app->AudioGetVolume();
}

