#include "../classes/InterfaceBuilder.h"

using namespace std;


void displayFileCreation();
void displayEnterDirectory();
void displayStart();
void displayHelp();
void displayQuit();
void displayMainMenu();

int main() {
	displayMainMenu();

	return 0;
}

void displayFileCreation() {
	cout << "File at: " << endl;
	return;
}

void displayEnterDirectory() {
	cout << "Enter directory: " << endl;
	return;

}

void displayStart() {
	IBuilder newMenu(false);
	vector<string> options = { "Create File", "Enter Directory", "Quit" };
	vector<void(*)()> functions = {displayFileCreation, displayEnterDirectory, displayMainMenu};
	newMenu.push_toOptions(options);
	newMenu.push_Functions(functions);

	newMenu.buildMenu();

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

void displayMainMenu()
{
	IBuilder menu;
	vector<string> options = { "Start Program", "Help", "Quit" };
	vector<void(*)()> functions = { displayStart, displayHelp, displayQuit };

	menu.push_toOptions(options);
	menu.push_Functions(functions);

	menu.buildMenu();

}
