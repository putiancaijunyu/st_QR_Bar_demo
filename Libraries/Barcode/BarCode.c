#include "BarCode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MainTask.h"
struct IntString
{
	int ch;
	char*psz;
};


#define	SETA 0
#define	SETB 1
#define	SETC 2


unsigned char	ia_Buf[4096];
int		i_LenBuf;
int		i_Ratio;

int ga2_Code128[2][207]=
{
	{
		64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
		80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
		0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
		16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
		32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
		48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
	},
	{
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
		16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
		32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
		48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
		64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
		80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
		-1,  -1,  -1,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
	},
};

void Clear()
{
	memset(ia_Buf,0,sizeof(ia_Buf));
	i_LenBuf = 0;
}

int GetEncodeLength()
{
	unsigned char *pb = (unsigned char*)ia_Buf;
	int i,iLen = 0;
	for(i=0;i<i_LenBuf;i++)
	{
		//wide is 3
		if(*pb&2) iLen += (i_Ratio-1);
		pb++;
	}
	return (iLen + i_LenBuf);
}

int GetBufferLength()
{
	return i_LenBuf;
}

unsigned char GetAt(int i) 
{
	return ia_Buf[i];
}

int GetRatio()
{
	return i_Ratio;
}

void SetRatio(int iRatio)
{
	i_Ratio=iRatio;
	if(i_Ratio<=0)	i_Ratio = 1;
}

//--Barcode39--
unsigned char* P_GetNarrowWideBarSpace39(char ch,unsigned char*pb)
{
  struct	IntString infs[]=
	{
		{'1',	"wnnwnnnnwn"},
		{'2',	"nnwwnnnnwn"},
		{'3',	"wnwwnnnnnn"},
		{'4',	"nnnwwnnnwn"},
		{'5',	"wnnwwnnnnn"},
		{'6',	"nnwwwnnnnn"},
		{'7',	"nnnwnnwnwn"},
		{'8',	"wnnwnnwnnn"},
		{'9',	"nnwwnnwnnn"},
		{'0',	"nnnwwnwnnn"},
		{'A',	"wnnnnwnnwn"},
		{'B',	"nnwnnwnnwn"},
		{'C',	"wnwnnwnnnn"},
		{'D',	"nnnnwwnnwn"},
		{'E',	"wnnnwwnnnn"},
		{'F',	"nnwnwwnnnn"},
		{'G',	"nnnnnwwnwn"},
		{'H',	"wnnnnwwnnn"},
		{'I',	"nnwnnwwnnn"},
		{'J',	"nnnnwwwnnn"},
		{'K',	"wnnnnnnwwn"},
		{'L',	"nnwnnnnwwn"},
		{'M',	"wnwnnnnwnn"},
		{'N',	"nnnnwnnwwn"},
		{'O',	"wnnnwnnwnn"},
		{'P',	"nnwnwnnwnn"},
		{'Q',	"nnnnnnwwwn"},
		{'R',	"wnnnnnwwnn"},
		{'S',	"nnwnnnwwnn"},
		{'T',	"nnnnwnwwnn"},
		{'U',	"wwnnnnnnwn"},
		{'V',	"nwwnnnnnwn"},
		{'W',	"wwwnnnnnnn"},
		{'X',	"nwnnwnnnwn"},
		{'Y',	"wwnnwnnnnn"},
		{'Z',	"nwwnwnnnnn"},
		{'-',	"nwnnnnwnwn"},
		{'.',	"wwnnnnwnnn"},
		{' ',	"nwwnnnwnnn"},
		{'*',	"nwnnwnwnnn"},
		{'$',	"nwnwnwnnnn"},
		{'/',	"nwnwnnnwnn"},
		{'+',	"nwnnnwnwnn"},
		{'%',	"nnnwnwnwnn"},
	};

	int i0,iNum0 = sizeof(infs)/sizeof(infs[0]);
	int i1 = 0;
	struct IntString *inf;
	for(i0=0;i0<iNum0;i0++)
	{
		inf = &infs[i0];
		if(inf->ch==ch)
		{
			for(i1=0;i1<10;i1++)
			{
				if(inf->psz[i1]=='w')	*pb += 2;
				if(i1%2==0)			*pb += 1;
				pb++;
			}
			return pb;
		}
	}
	return 0;
}

