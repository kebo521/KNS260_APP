//===================================================================
//-------------------数据转换,打包服务------------------------------
//===================================================================
#include "communal.h"


//	Hex数字转成相应字符
//	0x0-0x9='0'-'9'   0xA-0xF='A'-'F'  其它=' '
const char BcdToAsicCode[16]={"0123456789ABCDEF"};
//	字符转成相应Hex数字
//	'0'-'9'=0x0-0x9  'a'-'f'=0xA-0xF	'A'-'F'=0xA-0xF
u8 Conv_CharToNum(char c)		
{
	if (c>='0' && c<='9')
	{
		return (c-'0');
	}
	else if(c>='a' && c<='f')
	{
		return (c-'a'+10);
	}
	else if(c>='A' && c<='F')
	{
		return (c-'A'+10);
	}
	else return 0;
}

//  字符串转成BCD码，BCD码左对齐
//	bcd	="\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
//	Conv_StrToBcd("12345",5,bcd);	
//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";

void Conv_StrToBcd_Left(char* str,s16 slen,u8* bcd)
{
	u8	c;
	u8	b;
	s16		i=0;
	s16		j=0;
	//TRACE_HEX("Conv_StrToBcd_Left:str",str,API_strlen);
	for(i=0;i<slen;i++)
	{
		c=Conv_CharToNum((char)str[i]);
		b=bcd[j];
		if (i%2) //Right
		{
			b&=0xF0;
			b|=c;
			bcd[j++]=b;
		}else
		{
			b&=0x0F;
			b|=(c<<4);
			bcd[j]=b;
		}
	}
}

//  字符串转成BCD码，BCD码右对齐
//	bcd	="\x00\x00\x00\x00\x00\x00\x00";
//	Conv_StrToBcd_Right("12345",5,bcd,7);	
//	bcd	="\x00\x00\x00\x00\x01\x23\x45F";


void Conv_StrToBcd_Right(char* str,s16 slen,u8 *bcd,s16 blen)
{
	u8 a,b;
	while (slen>0) 
	{
		b=Conv_CharToNum(str[--slen]);
		if(slen<1)
			a=bcd[blen-1]/16;	
		else
			a=Conv_CharToNum(str[--slen]);
		bcd[--blen]=a*16+b;
	}
}

//  BCD码转成字符串
//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
//	Conv_BcdToStr(bcd,4,str);	
//	str	="12345FFF";
void Conv_BcdToStr(u8* bcd,s16 blen,char* str)
{
	s16		i=0;
	s16		j=0;

	for(i=0;i<blen;i++)
	{
		str[j++]=BcdToAsicCode[bcd[i]/16];	//取高4位
		str[j++]=BcdToAsicCode[bcd[i]&0x0f]; //取低4位
	}
	str[j++]=0;
}
s16  Conv_StrToHex(char* Str,s16 StrLen,u8* Hex)
{
	
	s16 	i,j;
	u8	a,b;
	
	
	i = 0;
	j = 0;
	if(StrLen%2)
	{
		Hex[j++]=Conv_CharToNum(Str[i++]);
	}
	else
	{
		a=Conv_CharToNum(Str[i++]);
		b=Conv_CharToNum(Str[i++]);
		Hex[j++]=a*16+b;
	}
//	//@TRACE("i=%d,j=%d,StrLen=%d\n",i,j,StrLen);
//	//@TRACE_HEX("Hex",Hex,20);

	for(;i<StrLen;)
	{
		a=Conv_CharToNum(Str[i++]);
		b=Conv_CharToNum(Str[i++]);
		Hex[j++]=a*16+b;
//		//@TRACE("FOR i=%d,j=%d\n",i,j);
	}
	return j;
}
//HEX转成字符串
//最多只能转5位
u8 Conv_HexToAsc(u16 Data,u8 *sAsc)
{//选取diLimit位之内的转换成数据 十进制
	u16 num,a;
	u8 digit;
	num=Data;
	
	if(num>=10000) digit=5;
	else if(num>=1000) digit=4;
	else if(num>=100) digit=3;
	else if(num>=10) digit=2;
	else digit=1;
	
	if(digit>4){
		a=num/10000;
		*(sAsc+digit-5)=(a&0x0f)|0x30;
		num=num%10000;
	}
	if(digit>3){
		a=num/1000;
		*(sAsc+digit-4)=(a&0x0f)|0x30;
		num=num%1000;
	}
	if(digit>2){
		a=num/100;
		*(sAsc+digit-3)=(a&0x0f)|0x30;
		num=num%100;
	}
	if(digit>1){
		a=num/10;
		*(sAsc+digit-2)=(a&0x0f)|0x30;
		num=num%10;
	}
	*(sAsc+digit-1)=((u8)num&0x0f)|0x30; 
	return digit;
}

