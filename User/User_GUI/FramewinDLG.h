#ifndef __FRAMEWINDLG_H
#define __FRAMEWINDLG_H
#include "DIALOG.h"
#define BUTTON_CLICK_SPEED        600
#define BUTTON_CLICK_DELAY        750
#define DEFAULT_WIDGET_EFFECT     (&WIDGET_Effect_3D2L)

#define MAIN_BKCOLOR              0xD0D0D0
#define MAIN_TEXTCOLOR            0x000000
#define MAIN_FONT                 (&GUI_FontYahei)
#define MAIN_BORDER               10
#define MAIN_TITLE_HEIGHT         10
//#define MAIN_LOGO_BITMAP          (&bmLogo_armflySmall)
#define MAIN_LOGO_OFFSET_X        0
#define MAIN_LOGO_OFFSET_Y        0

#define FRAME_BKCOLOR             0xB0B0B0
#define FRAME_TEXTCOLOR           0x000000
//#define FRAME_FONT                (&GUI_FontYahei)
#define FRAME_EFFECT              (&WIDGET_Effect_3D2L)
#define FRAME_BORDER              FRAME_EFFECT->EffectSize
#define FRAME_WIDTH               (LCD_GetXSize() - (FRAME_BORDER * 2) - (MAIN_BORDER * 2))
#define FRAME_HEIGHT              (LCD_GetYSize() - (FRAME_BORDER * 2) - (MAIN_BORDER + MAIN_TITLE_HEIGHT))

#define FRAME_BUTTON_BKCOLOR0     0xB8B8B8              /* Unpressed */
#define FRAME_BUTTON_BKCOLOR1     0xE0E0E0              /* Pressed   */
#define FRAME_BUTTON_BKCOLOR2     0xC0C0C0              /* Disabled  */
#define FRAME_BUTTON_COLOR0       0x000000              /* Unpressed */
#define FRAME_BUTTON_COLOR1       0x000000              /* Pressed   */
//#define FRAME_BUTTON_FONT         (&GUI_FontYahei)
#define FRAME_BUTTON_EFFECT       (&WIDGET_Effect_3D2L)

extern void _DeleteFrame(void) ;
extern WM_HWIN _CreateFrame(WM_CALLBACK* cb) ;
extern void _PaintFrame(void) ;
extern void _cbDialog_WatchFace(WM_MESSAGE * pMsg) ;
extern void _cbDialog_Applist(WM_MESSAGE * pMsg);
extern void _cbDialog_BarCode(WM_MESSAGE * pMsg);
extern void _cbDialog_QRCode(WM_MESSAGE * pMsg);
extern WM_HWIN _CreateButton(WM_HWIN hParent, const char* pText, int Id, int x, int y, int w, int h, unsigned TextId) ;
extern void CreateFramewin_Applist(WM_MESSAGE * pMsg);

extern void FramewinDLG_BarCode_init(void);
#endif

