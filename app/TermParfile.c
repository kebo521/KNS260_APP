#include "communal.h"


//=========================�ն˲���==================================
#define  TermParfilePath         "TermPar.bin"  // �ն˵�������� �̻�����
#define  TransactionfilePath     "TradeRc.bin"   // �ն˵Ľ��׼�¼


//=====(TERM_PAR�ṹ�ɿͻ�������)===========
int TermParFactoryReset(void)
{
	API_fremove(TermParfilePath);
	TermParSetDefault();
	return APP_FileSaveBuff(TermParfilePath,0,&Term_Par, sizeof(Term_Par));
}

int TermParLoad(void)
{
	int ret;
	ret=APP_FileReadBuff(TermParfilePath,0,&Term_Par,sizeof(Term_Par));
	if((ret != sizeof(Term_Par)) || (0!=API_strcmp(Term_Par.CustVer,CustomerVersion)))
	{// ��һ�ο��������ļ�
		return TermParFactoryReset();
	}
	return 0;
} 

//д��������ж�Ӧ��������
int  Par_Set(void* pBuf,u16 tLen)
{ 
	return APP_FileSaveBuff(TermParfilePath,(u8*)pBuf-(u8*)&Term_Par,pBuf,tLen);
}

//д��������ж�Ӧ��������
int  Par_SaveAll(void)
{ 
	return APP_FileSaveBuff(TermParfilePath,0,&Term_Par,sizeof(Term_Par));
}

//==========================���׼�¼==================================

//=====(TradeRecordItem�ṹ��TRADE_RECORD_MAX �����ɿͻ�������)===========
typedef struct
{
	u32 counter;		//�ܽ��׼�������һֱ��¼��ȥ
	TradeRecordItem item[TRADE_RECORD_MAX];	
}TradeRecordTable;
static TradeRecordTable *pTradeRecord=NULL;

//===============���潻�׼�¼���ļ�ϵͳ=================================
int SaveTradeRecordToFile(void)
{
	if(pTradeRecord)
		return APP_FileSaveBuff(TransactionfilePath,0,pTradeRecord,sizeof(TradeRecordTable));
	return 1;
}
//===============���ļ�ϵͳ��ȡ���׼�¼=================================
int ReadTradeRecordToFile(void)
{
	int ret;
	if(pTradeRecord==NULL)
		pTradeRecord=(TradeRecordTable *)malloc(sizeof(TradeRecordTable));
	ret=APP_FileReadBuff(TransactionfilePath,0,pTradeRecord,sizeof(TradeRecordTable));
	if(ret != sizeof(TradeRecordTable))
	{//----���ն��޴��ļ�-----
		pTradeRecord->counter=0;
	}
	return 0;
}
//===============����һ�����׼�¼==================================
int ImportTradeRecord(TradeRecordItem *pItem)
{
	int index;
	if(pTradeRecord==NULL)
	{//----�����һ��-----
		pTradeRecord=(TradeRecordTable *)malloc(sizeof(TradeRecordTable));
		pTradeRecord->counter=0;
	}
	if(pItem)
	{
		index=pTradeRecord->counter%TRADE_RECORD_MAX;
		API_memcpy(&pTradeRecord->item[index],pItem,sizeof(TradeRecordItem));
		pTradeRecord->counter++;
	}
	return SaveTradeRecordToFile();
}
//===============����һ�����׼�¼======index(1~n)============================
TradeRecordItem * GetTradeRecord(u32 index)
{
	if(index==0 || pTradeRecord==NULL)
		return NULL;
	if(index <= TRADE_RECORD_MAX && index <= pTradeRecord->counter)
	{
		return &pTradeRecord->item[(pTradeRecord->counter-index)%TRADE_RECORD_MAX];
	}
	return NULL;
}

//===============����һ�����׼�¼======index(1~n)============================
int ExportTradeRecord(u32 index,TradeRecordItem *pItem)
{
	if(index == 0)
		return -1;
	if(pTradeRecord==NULL)
		return -5;
	//--------------------�������-------------------------------------
	if(index > TRADE_RECORD_MAX)
		return -8;
	if(pItem!=NULL && index <= pTradeRecord->counter)
	{
		API_memcpy(pItem,&pTradeRecord->item[(pTradeRecord->counter-index)%TRADE_RECORD_MAX],sizeof(TradeRecordItem));
	}
	if(pTradeRecord->counter > TRADE_RECORD_MAX)
		return TRADE_RECORD_MAX-index;
	return (pTradeRecord->counter - index);
}
void ClearTradeRecord()
{
     if(pTradeRecord)
	 {	
		 pTradeRecord->counter = 0;
		 API_memset(pTradeRecord->item,0,sizeof(pTradeRecord->item));
	     SaveTradeRecordToFile();
     }
     else
     {
     	API_fremove(TransactionfilePath);
     } 
}


//===========�ָ���������========================
int APP_ParFacInit(char* title)
{
	if(APP_InputPin(title,STR_ENTER_THE_AUTHENTICATION_PASSWORD,  STR_PRESS_NUBER_KEYS_ENTER, "002197")) return 1;
	#ifdef HARD_WIFI
	pSdkFun->wifi->Rest();
	#endif
	ClearTradeRecord();
	if(0==TermParFactoryReset())	  
		  APP_ShowMsg(title, STR_RESTORE_FACTORY_SETTINGS_SUCCESSFULLY,3000);
	return 0;
}


