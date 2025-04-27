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
## Overview
This C++ program offers a menu-based interface for creating and manipulating matrices stored in text files. The program includes functionality to create input/output files, load matrices from a file, and perform operations on the matrices such as identifying "surrounded" elements and finding local maxima. The user interacts with the program through a text-based menu, and the results are displayed with color-coded output in the console.

---

## File Operations

### OperationFile Structure
```cpp
typedef struct operationFile {
    string input_File;
    string output_File;
};
```
The `operationFile` structure holds the paths of the input and output files for the program.

### Global Data
```cpp
int** globalInputMatrix = nullptr;
int** globalOutputMatrix = nullptr;
int globalRows = 0;
int globalCols = 0;
operationFile globalFilePaths;
```
The program uses global data to store the matrices and file paths for input and output. 

---

## Functions Overview

### Display Functions

1. **displayFileCreation()**
   - Prompts the user for the paths of the input and output files, creates the files, and loads the input matrix into global storage.

2. **displayEnterDirectory()**
   - Allows the user to enter paths for an existing input/output file, loads the input matrix, and initializes an empty output matrix.

3. **displayStart()**
   - Builds and displays the main start menu of the program.
     
4. **displayQuit()**
   - Terminates the program.

5. **displayMainMenu()**
   - Displays the main menu, which includes options for starting the program, viewing help, or quitting.

6. **displayOperations()**
   - Displays a menu for choosing matrix operations, such as finding surrounded elements or local maxima.

7. **displayOperationPrompt()**
   - A menu prompt asking the user to perform operations on the loaded matrix.

8. **displaySurrounded()**
   - Executes the "find_surrounded" operation on the matrix and displays the resulting output matrix.

9. **displayMaxima()**
    - Placeholder function for finding and displaying local maxima (currently not implemented).

10. **displayResultMatrix()**
    - Displays the resulting matrix, using color-coding to indicate values.

11. **colorPrint()**
    - A helper function to print text with specific console colors.

---

## Matrix Operations

### Matrix Loading and Memory Management

1. **loadMatrix()**
   - Loads a matrix from a given file into dynamically allocated memory.

2. **freeMatrix()**
   - Frees the dynamically allocated memory for a matrix.

### Matrix Operations

1. **find_surrounded()**
   - Identifies "surrounded" elements in the matrix based on a threshold value. A surrounded element is one that has at least two adjacent elements greater than the threshold value.

2. **find_localMaxima()**
   - Placeholder function for identifying local maxima in the matrix (not yet implemented).

---

## File Operations

### createFile()
- Prompts the user to enter the paths of the input and output files.
- Creates a new input file with matrix dimensions and pixel data.
- Writes the matrix data to the input file.

### selectFile()
- Prompts the user to enter the paths of the input and output files.
- Loads the matrix data from the selected input file.

---

## Code Implementation

### Main Loop
```cpp
int main() {
    displayMainMenu();
    return 0;
}
```
The main function starts the program and displays the main menu.

### Menu Navigation
```cpp
IBuilder newMenu(false); // false turns off centering
vector<string> options = { "Create File", "Enter Directory", "Back" };
vector<void(*)()> functions = { displayFileCreation, displayEnterDirectory, displayMainMenu };
newMenu.push_toOptions(options);
newMenu.push_Functions(functions);
newMenu.buildMenu();
```
The menus are built using `IBuilder`, which organizes options and associated functions.

---

## Matrix Operations - Find Surrounded

### Function Logic
The `find_surrounded()` function performs the following:
1. For each element in the matrix, checks its surrounding elements (up, down, left, right, and diagonals).
2. If the required surrounding elements are greater than a user-defined threshold, the current element is considered "surrounded" and marked in the output matrix.

### Corner Cases
The function handles special cases for corner and edge elements:
- Top-left corner
- Top-right corner
- Bottom-left corner
- Bottom-right corner
- Other border elements
---