int Encode39(const char* pszCodeIn)
{
	int iLen = strlen(pszCodeIn);
  unsigned char* pFst;
	unsigned char* p0,*p1;
	int i;
	char* pszCode = (char*)malloc(iLen + 3);
	sprintf(pszCode,"*%s*",pszCodeIn);
//	strupr(pszCode);

	pFst = ia_Buf;
	p0 = pFst;

	iLen += 2;
	
	for(i=0;i<iLen;i++)
	{
		p1 = P_GetNarrowWideBarSpace39(pszCode[i],p0);
		if(p1==0)	return 0;
		p0=p1;
	}
	i_LenBuf = p1-pFst;
	free(pszCode);

	return 1;
}
//--Barcode39--

//--BarcodeEAN13--
int P_GetCountryCode(char ch,unsigned char* pbCountryCode)
{
	const int iV = ch-'0';
	struct IntString infs[]=
	{
		{0,	"OOOOO"},
		{1,	"OEOEE"},
		{2,	"OEEOE"},
		{3,	"OEEEO"},
		{4,	"EOOEE"},
		{5,	"EEOOE"},
		{6,	"EEEOO"},
		{7,	"EOEOE"},
		{8,	"EOEEO"},
		{9,	"EEOEO"},
	};
	if(iV<0)	return 0;
	if(iV>9)	return 0;


	memcpy(pbCountryCode,infs[iV].psz,5);

	return 1;
}

unsigned char*P_GetLeftOddParity(unsigned char*pb,char ch)
{
	const int iV = ch-'0';
	struct IntString *inf;
  int i;
	struct IntString infs[]=
	{
		{0,	"sssbbsb"},
		{1,	"ssbbssb"},
		{2,	"ssbssbb"},
		{3,	"sbbbbsb"},
		{4,	"sbsssbb"},
		{5,	"sbbsssb"},
		{6,	"sbsbbbb"},
		{7,	"sbbbsbb"},
		{8,	"sbbsbbb"},
		{9,	"sssbsbb"},
	};
	
	if(iV<0)	return 0;
	if(iV>9)	return 0;

	inf = &infs[iV];
	
	for(i=0;i<7;i++)
	{
		if(inf->psz[i]=='b')	*pb += 1;
		pb++;
	}
	return pb;
}

unsigned char* P_GetLeftEvenParity(unsigned char*pb,char ch)
{
	const int iV = ch-'0';


	struct IntString infs[]=
	{
		{0,	"sbssbbb"},
		{1,	"sbbssbb"},
		{2,	"ssbbsbb"},
		{3,	"sbssssb"},
		{4,	"ssbbbsb"},
		{5,	"sbbbssb"},
		{6,	"ssssbsb"},
		{7,	"ssbsssb"},
		{8,	"sssbssb"},
		{9,	"ssbsbbb"},
	};
	char* psz = infs[iV].psz;
	int i;
	if(iV<0)	return 0;
	if(iV>9)	return 0;
	for(i=0;i<7;i++)
	{
		if(psz[i]=='b')	*pb += 1;
		pb++;
	}
	return pb;
}

unsigned char* P_GetRightPattern(unsigned char*pb,char ch)
{
	const int iV = ch-'0';


	struct IntString infs[]=
	{
		{0,	"bbbssbs"},
		{1,	"bbssbbs"},
		{2,	"bbsbbss"},
		{3,	"bssssbs"},
		{4,	"bsbbbss"},
		{5,	"bssbbbs"},
		{6,	"bsbssss"},
		{7,	"bsssbss"},
		{8,	"bssbsss"},
		{9,	"bbbsbss"},
	};
	char*psz = infs[iV].psz;
	int i;
	if(iV<0)	return 0;
	if(iV>9)	return 0;
	for(i=0;i<7;i++)
	{
		if(psz[i]=='b')	*pb += 1;
		pb++;
	}
	return pb;
}

char P_GetCheckSumDigit(const char*pszCode)
{
	const int iLen = strlen(pszCode);
	int i,iSum=0,iItem;

	for(i=iLen;i >=1;i--)
	{
		iItem=i%2?(pszCode[i-1]-'0')*1:(pszCode[i-1]-'0')*3;
		iSum+=iItem;
	}

	iSum %= 10;
	return '0'+(10-iSum)%10;
}

