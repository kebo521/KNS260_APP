#include "communal.h"

void insertHeadNodes(char* money,char* date,char* type,char* porder,char *pOutRefundNo)
{
	TradeRecordItem item,*pItem=NULL;
	if(pOutRefundNo)
	{
		int i=1;
		while(1)
		{//避免想同编号存入其中
			pItem=GetTradeRecord(i++);
			if(pItem)
			{
				if(API_strcmp(pItem->out_refund_no,pOutRefundNo)==0)
				{
					if( API_strcmp(pItem->type,type)==0)
						return;
					if(API_strcmp(type,ORDER_REFUND)==0)
					{
						break;
					}
				}
				continue;
			}
			break;
		}
		API_strcpy(item.out_refund_no,pOutRefundNo);// 平台订单号
	}
	else
	{
		item.out_refund_no[0]='\0';
	}
	if(pItem==NULL)
		pItem = &item;	//New
	API_strcpy(pItem->money,money);
	API_memcpy(pItem->date,date,10);
	pItem->date[10]='\0';
	if(date[10]==0x20)//判断日期和时间之间是否有空格
		API_memcpy(pItem->time,date+11,8); 
	else
		API_memcpy(pItem->time,date+10,8); 
	pItem->time[8]='\0';
	API_strcpy(pItem->type,type);// 类型
	API_strcpy(pItem->order,porder);// 平台订单号
	TRACE("insertHeadNodes SAVE type[%s]money[%s]porder[%s]\r\n",type,money,porder);
	if(pItem == (&item))
	{
		ImportTradeRecord(pItem);
	}
	else
	{
		ImportTradeRecord(NULL);
	}
}

// 显示本地链表里的交易明细
int Option_ShowItem(char* pOutMsg,int index)
{
	TradeRecordItem item;
	char  sDmoney[12];
	int   Residual;
	int   count = 0;
	
	Residual=ExportTradeRecord(index+1, &item);
	if(Residual >= 0)
	{	
		Conv_TmoneyToDmoney(sDmoney, item.money);
		API_strcpy(pOutMsg, item.time);
		count =9 - (1+API_strlen(sDmoney));
		while(count--)
			API_strcat(pOutMsg, " ");
		
		if(API_strstr(item.type, ORDER_REFUND_APPLY))
			API_strcat(pOutMsg, " ");
		else if (API_strstr(item.type, ORDER_REFUND))
			API_strcat(pOutMsg, "-");
		else
			API_strcat(pOutMsg, "+");

		API_strcat(pOutMsg, sDmoney);
	}
  	return Residual;
}

BOOL Option_RunItem(char* pTitle,int index)
{
	TradeRecordItem item;
	if (ExportTradeRecord(index+1,&item) < 0)
	{
		return TRUE;
	}

	if (OPER_NEW == APP_ShowEnquiriesMsg(item.money,item.type,item.date,item.time,item.order))
	{
		if (API_strstr(item.type,"收款"))
		{
			if (EVENT_OK == APP_ShowTradeMsg(STR_PRESS_CONFIRM_REFUND,10*1000))
			{
				if(APP_InputPin(ORDER_REFUND, STR_ENTER_ACCESS_CODE,  STR_KEY_INPUT_NUMBER, Term_Par.password)) 
					return -1;
				if(0 == Tcp_Link(pTitle))
				{
					int ret;
					ret=SubRefundTrade(pTitle,item.order,item.money);
					Tcp_Close(pTitle);
					if(ret==PAY_QUERY)
					{

					}
				}
				return FALSE;
			}
		}
	}

	return TRUE;
}

// 显示本地链表里的交易明细
int  Enquiries(char* pTitle)
{
	if(0>ExportTradeRecord(1,NULL))
	{
		return APP_ShowTradeMsg(STR_NO_TRANSACTION_RECORD,3*1000);
	}
//	return APP_GUI_OpProcess("Transaction Record", Option_ShowItem, Option_RunItem, NULL);
}		

int APP_ScanInput(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinLen,int InputMaxlen)	
{
	int 	ret;
	EDIT_DATA	EditData;	
	CLEAR(EditData);
	EditData.pTitle     =pTitle;
	EditData.pFrontText =pFrontTextBuf;
	EditData.pAfterText =pAfterTextBuf;

	EditData.Min		=InputMinLen;
	EditData.Max		=InputMaxlen;
	EditData.Way		=IME_NUM;
	EditData.Limit		=IME_NUM|IME_ABC|IME_abc;
	EditData.timeOutMs=30*1000;

	ret =APP_Edit(&EditData,pInputDef);
	if(ret>=0)
		return 0;
	else
		return 1;	
}

