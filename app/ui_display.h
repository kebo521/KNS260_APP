#ifndef _UI_DISPLAY_
#define _UI_DISPLAY_


#define FONT_SIZE    			(24)    
#define HZ_INDEX(hz)    		((hz[0] - 0xa1) * 94 + (hz[1] - 0xa1))
#define DOTS_BYTES    			((FONT_SIZE * FONT_SIZE / 8))

#ifdef DISPLAY_HORIZONTAL_SCREEN			//��������
//---------ȫ������----------------------
#define SCREEN_WIDTH		(320) 
#define SCREEN_HEIGT		(240) 
#define EFFECTIVE_X			(0) 
#define EFFECTIVE_Y			(24)
//---------Ӧ��ʹ�õ�������-------------------
#define SCREEN_APP_X		0 
#define SCREEN_APP_Y		0
#define SCREEN_APP_W		(SCREEN_WIDTH) 
#define SCREEN_APP_H		(SCREEN_HEIGT-EFFECTIVE_Y) 
//-------ͼƬ���������������ʾ-------------------------------
#define UI_MAP_TITLE_X		SCREEN_APP_X
#define UI_MAP_TITLE_Y		SCREEN_APP_Y
#define UI_MAP_TITLE_W		SCREEN_APP_W 
#define UI_MAP_TITLE_H		40 

#define UI_MAP_CONT_X		SCREEN_APP_X
#define UI_MAP_CONT_Y		(SCREEN_APP_Y+UI_MAP_TITLE_H)
#define UI_MAP_CONT_W		SCREEN_APP_W 
#define UI_MAP_CONT_H		(SCREEN_APP_H-UI_MAP_TITLE_H)
//----------ϵͳ������������---------------------------------
#define UI_TITLE_X			SCREEN_APP_X
#define UI_TITLE_Y			SCREEN_APP_Y
#define UI_TITLE_W			SCREEN_APP_W 
#define UI_TITLE_H			36 
#define UI_TITLE_COLOUR		RGB565(24,120,200) 
#define FONT_TITLE_COLOUR	RGB565_WITHE 

#define UI_CONT_X			SCREEN_APP_X
#define UI_CONT_Y			(SCREEN_APP_Y+UI_TITLE_H)
#define UI_CONT_W			SCREEN_APP_W 
#define UI_CONT_H			(SCREEN_APP_H-UI_TITLE_H)
#define UI_CONT_COLOUR		RGB565(240,244,248)
#define FONT_CONT_COLOUR	RGB565_BLACK 
//----------���Ʋ˵�����----------------------
#define SCREEN_MENU_X		(SCREEN_APP_X) 
#define SCREEN_MENU_Y		(SCREEN_APP_Y)
#define SCREEN_MENU_W		(SCREEN_APP_W) 
#define SCREEN_MENU_H		(SCREEN_APP_H) 
#define MENU_TITLE_H		36

#define MENU_TIEM_ALL_Y		(SCREEN_MENU_Y+MENU_TITLE_H)
#define MENU_TIEM_ALL_H		(SCREEN_APP_H-MENU_TITLE_H)
#define MENU_TIEM_H			30
#define MENU_TIEM_MAX		((SCREEN_APP_H-MENU_TITLE_H)/MENU_TIEM_H)			//���˵���
//------------�˵�ɫ�ʶ���-----------------
#define RGB565_TITLE_ICON	RGB565(0,127,255)   //0x03ff
#define RGB565_TITLE_FONT	RGB565_WITHE
#define RGB565_TIEM_ICON	UI_CONT_COLOUR
#define RGB565_TIEM_FONT	RGB565(48,48,48)	//0x3186
#define RGB565_SELE_ICON	RGB565(224,224,224)	//0xe71c
#define RGB565_SELE_FONT	RGB565(0,127,255)	//0x03ff

//============������Ϣ����������ʾ============
#define UI_TRADE_MSG_X		(SCREEN_APP_X+FONT_SIZE)
#define UI_TRADE_MSG_Y		(SCREEN_APP_Y+FONT_SIZE/2)
#define UI_TRADE_MSG_W		(SCREEN_APP_W-FONT_SIZE*2) 
#define UI_TRADE_MSG_H		(SCREEN_APP_H-FONT_SIZE)

//============����ʧ������������ʾ============
#define UI_TRADE_FA_MSG_X		(SCREEN_APP_X+FONT_SIZE/2)
#define UI_TRADE_FA_MSG_Y		(SCREEN_APP_Y+160)
#define UI_TRADE_FA_MSG_W		(SCREEN_APP_W-FONT_SIZE) 
#define UI_TRADE_FA_MSG_H		(FONT_SIZE)

