#ifndef _UI_DISPLAY_
#define _UI_DISPLAY_


#define FONT_SIZE    			(24)    
#define HZ_INDEX(hz)    		((hz[0] - 0xa1) * 94 + (hz[1] - 0xa1))
#define DOTS_BYTES    			((FONT_SIZE * FONT_SIZE / 8))

#ifdef DISPLAY_HORIZONTAL_SCREEN			//横屏定义
//---------全屏参数----------------------
#define SCREEN_WIDTH		(320) 
#define SCREEN_HEIGT		(240) 
#define EFFECTIVE_X			(0) 
#define EFFECTIVE_Y			(24)
//---------应用使用的屏区域-------------------
#define SCREEN_APP_X		0 
#define SCREEN_APP_Y		0
#define SCREEN_APP_W		(SCREEN_WIDTH) 
#define SCREEN_APP_H		(SCREEN_HEIGT-EFFECTIVE_Y) 
//-------图片标题与操作内容显示-------------------------------
#define UI_MAP_TITLE_X		SCREEN_APP_X
#define UI_MAP_TITLE_Y		SCREEN_APP_Y
#define UI_MAP_TITLE_W		SCREEN_APP_W 
#define UI_MAP_TITLE_H		40 

#define UI_MAP_CONT_X		SCREEN_APP_X
#define UI_MAP_CONT_Y		(SCREEN_APP_Y+UI_MAP_TITLE_H)
#define UI_MAP_CONT_W		SCREEN_APP_W 
#define UI_MAP_CONT_H		(SCREEN_APP_H-UI_MAP_TITLE_H)
//----------系统操作界面配置---------------------------------
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
//----------定制菜单参数----------------------
#define SCREEN_MENU_X		(SCREEN_APP_X) 
#define SCREEN_MENU_Y		(SCREEN_APP_Y)
#define SCREEN_MENU_W		(SCREEN_APP_W) 
#define SCREEN_MENU_H		(SCREEN_APP_H) 
#define MENU_TITLE_H		36

#define MENU_TIEM_ALL_Y		(SCREEN_MENU_Y+MENU_TITLE_H)
#define MENU_TIEM_ALL_H		(SCREEN_APP_H-MENU_TITLE_H)
#define MENU_TIEM_H			30
#define MENU_TIEM_MAX		((SCREEN_APP_H-MENU_TITLE_H)/MENU_TIEM_H)			//最多菜单项
//------------菜单色彩定义-----------------
#define RGB565_TITLE_ICON	RGB565(0,127,255)   //0x03ff
#define RGB565_TITLE_FONT	RGB565_WITHE
#define RGB565_TIEM_ICON	UI_CONT_COLOUR
#define RGB565_TIEM_FONT	RGB565(48,48,48)	//0x3186
#define RGB565_SELE_ICON	RGB565(224,224,224)	//0xe71c
#define RGB565_SELE_FONT	RGB565(0,127,255)	//0x03ff

//============交易信息文字坐标显示============
#define UI_TRADE_MSG_X		(SCREEN_APP_X+FONT_SIZE)
#define UI_TRADE_MSG_Y		(SCREEN_APP_Y+FONT_SIZE/2)
#define UI_TRADE_MSG_W		(SCREEN_APP_W-FONT_SIZE*2) 
#define UI_TRADE_MSG_H		(SCREEN_APP_H-FONT_SIZE)

//============交易失败文字坐标显示============
#define UI_TRADE_FA_MSG_X		(SCREEN_APP_X+FONT_SIZE/2)
#define UI_TRADE_FA_MSG_Y		(SCREEN_APP_Y+160)
#define UI_TRADE_FA_MSG_W		(SCREEN_APP_W-FONT_SIZE) 
#define UI_TRADE_FA_MSG_H		(FONT_SIZE)

//============扫码文字坐标显示============
#define UI_SCAN_TEXT_Y			(UI_CONT_Y+142)
#define UI_SCAN_MONEY_Y			(UI_CONT_Y+82)
//============图片上的文字坐标显示============
#define UI_NOSIGNEL_TEXT_Y		(182)
#define UI_WAITFOR_TEXT_Y		(124)

//============交易二维码坐标显示============
#define UI_QR_CODE_X			(SCREEN_APP_X+85)
#define UI_QR_CODE_Y			(SCREEN_APP_Y+42)
#define UI_QR_CODE_W			(150) 
#define UI_QR_CODE_H			(150)

