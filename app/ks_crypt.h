#ifndef __KS_CRYPT__H
#define __KS_CRYPT__H
//----------------------------------------------------------------------------------------------------------------------
//
//	V1.0	2014/12/4 10:09:22	��ʼ�汾����������������Сд��
//	V1.1 	2014/12/4 10:18:30	�޸�API_Hash,����HASH_FLAG,���ڴ������HASH����
//  V1.2 	2014/12/4 11:00:30  ����HASH_RESULT_LEN���壬API_HashҪ��ǿ������
//  V1.3 	2014/12/5 09:39:51  �淶ע��˵��
//
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------
//@���������

	/**
	 * ���ܺ������ض���
	 */
    enum CRYPT_RET
    { 
    	CRYPT_OK				=	 0,	//!< �ɹ�
    	CRYPT_PAR_ERR			=    1, //!< ��������
    	CRYPT_NOT_SUPPORTED		=	 2, //!< ϵͳ��֧��
    	CRYPT_ERR		    	=	-1, //!< ����
    	CRYPT_DEVICE_ERR		=   -2, //!< Ӳ������
    	CRYPT_NO_ACCESS			=   -3  //!< Ȩ�޲���
	};


    /**
     * ��ȡ�����
     * @param buf [out]		������������
     * @param len			��Ҫ���ɵ����������
     * @return {@link RET_OK} 	 					�ɹ�
     * @return {@link RET_PERMISSION_DENIED} 		Ȩ�޲���
     * @return {@link RET_API_PARAMETER_ERROR} 		������������
     * @return {@link RET_DEVICE_MALFUNCTION}		Ӳ�����ϣ����ʹ��Ӳ������������Ļ���
     * @return {@link RET_DEVICE_PARAMETER_ERROR}	Ӳ�������������ʹ��Ӳ������������Ļ���
     * @return {@link RET_FUNCTION_NOT_SUPPORT} 	���ܲ�֧��
     * @return {@link RET_SYSTEM_ERROR}				ϵͳ����
     */
    int API_Rng(u8* buf, u32 len);

//----------------------------------------------------------------------------------------------------------------------
//@CRCУ��
	/**
	 * CRC�㷨���Ͷ���
	 */
	enum CRC_TYPE
	{
		CRC_4				=0x00,	//!< ���ɶ���ʽx4+x+1, ���ʽ3 		
		CRC_8				=0x01,  //!< ���ɶ���ʽx8+x5+x4+1, ���ʽ31
		CRC_12				=0x02,  //!< ���ɶ���ʽx12+x11+x3+x+1, ���ʽ5E
		CRC_16				=0x03,  //!< ���ɶ���ʽx16+x15+x2+1, ���ʽ8005
		CRC_CCITT			=0x04,	//!< ���ɶ���ʽx16+x12+x5+1, ���ʽ1021
		CRC_32				=0x05,  //!< ���ɶ���ʽx32+x26+x23+...+x2+x+1, ���ʽ04C11DB7
		CRC_32C				=0x06   //!< ���ɶ���ʽx32+x28+x27+...+x8+x6+1, ���ʽ1EDC6F41
	};
	/**
     * CRCУ��
     * 
     * @param crc_iv   		����Ƿֶμ���, ��˲�������ϴ�CRC����Ľ�������Ƿֶμ���ĵ�һ�λ򲻷ֶν���ʱ������0xFFFFFFFF
     * @param crctype	crc���ͣ��ο�{@link CRC_TYPE}
     * @param buf 			CRC����Դ����
     * @param len 			Դ���ݳ���
     * @param crc [out]		CRC������
     * @return {@link RET_OK} 	 				�ɹ�
     * @return {@link RET_PERMISSION_DENIED} 	Ȩ�޲���
     * @return {@link RET_API_PARAMETER_ERROR} 	������������
     * @return {@link RET_FUNCTION_NOT_SUPPORT} ���ܲ�֧��
     * @return {@link RET_SYSTEM_ERROR}			ϵͳ����
     */
	int API_CalCrc(u32 crc_iv, u8 crctype, const u8* buf, u32 len, u32 * crc);