void Conv_StrInsert(char *sTarget,char *sSource,u8 position)
{//将SOURCE 插入到TARGET的POS位置//0=BEFORE
	u8 taLen,souLen;
	u8 i;
	taLen  = API_strlen(sTarget);
	souLen = API_strlen(sSource);
	if(position > taLen || souLen == 0)return; //插入位置不对,或插入字符串不对
	for(i=taLen+1;i>position;i--){
		sTarget[i+souLen-1]=sTarget[i-1];  //move sTarget back
	}
	//API_strcpy(sTarget+position+souLen,sTarget+position);
	API_strncpy(sTarget+position,sSource,souLen);
	sTarget[taLen+souLen]=0;
}


int Conv_IsHexChar(char b)
{
	return ((b>='0'&&b<='9')||(b>='a'&&b<='f')||(b>='A'&&b<='F'))?TRUE:FALSE;
}

int Conv_StrToLong(char* number)
{
   u8 		neg = 0;
   int   	n = 0;

   while (*number <= ' ' && *number > 0)
      ++number;
   if (*number == '-')
   {
      neg = 1;
      ++number;
   }
   else if (*number == '+')
      ++number;
   while (*number>='0' && *number<='9')
      n = (n * 10) + ((*number++) - '0');
   return (neg ? -n : n);
}
/*
void Conv_FomartByteStr(u8 *s,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
		s[i] &= 0xff;
}
*/
void String_Copy(u8* buf,u8* sBuf,u16 len)
{
	if(buf > sBuf)
	{
		while(len--)
		{
			buf[len]=sBuf[len];
		}
	}
	else
	{
		int i=0;
		for(i=0;i<len;i++)
		{
			buf[i]=sBuf[i];
		}
	}
}
//单字节Hex转成BCD形式
u8 Conv_HexToBcd(u8 Hex)
{
	u8 a,b;
	u8 Bcd;
	if(Hex>99)
	{
		return 0;
	}
	else
	{
		a=(Hex/10)&0x0f;
		b=(Hex%10)&0x0f;
		Bcd=a<<4|b;
		return Bcd;
	}

}
u8 Conv_BcdToHex(u8 Bcd)
{
	u8 a,b;
	a=(Bcd>>4)&0x0f;
	b=Bcd&0x0f;
	return (a*10+b)&0xff;
}

//-------------Guozu add---20110523---------------------
u32 Conv_StrToNum(u8* strbuf,u8 Inlen)
{
	u8 i;
	u32 buffhex=0;
	for(i=0;i<Inlen;i++)
	{
		buffhex *=10;
		buffhex +=(strbuf[i]-'0');
	}
	return buffhex;
}
void Conv_NumToStrRight(u32 InNum,u8 Outlen,u8* OutBuf)
{
	while(Outlen--)
	{
		OutBuf[Outlen]=InNum%10+'0';
		InNum /=10;
	}
}

void Conv_NumToStrLeft(u32 InNum,u8* OutBuf)
{
	u8 buff[12],Len=0;
	while(InNum)
	{
		buff[11-Len]=InNum%10+'0';
		InNum /=10;
		Len++;
	}
	API_memcpy(OutBuf,&buff[12-Len],Len);
	OutBuf[Len]=0x00;
}

