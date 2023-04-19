#ifndef _console_header
#define _console_header
// Color
#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15
#define default_ColorCode		7
//--------------------------------------------------------
#include <windows.h>
#include <conio.h>
void clrscr();
void clreol();
void gotoXY (int column, int line);
int whereX();
int whereY();
void textColor (int color);
void setBGColor(int color);
void setCursor(bool visible, DWORD size);
#endif
