#include "../classes/InterfaceBuilder.h"
#include <fstream>

using namespace std;


typedef struct operationFile {
	string input_File;
	string output_File;

};

//GLOBAL DATA
int** globalInputMatrix = nullptr;
int** globalOutputMatrix = nullptr;
int globalRows = 0;
int globalCols = 0;
operationFile globalFilePaths;


//displayFunctions
void displayFileCreation();
void displayEnterDirectory();

void displayStart();
void displayHelp();
void displayQuit();

void displayMainMenu();


void displayOperations();
void displayOperationPrompt(); // different from displaying operations asked whether u want to display ops or not

void displaySurrounded(); // differs from displayResultMatrix();
void displayMaxima();

void displayResultMatrix(int** outputMatrix, int& row, int& col);


void colorPrint(const string& data, WORD colorAttribute);
//processing functions

operationFile createFile();
operationFile selectFile();

int** loadMatrix(const string& fileName, int& rows, int& cols);
void freeMatrix(int**& matrix, int rows);

void find_surrounded(int**& inputMatrix, int**& outputMatrix, int rows, int columns);
void find_localMaxima();


//C:\\Users\\redgi\\OneDrive\\Desktop\\file.txt
//C:\\Users\\redgi\\OneDrive\\Desktop\\outfile.txt

//main loop
int main() {
	displayMainMenu();
	return 0;
}



//handle menu for file creation
void displayFileCreation() {

	freeMatrix(globalInputMatrix, globalRows);
	freeMatrix(globalOutputMatrix, globalRows);

	globalFilePaths = createFile(); // Save paths globally
	
	//loads the matrix to global storage, shared between functions
	globalInputMatrix = loadMatrix(globalFilePaths.input_File, globalRows, globalCols);

	// Create empty output matrix
	globalOutputMatrix = new int* [globalRows];
	for (int i = 0; i < globalRows; i++) {
		globalOutputMatrix[i] = new int[globalCols];
		for (int j = 0; j < globalCols; j++) {
			globalOutputMatrix[i][j] = 0; // initialize to 0
		}
	}

	displayOperationPrompt();
}

//handle menu option for already created file
void displayEnterDirectory() {
	freeMatrix(globalInputMatrix, globalRows);
	freeMatrix(globalOutputMatrix, globalRows);

	globalFilePaths = selectFile();

	//loads the matrix to global storage, shared between functions
	globalInputMatrix = loadMatrix(globalFilePaths.input_File, globalRows, globalCols);

	// Create empty output matrix
	globalOutputMatrix = new int* [globalRows];
	for (int i = 0; i < globalRows; i++) {
		globalOutputMatrix[i] = new int[globalCols];
		for (int j = 0; j < globalCols; j++) {
			globalOutputMatrix[i][j] = 0; // initialize to 0
		}
	}

	displayOperationPrompt();
	return;

}

void displayStart() { 
	//builds menu (For nathan) 
	IBuilder newMenu(false); // false turns off centering
	vector<string> options = { "Create File", "Enter Directory", "Back" };
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
	exit(0);
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

void displayOperations()
{
	IBuilder menu;
	vector<string> options = { "Find Surrounded", "Find Local Maxima", "Back", "Quit"};
	vector<void(*)()> functions = {displaySurrounded, displayMaxima, displayOperationPrompt, displayQuit};

	menu.push_toOptions(options);
	menu.push_Functions(functions);
	menu.buildMenu();
}

void displayOperationPrompt()
{
	IBuilder menu(false);
	vector<string> options = { "Perform Operations", "Back"};
	vector<void(*)()> functions = {displayOperations, displayStart};

	menu.push_toOptions(options);
	menu.push_Functions(functions);

	menu.buildMenu();
}

void displaySurrounded()
{
	find_surrounded(globalInputMatrix, globalOutputMatrix, globalRows, globalCols);
	displayResultMatrix(globalOutputMatrix, globalRows, globalCols);
}

//NATHAN
void displayMaxima()
{
	//find_localMaxima(...);
	//displayResultMatrix(...);
}

void displayResultMatrix(int** outputMatrix, int& row, int& col)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			WORD attribute = (outputMatrix[i][j] == 1 ? FOREGROUND_GREEN | BACKGROUND_GREEN:FOREGROUND_RED | BACKGROUND_RED);

			colorPrint(to_string(outputMatrix[i][j]), attribute);
		}
		cout << endl;
	}

}

