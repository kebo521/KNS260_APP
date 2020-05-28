#ifndef _KS_UI_
#define _KS_UI_

//===============色彩参数定义========================================

//-----------------S260定义----------------------------
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


typedef void (*FunFillColour)(A_RGB*,int,int);		//色彩填充函数定义(data,w,h)
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
 * GUI支持的图像格式定义
 */
typedef struct
{
	u16					w;				//!< 图像宽
	u16					h;				//!< 高
	u16					lineByte;		//每个行所占字节数
	u16					pointBit;		//每个点所占位数
	u8*					data;			
}IMAGE;									

typedef struct _GuiWindow{
	int left;
	int top;
	int width;
	int height;
	//---------------上面同RECTL-------------------------------------
	struct _GuiWindow *pChild;	//父一个窗口
	struct _GuiWindow *pParent;	//子窗口
	struct _GuiWindow *pNext;	//子窗口....
	
	A_RGB* 		wBack;	//Window 背景色，无 可借用复窗口还原
	A_RGB* 		widget;	//用结构体后面的空间不需要释放，Window 鍏宠仈鐢诲竷鎸囬拡
} GuiWindow,*LPGuiWindow;
//extern GuiWindow UI_screen;
//===============小图片小压缩==============
typedef struct{
	u8		w,h;
	u8		byteLine;	//单行字节数
	u8		MaxIn;		//单像素字节数
	A_RGB	Index[16];
	//u8 bitData[0];
} buffmap_bit;

//==============大图片高压缩==================
typedef struct{
	char head[4];	//"clz"
	u16 w,h;
	u8	sf;		//扫描方向,01 横向，02 纵向，03 旋转
	u8	cl;		//单像素字节数	
	u16 IndexMax;	//
	u32 idmax;	//idmax = 0,没有索引
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

	int (*mapbit_uzip)(buffmap_bit*,IMAGE*);	//(buffmap_bit* pInCLF,IMAGE *pOutMap) ,pOutMap->data 可以带空间，内部有判断
	int (*map2_uzip)(filemap_FZ*,IMAGE*);	//(filemap_FZ* pInCLF,IMAGE *pOutMap)
	int (*bitmapLoad)(const char*,IMAGE*);	//(const char* filename,IMAGE *pOutMap)	//打开图片文件
	void (*bitmapDestroy)(IMAGE*);	//(IMAGE* pBitMap)
}API_UI_Def;
extern API_UI_Def*			pUiFun;

#endif

