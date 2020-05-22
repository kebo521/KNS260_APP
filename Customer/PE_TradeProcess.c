#include "communal.h"


CoL_Data   g_ColData;
DfFlow_Link  pFlow;
char* pSendTranMsg=NULL;
char* pMD5Str=NULL;
char* pMd5=NULL;
#ifdef CONNECT_MYSELF
char *pSendLen7Addr=NULL;
#endif

TrandInfoMsgQueue *pTrandInfoMsgEnd=NULL;

// xml���ݴ��������������
char* Conv_HttpPost_GetData(char *pIndata)
{
	char *temp;
	temp = API_strstr(pIndata,"</xml>");
	if(temp)
	{
		*temp='\0';
		temp = API_strstr(pIndata,"<xml>");
		if(temp)
		{
			temp += 5;
			return temp;
		}
	}
	return NULL;
}

char *parse_xml_key(char *str, char **key)
{
    char *p = str;
    char *_key;
    
    p = API_strstr(p, "<");
    if (NULL == p)
    {
        return NULL;
    }
    
    _key = p + 1;
    p  = API_strstr(p, ">");
    if ( NULL == p )
    {
        return NULL;
    }
    *p = '\0';
    p++;
    
    //TRACE("%s�� ", _key);
    *key = _key;
    return p;
}

char *parse_xml_value(char *str, char **value)
{
    char *p = str;
    char *pos;
    char *value_begin, *value_end;
    const char cdata_head[] = "<![CDATA[";
    const char cdata_end[] = "]]>";
    
    pos = API_strstr(p, cdata_head);
    if( pos )
    {
		value_begin = pos + API_strlen(cdata_head);
		value_end   = API_strstr(value_begin, cdata_end);
        if ( !value_end )
        {
           return NULL;
        }
        
        //���� "</" tag
        pos = API_strstr(value_end, "</");
        if ( NULL == p )
        {
           return NULL;
        }
        p =  pos + 2;
    }
    else
    {
        value_begin = p;
        pos  = API_strstr(p, "</");
        if ( pos )
        {
            value_end = pos;
        }
        else
        {
            return NULL;
        }
        p = pos+1;
    }
    value_end[0] = '\0';
    //TRACE("%s\r\n", value_begin);
    *value = value_begin;
    return p;
}


/**
 * ����xml��Ԫ�ظ���
 *
 * @str xml�ַ���
 * @return Ԫ�ظ���
 */
int parse_to_count_items(char *str)
{
    int i = 0;
    int sign_count = 0;
    int item_count = 0;
    
    while(str[i])
    {
        if(str[i] == '<')
            sign_count++;
        i++;
    }
    
    //TRACE("%s\n", str);
    //TRACE("sign_count = [%d]\n", sign_count);
    
    if (NULL == API_strstr(str, "<![CDATA["))
    {
        item_count = sign_count / 2;
    }
    else
    {
        item_count = sign_count / 3;
    }
    //TRACE("count = [%d]\n", item_count);
    
    return item_count;
}

/**
 * ����xml����
 * ֧�� ����xml����
 * ֧�ָ�ʽ <total_fee>100</total_fee> �� <total_fee><![CDATA[100]]></total_fee>
 *
 * @str xml�ַ���
 * @return 0 �����ɹ�, ����ʧ�� -1
 */
sIdDataTable* parse_xml(char *str)
{
    char *p = str;
    char *key, *value;
    int count = 0;
    int len;
    sIdDataTable *table = NULL;
    
    count = parse_to_count_items( str );
    len = (int) API_strlen( str );
    if (count < 1) return NULL;
    
    //TRACE("count = %d len = %d\n", count, len);
    
    table = ( sIdDataTable* )malloc(sizeof(sIdDataTable) + (sizeof(sIdDataItem) * count) + len + 1);
	table->pRecvData = (char*)&table->Item[count];
	table->sLen      = len+1;

    API_memcpy(table->pRecvData, (char*)str, len+1);
    p = (char *)table->pRecvData;
    
    count = 0;
    
    while(*p)
    {
        // 1.�жϽ����Ƿ����
        p = API_strstr(p, "<");
        if (NULL == p)
        {
            if (count == 0)
            {
                return NULL;
            }
            break;  //����
        }
        // 1.��ȡkey
        if ((p =  parse_xml_key(p, &key)) == NULL)
            return NULL;
        //TRACE("%s\n", key);
        
        // 2.��ȡvalue
        if ((p =  parse_xml_value(p, &value)) == NULL)
           return NULL;
        
		table->Item[count].pID   = key;
		table->Item[count].pData = value;
        count ++;
    }
	table->Total     = count;     
    
    //TRACE("count = [%d]\n", count);
    //TRACE("\r\n");
    return table;
}