int Terminal_SetIpAddress(char* title)
{
	u8	i,len;
	if(APP_InputAbc(STR_IP_ADDRESS_SETTINGS, STR_IP_ADDRESS, STR_PRESS_NUBER_KEYS_ENTER, Term_Par.ServerIp,0, 16)==0)
	{
		len =API_strlen(Term_Par.ServerIp);
		for(i=0;i<len;i++)
			if(Term_Par.ServerIp[i]=='*') Term_Par.ServerIp[i]='.';		
		Par_Set(Term_Par.ServerIp, sizeof(Term_Par.ServerIp));
	}
	return 0;
}
int Terminal_SetPort(char* title)
{
	if(APP_InputNum(STR_PORT_SETTINGS,STR_PORT,  STR_PRESS_NUBER_KEYS_ENTER, Term_Par.ServerPort, 0,6)==0)
	{
		Par_Set(Term_Par.ServerPort, sizeof(Term_Par.ServerPort));
	}
	return 0;
}


int Terminal_SetAPN(char* title)
{
	if(APP_InputAbc(STR_ACCESS_POINT_SETTINGS,STR_ACCESS_POINT, STR_PRESS_NUBER_KEYS_ENTER, Term_Par.Apn,0, 15)==0)
	{
		Par_Set(Term_Par.Apn, sizeof(Term_Par.Apn));
	}
	return 0;
}

int Terminal_SetVolume(char *pTitle)
{
	u16 MessageID,Message;
	int volume,Ret=OPER_TIMEOUT;
	API_GUI_CreateWindow(pTitle,TOK,TCANCEL,0);
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM, STR_KEY_ADJUST);
	API_GUI_Show();

	volume=AudioGetVolume();
	TRACE("pre AudioSetVolume get [%d], term volume[%d]\r\n", volume, Term_Par.volume);
	UI_ShowParMiddleSlide(volume,volume*10);
	Set_WaitEvent(30*1000,EVENT_KEY);
	while(1)
	{
		if(FIFO_OperatGetMsg(&MessageID,&Message))
		{
			if(MessageID == EVEN_ID_KEY_DOWN)
			{
				if(Message==K_OK)
				{
					Ret=AudioSetVolume(volume);
					TRACE("AudioSetVolume-[%d]\r\n",Ret);
					if(Ret<0)
					{
						TRACE("AudioSetVolume-[%d][%x]\r\n",Ret,GetLastError());
					}
					Sleep(150);
					//APP_TTS_PlayText("音量设为%d",volume);
					Term_Par.volume = volume;
					TRACE("AudioSetVolume save [%d]\r\n", Term_Par.volume);
					Par_Set(&Term_Par.volume, sizeof(Term_Par.volume));
					Ret=OPER_OK;
					break;
				}
				if(Message==K_CANCEL)
				{
					Ret=OPER_RET;
					break;
				}
				Rewrite_WaitTime(30*1000);
				if(Message==K_1)
				{
					if(volume<9)
					{//InCode
						volume++;
						UI_ShowParMiddleSlide(volume,volume*10);
					}
				}
				else if(Message==K_7)
				{
					if(volume>1)
					{//InCode
						volume--;
						UI_ShowParMiddleSlide(volume,volume*10);
					}
				}
			}
			else if(MessageID == EVEN_ID_TIME_OUT)
			{
				Ret=OPER_TIMEOUT;
				break;
			}
		}
	}
	Set_WaitEvent(TIME_INFINE,EVENT_NONE);
	return Ret;
}

/*
 *  获取终端SN
 *
 *  @return 0 获取成功,  -1 获取失败
 */
int GetTermSN(void)
{
    if(0 > APP_GetHardMsg(TYPE_TERM_HARD_SN, g_ColData.term_sn, sizeof(g_ColData.term_sn)))
    {
        return -1;
    }

    return 0;
}


/*
 *	设置商户号
 */
int SetMerchant_ID(char* title)
{
	if(APP_InputAbc(title,STR_MERCHANT_ID_SETTINGS,  STR_PRESS_NUBER_KEYS_ENTER, Term_Par.mch_id,0, 32)==0)
	{
		API_strcpy(g_ColData.mch_id, Term_Par.mch_id);
        Par_Set(Term_Par.mch_id, sizeof(Term_Par.mch_id));
	}

	return 0;
}


/*
 *	设置门店编号
 */
int SetShopID(char* title)
{
	if(APP_InputAbc(title,STR_SET_SHOP_ID,  STR_PRESS_NUBER_KEYS_ENTER, Term_Par.op_shop_id, 0, 32)==0)
	{
		API_strcpy(g_ColData.op_shop_id, Term_Par.op_shop_id);
        Par_Set(Term_Par.op_shop_id, sizeof(Term_Par.op_shop_id));
	}

	return 0;
}


/*
 *	设置操作员
 */
