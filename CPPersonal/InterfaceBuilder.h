#pragma once
#include<windows.h>
#include<vector>
#include<string>
#include<iostream>


#define UP_ARROW    72
#define DOWN_ARROW  80
#define ENTER_KEY   13

using namespace std;


class IBuilder {
private:
	int height, width;
	vector<string> menuOptions;

	void clearScreen();
	
public:
	void buildMenu(vector<string> menuData, 
					int selection, 
					int w, 
					int h, 
					bool);
	void setCursorPosition(int x, int y);
	void s_TxtColor(WORD attributes);


	int getConsoleWidth() const;
	int getConsoleHeight() const;


	void push_toOptions(vector<string>);
	size_t _get_len_FromOptions() const;
	

	IBuilder();
	IBuilder(vector<string>);
};