//================检查并获得金额以分为单位的数值=====================
int Conv_MoneyToCentInt(char* pInstr)
{
	int Integers;
	u8 i,IntNum,j,Inlen;
	//------金额数据有效性检查----------
	Inlen=API_strlen(pInstr);
	if(Inlen>1)
	{//------两位以上判断----------
		if(pInstr[0]=='0' && pInstr[1]!='.')
			return -1;
	}
	for(IntNum=0;IntNum<Inlen;IntNum++)
		if(pInstr[IntNum]=='.') break;
	//-------小数点后不能超过两位--------
	if((Inlen-IntNum) > 3)
		return -2;
	//------小数点后不能再有小数点------
	for(j=IntNum+1;j<Inlen;j++)
	{
		if(pInstr[j]=='.') 
			return -3;
	}
	Integers=0;
	for(j=0;j<IntNum;j++)
		Integers=Integers*10 + (pInstr[j]&0x0f);
	IntNum++;
	for(i=0;i<2;i++)
	{
		Integers *= 10;
		if((i+IntNum) < Inlen)
			Integers += pInstr[IntNum+i]&0x0f;
	}
	return Integers;
}

//------------------显示金额 转 交易金额-------------------------------
int Conv_DmoneyToTmoney(char* pOutStr,char* pInsMoney)
{
	u8 i,j,k;
	u8 Inlen=API_strlen(pInsMoney);
	for(i=0;i<Inlen;i++)
		if(pInsMoney[i]=='.') break;
	//----整数部分------
	for(j=0;j<i;j++)
		pOutStr[j]=pInsMoney[j];
	//---小数部分精确两位----
	if(i<Inlen)	//有小数点
	{
		for(i=0; i<2; i++)
		{
			if((j+1) < Inlen)
				pOutStr[j]=pInsMoney[j+1];
			else
				pOutStr[j]='0';
			j++;
		}
	}
	else	//无小数点,两位0
	{
		pOutStr[j++]='0';
		pOutStr[j++]='0';
	}
	//---过滤无效位------
	for(i=0; i<j; i++)
		if(pOutStr[i]!='0')
			break;
	if(i)
	{
		k=j-i;
		for(j=0;j<k;j++)
			pOutStr[j]=pOutStr[j+i];
	}
	pOutStr[j]='\0';
	return j;
}

//------------------交易金额 转 显示金额-------------------------------
int Conv_TmoneyToDmoney(char* pOutdMoney,char* pIntMoney)
{
	u16 i=0,Inlen=API_strlen(pIntMoney);
	if(Inlen == 0)
	{
		pOutdMoney[0]='\0';
		return 0;
	}
	if(Inlen <= 2)
	{
		pOutdMoney[i++]='0';
		pOutdMoney[i++]='.';
		if(Inlen < 2)
			pOutdMoney[i++]='0';
		else
			pOutdMoney[i++]=*pIntMoney++;
		pOutdMoney[i++]=*pIntMoney++;
	}
	else
	{
		Inlen -= 2;
		while(i<Inlen)
		{
			pOutdMoney[i++]=*pIntMoney++;
		}
		pOutdMoney[i++]='.';
		pOutdMoney[i++]=*pIntMoney++;
		pOutdMoney[i++]=*pIntMoney++;
	}

	while(i--)	//去掉无效参数
	{
		if(pOutdMoney[i] == '.')
		{
			i--;
			break;
		}
		else if(pOutdMoney[i] != '0') 
			break;
	}
	pOutdMoney[++i]='\0';
	return i;
}


//===========统一转小写字符串Buff============================
void Conv_UpperToLowercase(char* pBuff,int Len)
{
	int i;
	for(i=0;i<Len;i++)
	{
		pBuff[i] |= 0x20;
	}
}


//===========用于POST打包方式数据============================
char *Conv_SetPackageHttpPOST(char* pPostStr,char* pPostID,char *pInData)
{
	int sIDlen,DataLen;
	*pPostStr++ ='<';
	sIDlen=API_strlen(pPostID);
	API_memcpy(pPostStr,pPostID,sIDlen);
	pPostStr += sIDlen;
	*pPostStr++ ='>';
	DataLen=API_strlen(pInData);
	API_memcpy(pPostStr,pInData,DataLen);
	pPostStr += DataLen;
	*pPostStr++ ='<';
	*pPostStr++ ='/';
	API_memcpy(pPostStr,pPostID,sIDlen);
	pPostStr += sIDlen;
	*pPostStr++ ='>';
	return pPostStr;
}


