#ifndef _TERM_PAR_FILE_
#define _TERM_PAR_FILE_

extern int TermParFactoryReset(void);
extern int TermParLoad(void);// main º¯Êýµ÷ÓÃ
extern int Par_Set(void* pBuf,u16 tLen);
extern int APP_ParFacInit(char* title);

#define	SAVE_TERM_PAR(par)		Par_Set(par,sizeof(par))

extern int ImportTradeRecord(TradeRecordItem *pItem);
extern TradeRecordItem * GetTradeRecord(u32 index);
extern int ExportTradeRecord(u32 index,TradeRecordItem *pItem);	//index>0 range(1~n),
extern int SaveTradeRecordToFile(void);
extern int ReadTradeRecordToFile(void);
extern void ClearTradeRecord(void);


#endif 

