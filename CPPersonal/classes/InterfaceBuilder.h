#pragma once
#include<windows.h>
#include<vector>
#include<string>
#include<conio.h>
#include<iostream>


#define UP_ARROW    72
#define DOWN_ARROW  80
#define ENTER_KEY   13

using namespace std;

class IBuilder {
private:
	vector<string> menuOptions;
	vector<void(*)()> menuFunctions; // VECTOR THAT HOLDS FUNCTIONS!!!!
	
	bool isCentered = true;


	void clearScreen();
	size_t _get_len_FromOptions() const;
	
public:
	void displayMenu(vector<string> menuData,
					int selection,
					int w, 
					int h);
	void setCursorPosition(int x, int y);
	void setCentering(bool);
	void s_TxtColor(WORD attributes);


	int getConsoleWidth() const;
	int getConsoleHeight() const;


	void push_toOptions(vector<string>);
	
	void push_Functions(void(*)());
	void push_Functions(vector<void(*)()>f);
	void buildMenu();

	IBuilder();
	IBuilder(bool);
	IBuilder(vector<string>);
};