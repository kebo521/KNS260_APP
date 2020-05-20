#ifndef _KS_LANGUAGE_
#define _KS_LANGUAGE_

typedef struct
{
	char Flaglang[4];
	char *pOK;
	char *pCancel;
	char *pSuccess;
	char *pFailed;
	char *pPlsChg;
	char *pShuDown;
	char *pEditFull;
	char *pLackInput;

	char *pSoftwareUpdate;
	char *pCheckUpdate;
	char *pUpdating;
	char *pPressContinue;
	char *pDowloadCompleted;
	char *pVerifyFailed;
	char *pDownloadFailed;
	char *pCreateFileFailed;
		
	char *pFirmUp;
	char *pCheckPackage;
	char *pVerifySignErr;
	char *pCalcSignErr;
	char *pInstalling;
	char *pAppInstalling;
	char *pTmsInstalling;

	char *pInputNumber;
	char *pInputLletters;
	char *pInputUletters;
	char *pKeyDownMsg;
	char *pKeyUpMsg;
	char *pKeyUpDownMsg;
	char *pKeyScanInitErr;
}KS_LANGUAGE;

extern KS_LANGUAGE sLanguageIndex;


#define TOK							sLanguageIndex.pOK
#define TCANCEL						sLanguageIndex.pCancel
#define STR_SUCCESS					sLanguageIndex.pSuccess
#define STR_FAILED					sLanguageIndex.pFailed
#define STR_UI_PLS_CHG				sLanguageIndex.pPlsChg
#define STR_UI_SHU_DOWN				sLanguageIndex.pShuDown
#define STR_EDIT_FULL				sLanguageIndex.pEditFull
#define STR_LACK_INPUT				sLanguageIndex.pLackInput

#define STR_SOFTWARE_UPDATA			sLanguageIndex.pSoftwareUpdate
#define STR_CHECK_UPDATA			sLanguageIndex.pCheckUpdate
#define STR_PRESS_OK_UPDATE			sLanguageIndex.pUpdating
#define STR_PRESS_OK_CONNET			sLanguageIndex.pPressContinue
#define STR_DOWNLOAD_COMPLETED		sLanguageIndex.pDowloadCompleted
#define STR_VERIFY_FAILED			sLanguageIndex.pVerifyFailed
#define STR_DOWNLOAD_FAILED			sLanguageIndex.pDownloadFailed
#define STR_CREATE_FILE_FAILED		sLanguageIndex.pCreateFileFailed

#define STR_FIRMWARE_UPGRADE		sLanguageIndex.pFirmUp
#define STR_CHECK_PACKAGE			sLanguageIndex.pCheckPackage
#define STR_VERIFY_SIGN_ERR			sLanguageIndex.pVerifySignErr
#define STR_CALC_SIGN_ERR			sLanguageIndex.pCalcSignErr
#define STR_INSTALLING				sLanguageIndex.pInstalling
#define STR_APP_INSTALLING			sLanguageIndex.pAppInstalling
#define STR_TMS_INSTALLING			sLanguageIndex.pTmsInstalling

#define STR_KEY_INPUT_NUMBER		sLanguageIndex.pInputNumber
#define KEY_INPUT_LOWERCASE_LETTERS	sLanguageIndex.pInputLletters
#define KEY_INPUT_UPPERCASE_LETTERS	sLanguageIndex.pInputUletters
#define STR_KEY_DOWT				sLanguageIndex.pKeyDownMsg
#define STR_KEY_UP					sLanguageIndex.pKeyUpMsg
#define STR_KEY_UPDOWT				sLanguageIndex.pKeyUpDownMsg

#define STR_SCAN_ERR_INIT			sLanguageIndex.pKeyScanInitErr


extern void API_InitSysLanguage(u8 index);
extern int API_SetLanguage(unsigned int language);

//extern int APP_SetLanguage(char* pTitle);

#define _LANG_ID_					1											// 1 默热中文
#define DS(en,ch)					((_LANG_ID_==0)?(en):(ch))					//多语言定义

#define STR_NUBER_INPUT  			DS("press keys to enter",	"请按数字键输入")
#define STR_ENTER_ADMIN_PASSu16	DS("enter admin password",	"请输入管理员密码")
#define STR_ENTER_DEBUG_PASSu16	DS("enter debug password",	"请输入调试管理密码")
#define STR_EDIT_SWITCH_ALPHA		DS("[Letter] switch input",	"按[字母]键切换输入")

//==============================WIFI操作=================================================
#define STR_NET_SUSS_LINK			DS("Connected successfully",	"连接成功")
#define STR_NET_LINK_WLAN			DS("connect the network",		"连接网络")
#define STR_NET_FAIL_LINK			DS("Failed to connect the network","连接网络失败")
#define STR_NET_ERR_LINK			DS("Network connection error",	"网络连接错误")
#define STR_NET_FAIL_SEND			DS("Failed to send data",		"发送数据失败")
#define STR_NET_FAIL_RECV			DS("Failed to receive data",	"接收数据失败")
#define STR_NET_ENC_MODE			DS("MODE",						"模式")

#define STR_WLAN_OPNEING			DS("Opening WIFI...",			"WIFI打开中...")	
#define STR_WLAN_OK_OPEN			DS("Press [OK] to open WIFI",	"按[确认]打开Wifi")	
#define STR_WLAN_CLOSEING			DS("Closing WIFI...",			"WIFI关闭中...")	
#define STR_WLAN_OK_CLOSE			DS("Press [OK] to close WIFI",	"按[确认]关闭Wifi")	
#define STR_WLAN_READING			DS("Reading WIFI...",			"读取WIFI中...")	
#define STR_WLAN_FAIL_READ			DS("Failed to read WIFI",		"读取WIFI失败")	
#define STR_WLAN_NOT_START			DS("WIFI boot unaccomplished",	"WIFI启动未完成")	

#define STR_SIGNAL_STGTH			DS("Signal strength",			"信号强度")	
#define STR_SIGNAL_XL				DS("Very strong",				"极强")	
#define STR_SIGNAL_L				DS("Strong",					"  强")	
#define STR_SIGNAL_M				DS("Medium",					"  中")	
#define STR_SIGNAL_S				DS("Weak",						"  弱")	
#define STR_SIGNAL_XS				DS("Very weak",					"极弱")	

#define STR_OPEN_WIFI				DS("Please open WIFI",			"请开启WIFI")
#define STR_SCAN_QRCODE				DS("Please scan QR code",		"请扫热点二维码")
#define STR_EXIT					DS("[Cancel] button to exit",	"[取消]键退出")
#define STR_OPEN_WALN				DS("Connect Open WALN?",		"确认连接开放网络?")



#endif

