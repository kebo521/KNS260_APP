#include "communal.h"


void md5(unsigned char *input, u32 ilen, unsigned char* pOutput)
{
	pTlsFuntion->hash->md(MBEDTLS_MD_MD5,input,ilen,pOutput);
}

//===================================================================================================
int API_Hash(int type, u8* input, int inlen, u8* output, int flag)
{
	mbedtls_md_type_t md_type_t;
	if(pTlsFuntion==NULL)
		return CRYPT_ERR;
	
	if(type == HASH_TYPE_MD2)
		md_type_t=MBEDTLS_MD_MD2;
	else if(type == HASH_TYPE_MD4)
		md_type_t=MBEDTLS_MD_MD4;
	else if(type == HASH_TYPE_MD5)
		md_type_t=MBEDTLS_MD_MD5;
	else if(type == HASH_TYPE_SHA1)
		md_type_t=MBEDTLS_MD_SHA1;
	else if(type == HASH_TYPE_SHA224)
		md_type_t=MBEDTLS_MD_SHA224;
	else if(type == HASH_TYPE_SHA256)
		md_type_t=MBEDTLS_MD_SHA256;
	else if(type == HASH_TYPE_SHA384)
		md_type_t=MBEDTLS_MD_SHA384;
	else if(type == HASH_TYPE_SHA512)
		md_type_t=MBEDTLS_MD_SHA512;
	else if(type == HASH_TYPE_SM3)
		md_type_t=GUO_TLS_MD_SM3;
	else 
		return CRYPT_NOT_SUPPORTED;

	if(flag == HASH_DIRECT)
	{
		return	pTlsFuntion->hash->md(md_type_t,input,inlen,output);
	}
	else 
	{	
		static mbedtls_md_context_t ctx;
		if(flag == HASH_INIT)
		{
			return	pTlsFuntion->hash->md_starts(&ctx,md_type_t);
		}
		else if(flag == HASH_UPDATE)
		{
			return	pTlsFuntion->hash->md_update(&ctx,input,inlen);
		}
		else if(flag == HASH_RESULT)
		{
			return	pTlsFuntion->hash->md_finish(&ctx,output,NULL);
		}
	}
	return CRYPT_NOT_SUPPORTED;
}



int API_Hmac_sha256(u8* key,u16 keylen, u8* input, int inlen, u8* output)
{
	return pTlsFuntion->hash->md_hmac(MBEDTLS_MD_SHA256,key,keylen,input,inlen,output);
}

int API_Crypt(int type, const u8* key, int keylen, const u8* iv, const u8* input, int inlen, u8* output, int * outlen, int mode)
{
	return pTlsFuntion->cry->Crypt(type,key,keylen,iv,input,inlen,output,outlen,mode);
}


void Des_B1Dec(u8 *Buff ,u8 *key ,u8 key_number)
{
	int outlen=key_number*8;
	API_Crypt(CRYPT_TYPE_DES,key,8,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_DECRYPT|CRYPT_MODE_ECB);
}
void Des_B1Enc(u8 *Buff ,u8 *key ,u8 key_number)
{
	int outlen=key_number*8;
	API_Crypt(CRYPT_TYPE_DES,key,8,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_ENCRYPT|CRYPT_MODE_ECB);
}

void Des_B2Dec(u8 *Buff ,u8 *key ,u8 key_number)
{
	int outlen=key_number*8;
	API_Crypt(CRYPT_TYPE_DES,key,16,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_DECRYPT|CRYPT_MODE_ECB);
}
void Des_B2Enc(u8 *Buff ,u8 *key ,u8 key_number)
{
	int outlen=key_number*8;
	API_Crypt(CRYPT_TYPE_DES,key,16,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_ENCRYPT|CRYPT_MODE_ECB);
}

void Des_B3Dec(u8 *Buff ,u8 *key ,u8 key_number)
{
	int outlen=key_number*8;
	API_Crypt(CRYPT_TYPE_DES,key,24,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_DECRYPT|CRYPT_MODE_ECB);
}

void Des_B3Enc(u8 *Buff ,u8 *key ,u8 key_number)
{	
	int outlen=key_number*8;
	API_Crypt(CRYPT_TYPE_DES,key,24,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_ENCRYPT|CRYPT_MODE_ECB);
}

//=====国密对称加密算法====================
//----Buff 输入输出数据指针
//----Key 密钥指针
//----key_number 数据密钥倍长(16倍)
void SM4_ENC(u8 *Buff ,u8 *key ,u8 key_number)
{
	int outlen=key_number*16;
	API_Crypt(CRYPT_TYPE_SM4,key,16,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_ENCRYPT|CRYPT_MODE_ECB);
}

//=====国密对称解密算法=====================
//----Buff 输入输出数据指针
//----Key 密钥指针
//----key_number 数据密钥倍长(16倍)
void SM4_DEC(u8 *Buff ,u8 *key ,u8 key_number)
{
	int outlen=key_number*16;
	API_Crypt(CRYPT_TYPE_SM4,key,16,NULL,Buff,outlen,Buff,&outlen,CRYPT_MODE_DECRYPT|CRYPT_MODE_ECB);
}



int APP_base64_encode(unsigned char *dst, size_t dlen, size_t *olen,const unsigned char *src, size_t slen)
{
	return pTlsFuntion->cry->base64_encode(dst,dlen,olen,src,slen);
}

int APP_base64_decode(unsigned char *dst, size_t dlen, size_t *olen,const unsigned char *src, size_t slen)
{
	return pTlsFuntion->cry->base64_decode(dst,dlen,olen,src,slen);
}