int EncodeEan13(const char* pszCodeIn)
{
	unsigned char* pFst;
	unsigned char* pb;
	unsigned char iaCountryCode[6];
	int i;
	int b;

	//only allow 12 characters as input
	char szCode[14];
	const int iLen = strlen(pszCodeIn);
	if(iLen>12)
	{
		strncpy(szCode,pszCodeIn,12);
	}
	else
	{
		strcpy(szCode,pszCodeIn);
		while(strlen(szCode)<12)	strcat(szCode,"0");
	}

	pFst = ia_Buf;
	pb = pFst;

	//"bsb"-long
	*pb += 5;	pb++;
	*pb += 4;	pb++;
	*pb += 5;	pb++;

	
	b = P_GetCountryCode(szCode[0],iaCountryCode);
	if(b==0)	return 0;

	pb = P_GetLeftOddParity(pb,szCode[1]);

	
	for(i=2;i<7;i++)
	{
		if(iaCountryCode[i-2]=='O')
		{
			pb = P_GetLeftOddParity(pb,szCode[i]);
		}
		else if(iaCountryCode[i-2]=='E')
		{
			pb=P_GetLeftEvenParity(pb,szCode[i]);
		}
	}

	//"sbsbs"-long
	*pb += 4;	pb++;
	*pb += 5;	pb++;
	*pb += 4;	pb++;
	*pb += 5;	pb++;
	*pb += 4;	pb++;

	for(i=7;i<12;i++)
	{
		pb = P_GetRightPattern(pb,szCode[i]);
	}

	i = P_GetCheckSumDigit(szCode);
	pb = P_GetRightPattern(pb,(char)i);

	//"bsb"-long
	*pb += 5;	pb++;
	*pb += 4;	pb++;
	*pb += 5;	pb++;

	i_LenBuf = pb-pFst;

	return 1;
}
//--BarcodeEAN13--

//--Barcode128--
int GetCheckDigit(const int iSet,char* pszCode)
{
	int	iSum=0,iCurSet=0,iChar128,iCharNext,iWeight,iPosition;
	int iNum;

	iCurSet = iSet;
	if(iSet==SETA)
	{
		iSum = 103;
	}
	else 
		if(iSet==SETB)
		{
			iSum = 104;
		}
		else 
			if(iSet==SETC)
			{
				iSum = 105;
			}

			iPosition = 0;
			iWeight = 1;

			iNum = strlen(pszCode);
			while(iPosition<iNum)
			{
				if(iCurSet==SETC)
				{
					if(ga2_Code128[SETA][pszCode[iPosition]]==101)
					{
						iChar128 = 101;
						iSum += (iWeight*iChar128);

						iPosition++;
						iWeight++;
						iCurSet = SETA;
					}
					else if(ga2_Code128[SETA][pszCode[iPosition]]==100)
					{
						iChar128 = 100;
						iSum += (iWeight*iChar128);
						iPosition++;
						iWeight++;
						iCurSet = SETB;
					}
					else 
						if(ga2_Code128[SETA][pszCode[iPosition]]==102)
						{
							iChar128 = 102;
							iSum += (iWeight*iChar128);
							iPosition++;
							iWeight++;
						}
						else
						{
							char chT = pszCode[iPosition+2];
							pszCode[iPosition+2] = 0;
							iChar128 = atol(&pszCode[iPosition]);
							pszCode[iPosition+2] = chT;

							iSum += (iWeight*iChar128);
							iPosition += 2;
							iWeight++;
						}
				}
				else 
				{
					int iTemp2 = pszCode[iPosition];
					if(iTemp2<-1)	iTemp2 = iTemp2&255;

					iChar128 = ga2_Code128[iCurSet][iTemp2];

					iSum += (iWeight*iChar128);

					iPosition++;
					iWeight++;

					if(iCurSet==SETA)
					{
						if(iChar128==100)
							iCurSet = SETB;
						else if(iChar128==99)
							iCurSet = SETC;
					}
					else 
						if(iCurSet==SETB)
						{
							if(iChar128==101)		iCurSet = SETA;
							else if(iChar128==99)	iCurSet = SETC;
						}
						else 
							if(iChar128==98)
							{
								if(iCurSet==SETA)
									iCharNext = ga2_Code128[SETB][pszCode[iPosition]];
								else
									iCharNext = ga2_Code128[SETA][pszCode[iPosition]];

								iSum += (iWeight*iCharNext);
								iPosition++;
								iWeight++;
							}
				}
			}
			return iSum%103;
}

