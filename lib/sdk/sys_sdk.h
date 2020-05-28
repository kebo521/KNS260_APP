
#ifndef _SYS_SDK_
#define _SYS_SDK_

#include "sdk_port.h"
#include "sdk_font.h"


typedef struct{
	u16 Year; /*��1980-2099*/
	u8 Month; /*��1 �C12*/
	u8 Day; /*��1 �C31*/
	u8 Hour; /*ʱ0 �C 23*/
	u8 Minute; /*��0 �C59*/
	u8 Second; /*��0 �C59*/
	u8 DayOfWeek; /*��1�C��7������ȡʱ����Ч��*/
} ST_TIME;



typedef enum{
	LOG_DEBUG, /*��ʾ������Ϣ*/
	LOG_INFO, /*��ʾ��ʾ��Ϣ*/
	LOG_WARN, /*��ʾ������Ϣ*/
	LOG_ERROR, /*��ʾ������Ϣ*/
	LOG_NULL,	//�޵�����Ϣ
} LOG_T;


typedef struct	
{
	char Mask[4]; 	// "sdk"
	int (*Init)(char*);	//
	int (*Exit)(int);	//(int recode)
	u32 (*GetTickCount)(void);		// return current ms
	u8 (*IsTimeExpired)(u32);		// EndtimeMs
	void (*Sleep)(unsigned int);	//sleep Ms
	void (*GetTime)(ST_TIME*);	//(ST_TIME *systime)
	int (*SetTime)(ST_TIME*);

	char* (*eStrstr)(char*, const char*);	//(char* src1, const char* src2) ret Pointer end 
	void (*logSet)(LOG_T,int);					//(LOG_T CurrPrio,int clog) CurrPrio ���Լ���clog �Ƿ�����
	int (*Log)(LOG_T,const char*,...);		//(LOG_T Prio,const char *fmt,...)
	void (*logHex)(LOG_T,char*,void*,int);	//(LOG_T Prio,char* msg,void* pBuff,int Len)
	
	void (*kernalHandle)(void);	
	void (*kernelEnd)(void);
	void (*kernelLoad)(PFUNC);			//(PFUNC NewFunc)
	void (*kernelSeize)(PFUNC,PFUNC);	//(PFUNC pTarget,PFUNC NewFunc)
	void (*kernelRemove)(PFUNC);		//(PFUNC pTarget)
	void (*kernelTimeArrival)(int);		//(int tag_timeMs)	(GetTickCount + ms)
	int (*kernelRunFunc)(R_PFUNC);		//(R_PFUNC pRfunc)
}API_SDK_Def;

extern API_SDK_Def	api_SysFun;;


#define LogSet(t,c)						api_SysFun.logSet(t,c)	
#define LOG(t,...)						api_SysFun.Log(t, ## __VA_ARGS__)
#define TRACE(...)						api_SysFun.Log(LOG_INFO, ## __VA_ARGS__)
#define LOG_HEX(logT,msg,pBuff,Len)		api_SysFun.logHex(logT,msg,pBuff,Len)
#define TRACE_HEX(msg,pBuff,Len)		api_SysFun.logHex(LOG_INFO,msg,pBuff,Len)


#endif
