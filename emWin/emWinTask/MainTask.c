/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2003  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emWin/GSC Grafical user interface for embedded applications ****
emWin is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : MainTask.c
Purpose     : Main program, called from after main after initialisation
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "Main.h"
#include "LCDConf.h"
//#include "BarCode.h"
//#include "BarCode.h"
#include "FramewinDLG.h"
const unsigned char Barcodetest1[]={"6942023335667"};
/*********************************************************************
*
*       Dialog IDs
*/
#define ID_BUTTON_SETUP          1
#define ID_BUTTON_CALIBRATION    2
#define ID_BUTTON_ABOUT          3


//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 20)
extern WM_HWIN CreateFramewin_WatchFace(void);
//extern WM_HWIN CreateFramewin_Applist(void);
extern WM_HWIN CreateFramewin_BarCode(void);
extern WM_HWIN CreateFramewin_QRCode(void);
extern int DrawBarcode(int codeType,int left,int top,int right,int bottom,unsigned char* data);

static WM_HWIN    _hLastFrame;
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/*********************************************************************
*
*       Static code
*
**********************************************************************/
static void _cbBkWindow(WM_MESSAGE * pMsg) 
{
	switch (pMsg->MsgId) 
	{
		/* ???? */
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			//GUI_SetColor(u32Color);
			//GUI_DrawCircle(iWatchFaceOriginX, iWatchFaceOriginY, iWatchFaceRadius);
		//	GUI_SetTextMode(GUI_TM_TRANS);
			//GUI_SetFont(&GUI_Font8x16);
			//GUI_DispStringInRectWrap(acMessage, &rtMessage, GUI_TA_HCENTER, GUI_WRAPMODE_WORD);
			//GUI_DispStringInRectWrap(acSensor, &rtSensor, GUI_TA_HCENTER, GUI_WRAPMODE_WORD);
			//GUI_SetFont(&GUI_FontD32);
			//GUI_DispStringInRectWrap(acTime, &rtTime, GUI_TA_HCENTER, GUI_WRAPMODE_WORD);
			//DISPLAY_RENCODE_TO_TFT((u8 *)codetest);
		//  DrawBarcode(1,0,0,200,100,(unsigned char *)Barcodetest1);
		default:
			WM_DefaultProc(pMsg);
	}
}

WM_HWIN _CreateButton(WM_HWIN hParent, const char* pText, int Id, int x, int y, int w, int h, unsigned TextId) 
{
	WM_HWIN hButton;
	hButton = BUTTON_CreateEx(x, y, w, h, hParent, WM_CF_SHOW, 0, Id);
	
	BUTTON_SetText      (hButton,    pText);
//	BUTTON_SetFont      (hButton,    FRAME_BUTTON_FONT);
	BUTTON_SetBkColor   (hButton, 0, FRAME_BUTTON_BKCOLOR0);
	BUTTON_SetBkColor   (hButton, 1, FRAME_BUTTON_BKCOLOR1);
	BUTTON_SetBkColor   (hButton, 2, FRAME_BUTTON_BKCOLOR2);
	BUTTON_SetTextColor (hButton, 0, FRAME_BUTTON_COLOR0);
	BUTTON_SetTextColor (hButton, 1, FRAME_BUTTON_COLOR1);
	BUTTON_SetTextColor (hButton, 2, FRAME_BUTTON_COLOR0);
	WIDGET_SetEffect    (hButton,    FRAME_BUTTON_EFFECT);
	
	
	BUTTON_SetFocussable(hButton,    1);
	
	return hButton;
}

void _PaintFrame(void) 
{
	GUI_RECT r;
	WM_GetClientRect(&r);
	GUI_SetBkColor(FRAME_BKCOLOR);
	GUI_SetColor(FRAME_TEXTCOLOR);
//	GUI_SetFont(FRAME_FONT);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_ClearRectEx(&r);
}

WM_HWIN _CreateFrame(WM_CALLBACK* cb) 
{
	int x = 0;
	int y = 0;
	x = FRAME_BORDER + MAIN_BORDER;
	y = FRAME_BORDER + MAIN_TITLE_HEIGHT;
	_hLastFrame = WM_CreateWindowAsChild(x, y, FRAME_WIDTH, FRAME_HEIGHT, WM_HBKWIN, WM_CF_SHOW, cb, 0);
	return _hLastFrame;
}

void _DeleteFrame(void) 
{
	WM_DeleteWindow(_hLastFrame);
	_hLastFrame = 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/

void MainTask(void);
void MainTask(void) {
	
	GUI_Init();
	/*
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	*/
	
	WM_SetCallback(WM_HBKWIN, &_cbBkWindow);
	
	/*watchface*/
	_CreateFrame(&_cbDialog_WatchFace);
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_UC_SetEncodeUTF8();
	//CreateFramewin_Applist();
	while(1)
	{
		GUI_Delay(5000);
	}
	
//	CreateFramewin_WatchFace();
	
//	CreateFramewin_QRCode();
//	CreateFramewin_BarCode();

}

/*************************** End of file ****************************/