//============ɨ������������ʾ============
#define UI_SCAN_TEXT_Y			(UI_CONT_Y+142)
#define UI_SCAN_MONEY_Y			(UI_CONT_Y+82)
//============ͼƬ�ϵ�����������ʾ============
#define UI_NOSIGNEL_TEXT_Y		(182)
#define UI_WAITFOR_TEXT_Y		(124)

//============���׶�ά��������ʾ============
#define UI_QR_CODE_X			(SCREEN_APP_X+85)
#define UI_QR_CODE_Y			(SCREEN_APP_Y+42)
#define UI_QR_CODE_W			(150) 
#define UI_QR_CODE_H			(150)

#define UI_QR_MONEY_X			(SCREEN_APP_X+70)
#define UI_QR_MONEY_Y			(SCREEN_APP_Y+10)
#define UI_QR_MONEY_W			(SCREEN_APP_W-70*2)
#define UI_QR_MONEY_H			(FONT_SIZE)

//============������ϸ����������ʾ============
#define UI_ENQU_MONEY_X			(SCREEN_APP_X+FONT_SIZE/2)
#define UI_ENQU_MONEY_Y			(SCREEN_APP_Y+16)
#define UI_ENQU_MONEY_W			(SCREEN_APP_W-FONT_SIZE) 
#define UI_ENQU_MONEY_H			(FONT_SIZE)
#define UI_ENQU_SPACING_H		(8)

//============�����˿�����������ʾ============
#define UI_EDIT_MERCH_SN_X			(UI_CONT_X+48)
#define UI_EDIT_MERCH_SN_Y			(UI_CONT_Y+64)
#define UI_EDIT_MERCH_SN_W			(UI_CONT_W-48*2) 
#define UI_EDIT_MERCH_SN_H			(FONT_SIZE*2)

//============����༭����===============
#define UI_EDIT_bMONEY_X			(UI_CONT_X+69)
#define UI_EDIT_bMONEY_Y			(UI_CONT_Y+64)
#define UI_EDIT_bMONEY_W			(UI_CONT_W-69*2)
#define UI_EDIT_bMONEY_H			36 
//------ͼƬ�����Ŵ�С����---------------
#define UI_EDIT_bMONEY_fW			14 
#define UI_EDIT_bMONEY_fH			19 
//------ͼƬ���С����---------------
#define UI_EDIT_bMONEY_dW			14 
#define UI_EDIT_bMONEY_dH			30 
//------ͼƬ���ִ�С����---------------
#define UI_EDIT_bMONEY_sW			22 
#define UI_EDIT_bMONEY_sH			30 

//============С���༭����===============
#define UI_EDIT_sMONEY_X			(SCREEN_APP_X+FONT_SIZE)
#define UI_EDIT_sMONEY_Y			(SCREEN_APP_Y+120)
#define UI_EDIT_sMONEY_W			(UI_CONT_W-FONT_SIZE*2) 
#define UI_EDIT_sMONEY_H			26 
//------ͼƬ�����Ŵ�С����---------------
#define UI_EDIT_sMONEY_fW			9 
#define UI_EDIT_sMONEY_fH			13 
//------ͼƬ���С����---------------
#define UI_EDIT_sMONEY_dW			9 
#define UI_EDIT_sMONEY_dH			22 
//------ͼƬ���ִ�С����---------------
#define UI_EDIT_sMONEY_sW			16 
#define UI_EDIT_sMONEY_sH			22 

#else		//===============================================================================

//---------ȫ������----------------------
#define SCREEN_WIDTH		(240) 
#define SCREEN_HEIGT		(320) 
#define EFFECTIVE_X			(0) 
#define EFFECTIVE_Y			(24)
//---------Ӧ��ʹ�õ�������-------------------
#define SCREEN_APP_X		(EFFECTIVE_X) 
#define SCREEN_APP_Y		(EFFECTIVE_Y)
#define SCREEN_APP_W		(SCREEN_WIDTH) 
#define SCREEN_APP_H		(SCREEN_HEIGT-EFFECTIVE_Y) 
//-------ͼƬ���������������ʾ-------------------------------
#define UI_MAP_TITLE_X		SCREEN_APP_X
#define UI_MAP_TITLE_Y		SCREEN_APP_Y
#define UI_MAP_TITLE_W		SCREEN_APP_W 
#define UI_MAP_TITLE_H		40 