//========拷贝pPostID=pInData到pGetStr并返回pGetStr的末地址========
char *Conv_SetPackageHttpGET(char* pGetStr,char* pPostID,char *pInData)
{
	int sIDlen,DataLen;
	sIDlen=API_strlen(pPostID);
	API_memcpy(pGetStr,pPostID,sIDlen);
	pGetStr += sIDlen;
	*pGetStr++ ='=';
	DataLen=API_strlen(pInData);
	API_memcpy(pGetStr,pInData,DataLen);
	pGetStr += DataLen;
	return pGetStr;
}

//========拷贝pIn到pOut并返回pOut的末地址,以'\0'做结束========
char *Conv_Strcpy(char* pOut,const char* pIn)
{
	while(*pIn)
	{
		*pOut++ = *pIn++;
	}
	*pOut='\0';
	return pOut;
}

void Conv_U32memcpy(u32* pOut,u32* pIn,int len)
{
	while(len--)
	{
		*pOut++ = *pIn++;
	}
}



char* tRChar(const char* pfPath, const char cDim)
{
    int len = API_strlen(pfPath);
    int loop = 0;

    for (loop = len; loop > 0; loop--)
    {
        if (pfPath[loop] == cDim)
        {
            return (char*)&(pfPath[loop+1]);
        }
    }
    return (char*)pfPath;
}

u8 Conv_HttpGetName(char* pOutName,const char* pInAddre)
{
	u8 sslEn=0;
	char *pStr;
	pStr=API_strstr(pInAddre,"//");
	if(pStr)
	{
		pStr += 2;
		while(*pStr)
		{
			*pOutName = *pStr;
			if(*pOutName == '/')
				break;
			pOutName++;pStr++;
		}
		*pOutName='\0';

		if(API_strstr(pInAddre,"https"))	//https
			sslEn= 1;
	}
	else	//IP 地址
	{
		API_strcpy(pOutName,pInAddre);
	}
	return sslEn;
}


void twebGetHostGET(const char *url, char *server, char *GET, char *file)
{
	char myurl[256] = {0};
	char *pHost = NULL;
	char *temp = NULL;

	API_strcpy(myurl, url);
	
	if(file) API_strcpy(file, tRChar(url, '/'));   //分离文件名
	temp = API_strstr(myurl, "http://");
	if(temp) temp = myurl+API_strlen("http://");
	else
	{
		temp = API_strstr(myurl, "https://");
		if(temp) temp = myurl+API_strlen("https://");
		else temp = myurl;
	}
	for (pHost = temp; *pHost != '/' && *pHost != '\0'; ++pHost);
	if ((int)(pHost - myurl) == API_strlen(myurl))
		API_strcpy(GET, "/");
	else
		API_strcpy(GET, pHost);
	*pHost = '\0';
	API_strcpy(server, temp);
}

char* Conv_HttpPost_SetHead(char * url,char *pBuffOut)
{
	char serverAdd[64] = {0};
	char fileName[32] = {0};
	char PostAdd[64] = {0};
	twebGetHostGET(url, serverAdd, PostAdd, fileName);
	//TRACE("serverAdd:%s\r\nPostAdd:%s\r\nfileName:%s\r\n", serverAdd,PostAdd,fileName);
	API_sprintf(pBuffOut, "POST %s HTTP/1.1\r\n",PostAdd);
	pBuffOut += API_strlen(pBuffOut);
	pBuffOut=Conv_Strcpy(pBuffOut,"User-Agent: Apache-HttpClient/4.4.1 \r\n");
	API_sprintf(pBuffOut,"Host: %s\r\n",serverAdd);
	pBuffOut += API_strlen(pBuffOut);
	pBuffOut=Conv_Strcpy(pBuffOut,"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n");
	pBuffOut=Conv_Strcpy(pBuffOut,"Connection: Keep-Alive\r\n");
	pBuffOut=Conv_Strcpy(pBuffOut,"Content-Length:");
	return pBuffOut;
}

