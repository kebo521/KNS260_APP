//============================================================
//---显示功能---
#include "communal.h"

#ifdef __cplusplus
extern "C" {
#endif


UI_DisplayTheme tUI_Theme;

//===========标准主题==========================
const UI_DisplayTheme UI_comTheme=
{
	"按[↓]键下翻页",
	"按[↑]键上翻页",
	"↑]上翻页,↓]下翻页",

	"Small_f.clz",
	UI_EDIT_sMONEY_fW,
	UI_EDIT_sMONEY_fH,
};


void UI_LoadTheme(const UI_DisplayTheme *pTheme)
{
	API_memcpy(&tUI_Theme,pTheme,sizeof(UI_DisplayTheme));
}

void UI_DisplayInit(void)
{
	UI_LoadTheme(&UI_comTheme);
}

//=========设置菜单界面显示多少行菜单项=================
void UI_SetMenuItem(int num)
{
	pGuiFun->LoadWindow(pGuiFun->GetWindow(NULL),num);
}
//=====================区域图片备份======================================
RECTL tBitMapRect;
A_RGB* pBitMapBuff=NULL;

void UI_DisplayBitMapGet(u16 x,u16 y,u16 w,u16 h)
{
	tBitMapRect.left = x;
	tBitMapRect.top = y;
	tBitMapRect.width = w;
	tBitMapRect.height = h;
	if(pBitMapBuff) free(pBitMapBuff);
	pBitMapBuff=(A_RGB*)malloc(w*h*sizeof(A_RGB));
	pGuiFun->GetRectBuff(&tBitMapRect,pBitMapBuff);
}

void UI_DisplayBitMapSet(void)
{
	pGuiFun->SetRectBuff(&tBitMapRect,pBitMapBuff);
}
void UI_DisplayBitMapEND(void)
{
	if(pBitMapBuff)
	{
		free(pBitMapBuff);
		pBitMapBuff = NULL;
	}
}
//================================画框=======================================================
void UI_ShowColorRect(RECTL *pRect,int Width,A_RGB Color)
{
	pGuiFun->ShowRect(pRect,Width,Color);
}

//=============================================================================
void UI_SetColorRGB565(A_RGB fgColor, u32 bgColor)
{
	pFontFun->SetFontColor(fgColor,bgColor);
}
int UI_DrawString(POINT* prclTrg,const char *src)
{
	return pGuiFun->DrawLineString(prclTrg,src);
}

int UI_DrawRectString(RECTL* pRect,const char *src)
{
	return pGuiFun->DrawRectString(pRect,src);

}

//==========自定义编辑器(自定义UI显示====================
void API_GUI_InputEdit(char* pStrDef,int tMaxLen,u32 Way,Fun_ShowNum pShow)
{
	pGuiFun->InputEdit(pStrDef,tMaxLen,Way,pShow);
}


//static u8 SPF_runLock=FALSE;
int UI_ShowPictureFile(RECTL *prclTrg,const char *pfilePath)
{
	return pGuiFun->ShowPicture(prclTrg,pfilePath);
}

void API_GUI_OprInfo(char* pShowInfo,char *pAfterText)
{
	pGuiFun->OprInfo(pShowInfo,pAfterText);
}

void UI_EditShowMoney(u32 flagPs,char* pMoney)
{
	u8 sLen,i;
	u16 width;
	RECTL Rect;
	//---￥:14x19 .:14x30 0~9:22x30-----
	sLen=API_strlen(pMoney);
	for(i=0;i<sLen;i++)
		if(pMoney[i]=='.')
			break;
	if(i<sLen)
		width=UI_EDIT_bMONEY_fW+ sLen*UI_EDIT_bMONEY_sW -(UI_EDIT_bMONEY_sW-UI_EDIT_bMONEY_dW);
	else
		width=UI_EDIT_bMONEY_fW+ sLen*UI_EDIT_bMONEY_sW;

	Rect.left	= UI_EDIT_bMONEY_X;
	Rect.top	= UI_EDIT_bMONEY_Y;
	Rect.width	= UI_EDIT_bMONEY_W;
	if(flagPs&0x80000000)
	{
		Rect.height = UI_EDIT_bMONEY_H;
		UI_DisplayBitMapGet(Rect.left,Rect.top,Rect.width,Rect.height);
	}
	else
	{
		UI_DisplayBitMapSet();
	}
	Rect.left += (Rect.width-width)/2;
	Rect.width	= UI_EDIT_bMONEY_fW;
	Rect.height = UI_EDIT_bMONEY_fH;
	UI_ShowPictureFile(&Rect,"InSumf.clz");
	Rect.left	+= UI_EDIT_bMONEY_fW;
	Rect.top	+= UI_EDIT_bMONEY_H-UI_EDIT_bMONEY_sH;
	
	Rect.height = UI_EDIT_bMONEY_sH;
	for(i=0;i<sLen;i++)
	{
		if(pMoney[i]=='.')
		{
			Rect.width	= UI_EDIT_bMONEY_dW;
			UI_ShowPictureFile(&Rect,"InSumd.clz");
			Rect.left	+= UI_EDIT_bMONEY_dW;
		}
		else 
		{
			Rect.width	= UI_EDIT_bMONEY_sW;
			if(pMoney[i]=='0')
				UI_ShowPictureFile(&Rect,"InSum0.clz");
			else if(pMoney[i]=='1')
				UI_ShowPictureFile(&Rect,"InSum1.clz");
			else if(pMoney[i]=='2')
				UI_ShowPictureFile(&Rect,"InSum2.clz");
			else if(pMoney[i]=='3')
				UI_ShowPictureFile(&Rect,"InSum3.clz");
			else if(pMoney[i]=='4')
				UI_ShowPictureFile(&Rect,"InSum4.clz");
			else if(pMoney[i]=='5')
				UI_ShowPictureFile(&Rect,"InSum5.clz");
			else if(pMoney[i]=='6')
				UI_ShowPictureFile(&Rect,"InSum6.clz");
			else if(pMoney[i]=='7')
				UI_ShowPictureFile(&Rect,"InSum7.clz");
			else if(pMoney[i]=='8')
				UI_ShowPictureFile(&Rect,"InSum8.clz");
			else if(pMoney[i]=='9')
				UI_ShowPictureFile(&Rect,"InSum9.clz");
			Rect.left	+= UI_EDIT_bMONEY_sW;
		}
	}
}

void UI_EditShowStr(u32 flagPs,char* pBuff)
{
	if(pBuff==NULL)
	{
		if(flagPs & IME_NUM)
		{
			APP_HitMsg("数字输入",1500);
		}
		else if(flagPs & IME_ABC)
		{
			APP_HitMsg("大写字母输入",1500);
		}
		else if(flagPs & IME_abc)
		{
			APP_HitMsg("小写字母输入",1500);
		}
		return;
	}
	else
	{
		RECTL	Rect;
		Rect.left	= UI_EDIT_MERCH_SN_X;
		Rect.top	= UI_EDIT_MERCH_SN_Y;
		Rect.width	= UI_EDIT_MERCH_SN_W;
		Rect.height = UI_EDIT_MERCH_SN_H;
		if(flagPs&0x80000000)
		{
			UI_DisplayBitMapGet(Rect.left,Rect.top,Rect.width,Rect.height);
		}
		else
		{
			UI_DisplayBitMapSet();
		}
		UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
		UI_DrawRectString(&Rect,pBuff);
	}
}

void UI_ShowSmallNum(RECTL *prclTrg,int flagMoney,char *pNum)
{
	u8 sLen,i;
	u16 width;
	RECTL Rect;
	//---￥:9x13 .:9x22 0~9:16x22-----
	sLen=API_strlen(pNum);
	if(flagMoney)
	{
		width=tUI_Theme.sMoney_fW+ sLen*UI_EDIT_sMONEY_sW -(UI_EDIT_sMONEY_sW-UI_EDIT_sMONEY_dW);
	}
	else
	{
		for(i=0;i<sLen;i++)
		{
			if(pNum[i]=='.') break;
		}
		if(i<sLen)
			width=sLen*UI_EDIT_sMONEY_sW -(UI_EDIT_sMONEY_sW-UI_EDIT_sMONEY_dW);
		else
			width=sLen*UI_EDIT_sMONEY_sW;
	}
	Rect.left = prclTrg->left+(prclTrg->width - width)/2;
	Rect.top	= prclTrg->top;
	Rect.width	= tUI_Theme.sMoney_fW;
	Rect.height = tUI_Theme.sMoney_fH;
	UI_ShowPictureFile(&Rect,tUI_Theme.pMoney_fName);
	
	Rect.left	+= tUI_Theme.sMoney_fW;
	Rect.height = UI_EDIT_sMONEY_sH;
	Rect.top	= prclTrg->top+prclTrg->height-Rect.height;
	for(i=0;i<sLen;i++)
	{
		if(pNum[i]=='.')
		{
			Rect.width	= UI_EDIT_sMONEY_dW;
			UI_ShowPictureFile(&Rect,"Small_d.clz");
			Rect.left	+= UI_EDIT_sMONEY_dW;
		}
		else 
		{
			Rect.width	= UI_EDIT_sMONEY_sW;
			if(pNum[i]=='0')
				UI_ShowPictureFile(&Rect,"Small0.clz");
			else if(pNum[i]=='1')
				UI_ShowPictureFile(&Rect,"Small1.clz");
			else if(pNum[i]=='2')
				UI_ShowPictureFile(&Rect,"Small2.clz");
			else if(pNum[i]=='3')
				UI_ShowPictureFile(&Rect,"Small3.clz");
			else if(pNum[i]=='4')
				UI_ShowPictureFile(&Rect,"Small4.clz");
			else if(pNum[i]=='5')
				UI_ShowPictureFile(&Rect,"Small5.clz");
			else if(pNum[i]=='6')
				UI_ShowPictureFile(&Rect,"Small6.clz");
			else if(pNum[i]=='7')
				UI_ShowPictureFile(&Rect,"Small7.clz");
			else if(pNum[i]=='8')
				UI_ShowPictureFile(&Rect,"Small8.clz");
			else if(pNum[i]=='9')
				UI_ShowPictureFile(&Rect,"Small9.clz");
			Rect.left	+= UI_EDIT_sMONEY_sW;
		}
	}
}

//====显示背景图片与参数,pfilePath图片文件名,pMsg参数信息,mTop背景图片上的垂直位置===
void UI_ShowScreenBmp(const char* pfilePath,char* pMsg,u16 mTop)
{
	//pSdkFun->ui->ShowScreenBmp(pfilePath,pMsg,mTop);
	RECTL	Rect;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	UI_ShowPictureFile(&Rect,pfilePath);
	if(pMsg)
	{
		u16 width;
		Rect.left=FONT_SIZE/2;
		Rect.top =SCREEN_APP_Y+mTop;
		Rect.width= (SCREEN_APP_W-FONT_SIZE);
		Rect.height = FONT_SIZE+FONT_SIZE;
		width=API_strlen(pMsg)*FONT_SIZE/2;
		if(width < Rect.width)
			Rect.left += (Rect.width-width)/2;

		UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
		UI_DrawRectString(&Rect,pMsg);
	}
	API_GUI_Show();
}

void UI_ShowBmpAndMoney(const char* pfilePath,char* pTradeMoney)
{
	RECTL	Rect;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	UI_ShowPictureFile(&Rect,pfilePath);
	if(pTradeMoney)
	{
		Rect.left	= UI_EDIT_sMONEY_X;
		Rect.top	= UI_EDIT_sMONEY_Y;
		Rect.width	= UI_EDIT_sMONEY_W;
		Rect.height = UI_EDIT_sMONEY_H;
		if(pTradeMoney[0]>='0' && pTradeMoney[0] <= '9')
		{
			char		sShowStr[12];
			Conv_TmoneyToDmoney(sShowStr,pTradeMoney);
			UI_ShowSmallNum(&Rect,1,sShowStr);
		}
		else
		{
			POINT rclTrg;
			u16		Width;
			Width = API_strlen(pTradeMoney)*FONT_SIZE/2;
			if(Width < Rect.width)
				rclTrg.left=Rect.left+(Rect.width-Width)/2;
			else rclTrg.left=Rect.left;
			rclTrg.top =Rect.top;
			UI_SetColorRGB565(RGB565_WITHE,RGB565_PARENT);
			UI_DrawString(&rclTrg,pTradeMoney);
		}
	}
}


//========屏显示外框('0'显示微信图标绿,'1'显示支付宝图标蓝)========================
int UI_ShowRQRect(char* pFlag)
{
	RECTL	Rect;
	Rect.left	= SCREEN_APP_X;
	Rect.top	= SCREEN_APP_Y;
	Rect.width	= SCREEN_APP_W;
	Rect.height = SCREEN_APP_H;
	if(pFlag[0]=='0')
		UI_ShowColorRect(&Rect,9,RGB565(3,208,13));
	else if(pFlag[0]=='1')
		UI_ShowColorRect(&Rect,9,RGB565(0,169,237));
	API_GUI_Show();
	return 0;
}

//=============底部显示进度条==ratio(0~100)===============================
void UI_ShowBottomProgress(u8 ratio)
{
	pGuiFun->ShowBottomProgress(ratio);
}

//=============显示滑轨==ratio(0~100)===============================
void UI_ShowParMiddleSlide(u8 par,int ratio)
{
	POINT fTrg;
	int ret;
	char sbuff[4];
	LPGuiWindow pWindow;
	pWindow=pGuiFun->GetWindow(NULL);
	pUiFun->ShowParMiddleSlide(pWindow,ratio);

	ret=sprintf(sbuff,"%d",par);
	fTrg.left = SCREEN_APP_X+(SCREEN_APP_W-ret*FONT_SIZE/2)/2;
	fTrg.top = SCREEN_APP_Y+ (SCREEN_APP_H-32)/2  +32;
	pFontFun->SetFontColor(RGB565(56,56,56),RGB565(255,255,255));
	pFontFun->DrawLineString(pWindow,&fTrg,sbuff);
	pGuiFun->Show();
}

//===============清除显示内容(指定区域)=================================================
void API_GUI_ClearScreen(RECTL* pRect)
{
	pGuiFun->ClearScreen(pRect);
}

//================================================================
int   API_GUI_CreateWindow(const char* pTitle,const char* pOk,const char* pCancel,u32 tGuiType)
{
	return pGuiFun->CreateShowWindow(pTitle,pOk,pCancel);
}


int  API_GUI_Info(const IMAGE* pImg,u32 tTextType,const char* pTextBuf)
{
	return pGuiFun->Info(pImg,tTextType,pTextBuf);
}

void API_GUI_Edit_Prompt(u32 tFrontTextType,char* pFrontTextBuf,u32 tAfterTextType,char* pAfterTextBuf)
{
	pGuiFun->Edit_Prompt(tFrontTextType,pFrontTextBuf,tAfterTextType,pAfterTextBuf);
}

void API_GUI_Edit(u32 tTextType,char* pTextDef,int tMaxLen,u32 tImeType,u32 tImeLimit)
{
	pGuiFun->Edit_Control(tTextType,pTextDef,tMaxLen,tImeType,tImeLimit);
}

int API_GUI_Edit_GetText(char* pAscText,int tMaxLen)
{
	return pGuiFun->Edit_GetText(pAscText,tMaxLen);
}



//===================================================================================
void UI_ImgShowNum(u32 flagPs,char* pStrNum)
{
	u8 sLen,i;
	RECTL Rect;
	if(flagPs&0x80000000)
	{
		Rect.left	= UI_EDIT_bMONEY_X;
		Rect.top	= UI_EDIT_bMONEY_Y;
		Rect.width	= UI_EDIT_bMONEY_W;
		Rect.height = UI_EDIT_bMONEY_H;
		UI_DisplayBitMapGet(Rect.left,Rect.top,Rect.width,Rect.height);
	}
	else
	{
		UI_DisplayBitMapSet();
	}
	sLen=API_strlen(pStrNum);
	if(sLen)
	{
		//--- 0~9:22x30-----
		Rect.left = UI_EDIT_bMONEY_X+(UI_EDIT_bMONEY_W-(sLen*UI_EDIT_bMONEY_sW))/2;
		Rect.top = UI_EDIT_bMONEY_Y+(UI_EDIT_bMONEY_H-UI_EDIT_bMONEY_sH)/2;
		Rect.width	= UI_EDIT_bMONEY_sW;
		Rect.height = UI_EDIT_bMONEY_sH;
		for(i=0;i<sLen;i++)
		{
			if(flagPs&0xff)
				UI_ShowPictureFile(&Rect,"InSumX.clz");
			else switch(pStrNum[i])
			{
				case '0': UI_ShowPictureFile(&Rect,"InSum0.clz"); break;
				case '1': UI_ShowPictureFile(&Rect,"InSum1.clz"); break;
				case '2': UI_ShowPictureFile(&Rect,"InSum2.clz"); break;
				case '3': UI_ShowPictureFile(&Rect,"InSum3.clz"); break;
				case '4': UI_ShowPictureFile(&Rect,"InSum4.clz"); break;
				case '5': UI_ShowPictureFile(&Rect,"InSum5.clz"); break;
				case '6': UI_ShowPictureFile(&Rect,"InSum6.clz"); break;
				case '7': UI_ShowPictureFile(&Rect,"InSum7.clz"); break;
				case '8': UI_ShowPictureFile(&Rect,"InSum8.clz"); break;
				case '9': UI_ShowPictureFile(&Rect,"InSum9.clz"); break;
				case '*': UI_ShowPictureFile(&Rect,"InSumX.clz"); break;
			}
			Rect.left	+= UI_EDIT_bMONEY_sW;
		}
	}
}


//=========================================================================================
int APP_GUI_Menu(char* pTitle,char *pMsg,int tNum,int tCurInx,const char** pMenuText,int timeoutMs)
{
	return pGuiFun->Menu(pTitle,pMsg,tNum,tCurInx,pMenuText,timeoutMs);
}

//====================================================
//make a QR code and display it to lcd
void API_GUI_Draw565QRcode(RECTL* pRECTL,char *pInMsg,A_RGB fgColor)
{
	pGuiFun->ShowQrCodeRect(pRECTL,pInMsg,fgColor);
}

void API_GUI_Show(void)
{
	pGuiFun->Show();
}

//----由于滚显示更新信息---pOriginal 原信息空间 Originalsize原信息空间大小--pAddMsg 新加信息------


void APP_ShowSta(char *pTitle,char *pMsg)
{
	pGuiFun->CreateShowWindow(pTitle,NULL,NULL);
	pGuiFun->Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_CENTER,pMsg);
	pGuiFun->Show();
}