//----------------------------------------------------------------------------------------------------------------------
//@��ϣ����

	/**
	 * HASH�㷨���Ͷ���
	 */
    enum HASH_TYPE 
    {
        HASH_TYPE_SHA1      = 1,    //!< SHA1�㷨
        HASH_TYPE_SHA224    = 2,    //!< SHA224�㷨,Ŀǰ��֧��
        HASH_TYPE_SHA256    = 3,	//!< SHA256�㷨
        HASH_TYPE_SHA384    = 4,    //!< SHA384�㷨,Ŀǰ��֧��
        HASH_TYPE_SHA512    = 5,    //!< SHA512�㷨
        HASH_TYPE_MD2       = 11,   //!< MD2�㷨,Ŀǰ��֧��
        HASH_TYPE_MD4       = 12,   //!< MD4�㷨,Ŀǰ��֧��
        HASH_TYPE_MD5       = 13,   //!< MD5�㷨
        HASH_TYPE_SM3       = 21,   //!< SM3�㷨
    };

    /**
	 * HASH�㷨�����ͳ��ȶ���
	 */
    enum HASH_RESULT_LEN
    {
		HASH_RESULT_LEN_SHA1 	= 20, //!< SHA1�������20byte
		HASH_RESULT_LEN_SHA224	= 32, //!< SHA224�������32byte
    	HASH_RESULT_LEN_SHA256	= 32, //!< SHA256�������32byte
		HASH_RESULT_LEN_SHA384	= 64, //!< SHA384�������64byte
		HASH_RESULT_LEN_SHA512	= 64, //!< SHA512�������64byte
		HASH_RESULT_LEN_MD2		= 16, //!< MD2�������16byte
		HASH_RESULT_LEN_MD4		= 16, //!< MD4�������16byte
    	HASH_RESULT_LEN_MD5		= 16, //!< MD5�������16byte
    	HASH_RESULT_LEN_SM3		= 20, //!< SM3�������20byte
    };

	/**
	 * HASH������
	 */
    enum HASH_FLAG
    {
    	HASH_DIRECT			= 0,	//!< ֱ�Ӽ���HASH				input,inlen,output����
    	HASH_INIT			= 1,	//!< �ֿ����HASH ��ʼ��,   	output����
    	HASH_UPDATE			= 2,	//!< �ֿ����HASH ��������, 	input,inlen,output����
    	HASH_RESULT			= 3,	//!< �ֿ����HASH ������,  	input,inlen,output����
    };

    /**
     * ��ϣ����
     *
     * @param type      	{@link HASH_TYPE}
     * @param input     	��������
     * @param inlen     	�������ݳ���
     * @param output  [out]	����������
     * @param outsize		�����������С
     * @param outlen [out]	����������
     * @param flag			{@link HASH_FLAG}
     * @return {@link RET_OK} 	 					�ɹ�
     * @return {@link RET_PERMISSION_DENIED} 		Ȩ�޲���
     * @return {@link RET_API_PARAMETER_ERROR} 		������������
     * @return {@link RET_FUNCTION_NOT_SUPPORT} 	���ܲ�֧��
     * @return {@link RET_SYSTEM_ERROR}				ϵͳ����
     */
    int API_Hash(int type, u8* input, int inlen, u8* output, int flag);

	int API_Hmac_sha256(u8* key,u16 keylen, u8* input, int inlen, u8* output);
//----------------------------------------------------------------------------------------------------------------------
//@�ӽ��ܼ���


	
    #define MAX_RSA_MODULUS_BITS    2048 								//!< RSA���֧��λ��
    #define MAX_RSA_MODULUS_LEN     ((MAX_RSA_MODULUS_BITS + 7) / 8)	//!< RSA��Կģ��󳤶�
    #define MAX_RSA_PRIME_BITS      ((MAX_RSA_MODULUS_BITS + 1) / 2)	//!< RSA˽Կָ�����֧��λ��
    #define MAX_RSA_PRIME_LEN       ((MAX_RSA_PRIME_BITS   + 7) / 8)	//!< RSA˽Կָ����󳤶�
    #define MAX_RSA_EXPONENT_LEN    4									//!< RSA��Կָ����󳤶�

    /**
     * RSA��Կ
     */
    typedef struct 
    {
		u32  	length;                                 //!< length in bytes of modulus
		u8 		modulus[MAX_RSA_MODULUS_LEN];           //!< modulus N
		u8 		exponent[MAX_RSA_EXPONENT_LEN];         //!< public exponent E ����λǰ��0
    } RSA_PUBKEY;

    /**
     * RSA˽Կ
     */
    typedef struct 
    {
		u32  	length;                                 //!< length in bytes of modulus
		u8 		modulus[MAX_RSA_MODULUS_LEN];           //!< modulus N
		u8 		publicExponent[MAX_RSA_EXPONENT_LEN];   //!< public exponent E ����λǰ��0
		u8 		exponent[MAX_RSA_MODULUS_LEN];          //!< private exponent D ����λǰ��0
		u8 		prime[2][MAX_RSA_PRIME_LEN];            //!< prime factors P,Q
		u8 		primeExponent[2][MAX_RSA_PRIME_LEN];    //!< exponents for CRT
		u8 		coefficient[MAX_RSA_PRIME_LEN];         //!< CRT coefficient
    } RSA_PRIVKEY;

    /**
     * SM2��Կ
     */
    typedef struct 
    {
        u8 xQ[32]; //!< ��Բ������һ��x
        u8 yQ[32]; //!< ��Բ������һ��y
    } SM2_PUBKEY;

    /**
     * SM2˽Կ
     */
    typedef struct 
    {
        u8 xQ[32]; //!< ��Բ������һ��x
        u8 yQ[32]; //!< ��Բ������һ��x
        u8  d[32]; //!< �����k
    } SM2_PRIVKEY;

//===========================================================================================================
	extern void Des_B1Dec(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B1Enc(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B2Dec(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B2Enc(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B3Dec(u8 *Buff ,u8 *key ,u8 key_number);
	extern void Des_B3Enc(u8 *Buff ,u8 *key ,u8 key_number);
	//=====���ܶԳƼ����㷨====================
	//----Buff �����������ָ��
	//----Key ��Կָ��
	//----key_number ������Կ����(16��)
	extern void SM4_ENC(u8 *Buff ,u8 *key ,u8 key_number);
	//=====���ܶԳƽ����㷨=====================
	//----Buff �����������ָ��
	//----Key ��Կָ��
	//----key_number ������Կ����(16��)
	extern void SM4_DEC(u8 *Buff ,u8 *key ,u8 key_number);


//----------------------------------------------------------------------------------------------------------------------

	extern void md5(unsigned char *input, u32 ilen, unsigned char* pOutput);	//��ʱ��

	extern int APP_base64_encode(unsigned char *dst, size_t dlen, size_t *olen,const unsigned char *src, size_t slen);

	extern int APP_base64_decode(unsigned char *dst, size_t dlen, size_t *olen,const unsigned char *src, size_t slen);


#endif

