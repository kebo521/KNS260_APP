#ifndef _PE_TERMPAR_
#define _PE_TERMPAR_

#define STR_PRESS_CONFIRM_REFUND					DS("Press [OK] to refund",								"按[确认]键退款")
//#define STR_PRESS_NUBER_KEYS_ENTER                DS("Press a numeric key to input",						"请按数字键输入")
#define STR_ACCESS_POINT_SETTINGS 					DS("Access point settings",								"接入点设置")
#define STR_ACCESS_POINT  							DS("Access Point",										"接入点")
#define STR_IP_ADDRESS_SETTINGS						DS("IP settings",										"IP地址设置")
#define STR_IP_ADDRESS								DS("IP address",										"IP地址")
#define STR_PORT_SETTINGS 							DS("Port settings",										"端口设置")
#define STR_PORT 									DS("Port",												"端口")
#define STR_SUCCESSFULLY_SET_UP						DS("setting successfully",								"设置成功")
#define STR_MERCHANT_ID_SETTINGS					DS("Merchant ID",										"设置商户ID")
#define STR_MERCHANT_KEY_SETTINGS					DS("Merchant key",										"设置商户密钥")
#define STR_SET_SHOP_ID                             DS("Shop ID",                                           "设置门店编号")
#define STR_SET_DEVICE_ID                           DS("Device ID",                                         "设备编号")
#define STR_SET_USER_ID                             DS("User ID",                                           "设置操作员")
#define STR_SCAN_MERCHANT_INFO_CODE					DS("Please scan merchant information code",				"请扫商户信息码")
#define STR_PRESS_CONFIRMFILL_THE_LIGHT				DS("Press [Confirm] to fill light",						"按[确认]键补光")
#define STR_CHANNEL_NAME                            DS("swiftpass",                                         "威富通")

#define STR_DATA_FORMAT_ERROR                       DS("Data Format error",                                 "商户号长度错")
#define STR_MERCHANT_NUMBER_LENGTH_ERROR			DS("Merchant ID length error",							"商户号长度错")
#define STR_KEY_LENGTH_ERROR						DS("Key length error",									"密钥长度错")
#define STR_IMPORTED_SUCCESSFULLY					DS("Imported successfully",								"导入成功")
//#define STR_ENTER_THE_AUTHENTICATION_PASSu16		DS("Please enter authentication password",				"请输入认证密码")
//#define STR_RESTORE_FACTORY_SETTINGS_SUCCESSFULLY	DS("Factory settings restored successfully",			"恢复出厂设置成功")
#define STR_TIME_SETTING							DS("Time setting",										"时间设置")
#define STR_MERCHANT_KEY_INPUT						DS("Merchant key input",								"商户密钥输入")
#define STR_SCAN_QRCODE_IMPORT_MERCHANT_INFO		DS("Scan CUP Merchant ID",								"扫码导入商户信息")
#define STR_SCAN_QRCODE_IMPORT_FPS_ID				DS("Scan FPS Merchant ID",								"扫码导入FPS商户信息")
#define STR_NO_TRANSACTION_RECORD                   DS("No transaction record",                             "无交易记录")
#define STR_NO_WRITE_SN					            DS("The terminal did not write the serial number",      "终端未写序列号")
#define STR_KEY_ADJUST                              DS("Press ← [7],[1] →",                                 "按 ← [7],[1] →")

#define STR_ENTER_ORI_KEY							DS("Please enter\nthe access code", 						"请输入旧授权码")	
#define STR_INPUT_NEW_KEY							DS("please input a\nnew access code",						"请输入新授权码")
#define STR_INPUT_NEW_KEY_AGAIN						DS("please input the new\naccess code again",				"请再次输入新授权码")
#define STR_INPUT_TWO_ERR							DS("the two access code\nare inconsistent\n,please re-input","两次输入授权码不一致\n请重新输入")

extern int APP_InputNum(char* pTitle, char* pFrontTextBuf, char* pAfterTextBuf, char* pInputDef, int InputMinLen, int InputMaxlen);
extern int Terminal_SetGprsInfo(char *pTitle);
extern void insertHeadNodes(char* money,char* date,char* type,char* porder,char *pOutRefundNo);
extern int Enquiries(char* pTitle);
extern int CheckMchidIsNull(void);
extern int SetMerchant_ID(char* title);
extern int SetShopID(char* title);
extern int SetUserID(char* title);
extern int SetRefundPwd(char* title);
extern int GetTermSN(void);
extern int ShowSnQrCode(char* title);
extern int InputMerchantKey(char* title);
extern int ScanMerchantInfo(char *title);
extern int ScanFPS_MerchantInfo(char *title);
extern int Terminal_SetVolume(char *pTitle);

#endif /* _PE_TERMPAR_ */