#define UI_QR_MONEY_X			(SCREEN_APP_X+70)
#define UI_QR_MONEY_Y			(SCREEN_APP_Y+10)
#define UI_QR_MONEY_W			(SCREEN_APP_W-70*2)
#define UI_QR_MONEY_H			(FONT_SIZE)

//============订单明细文字坐标显示============
#define UI_ENQU_MONEY_X			(SCREEN_APP_X+FONT_SIZE/2)
#define UI_ENQU_MONEY_Y			(SCREEN_APP_Y+16)
#define UI_ENQU_MONEY_W			(SCREEN_APP_W-FONT_SIZE) 
#define UI_ENQU_MONEY_H			(FONT_SIZE)
#define UI_ENQU_SPACING_H		(8)

//============订单退款文字坐标显示============
#define UI_EDIT_MERCH_SN_X			(UI_CONT_X+48)
#define UI_EDIT_MERCH_SN_Y			(UI_CONT_Y+64)
#define UI_EDIT_MERCH_SN_W			(UI_CONT_W-48*2) 
#define UI_EDIT_MERCH_SN_H			(FONT_SIZE*2)

//============大金额编辑坐标===============
#define UI_EDIT_bMONEY_X			(UI_CONT_X+69)
#define UI_EDIT_bMONEY_Y			(UI_CONT_Y+64)
#define UI_EDIT_bMONEY_W			(UI_CONT_W-69*2)
#define UI_EDIT_bMONEY_H			36 
//------图片金额符号大小定义---------------
#define UI_EDIT_bMONEY_fW			14 
#define UI_EDIT_bMONEY_fH			19 
//------图片点大小定义---------------
#define UI_EDIT_bMONEY_dW			14 
#define UI_EDIT_bMONEY_dH			30 
//------图片数字大小定义---------------
#define UI_EDIT_bMONEY_sW			22 
#define UI_EDIT_bMONEY_sH			30 

//============小金额编辑坐标===============
#define UI_EDIT_sMONEY_X			(SCREEN_APP_X+FONT_SIZE)
#define UI_EDIT_sMONEY_Y			(SCREEN_APP_Y+120)
#define UI_EDIT_sMONEY_W			(UI_CONT_W-FONT_SIZE*2) 
#define UI_EDIT_sMONEY_H			26 
//------图片金额符号大小定义---------------
#define UI_EDIT_sMONEY_fW			9 
#define UI_EDIT_sMONEY_fH			13 
//------图片点大小定义---------------
#define UI_EDIT_sMONEY_dW			9 
#define UI_EDIT_sMONEY_dH			22 
//------图片数字大小定义---------------
#define UI_EDIT_sMONEY_sW			16 
#define UI_EDIT_sMONEY_sH			22 

#else		//===============================================================================

//---------全屏参数----------------------
#define SCREEN_WIDTH		(240) 
#define SCREEN_HEIGT		(320) 
#define EFFECTIVE_X			(0) 
#define EFFECTIVE_Y			(24)
//---------应用使用的屏区域-------------------
#define SCREEN_APP_X		(EFFECTIVE_X) 
#define SCREEN_APP_Y		(EFFECTIVE_Y)
#define SCREEN_APP_W		(SCREEN_WIDTH) 
#define SCREEN_APP_H		(SCREEN_HEIGT-EFFECTIVE_Y) 
//-------图片标题与操作内容显示-------------------------------
#define UI_MAP_TITLE_X		SCREEN_APP_X
#define UI_MAP_TITLE_Y		SCREEN_APP_Y
#define UI_MAP_TITLE_W		SCREEN_APP_W 
#define UI_MAP_TITLE_H		40 

#define UI_MAP_CONT_X		SCREEN_APP_X
#define UI_MAP_CONT_Y		(SCREEN_APP_Y+UI_MAP_TITLE_H)
#define UI_MAP_CONT_W		SCREEN_APP_W 
#define UI_MAP_CONT_H		(SCREEN_APP_H-UI_MAP_TITLE_H)
//----------系统操作界面配置---------------------------------
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
//----------定制菜单参数----------------------
#define SCREEN_MENU_X		(SCREEN_APP_X) 
#define SCREEN_MENU_Y		(SCREEN_APP_Y)
#define SCREEN_MENU_W		(SCREEN_APP_W) 
#define SCREEN_MENU_H		(SCREEN_APP_H) 
#define MENU_TITLE_H		40

