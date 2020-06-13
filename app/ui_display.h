#ifndef _UI_DISPLAY_
#define _UI_DISPLAY_


#define FONT_SIZE    			(24)    

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
//#define UI_TITLE_COLOUR		RGB565(24,120,200) 
#define FONT_TITLE_COLOUR	RGB565_WITHE 

#define UI_CONT_X			SCREEN_APP_X
#define UI_CONT_Y			(SCREEN_APP_Y+UI_TITLE_H)
#define UI_CONT_W			SCREEN_APP_W 
#define UI_CONT_H			(SCREEN_APP_H-UI_TITLE_H)
//#define UI_CONT_COLOUR		RGB565(240,244,248)
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
//#define RGB565_TIEM_ICON	UI_CONT_COLOUR
//#define RGB565_TIEM_FONT	RGB565(48,48,48)	//0x3186
//#define RGB565_SELE_ICON	RGB565(224,224,224)	//0xe71c
//#define RGB565_SELE_FONT	RGB565(0,127,255)	//0x03ff

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




typedef struct
{
	char				*pShowKeyDown;
	char				*pShowkeyUp;
	char				*pShowKeyUpDown;
	
	char				*pMoney_fName;			// С��������
	u16					sMoney_fW;				// С�����ſ�
	u16					sMoney_fH;				// С�����Ÿ�
}UI_DisplayTheme;		//��ʾ���⣬���ں����л�
extern UI_DisplayTheme tUI_Theme;

/**
 * �ı���ʾ���Ͷ���
 */

extern void UI_LoadTheme(const UI_DisplayTheme *pTheme);
extern void UI_DisplayInit(void);
//=========���ò˵�������ʾ�����в˵���=================
extern void UI_SetMenuItem(int num);

extern int UI_ShowPictureFile(RECTL *prclTrg,const char *pfilePath);

extern void UI_DisplayBitMapGet(u16 x,u16 y,u16 w,u16 h);
extern void UI_DisplayBitMapSet(void);

extern void UI_ShowBottomProgress(u8 ratio);
extern void UI_ShowParMiddleSlide(u8 par,int ratio);

extern void UI_SetColorRGB565(A_RGB fgColor, u32 bgColor);
extern int UI_DrawString(POINT* prclTrg,const char *src);
extern int UI_DrawRectString(RECTL* pRect,const char *src);
extern void API_GUI_OprInfo(char* pShowInfo,char *pAfterText);
extern void UI_EditShowMoney(u32 flagPs,char* pMoney);
extern void UI_EditShowStr(u32 flagPs,char* pBuff);
extern void UI_ShowSmallNum(RECTL *prclTrg,int flagMoney,char *pNum);
extern void UI_ShowScreenBmp(const char* pfilePath,char* pMsg,u16 mTop);
extern void UI_ShowBmpAndMoney(const char*  pfilePath,char* pTradeMoney);

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

extern int APP_GUI_Menu(char* pTitle,char *pMsg,int tNum,int tCurInx,const char** pMenuText,int timeoutMs);

#define 	APP_ShowChangeInfo	pGuiFun->ShowChangeInfo

extern void API_GUI_Draw565QRcode(RECTL* pRECTL,char *pInMsg,A_RGB fgColor);

/**
 * ��ʾGUI����, ��ʼ����
 *
 * @return {@link RET_OK} 						�ɹ�
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		���ܲ�֧��
 * @return {@link RET_SYSTEM_ERROR}     		ϵͳ����
 */
extern void API_GUI_Show(void);

extern void APP_ShowSta(char *pTitle,char *pMsg);
//===========������ʾ����=======
extern int APP_ShowMsg(char *pTitle,char *pMsg,int timeOutMs);
//===========���Ͻ���ʾ����=======
extern int APP_ShowInfo(char *pTitle,char *pInfo,int timeOutMs);
extern int APP_ShowInfoMsg(char *pTitle,char *pInfo,char *pAfterText,int timeOutMs);

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



#endif