char* Conv_HttpPost_SetData(char *param, char *pBuffOut)
{
	API_sprintf(pBuffOut, "%d\r\n\r\n",API_strlen(param));//内容和请求头要用回车换行分开
	pBuffOut += API_strlen(pBuffOut);
	pBuffOut=Conv_Strcpy(pBuffOut, param);
	return pBuffOut;
}

//===============单元层JSON取数据={"id":"Data"}============================
sIdDataTable* Conv_SingleJSON_GetMsg(char *pIndata,char* pEnd)
{
	sIdDataTable *pIdData;
	sIdDataItem *pItem=NULL;
	char		*pStrStart,*pStrEnd;
	u16 	count;
	u8		ItemIndex,cycle=0;
	//------------找到起点-----------------------
	pStrStart=pIndata;
	while(pStrStart < pEnd)
	{
		if(*pStrStart++ == '{') 
		{
			cycle++;
			break;
		}
	}
	if(cycle!=1) return NULL;
	//------------找到终点-----------------------
	count=0;
	pStrEnd=pStrStart;
	while(pStrEnd < pEnd)
	{
		if(*pStrEnd == '{')
			cycle++;
		else if(*pStrEnd == '}')
			cycle--;
		if(cycle == 0) break;
		pStrEnd++;
	}
	if(cycle) return NULL;
	//-----------计算参数总数-----------------------
	count =0;
	cycle =0;
	while((pStrStart+count) < pStrEnd)
	{
		if(pStrStart[count] == ':')
			cycle++;
		count++;
	}
	if(cycle<1) return NULL;
	//-----------申请对应空间----------------------
	pIdData=(sIdDataTable*)malloc(sizeof(sIdDataTable)+(sizeof(sIdDataItem)*cycle)+count+1); //+1 = +'\0';
	pIndata = (char*)&pIdData->Item[cycle]; //不改变原来数据，借用原来形参
	//--------记录数据--------
	API_memcpy(pIndata,pStrStart,count);
	pStrEnd = pIndata+count;	//重新
	*pStrEnd = '\0';
	cycle=0;
	ItemIndex=0;
	while(pIndata < pStrEnd)
	{
		if(*pIndata == '\"')
		{
			if(cycle==0)	//0 strar
			{
				pItem=&pIdData->Item[ItemIndex++];
				cycle++;	// 1-> IDStar
			}
			else if(cycle==2) // 2-> End ID
			{
				*pIndata='\0';	//增加结束符号
				cycle++; // 3-> :
			}
			else if(cycle==4)	// 4->Data Strat
			{
				cycle++;		//5 Strat Data
			}
			else if(cycle==5)
			{//为5时空数据""
				pItem->pData=pIndata;
				*pIndata='\0';	//增加结束符号
				cycle=7;	// 7-> Next
			}
			else if(cycle==6) // 6-> End IDEnd
			{
				*pIndata='\0';	//增加结束符号
				cycle=7;	// 7-> Next
			}
		}
		else if(*pIndata == ':')
		{
			if(cycle==3) 
				cycle++; // 4-> Data:
		}
		else if(*pIndata == ',')
		{
			if(cycle==7)
			{
				*pIndata='\0';	
				cycle=0;  //0 strar
			}
		}
		else if(*pIndata == '{')
		{
			if(cycle == 4)
			{
				count=1;
				pItem->pData=pIndata++;
				while(pIndata < pStrEnd)
				{
					if(*pIndata == '{')
						count++;
					else if(*pIndata == '}')
						count--;
					if(count == 0) break;
					pIndata++;
				}
				pIndata++;	
				*pIndata='\0';	
				cycle=0;  //0 strar
			}
			else if(cycle==5) // 3-> Data Str
			{
				count=1;
				pItem->pData=pIndata++;
				while(pIndata < pStrEnd)
				{
					if(*pIndata == '{')
						count++;
					else if(*pIndata == '}')
						count--;
					if(count == 0) break;
					pIndata++;
				}
				pIndata++;
				*pIndata='\0';
				pIndata++;
				cycle=0;  //0 strar
			}
		}
		else
		{
			if(cycle==1)	// 1-> IDStar
			{
				pItem->pID=pIndata;
				cycle++;	// 2-> End IDStar
			}
			else if(cycle==4)	// 4-> Data Int 
			{
				if(*pIndata > ' ')	//过滤空格或换行符等
				{
					pItem->pData=pIndata;
					cycle=7;		//5 End ,
				}
			}
			else if(cycle==5) // 3-> Data Str
			{
				pItem->pData=pIndata;
				cycle++;	// 6-> End Data
			}
		}
		pIndata++;
	}
	pIdData->Total = ItemIndex;
	return pIdData;
}


