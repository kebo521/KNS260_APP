#ifndef _APP_MAIN_
#define _APP_MAIN_


#define SdkVersion					"2.0.2"


#define TOK							DS("OK",						"确认")
#define TCANCEL						DS("Cancel",					"取消")	
#define STR_SUCCESS					DS("SUCCESS",					"成功")
#define STR_FAILED					DS("FAILED",					"失败")
#define STR_SET_OK					DS("Set Success",				"设置成功")
#define STR_SET_FAIL				DS("Set Fail",					"设置失败")
#define STR_SUM_SIGN				DS("$ ",						"￥")
#define STR_MENU_MANAGE				DS("Terminal management",		"终端管理")
#define STR_MENU_SYSTEM				DS("System settings",			"系统设置")
#define STR_MENU_FACTORY			DS("Factory settings",			"工厂设置")
#define STR_MENU_FUNCTION			DS("Function settings",			"功能设置")
#define STR_MENU_SN					DS("Terminal serial no",		"终端序列号")
#define STR_MENU_WIFI_EN			DS("WLAN ON/OFF",				"WLAN开关")
#define STR_MENU_WIFI_PASS			DS("WLAN password setting",		"WLAN密码设置")
#define STR_UI_PLS_CHG				DS("Please charge the power",	"请充电")
#define STR_UI_SHU_DOWN				DS("Powering off",				"正在关机")
#define STR_EDIT_FULL				DS("The input is full",			"输入已满")
#define STR_EDIT_SWITCH_ALPHA		DS("Press [Letter] to switch input","按[字母]键切换输入")
#define STR_EDIT_OK_CONNET			DS("Press [OK] to connect",		"按[确认]键连接")	
#define STR_EDIT_AMOUNT_INVALID		DS("Invalid amount",			"无效金额")	
#define STR_EDIT_AMOUNT_NULL		DS("Please enter amount",		"请输金额")	
#define STR_EDIT_ORDER_INVALID		DS("Invalid merchant number",	"无效商户单号")	

#define STR_NET_OPEN				DS("Open network",				"打开网络")
#define STR_NET_CLOSE				DS("Close network",				"关闭网络")
#define STR_NET_NO_SERVICE			DS("No network service",		"无网络服务")
#define STR_NET_WEAK_SIGNAL			DS("Weak signal",				"信号弱")
#define STR_NET_FAIL_OPEN			DS("Failed to open network",	"打开网络失败")
#define STR_NET_FAIL_GET_NAME		DS("Failed to obtain domain name","获取域名失败")
#define STR_NET_CENTER_LINK			DS("center Connecting",			"连接中心")
#define STR_NET_CENTER_FAIL			DS("center Connect Fail",		"连接失败")

#define STR_NET_SUSS_LINK			DS("Connected successfully",	"连接成功")
#define STR_NET_LINK_WLAN			DS("connect the network",		"连接网络")
#define STR_NET_FAIL_LINK			DS("connect Failed",			"连接网络失败")
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

#define STR_TRAND_MAIN_NAME			DS("Main transaction",			"主交易")	
#define STR_TRAND_TIME				DS("Transaction time",			"交易时间")	
#define STR_TRAND_ORDER				DS("Transaction ID",			"商户单号")	

#define STR_SCAN_ERR_INIT			DS("Failed to initialize camera","摄像头初始化失败")	

#define STR_SOFTWARE_UPDATA			DS("Software update",			"软件升级")
#define STR_CHECK_UPDATA			DS("Check version updates",		"有版本需要更新")
#define STR_PRESS_OK_UPDATE			DS("Pls do not shut down",		"更新中,请不要关机")
#define STR_PRESS_OK_CONNET			DS("Press[OK]to continue",		"按[确认]键继续")	