#define UI_MAP_CONT_X		SCREEN_APP_X
#define UI_MAP_CONT_Y		(SCREEN_APP_Y+UI_MAP_TITLE_H)
#define UI_MAP_CONT_W		SCREEN_APP_W 
#define UI_MAP_CONT_H		(SCREEN_APP_H-UI_MAP_TITLE_H)
//----------ϵͳ������������---------------------------------
#define UI_TITLE_X			SCREEN_APP_X
#define UI_TITLE_Y			SCREEN_APP_Y
#define UI_TITLE_W			SCREEN_APP_W 
#define UI_TITLE_H			40 
#define UI_TITLE_COLOUR		RGB565(24,120,200) 
#define FONT_TITLE_COLOUR	RGB565_WITHE 

#define UI_CONT_X			SCREEN_APP_X
#define UI_CONT_Y			(SCREEN_APP_Y+UI_TITLE_H)
#define UI_CONT_W			SCREEN_APP_W 
#define UI_CONT_H			(SCREEN_APP_H-UI_TITLE_H)
#define UI_CONT_COLOUR		RGB565(240,244,248)
#define FONT_CONT_COLOUR	RGB565_BLACK 
//----------���Ʋ˵�����----------------------
#define SCREEN_MENU_X		(SCREEN_APP_X) 
#define SCREEN_MENU_Y		(SCREEN_APP_Y)
#define SCREEN_MENU_W		(SCREEN_APP_W) 
#define SCREEN_MENU_H		(SCREEN_APP_H) 
#define MENU_TITLE_H		40

#define MENU_TIEM_ALL_Y		(SCREEN_MENU_Y+MENU_TITLE_H)
#define MENU_TIEM_ALL_H		(SCREEN_APP_H-MENU_TITLE_H)
#define MENU_TIEM_H			32
#define MENU_TIEM_MAX		((SCREEN_APP_H-MENU_TITLE_H)/MENU_TIEM_H)			//���˵���
//------------�˵�ɫ�ʶ���-----------------
#define RGB565_TITLE_ICON	RGB565(0,127,255)   //0x03ff
#define RGB565_TITLE_FONT	RGB565_WITHE
#define RGB565_TIEM_ICON	UI_CONT_COLOUR
#define RGB565_TIEM_FONT	RGB565(48,48,48)	//0x3186
#define RGB565_SELE_ICON	RGB565(224,224,224)	//0xe71c
#define RGB565_SELE_FONT	RGB565(0,127,255)	//0x03ff

//============������Ϣ����������ʾ============
#define UI_TRADE_MSG_X		(SCREEN_APP_X+FONT_SIZE/2)
#define UI_TRADE_MSG_Y		(SCREEN_APP_Y+16)
#define UI_TRADE_MSG_W		(SCREEN_APP_W-FONT_SIZE) 
#define UI_TRADE_MSG_H		(SCREEN_APP_H-32)

//============����ʧ������������ʾ============
#define UI_TRADE_FA_MSG_X			(SCREEN_APP_X+FONT_SIZE/2)
#define UI_TRADE_FA_MSG_Y			(SCREEN_APP_Y+200)
#define UI_TRADE_FA_MSG_W			(SCREEN_APP_W-FONT_SIZE) 
#define UI_TRADE_FA_MSG_H			(FONT_SIZE*3)

//============���׶�ά��������ʾ============
#define UI_QR_CODE_X			(SCREEN_APP_X+20)
#define UI_QR_CODE_Y			(SCREEN_APP_Y+24+24+10)
#define UI_QR_CODE_W			(200) 
#define UI_QR_CODE_H			(200)

#define UI_QR_MONEY_X			(61)
#define UI_QR_MONEY_Y			(SCREEN_APP_Y+20)
#define UI_QR_MONEY_W			(118)
#define UI_QR_MONEY_H			(FONT_SIZE)

//============������ϸ����������ʾ============
#define UI_ENQU_MONEY_X			(SCREEN_APP_X+FONT_SIZE/2)
#define UI_ENQU_MONEY_Y			(SCREEN_APP_Y+16)
#define UI_ENQU_MONEY_W			(SCREEN_APP_W-FONT_SIZE) 
#define UI_ENQU_MONEY_H			(FONT_SIZE)
#define UI_ENQU_SPACING_H		(8)

