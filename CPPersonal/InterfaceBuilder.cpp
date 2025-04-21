#include "InterfaceBuilder.h"

void IBuilder::clearScreen()
{
	system("cls");
}

void IBuilder::buildMenu(vector<string> menuData, 
						int selection, 
						int w,
						int h, 
						bool isCentered=true)
{
	int pos_X = w, pos_Y = h; //centered X, and Y

	if (isCentered) {
		pos_X = (w / 2);
		pos_Y = (h / 2) - 1;
	}
	for (int i = 0; i < menuData.size(); i++)
	{
		//if the centering is enabled, then the menu will print centered
		isCentered ? setCursorPosition(pos_X - (menuData[i].length() + 2) / 2, 
			pos_Y + i) : setCursorPosition(pos_X, pos_Y + i);

		
	}
}

void IBuilder::setCursorPosition(int x, int y)
{
	COORD pos = {*(SHORT*)&x, *(SHORT*)&y}; // cast to shorts, *see wincontypes.h 

	//sCCP takes  HANDLE and COORD arguments
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void IBuilder::s_TxtColor(WORD attributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);

}

int IBuilder::getConsoleWidth() const
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
	return (bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1);
}

int IBuilder::getConsoleHeight() const
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
	return (bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1);
}

void IBuilder::push_toOptions(vector<string> items)
{	
	//allows the user to choose what the menus actually say
	menuOptions = items;

	return;
}

size_t IBuilder::_get_len_FromOptions() const { return menuOptions.size();}



IBuilder::IBuilder(){}

IBuilder::IBuilder(vector<string> data) : menuOptions(data)
{}