int PE_CheckRecvData(char* pRecv,int Len)
{
	pRecv[Len] = '\0';
	if (OPER_OK != PE_LoadRecvData(pRecv)){
		APP_ShowMsg(NULL, STR_DATA_FORMAT_ERR, 5000);
		return -1;
	}

	if (OPER_CRCERR == Conv_Sign_Check(PE_RecvTable,"key",g_ColData.key)){
		APP_ShowMsg(NULL, STR_SIGN_ERR, 5000);
		return -1;
	} 

	return 0;
}


int sha256_Sign_Check(sIdDataTable *pStart,const char* KeyName,char* KeyData)
{
	char *pGetStr,*pSignBuff;
	char* pSignData=NULL;
	u8 sha256Resultbuff[32],signBuff[32];
	u16 i,MaxNum;
	int ret;
	sIdDataItem *pItem;
	MaxNum=pStart->Total;
	pSignBuff=(char*)malloc(pStart->sLen);
	pGetStr=pSignBuff;
	for(i=0;i<MaxNum;i++)
	{
		pItem=&pStart->Item[i];
		if(0==API_strcmp("sign",pItem->pID))
		{
			pSignData=pItem->pData;
		}
		else
		{
			pGetStr += API_sprintf(pGetStr,"%s=%s&",pItem->pID,pItem->pData);
		}
	}
	if(pSignData)
	{
		pGetStr += API_sprintf(pGetStr,"%s=%s",KeyName,KeyData);
		API_Hash(HASH_TYPE_SHA256,(u8*)pSignBuff,pGetStr-pSignBuff,sha256Resultbuff,HASH_DIRECT);
		Conv_StrToBcd_Left(pSignData,32,signBuff);
		ret=API_memcmp(signBuff,sha256Resultbuff,16);
		if(ret)
		{
			*pGetStr='\0';
			TRACE("Err HttpPosData:");
			TRACE(pSignBuff);
			TRACE_HEX("Md5Resultbuff",sha256Resultbuff,16);
			TRACE_HEX("signBuff",signBuff,16);
			ret=OPER_CRCERR;
		}
	}
	else
	{
		TRACE("Err NoSignData");
		ret=OPER_NO_CHECK;
	}
	free(pSignBuff);
	return ret;
}

int FPS_CheckRecvData(char* pRecv,int Len)
{
	int ret = 0;

	pRecv[Len] = '\0';
	if (OPER_OK != PE_LoadRecvData(pRecv)){
		APP_ShowMsg(NULL, STR_DATA_FORMAT_ERR, 5000);
		return -1;
	}

	if (OPER_CRCERR == sha256_Sign_Check(PE_RecvTable,"key",g_ColData.keyFPS)){
		APP_ShowMsg(NULL, STR_SIGN_ERR, 5000);
		return -1;
	} 

	return ret;
}


// �����������
int PE_LoadRecvData(char *pInRecv)
{
	// �ύxml�ڲ�����
	pInRecv=Conv_HttpPost_GetData(pInRecv);
	if(pInRecv==NULL)
	{
		TRACE("->PE_LoadRecvData: GetHttpPOST ERR\r\n");
		return OPER_ERR;
	}
	TRACE("->pInRecvGetXml:\r\n%s\r\n",pInRecv);
	/*
	 * ����ṹ����, ����pID�ַ�������С������
	 */
	if(PE_RecvTable) free(PE_RecvTable);
	PE_RecvTable = parse_xml(pInRecv);
	if(PE_RecvTable==NULL) 
		return OPER_ERR;
	ArrayStringIdGroup(PE_RecvTable); 

	return OPER_OK;
}

// �ͷŽ�������
void PE_FreeRecvData(void)
{
	if(PE_RecvTable)
	{
		free(PE_RecvTable);
		PE_RecvTable=NULL;
	}
}

//=========��ȡID����================================
char* PE_GetRecvIdPar(char* pPostID)
{
	if(PE_RecvTable==NULL)
		return NULL;
	return Conv_GetParFindID(PE_RecvTable,pPostID);
}

//=========��ȡID����=================================
BOOL PE_ReadRecvIdPar(char* pPostID,char *pOutData,int OutSize)
{
	char *pData;
	if(PE_RecvTable==NULL)
		return FALSE;
	pData=Conv_GetParFindID(PE_RecvTable,pPostID);
	if(pData)
	{
		OutSize--;	//Ԥ��һ��������
		API_memcpy(pOutData,pData,OutSize);
		pOutData[OutSize]='\0';
		return TRUE;
	}
	return FALSE;
}

