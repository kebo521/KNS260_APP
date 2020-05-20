#ifndef _COMMUNAL_
#define _COMMUNAL_
//==========================定义公共区版本号==============================
#define		PUBLIC_VERSION					"02"

#include "comm_type.h"
#include "file_stu.h"
#include "gui_sdk.h"
#include "sys_sdk.h"
#include "app_sdk.h"
#include "gfs_use.h"
#include "tls_sdk.h"
#include "drv_wifi.h"



#define RGB565(r,g,b)		((((b)&0xF8)<<8)|(((g)&0xFC)<<3)|((r)>>3))	//RGB24真彩转565色彩,色彩丢失，地位不保留

#define RGB565_PARENT		0xFF000000


#define TIMED_REFRESH		0


#define FASTBOOT_RUNNING	0
#define FASTBOOT_STOP		1

//#define API_sprintf  	sprintf
//#define API_memcpy        memcpy
//#define API_strcpy        strcpy
#define API_strncpy       strncpy
#define API_strcat        strcat
//#define API_memcmp        memcmp
#define API_strcmp        strcmp
#define API_strstr        strstr
//#define API_memset        memset
//#define API_strlen        strlen
//#define API_toupper       toupper
#define API_atoi			atoi

//================================================
#define RET_OK					0
#define RET_ERR					-1


#define		BYTE2_TO_INT(buf)	(buf[0]*0x100+buf[1])
#define		BYTE4_TO_INT(buf)	(buf[0]*0x1000000+buf[1]*0x10000+buf[2]*0x100+buf[3])

#define		DfGetStr2Len(nL,sL)	{nL=sL[0]*0x100+sL[1];}
#define		DfSetStr2Len(sL,nL)	{sL[0]=(u8)(nL/0x100); sL[1]=(u8)nL;}
#define 	DfGetStr4Len(nL,sL) {nL=sL[0]*0x1000000+sL[1]*0x10000+sL[2]*0x100+sL[3];}
#define 	DfSetStr4Len(sL,nL) {sL[0]=nL/0x1000000; sL[1]=(u8)(nL/0x10000);sL[2]=(u8)(nL/0x100);sL[3]=(u8)nL;}
#define		DfGetBeiSu(nL,n)	((nL+(n-1))&(~(n-1)))	//设成整数倍长度2/4/8/16/32...
#define 	offsetof(bak,item)	(int)(&((bak *)0)->item)
#define 	offsize(bak,item)	(sizeof(((bak *)0)->item))
#define 	_BIT(__n)       	(1<<(__n))



#ifndef FILE
typedef void*		  	FILE;
#endif


//---------定义通用函数所使用的接口----------------
#define		malloc(size)	        LocalAlloc(0,size)			
#define		free(p)					LocalFree(p)
#define		realloc(p,size)			LocalReAlloc(p,size)

#define		FreeNull(p) 			{free(p); p=NULL;}


//=========定义语言=======================================
//#define _LANG_ID_		(1)						//默热中文
//#define DS(en,ch)		((_LANG_ID_==0)?(en):(ch))					//多语言定义
//===========tls库定义接口=================================
#include "app_main.h"


#include "dataconv.h"

#include "ks_crypt.h"

//========客户区定义==================
#include "PE_customer.h"

//=======主区定义============
#include "ui_menu.h"
#include "ui_display.h"
#include "app_sdk.h"
#include "gbk2unicode.h"
#include "EvenMsg.h"

#include "drv_wifi.h"
#include "app_net.h"


#include "FactoryMenu.h"
#include "App_main.h"


#include "TermParfile.h"



#endif

