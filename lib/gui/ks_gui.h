

#ifndef _GUI_DISPLAY_
#define _GUI_DISPLAY_

#define FONT_SIZE    		(24)    
#define MENU_ITEM_MAX    	8    		//菜单最大项数

#define RGB565_WITHE		RGB_CURR(0xff,0xff,0xff)	//0x0000FFFF
#define RGB565_BLACK		RGB_CURR(0x00,0x00,0x00)	//0x00000000

#define RGB565_RED			RGB_CURR(0xff,0x00,0x00)
#define RGB565_GREEN		RGB_CURR(0x00,0xff,0x00)	//0x07E0
#define RGB565_BLUE		RGB_CURR(0x00,0x00,0xff)	//0x001F

//------------菜单色彩定义-----------------
//#define RGB565_TITLE_ICON		RGB_CURR(0,127,255)   //0x03ff
//#define RGB565_TITLE_FONT		RGB565_WITHE
#define RGB565_TIEM_ICON		RGB_CURR(240,244,248)
#define RGB565_TIEM_FONT		RGB_CURR(48,48,48)	//0x3186
#define RGB565_SELE_ICON		RGB_CURR(224,224,224)	//0xe71c
#define RGB565_SELE_FONT		RGB_CURR(0,127,255)	//0x03ff

#define UI_CONT_COLOUR		RGB565_TIEM_ICON
#define FONT_CONT_COLOUR		RGB565_BLACK 

#define UI_TITLE_COLOUR		RGB_CURR(24,120,200) 
#define FONT_TITLE_COLOUR		RGB565_WITHE 






typedef enum 
{
	GUI_SHOW_MSG	= 0x11	,		//普通显示内容
	GUI_EDIT_MSG	= 0x21	,		//编辑窗口
	GUI_MENU_LINE	= 0x51	,		//一维菜单 
	GUI_MENU_TWO	= 0x52	,		//二维菜单
}GUI_TYPE;			//V1.2	

/**
 * 文本输入类型定义
 */
typedef enum 
{
	IME_NONE			=0x00000000,		//!< NONE
	IME_NUM			=0x00000001,		//!< 数字
	IME_abc			=0x00000002,		//!< 小写字母
	IME_ABC			=0x00000004,		//!< 大小字母
	IME_Abc			=0x00000008,		//!< 大小写混合字母
	IME_SYM			=0x00000010,		//!< 符号
	IME_SUM			=0x00000020,		//!< 金额 1.23
	IME_PY				=0x00000040,		//!< 拼音 支持GB2312编码
	IME_PYGBK			=0x00000080,		//!< 全拼 支持GBK编码
	IME_FMT			=0x00000100,		//!< 格式化模式数字输入，如IP,账号等.
	IME_SCAN			=0x00000200,		//!< 扫码输入
	IME_MASK			=0x000003FF,		//!< 掩码
	IME_PIN_MODE		=0x10000000,		//!< 密码模式	
	IME_SYM_MODE		=0x20000000,		//!< 符号模式	
	IME_ENG			=IME_ABC|IME_abc|IME_Abc, //!< 英文输入
	IME_END	
}IME_TYPE;			//V1.2	




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
	TEXT_12					=12,			//!< 12x12字体大小
	TEXT_16					=16,			//!< 16x16字体大小
	TEXT_20					=20,			//!< 20x20字体大小
	TEXT_24					=24,			//!< 24x24字体大小
	TEXT_32					=32,			//!< 32x32字体大小
	TEXT_SIZE					=0x000000FF,	//!< 字体大小掩码
	                    	
	TEXT_NONE					=0x00000000,	//!< 普通文本
	TEXT_NORMAL				=0x00000000,	//!< 普通文本
	TEXT_SHADOW				=0x00000100,	//!< 阴影字(彩色有效)
	TEXT_BORDER				=0x00000200,	//!< 空心字
	TEXT_BOLD					=0x00000400,	//!< 加粗
	TEXT_BACK					=0x00000800,	//!< 带背景色
	
	TEXT_ALIGN_LEFT			=0x10000000,	//!< 水平左对齐
	TEXT_ALIGN_CENTER			=0x20000000,	//!< 水平居中对齐
	TEXT_ALIGN_RIGHT			=0x40000000,	//!< 水平右对齐
	TEXT_ALIGN_MASK			=0x70000000,	//!< 水平对齐掩码
	                    	
	TEXT_VALIGN_TOP			=0x01000000,	//!< 垂直上对齐
	TEXT_VALIGN_CENTER		=0x02000000,	//!< 垂直居中对齐
	TEXT_VALIGN_BOTTOM		=0x04000000,	//!< 垂直下对齐
	TEXT_VALIGN_MASK			=0x07000000,	//!< 垂直对齐掩码

	TEXT_EXSTYLE_UNDERLINE	=0x00100000,	//加下划线
	TEXT_EXSTYLE_OVERLINE	=0x00200000,	//加上划线
	TEXT_EXSTYLE_BORDER		=0x00400000,	//加框
	TEXT_RECT_CLEAR 			=0x00800000,	//先清空后显示
	TEXT_LINE_NUM_MASK		=0x000F0000,	//指定行号(1~15)
}TEXT_TYPE;	//V1.1



typedef void (*Fun_ShowNum)(u32,char*); 


//=================================================================================


#endif

