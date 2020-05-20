

#ifndef _GBK2UNICODE_H_
#define _GBK2UNICODE_H_
extern int API_GbkToUniCode(u16 *dest,int dest_size, char *src);
extern int API_GbkToUtf8(char *pUtf8,int dest_size,char *pGbk);

extern int API_UniCodeToGbk(char *dest,int dest_size, u16 *pSrc,u16 tLen);
extern int API_Utf8ToGbk(char *pGbk,int dest_size,char *pUtf8);

#endif 