// �ȶ�ID��Ӧ�Ĳ���
int PE_CheckRecvIdPar(char* pPostID,char *pCheck)
{
	char *pData;
	if(PE_RecvTable==NULL)
		return OPER_ERR;
	pData=Conv_GetParFindID(PE_RecvTable,pPostID);
	if(pData)
	{
		if(0 == API_strcmp(pCheck,pData))
			return OPER_OK;
		TRACE("Id[%s]CheckData target[%s],Read[%s]\r\n",pPostID,pCheck,pData);
	}
	return OPER_ERR;
}

void DataInit(void)
{
	if(pSendTranMsg==NULL)
		pSendTranMsg=malloc(BufSize);
	if(pMD5Str==NULL)
		pMD5Str=malloc(BufSize);
	if(pMd5==NULL)
		pMd5=malloc(BufSize);
	
}
void DataFree(void)
{
	if(pSendTranMsg)
	{
		free(pSendTranMsg);
		pSendTranMsg=NULL;
	}
	if(pMd5)
	{
		free(pMd5);
		pMd5=NULL; 
	}
	PE_FreeRecvData();
}


void Send_add_item(char* pID,char* pData)
{
	if(API_strlen(pData))
	{
		PE_pSend=Conv_SetPackageHttpPOST(PE_pSend,pID,pData);
		*PE_pSend++ ='\n';
		PE_pMD5=Conv_SetPackageHttpGET(PE_pMD5,pID,pData);
		*PE_pMD5++= '&';	//������һ��
	}
}


void Send_add_sign(char* pID,char* pData)
{
	u8 Md5Resultbuff[16];
	PE_pMD5=Conv_SetPackageHttpGET(PE_pMD5,"key",g_ColData.key);
	
	md5((u8*)pMd5,PE_pMD5-pMd5,Md5Resultbuff);
	Conv_BcdToStr(Md5Resultbuff,16, g_ColData.sign);
	
	PE_pSend=Conv_SetPackageHttpPOST(PE_pSend,pID,pData);
	*PE_pSend++ ='\n';
}

void Send_add_sha256sign(char* pID)
{
	u8 sha256Buff[32]={0};
	char sSignOut[64+1];
	PE_pMD5=Conv_SetPackageHttpGET(PE_pMD5,"key",g_ColData.keyFPS);
	//TRACE_HEX("->sha256Buff1",pMd5,PE_pMD5-pMd5);
	API_Hash(HASH_TYPE_SHA256,(u8*)pMd5,PE_pMD5-pMd5,sha256Buff,HASH_DIRECT);
	Conv_BcdToStr(sha256Buff,sizeof(sha256Buff), sSignOut);
	PE_pSend=Conv_SetPackageHttpPOST(PE_pSend,pID,sSignOut);
}

// ��1���ĸ�����Ϣ  Ҳ�Ǹ�ǰ��Լ�������ͣ����Ͳ�ͨ���Ӳ�ͬ
void TradeGet_start(const char *pTradeAddress)
{  
	PE_SendBuf=pSendTranMsg;
	PE_pSend=PE_SendBuf;
	PE_pMD5 = pMd5;

	TRACE("pay_url:%s\r\n",pTradeAddress);
	
	#ifdef CONNECT_MYSELF
	pSendLen7Addr=Conv_HttpPost_SetHead((char*)pTradeAddress,PE_pSend);
	//API_sprintf(pSendLenAddr[7], "% 3d\r\n\r\n",API_strlen(param)) Ԥ��7���ֽڿռ�
	PE_pSend=pSendLen7Addr+7;
	PE_pSend=Conv_Strcpy(PE_pSend,"<xml>");
	#else
	PE_pSend=Conv_Strcpy(PE_pSend,"<r>");
	PE_pSend=Conv_SetPackageHttpPOST(PE_pSend,"u",(char*)pTradeAddress);
	PE_pSend=Conv_Strcpy(PE_pSend,"<xml>");
	#endif
	*PE_pSend++ ='\n';
}


void TradeGet_End(void)
{	
	#ifdef CONNECT_MYSELF
	char sendLen[8];
	PE_pSend=Conv_Strcpy(PE_pSend,"</xml>");
	*PE_pSend++ ='\n';
	//----------------��3���ֽڹ̶�����д��buff��---------------------
	API_sprintf(sendLen,"%03d\r\n\r\n",PE_pSend-pSendLen7Addr-7); //Ԥ��7���ֽڿռ�
	API_memcpy(pSendLen7Addr,sendLen,7);
	#else
	PE_pSend=Conv_Strcpy(PE_pSend,"</xml></r>");
	#endif
	pFlow.pMsgLen=PE_pSend-PE_SendBuf;
	*PE_pSend='\0';	//End
	//TRACE("TradeGet End pSend:");
	TRACE("->PE_SendBuf:\r\n%s\r\n", PE_SendBuf);
}