void APP_ShowInfoSta(char *pTitle,char *pInfo,char *pAfterText)
{
	pGuiFun->CreateShowWindow(pTitle,TOK,TCANCEL);
	pGuiFun->OprInfo(pInfo,pAfterText);
	pGuiFun->Show();
}


int APP_ShowMsg(char *pTitle,char *pMsg,int timeOutMs)
{
	pGuiFun->CreateShowWindow(pTitle,TOK,TCANCEL);
	pGuiFun->Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_CENTER,pMsg);
	pGuiFun->Show();
	return APP_WaitUiEvent(timeOutMs);
}

int APP_ShowInfo(char *pTitle,char *pInfo,int timeOutMs)
{
	pGuiFun->CreateShowWindow(pTitle,TOK,TCANCEL);
	pGuiFun->OprInfo(pInfo,NULL);
	pGuiFun->Show();
	return APP_WaitUiEvent(timeOutMs);
}

int APP_ShowInfoMsg(char *pTitle,char *pInfo,char *pAfterText,int timeOutMs)
{
	pGuiFun->CreateShowWindow(pTitle,TOK,TCANCEL);
	pGuiFun->OprInfo(pInfo,pAfterText);
	pGuiFun->Show();
	return APP_WaitUiEvent(timeOutMs);
}

void APP_HitMsg(const char* pMsg,int tTimeOutMS)
{
	pGuiFun->ShowPopup(pMsg,tTimeOutMS);
}



#ifdef __cplusplus
}
#endif /* __cplusplus */