//============�����˿�����������ʾ============
#define UI_EDIT_MERCH_SN_X			(UI_CONT_X+24)
#define UI_EDIT_MERCH_SN_Y			(UI_CONT_Y+80)
#define UI_EDIT_MERCH_SN_W			(UI_CONT_W-48) 
#define UI_EDIT_MERCH_SN_H			(FONT_SIZE*2)

//============ɨ������������ʾ============
#define UI_SCAN_TEXT_Y			(UI_CONT_Y+210)
#define UI_SCAN_MONEY_Y			(UI_CONT_Y+124)
//============ͼƬ�ϵ�����������ʾ============
#define UI_NOSIGNEL_TEXT_Y		(160)
#define UI_WAITFOR_TEXT_Y		(160)

//=========Ĭ�ϴ���༭����===============
//------ͼƬ�����Ŵ�С����---------------
#define UI_EDIT_bMONEY_fW			14 
#define UI_EDIT_bMONEY_fH			19 
//------ͼƬ���С����----------------
#define UI_EDIT_bMONEY_dW			14 
#define UI_EDIT_bMONEY_dH			30 
//------ͼƬ���ִ�С����---------------
#define UI_EDIT_bMONEY_sW			22 
#define UI_EDIT_bMONEY_sH			30 
//------����༭����------------------
#define UI_EDIT_bMONEY_W			(UI_EDIT_bMONEY_fW+UI_EDIT_bMONEY_sW*7)
#define UI_EDIT_bMONEY_H			36 
#define UI_EDIT_bMONEY_X			((UI_CONT_W-UI_EDIT_bMONEY_W)/2)
#define UI_EDIT_bMONEY_Y			152

//============С���༭����===============
#define UI_EDIT_sMONEY_X			(24)
#define UI_EDIT_sMONEY_Y			(184)
#define UI_EDIT_sMONEY_W			(UI_CONT_W- UI_EDIT_sMONEY_X*2) 
#define UI_EDIT_sMONEY_H			(26) 
//------ͼƬ�����Ŵ�С����---------------
#define UI_EDIT_sMONEY_fW			9 
#define UI_EDIT_sMONEY_fH			13 
//------ͼƬ���С����---------------
#define UI_EDIT_sMONEY_dW			9 
#define UI_EDIT_sMONEY_dH			22 
//------ͼƬ���ִ�С����---------------
#define UI_EDIT_sMONEY_sW			16 
#define UI_EDIT_sMONEY_sH			22 

#endif



typedef struct
{
	char				*pShowKeyDown;
	char				*pShowkeyUp;
	char				*pShowKeyUpDown;
	
	u16					*pMoney_fName;			// С��������
	u16					sMoney_fW;				// С�����ſ�
	u16					sMoney_fH;				// С�����Ÿ�
}UI_DisplayTheme;		//��ʾ���⣬���ں����л�
extern UI_DisplayTheme tUI_Theme;


/**
 * GUI֧�ֵ�ͼ���ʽ����
 */
typedef struct
{
	u16					w;				//!< ͼ���
	u16					h;				//!< ��
	u16					idata[2];		//!< ��ɫͼƬ����Ϊ:num * ((w+8-1)/8) * h <br/> ��ɫͼƬ����Ϊ:num * w * h * (DISP_DEPTH/8)
}IMAGE;									//ͼƬ�ļ����ݶ��壬�ļ�ʹ��mmap��ͽṹ��һ��


typedef struct
{
	RECTL 	Rect;
	uint16	LcdBuff[2];		//!< ��ɫͼƬ����Ϊ:num * ((w+8-1)/8) * h <br/> ��ɫͼƬ����Ϊ:num * w * h * (DISP_DEPTH/8)
}DisplayBackup;		

typedef enum
{
	MENU_ICON_NUM		=0x0001,			//ͼ��Ϊ���,	��MENU_LIST���ʹ��
	MENU_ICOM_IMG		=0x0002,			//ͼ��Ϊͼ��,	��MENU_LIST���ʹ��
	MENU_LIST			=0x0100,			//�б�˵�
	MENU_RADIO			=0x0200,			//����ѡ��˵�
	MENU_CHECK			=0x0400,			//����ѡ��˵�
	MENU_MUILT_LINE		=0x1000,			//�����ı�,		�������������ʹ��
	MENU_MAX			=0xFFFF
}UI_MENU_TYPE;

/**
 * �ı���ʾ���Ͷ���
 */
