/*
 * File:   linux_fb.h
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  linux_framebuffer
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef KS_UI_FONT_H
#define KS_UI_FONT_H




typedef struct	
{
	char Mask[4]; 	// "Fnt"
	void (*SetSysEnColor)(A_RGB,u32);	//(A_RGB ForeColor,A_RGB BackColor)
	void (*DisplaySysString)(GuiWindow*,int,int,int,char*);	//(Window£¬x,y,TEXT_TYPE,pMsg) TEXT_TYPE=TEXT_12/TEXT_16/TEXT_24
	
	int (*InitFontLib)(char*);		//(char *pfile)
	void (*DeInitFontLib)(void);	//
	void (*SetFontColor)(A_RGB,u32);	//(A_RGB fgColor,u32 bgColor) RGB_CURR , (.a)0xff000000|bgColor Îª²»Í¸Ã÷
	int (*DrawLineString)(GuiWindow*,POINT*,const char*);//Display single line of text, no automatic line breaks
	int (*DrawRectString)(GuiWindow*,RECTL*,const char*);//The specified area displays text and wraps automatically
	void (*DrawCenterString)(GuiWindow*,char*);	//(GuiWindow *pWindow,char *src)

	int (*GbkToUniCode)(u16*,int, char *); //(u16 *dest,int dest_size, char *src)
	int (*UniCodeToGbk)(char*,int,u16*,int);	//(char *dest,int dest_size, u16 *pSrc,u16 tLen)
	int (*Utf8ToGbk)(char*,int,char*);	//(char *pGbk,int dest_size,char *pUtf8)
	int (*GbkToUtf8)(char*,int,char*);	//(char *pUtf8,int dest_size,char *pGbk)
}API_FONT_Def;
extern API_FONT_Def* pFontFun;



#endif /*LINUX_FB_H*/