void GenerateNonceStr(void)
{
	u8 randbuff[16];
	APP_GetRand(randbuff,16);
	Conv_BcdToStr(randbuff,16,g_ColData.nonce_str);
}

/**
 * <����ʱ���ַ�������ʽyyyymmddhhmmss>
 *
 */
void GenerateTimeStart(void)
{
	char DataTime[20];
	GetSysDateTime(DataTime,"%04d%02d%02d%02d%02d%02d");
	API_sprintf(g_ColData.time_start,"%s",DataTime);
	TRACE("g_ColData.time_start:%s \r\n",g_ColData.time_start); 
}

void GenerateOutTradeNo(void)
{
	char DataTime[20];
	GetSysDateTime(DataTime, "%04d%02d%02d%02d%02d%02d");
	API_sprintf(g_ColData.out_trade_no, "%s%s", g_ColData.term_sn+2, DataTime);
	TRACE("g_ColData.out_trade_no:%s \r\n", g_ColData.out_trade_no); 
}

//�̻��˿�� out_refund_no
void GenerateOutRefundNo(void)
{ 
	char DataTime[20];
	GetSysDateTime(DataTime, "%04d%02d%02d%02d%02d%02d");
	API_sprintf(g_ColData.out_refund_no, "%s%s", g_ColData.term_sn+2, DataTime); 
}


TrandInfoMsgQueue *CreateInfoMsgQueueNode(void)
{
	TrandInfoMsgQueue *pEndMsg;
	char DataTime[20];
	pEndMsg=(TrandInfoMsgQueue *)malloc(sizeof(TrandInfoMsgQueue));
	if(pEndMsg==NULL)
	{
		APP_ShowMsg("WARNING","space is not enough",2000);
		return NULL;
	}
	API_memset(pEndMsg,0x00,sizeof(TrandInfoMsgQueue));
	GetSysDateTime(DataTime, "%04d%02d%02d%02d%02d%02d");
	API_sprintf(pEndMsg->msgId, "%s%s", g_ColData.term_sn+2,DataTime+4); 
	pEndMsg->pPrevious = pTrandInfoMsgEnd;
	pTrandInfoMsgEnd=pEndMsg;
	return pEndMsg;
}

void FreeInfoMsgQueueNode(TrandInfoMsgQueue *pNode)
{
	TrandInfoMsgQueue *pLast;
	if(pTrandInfoMsgEnd==NULL) return;
	if(pNode == pTrandInfoMsgEnd)
	{
		pTrandInfoMsgEnd=pTrandInfoMsgEnd->pPrevious;
		free(pNode);
		return;
	}	
	pLast=pTrandInfoMsgEnd;
	while(pLast)
	{
		if(pLast->pPrevious == pNode)
		{
			pLast->pPrevious=pNode->pPrevious;
			free(pNode);
			return;
		}
		pLast=pLast->pPrevious;
	}
}



/**
 * <��ʼ��Ԫ��ֵ>
 */
void InitElementValue(void)
{
	API_strcpy(g_ColData.attach,"testbuy");
	API_strcpy(g_ColData.body, "pay");
	API_strcpy(g_ColData.notify_url,"http://paysdk.WXPAY.qq.com/example/notify.php");
	API_strcpy(g_ColData.charset,"UTF-8");
	API_strcpy(g_ColData.sign_type,"MD5");
	API_strcpy(g_ColData.version, "2.0");
}

/**
 * <����service>
 */
void SetServiceElementValue(char *value)
{
	API_strcpy(g_ColData.service, value);
}


/**
 * <����service>
 *
 */
void SetMchCreateIp(void)
{
	API_strcpy(g_ColData.mch_create_ip, g_ColData.spbill_create_ip);
	if (API_strcmp(g_ColData.mch_create_ip, "") == 0)
	{
		// sdk ���ܻ��ȡʧ��
		API_strcpy(g_ColData.mch_create_ip, "192.168.0.5");
	}
}

/**
 * <������>
 *
 */
int InputTotalFee(char *pTitle)
{
	CLEAR(g_ColData.total_fee);
	if(0>APP_EditSum(pTitle,'S',g_ColData.total_fee,60*1000))
	{
		return -1;
	}

	return 0;
}

/**
 * <ɨ����������id>
 */	
int ScanAuthCode(void)
{
	CLEAR(g_ColData.auth_code);
	if(0 > APP_CamScan('S',g_ColData.total_fee,g_ColData.auth_code,10,256-1,20*1000)) 
	{
		return -1;
	}

	if(API_memcmp(g_ColData.auth_code,"28",2)==0)// ֧����/
	{      
		g_ColData.pay_type='A';
	}
	else 
	{
	    g_ColData.pay_type='W';
	}

	return 0;
}



