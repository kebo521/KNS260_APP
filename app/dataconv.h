#ifndef	__DATACONV_H__
#define	__DATACONV_H__

	//=======多层Json参数定义===========
	typedef enum
	{	
		ITEM_FALSE,
		ITEM_TRUE,
		ITEM_NULL,
		ITEM_INT,
		ITEM_STRING,
		ITEM_STRUCT,
		ITEM_ARRAY,
	}JSON_ITEM_TYPE;

	typedef struct
	{
		char	*pkey;
		void	*pValue;
		u16 	dType,vaNum;
	}dfJsonItem;

	typedef struct _dfJsonTable
	{
		struct _dfJsonTable *pNext;
		u16 		sLen,Total;
		dfJsonItem	Item[0];
	}dfJsonTable;
		

	//typedef void*  	dfJsonTable;	
	//=======单层Json参数定义===========
	typedef struct
	{
		char	*pID;
		char	*pData;
	}sIdDataItem;

	typedef struct _sIdDataTable
	{
		struct _sIdDataTable *pPrevious;	//回退指针
		char		*pRecvData;
		u16			sLen,Total;
		sIdDataItem Item[0];
	}sIdDataTable;

	//#include  "type.h"
	//#include  "string.h"
	//	write your header here
	//	Hex数字转成相应字符
						
	//	字符转成相应Hex数字
	//	'0'-'9'=0x0-0x9  'a'-'f'=0xA-0xF	'A'-'F'=0xA-0xF
	extern u8 Conv_CharToNum(char c);
			
	//  字符串转成BCD码，BCD码左对齐
	//	bcd	="\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
	//	Conv_StrToBcd("12345",5,bcd);	
	//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
	extern void Conv_StrToBcd_Left(char* str,s16 API_strlen,u8* bcd);
	
	//  字符串转成BCD码，BCD码右对齐
	//	bcd	="\x00\x00\x00\x00\x00\x00\x00";
	//	Conv_StrToBcd_Right("12345",5,bcd,7);	
	//	bcd	="\x00\x00\x00\x00\x01\x23\x45F";
	extern void Conv_StrToBcd_Right(char* str,s16 slen,u8 *bcd,s16 blen);
	
	//  BCD码转成字符串
	//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
	//	Conv_BcdToStr(bcd,4,str);	
	//	str	="12345FFF";
	extern void Conv_BcdToStr(u8* bcd,s16 blen,char* str);
	extern s16  Conv_StrToHex(char* Str,s16 StrLen,u8* Hex);
	//HEX转成字符串
	//最多只能转5位
	extern u8 Conv_HexToAsc(u16 Data,u8 *sAsc);
	extern void Conv_StrInsert(char *sTarget,char *sSource,u8 position);
	
	extern int Conv_IsHexChar(char b);
	extern u8 Conv_HexToBcd(u8 Hex);
	extern u8 Conv_BcdToHex(u8 Bcd);
	extern int Conv_StrToLong(char* number);
//	extern void Conv_FomartByteStr(u8 *s,u8 len);
	extern u32 Conv_StrToNum(u8* strbuf,u8 Inlen);
	extern void Conv_NumToStrRight(u32 InNum,u8 Outlen,u8* OutBuf);
	extern void Conv_NumToStrLeft(u32 InNum,u8* OutBuf);
	extern int Conv_MoneyToCentInt(char* pInstr);
	extern int Conv_DmoneyToTmoney(char* pOutStr,char* pInsMoney);
	extern int Conv_TmoneyToDmoney(char* pOutdMoney,char* pIntMoney);
	extern void Conv_UpperToLowercase(char* pBuff,int Len);
	extern void ArrayStringGroup(const char* pStringGroup[],u16 MaxNum,u16 *pArrayIndexTable);
	extern char *Conv_SetPackageHttpPOST(char* pPostStr,char* pPostID,char *pInData);
	extern char *Conv_SetPackageJson(char* pPostStr,char* pPostID,char *pInData);
	extern char *Conv_SetPackageHttpGET(char* pGetStr,char* pPostID,char *pInData);
	extern char *eStrcpy(char* destination,const char* source);
	extern void Conv_U32memcpy(u32* pOut,u32* pIn,int len);

	extern char* tRChar(const char* pfPath, const char cDim);
	extern u8 Conv_HttpGetName(char* pOutName,const char* pInAddre);
	extern char* Conv_HttpPost_SetHead(char * url,char *pBuffOut);
	extern char* Conv_Post_SetHead(char * url,char *pContentType,char *pBuffOut);
	extern char* Conv_HttpPost_SetData(char *param, char *pBuffOut);	
	//====================单层JSON处理======================================
	extern sIdDataTable* Conv_SingleJSON_GetMsg(char *pIndata,char* pEnd);
	//extern void ArrayStringIdGroup(sIdDataTable *pStart);
	extern int Conv_Sign_Check(sIdDataTable *pStart,const char* KeyName,char* KeyData);
	extern char* Conv_GetParFindID(sIdDataTable *pStart,char* pPostID);
	#define Conv_SingleJSON_free(pTable)	{free(pTable); pTable=NULL}
	//====================多层JSON处理======================================
	extern dfJsonTable* Conv_JSON_GetMsg(char *pIndata,char* pEnd);
	extern char* Conv_GetJsonValue(dfJsonTable *pStart,char* pKey,u8 *pType); //===参数pKey 支持多级别访问，用'/'隔开，如 "abc/efg/hij"==========
	extern void Conv_JSON_free(dfJsonTable *pTable);
	//===========================================================================
	extern void GetSysDateTime(char *pOutDateTime,const char *spFormat);
	extern void SetSysDateTime(char *pInDateTime);
	extern void APP_GetRand(u8 *pOutRand,int RandLen);

	//========================时间戳与标准时间转换=========================
	extern int Conv_DateToTimestamp(ST_TIME *pTimeIn,int timeZone,u32 *pTimestampOut);
	extern int Conv_TimestampToDate(u32 timestampIn,int timeZone,ST_TIME *pTimeOut);

	//extern void* API_memcpy(void *dst, const void *src, int count);
	//extern void* API_memset(void* dst, int value, int count);
	//extern int API_memcmp(const void* src1, const void* src2, int count);
	//extern char* API_strcpy(char* dst, const char* src);
	//extern int API_strlen(const char* src);
	//extern int API_sprintf(char* str, const char* format, ...);
#endif
