

#ifndef _GUI_DISPLAY_
#define _GUI_DISPLAY_

#define FONT_SIZE    		(24)    
#define MENU_ITEM_MAX    	8    		//�˵��������

#define RGB565_WITHE		RGB_CURR(0xff,0xff,0xff)	//0x0000FFFF
#define RGB565_BLACK		RGB_CURR(0x00,0x00,0x00)	//0x00000000

#define RGB565_RED			RGB_CURR(0xff,0x00,0x00)
#define RGB565_GREEN		RGB_CURR(0x00,0xff,0x00)	//0x07E0
#define RGB565_BLUE		RGB_CURR(0x00,0x00,0xff)	//0x001F

//------------�˵�ɫ�ʶ���-----------------
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
	GUI_SHOW_MSG	= 0x11	,		//��ͨ��ʾ����
	GUI_EDIT_MSG	= 0x21	,		//�༭����
	GUI_MENU_LINE	= 0x51	,		//һά�˵� 
	GUI_MENU_TWO	= 0x52	,		//��ά�˵�
}GUI_TYPE;			//V1.2	

/**
 * �ı��������Ͷ���
 */
typedef enum 
{
	IME_NONE			=0x00000000,		//!< NONE
	IME_NUM			=0x00000001,		//!< ����
	IME_abc			=0x00000002,		//!< Сд��ĸ
	IME_ABC			=0x00000004,		//!< ��С��ĸ
	IME_Abc			=0x00000008,		//!< ��Сд�����ĸ
	IME_SYM			=0x00000010,		//!< ����
	IME_SUM			=0x00000020,		//!< ��� 1.23
	IME_PY				=0x00000040,		//!< ƴ�� ֧��GB2312����
	IME_PYGBK			=0x00000080,		//!< ȫƴ ֧��GBK����
	IME_FMT			=0x00000100,		//!< ��ʽ��ģʽ�������룬��IP,�˺ŵ�.
	IME_SCAN			=0x00000200,		//!< ɨ������
	IME_MASK			=0x000003FF,		//!< ����
	IME_PIN_MODE		=0x10000000,		//!< ����ģʽ	
	IME_SYM_MODE		=0x20000000,		//!< ����ģʽ	
	IME_ENG			=IME_ABC|IME_abc|IME_Abc, //!< Ӣ������
	IME_END	
}IME_TYPE;			//V1.2	




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
	TEXT_12					=12,			//!< 12x12�����С
	TEXT_16					=16,			//!< 16x16�����С
	TEXT_20					=20,			//!< 20x20�����С
	TEXT_24					=24,			//!< 24x24�����С
	TEXT_32					=32,			//!< 32x32�����С
	TEXT_SIZE					=0x000000FF,	//!< �����С����
	                    	
	TEXT_NONE					=0x00000000,	//!< ��ͨ�ı�
	TEXT_NORMAL				=0x00000000,	//!< ��ͨ�ı�
	TEXT_SHADOW				=0x00000100,	//!< ��Ӱ��(��ɫ��Ч)
	TEXT_BORDER				=0x00000200,	//!< ������
	TEXT_BOLD					=0x00000400,	//!< �Ӵ�
	TEXT_BACK					=0x00000800,	//!< ������ɫ
	
	TEXT_ALIGN_LEFT			=0x10000000,	//!< ˮƽ�����
	TEXT_ALIGN_CENTER			=0x20000000,	//!< ˮƽ���ж���
	TEXT_ALIGN_RIGHT			=0x40000000,	//!< ˮƽ�Ҷ���
	TEXT_ALIGN_MASK			=0x70000000,	//!< ˮƽ��������
	                    	
	TEXT_VALIGN_TOP			=0x01000000,	//!< ��ֱ�϶���
	TEXT_VALIGN_CENTER		=0x02000000,	//!< ��ֱ���ж���
	TEXT_VALIGN_BOTTOM		=0x04000000,	//!< ��ֱ�¶���
	TEXT_VALIGN_MASK			=0x07000000,	//!< ��ֱ��������

	TEXT_EXSTYLE_UNDERLINE	=0x00100000,	//���»���
	TEXT_EXSTYLE_OVERLINE	=0x00200000,	//���ϻ���
	TEXT_EXSTYLE_BORDER		=0x00400000,	//�ӿ�
	TEXT_RECT_CLEAR 			=0x00800000,	//����պ���ʾ
	TEXT_LINE_NUM_MASK		=0x000F0000,	//ָ���к�(1~15)
}TEXT_TYPE;	//V1.1



typedef void (*Fun_ShowNum)(u32,char*); 


//=================================================================================


#endif

