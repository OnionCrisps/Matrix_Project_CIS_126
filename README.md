# Interface Builder (IBuilder)

A simple C++ console-based **Menu Builder** for Windows that allows you to easily create, display, and handle interactive text-based menus.  
Supports dynamic resizing, keyboard navigation (arrow keys + enter), custom text colors, and function callbacks tied to menu options.

---

## Features

- Centered or non-centered menu display
- Smooth arrow key navigation (up/down)
- Function binding for menu selections
- Console resize support
- Custom text color support
- Clear and simple usage

---

## Requirements

- **Windows** OS (uses Windows-specific libraries like `windows.h`, `conio.h`)
- **C++11** or higher
- Compatible compiler (Visual Studio, g++, clang on Windows)

---

## Files

- `InterfaceBuilder.h` — Main header file with the `IBuilder` class.
- `InterfaceBuilder.cpp` — Implementation file.

---

## Basic Usage

```cpp
#include "InterfaceBuilder.h"

// Example functions to bind
void sayHello() {
    cout << "Hello World!" << endl;
}

void sayBye() {
    cout << "Goodbye!" << endl;
}

int main() {
    IBuilder menu;

    // Push menu options
    menu.push_toOptions({"Say Hello", "Say Goodbye"});

    // Push corresponding functions
    menu.push_Functions({sayHello, sayBye});

    // Build and run the menu
    menu.buildMenu();

    return 0;
}
```

---

## Key Controls

- **Up Arrow**: Move selection up
- **Down Arrow**: Move selection down
- **Enter**: Select an option and execute its corresponding function

---

## Class Reference: `IBuilder`

### Constructors

- `IBuilder()`
  - Default constructor. Initializes with centered menu.

- `IBuilder(bool center)`
  - Initializes menu with centering based on `center` parameter.

- `IBuilder(vector<string> data)`
  - Initializes menu with provided options and centered alignment.


### Public Methods

- `void displayMenu(vector<string> menuData, int selection, int w, int h)`
  - Displays the menu options on screen.
  - Highlights the currently selected option.

- `void setCursorPosition(int x, int y)`
  - Sets the cursor position in the console window.

- `void setCentering(bool center)`
  - Enables or disables centering of menu items.

- `void s_TxtColor(WORD attributes)`
  - Sets the text color and attributes in the console.

- `int getConsoleWidth() const`
  - Returns the current width of the console window.

- `int getConsoleHeight() const`
  - Returns the current height of the console window.

- `void push_toOptions(vector<string> items)`
  - Sets the menu options to be displayed.

- `void push_Functions(void(*func)())`
  - Adds a single function to the list of actions.

- `void push_Functions(vector<void(*)()> functions)`
  - Adds multiple functions to the list of actions.

- `void buildMenu()`
  - Runs the interactive menu loop allowing user navigation and selection.

### Private Methods

- `void clearScreen()`
  - Clears the console screen.

- `size_t _get_len_FromOptions() const`
  - Returns the number of menu options.


---

## Customization

- `setCentering(bool)` — Set whether the menu options should be centered.
- `s_TxtColor(WORD attributes)` — Change console text color.

Example:
```cpp
menu.setCentering(false); // Left-align menu
```


---

## License

This project is released under the MIT License.

---

> Made with ❤️ for Windows console apps.

