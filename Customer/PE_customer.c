#include "communal.h"
#ifdef __cplusplus
extern "C" {
#endif

UI_DisplayTheme const UI_WftTheme=
{
	"press[0] next page",
	"press[8] Prev page",
	"page: [8]↑, [0]↓",
	
	L"E:\\bmp\\Small_f.bin",
	14,
	13,
};

//=================终端参数管理========================
TERM_PAR    Term_Par;

void TermParSetDefault(void)
{
	CLEAR(Term_Par);
	API_strcpy(Term_Par.ServerIp,"113.105.146.93");
	API_strcpy(Term_Par.ServerPort,"8888");
	API_strcpy(Term_Par.Apn,"CMNET");
	API_strcpy(Term_Par.password, "888888");
	Term_Par.volume = 7;

	#ifdef HARD_WIFI
	Term_Par.WifiOpen[0]=1;
	#endif
	API_strcpy(Term_Par.CustVer,  CustomerVersion);

	// 主控默认设置为中文
	pSdkFun->sdk->language(_LANG_ID_);

	// 清流水
	ClearTradeRecord();
}

// 客户区域进入函数
void MachDatainit(void)
{
	CLEAR(g_ColData);
	API_strcpy(g_ColData.mch_id,		Term_Par.mch_id);
	API_strcpy(g_ColData.key,			Term_Par.mch_key);
	API_strcpy(g_ColData.op_shop_id,	Term_Par.op_shop_id);
	API_strcpy(g_ColData.op_user_id,	Term_Par.op_user_id);

//	API_strcpy(g_ColData.merchantId, "181510000316");
//	API_strcpy(g_ColData.keyFPS, "06221c2e1e44f4528b9668efb9f29d1d");
	API_strcpy(g_ColData.merchantId,g_ColData.mch_id);
	API_strcpy(g_ColData.keyFPS, g_ColData.key);

	AudioSetVolume(Term_Par.volume);
	InitElementValue();
	GetTermSN();
	UI_LoadTheme(&UI_WftTheme);
}



int  SoftInfo(char*  ptitle)
{
	char Msg[256]={0};
	API_strcat(Msg, STR_TERM_MODEL);
	API_strcat(Msg, ": ");
	API_strcat(Msg, TermModel);
	API_strcat(Msg,"\n");

	API_strcat(Msg, STR_VERSION);
	API_strcat(Msg, ": ");
	API_strcat(Msg, Version);
	API_strcat(Msg,"\n");

	API_strcat(Msg, STR_RELEASE_TIME);
	API_strcat(Msg, ": ");
	API_strcat(Msg, ReleaseTime);
	API_strcat(Msg,"\n");

	API_strcat(Msg, STR_TERM_CHANNEL);
	API_strcat(Msg, ": ");
	API_strcat(Msg, STR_CHANNEL_NAME);
	API_strcat(Msg,"\n");

	API_strcat(Msg,"SN: ");
	APP_GetHardMsg(TYPE_TERM_HARD_SN, g_ColData.term_sn, sizeof(g_ColData.term_sn));
	API_strcat(Msg,g_ColData.term_sn);
	API_GUI_CreateWindow(STR_DEVICE_INFORMATION,NULL,NULL,0);
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_TOP,Msg);
	API_GUI_Show();
	APP_WaitUiEvent(5000);

	return 0;
}

