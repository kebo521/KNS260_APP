#include "communal.h"




//===================主用就所调用主控的接口===============================
typedef struct 
{
	const char 					cInterfaceVer[4];//接口版本号，第一位功能项数量[2]，第二位~第四位定义版本[x.x.x]。
	const API_SDK_Def* 			sys;
	const API_FONT_Def*			font;		//字库资源
	const API_Even_Def*			event;
	const API_UI_Def*			ui;
	const API_GUI_Def* 			gui;
	const API_TLS_INTERFACE* 	tls;	
	const API_SDK_INTERFACE* 	sdk;
}APP_INTERFACE;


const API_SDK_Def*		pSysFun;
const API_FILE_Def*		pFileFun;
const API_FONT_Def* 		pFontFun;		//字库资源
const API_Even_Def* 		pEventFun;		//字库资源
const API_UI_Def*			pUiFun;
const API_GUI_Def*		pGuiFun;
const API_TLS_INTERFACE*	pTlsFuntion;
const API_SDK_INTERFACE* 	pSdkFun;
void app_main(APP_INTERFACE *pAppSdk)
{
	pSysFun = pAppSdk->sys;
	pFileFun = pAppSdk->file;
	pFontFun = pAppSdk->font;
	pEventFun = pAppSdk->event;
	pUiFun = pAppSdk->ui;
	pGuiFun = pAppSdk->gui;
	pTlsFuntion= pAppSdk->tls;
	pSdkFun = pAppSdk->sdk;
	TRACE_HEX("AppMercuryMain InterfaceVer",pAppSdk->cInterfaceVer);
	TermParLoad();
	MachDatainit();
	ReadTradeRecordToFile();
	//------------创建应用主线程----------
	/*
	 DisplayInit();
    //DisplaySetColor(MERCURY_WHITE, MERCURY_BLACK);
    DisplaySetScreenOffTimeout(0);//Always on
    DisplayClearScreen();
    DisplaySetBrightness(10);
    DisplaySetDirection(DMDO_0);
	*/
	
	APP_OperationCreateThread(customer_main,15*1024);
	for(;;)
	{
		Sleep(0xffffffff);
	/*
		if(0 > SweepFlow(NULL))
		{
			APP_TradeMainMenu("主交易");
		}
		*/
	}
	//Cam_DeInit();
	//StopTimedRefresh();
}