unsigned char* P_GetBarSpace128(unsigned char* pb,int iV)
{
	struct IntString infs[]=
	{
		{0,		"bbsbbssbbss"},
		{1,		"bbssbbsbbss"},
		{2,		"bbssbbssbbs"},
		{3,		"bssbssbbsss"},
		{4,		"bssbsssbbss"},
		{5,		"bsssbssbbss"},
		{6,		"bssbbssbsss"},
		{7,		"bssbbsssbss"},
		{8,		"bsssbbssbss"},
		{9,		"bbssbssbsss"},
		{10,	"bbssbsssbss"},
		{11,	"bbsssbssbss"},
		{12,	"bsbbssbbbss"},
		{13,	"bssbbsbbbss"},
		{14,	"bssbbssbbbs"},
		{15,	"bsbbbssbbss"},
		{16,	"bssbbbsbbss"},
		{17,	"bssbbbssbbs"},
		{18,	"bbssbbbssbs"},
		{19,	"bbssbsbbbss"},
		{20,	"bbssbssbbbs"},
		{21,	"bbsbbbssbss"},
		{22,	"bbssbbbsbss"},
		{23,	"bbbsbbsbbbs"},
		{24,	"bbbsbssbbss"},
		{25,	"bbbssbsbbss"},
		{26,	"bbbssbssbbs"},
		{27,	"bbbsbbssbss"},
		{28,	"bbbssbbsbss"},
		{29,	"bbbssbbssbs"},
		{30,	"bbsbbsbbsss"},
		{31,	"bbsbbsssbbs"},
		{32,	"bbsssbbsbbs"},
		{33,	"bsbsssbbsss"},
		{34,	"bsssbsbbsss"},
		{35,	"bsssbsssbbs"},
		{36,	"bsbbsssbsss"},
		{37,	"bsssbbsbsss"},
		{38,	"bsssbbsssbs"},
		{39,	"bbsbsssbsss"},
		{40,	"bbsssbsbsss"},
		{41,	"bbsssbsssbs"},
		{42,	"bsbbsbbbsss"},
		{43,	"bsbbsssbbbs"},
		{44,	"bsssbbsbbbs"},
		{45,	"bsbbbsbbsss"},
		{46,	"bsbbbsssbbs"},
		{47,	"bsssbbbsbbs"},
		{48,	"bbbsbbbsbbs"},
		{49,	"bbsbsssbbbs"},
		{50,	"bbsssbsbbbs"},
		{51,	"bbsbbbsbsss"},
		{52,	"bbsbbbsssbs"},
		{53,	"bbsbbbsbbbs"},
		{54,	"bbbsbsbbsss"},
		{55,	"bbbsbsssbbs"},
		{56,	"bbbsssbsbbs"},
		{57,	"bbbsbbsbsss"},
		{58,	"bbbsbbsssbs"},
		{59,	"bbbsssbbsbs"},
		{60,	"bbbsbbbbsbs"},
		{61,	"bbssbssssbs"},
		{62,	"bbbbsssbsbs"},
		{63,	"bsbssbbssss"},
		{64,	"bsbssssbbss"},
		{65,	"bssbsbbssss"},
		{66,	"bssbssssbbs"},
		{67,	"bssssbsbbss"},
		{68,	"bssssbssbbs"},
		{69,	"bsbbssbssss"},
		{70,	"bsbbssssbss"},
		{71,	"bssbbsbssss"},
		{72,	"bssbbssssbs"},
		{73,	"bssssbbsbss"},
		{74,	"bssssbbssbs"},
		{75,	"bbssssbssbs"},
		{76,	"bbssbsbssss"},
		{77,	"bbbbsbbbsbs"},
		{78,	"bbssssbsbss"},
		{79,	"bsssbbbbsbs"},
		{80,	"bsbssbbbbss"},
		{81,	"bssbsbbbbss"},
		{82,	"bssbssbbbbs"},
		{83,	"bsbbbbssbss"},
		{84,	"bssbbbbsbss"},
		{85,	"bssbbbbssbs"},
		{86,	"bbbbsbssbss"},
		{87,	"bbbbssbsbss"},
		{88,	"bbbbssbssbs"},
		{89,	"bbsbbsbbbbs"},
		{90,	"bbsbbbbsbbs"},
		{91,	"bbbbsbbsbbs"},
		{92,	"bsbsbbbbsss"},
		{93,	"bsbsssbbbbs"},
		{94,	"bsssbsbbbbs"},
		{95,	"bsbbbbsbsss"},
		{96,	"bsbbbbsssbs"},
		{97,	"bbbbsbsbsss"},
		{98,	"bbbbsbsssbs"},
		{99,	"bsbbbsbbbbs"},
		{100,	"bsbbbbsbbbs"},
		{101,	"bbbsbsbbbbs"},
		{102,	"bbbbsbsbbbs"},
		//{103,	"bbsbsbbbbss"},
		{103,	"bbsbssssbss"},
		{104,	"bbsbssbssss"},
		{105,	"bbsbssbbbss"},
		{106,	"bbsssbbbsbsbb"},
	};	

	int i;
	struct IntString *inf;
	if(iV<0)	return 0;
	if(iV>106)	return 0;
	inf=&infs[iV];
	for(i=0;i<11;i++)
	{
		if(inf->psz[i]=='b')	*pb += 1;
		pb++;
	}
	if(iV==106)	
	{
		*pb += 1;	
		pb++;
		*pb += 1;	
		pb++;
	}
	return pb;
}