void colorPrint(const string& data, WORD colorAttribute)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttribute);
	cout << data;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);

}

//Create the file
operationFile createFile()
{
	string fileLocation, outputLocation;

	do {
		cout << "Enter the name and path of the file (use \\\\ between directories): ";
		getline(cin, fileLocation); cout << endl;
	} while (empty(fileLocation));

	do {
		cout << "Enter the name and path of the output file (use \\\\ between directories): ";
		getline(cin, outputLocation); cout << endl;
	} while (empty(outputLocation));

	ofstream new_File(fileLocation), output_File(outputLocation);
	
	operationFile file_Structure;
	file_Structure.input_File = fileLocation;
	file_Structure.output_File = outputLocation;

	if (new_File.is_open()) {
		do {
			cout << "Enter the amount of rows in the color matrix: ";
			cin >> globalRows; cout << endl;
		} while (globalRows <= 2);

		do {
			cout << "Enter the amount of columns in the color matrix: ";
			cin >> globalCols; cout << endl;
		} while (globalCols <= 2);

		new_File << globalRows << endl;
		new_File << globalCols << endl;
		for (int i = 0; i < globalRows; i++) {
			for (int j = 0; j < globalCols; j++) {
				int data = 0;
				do {
					cout << "Enter pixel data for position (" << i << ", " << j << "): ";
					cin >> data; cout << "\n";
				} while (data < 0 || data > 255);
				new_File << data << " ";
			}
			new_File << endl;
		}
		new_File.close();
		cout << "\nFile created successfully!" << endl;
	}
	else { cerr << "Unable to create file!"; displayStart();}

	return file_Structure;

}

operationFile selectFile()
{
	string fileLocation=" ", outputLocation=" ";

	do {
		cout << "Enter the name and path of the file (use \\\\ between directories): ";
		getline(cin, fileLocation); cout << endl;
	} while (empty(fileLocation));

	do {
		cout << "Enter the name and path of the output file (use \\\\ between directories): ";
		getline(cin, outputLocation); cout << endl;
	} while (empty(outputLocation));

	operationFile file_Structure;
	file_Structure.input_File = fileLocation;
	file_Structure.output_File = outputLocation;
	ifstream myFile(fileLocation);

	myFile >> globalRows;
	myFile >> globalCols;

	myFile.close();

	return file_Structure;
}

//loads the matrix with the file data
int** loadMatrix(const string& filename, int& rows, int& cols)
{
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "Cannot open file: " << filename << endl;
		return nullptr;
	}

	inFile >> rows >> cols;

	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			inFile >> matrix[i][j];
		}
	}

	inFile.close();
	return matrix;
}

void freeMatrix(int**& matrix, int rows) {
	if (matrix) {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
	}
}


