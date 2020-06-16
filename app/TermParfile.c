#include "communal.h"


//=========================终端参数==================================
#define  TermParfilePath         "TermPar.bin"  // 终端的网络参数 商户参数
#define  TransactionfilePath     "TradeRc.bin"   // 终端的交易记录


//=====(TERM_PAR结构由客户区定义)===========
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
	{// 第一次开机创建文件
		return TermParFactoryReset();
	}
	return 0;
} 

//写入参数体中对应参数内容
int  Par_Set(void* pBuf,u16 tLen)
{ 
	return APP_FileSaveBuff(TermParfilePath,(u8*)pBuf-(u8*)&Term_Par,pBuf,tLen);
}

//写入参数体中对应参数内容
int  Par_SaveAll(void)
{ 
	return APP_FileSaveBuff(TermParfilePath,0,&Term_Par,sizeof(Term_Par));
}

//==========================交易记录==================================

//=====(TradeRecordItem结构与TRADE_RECORD_MAX 数量由客户区定义)===========
typedef struct
{
	u32 counter;		//总交易计数器，一直记录下去
	TradeRecordItem item[TRADE_RECORD_MAX];	
}TradeRecordTable;
static TradeRecordTable *pTradeRecord=NULL;

//===============保存交易记录到文件系统=================================
int SaveTradeRecordToFile(void)
{
	if(pTradeRecord)
		return APP_FileSaveBuff(TransactionfilePath,0,pTradeRecord,sizeof(TradeRecordTable));
	return 1;
}
//===============从文件系统读取交易记录=================================
int ReadTradeRecordToFile(void)
{
	int ret;
	if(pTradeRecord==NULL)
		pTradeRecord=(TradeRecordTable *)malloc(sizeof(TradeRecordTable));
	ret=APP_FileReadBuff(TransactionfilePath,0,pTradeRecord,sizeof(TradeRecordTable));
	if(ret != sizeof(TradeRecordTable))
	{//----新终端无此文件-----
		pTradeRecord->counter=0;
	}
	return 0;
}
//===============导入一条交易记录==================================
int ImportTradeRecord(TradeRecordItem *pItem)
{
	int index;
	if(pTradeRecord==NULL)
	{//----保存第一条-----
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
//===============导出一条交易记录======index(1~n)============================
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

//===============导出一条交易记录======index(1~n)============================
int ExportTradeRecord(u32 index,TradeRecordItem *pItem)
{
	if(index == 0)
		return -1;
	if(pTradeRecord==NULL)
		return -5;
	//--------------------容量检查-------------------------------------
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


//===========恢复出厂设置========================
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


