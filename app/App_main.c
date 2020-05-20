#include "communal.h"




//===================���þ����������صĽӿ�===============================
typedef struct 
{
	const char 					cInterfaceVer[4];//�ӿڰ汾�ţ���һλ����������[2]���ڶ�λ~����λ����汾[x.x.x]��
	const API_SDK_Def* 			sys;
	const API_FONT_Def*			font;		//�ֿ���Դ
	const API_Even_Def*			event;
	const API_UI_Def*			ui;
	const API_GUI_Def* 			gui;
	const API_TLS_INTERFACE* 	tls;	
	const API_SDK_INTERFACE* 	sdk;
}APP_INTERFACE;


const API_SDK_Def*		pSysFun;
const API_FILE_Def*		pFileFun;
const API_FONT_Def* 		pFontFun;		//�ֿ���Դ
const API_Even_Def* 		pEventFun;		//�ֿ���Դ
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
	//------------����Ӧ�����߳�----------
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
			APP_TradeMainMenu("������");
		}
		*/
	}
	//Cam_DeInit();
	//StopTimedRefresh();
}