void find_surrounded(int**& inputMatrix, int**& outputMatrix, int rows, int columns) {
	int threshold = 0;
	do {
		cout << "Enter the threshold value (between 0 and 255): "; cin >> threshold;
	} while (threshold < 0 || threshold > 255);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int req = 0;
			//corner cases

			//TOP LEFT CORNER
			if (i == 0 && j == 0) {
				req += (inputMatrix[i + 1][j + 1] > threshold); // lower  right column if greater than threshold add 1 to it
				req += (inputMatrix[i][j + 1] > threshold); // right column
				req += (inputMatrix[i + 1][j] > threshold); // bottom column

				outputMatrix[i][j] = (req >= 2); // if req >= 2 then outputMatrix at pos (i,j) is 1, otherwise (i,j) is 0;
			}
			//TOP RIGHT CORNER

			else if (i == 0 && j == columns - 1) {
				req += (inputMatrix[i + 1][j - 1] > threshold); // lower  left column if greater than threshold add 1 to it
				req += (inputMatrix[i][j - 1] > threshold); // left column
				req += (inputMatrix[i + 1][j] > threshold); // bottom column

				outputMatrix[i][j] = (req >= 2); // if req >= 2 then outputMatrix at pos (i,j) is 1, otherwise (i,j) is 0;
			}
			//BOTTOM LEFT CORNER
			else if (i == rows - 1 && j == 0) {
				req += (inputMatrix[i - 1][j + 1] > threshold); // top right column
				req += (inputMatrix[i][j + 1] > threshold); // right column
				req += (inputMatrix[i - 1][j] > threshold); // top column

				outputMatrix[i][j] = (req >= 2);
			}

			//BOTTOM 
			else if (i == rows - 1 && j == columns - 1) {
				req += (inputMatrix[i - 1][j - 1] > threshold); //top  left column 
				req += (inputMatrix[i][j - 1] > threshold); // left column
				req += (inputMatrix[i - 1][j] > threshold); // top column

				outputMatrix[i][j] = (req >= 2);

			}

			//BORDER BUT NO CORNER:

			//TOP
			else if (i == 0 && (j > 0 && j < columns - 1)) {
				req += (inputMatrix[i + 1][j - 1] > threshold); // lowerLeft
				req += (inputMatrix[i + 1][j + 1] > threshold); // lowerRight
				req += (inputMatrix[i][j - 1] > threshold); // left column
				req += (inputMatrix[i][j + 1] > threshold); // right column
				req += (inputMatrix[i + 1][j] > threshold); // bottom column

				outputMatrix[i][j] = (req >= 4);

			}

			//BOTTOM

			else if (i == rows - 1 && (j > 0 && j < columns - 1)) {
				req += (inputMatrix[i - 1][j - 1] > threshold); //top  left column 
				req += (inputMatrix[i - 1][j + 1] > threshold); // top right column
				req += (inputMatrix[i][j - 1] > threshold); // left column
				req += (inputMatrix[i][j + 1] > threshold); // right column
				req += (inputMatrix[i - 1][j] > threshold); // top column

				outputMatrix[i][j] = (req >= 4);

			}
			// LEFT 

			else if (j == 0 && (i > 0 && i < rows -1)) {
				req += (inputMatrix[i - 1][j + 1] > threshold); // top right column
				req += (inputMatrix[i + 1][j + 1] > threshold); // lowerRight
				req += (inputMatrix[i - 1][j] > threshold); // top column
				req += (inputMatrix[i + 1][j] > threshold); // bottom column
				req += (inputMatrix[i][j + 1] > threshold); // right column

				outputMatrix[i][j] = (req >= 4);

			}

			//RIGHT

			else if (j == columns - 1 && (i > 0 && i < rows - 1)) {
				req += (inputMatrix[i - 1][j - 1] > threshold); //top  left column 
				req += (inputMatrix[i + 1][j - 1] > threshold); // lowerLeft
				req += (inputMatrix[i - 1][j] > threshold); // top column
				req += (inputMatrix[i + 1][j] > threshold); // bottom column
				req += (inputMatrix[i][j - 1] > threshold); // left column

				outputMatrix[i][j] = (req >= 4);
			}

			else {
				//diagonals
				req += (inputMatrix[i - 1][j - 1] > threshold); //top  left column 
				req += (inputMatrix[i + 1][j + 1] > threshold); // lowerRight
				req += (inputMatrix[i - 1][j + 1] > threshold); // top right column
				req += (inputMatrix[i + 1][j - 1] > threshold); // lowerLeft
				//sides
				req += (inputMatrix[i - 1][j] > threshold); // top column
				req += (inputMatrix[i + 1][j] > threshold); // bottom column
				req += (inputMatrix[i][j - 1] > threshold); // left column
				req += (inputMatrix[i][j + 1] > threshold); // right column
				outputMatrix[i][j] = (req >= 6);

			}
		}
	}
}

//NATHAN
void find_localMaxima()
{
}