//=======================依据pID字符串进行小端排列=================================================
void ArrayStringIdGroup(sIdDataTable *pStart)
{
	u16 i,j,MaxNum,sLen;
	sIdDataItem Item,*pItemi,*pItemj;
	if(pStart==NULL) return;
	sLen=sizeof(sIdDataItem)/4;
	MaxNum=pStart->Total;
	for(j=0;j<MaxNum;j++)
	{
		pItemj=&pStart->Item[j];
		for(i=j+1;i<MaxNum;i++)
		{
			pItemi=&pStart->Item[i];
			if(API_strcmp(pItemj->pID,pItemi->pID) > 0)
			{//小端排列
				Conv_U32memcpy((u32*)&Item,(u32*)pItemj,sLen);
				Conv_U32memcpy((u32*)pItemj,(u32*)pItemi,sLen);
				Conv_U32memcpy((u32*)pItemi,(u32*)&Item,sLen);
			}
		}
	}
}

int Conv_Sign_Check(sIdDataTable *pStart,const char* KeyName,char* KeyData)
{
	char *pGetStr,*pMd5Data;
	char* pSignData=NULL;
	u8 Md5Resultbuff[16],signBuff[16];
	u16 i,MaxNum;
	int ret;
	sIdDataItem *pItem;
	MaxNum=pStart->Total;
	pMd5Data=(char*)malloc(pStart->sLen);
	pGetStr=pMd5Data;
	for(i=0;i<MaxNum;i++)
	{
		pItem=&pStart->Item[i];
		if(0==API_strcmp("sign",pItem->pID))
		{
			pSignData=pItem->pData;
		}
		else
		{
			API_sprintf(pGetStr,"%s=%s&",pItem->pID,pItem->pData);
			pGetStr += API_strlen(pGetStr);
		}
	}
	if(pSignData)
	{
		API_sprintf(pGetStr,"%s=%s",KeyName,KeyData);
		pGetStr += API_strlen(pGetStr);
		API_Hash(HASH_TYPE_MD5,(u8*)pMd5Data,pGetStr-pMd5Data,Md5Resultbuff,HASH_DIRECT);
		Conv_StrToBcd_Left(pSignData,32,signBuff);
		ret=API_memcmp(signBuff,Md5Resultbuff,16);
		if(ret)
		{
			*pGetStr='\0';
			TRACE("Err HttpPosData:");
			TRACE(pMd5Data);
			TRACE_HEX("Md5Resultbuff",Md5Resultbuff,16);
			TRACE_HEX("signBuff",signBuff,16);
			ret=OPER_CRCERR;
		}
	}
	else
	{
		TRACE("Err NoSignData");
		ret=OPER_NO_CHECK;
	}
	free(pMd5Data);
	return ret;
}

char* Conv_GetParFindID(sIdDataTable *pStart,char* pPostID)
{
	int ret;
	u16 left,right,middle;
	//------中位法找到节点--------
	left=0;
	right=pStart->Total;
	while(left < right)
	{
		middle=(left+right)/2;
		ret=API_strcmp(pPostID,pStart->Item[middle].pID);
		if(ret==0)
		{
			return pStart->Item[middle].pData;
		}
		if(ret > 0)
			left=middle+1;
		else
			right=middle;
	}
	TRACE("Conv_GetParFindID[%s] Nofind\r\n",pPostID);
	return NULL;
}

