/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.28                          *
*        Compiled Jan 30 2015, 16:41:06                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "qr_encode.h"
#include "FramewinDLG.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0  (GUI_ID_USER + 0x00)
#define ID_LISTWHEEL_0  (GUI_ID_USER + 0x03)
#define QRCODE_Y 	10		//TFT二维码显示坐标y

void QREnCode(u8 *qrcode_data)
{
		EncodeData((char *)qrcode_data);
}

void DISPLAY_RENCODE_TO_TFT(u8 *qrcode_data)
{
	u8 i,j;
	u16 x,y,p;
	u8 qrencode_buff[12];			//存放LCD ID字符串
	printf("DISPLAY_RENCODE_TO_TFT!\n");
	EncodeData((char *)qrcode_data);
	GUI_SetColor(GUI_WHITE);
	GUI_FillRect(0,0,280,320);	 
	if(m_nSymbleSize*2>240)	
	{
		printf("The QR Code is too large!\n");
		return;
	}
	for(i=0;i<10;i++)
	{
		if((m_nSymbleSize*i*2)>240)	break;
	}
	p=(i-1);//*2;//点大小
	x=(150-m_nSymbleSize*p)/2;
	y=QRCODE_Y;
	for(i=0;i<m_nSymbleSize;i++)
	{
		for(j=0;j<m_nSymbleSize;j++)
		{
			//USART1_SendData(m_byModuleData[j][i]);
			if(m_byModuleData[i][j]==1)
			{
				GUI_SetColor(GUI_BLACK);
				GUI_FillRect(x+p*i,y+p*j,x+p*(i+1)-1,y+p*(j+1)-1);
			}else
			{
				GUI_SetColor(GUI_WHITE);
				GUI_FillRect(x+p*i,y+p*j,x+p*(i+1)-1,y+p*(j+1)-1);	
			}

		}
			
	}
}
//0 0 5 5
//6 6 11 11
const u8 codetest[]={//微信名片，可以去百度上搜索二维码名片 查看
"BEGIN:VCARD\r\n"
"VERSION:3.0\r\n"
"N:外星人\r\n"//名字
"TEL:13888888888\r\n"//手机号
"TEL;TYPE=WORK,VOICE:0571-88888888\r\n"//工作号码
"TEL;TYPE=HOME,VOICE:0571-66666666\r\n"//家庭号码
"NOTE:QQ:12345\r\n"//QQ号码
"EMAIL:12345@qq.com\r\n"//邮箱地址
"ORG:公司名称\r\n"//公司
"TITLE:职位名称\r\n"
"URL:http://个人主页\r\n"
"ADR;TYPE=WORK:工作地址\r\n"//地址
"ADR;TYPE=HOME:家庭住址\r\n"
"END:VCARD"
};


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 100, 0, 150, 150, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
void _cbDialog_QRCode(WM_MESSAGE * pMsg) {
	int i;
	WM_HWIN hWin=pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
			WM_SetFocus(hWin);
			break;
		case WM_PAINT:
			hWin = pMsg->hWin;
			_PaintFrame();
		  DISPLAY_RENCODE_TO_TFT((u8 *)codetest);
		case WM_TOUCH:
			if (((GUI_PID_STATE *)pMsg->Data.p)->Pressed == 1) 
			{
					_DeleteFrame();
					_CreateFrame(&_cbDialog_Applist);	
			}	
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/

WM_HWIN CreateFramewin_QRCode(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog_QRCode, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