int P_Encode128(char*pszCode,const int iSetIn)
{
	
	unsigned char* pFst = ia_Buf;
	unsigned char* pb = pFst;
	int iCheckDigit;
	int iNum;
	int iChar,iCharNext;
	int iPosition = 0;
	int iSet = iSetIn;
	
	if(iSetIn==SETA)	pb = P_GetBarSpace128(pb,103);
	else 
	if(iSetIn==SETB)	pb = P_GetBarSpace128(pb,104);
	else					pb = P_GetBarSpace128(pb,105);
	if(pb==0)	return 0;

	iCheckDigit = GetCheckDigit(iSetIn,pszCode);
	iNum = strlen(pszCode);



	while(iPosition<iNum)
	{
		if(iSet==SETC)
		{
			if(ga2_Code128[SETA][pszCode[iPosition]]==101)
			{
				pb = P_GetBarSpace128(pb,101);
				iPosition++;
				iSet = SETA;
			}
			else if(ga2_Code128[SETA][pszCode[iPosition]]==100)
			{
				pb = P_GetBarSpace128(pb,100);
				iPosition++;
				iSet =  SETB;
			}	
			else if(ga2_Code128[SETA][pszCode[iPosition]]==102)
			{
				pb = P_GetBarSpace128(pb,100);
				iPosition++;
			}
			else
			{
				char chT = pszCode[iPosition+2];
				pszCode[iPosition+2] = 0;
				iChar = atoi(&pszCode[iPosition]);
				pszCode[iPosition+2] = chT;

				pb = P_GetBarSpace128(pb,iChar);
				if(pb==0)return 0;
				iPosition += 2;
			}	
		}
		else
		{
			int iTemp2 = pszCode[iPosition];
			if(iTemp2<-1)iTemp2 = iTemp2&255;

			iChar = ga2_Code128[iSet][iTemp2];
			pb = P_GetBarSpace128(pb,iChar);

			if(pb==0)return 0;
			iPosition++;
			if(iSet== SETA)
			{
				if(iChar==100)	iSet= SETB;
				else if(iChar==99)	iSet= SETC;
			}
			else if(iSet== SETB)
			{
				if(iChar==101)	iSet= SETA;
				else if(iChar==99)	iSet= SETC;
			}
			else if(iChar==98)
			{
				if(iSet== SETA)
					iCharNext = ga2_Code128[ SETB][pszCode[iPosition]];
				else
					iCharNext = ga2_Code128[ SETA][pszCode[iPosition]];

				pb = P_GetBarSpace128(pb,iChar);
				if(pb==0)return 0;
				iPosition++;
			}	
		}
	}

	pb = P_GetBarSpace128(pb,iCheckDigit);
	if(pb==0)return 0;
	pb = P_GetBarSpace128(pb,106);
	i_LenBuf = pb-pFst;

	return 1;
}

int Encode128A(const char* pszCode)	
{
	return P_Encode128((char*)pszCode, SETA);
}

