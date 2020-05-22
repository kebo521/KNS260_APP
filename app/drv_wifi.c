#include "communal.h"

#ifdef HARD_WIFI

int WIFI_GetVersion(char* sVersion,int sizeVer)
{
	if(pSdkFun->wifi->GetVersion == NULL)
		return OPER_HARD_Err;	//无WIFI功能
	return pSdkFun->wifi->GetVersion(sVersion,sizeVer);
}
void WIFI_Sleep(int en)
{
	pSdkFun->wifi->Sleep(en);
}

int WIFI_Connet(u8 Enssl,char* pHost,u16 port)
{
	return pSdkFun->wifi->Connet(Enssl,pHost,port);
}

int WIFI_DisConnet(int timeoutMs)
{
	return pSdkFun->wifi->DisConnet(timeoutMs);
}

int WIFI_SendBuff(char* pSend,int sLen)
{
	return pSdkFun->wifi->SendBuff(pSend,sLen);
}


int WIFI_RecvBuff(char* pRecv,int RecvSize,int timeOutMs,CHECK_DATA_FULL pCheckFull)
{
	return pSdkFun->wifi->RecvBuff(pRecv,RecvSize,timeOutMs,pCheckFull);
}

int Wifi_NetAddrGet(char *pszIp)
{
	return pSdkFun->wifi->NetAddrGet(pszIp);
}



//================================================================
/*	0：OPEN
. 1：WEP
. 2：WPA_PSK
. 3：WPA2_PSK
. 4：WPA_WPA2_PSK
. 5：WPA2_Enterprise（.目前 AT 不不.支持连接这种加密 AP）
*/
u8 rak_EncrypName(char *pEnName,u8 sec_type)
{
	if(sec_type==0)
	{
		API_strcpy(pEnName,"OPEN");
	}
	else if(sec_type==1)
	{
		API_strcpy(pEnName,"WEP");
	}
	else if(sec_type==2)
	{
		API_strcpy(pEnName,"WPA_PSK");
	}
	else if(sec_type==3)
	{
		API_strcpy(pEnName,"WPA2_PSK");
	}
	else if(sec_type==4)
	{
		API_strcpy(pEnName,"WPA_WPA2_PSK");
	}
	else //if(sec_type==5)
	{
		API_strcpy(pEnName,"WPA2_Enterprise");
	}
	return sec_type;
}

//==============================================================================
static Wifi_MsgTable tWifiMsgTable;