//===================特殊菜单=================================================
//功能:   夸平台二维码收款交易菜单
//输入数据:pTitle 标题，tNum菜单总项数，pMenuAll菜单显示与功能
//输出数据:RET_OK创建成功，RET_ERR 创建失败
//---------------------------------------------------------------
/*
int PE_TradeQrCodeMenuProcess(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs)
{
	int ret;
	u32 Event;

	APP_ShowPayMeth(pTitle);
	while(1)
	{
		Event=API_WaitEvent(TimeOutMs,EVENT_UI,EVENT_KEY,EVENT_NONE);
		if(Event&EVENT_CANCEL)
		{
			ret=OPER_RET;
			break;
		}
		if(Event&EVENT_KEY)
		{
			u8 KeyVal;
			KeyVal=Event&EVENT_INDEX;
			if(KeyVal>=K_1 && KeyVal<=K_8)
			{
				KeyVal -= K_1;
				if(KeyVal < tNum)
				{
					ret=(*pMenuAll[KeyVal].pFunMenu)(pMenuAll[KeyVal].pText);
					break;
				}
			}
		}
		else if(Event&EVENT_TIMEOUT)
		{
			ret=OPER_TIMEOUT;
			break;
		}
	}
	return ret;
}
*/
int APP_QRMenu(char* title)
{
	int ret;
	CMenuItemStru MenuStruPar[]=
	{
		STR_MENU_ALIPAY,	QrTypeZFB,
		STR_MENU_WECHAT,	QrTypeWX,
		STR_MENU_UNIONPAY,	QrTypeUN,
		STR_MENU_FPS,		QrTypeFPS,		
	};
	CLEAR(g_ColData.total_fee);
	ret=APP_EditSum(title,'D',g_ColData.total_fee,30*1000);
	if(ret <= 0) return ret;
	APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
	APP_AddCurrentMenuOtherFun(MENU_BACK_MAP,"PayMeth.clz",NULL);
	return 0;
}


int APP_TermMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		STR_MERCHANT_ID_SETTINGS,				SetMerchant_ID,
		STR_MERCHANT_KEY_SETTINGS,				InputMerchantKey,
		STR_SCAN_QRCODE_IMPORT_MERCHANT_INFO,	ScanMerchantInfo,
		STR_SET_SHOP_ID,						SetShopID,
		STR_SET_USER_ID,						SetUserID,
		#ifdef HARD_WIFI
		WIFI_SWITCH,							APP_WIFI_EN,
		WIFI_PASSu16,							APP_WIFI_SetKey,
		#endif
		STR_DEVICE_INFORMATION,					SoftInfo,
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
}

int OrderQueryMenu(char* title)
{
	CMenuItemStru MenuItems[] = {
		ORDER_QUERY, 			QueryFlow,
		ORDER_FPS_QUERY,		FPS_QueryFlow,
		ORDER_QUERY_REFUND,		QueryRefundResult,
		ORDER_RECORD,			Enquiries,
	};
	if(0 != CheckParamPreFlow())
	{
		return -1;
	}
	APP_CreateNewMenuByStruct(title, sizeof(MenuItems)/sizeof(CMenuItemStru), MenuItems, 30*1000);
	//APP_AddCurrentMenuOtherFun(MENU_KEY_FUN,Enquiries,ORDER_RECORD);
	return APP_ShowMenuProsse();
}

int APP_TradeMainMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		SCAVENGING_RECEIPT,		SweepFlow,
		QRCODE_RECEIPT,			APP_QRMenu,
		ORDER_REFUND,			RefundFlow,
		ORDER_QUERY,			OrderQueryMenu,
	};
	APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
	APP_AddCurrentMenuOtherFun(MENU_BACK_MAP,"PayCont.clz",NULL);
	return 0;
}


int MerchantInfoMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		STR_SCAN_QRCODE_IMPORT_MERCHANT_INFO,	ScanMerchantInfo,
//		STR_SCAN_QRCODE_IMPORT_FPS_ID,			ScanFPS_MerchantInfo,
		STR_MERCHANT_ID_SETTINGS,				SetMerchant_ID,
		STR_MERCHANT_KEY_SETTINGS,				InputMerchantKey,
		STR_SET_SHOP_ID,						SetShopID,
		STR_SET_USER_ID,						SetUserID,
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}	

int PE_wifi_FunSet(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		WIFI_SWITCH,							APP_WIFI_EN,
		WIFI_PASSu16,							APP_WIFI_SetKey,
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}	

int customer_MainMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		STR_MERCHANT_INFO,						MerchantInfoMenu,
		WIFI_FUNTION,							PE_wifi_FunSet,
		#ifdef DOMESTIC_BANK_VERION
		STR_SET_VOLUME,							Terminal_SetVolume,
		#endif
		STR_SET_ADMIN_PASSu16,					SetRefundPwd,
		STR_DEVICE_INFORMATION,					SoftInfo,
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}


void customer_main(unsigned long argc,void * lpThreadParameter)
{
	// 关闭公共区自动提示
	TCP_SetInterNotDisplay(TRUE);	

	for(;;)
	{
		if(0 > SweepFlow(NULL))
		{
			APP_TradeMainMenu(STR_TRADE_MENU);
		}
	}
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

