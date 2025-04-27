#include "InterfaceBuilder.h"

void IBuilder::clearScreen()
{
	system("cls");
}

void IBuilder::displayMenu(vector<string> menuData, 
						int selection, 
						int w,
						int h)
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
			pos_Y + i) : setCursorPosition(0, i);
		if (i == selection) {
			s_TxtColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // red bg, white text
			cout << "[" << menuData[i] << "]";
			s_TxtColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
		}
		else {
			s_TxtColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << " " << menuData[i] << " ";
		}
		
	}
}

void IBuilder::setCursorPosition(int x, int y)
{
	COORD pos = {*(SHORT*)&x, *(SHORT*)&y}; // cast to shorts, *see wincontypes.h 

	//sCCP takes  HANDLE and COORD arguments
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void IBuilder::setCentering(bool c)
{
	isCentered = c;
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

void IBuilder::push_Functions(void(*func)())
{
	menuFunctions.push_back(func);
}

void IBuilder::push_Functions(vector<void(*)()> f)
{
	menuFunctions = f;
}


void IBuilder::buildMenu()
{
	int selected = 0;
	int maxSize = _get_len_FromOptions();
	int prev_W = -1, prev_H = -1;
	int lastSelection = -1;
	int width, height;
	while (true) {
		width = getConsoleWidth();
		height = getConsoleHeight();

		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {
				key = _getch();

				if (key == UP_ARROW) {
					selected = (selected <= 0) ? maxSize - 1 : selected - 1;
				}
				else if (key == DOWN_ARROW) {
					selected = (selected + 1) % maxSize;
				}
			}
			else if (key == ENTER_KEY) {
				clearScreen();
				menuFunctions[selected]();
				system("pause");

				lastSelection = -1; // force redraw
			}
		}

		if (selected != lastSelection || width != prev_W || height != prev_H) {
			clearScreen();
			displayMenu(menuOptions, selected, width, height);
			lastSelection = selected;
			prev_W = width;
			prev_H = height;
		}

		Sleep(50);
	}
}


IBuilder::IBuilder() { isCentered = true; }

IBuilder::IBuilder(bool center) : isCentered(center)
{}

IBuilder::IBuilder(vector<string> data) : menuOptions(data)
{
	isCentered = true;
}