//===多层JSON处理功能{"abb":"cdd","struct":{"abb":"cdd"}.....}===============
//--注: pIndata不能是ROM空间，处理后会修改pIndata中的参数,
//--    用完后需要Conv_JSON_free释放空间
dfJsonTable* Conv_JSON_GetMsg(char *pIndata,char* pEnd)
{
	return (dfJsonTable*)pSdkFun->app->JsonLoad(pIndata,pEnd);
}

/*
===参数pKey 支持多级别访问，用'/'隔开,支持组访问用"[i]",i表示下标，如 "abc/list[2]/hij"==========
注: ITEM_STRUCT,类型:pType为空时不会返回指针.
如返回指针为ITEM_STRUCT类型可当(dfJsonTable*)参数继续用Conv_GetJsonValue来解下一层
*/
char* Conv_GetJsonValue(dfJsonTable *pStart,char* pKey,u8 *pType)
{
	return (char*)pSdkFun->app->JsonGetValue(pStart,pKey,pType);
}


void Conv_JSON_free(dfJsonTable *pTable)
{
	pSdkFun->app->JsonDestroy(pTable);
}
//==========================================================================================
void GetSysDateTime(char *pOutDateTime,const char *spFormat)
{
	ST_TIME	dtime;
	OsGetTime(&dtime);
	API_sprintf(pOutDateTime,spFormat,
			dtime.Year,dtime.Month,dtime.Day,
			dtime.Hour,dtime.Minute,dtime.Second); 

}

//---输入格式 2018 03 08 17 03 43---每个元素间隔不限----------------
void SetSysDateTime(char *pInDateTime)
{
	ST_TIME dtime,inTime;
	char sBuff[8];
	//2018 03 08 17 03 43
	API_memcpy(sBuff,pInDateTime,4); sBuff[4]='\0';
	inTime.Year =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+5,2); sBuff[2]='\0';
	inTime.Month=API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+8,2); //sBuff[2]='\0';
	inTime.Day =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+11,2); //sBuff[2]='\0';
	inTime.Hour =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+14,2); //sBuff[2]='\0';
	inTime.Minute=API_atoi(sBuff);
	
	OsGetTime(&dtime);
	if(dtime.Year!=inTime.Year || dtime.Month!=inTime.Month || dtime.Day!=inTime.Day \
		|| dtime.Hour!=inTime.Hour || dtime.Minute!=inTime.Minute)
	{
		API_memcpy(sBuff,pInDateTime+17,2); //sBuff[19]='\0';
		inTime.Second=API_atoi(sBuff); 
		OsSetTime(&inTime);
	}
}


void APP_GetRand(u8 *pOutRand,int RandLen)
{
	int systemTime[2];
	u8* pRand;
	systemTime[1]=API_TimeCurrMS();
	systemTime[0]= ~systemTime[1];
	pRand = (u8*)systemTime;
	Des_B1Dec(pRand,"app23key",1);
	while(RandLen--) *pOutRand++ = *pRand++;
}

//===================DateTime to Timestamp=============================================
#define TIME_SECONDS_IN_DAY 		(24*3600)
#define TIME_SECONDS_IN_WEEk		(7*TIME_SECONDS_IN_DAY)
#define TIME_SECONDS_IN_NORMAL_YEAR (365*TIME_SECONDS_IN_DAY)
#define TIME_SECONDS_IN_LEAP_YEAR	(366*TIME_SECONDS_IN_DAY)

const static u8 Month_MaxDay[12] ={31,28,31,30,31,30,31,31,30,31,30,31};

/* Determines year is a leap year */
static int cal_leapyear(unsigned int year)
{
	if((((year&0x03)==0) && (year % 100)) ||  (year % 400 == 0))/* Leap year */
	{
		return 1;
	}
	/* Not a leap year */
	return 0;
}

