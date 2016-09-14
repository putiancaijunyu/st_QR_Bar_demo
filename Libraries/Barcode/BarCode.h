#ifndef BAR_CODE_H
#define BAR_CODE_H
#include "bsp.h"
#define CODE39			0
#define CODEEAN_13		1
#define CODE128A		2
#define CODE128B		3
#define CODE128C		4

typedef unsigned char	BYTE;
typedef unsigned long   COLORREF;
#define RGB(r,g,b)          ((unsigned long)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))

int DrawBarcode();
int EncodeDataForBarCode(int codeType,int xleft,int xtop,int xright,int xbottom,unsigned char* data);
int DrawBarcode();
#endif
