#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getConsoleHeight() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void ib_print(const string& data, int iW, int iL) {
	setCursorPosition(iW, iL);
	cout << data;
}
int main() {
	while (true)
	{
		system("cls");
		ib_print("Hey World", getConsoleWidth() / 2, getConsoleHeight() / 2);
		Sleep(1000);
	
	}
	return 0;
}