int Wifi_RunItem(char* pTitle,int index)
{
	char ShowMsg[64];
	char sBuff[32+1];
	s8	rssi;
	u8	sec_type=0;
	EDIT_DATA tEdit;
	int ret;
	if(index < tWifiMsgTable.plist->writeTotal)
	{
		API_sprintf(ShowMsg,"%s:",STR_SIGNAL_STGTH);
		ret=API_strlen(ShowMsg);
		rssi=tWifiMsgTable.plist->item[index].rssi;
		if(rssi > -60)
			API_strcpy(ShowMsg+ret,STR_SIGNAL_XL);
		else if(rssi > -70)
			API_strcpy(ShowMsg+ret,STR_SIGNAL_L);
		else if(rssi > -80)
			API_strcpy(ShowMsg+ret,STR_SIGNAL_M);
		else if(rssi > -90)
			API_strcpy(ShowMsg+ret,STR_SIGNAL_S);
		else 
			API_strcpy(ShowMsg+ret,STR_SIGNAL_XS);
		ret=API_strlen(ShowMsg);
		API_sprintf(ShowMsg+ret,"\n%s:",STR_NET_ENC_MODE);
		ret=API_strlen(ShowMsg);
		sec_type=rak_EncrypName(ShowMsg+ret,tWifiMsgTable.plist->item[index].sectype);
	}
	else return EVENT_NONE;
	//----------------显示标题去掉"√"----------------------------
	//pTitle=tWifiMsgTable.plist->item[index].ssid;
	sBuff[0]='\0';
	if(sec_type)
	{
		//--------导入终端已存密码-------------
		if(tWifiMsgTable.pFile)
		{
			int i;
			for(i=0;i<tWifiMsgTable.pFile->Total;i++)
			{
				if(0==API_strcmp(tWifiMsgTable.pFile->item[i].ssid,tWifiMsgTable.plist->item[index].ssid))
				{
					API_strcpy(sBuff,tWifiMsgTable.pFile->item[i].password);
					break;
				}
			}
		}
		//--------------------------------------------------
		tEdit.pTitle=pTitle;
		tEdit.pFrontText=ShowMsg;
		tEdit.pAfterText=STR_EDIT_SWITCH_ALPHA;
		tEdit.Way=IME_NUM;
		tEdit.Limit=IME_NUM|IME_ABC|IME_abc|IME_SCAN;
		tEdit.Max=32;
		tEdit.Min=8;
		tEdit.timeOutMs=30*1000;
		ret=APP_Edit(&tEdit,sBuff);
		if(ret <  tEdit.Min)
			return EVENT_NONE;
	}
	else
	{
		if(EVENT_OK != APP_ShowMsg(pTitle,STR_OPEN_WALN,10*1000))
			return EVENT_NONE;
	}
	APP_ShowSta(pTitle,STR_NET_LINK_WLAN);
	if(0==pSdkFun->wifi->set_key(tWifiMsgTable.plist->item[index].ssid,sBuff,sec_type))
		APP_ShowMsg(pTitle,STR_NET_SUSS_LINK,5000);
	else
		APP_ShowMsg(pTitle,STR_NET_FAIL_LINK,5000);
	return (EVENT_QUIT+1);//退出当前菜单
}

int APP_WIFI_AutoRun(char *pTitle)
{
	APP_ScreenSleep(TRUE);
	return pSdkFun->wifi->AutoRun();
}

int APP_WIFI_ScanKey(char *pTitle)
{
	char OutCode[64],*pStard,*pPar,*pEnd;
	char ssid[32],pPassword[32];
	int  ret;
	if(pSdkFun->wifi->set_key == NULL)
		return OPER_HARD_Err;
	
	API_GUI_CreateWindow(pTitle,NULL,NULL,0);
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_EXSTYLE_UNDERLINE,STR_SCAN_QRCODE);
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,STR_EXIT);
	API_GUI_Show();
	ret=APP_OnlyCamScan(0,20,64,OutCode,30*1000);
	if(ret<0) return 1;
	//WIFI:T:WPA;S:ZTGuesthouse;P:zt10f213;;]
	pStard=API_strstr(OutCode,"WIFI:");
	if(pStard==NULL) return 1;
	
	pPar=API_strstr(pStard,"S:");
	if(pPar==NULL) return 2;
	pPar += 2;
	pEnd=API_strstr(pPar,";");
	if(pEnd==NULL) return 3;
	if(pPar[0]=='\"' && pEnd[-1]=='\"')
	{
		pPar++ ;
		pEnd--;
	}
	CLEAR(ssid);
	API_memcpy(ssid,pPar,pEnd-pPar);

	pPar=API_strstr(pStard,"P:");
	if(pPar==NULL) return 4;
	pPar += 2;
	pEnd=API_strstr(pPar,";");
	if(pEnd==NULL) return 5;
	if(pPar[0]=='\"' && pEnd[-1]=='\"')
	{
		pPar++ ;
		pEnd--;
	}
	CLEAR(pPassword);
	API_memcpy(pPassword,pPar,pEnd-pPar);
	TRACE("ssid[%s]pPassword[%s]\r\n",ssid,pPassword);
	APP_ShowSta(pTitle,STR_NET_LINK_WLAN);
	if(0==pSdkFun->wifi->set_key(ssid,pPassword,1))
		APP_ShowMsg(pTitle,STR_NET_SUSS_LINK,5000);
	else
		APP_ShowMsg(pTitle,STR_NET_FAIL_LINK,5000);
	return 0;
}