#define MENU_TIEM_ALL_Y		(SCREEN_MENU_Y+MENU_TITLE_H)
#define MENU_TIEM_ALL_H		(SCREEN_APP_H-MENU_TITLE_H)
#define MENU_TIEM_H			32
#define MENU_TIEM_MAX		((SCREEN_APP_H-MENU_TITLE_H)/MENU_TIEM_H)			//最多菜单项
//------------菜单色彩定义-----------------
#define RGB565_TITLE_ICON	RGB565(0,127,255)   //0x03ff
#define RGB565_TITLE_FONT	RGB565_WITHE
#define RGB565_TIEM_ICON	UI_CONT_COLOUR
#define RGB565_TIEM_FONT	RGB565(48,48,48)	//0x3186
#define RGB565_SELE_ICON	RGB565(224,224,224)	//0xe71c
#define RGB565_SELE_FONT	RGB565(0,127,255)	//0x03ff

//============交易信息文字坐标显示============
#define UI_TRADE_MSG_X		(SCREEN_APP_X+FONT_SIZE/2)
#define UI_TRADE_MSG_Y		(SCREEN_APP_Y+16)
#define UI_TRADE_MSG_W		(SCREEN_APP_W-FONT_SIZE) 
#define UI_TRADE_MSG_H		(SCREEN_APP_H-32)

//============交易失败文字坐标显示============
#define UI_TRADE_FA_MSG_X			(SCREEN_APP_X+FONT_SIZE/2)
#define UI_TRADE_FA_MSG_Y			(SCREEN_APP_Y+200)
#define UI_TRADE_FA_MSG_W			(SCREEN_APP_W-FONT_SIZE) 
#define UI_TRADE_FA_MSG_H			(FONT_SIZE*3)

//============交易二维码坐标显示============
#define UI_QR_CODE_X			(SCREEN_APP_X+20)
#define UI_QR_CODE_Y			(SCREEN_APP_Y+24+24+10)
#define UI_QR_CODE_W			(200) 
#define UI_QR_CODE_H			(200)

#define UI_QR_MONEY_X			(61)
#define UI_QR_MONEY_Y			(SCREEN_APP_Y+20)
#define UI_QR_MONEY_W			(118)
#define UI_QR_MONEY_H			(FONT_SIZE)

//============订单明细文字坐标显示============
#define UI_ENQU_MONEY_X			(SCREEN_APP_X+FONT_SIZE/2)
#define UI_ENQU_MONEY_Y			(SCREEN_APP_Y+16)
#define UI_ENQU_MONEY_W			(SCREEN_APP_W-FONT_SIZE) 
#define UI_ENQU_MONEY_H			(FONT_SIZE)
#define UI_ENQU_SPACING_H		(8)

//============订单退款文字坐标显示============
#define UI_EDIT_MERCH_SN_X			(UI_CONT_X+24)
#define UI_EDIT_MERCH_SN_Y			(UI_CONT_Y+80)
#define UI_EDIT_MERCH_SN_W			(UI_CONT_W-48) 
#define UI_EDIT_MERCH_SN_H			(FONT_SIZE*2)

//============扫码文字坐标显示============
#define UI_SCAN_TEXT_Y			(UI_CONT_Y+210)
#define UI_SCAN_MONEY_Y			(UI_CONT_Y+124)
//============图片上的文字坐标显示============
#define UI_NOSIGNEL_TEXT_Y		(160)
#define UI_WAITFOR_TEXT_Y		(160)

//=========默认大金额编辑坐标===============
//------图片金额符号大小定义---------------
#define UI_EDIT_bMONEY_fW			14 
#define UI_EDIT_bMONEY_fH			19 
//------图片点大小定义----------------
#define UI_EDIT_bMONEY_dW			14 
#define UI_EDIT_bMONEY_dH			30 
//------图片数字大小定义---------------
#define UI_EDIT_bMONEY_sW			22 
#define UI_EDIT_bMONEY_sH			30 
//------大金额编辑坐标------------------
#define UI_EDIT_bMONEY_W			(UI_EDIT_bMONEY_fW+UI_EDIT_bMONEY_sW*7)
#define UI_EDIT_bMONEY_H			36 
#define UI_EDIT_bMONEY_X			((UI_CONT_W-UI_EDIT_bMONEY_W)/2)
#define UI_EDIT_bMONEY_Y			152

