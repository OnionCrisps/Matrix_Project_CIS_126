#include "../classes/InterfaceBuilder.h"

using namespace std;

void displayStart() {
	cout << "Start" << endl;
	return;
}
void displayHelp() {
	cout << "Help" << endl;
	return;
}

void displayQuit() {
	cout << "Quit" << endl;
	return;
}

int main() {

	IBuilder menu;

	vector<string> options = { "Start Program", "Help", "Quit" };
	vector<void(*)()> functions = { displayStart, displayHelp, displayQuit };

	menu.push_toOptions(options);
	menu.push_Functions(functions);

	menu.buildMenu();

	return 0;
}
