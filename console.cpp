#include <stdio.h>
#include "console.h"
void clreol( ) {
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;
    FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
    info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
    gotoXY (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}
void clrscr() {
	system("cls");
}
void gotoXY (int column, int line){
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int whereX(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
int whereY(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
void textColor (int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void setCursor(bool visible, DWORD size) {
	if(size == 0)  size = 20;	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void setBGColor(int color){
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    int wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