int SetUserID(char* title)
{
	if(APP_InputAbc(title,STR_SET_USER_ID,  STR_PRESS_NUBER_KEYS_ENTER, Term_Par.op_user_id,0, 32)==0)
	{
		API_strcpy(g_ColData.op_user_id, Term_Par.op_user_id);
        Par_Set(Term_Par.op_user_id, sizeof(Term_Par.op_user_id));
	}

	return 0;
}

int PE_InputPin(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf, 
	char* pInputDef,int InputMinlen,int InputMaxlen)
{
	int			ret;
	EDIT_DATA	EditData;

	CLEAR(EditData);
	EditData.pTitle			= pTitle;
	EditData.pFrontText		= pFrontTextBuf;
	EditData.pAfterText		= pAfterTextBuf;
	EditData.Min			= InputMinlen;
	EditData.Max			= InputMaxlen;
	EditData.Way			= IME_NUM|IME_PIN_MODE;
	EditData.Limit			= IME_NUM|IME_PIN_MODE;
    EditData.timeOutMs		= 30*1000;
	ret =APP_Edit(&EditData, pInputDef);
	if(ret >= 0)
		return 0;
	else
		return 1;
}

/*
 *  设置退款管理密码
 */
int SetRefundPwd(char* title)
{
	char pwd[6+1] = {0};
	char pwd2[6+1] = {0};

	API_strcpy(pwd, Term_Par.password);
	if(PE_InputAccessCode(title, STR_ENTER_ORI_KEY,  STR_PRESS_NUBER_KEYS_ENTER, pwd) == 0)
	{
		while(1)
		{
			CLEAR(pwd);
			CLEAR(pwd2);
			if ((PE_InputPin(title, STR_INPUT_NEW_KEY,  STR_PRESS_NUBER_KEYS_ENTER, pwd, 6, 6) != 0) ||
				PE_InputPin(title, STR_INPUT_NEW_KEY_AGAIN,  STR_PRESS_NUBER_KEYS_ENTER, pwd2, 6, 6) != 0)
			{
				return -1;
			}

			if (API_strcmp(pwd, pwd2) != 0)
			{
				APP_ShowMsg(title, STR_INPUT_TWO_ERR, 5000);
				continue;
			}

			API_strcpy(Term_Par.password, pwd);
			Par_Set(Term_Par.password, sizeof(Term_Par.password));
			APP_ShowMsg(title, STR_SET_OK, 5000);
			break;
		}
	}

	return 0;
}


/*
 *	显示sn二维码
 */
int ShowSnQrCode(char* title)
{
	char sn[32+1] = {0};

	if (0 == API_strlen(g_ColData.term_sn))
	{
		if(0 > APP_GetHardMsg(TYPE_TERM_HARD_SN, g_ColData.term_sn, sizeof(g_ColData.term_sn)))
		{
			APP_ShowMsg("WARNING","Terminal not available",3000);
			return -1;
		}
	}
	API_strcpy(sn,	g_ColData.term_sn);
	APP_ShowQRcodeDis(sn, NULL);
	return 0;
}


int CheckMchidIsNull(void)
{	
	if (0 == API_strlen(g_ColData.mch_id))
	{
		return 1;
	}

	return 0;
}

int InputMerchantKey(char* title)
{
	char  key[36]={0};
	if(APP_ScanInput(title,STR_MERCHANT_KEY_SETTINGS,  STR_PRESS_NUBER_KEYS_ENTER, key,16, 32)==0)
	{
		API_memset(Term_Par.mch_key,0,sizeof(Term_Par.mch_key));
		API_memcpy(Term_Par.mch_key,key,32);
		if(Par_Set(Term_Par.mch_key, sizeof(Term_Par.mch_key))==0)
		{
            API_strcpy(g_ColData.key,           Term_Par.mch_key);
			APP_ShowMsg(title,STR_SUCCESSFULLY_SET_UP,4000);	
		}
	}
	return 0;
}

