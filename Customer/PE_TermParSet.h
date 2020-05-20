#ifndef _PE_TERMPAR_
#define _PE_TERMPAR_

#define STR_PRESS_CONFIRM_REFUND					DS("Press [OK] to refund",								"��[ȷ��]���˿�")
//#define STR_PRESS_NUBER_KEYS_ENTER                DS("Press a numeric key to input",						"�밴���ּ�����")
#define STR_ACCESS_POINT_SETTINGS 					DS("Access point settings",								"���������")
#define STR_ACCESS_POINT  							DS("Access Point",										"�����")
#define STR_IP_ADDRESS_SETTINGS						DS("IP settings",										"IP��ַ����")
#define STR_IP_ADDRESS								DS("IP address",										"IP��ַ")
#define STR_PORT_SETTINGS 							DS("Port settings",										"�˿�����")
#define STR_PORT 									DS("Port",												"�˿�")
#define STR_SUCCESSFULLY_SET_UP						DS("setting successfully",								"���óɹ�")
#define STR_MERCHANT_ID_SETTINGS					DS("Merchant ID",										"�����̻�ID")
#define STR_MERCHANT_KEY_SETTINGS					DS("Merchant key",										"�����̻���Կ")
#define STR_SET_SHOP_ID                             DS("Shop ID",                                           "�����ŵ���")
#define STR_SET_DEVICE_ID                           DS("Device ID",                                         "�豸���")
#define STR_SET_USER_ID                             DS("User ID",                                           "���ò���Ա")
#define STR_SCAN_MERCHANT_INFO_CODE					DS("Please scan merchant information code",				"��ɨ�̻���Ϣ��")
#define STR_PRESS_CONFIRMFILL_THE_LIGHT				DS("Press [Confirm] to fill light",						"��[ȷ��]������")
#define STR_CHANNEL_NAME                            DS("swiftpass",                                         "����ͨ")

#define STR_DATA_FORMAT_ERROR                       DS("Data Format error",                                 "�̻��ų��ȴ�")
#define STR_MERCHANT_NUMBER_LENGTH_ERROR			DS("Merchant ID length error",							"�̻��ų��ȴ�")
#define STR_KEY_LENGTH_ERROR						DS("Key length error",									"��Կ���ȴ�")
#define STR_IMPORTED_SUCCESSFULLY					DS("Imported successfully",								"����ɹ�")
//#define STR_ENTER_THE_AUTHENTICATION_PASSu16		DS("Please enter authentication password",				"��������֤����")
//#define STR_RESTORE_FACTORY_SETTINGS_SUCCESSFULLY	DS("Factory settings restored successfully",			"�ָ��������óɹ�")
#define STR_TIME_SETTING							DS("Time setting",										"ʱ������")
#define STR_MERCHANT_KEY_INPUT						DS("Merchant key input",								"�̻���Կ����")
#define STR_SCAN_QRCODE_IMPORT_MERCHANT_INFO		DS("Scan CUP Merchant ID",								"ɨ�뵼���̻���Ϣ")
#define STR_SCAN_QRCODE_IMPORT_FPS_ID				DS("Scan FPS Merchant ID",								"ɨ�뵼��FPS�̻���Ϣ")
#define STR_NO_TRANSACTION_RECORD                   DS("No transaction record",                             "�޽��׼�¼")
#define STR_NO_WRITE_SN					            DS("The terminal did not write the serial number",      "�ն�δд���к�")
#define STR_KEY_ADJUST                              DS("Press �� [7],[1] ��",                                 "�� �� [7],[1] ��")

#define STR_ENTER_ORI_KEY							DS("Please enter\nthe access code", 						"���������Ȩ��")	
#define STR_INPUT_NEW_KEY							DS("please input a\nnew access code",						"����������Ȩ��")
#define STR_INPUT_NEW_KEY_AGAIN						DS("please input the new\naccess code again",				"���ٴ���������Ȩ��")
#define STR_INPUT_TWO_ERR							DS("the two access code\nare inconsistent\n,please re-input","����������Ȩ�벻һ��\n����������")

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

