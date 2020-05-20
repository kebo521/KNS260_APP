#include "communal.h"


//===============要求下载unicode.bin文件===============================
int API_GbkToUniCode(u16 *dest,int dest_size, char *src) 
{
	return pFontFun->GbkToUniCode(dest,dest_size,src);
}

int API_GbkToUtf8(char *pUtf8,int dest_size,char *pGbk) 
{
	return pFontFun->GbkToUtf8(pUtf8,dest_size,pGbk);
}


//===============要求下载gbk.bin文件===============================
int API_UniCodeToGbk(char *dest,int dest_size, u16 *pSrc,u16 tLen) 
{
	return pFontFun->UniCodeToGbk(dest,dest_size,pSrc,tLen);
}

int API_Utf8ToGbk(char *pGbk,int dest_size,char *pUtf8) 
{
	return pFontFun->Utf8ToGbk(pGbk,dest_size,pUtf8);
}