//============小金额编辑坐标===============
#define UI_EDIT_sMONEY_X			(24)
#define UI_EDIT_sMONEY_Y			(184)
#define UI_EDIT_sMONEY_W			(UI_CONT_W- UI_EDIT_sMONEY_X*2) 
#define UI_EDIT_sMONEY_H			(26) 
//------图片金额符号大小定义---------------
#define UI_EDIT_sMONEY_fW			9 
#define UI_EDIT_sMONEY_fH			13 
//------图片点大小定义---------------
#define UI_EDIT_sMONEY_dW			9 
#define UI_EDIT_sMONEY_dH			22 
//------图片数字大小定义---------------
#define UI_EDIT_sMONEY_sW			16 
#define UI_EDIT_sMONEY_sH			22 

#endif



typedef struct
{
	char				*pShowKeyDown;
	char				*pShowkeyUp;
	char				*pShowKeyUpDown;
	
	u16					*pMoney_fName;			// 小金额符号名
	u16					sMoney_fW;				// 小金额符号宽
	u16					sMoney_fH;				// 小金额符号高
}UI_DisplayTheme;		//显示主题，用于后期切换
extern UI_DisplayTheme tUI_Theme;


/**
 * GUI支持的图像格式定义
 */
typedef struct
{
	u16					w;				//!< 图像宽
	u16					h;				//!< 高
	u16					idata[2];		//!< 单色图片长度为:num * ((w+8-1)/8) * h <br/> 彩色图片长度为:num * w * h * (DISP_DEPTH/8)
}IMAGE;									//图片文件数据定义，文件使用mmap后和结构体一致


typedef struct
{
	RECTL 	Rect;
	uint16	LcdBuff[2];		//!< 单色图片长度为:num * ((w+8-1)/8) * h <br/> 彩色图片长度为:num * w * h * (DISP_DEPTH/8)
}DisplayBackup;		

typedef enum
{
	MENU_ICON_NUM		=0x0001,			//图标为序号,	与MENU_LIST组合使用
	MENU_ICOM_IMG		=0x0002,			//图标为图像,	与MENU_LIST组合使用
	MENU_LIST			=0x0100,			//列表菜单
	MENU_RADIO			=0x0200,			//单项选择菜单
	MENU_CHECK			=0x0400,			//多项选择菜单
	MENU_MUILT_LINE		=0x1000,			//多行文本,		与其它类型组合使用
	MENU_MAX			=0xFFFF
}UI_MENU_TYPE;

/**
 * 文本显示类型定义
 */