int Encode128B(const char* pszCode)	
{
	return P_Encode128((char*)pszCode, SETB);
}

int Encode128C(const char* pszCode)	
{
	return P_Encode128((char*)pszCode, SETC);
}
//--Barcode128--

int DrawBarcode(int codeType,int left,int top,int right,int bottom,char* data)
{
	 
	int i_Ratio = 3;
	int res = -1;
	int iPenW = 1;
	int width = right - left;								
	int dataLen = strlen(data);
	float fPenW = 0.0;
	int subCnt = 4;
	unsigned char *pb;
	int i0,iNum0;
	unsigned char bBar;
	int i1,iNum1;
	int iY;
	COLORREF clrBar,clrSpace;
	if (dataLen<1)
	{
		return -1;
	}
	Clear();
	switch (codeType)
	{
	case CODE39:
		res = Encode39(data);
		iPenW = width/(15*(dataLen+2)+(dataLen-1));			//code39每个字符都有15条线 前后有标记字符* 每个数据字符间隔一个空白线条
		fPenW = width/(15*(dataLen+2)+(dataLen-1));
		if ((fPenW-iPenW)<0.1 && iPenW>1)
		{
			iPenW -= 1;
		}
		width = width - iPenW*15*(dataLen+2) - (dataLen-1);
		left += width/2 - 5;
		break;
	case CODEEAN_13:
		res = EncodeEan13(data);
		iPenW = width/95;									//CODEEAN_13每个字符都有95条线
		width -= iPenW*95;
		left += width/2;
		subCnt = 10;
		break;
	case CODE128A:
		res = Encode128A(data);
		fPenW = (float)width/71.99884;						//像素转换成英寸 72dpi 1厘米=28.346像素 1 英寸＝2.54 厘米
		fPenW = (float)fPenW/(11*dataLen+35);				//转换公式 L=(11C+35)X L:条码宽带，不包括静止区，英寸为单位 C:数据长度 X:线条宽度，以英寸为单位
		iPenW =	fPenW * 71.99884;
		if (iPenW<1)
		{
			iPenW = 1;
		}
		width -= iPenW*(11*dataLen+35);
		left += width/2 + 2;
		break;
	case CODE128B:											
		res = Encode128B(data);
		res = Encode128A(data);
		fPenW = (float)width/71.99884;						//像素转换成英寸 72dpi 1厘米=28.346像素 1 英寸＝2.54 厘米
		fPenW = (float)fPenW/(11*dataLen+35);				//转换公式 L=(11C+35)X L:条码宽带，不包括静止区，英寸为单位 C:数据长度 X:线条宽度，以英寸为单位
		iPenW =	fPenW * 71.99884;
		if (iPenW<1)
		{
			iPenW = 1;
		}
		width -= iPenW*(11*dataLen+35);
		left += width/2 + 2;
		break;
	case CODE128C:											
		res = Encode128C(data);
		fPenW = (float)width/71.99884;						//像素转换成英寸 72dpi 1厘米=28.346像素 1 英寸＝2.54 厘米
		fPenW = (float)fPenW/(5.5*dataLen+35);				//转换公式 L=(5.5C+35)X L:条码宽带，不包括静止区，英寸为单位 C:数据长度 X:线条宽度，以英寸为单位
		iPenW =	fPenW * 71.99884;								
		if (iPenW<1)
		{
			iPenW = 1;
		}
		width -= iPenW*(5.5*dataLen+35);
		left += width/2 + 2;
		break;
	}
	if (res != 1)
	{
		return -1;
	}

	pb = ia_Buf;
	iNum0 = i_LenBuf;

	clrBar	= RGB(0,0,0);
	clrSpace = RGB(255,255,255);

	for(i0=0;i0<iNum0;i0++)
	{
		bBar	= *pb&0x01;
		iNum1	= (*pb&0x02)?i_Ratio:1;
		iY		= (*pb&0x04)?bottom:(bottom - subCnt);
		for(i1=0;i1<iNum1;i1++)
		{
			//根据需要采用其他平台GDI画线
		//	pvSetLineStyle(0xffff, iPenW);
			GUI_SetPenSize(iPenW);
			if(bBar)	GUI_SetColor(clrBar);
			else		GUI_SetColor(clrSpace);

			GUI_DrawLine(left,top,left,iY);

			left += iPenW;
		}
		pb++;
	}
}