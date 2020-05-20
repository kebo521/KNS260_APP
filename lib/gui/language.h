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

#define _LANG_ID_					1											// 1 Ĭ������
#define DS(en,ch)					((_LANG_ID_==0)?(en):(ch))					//�����Զ���

#define STR_NUBER_INPUT  			DS("press keys to enter",	"�밴���ּ�����")
#define STR_ENTER_ADMIN_PASSu16	DS("enter admin password",	"���������Ա����")
#define STR_ENTER_DEBUG_PASSu16	DS("enter debug password",	"��������Թ�������")
#define STR_EDIT_SWITCH_ALPHA		DS("[Letter] switch input",	"��[��ĸ]���л�����")

//==============================WIFI����=================================================
#define STR_NET_SUSS_LINK			DS("Connected successfully",	"���ӳɹ�")
#define STR_NET_LINK_WLAN			DS("connect the network",		"��������")
#define STR_NET_FAIL_LINK			DS("Failed to connect the network","��������ʧ��")
#define STR_NET_ERR_LINK			DS("Network connection error",	"�������Ӵ���")
#define STR_NET_FAIL_SEND			DS("Failed to send data",		"��������ʧ��")
#define STR_NET_FAIL_RECV			DS("Failed to receive data",	"��������ʧ��")
#define STR_NET_ENC_MODE			DS("MODE",						"ģʽ")

#define STR_WLAN_OPNEING			DS("Opening WIFI...",			"WIFI����...")	
#define STR_WLAN_OK_OPEN			DS("Press [OK] to open WIFI",	"��[ȷ��]��Wifi")	
#define STR_WLAN_CLOSEING			DS("Closing WIFI...",			"WIFI�ر���...")	
#define STR_WLAN_OK_CLOSE			DS("Press [OK] to close WIFI",	"��[ȷ��]�ر�Wifi")	
#define STR_WLAN_READING			DS("Reading WIFI...",			"��ȡWIFI��...")	
#define STR_WLAN_FAIL_READ			DS("Failed to read WIFI",		"��ȡWIFIʧ��")	
#define STR_WLAN_NOT_START			DS("WIFI boot unaccomplished",	"WIFI����δ���")	

#define STR_SIGNAL_STGTH			DS("Signal strength",			"�ź�ǿ��")	
#define STR_SIGNAL_XL				DS("Very strong",				"��ǿ")	
#define STR_SIGNAL_L				DS("Strong",					"  ǿ")	
#define STR_SIGNAL_M				DS("Medium",					"  ��")	
#define STR_SIGNAL_S				DS("Weak",						"  ��")	
#define STR_SIGNAL_XS				DS("Very weak",					"����")	

#define STR_OPEN_WIFI				DS("Please open WIFI",			"�뿪��WIFI")
#define STR_SCAN_QRCODE				DS("Please scan QR code",		"��ɨ�ȵ��ά��")
#define STR_EXIT					DS("[Cancel] button to exit",	"[ȡ��]���˳�")
#define STR_OPEN_WALN				DS("Connect Open WALN?",		"ȷ�����ӿ�������?")



#endif