typedef enum
{
	TEXT_3X5				=4,				//!< 3x5字体大小
	TEXT_6X8				=6,				//!< 6x8字体大小
	TEXT_12					=12,			//!< 12x12字体大小
	TEXT_16					=16,			//!< 16x16字体大小
	TEXT_20					=20,			//!< 20x20字体大小
	TEXT_24					=24,			//!< 24x24字体大小
	TEXT_32					=32,			//!< 32x32字体大小
	TEXT_SIZE				=0x000000FF,	//!< 字体大小掩码
	                    	
	TEXT_NONE				=0x00000000,	//!< 普通文本
	TEXT_NORMAL				=0x00000000,	//!< 普通文本
	TEXT_SHADOW				=0x00000100,	//!< 阴影字(彩色有效)
	TEXT_BORDER				=0x00000200,	//!< 空心字
	TEXT_BOLD				=0x00000400,	//!< 加粗
	TEXT_BACK				=0x00000800,	//!< 带背景色
	                    	
	TEXT_ALIGN_LEFT			=0x10000000,	//!< 水平左对齐
	TEXT_ALIGN_CENTER		=0x20000000,	//!< 水平居中对齐
	TEXT_ALIGN_RIGHT		=0x40000000,	//!< 水平右对齐
	TEXT_ALIGN_MASK			=0x70000000,	//!< 水平对齐掩码
	                    	
	TEXT_VALIGN_TOP			=0x01000000,	//!< 垂直上对齐
	TEXT_VALIGN_CENTER		=0x02000000,	//!< 垂直居中对齐
	TEXT_VALIGN_BOTTOM		=0x04000000,	//!< 垂直下对齐
	TEXT_VALIGN_MASK		=0x07000000,	//!< 垂直对齐掩码

	TEXT_EXSTYLE_UNDERLINE  =0x00100000,	//加下划线
	TEXT_EXSTYLE_OVERLINE   =0x00200000,	//加上划线
	TEXT_EXSTYLE_BORDER     =0x00400000,	//加框
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

//===============清除显示内容(指定区域)=================================================
extern void API_GUI_ClearScreen(RECTL* pRect);
/**
 * 创建一个窗体用于GUI界面交互
 *
 * @param pTitle 		界面标题
 * @param pOk 			按钮栏中存在OK键的提示, 为NULL不存在该按钮
 * @param pCancel 		按钮栏中存在Cancel键的提示, 为NULL不存在该按钮
 * @param tGuiType 		窗体显示类型 {@link WIN_TYPE} 例如 WIN_FULL|WIN_NOBTN 或者　WIN_POP|WIN_NOBTN
 * @return {@link RET_OK} 						成功
 * @return {@link RET_API_PARAMETER_ERROR}		函数参数错误
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		功能不支持
 * @return {@link RET_SYSTEM_ERROR}     		系统错误
 */
extern int   API_GUI_CreateWindow(const char* pTitle,const char* pOk,const char* pCancel,u32 tGuiType);

/**
 * GUI提示信息显示
 *
 * IMG + 提示文本
 * @param pImg 		{@link IMAGE}指针或IMAGE存储结构的路径
 * @param tTextType {@link TEXT_TYPE}组合类型
 * @param pTextBuf 	文本提示信息
 * @return {@link RET_OK} 						成功
 * @return {@link RET_API_PARAMETER_ERROR}		函数参数错误
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		功能不支持
 * @return {@link RET_SYSTEM_ERROR}     		系统错误
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
 * 显示GUI界面, 开始交互
 *
 * @return {@link RET_OK} 						成功
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		功能不支持
 * @return {@link RET_SYSTEM_ERROR}     		系统错误
 */
extern int   API_GUI_Show(void);

extern void APP_ShowSta(char *pTitle,char *pMsg);
//===========剧中显示内容=======
extern int APP_ShowMsg(char *pTitle,char *pMsg,int timeOutMs);
//===========左上角显示内容=======
extern int APP_ShowInfo(char *pTitle,char *pInfo,int timeOutMs);

//extern int APP_GUI_Edit(char *pTitle,const char* pFrontTextBuf,const char* pAfterTextBuf,char* pOutMsg,int MinLen,int MaxLen);


extern void APP_HitMsg(const char* pMsg,int tTimeOutMS);

/**
 * 构建一个GUI菜单行列表 
 * @param pTitle 		界面标题
 * @param pLineText 	行内容
 * @param LineMax 		行数量(Bit15 行号标记)
 * @param pAfterText 	末行显示内容(上划线右靠)
 */
extern void APP_GUI_LineMenu(char* pTitle,char *pLineText[],u16 LineMax,char* pAfterText);

//====回调函数指针，用于GUI选项列表显示项==========
/**
 * 定义构建一个GUI选项列表显示项函数指针
 * @param char* 		返回显示数据指针
 * @param int 			列表项0~n
 * @param return 		0~n剩余没显示的项数，<0 不能显示的内容
 */
typedef int (*fOption_ShowItem)(char*,int);
/**
 * 构建一个GUI选项列表
 *
 * 构建一个GUI选项列表, 
 * @param pTitle 		界面标题
 * @param Start 		起始索引
 * @param pFunShowItem 	显示内容生成函数
 * @param return 		显示参数排列项剩余项
 */
extern void APP_GUI_Option(char* pTitle,char *pMenuText[],int ItemMax,u8 UpDownBit);


//====回调函数指针，用于GUI选项处理功能==========
/**
 * 定义构建一个GUI选项列表显示项函数指针
 * @param char* 		显示标题
 * @param int 			列表项0~n
 * @return {@link TRUE,FALSE} TRUE(继续显示菜单)，FALSE(退出菜单显示)
 */
typedef BOOL (*fOption_RunItem)(char*,int);

/**
 * 构建一个GUI选项列表处理函数
 *
 * 构建一个GUI选项列表,并对其进行处理, 
 * @param pTitle 		界面标题
 * @param pFunShowItem 	显示内容生成函数
 * @param pFunRun 		处理对应项操作
 * @param pFunKey 		功能键处理功能
 * @param return 		显示参数排列项
 */
int APP_GUI_OpProcess(char *pTitle,fOption_ShowItem pFunShowItem,fOption_RunItem pFunRunItem,APP_HANDLE pFunKey);


#endif

