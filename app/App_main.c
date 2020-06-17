#include "communal.h"




//===================主用就所调用主控的接口===============================
typedef struct 
{
	char	Mask[4];			//接口版本号，第一位功能项数量[2]，第二位~第四位定义版本[x.x.x]。
	const API_SDK_Def* 			sys;
	const API_FILE_Def*			file;
	const API_FONT_Def*			font;		//字库资源
	const API_Even_Def*			event;
	const API_UI_Def*			ui;
	const API_GUI_Def* 			gui;
	const API_TLS_INTERFACE* 	tls;	
	const API_SDK_INTERFACE* 	sdk;
}APP_INTERFACE;


int app_main(int argv, const char * args)
{
	UI_DisplayInit();
	TermParLoad();
	MachDatainit();
	ReadTradeRecordToFile();
	//api_SysFun.logSet(LOG_DEBUG,1);
	//------------创建应用主线程----------
	return customer_MainMenu("主交易");
}


#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
void Init_RamData(void)
{
    u8 *destin,*source,*end;		
	destin 		= __section_begin(".data");
	source		= __section_begin(".data_init");
	end			= __section_end(".data_init");
	if(destin == NULL||source ==NULL||end == NULL) return ;
	while (source < end)	// Copy initialized data from ROM to RAM 
	{
		*destin++ = *source++;
	}
	destin 	= __section_begin(".bss");
	end 	= __section_end(".bss");
	if(destin == NULL||end==NULL) return ;
   	while(destin < end)	// Clear the zero-initialized data section
	{
		*destin++ = 0;
	}
}

API_SDK_Def		api_SysFun;
//API_FILE_Def	api_FileFun;
API_FILE_Def*		pFileFun;
API_FONT_Def* 		pFontFun;		//字库资源
API_Even_Def* 		pEventFun;		//字库资源
API_UI_Def*			pUiFun;
API_GUI_Def*		pGuiFun;
API_TLS_INTERFACE*	pTlsFuntion;
API_SDK_INTERFACE* 	pSdkFun;

#pragma location = ".code_entry"
int __startup_appmain(APP_INTERFACE * pRunTime, int argv, const char * args) 
{
	Init_RamData();
	memcpy(&api_SysFun,pRunTime->sys,sizeof(API_SDK_Def));
	pFileFun = (API_FILE_Def*)pRunTime->file;
	pFontFun = (API_FONT_Def*)pRunTime->font;
	pEventFun = (API_Even_Def*)pRunTime->event;
	pUiFun = (API_UI_Def*)pRunTime->ui;
	pGuiFun = (API_GUI_Def*)pRunTime->gui;
	pTlsFuntion= (API_TLS_INTERFACE*)pRunTime->tls;
	pSdkFun = (API_SDK_INTERFACE*)pRunTime->sdk;
	return app_main(argv,args);
}