#define STR_PRESS_NUBER_KEYS_ENTER  				DS("Please press the number keys to enter",				"请按数字键输入")
#define STR_ENTER_THE_AUTHENTICATION_PASSWORD		DS("Please enter the authentication password",			"请输入认证密码")
#define STR_ENTER_THE_ADMIN_PASSWORD                DS("Please enter the admin password",					"请输入管理员密码")

#define STR_RESTORE_FACTORY_SETTINGS_SUCCESSFULLY	DS("Restore factory settings successfully",				"恢复出厂设置成功")

#define STR_KEY_INPUT_NUMBER			DS("[number mode]",		"    [数字]键输入数字")
#define KEY_INPUT_LOWERCASE_LETTERS		DS("[lowercase  ]",		"[数字]键输入小写字母")
#define KEY_INPUT_UPPERCASE_LETTERS		DS("[uppercase  ]",		"[数字]键输入大写字母")

#define WIFI_SWITCH						DS("Wifi On/Off",						"WIFI开关")
#define WIFI_SELECTION					DS("Hotspot Selection", 				"热点选择")
#define WIFI_SCAN_QRCODE				DS("Scan Wifi QRcode", 					"扫wifi二维码")

#define STR_OPEN_WIFI					DS("Please open WIFI",					"请开启WIFI")
#define STR_SCAN_QRCODE					DS("Please scan QR code",				"请扫热点二维码")
#define STR_EXIT						DS("[Cancel] button to exit",			"[取消]键退出")
#define STR_ENTER_OPE_ADMIN_PASSWORD	DS("Enter OperAdmin Key",				"请输操作管理员密码")

#define STR_PLEASE_CHARGE				DS("Low battery,charge",				"电量不足,请充电")

#define STR_SYSTEM						DS("SYSTEM",							"系统")
#define STR_APP_START					DS("APP start-up",						"启动应用")

#define STR_KEY_DOWT					DS("key[0] Page down",					"按[0]键下翻页")
#define STR_KEY_UP						DS("key[8] Page up",					"按[8]键上翻页")
#define STR_KEY_UPDOWT					DS("key[8]up,key[0]down",				"[8]上翻页,[0]下翻页")

#define STR_LACK_INPUT					DS("Lack input",						"输入位数不足")
#define STR_OPEN_WALN					DS("Connect Open WALN?",				"确认连接开放网络?")

#define STR_OPEN_WALN					DS("Connect Open WALN?",				"确认连接开放网络?")

#define STR_PASSWORD_ERR				DS("password error",					"密码错误")


//=====================接口参数=========================================


typedef struct	
{
	char Mask[4]; 	// "app"
	void* (*malloc)(u32);
	void (*free)(void*);
	void (*SetSleep)(int);//(int En)
	int (*GetHardMsg)(u8,void *,int);	//(u8 type,void *pOut,int OutSize)
	int (*SetHardMsg)(u8,void *,int);	//(u8 type,void *pIn,int InSize)
	char* (*GetMasterVersion)(void);	// return Version
	int (*GetParVersion)(char*,int);	//(char* pParVer,int sizeVer)
	int (*OnlyCamScan)(char,int,int,char*,int);	//(char flagKey,int MinLen,int MaxLen,char* pOutCode,int msTimeOut)
	void* (*JsonLoad)(char*,char*);	//(char *pIndata,char* pEnd)
	void* (*JsonGetValue)(void*,char*,u8 *); //(dfJsonTable *pStart,char* pKey,u8 *pType)
	void (*JsonDestroy)(void *);	//(dfJsonTable *pTable)
	int (*NetInstallAPP)(char*);	//(char *pTitle)
}API_USE_Def;

typedef struct 
{
	char Mask[4]; 							// "api"
	const API_WIFI_Def*			wifi;		//Wifi通信接口
	const API_NetWork_Def* 		net;		//网络通信接口
	const API_USE_Def*			app;		//应用接口，主控提供
}API_SDK_INTERFACE;


extern API_SDK_INTERFACE* 	pSdkFun;

#endif