typedef enum
{
	TEXT_3X5				=4,				//!< 3x5�����С
	TEXT_6X8				=6,				//!< 6x8�����С
	TEXT_12					=12,			//!< 12x12�����С
	TEXT_16					=16,			//!< 16x16�����С
	TEXT_20					=20,			//!< 20x20�����С
	TEXT_24					=24,			//!< 24x24�����С
	TEXT_32					=32,			//!< 32x32�����С
	TEXT_SIZE				=0x000000FF,	//!< �����С����
	                    	
	TEXT_NONE				=0x00000000,	//!< ��ͨ�ı�
	TEXT_NORMAL				=0x00000000,	//!< ��ͨ�ı�
	TEXT_SHADOW				=0x00000100,	//!< ��Ӱ��(��ɫ��Ч)
	TEXT_BORDER				=0x00000200,	//!< ������
	TEXT_BOLD				=0x00000400,	//!< �Ӵ�
	TEXT_BACK				=0x00000800,	//!< ������ɫ
	                    	
	TEXT_ALIGN_LEFT			=0x10000000,	//!< ˮƽ�����
	TEXT_ALIGN_CENTER		=0x20000000,	//!< ˮƽ���ж���
	TEXT_ALIGN_RIGHT		=0x40000000,	//!< ˮƽ�Ҷ���
	TEXT_ALIGN_MASK			=0x70000000,	//!< ˮƽ��������
	                    	
	TEXT_VALIGN_TOP			=0x01000000,	//!< ��ֱ�϶���
	TEXT_VALIGN_CENTER		=0x02000000,	//!< ��ֱ���ж���
	TEXT_VALIGN_BOTTOM		=0x04000000,	//!< ��ֱ�¶���
	TEXT_VALIGN_MASK		=0x07000000,	//!< ��ֱ��������

	TEXT_EXSTYLE_UNDERLINE  =0x00100000,	//���»���
	TEXT_EXSTYLE_OVERLINE   =0x00200000,	//���ϻ���
	TEXT_EXSTYLE_BORDER     =0x00400000,	//�ӿ�
}TEXT_TYPE;	//V1.1

extern void UI_LoadTheme(UI_DisplayTheme *pTheme);
extern void UI_DisplayInit(void);

extern int UI_ShowPictureFile(RECTL *prclTrg,const u16 *pfilePath);

extern void UI_DisplayBitMapGet(u16 x,u16 y,u16 w,u16 h);
extern void UI_DisplayBitMapSet(void);

extern void UI_ShowBottomProgress(u8 ratio);
extern void UI_ShowParMiddleSlide(u8 par,int ratio);

extern void UI_SetColorRGB565(A_RGB fgColor, uint32 bgColor);
extern int UI_DrawString(POINT* prclTrg,const char *src);
extern int UI_DrawRectString(RECTL* pRect,const char *src);
extern void API_GUI_OprInfo(char* pShowInfo,char *pAfterText);
extern void UI_EditShowMoney(u32 flagPs,char* pMoney);
extern void UI_EditShowStr(u32 flagPs,char* pBuff);
extern void UI_ShowSmallNum(RECTL *prclTrg,int flagMoney,char *pNum);
extern void UI_ShowScreenBmp(const char* pfilePath,char* pMsg,u16 mTop);
extern void UI_ShowBmpAndMoney(uint16 * pfilePath,char* pTradeMoney);

extern void UI_ShowColorRect(RECTL *pRect,int Width,A_RGB Color);

//===============�����ʾ����(ָ������)=================================================
extern void API_GUI_ClearScreen(RECTL* pRect);
/**
 * ����һ����������GUI���潻��
 *
 * @param pTitle 		�������
 * @param pOk 			��ť���д���OK������ʾ, ΪNULL�����ڸð�ť
 * @param pCancel 		��ť���д���Cancel������ʾ, ΪNULL�����ڸð�ť
 * @param tGuiType 		������ʾ���� {@link WIN_TYPE} ���� WIN_FULL|WIN_NOBTN ���ߡ�WIN_POP|WIN_NOBTN
 * @return {@link RET_OK} 						�ɹ�
 * @return {@link RET_API_PARAMETER_ERROR}		������������
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		���ܲ�֧��
 * @return {@link RET_SYSTEM_ERROR}     		ϵͳ����
 */
extern int   API_GUI_CreateWindow(const char* pTitle,const char* pOk,const char* pCancel,u32 tGuiType);

