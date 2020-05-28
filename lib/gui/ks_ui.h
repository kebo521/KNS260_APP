#ifndef _KS_UI_
#define _KS_UI_

//===============ɫ�ʲ�������========================================

//-----------------S260����----------------------------
typedef struct {
	uint16_t r:5;
	uint16_t g:6;
	uint16_t b:5;
} XuiColor;

typedef uint16_t  			A_RGB;		// <= RGB_CURR
#define	RGB_CURR(r,g,b)		((((b)&0xF8)<<8)|(((g)&0xFC)<<3)|((r)>>3))	//(u32)(XuiColor)(b,g,r,0xff))
#define RGB565_CLEAR		0x0000		// Transparent color

#define SCREEN_LINE_MAX		20		// Transparent color


typedef union {
  A_RGB		argb;
  XuiColor	color;
}GuiColor;


typedef void (*FunFillColour)(A_RGB*,int,int);		//ɫ����亯������(data,w,h)
//=====================================================================================================
typedef struct{
  int left;
  int top;
} POINT, *PPOINT;

typedef struct{
  int left;
  int top;
  int width;
  int height;
}RECTL,*LPRECTL;

/**
 * GUI֧�ֵ�ͼ���ʽ����
 */
typedef struct
{
	u16					w;				//!< ͼ���
	u16					h;				//!< ��
	u16					lineByte;		//ÿ������ռ�ֽ���
	u16					pointBit;		//ÿ������ռλ��
	u8*					data;			
}IMAGE;									

typedef struct _GuiWindow{
	int left;
	int top;
	int width;
	int height;
	//---------------����ͬRECTL-------------------------------------
	struct _GuiWindow *pChild;	//��һ������
	struct _GuiWindow *pParent;	//�Ӵ���
	struct _GuiWindow *pNext;	//�Ӵ���....
	
	A_RGB* 		wBack;	//Window ����ɫ���� �ɽ��ø����ڻ�ԭ
	A_RGB* 		widget;	//�ýṹ�����Ŀռ䲻��Ҫ�ͷţ�Window 关联画布指针
} GuiWindow,*LPGuiWindow;
//extern GuiWindow UI_screen;
//===============СͼƬСѹ��==============
typedef struct{
	u8		w,h;
	u8		byteLine;	//�����ֽ���
	u8		MaxIn;		//�������ֽ���
	A_RGB	Index[16];
	//u8 bitData[0];
} buffmap_bit;

//==============��ͼƬ��ѹ��==================
typedef struct{
	char head[4];	//"clz"
	u16 w,h;
	u8	sf;		//ɨ�跽��,01 ����02 ����03 ��ת
	u8	cl;		//�������ֽ���	
	u16 IndexMax;	//
	u32 idmax;	//idmax = 0,û������
	u32 rgbId[0];
	//bitmap_term data[0];
} filemap_FZ;


typedef struct _API_UI	
{
	char Mask[4]; 	// "UI"
	int (*open)(int,char **);	//(int argc,char **argv)
	void (*close)(void);

	LPGuiWindow (*RootCanvas)(void);
	LPGuiWindow (*StatusbarCanvas)(void);
	void (*ShowWindow)(GuiWindow *,int,int);	//GuiWindow *,int show, int flag
	int (*ClearArea)(GuiWindow *,RECTL*); //(GuiWindow *window,RECTL* pRect)
	void (*DestroyWindow)(GuiWindow *);

	void (*Push)(GuiWindow *,RECTL*);	//Cache area is pushed to video memory,(RECTL==NULL,Show full area)

	void (*FillRectSingLe)(GuiWindow *,RECTL*,A_RGB);	//(xywh,RGB_CURR(r,g,b))
	void (*FillRectXor)(GuiWindow *,RECTL*,A_RGB);	//(GuiWindow *pWindow,RECTL *pRect,A_RGB Color)
	void (*GetRectBuff)(GuiWindow *,RECTL*,A_RGB*);	//(GuiWindow *pWindow,RECTL *pRect,A_RGB *pRGB)
	void (*SetRectBuff)(GuiWindow *,RECTL*,A_RGB*); //(GuiWindow *pWindow,RECTL *pRect,A_RGB *pRGB)

	void (*ShowQrCode)(GuiWindow *,RECTL* ,const char*,A_RGB);	//(xywh,"Text",RGB_CURR(r,g,b))
	int (*ShowPictureFile)(GuiWindow *,RECTL *,const char *);
	void (*ShowBottomProgress)(GuiWindow *,RECTL *,int,int);	//(GuiWindow *pWindow,RECTL *pRect,int thick,int ratio) ratio (0~100)
	void (*ShowParMiddleSlide)(GuiWindow *,int); //ratio (0~100)

	int (*mapbit_uzip)(buffmap_bit*,IMAGE*);	//(buffmap_bit* pInCLF,IMAGE *pOutMap) ,pOutMap->data ���Դ��ռ䣬�ڲ����ж�
	int (*map2_uzip)(filemap_FZ*,IMAGE*);	//(filemap_FZ* pInCLF,IMAGE *pOutMap)
	int (*bitmapLoad)(const char*,IMAGE*);	//(const char* filename,IMAGE *pOutMap)	//��ͼƬ�ļ�
	void (*bitmapDestroy)(IMAGE*);	//(IMAGE* pBitMap)
}API_UI_Def;
extern API_UI_Def*			pUiFun;

#endif

