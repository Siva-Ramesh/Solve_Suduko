#include <iostream>
using namespace std;

const int SIZE = 9;

// Function to print the Sudoku board
void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number in the given cell
bool isSafeToPlace(char board[SIZE][SIZE], int r, int c, char num) {
    // Check row
    for (int i = 0; i < SIZE; ++i) {
        if (board[r][i] == num) 
            return false;
    }

    // Check column
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][c] == num)
            return false;
    }

    // Check 3x3 grid
    int startRow = r - (r % 3);
    int startCol = c - (c % 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(char board[SIZE][SIZE], int r, int c) {
    // If we reached the end of the board
    if (r == SIZE) 
        return true;

    // Move to the next cell
    if (c == SIZE) 
        return solveSudoku(board, r + 1, 0);

    // Skip cells that are already filled
    if (board[r][c] != '.')
        return solveSudoku(board, r, c + 1);

    // Try placing numbers from 1 to 9
    for (char num = '1'; num <= '9'; ++num) {
        if (isSafeToPlace(board, r, c, num)) {
            board[r][c] = num;

            if (solveSudoku(board, r, c + 1))
                return true;

            // Backtrack if placing num did not lead to a solution
            board[r][c] = '.';
        }
    }

    return false;
}

int main() {
    char board[SIZE][SIZE];

    // Input the Sudoku board from the user
    cout << "Enter the Sudoku board (9x9), use '.' for empty cells:" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> board[i][j];
        }
    }

    // Solve the Sudoku puzzle
    if (solveSudoku(board, 0, 0)) {
        // Print the solved Sudoku board
        cout << "Solved Sudoku board:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}

