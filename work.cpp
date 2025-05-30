#include <iostream>
#include <vector>
using namespace std;


void printSudoku9x9(int arr[9][9])                                        //print sudoku board
{
	cout << "-----------------------------------" << endl;
	for (int y = 0; y < 9; y++) 
	{
		for (int x = 0; x < 9; x++)
		{
			cout << arr[y][x] << "   ";
			if ((x == 2 )||( x == 5)) cout << "  |  ";
		}
		cout << endl;
		if(y==2||y==5)cout << "___________________________________" << endl;
	}
	cout << "-----------------------------------" << endl;

}

bool canPlace9x9(int arr[9][9], int row, int col, int n)                //places number into board and checks if the number is already present n the cell
{
	if (arr[row][col] != 0) return false;
	bool status = true;
	int gridx = (col / 3) * 3;
	int gridy = (row / 3) * 3;
	for (int i = 0; i < 9; i++) 
	{
		if (arr[row][i] == n) 
		{ status = false; break; }
		if (arr[i][col] == n) 
		{ status = false; break; }
		if (arr[gridy + i / 3][gridx + i % 3] == n) 
		{ status = false; break; }
	}
	return status;
}

void nextEmpty(int arr[9][9], int row, int col, int& rowNext, int& colNext)                        //find empty cell
{

	int indexNext = 9 * 9 + 1;
	
	for (int i = row * 9 + col + 1; i < 9 * 9; i++) 
	{
		if (arr[i / 9][i % 9] == 0) 
		{

			indexNext = i;
			break;
		}
	}
	rowNext = indexNext / 9;
	colNext = indexNext % 9;
}

void copyArray(int arr[9][9], int arrCpy[9][9])                              //copy array to board
{
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			arrCpy[y][x] = arr[y][x];
}
vector<int> findPlaceables(int arr[9][9], int row, int col) 
{
	vector<int> placebles = {};
	for (int n = 1; n <= 9; n++)
		if (canPlace9x9(arr, row, col, n)) placebles.push_back(n);
	return placebles;
}


bool solveSudoku9x9(int arr[9][9], int row, int col)                          //solve sudoku
{


	if (row > 8) return true;
	if (arr[row][col] != 0) 
	{
		int rowNext, colNext;
		nextEmpty(arr, row, col, rowNext, colNext);
		return solveSudoku9x9(arr, rowNext, colNext);
	}

	vector<int> placebles = findPlaceables(arr, row, col);

	if (placebles.size() == 0)
	{
		
		return false; 
	
	};

	bool status = false;
	for (int i = 0; i < placebles.size(); i++) 
	{
		int n = placebles[i];
		int arrCpy[9][9];
		
		copyArray(arr, arrCpy);
		arrCpy[row][col] = n;
		
		int rowNext = row;
		int colNext = col;
		
		nextEmpty(arrCpy, row, col, rowNext, colNext);
		
		if (solveSudoku9x9(arrCpy, rowNext, colNext)) 
		{
			copyArray(arrCpy, arr);
			status = true;
			break;
		}
	}
	return status;
}


int main(int argc, char** argv)                    //main function
{
 int board[9][9];

    cout << "Enter your Sudoku puzzle (use 0 for empty cells):\n";
    for (int i = 0; i < 9; i++) 
	{
        for (int j = 0; j < 9; j++) 
		{
            cout << "Enter value for cell [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> board[i][j];
            
            while (board[i][j] < 0 || board[i][j] > 9) 
			{
                cout << "Invalid input. Please enter a number between 0 and 9: ";
                cin >> board[i][j];
            }
                        
        }
        
    }
    cout << "\nYour Sudoku puzzle:\n";
    printSudoku9x9(board);
    
	if (solveSudoku9x9(board, 0, 0)) cout << "successfully solved board!" << endl;
	printSudoku9x9(board);
	
	return 0;
}