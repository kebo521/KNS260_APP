#ifndef _UI_DISPLAY_
#define _UI_DISPLAY_

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
	u16					mline,len;				//!< 高
	u8*					pByte;			
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

extern int ui_Open(int argc,char **argv);
extern void ui_Close(void);
extern A_RGB* ui_get_screen(RECTL* pRect,int *pLineWidth);
extern void ui_screen_color(A_RGB cBack);
extern void ui_syn_push(void);

//=============================================================
extern GuiWindow *UI_RootCanvas(void);
extern GuiWindow *UI_StatusbarCanvas(void);
extern GuiWindow *UI_CreateCanvas(GuiWindow *parent, unsigned int x, unsigned int y,unsigned int width, unsigned int height);
extern void UI_Push(GuiWindow *pWindow,RECTL *pRect);
//extern void UI_CanvasSetBackground(GuiWindow *pWindow,int bgstyle,void *img,A_RGB bg);
extern void UI_DestroyWindow(GuiWindow *window);
extern int UI_ClearArea(GuiWindow *window,RECTL *pRect);
extern void UI_ShowWindow(GuiWindow *window,int show, int flag);

extern void UI_FillHitBack(A_RGB* pBack,int w,int h);
extern void UI_SetBackground(GuiWindow *pWindow,FunFillColour pFillColour);	//(u32* pOut,int width,int height)
extern void UI_ShowBackground(GuiWindow *pWindow);
extern void UI_point(GuiWindow *pWindow,int x,int y,A_RGB Inrgb);
extern void UI_line(GuiWindow *pWindow,int xs, int ys, int xe, int ye,A_RGB argb);
extern void UI_hline(GuiWindow *pWindow,int left,int top,int width,A_RGB Color);	 //horizontally line
extern void UI_vline(GuiWindow *pWindow,int left,int top,int height,A_RGB Color); //vertically line
extern void UI_FillRectSingLe(GuiWindow *pWindow,RECTL *pRect,A_RGB Color);
extern void UI_FillRectXor(GuiWindow *pWindow,RECTL *pRect,A_RGB Color);
extern void UI_GetRectBuff(GuiWindow *pWindow,RECTL *pRect,A_RGB *pRGB);
extern void UI_SetRectBuff(GuiWindow *pWindow,RECTL *pRect,A_RGB *pRGB);
extern int UI_ShowPictureFile(GuiWindow *pWindow,RECTL *prclTrg,const char *pfilePath);
extern void UI_ShowQrCode(GuiWindow *pWindow,RECTL* pRect,const char* pInfo,A_RGB Color);

extern void UI_ShowBottomProgress(GuiWindow *pWindow,RECTL *pRect,int thick,int ratio);

typedef struct _API_UI	
{
	char Mask[4]; 	// "UI"
	int (*open)(int,char **);	//(int argc,char **argv)
	void (*close)(void);

	LPGuiWindow (*RootCanvas)(void);
	LPGuiWindow (*StatusbarCanvas)(void);
	void (*ShowWindow)(GuiWindow *,int,int);	//GuiWindow *,int show, int flag
	void (*DestroyWindow)(GuiWindow *);

	void (*Push)(GuiWindow *,RECTL*);	//Cache area is pushed to video memory,(RECTL==NULL,Show full area)

	void (*FillRectSingLe)(GuiWindow *,RECTL*,A_RGB);	//(xywh,RGB_CURR(r,g,b))

	void (*ShowQrCode)(GuiWindow *,RECTL* ,const char*,A_RGB);	//(xywh,"Text",RGB_CURR(r,g,b))
	int (*ShowPictureFile)(GuiWindow *,RECTL *,const char *);
	void (*ShowBottomProgress)(GuiWindow *,RECTL *,int,int);	//(GuiWindow *pWindow,RECTL *pRect,int thick,int ratio) ratio (0~100)
	void (*ShowParMiddleSlide)(GuiWindow *,int); //ratio (0~100)
}API_UI_Def;
extern const API_UI_Def*			pUiFun;

#endif