/* Returns 0 if encoded properly, or -1 if error */
/* timeZone East is +, West is - */
/* Epoch is 1970-01-01 00:00:00 */
int Conv_DateToTimestamp(DATE_TIME *pTimeIn,int timeZone,u32 *pTimestampOut)
{
	u32 i,DayAdd,timeAddS;

	if(pTimeIn->Year < 1970)
		return -1;
	if((pTimeIn->Month < 1) || (pTimeIn->Month > 12)) 
		return -1;
	if (pTimeIn->Day < 1) 
		return -1;
	if (pTimeIn->Day > (Month_MaxDay[pTimeIn->Month-1] + ((pTimeIn->Month == 2) && cal_leapyear(pTimeIn->Year)))) 
		return -1;
	
	timeAddS=0;
	/* Count years */
	for(i=1970;i<pTimeIn->Year;i++)
	{
		timeAddS += cal_leapyear(i) ? TIME_SECONDS_IN_LEAP_YEAR : TIME_SECONDS_IN_NORMAL_YEAR;
	}
	DayAdd=0;
	/* Count months */
	for(i=1;i<pTimeIn->Month;i++)
	{
		DayAdd += Month_MaxDay[i-1]+((i == 2) && (cal_leapyear(pTimeIn->Year)));
	}
	/* Convert days to seconds */
	DayAdd +=  (pTimeIn->Day - 1);
	timeAddS += DayAdd*TIME_SECONDS_IN_DAY;
	/* Rest is easy */
	timeAddS += pTimeIn->Hour * 3600;
	timeAddS += pTimeIn->Min* 60;
	timeAddS += pTimeIn->Sec;
	timeAddS -= timeZone*3600;
	*pTimestampOut = timeAddS;
	return 0;
}

/* Returns 0 if decoded properly, or -1 if error */
/* timeZone East is +, West is - */
/* Epoch is 1970-01-01 00:00:00 */
int Conv_TimestampToDate(u32 timestampIn,int timeZone,DATE_TIME *pTimeOut)
{
	u32 i,count,base;

	/* Initialize time structure */
	count	= timestampIn+(timeZone*3600);
	pTimeOut->Year		= 1970;
	pTimeOut->Month		= 1;
	pTimeOut->Day		= 1;
	pTimeOut->WeekDay	= 4;
      
	/* Take off years */
	while (count >= (base=(cal_leapyear(pTimeOut->Year) ? TIME_SECONDS_IN_LEAP_YEAR : TIME_SECONDS_IN_NORMAL_YEAR))) 
	{
		count -= base;
		pTimeOut->Year++;
	}
      
	/* Now we have only days left. We are at 01-01-year */
	/* Months are zero-indexed for simplicity. January == 0 */
	for (i = 0; i < 12; i++) 
	{
		base = (Month_MaxDay[i]+((pTimeOut->Month== 2) && (cal_leapyear(pTimeOut->Year))))*TIME_SECONDS_IN_DAY;
		if (count < base) 
			break;
		
		count -= base;
		pTimeOut->Month++;
	}
	/* Determine days */
	pTimeOut->Day+= (count / TIME_SECONDS_IN_DAY);

	/* Determine HM:MM:SS */
	pTimeOut->Hour	= (count % TIME_SECONDS_IN_DAY) / 3600;
	pTimeOut->Min	= (count % 3600) / 60;
	pTimeOut->Sec	= count % 60;
	  
	/*****************1week equal 7 days***************************/
	count=timestampIn%TIME_SECONDS_IN_WEEk;
	pTimeOut->WeekDay+=count/TIME_SECONDS_IN_DAY;
	if(pTimeOut->WeekDay>= 7)
		pTimeOut->WeekDay = pTimeOut->WeekDay - 7;	
	return 0;
}

//=====================================================================================================


char* API_strcpy(char* dst, const char* src)
{
	return strcpy(dst,src);

}


int API_sprintf(char* str, const char* format, ...)
{
	int ret;
	va_list arg;
	va_start(arg, format);
	ret=vsprintf(str,format,arg);
	va_end(arg);
	return ret;
}


