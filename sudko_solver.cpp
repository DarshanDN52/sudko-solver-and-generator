#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
class Sudoku {
public:
    vector<vector<int>> grid;
    Sudoku();
    void printGrid();
    bool isSafe(int row, int col, int num);
    bool solveSudoku(int &backtrackCount);
    void manualEntryToSolve();
    void enterSudokuPuzzle();
    void generateSudoku();
    void fillDiagonal();
    bool fillGrid();
    int countSolutions();
    bool findEmptyCell(int &row, int &col);
};
Sudoku::Sudoku() {
    grid = vector<vector<int>>(9, vector<int>(9, 0));
}
void Sudoku::printGrid() {
    cout << "\n-------------------------\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0)
                cout << "| ";
            if (grid[i][j] != 0)
                cout << grid[i][j] << " ";
            else
                cout << "_ ";
        }
        cout << "|\n";
        if ((i + 1) % 3 == 0)
            cout << "-------------------------\n";
    }
}

bool Sudoku::isSafe(int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
    return true;
}
bool Sudoku::findEmptyCell(int &row, int &col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}
bool Sudoku::solveSudoku(int &backtrackCount) {
    int row, col;
    if (!findEmptyCell(row, col)) return true;
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(backtrackCount)) return true;
            grid[row][col] = 0;
            backtrackCount++;
        }
    }
    return false;
}
void Sudoku::manualEntryToSolve() {
    int row, col, num;
    while (true) {
        cout << "\nEnter row (1-9), column (1-9), number (1-9) or -1 to finish: ";
        cin >> row;
        if (row == -1) {
            bool isComplete = true;
            for (int i = 0; i < 9 && isComplete; i++)
                for (int j = 0; j < 9; j++)
                    if (grid[i][j] == 0)
                        isComplete = false;
            if (isComplete) {
                cout << "\nSudoku puzzle completed successfully!\n";
                break;
            } else {
                char continueChoice;
                cout << "The puzzle is not complete. Solve it? (Y/N): ";
                cin >> continueChoice;
                if (continueChoice == 'N' || continueChoice == 'n') {
                    cout << "Exiting manual entry.\n";
                    break;
                } else if (continueChoice == 'Y' || continueChoice == 'y') {
                    int backtrackCount = 0;
                    if (solveSudoku(backtrackCount)) {
                        cout << "Sudoku solved:\n";
                        printGrid();
                        cout << "Solved using " << backtrackCount << " backtracks.\n";
                    } else {
                        cout << "No solution exists!\n";
                    }
                    break;
                } else {
                    cout << "Invalid choice! Please enter Y or N.\n";
                }
            }
        } else {
            cin >> col >> num;
            if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
                cout << "Invalid input! Please use values 1-9.\n";
                continue;
            }
            int r = row - 1, c = col - 1;
            if (grid[r][c] != 0) {
                cout << "Cell already filled! Choose an empty cell.\n";
                continue;
            }
            if (!isSafe(r, c, num)) {
                cout << "Invalid move! Conflict in row, column, or box.\n";
                continue;
            }
            grid[r][c] = num;
            cout << "Valid move. Current grid:\n";
            printGrid();
        }
    }
}

void Sudoku::enterSudokuPuzzle() {
    cout << "Enter the Sudoku puzzle (0 for empty cells, -1 to stop early after 2 values):\n";
    int valueCount = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int val;
            cout << "Cell (" << i + 1 << "," << j + 1 << "): ";
            cin >> val;
            if (val == -1) {
                if (valueCount >= 2) {
                    cout << "Early exit.\n";
                    return;
                } else {
                    cout << "Enter at least 2 values before exiting.\n";
                    j--;
                    continue;
                }
            }
            if (val < 0 || val > 9) {
                cout << "Invalid! Enter 0-9.\n";
                j--;
                continue;
            }
            if (val == 0) {
                grid[i][j] = 0;
                continue;
            }
            int temp = grid[i][j];
            grid[i][j] = 0;
            if (!isSafe(i, j, val)) {
                cout << "Invalid! Conflict in row/col/box.\n";
                grid[i][j] = temp;
                j--;
            } else {
                grid[i][j] = val;
                valueCount++;
            }
        }
    }
}

void Sudoku::generateSudoku() {
    int difficulty;
    cout << "Select difficulty (1-Easy, 2-Medium, 3-Hard): ";
    cin >> difficulty;
    int clues = (difficulty == 1) ? 60 + rand() % 5 :
                (difficulty == 2) ? 45 + rand() % 5 :
                                   30 + rand() % 5;
    grid = vector<vector<int>>(9, vector<int>(9, 0));
    fillDiagonal();
    fillGrid();
    int removed = 81 - clues;
    while (removed > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (grid[row][col] == 0) continue;
        int backup = grid[row][col];
        grid[row][col] = 0;
        vector<vector<int>> tempGrid = grid;
        if (countSolutions() != 1)
            grid[row][col] = backup;
        else
            removed--;
    }
}

void Sudoku::fillDiagonal() {
    for (int i = 0; i < 9; i += 3) {
        vector<int> nums = {1,2,3,4,5,6,7,8,9};
        random_shuffle(nums.begin(), nums.end());
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                grid[i + r][i + c] = nums[r * 3 + c];
    }
}

bool Sudoku::fillGrid() {
    int row, col;
    if (!findEmptyCell(row, col)) return true;
    vector<int> nums = {1,2,3,4,5,6,7,8,9};
    random_shuffle(nums.begin(), nums.end());
    for (int num : nums) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (fillGrid()) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

int Sudoku::countSolutions() {
    int row, col;
    if (!findEmptyCell(row, col)) return 1;
    int count = 0;
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            count += countSolutions();
            grid[row][col] = 0;
            if (count > 1) return count;
        }
    }
    return count;
}

int main() {
    Sudoku sudoku;
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Enter Sudoku Puzzle to Solve\n";
        cout << "2. Generate Sudoku Puzzle\n";
        cout << "3. Solve Sudoku\n";
        cout << "4. Manual Entry to Solve\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        int backtrackCount = 0;
        switch (choice) {
            case 1:
                sudoku.grid = vector<vector<int>>(9, vector<int>(9, 0));
                sudoku.enterSudokuPuzzle();
                sudoku.printGrid();
                break;
            case 2:
                sudoku.generateSudoku();
                sudoku.printGrid();
                break;
            case 3:
                if (sudoku.solveSudoku(backtrackCount)) {
                    sudoku.printGrid();
                    cout << "Solved using " << backtrackCount << " backtracks.\n";
                } else {
                    cout << "No solution exists!\n";
                }
                break;
            case 4:
                sudoku.manualEntryToSolve();
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