int APP_WIFI_SetKey(char *pTitle)
{
	int 	ret;
	u16		i,Max;
	char* *pShowItem;
	char	*pText;
	if(pSdkFun->wifi->get_host == NULL)
		return OPER_HARD_Err;
	
	APP_ShowSta(pTitle,STR_WLAN_READING);
	ret= pSdkFun->wifi->get_host(&tWifiMsgTable,30*1000);
	if(ret==WIFI_NO_OPEN)
	{
		return APP_ShowMsg(pTitle,STR_OPEN_WIFI,2000);
	}
	else if(ret==WIFI_NO_INIT)
	{
		return APP_ShowMsg(pTitle,STR_WLAN_NOT_START,3000);
	}
	
	if(tWifiMsgTable.plist==NULL ||tWifiMsgTable.plist->writeTotal<1)
	{
		return APP_ShowMsg(pTitle,STR_WLAN_FAIL_READ,3000);
	}
	//---------------------CreateNewMenuByStr----------------------------------------------
	Max=tWifiMsgTable.plist->writeTotal;
	pShowItem=(char **)malloc(Max*(4+20));
	pText=(char*)&pShowItem[Max];
	TRACE("Adder pShowItem[%X],pText[%X]\r\n",pShowItem,pText);
	for(i=0;i<Max;i++)
	{
		API_Utf8ToGbk(pText,18+1,tWifiMsgTable.plist->item[i].ssid);
		if(tWifiMsgTable.pCurrent->ssid[0])
		{
			if(0 == API_strcmp(tWifiMsgTable.plist->item[i].ssid,tWifiMsgTable.pCurrent->ssid))
			{
				ret=API_strlen(pText);
				if(ret<17)
					API_memset(pText+ret,' ',17-ret);
				API_strcpy(pText+15,"√");//
			}
		}
		pShowItem[i]=pText;
		pText += 20;
	}
	ret=APP_CreateNewMenuByStr(pTitle,Max,pShowItem,&Wifi_RunItem,30*1000);
	free(pShowItem);
	//--------------------------------------------------------------------------------------------
	APP_ScreenSleep(FALSE);
	APP_AddCurrentMenuOtherFun(MENU_KEY_FUN,(void*)&APP_WIFI_ScanKey,"扫码连接");
	APP_AddCurrentMenuOtherFun(MENU_OUT_FUN,(void*)&APP_WIFI_AutoRun,NULL);
	//APP_AddCurrentMenuOtherFun(MENU_SHOW_AFT,NULL,STR_KEY_UPDOWT);
	return ret;
}


int APP_WIFI_EN(char* pTitle)
{
	int ret,status;
	if(pSdkFun->wifi->get_status==NULL)
		return OPER_HARD_Err;
	status=pSdkFun->wifi->get_status();
	if(status < 0)
	{	
		if(EVENT_OK == APP_ShowMsg(pTitle,STR_WLAN_OK_OPEN,5000))
		{
			APP_ShowSta(pTitle,STR_WLAN_OPNEING);
			ret=pSdkFun->wifi->open();
			if(ret == OPER_ERR)
			{
				APP_ShowSta(pTitle,STR_FAILED);
				pSdkFun->wifi->close();
			}
			else if(ret == OPER_OK)
			{
				APP_ShowMsg(pTitle,STR_SUCCESS,2000);
			}
			return ret;
		}
	}
	else
	{
		if(EVENT_OK == APP_ShowMsg(pTitle,STR_WLAN_OK_CLOSE,5000))
		{
			APP_ShowSta(pTitle,STR_WLAN_CLOSEING);
			return pSdkFun->wifi->close();
		}
	}
	return 0;
}

#endif

