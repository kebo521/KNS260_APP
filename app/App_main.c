#include "communal.h"




//===================���þ����������صĽӿ�===============================
typedef struct 
{
	char	Mask[4];			//�ӿڰ汾�ţ���һλ����������[2]���ڶ�λ~����λ����汾[x.x.x]��
	const API_SDK_Def* 			sys;
	const API_FILE_Def*			file;
	const API_FONT_Def*			font;		//�ֿ���Դ
	const API_Even_Def*			event;
	const API_UI_Def*			ui;
	const API_GUI_Def* 			gui;
	const API_TLS_INTERFACE* 	tls;	
	const API_SDK_INTERFACE* 	sdk;
}APP_INTERFACE;


int app_main(int argv, const char * args)
{
	TRACE("app_main argv[%d],args[%x]\r\n",argv,args);
	APP_ShowMsg("����Ӧ��","������...",2000);
	TermParLoad();
	APP_ShowMsg("����Ӧ��","������ʼ��...",2000);
	TRACE("app_main 2\r\n");
	MachDatainit();
	APP_ShowMsg("����Ӧ��","������ʼ��2..",2000);
	TRACE("app_main 3\r\n");
	ReadTradeRecordToFile();
	TRACE("app_main 4\r\n");
	//------------����Ӧ�����߳�----------
	//customer_main(argv,args);
	//APP_TradeMainMenu("������");
	//APP_ShowMenuProsse();
	/*
	 DisplayInit();
    //DisplaySetColor(MERCURY_WHITE, MERCURY_BLACK);
    DisplaySetScreenOffTimeout(0);//Always on
    DisplayClearScreen();
    DisplaySetBrightness(10);
    DisplaySetDirection(DMDO_0);
	*/
	
	
	if(0 > SweepFlow(NULL))
	{
		TRACE("app_main 5\r\n");
		APP_TradeMainMenu("������");
		TRACE("app_main 6\r\n");
		APP_ShowMenuProsse();
	}
		
	return 0;
}


#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
void Init_RamData(void)
{
    u32 len;									
    u8 *bss_start,			*bss_end;						
    u8 *data_ram, 			*data_rom,		*data_rom_end;		
	data_ram 		= __section_begin(".data");
	data_rom		= __section_begin(".data_init");
	data_rom_end	= __section_end(".data_init");
	len 			= data_rom_end - data_rom;
	TRACE("data_ram1[%x][%X,%X][%x]\r\n",data_ram,data_rom,data_rom_end,len);
	if(data_ram == NULL||data_rom ==NULL||data_rom_end == NULL) return ;
	while (len--)	// Copy initialized data from ROM to RAM 
	{
		TRACE("lenD[%d]\r\n",len);
		*data_ram++ = *data_rom++;
	}
	bss_start 	= __section_begin(".bss");
	bss_end 	= __section_end(".bss");
    len 			= bss_end - bss_start;
	TRACE("data_zero[%X,%X][%x]\r\n",bss_start,bss_end,len);
	if(bss_start == NULL||bss_end==NULL) return ;
   	while(len--)	// Clear the zero-initialized data section
	{
		TRACE("lenZ[%d]\r\n",len);
		*bss_start++ = 0;
	}
}



int a345=83,b234=64,c455=0;
API_SDK_Def		api_SysFun;
API_FILE_Def*		pFileFun;
API_FONT_Def* 		pFontFun;		//�ֿ���Դ
API_Even_Def* 		pEventFun;		//�ֿ���Դ
API_UI_Def*			pUiFun;
API_GUI_Def*		pGuiFun;
API_TLS_INTERFACE*	pTlsFuntion;
API_SDK_INTERFACE* 	pSdkFun;

#pragma location = ".code_entry"
int __startup_appmain(APP_INTERFACE * pRunTime, int argv, const char * args) 
{
	memcpy(&api_SysFun,pRunTime->sys,sizeof(API_SDK_Def));
	pFileFun = (API_FILE_Def*)pRunTime->file;
	pFontFun = (API_FONT_Def*)pRunTime->font;
	pEventFun = (API_Even_Def*)pRunTime->event;
	pUiFun = (API_UI_Def*)pRunTime->ui;
	pGuiFun = (API_GUI_Def*)pRunTime->gui;
	pTlsFuntion= (API_TLS_INTERFACE*)pRunTime->tls;
	pSdkFun = (API_SDK_INTERFACE*)pRunTime->sdk;
	TRACE_HEX("__startup_appmain InterfaceVer",pRunTime->Mask,4);
	APP_ShowMsg("ȫ�ֱ���","��ʼ��...",8000);
	Init_RamData();
	TRACE("startup_appmain [%d,%d,%d]\r\n",a345,b234,c455);
	return app_main(argv,args);
}