int ScanMerchantInfo(char *title)
{
    char OutCode[64]={0};
    char mch_id[32];
    int  ret,IndexId;

    API_GUI_CreateWindow(title,NULL,NULL,0);
    API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_EXSTYLE_UNDERLINE, STR_SCAN_MERCHANT_INFO_CODE);
    API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,STR_PRESS_CONFIRMFILL_THE_LIGHT);
    API_GUI_Show();
    ret=APP_OnlyCamScan(0,41,50,OutCode,30*1000);
    if(ret<0) return 1;
    //------------取ID-----------------
    for(IndexId=0;IndexId<ret;IndexId++)
    {
        if(OutCode[IndexId] <= ' ') break;
    }
    if(IndexId<8 || IndexId>16)
    {
        APP_ShowMsg(title, STR_MERCHANT_NUMBER_LENGTH_ERROR,5000);
        return -1;
    }
    API_memcpy(mch_id,OutCode,IndexId);
    mch_id[IndexId]='\0';

    while(OutCode[IndexId] <= ' ') IndexId++;   //过滤空格获'\'
    //------------取KEY-----------------
    if((ret-IndexId) != 32)
    {
        APP_ShowMsg(title, STR_KEY_LENGTH_ERROR,5000);
        return -2;
    }

    API_strcpy(Term_Par.mch_id, mch_id);
    API_memcpy(Term_Par.mch_key, OutCode+IndexId, 32);
    Term_Par.mch_key[32]='\0';

    Par_Set(Term_Par.mch_id, sizeof(Term_Par.mch_id));
    Par_Set(Term_Par.mch_key, sizeof(Term_Par.mch_key));
    MachDatainit();

    return APP_ShowMsg(title,STR_IMPORTED_SUCCESSFULLY,5000);
}

/*
int ScanFPS_MerchantInfo(char *title)
{
    char OutCode[80]={0};
    char mch_id[36];
    int  ret,IndexId;

    API_GUI_CreateWindow(title,NULL,NULL,0);
    API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_EXSTYLE_UNDERLINE, STR_SCAN_MERCHANT_INFO_CODE);
    API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,STR_PRESS_CONFIRMFILL_THE_LIGHT);
    API_GUI_Show();
    ret=APP_OnlyCamScan(0,41,80,OutCode,30*1000);
    if(ret<0) return 1;
    //------------取ID-----------------
    for(IndexId=0;IndexId<ret;IndexId++)
    {
        if(OutCode[IndexId] <= ' ') break;
    }
    if(IndexId<8 || IndexId>32)
    {
        APP_ShowMsg(title, STR_MERCHANT_NUMBER_LENGTH_ERROR,5000);
        return -1;
    }
    API_memcpy(mch_id,OutCode,IndexId);
    mch_id[IndexId]='\0';

    while(OutCode[IndexId] <= ' ') IndexId++;   //过滤空格获'\'
    //------------取KEY-----------------
    if((ret-IndexId) != 32)
    {
        APP_ShowMsg(title, STR_KEY_LENGTH_ERROR,5000);
        return -2;
    }

    API_strcpy(Term_Par.FPS_id, mch_id);
    API_memcpy(Term_Par.FPS_key, OutCode+IndexId, 32);
    Term_Par.FPS_key[32]='\0';

    Par_Set(Term_Par.FPS_id, sizeof(Term_Par.FPS_id));
    Par_Set(Term_Par.FPS_key, sizeof(Term_Par.FPS_key));
    MachDatainit();

    return APP_ShowMsg(title,STR_IMPORTED_SUCCESSFULLY,5000);
}
*/

int PE_ParFacInit(char* title)
{
	char  key[16]={0};
	if(APP_InputAbc(title,STR_ENTER_THE_AUTHENTICATION_PASSu16,  STR_PRESS_NUBER_KEYS_ENTER, key,6, 10)==0)
	{
		if(API_memcmp(key,"002197",6)==0)
		{
        	ClearTradeRecord();
			if(0==TermParFactoryReset())	  
			APP_ShowMsg(title, STR_RESTORE_FACTORY_SETTINGS_SUCCESSFULLY,3000);
		}
	}
	return 0;
}

int SetTime(char* title)
{
	char str[32]={0};
	GetSysDateTime(str,"%04d%02d%02d%02d%02d%02d");
	if(APP_InputNum(title,STR_TIME_SETTING,  STR_PRESS_NUBER_KEYS_ENTER, str, 14,14)==0)
	{
		char Date[20];
		API_memcpy(Date   ,str	,4);
		API_memcpy(Date+5 ,str+4 ,2);
		API_memcpy(Date+8 ,str+6 ,2);
		API_memcpy(Date+11,str+8 ,2);
		API_memcpy(Date+14,str+10,2);
		API_memcpy(Date+17,str+12,2);
		SetSysDateTime(Date);
	}
	return 0;
}

int Terminal_SetGprsInfo(char *pTitle)
{
	CMenuItemStru MenuStruPar[]=
	{
		//"网络IP设置",							Terminal_SetIpAddress,
		//"端口设置",								Terminal_SetPort,
		//"接入点设置",							Terminal_SetAPN,
		STR_MERCHANT_ID_SETTINGS,				SetMerchant_ID,
		STR_MERCHANT_KEY_SETTINGS,				InputMerchantKey,
		STR_SCAN_QRCODE_IMPORT_MERCHANT_INFO,	ScanMerchantInfo,
		//"终端时间设置",							SetTime,
		//"恢复出厂设置",							PE_ParFacInit,
	};
	return APP_CreateNewMenuByStruct(pTitle,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
}

