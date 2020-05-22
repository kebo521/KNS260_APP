#ifndef __KS_CRYPT__H
#define __KS_CRYPT__H
//----------------------------------------------------------------------------------------------------------------------
//
//	V1.0	2014/12/4 10:09:22	初始版本管理，修正函数名大小写。
//	V1.1 	2014/12/4 10:18:30	修改API_Hash,增加HASH_FLAG,用于处理大块的HASH计算
//  V1.2 	2014/12/4 11:00:30  增加HASH_RESULT_LEN定义，API_Hash要求强制输入
//  V1.3 	2014/12/5 09:39:51  规范注释说明
//
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------
//@随机数生产

	/**
	 * 加密函数返回定义
	 */
    enum CRYPT_RET
    { 
    	CRYPT_OK				=	 0,	//!< 成功
    	CRYPT_PAR_ERR			=    1, //!< 参数错误
    	CRYPT_NOT_SUPPORTED		=	 2, //!< 系统不支持
    	CRYPT_ERR		    	=	-1, //!< 错误
    	CRYPT_DEVICE_ERR		=   -2, //!< 硬件故障
    	CRYPT_NO_ACCESS			=   -3  //!< 权限不足
	};


    /**
     * 获取随机数
     * @param buf [out]		随机数输出缓存
     * @param len			需要生成的随机数长度
     * @return {@link RET_OK} 	 					成功
     * @return {@link RET_PERMISSION_DENIED} 		权限不足
     * @return {@link RET_API_PARAMETER_ERROR} 		函数参数错误
     * @return {@link RET_DEVICE_MALFUNCTION}		硬件故障（如果使用硬件产生随机数的话）
     * @return {@link RET_DEVICE_PARAMETER_ERROR}	硬件参数错误（如果使用硬件产生随机数的话）
     * @return {@link RET_FUNCTION_NOT_SUPPORT} 	功能不支持
     * @return {@link RET_SYSTEM_ERROR}				系统错误
     */
    int API_Rng(u8* buf, u32 len);

//----------------------------------------------------------------------------------------------------------------------
//@CRC校验
	/**
	 * CRC算法类型定义
	 */
	enum CRC_TYPE
	{
		CRC_4				=0x00,	//!< 生成多项式x4+x+1, 简记式3 		
		CRC_8				=0x01,  //!< 生成多项式x8+x5+x4+1, 简记式31
		CRC_12				=0x02,  //!< 生成多项式x12+x11+x3+x+1, 简记式5E
		CRC_16				=0x03,  //!< 生成多项式x16+x15+x2+1, 简记式8005
		CRC_CCITT			=0x04,	//!< 生成多项式x16+x12+x5+1, 简记式1021
		CRC_32				=0x05,  //!< 生成多项式x32+x26+x23+...+x2+x+1, 简记式04C11DB7
		CRC_32C				=0x06   //!< 生成多项式x32+x28+x27+...+x8+x6+1, 简记式1EDC6F41
	};
	/**
     * CRC校验
     * 
     * @param crc_iv   		如果是分段计算, 则此参数存放上次CRC计算的结果；当是分段计算的第一段或不分段结算时，填入0xFFFFFFFF
     * @param crctype	crc类型，参考{@link CRC_TYPE}
     * @param buf 			CRC计算源数据
     * @param len 			源数据长度
     * @param crc [out]		CRC计算结果
     * @return {@link RET_OK} 	 				成功
     * @return {@link RET_PERMISSION_DENIED} 	权限不足
     * @return {@link RET_API_PARAMETER_ERROR} 	函数参数错误
     * @return {@link RET_FUNCTION_NOT_SUPPORT} 功能不支持
     * @return {@link RET_SYSTEM_ERROR}			系统错误
     */
	int API_CalCrc(u32 crc_iv, u8 crctype, const u8* buf, u32 len, u32 * crc);
