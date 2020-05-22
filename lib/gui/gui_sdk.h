#ifndef _GUI_SDK_
#define _GUI_SDK_

#include "ks_ui.h"
#include "ks_font.h"
#include "ks_gui.h"
#include "input_hand.h"

typedef struct	
{
	char Mask[4]; 	// "GUI"
	void (*LoadWindow)(LPGuiWindow,int);	//(GuiWindow *pWindow,int contLine)
	LPGuiWindow (*GetWindow)(void);
	void (*FillRect)(RECTL*,A_RGB);	//(RECTL *pRect,A_RGB Color)
	void (*XorRect)(RECTL*,A_RGB);	//(RECTL *pRect,A_RGB Color)
	void (*GetRectBuff)(RECTL*,A_RGB*);	//(RECTL *pRect,A_RGB *pRGB)
	void (*SetRectBuff)(RECTL*,A_RGB*); //(RECTL *pRect,A_RGB *pRGB)
	
	void (*ClearScreen)(RECTL*);
	int (*LoadBackground)(FunFillColour);
	int (*CreateWindow)(const char*,const char*,const char*,FunFillColour); //(const char* pTitle,const char* pOk,const char* pCancel,FunFillColour fBackColour)
	void (*Show)(void);

	int (*CreateShowWindow)(const char*,const char*,const char*);	//(const char* pTitle,const char* pOk,const char* pCancel)
	int (*CreateMenuWindow)(const char*,const char*,const char*);	//(const char* pTitle,const char* pOk,const char* pCancel)
	void (*DisplaySysEn)(POINT *,int ,char*);	//(POINT *pPOINT,int type(TEXT_TYPE),char* pMsgEn)
	int (*DrawLineString)(POINT* ,const char*);	//(POINT* pPOINT,const char *src)
	int (*DrawRectString)(RECTL* ,const char*);	//(POINT* pPOINT,const char *src)
	int  (*Info)(const IMAGE*,u32,const char*);						//(const IMAGE* pImg,u32 tTextType,const char* pTextBuf)
	void (*OprInfo)(char*,char*);									//(char* pShowInfo,char *pAfterText)
	void (*ShowQrCode)(const char*,A_RGB );					//(const char* pInfo,A_RGB Color)
	void (*ShowQrCodeRect)(RECTL*,const char*,A_RGB );

	void (*Edit_Prompt)(u32 ,char*,u32 ,char*); //(u32 tFrontTextType,char* pFrontTextBuf,u32 tAfterTextType,char* pAfterTextBuf)
	void (*Edit_Control)(u32,char*,int,u32,u32); //(u32 tTextType,char* pTextDef,int tMaxLen,u32 tImeType,u32 tImeLimit)
	void (*InputEdit)(char*,int,u32,Fun_ShowNum);	//(char* pStrDef,int tMaxLen,u32 Way,Fun_ShowNum pShow)
	int (*Edit_GetText)(char*,int );			//(char* pAscText,int tMaxLen)
	
	int (*ShowPopup)(const char*,int);	//(const char* pMsg,int tTimeOutMS)
	void (*ShowChangeInfo)(char *,int,const char*,...);		//(char *pOriginal,int Originalsize,const char* format,...)
		
	int (*Menu)(char*,char *,int,int,const char**,int);			//(char* pTitle,char *pMsg,int tNum,int tCurInx,const char** pMenuText,int timeoutMs)
	int (*FixedMenu)(char*,const void *,void*);		//(char* pTitle,const FixedMenuUITable *pFixedMenu,void* pTagFunc)
		
	int (*CreateMenuByStr)(char *,int,char**,void*,int);	//(char *pTitle,int tNum,char* *pMenuText,const APP_IndexH pUnifiedFunc,int TimeOutMs)
	int (*CreateMenuByStruct)(char *,int,void *,int);	//(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs)
	int (*CreateMenuByList)(char* ,void*,int);	//(char* pTitle,CMenuListPar* pMenulist,int TimeOutMs)
	void (*AddCurrentMenuOtherFun)(int,void*,const char *);	//(UI_MENU_ADD_TYPE type,void* pFunc,const char *pData)
	int (*DesignatMenuItem)(void*,char*);		//(void* pTagFunc,char *pTagTitle)
	int(*ShowProsseMenu)(void);		
				
	int (*ShowPicture)(RECTL*,const char *);	//(RECTL *pRect,const char *pfilePath)
	
	void (*ShowBottomProgress)(int);			//(int ratio)
	void (*ShowRect)(RECTL*,u16,A_RGB);	//(RECTL *pRect,u16 Width,A_RGB Color)

	void (*Countdown_ShowInit)(u32,int,int);	//tTextType,slen,timeSInit
	int (*Countdown_ShowGet)(void);				//Time out return EVENT_TIMEOUT
	void (*SetLanguage)(u8);		//(u8 index)
}API_GUI_Def;

extern API_GUI_Def*		pGuiFun;;

#endif

