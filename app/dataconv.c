//===================================================================
//-------------------����ת��,�������------------------------------
//===================================================================
#include "communal.h"


//	Hex����ת����Ӧ�ַ�
//	0x0-0x9='0'-'9'   0xA-0xF='A'-'F'  ����=' '
const char BcdToAsicCode[16]={"0123456789ABCDEF"};
//	�ַ�ת����ӦHex����
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

//  �ַ���ת��BCD�룬BCD�������
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

//  �ַ���ת��BCD�룬BCD���Ҷ���
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

//  BCD��ת���ַ���
//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
//	Conv_BcdToStr(bcd,4,str);	
//	str	="12345FFF";
void Conv_BcdToStr(u8* bcd,s16 blen,char* str)
{
	s16		i=0;
	s16		j=0;

	for(i=0;i<blen;i++)
	{
		str[j++]=BcdToAsicCode[bcd[i]/16];	//ȡ��4λ
		str[j++]=BcdToAsicCode[bcd[i]&0x0f]; //ȡ��4λ
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
//HEXת���ַ���
//���ֻ��ת5λ
u8 Conv_HexToAsc(u16 Data,u8 *sAsc)
{//ѡȡdiLimitλ֮�ڵ�ת�������� ʮ����
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
{//��SOURCE ���뵽TARGET��POSλ��//0=BEFORE
	u8 taLen,souLen;
	u8 i;
	taLen  = API_strlen(sTarget);
	souLen = API_strlen(sSource);
	if(position > taLen || souLen == 0)return; //����λ�ò���,������ַ�������
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
//���ֽ�Hexת��BCD��ʽ
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

//================��鲢��ý���Է�Ϊ��λ����ֵ=====================
int Conv_MoneyToCentInt(char* pInstr)
{
	int Integers;
	u8 i,IntNum,j,Inlen;
	//------���������Ч�Լ��----------
	Inlen=API_strlen(pInstr);
	if(Inlen>1)
	{//------��λ�����ж�----------
		if(pInstr[0]=='0' && pInstr[1]!='.')
			return -1;
	}
	for(IntNum=0;IntNum<Inlen;IntNum++)
		if(pInstr[IntNum]=='.') break;
	//-------С������ܳ�����λ--------
	if((Inlen-IntNum) > 3)
		return -2;
	//------С�����������С����------
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

//------------------��ʾ��� ת ���׽��-------------------------------
int Conv_DmoneyToTmoney(char* pOutStr,char* pInsMoney)
{
	u8 i,j,k;
	u8 Inlen=API_strlen(pInsMoney);
	for(i=0;i<Inlen;i++)
		if(pInsMoney[i]=='.') break;
	//----��������------
	for(j=0;j<i;j++)
		pOutStr[j]=pInsMoney[j];
	//---С�����־�ȷ��λ----
	if(i<Inlen)	//��С����
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
	else	//��С����,��λ0
	{
		pOutStr[j++]='0';
		pOutStr[j++]='0';
	}
	//---������Чλ------
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

//------------------���׽�� ת ��ʾ���-------------------------------
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

	while(i--)	//ȥ����Ч����
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


//===========ͳһתСд�ַ���Buff============================
void Conv_UpperToLowercase(char* pBuff,int Len)
{
	int i;
	for(i=0;i<Len;i++)
	{
		pBuff[i] |= 0x20;
	}
}


//===========����POST�����ʽ����============================
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


//========����pPostID=pInData��pGetStr������pGetStr��ĩ��ַ========
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

//========����pIn��pOut������pOut��ĩ��ַ,��'\0'������========
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
            return &(pfPath[loop+1]);
        }
    }
    return pfPath;
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
	else	//IP ��ַ
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
	
	if(file) API_strcpy(file, tRChar(url, '/'));   //�����ļ���
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
	API_sprintf(pBuffOut, "%d\r\n\r\n",API_strlen(param));//���ݺ�����ͷҪ�ûس����зֿ�
	pBuffOut += API_strlen(pBuffOut);
	pBuffOut=Conv_Strcpy(pBuffOut, param);
	return pBuffOut;
}

//===============��Ԫ��JSONȡ����={"id":"Data"}============================
sIdDataTable* Conv_SingleJSON_GetMsg(char *pIndata,char* pEnd)
{
	sIdDataTable *pIdData;
	sIdDataItem *pItem=NULL;
	char		*pStrStart,*pStrEnd;
	u16 	count;
	u8		ItemIndex,cycle=0;
	//------------�ҵ����-----------------------
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
	//------------�ҵ��յ�-----------------------
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
	//-----------�����������-----------------------
	count =0;
	cycle =0;
	while((pStrStart+count) < pStrEnd)
	{
		if(pStrStart[count] == ':')
			cycle++;
		count++;
	}
	if(cycle<1) return NULL;
	//-----------�����Ӧ�ռ�----------------------
	pIdData=(sIdDataTable*)malloc(sizeof(sIdDataTable)+(sizeof(sIdDataItem)*cycle)+count+1); //+1 = +'\0';
	pIndata = (char*)&pIdData->Item[cycle]; //���ı�ԭ�����ݣ�����ԭ���β�
	//--------��¼����--------
	API_memcpy(pIndata,pStrStart,count);
	pStrEnd = pIndata+count;	//����
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
				*pIndata='\0';	//���ӽ�������
				cycle++; // 3-> :
			}
			else if(cycle==4)	// 4->Data Strat
			{
				cycle++;		//5 Strat Data
			}
			else if(cycle==5)
			{//Ϊ5ʱ������""
				pItem->pData=pIndata;
				*pIndata='\0';	//���ӽ�������
				cycle=7;	// 7-> Next
			}
			else if(cycle==6) // 6-> End IDEnd
			{
				*pIndata='\0';	//���ӽ�������
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
				if(*pIndata > ' ')	//���˿ո���з���
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

/*
sIdDataTable* Conv_JSON_GetMsg(char *pIndata,char* pEnd)
{
	sIdDataTable *pIdData;
	sIdDataItem *pItem=NULL;
	char *pOffset;
	u8 cycle=0,ItemIndex;
	//--------�����������--------
	pOffset=pIndata;
	while(pOffset < pEnd)
	{
		if(*pOffset == ':')
			cycle++;
		pOffset++;
	}
	if(cycle<1) return NULL;
	//--------�����Ӧ�ռ�--------
	pIdData=(sIdDataTable*)malloc(sizeof(sIdDataTable)+(sizeof(sIdDataItem)*cycle));
	pIdData->Total = cycle;
	//--------��¼����--------
	cycle=0;
	ItemIndex=0;
	while(pIndata < pEnd)
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
				*pIndata='\0';	//���ӽ�������
				cycle++; // 3-> :
			}
			else if(cycle==4)	// 4->Data Strat
			{
				cycle++;		//5 Strat Data
			}
			else if(cycle==5) // 3-> Data NULL
			{
				pItem->pData=pIndata;
				cycle++;  // 6-> End IDEnd
			}
			//-----------------------------
			if(cycle==6) // 6-> End IDEnd
			{
				*pIndata='\0';	//���ӽ�������
				cycle++;	// 7-> Next
			}
		}
		else if(*pIndata == ':')
		{
			if(cycle==3) 
				cycle++; // 4-> Data:
		}
		else if(*pIndata == '{')
		{
			if(cycle==4) 
			{
				int cont=1;
				pIndata++;
				pOffset=pIndata;
				while(pOffset < pEnd)
				{
					if(*pOffset == '{')
						cont++;
					else if(*pOffset == '}')
						cont--;
					if(cont==0) break;
				}
				if(cont==0){
					pItem->pData=Conv_JSON_GetMsg(pIndata,pOffset);
					pItem->dType=ITEM_STRUCT;
					pIndata=pOffset;
					while(pIndata < pEnd)
					{
						if((u8)*pIndata > ' ')
							break;
						pIndata++;
					}
				}
				cycle=7;		//5 End ,
			}
		}
		else if(*pIndata == ',')
		{
			if(cycle==7)
			{
				*pIndata='\0';	
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
			else if(cycle==4)	// 3-> Data Int
			{
				pItem->pData=pIndata;
				pItem->dType=ITEM_NULL;
				cycle=7;		//5 End ,
			}
			else if(cycle==5) // 3-> Data Str
			{
				pItem->pData=pIndata;
				pItem->dType=ITEM_STRING;
				cycle++;	// 6-> End Data
			}
		}
		pIndata++;
	}
	return pIdData;
}
*/

//=======================����pID�ַ�������С������=================================================
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
			{//С������
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
			TRACE_Str(pMd5Data);
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
	//------��λ���ҵ��ڵ�--------
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

//===���JSON������{"abb":"cdd","struct":{"abb":"cdd"}.....}===============
//--ע: pIndata������ROM�ռ䣬�������޸�pIndata�еĲ���,
//--    �������ҪConv_JSON_free�ͷſռ�
dfJsonTable* Conv_JSON_GetMsg(char *pIndata,char* pEnd)
{
	dfJsonTable *pIdData;
	dfJsonItem *pItem=NULL;
	u16 		colonCount,parenCount;
	u16			ItemIndex,cycle;
	//------------�ҵ����-----------------------
	parenCount=0;
	while(pIndata < pEnd)
	{
		if(*pIndata++ == '{') 
		{
			parenCount++;
			break;
		}
	}
	if(parenCount!=1) return NULL;
	//------------�ҵ��յ�-----------------------
	colonCount=0;
	{
		char *pE=pEnd;
		pEnd=pIndata;
		while(pEnd < pE)
		{
			if(*pEnd == '{')
				parenCount++;
			else if(*pEnd == '}')
			{
				if(--parenCount == 0) break;
			}
			else if(*pEnd == ':')
			{
				if(parenCount == 1)	//-�����һ���������-
					colonCount++;
			}
			pEnd++;
		}
	}
	if(parenCount)
	{
		TRACE("JSON_GetMsg ERR The {} number does not match[%d]\r\n",parenCount);
		return NULL;
	}
	if(colonCount<1)
	{
		TRACE("GetMsg  The : number Err[%d]\r\n",colonCount);
		return NULL;
	}
	*pEnd = '\0';
	//-----------�����Ӧ�ռ�----------------------
	pIdData=(dfJsonTable*)malloc(sizeof(dfJsonTable)+(sizeof(dfJsonItem)*colonCount)); //+1 = +'\0';
	pIdData->pNext= NULL;
	pIdData->sLen = pEnd-pIndata;
	cycle=0;
	ItemIndex=0;
	while(pIndata < pEnd)
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
				*pIndata='\0';	//���ӽ�������
				cycle++; // 3-> :
			}
			else if(cycle==4)	// 4->Data Strat
			{
				cycle++;		//5 Strat Data
			}
			else if(cycle==5)
			{//Ϊ5ʱ������""
				pItem->dType= ITEM_STRING;
				pItem->vaNum= 0;
				pItem->pValue=pIndata;
				*pIndata='\0';	//���ӽ�������
				cycle=7;	// 7-> Next
			}
			else if(cycle==6) // 6-> End IDEnd
			{
				*pIndata='\0';	//���ӽ�������
				cycle=7;	// 7-> Next
			}
		}
		else if(*pIndata == '[')
		{
			char *pKuoEnd;
			u16 dkjs,dkNum;
			pKuoEnd = ++pIndata;
			parenCount=1;
			dkjs=0;dkNum=0;
			while(pKuoEnd < pEnd)
			{
				if(*pKuoEnd == '[')
					parenCount++;
				else if(*pKuoEnd == ']')
				{
					parenCount--;
					if(parenCount == 0) break;
				}
				else if(*pKuoEnd == '{')
					dkjs++;
				else if(*pKuoEnd == '}')
				{
					dkjs--;
					if(dkjs == 0)
						dkNum++;
				}				
				pKuoEnd++;
			}
			if(parenCount==0 && dkNum > 0)
			{
				dfJsonTable *pNext=NULL;
				char *pS,*pE;
				for(dkjs=0;dkjs<dkNum;dkjs++)
				{
					pS = NULL;
					parenCount=0;
					while(pIndata < pKuoEnd)
					{
						if(*pIndata == '{')
						{
							if(++parenCount == 1)
								pS = pIndata;
						}
						else if(*pIndata == '}')
						{
							if(--parenCount == 0) break;
						}
						pIndata++;
					}
					pE = ++pIndata;
					if(pS)
					{
						if(pNext==NULL)
						{
							pNext=Conv_JSON_GetMsg(pS,pE);
							pItem->pValue=pNext;
						}
						else 
						{
							pNext->pNext=Conv_JSON_GetMsg(pS,pE);
							pNext=pNext->pNext;
						}
					}
				}
				pItem->vaNum= dkNum;
				pItem->dType= ITEM_STRUCT;
			}
			else
			{
				pItem->dType= ITEM_STRING;
				pItem->pValue=pIndata;
				*pKuoEnd = '\0';
			}
			pIndata=pKuoEnd;
			pIndata++;
			cycle=0;  //0 strar
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
			if(cycle==4 || cycle==5)	//cycle==4 Ϊ:{} ģʽ   , cycle==5 Ϊ:"{}" ģʽ
			{
				char *p;
				p=pIndata;
				p++; 
				parenCount=1;
				colonCount=0;
				while(p < pEnd)
				{
					if(*p == '{')
						parenCount++;
					else if(*p == '}')
					{
						if(--parenCount == 0) break;
					}
					else if(*p == ':')
						colonCount++;
					p++;
				}
				p++;
				pItem->vaNum= 1;
				if(parenCount==0)
				{
					if(colonCount>0)
					{
						pItem->dType= ITEM_STRUCT;
						pItem->pValue=Conv_JSON_GetMsg(pIndata,p);
					}
					else
					{
						pItem->dType= ITEM_NULL;
						pItem->pValue=pIndata;
						*p = '\0';
					}
				}
				else
				{
					TRACE("JSON_GetMsg Key[%s],Get Value ERR \r\n",pItem->pkey);
					free(pIdData);
					return NULL;
				}
				pIndata=p;
				if(cycle==5)
					pIndata++;
				cycle=0;  //0 strar
			}
		}
		else
		{
			if(cycle==1)	// 1-> IDStar
			{
				pItem->pkey=pIndata;
				cycle++;	// 2-> End IDStar
			}
			else if(cycle==4)	// 3-> Data Int 
			{
				if(*pIndata > ' ')	//���˿ո���з���
				{
					pItem->dType= ITEM_INT;
					pItem->pValue=pIndata;
					cycle=7;//5 End ,
				}
			}
			else if(cycle==5) // 3-> Data Str
			{
				pItem->dType= ITEM_STRING;
				pItem->pValue=pIndata;
				cycle++;	// 6-> End Data
			}
		}
		pIndata++;
	}
	pIdData->Total = ItemIndex;
	return pIdData;
}

/*
===����pKey ֧�ֶ༶����ʣ���'/'����,֧���������"[i]",i��ʾ�±꣬�� "abc/list[2]/hij"==========
ע: ITEM_STRUCT,����:pTypeΪ��ʱ���᷵��ָ��.
�緵��ָ��ΪITEM_STRUCT���Ϳɵ�(dfJsonTable*)����������Conv_GetJsonValue������һ��
*/
char* Conv_GetJsonValue(dfJsonTable *pStart,char* pKey,u8 *pType)
{
	char *src1,*src2;
	u16 i,Max;
	if(pStart == NULL)
	{
		TRACE("Conv GetJsonStr[%s] pStart Err\r\n",pKey);
		return NULL;
	}
	Max=pStart->Total;
	for(i=0;i<Max;i++)
	{
		src1=pKey;
		src2=pStart->Item[i].pkey;
		while(*src2)
		{
			if(*src1 != *src2)
				break;
			src1++; src2++;
		}
		
		if(*src2 == '\0')
		{
			if(*src1 == '\0')
			{
				if(pType) 
				{
					*pType= pStart->Item[i].dType;
				}
				else if(pStart->Item[i].dType == ITEM_STRUCT)
				{
					TRACE("GetJsonStr[%s] dtype is[%d],pType is NULL,not return\r\n",pKey,pStart->Item[i].dType);
					return NULL;
				}
				return pStart->Item[i].pValue;
			}
			else if(*src1 == '/')	//����ڶ���
			{
				if(pStart->Item[i].dType == ITEM_STRUCT)
				{
					return Conv_GetJsonValue((dfJsonTable *)pStart->Item[i].pValue,++src1,pType);
				}
				TRACE("GetJsonStr pKey[%s] '/' warning\r\n",pKey);
				return pStart->Item[i].pValue;
			}
			else if(*src1 == '[')	//����ּ���
			{//"abc/efg/hij[3]"
				u16 index=0;
				src1 ++;
				while((*src1 >= '0') && (*src1 <= '9'))
				{
					index =index*10 + ((*src1)&0x0f);
					src1++;
				}
				if(*src1++ != ']')
				{
					TRACE("GetJsonStr[%s] Format error,not return\r\n",pKey);
					return NULL;
				}
				else
				{
					dfJsonTable *pArray=(dfJsonTable *)pStart->Item[i].pValue;
					while(index--) pArray = pArray->pNext;
					
					if(pArray)
					{
						if(*src1 == '/')
							return Conv_GetJsonValue(pArray,++src1,pType);
						else if(pType) 
						{
							*pType= pStart->Item[i].dType;
							return pArray;
						}
						return NULL;
					}
					return pArray;
				}
			}
		}
	}
	TRACE("GetJsonStr[%s] Nofind\r\n",pKey);
	return NULL;
}


void Conv_JSON_free(dfJsonTable *pTable)
{
	u16 i,max;
	if(pTable==NULL) return ;
	max=pTable->Total;
	for(i=0;i<max;i++)
	{
		if(pTable->Item[i].dType == ITEM_STRUCT)
		{
			dfJsonTable *pCurr,*pNext;
			pCurr=(dfJsonTable*)pTable->Item[i].pValue;
			while(pCurr)
			{
				pNext = pCurr->pNext;
				Conv_JSON_free(pCurr);
				pCurr=pNext;
			}
		}
		
	}
	free(pTable);
}
//==========================================================================================
void GetSysDateTime(char *pOutDateTime,const char *spFormat)
{
	SYSTEMTIME	systemTime;
	GetLocalTime(&systemTime);	
	API_sprintf(pOutDateTime,spFormat,
			systemTime.wYear,systemTime.wMonth,systemTime.wDay,
			systemTime.wHour,systemTime.wMinute,systemTime.wSecond); 

}

//---�����ʽ 2018 03 08 17 03 43---ÿ��Ԫ�ؼ������----------------
void SetSysDateTime(char *pInDateTime)
{
	SYSTEMTIME dtime,inTime;
	char sBuff[8];
	//2018 03 08 17 03 43
	API_memcpy(sBuff,pInDateTime,4); sBuff[4]='\0';
	inTime.wYear =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+5,2); sBuff[2]='\0';
	inTime.wMonth=API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+8,2); //sBuff[2]='\0';
	inTime.wDay =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+11,2); //sBuff[2]='\0';
	inTime.wHour =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+14,2); //sBuff[2]='\0';
	inTime.wMinute=API_atoi(sBuff);
	
	GetLocalTime(&dtime);
	if(dtime.wYear!=inTime.wYear || dtime.wMonth!=inTime.wMonth || dtime.wDay!=inTime.wDay \
		|| dtime.wHour!=inTime.wHour || dtime.wMinute!=inTime.wMinute)
	{
		API_memcpy(sBuff,pInDateTime+17,2); //sBuff[19]='\0';
		inTime.wSecond=API_atoi(sBuff); 
		inTime.wMilliseconds=0;
		SetLocalTime(&inTime); 
	}
}


void APP_GetRand(u8 *pOutRand,int RandLen)
{
	SYSTEMTIME  systemTime;
	GetLocalTime(&systemTime);	  
	srand_m(systemTime.wSecond);
	while(RandLen--) pOutRand[RandLen]=rand_m();
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

void* API_memcpy(void *dst, const void *src, int count)
{
	return memcpy_m(dst,src,count);
}

void* API_memset(void* dst, int value, int count)
{
	return memset_m(dst,value,count);
}
int API_memcmp(const void* src1, const void* src2, int count)
{
	return memcmp_m(src1, src2, count);
}

char* API_strcpy(char* dst, const char* src)
{
	return strcpy_m(dst,src);

}
int API_strlen(const char* src)
{
	return strlen_m(src);
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