//----------------------------------------------------------------------------------------------------------------------
//@哈希计算

	/**
	 * HASH算法类型定义
	 */
    enum HASH_TYPE 
    {
        HASH_TYPE_SHA1      = 1,    //!< SHA1算法
        HASH_TYPE_SHA224    = 2,    //!< SHA224算法,目前不支持
        HASH_TYPE_SHA256    = 3,	//!< SHA256算法
        HASH_TYPE_SHA384    = 4,    //!< SHA384算法,目前不支持
        HASH_TYPE_SHA512    = 5,    //!< SHA512算法
        HASH_TYPE_MD2       = 11,   //!< MD2算法,目前不支持
        HASH_TYPE_MD4       = 12,   //!< MD4算法,目前不支持
        HASH_TYPE_MD5       = 13,   //!< MD5算法
        HASH_TYPE_SM3       = 21,   //!< SM3算法
    };

    /**
	 * HASH算法个类型长度定义
	 */
    enum HASH_RESULT_LEN
    {
		HASH_RESULT_LEN_SHA1 	= 20, //!< SHA1结果长度20byte
		HASH_RESULT_LEN_SHA224	= 32, //!< SHA224结果长度32byte
    	HASH_RESULT_LEN_SHA256	= 32, //!< SHA256结果长度32byte
		HASH_RESULT_LEN_SHA384	= 64, //!< SHA384结果长度64byte
		HASH_RESULT_LEN_SHA512	= 64, //!< SHA512结果长度64byte
		HASH_RESULT_LEN_MD2		= 16, //!< MD2结果长度16byte
		HASH_RESULT_LEN_MD4		= 16, //!< MD4结果长度16byte
    	HASH_RESULT_LEN_MD5		= 16, //!< MD5结果长度16byte
    	HASH_RESULT_LEN_SM3		= 20, //!< SM3结果长度20byte
    };

	/**
	 * HASH计算标记
	 */
    enum HASH_FLAG
    {
    	HASH_DIRECT			= 0,	//!< 直接计算HASH				input,inlen,output必须
    	HASH_INIT			= 1,	//!< 分块计算HASH 初始化,   	output必须
    	HASH_UPDATE			= 2,	//!< 分块计算HASH 更新数据, 	input,inlen,output必须
    	HASH_RESULT			= 3,	//!< 分块计算HASH 计算结果,  	input,inlen,output必须
    };

    /**
     * 哈希运算
     *
     * @param type      	{@link HASH_TYPE}
     * @param input     	输入数据
     * @param inlen     	输入数据长度
     * @param output  [out]	输出结果缓存
     * @param outsize		输出结果缓存大小
     * @param outlen [out]	输出结果长度
     * @param flag			{@link HASH_FLAG}
     * @return {@link RET_OK} 	 					成功
     * @return {@link RET_PERMISSION_DENIED} 		权限不足
     * @return {@link RET_API_PARAMETER_ERROR} 		函数参数错误
     * @return {@link RET_FUNCTION_NOT_SUPPORT} 	功能不支持
     * @return {@link RET_SYSTEM_ERROR}				系统错误
     */
    int API_Hash(int type, u8* input, int inlen, u8* output, int flag);

	int API_Hmac_sha256(u8* key,u16 keylen, u8* input, int inlen, u8* output);
//----------------------------------------------------------------------------------------------------------------------
//@加解密计算


	
    #define MAX_RSA_MODULUS_BITS    2048 								//!< RSA最大支持位数
    #define MAX_RSA_MODULUS_LEN     ((MAX_RSA_MODULUS_BITS + 7) / 8)	//!< RSA公钥模最大长度
    #define MAX_RSA_PRIME_BITS      ((MAX_RSA_MODULUS_BITS + 1) / 2)	//!< RSA私钥指数最大支持位数
    #define MAX_RSA_PRIME_LEN       ((MAX_RSA_PRIME_BITS   + 7) / 8)	//!< RSA私钥指数最大长度
    #define MAX_RSA_EXPONENT_LEN    4									//!< RSA公钥指数最大长度

    /**
     * RSA公钥
     */
    typedef struct 
    {
		u32  	length;                                 //!< length in bytes of modulus
		u8 		modulus[MAX_RSA_MODULUS_LEN];           //!< modulus N
		u8 		exponent[MAX_RSA_EXPONENT_LEN];         //!< public exponent E 不足位前补0
    } RSA_PUBKEY;

    /**
     * RSA私钥
     */
    typedef struct 
    {
		u32  	length;                                 //!< length in bytes of modulus
		u8 		modulus[MAX_RSA_MODULUS_LEN];           //!< modulus N
		u8 		publicExponent[MAX_RSA_EXPONENT_LEN];   //!< public exponent E 不足位前补0
		u8 		exponent[MAX_RSA_MODULUS_LEN];          //!< private exponent D 不足位前补0
		u8 		prime[2][MAX_RSA_PRIME_LEN];            //!< prime factors P,Q
		u8 		primeExponent[2][MAX_RSA_PRIME_LEN];    //!< exponents for CRT
		u8 		coefficient[MAX_RSA_PRIME_LEN];         //!< CRT coefficient
    } RSA_PRIVKEY;

    /**
     * SM2公钥
     */
    typedef struct 
    {
        u8 xQ[32]; //!< 椭圆曲线上一点x
        u8 yQ[32]; //!< 椭圆曲线上一点y
    } SM2_PUBKEY;

    /**
     * SM2私钥
     */
    typedef struct 
    {
        u8 xQ[32]; //!< 椭圆曲线上一点x
        u8 yQ[32]; //!< 椭圆曲线上一点x
        u8  d[32]; //!< 随机数k
    } SM2_PRIVKEY;

//===========================================================================================================
	extern void Des_B1Dec(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B1Enc(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B2Dec(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B2Enc(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B3Dec(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B3Enc(u8 *Buff ,u8 *key ,u8 key_number);
	//=====国密对称加密算法====================
	//----Buff 输入输出数据指针
	//----Key 密钥指针
	//----key_number 数据密钥倍长(16倍)
	extern void SM4_ENC(u8 *Buff ,u8 *key ,u8 key_number);
	//=====国密对称解密算法=====================
	//----Buff 输入输出数据指针
	//----Key 密钥指针
	//----key_number 数据密钥倍长(16倍)
	extern void SM4_DEC(u8 *Buff ,u8 *key ,u8 key_number);


//----------------------------------------------------------------------------------------------------------------------

	extern void md5(unsigned char *input, u32 ilen, unsigned char* pOutput);	//临时用

	extern int APP_base64_encode(unsigned char *dst, size_t dlen, size_t *olen,const unsigned char *src, size_t slen);

	extern int APP_base64_decode(unsigned char *dst, size_t dlen, size_t *olen,const unsigned char *src, size_t slen);


#endif