/**
 * GUI��ʾ��Ϣ��ʾ
 *
 * IMG + ��ʾ�ı�
 * @param pImg 		{@link IMAGE}ָ���IMAGE�洢�ṹ��·��
 * @param tTextType {@link TEXT_TYPE}�������
 * @param pTextBuf 	�ı���ʾ��Ϣ
 * @return {@link RET_OK} 						�ɹ�
 * @return {@link RET_API_PARAMETER_ERROR}		������������
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		���ܲ�֧��
 * @return {@link RET_SYSTEM_ERROR}     		ϵͳ����
 */
extern int  API_GUI_Info(const IMAGE* pImg,u32 tTextType,const char* pTextBuf);
extern void API_GUI_Edit_Prompt(u32 tFrontTextType,char* pFrontTextBuf,u32 tAfterTextType,char* pAfterTextBuf);
extern void API_GUI_Edit(u32 tTextType,char* pTextDef,int tMaxLen,u32 tImeType,u32 tImeLimit);

extern u32 API_UI_FeeEdit(u16 keyNum);
extern void UI_ImgShowNum(u32 flagPs,char* pStrNum);

extern void API_GUI_InputEdit(char* pStrDef,int tMaxLen,u32 Way,Fun_ShowNum pShow);

extern int API_GUI_Edit_GetText(char* pAscText,int tMaxLen);

extern int   APP_GUI_Menu(char* pTitle,int stratIndex,int tNum,int tCurInx,char** pMenuText);

#define 	APP_ShowChangeInfo	pGuiFun->ShowChangeInfo

extern void API_GUI_Draw565QRcode(RECTL* pRECTL,char *pInMsg,A_RGB fgColor);

/**
 * ��ʾGUI����, ��ʼ����
 *
 * @return {@link RET_OK} 						�ɹ�
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		���ܲ�֧��
 * @return {@link RET_SYSTEM_ERROR}     		ϵͳ����
 */
extern int   API_GUI_Show(void);

extern void APP_ShowSta(char *pTitle,char *pMsg);
//===========������ʾ����=======
extern int APP_ShowMsg(char *pTitle,char *pMsg,int timeOutMs);
//===========���Ͻ���ʾ����=======
extern int APP_ShowInfo(char *pTitle,char *pInfo,int timeOutMs);

//extern int APP_GUI_Edit(char *pTitle,const char* pFrontTextBuf,const char* pAfterTextBuf,char* pOutMsg,int MinLen,int MaxLen);


extern void APP_HitMsg(const char* pMsg,int tTimeOutMS);

/**
 * ����һ��GUI�˵����б� 
 * @param pTitle 		�������
 * @param pLineText 	������
 * @param LineMax 		������(Bit15 �кű��)
 * @param pAfterText 	ĩ����ʾ����(�ϻ����ҿ�)
 */
extern void APP_GUI_LineMenu(char* pTitle,char *pLineText[],u16 LineMax,char* pAfterText);

//====�ص�����ָ�룬����GUIѡ���б���ʾ��==========
/**
 * ���幹��һ��GUIѡ���б���ʾ���ָ��
 * @param char* 		������ʾ����ָ��
 * @param int 			�б���0~n
 * @param return 		0~nʣ��û��ʾ��������<0 ������ʾ������
 */
typedef int (*fOption_ShowItem)(char*,int);
/**
 * ����һ��GUIѡ���б�
 *
 * ����һ��GUIѡ���б�, 
 * @param pTitle 		�������
 * @param Start 		��ʼ����
 * @param pFunShowItem 	��ʾ�������ɺ���
 * @param return 		��ʾ����������ʣ����
 */
extern void APP_GUI_Option(char* pTitle,char *pMenuText[],int ItemMax,u8 UpDownBit);


//====�ص�����ָ�룬����GUIѡ�����==========
/**
 * ���幹��һ��GUIѡ���б���ʾ���ָ��
 * @param char* 		��ʾ����
 * @param int 			�б���0~n
 * @return {@link TRUE,FALSE} TRUE(������ʾ�˵�)��FALSE(�˳��˵���ʾ)
 */
typedef BOOL (*fOption_RunItem)(char*,int);

/**
 * ����һ��GUIѡ���б�����
 *
 * ����һ��GUIѡ���б�,��������д���, 
 * @param pTitle 		�������
 * @param pFunShowItem 	��ʾ�������ɺ���
 * @param pFunRun 		�����Ӧ�����
 * @param pFunKey 		���ܼ�������
 * @param return 		��ʾ����������
 */
int APP_GUI_OpProcess(char *pTitle,fOption_ShowItem pFunShowItem,fOption_RunItem pFunRunItem,APP_HANDLE pFunKey);


#endif

