#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>

#define UP_ARROW    72
#define DOWN_ARROW  80
#define ENTER_KEY   13

using namespace std;

vector<string> options = { "Print", "Change", "Quit" };

void setCursorPosition(int x, int y) {
    COORD pos = { *(SHORT*)&x, *(SHORT*)&y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setTextColor(WORD attributes) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

void clearScreen() {
    system("cls"); 
}

void drawMenu(int selected, int width, int height, vector<string> options) {
    //center
    int centerX = width / 2;
    int centerY = height / 2 - 1; 
   // 
    for (int i = 0; i < options.size(); i++) {
        setCursorPosition(centerX - (options[i].length() + 2) / 2, centerY + i);
        if (i == selected) {
            setTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // red bg, white text
            cout << "[" << options[i] << "]";
        }
        else {
            setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << " " << options[i] << " ";
        }
    }

    // Reset color
    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

int main() {
    int maxSize = options.size();
    int selected = 0;
    bool isRunning = true;

    int prevWidth = -1;
    int prevHeight = -1;

    while (isRunning) {
        int width = getConsoleWidth();
        int height = getConsoleHeight();

        // Only redraw if screen size changed or on input
        if (width != prevWidth || height != prevHeight) {
            clearScreen();
            drawMenu(selected, width, height, options);
            prevWidth = width;
            prevHeight = height;
        }

        if (_kbhit()) {
            int key = _getch();
            if (key == 224) {
                key = _getch();


                if (key == UP_ARROW) {
                    (selected <= 0) ? selected = maxSize : NULL;
                    --selected;
                }
                else if (key == DOWN_ARROW) {
                    selected++;
                    (selected >= maxSize) ? selected = 0 : NULL;
                }

                clearScreen();
                drawMenu(selected, width, height, options);
            }
            else if (key == ENTER_KEY) {
                clearScreen();
                
                switch (selected) {
                case 0:
                    cout << "This is: " << options[selected] << endl;
                    return 1;
                case 1:
                    cout << "This is: " << options[selected] << endl;
                    return 1;
                case 2:
                    cout << "This is: " << options[selected] << endl;
                    return 1;
                }

                system("pause");
                clearScreen();
                prevWidth = -1; // force redraw after pause
            }
        }

        Sleep(50); // prevents CPU abuse
    }

    return 0;
}
