# CPPersonal

# 🧱 IBuilder Class Documentation

## 📚 Overview

`IBuilder` is a Windows-only C++ class designed to manage and display console-based interactive menus.  
It's perfect for CLI tools, games, utilities, or dev environments where the user navigates via arrow keys and selects options with Enter.

---

## 📦 Class Members

### 🔒 Private Members

```cpp
vector<string> menuOptions;
void clearScreen();
```
- `menuOptions`: Stores the list of menu option strings.
- `clearScreen()`: Clears the console screen.

---

## 🛠️ Public Methods

### IBuilder()

```cpp
IBuilder();
```
Default constructor. Initializes an empty builder.

---

### IBuilder(vector<string> menuData)

```cpp
IBuilder(vector<string> menuData);
```
Constructor that sets up the builder with an initial list of menu options.

---

### void buildMenu(vector<string> menuData, int selection, int w, int h, bool highlight)

```cpp
void buildMenu(vector<string> menuData, int selection, int w, int h, bool highlight);
```
Builds and displays a visual menu on the console.

- **menuData**: Vector of menu option strings.  
- **selection**: Index of the currently selected option.  
- **w, h**: X and Y screen position to display the menu.  
- **highlight**: Whether to highlight the currently selected item.

---

### void setCursorPosition(int x, int y)

```cpp
void setCursorPosition(int x, int y);
```
Moves the console cursor to a specific position `(x, y)` using the Windows API.

---

### void s_TxtColor(WORD attributes)

```cpp
void s_TxtColor(WORD attributes);
```
Sets the console text color using `WORD` color attributes.

Example attributes:
- `FOREGROUND_RED`
- `FOREGROUND_GREEN`
- `FOREGROUND_BLUE`  
Combine using bitwise OR: `FOREGROUND_RED | FOREGROUND_INTENSITY`

---

### int getConsoleWidth() const

```cpp
int getConsoleWidth() const;
```
Returns the current console window width.

---

### int getConsoleHeight() const

```cpp
int getConsoleHeight() const;
```
Returns the current console window height.

---

### void push_toOptions(vector<string> newOptions)

```cpp
void push_toOptions(vector<string> newOptions);
```
Adds new strings to the internal `menuOptions` list.

---

### size_t _get_len_FromOptions() const

```cpp
size_t _get_len_FromOptions() const;
```
Returns the number of options stored in `menuOptions`.

---

## 🎯 Keyboard Constants

```cpp
#define UP_ARROW    72
#define DOWN_ARROW  80
#define ENTER_KEY   13
```
These define key codes typically returned by `_getch()` from `<conio.h>`.

---

## 📚 Dependencies

```cpp
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
```
- `<windows.h>`: For console manipulation and cursor positioning.  
- `<vector>`, `<string>`: To store menu options.  
- `<iostream>`: For console I/O.

---

    return 0;
}
```

---
