# 🔢 Sudoku Solver and Generator in C++

This project is a **console-based Sudoku game** that allows users to:

- ✅ Enter and solve their own Sudoku puzzle
- 🔁 Generate puzzles of varying difficulty (Easy, Medium, Hard)
- 🧠 Solve puzzles using recursive backtracking
- ✍️ Manually input values step-by-step
- 📊 Track number of backtracking steps used in solving

Built using **Object-Oriented Programming** in C++ with clear modular design.

---

## 🎮 Features

- **Fully Interactive Console Menu**
- **Sudoku Puzzle Generator** (Unique Solution Ensured)
- **Backtracking Solver** with performance tracking
- **Manual Entry Mode** (row, col, value)
- **Input Validation** (row/col/box constraint checking)
- **Difficulty Levels**:
  - Easy: 60+ clues
  - Medium: 45+ clues
  - Hard: 30+ clues

---

## 🧠 Algorithms Used

- **Backtracking** for solving and generating puzzles
- **Randomized filling** of diagonal 3x3 boxes
- **Safe placement checks** via `isSafe(row, col, num)`
- **Unique solution enforcement** with `countSolutions()`
- **Grid visualization** using ASCII format

---

## 🖥️ Sample Menu

Menu:
1. Enter Sudoku Puzzle to Solve
2. Generate Sudoku Puzzle
3. Solve Sudoku
4. Manual Entry to Solve
5. Exit
Choice: 2
Select difficulty (1-Easy, 2-Medium, 3-Hard): 2

-------------------------
| 4 3 2 | _ _ _ | 8 _ 5 |
| 1 _ _ | 5 8 _ | _ _ _ |
| _ _ 5 | 1 _ 2 | _ 6 7 |
-------------------------
| _ _ 1 | 7 _ _ | 9 2 8 |
| 9 2 3 | _ 4 1 | _ _ 6 |
| _ 5 _ | 2 _ 6 | 1 4 3 |
-------------------------
| 3 7 9 | 4 _ _ | 6 8 _ |
| 5 1 6 | _ _ _ | _ 9 4 |
| 2 _ 4 | _ 7 _ | 3 _ 1 |
-------------------------

Menu:
1. Enter Sudoku Puzzle to Solve
2. Generate Sudoku Puzzle
3. Solve Sudoku
4. Manual Entry to Solve
5. Exit
Choice: 3

-------------------------
| 4 3 2 | 9 6 7 | 8 1 5 |
| 1 6 7 | 5 8 4 | 2 3 9 |
| 8 9 5 | 1 3 2 | 4 6 7 |
-------------------------
| 6 4 1 | 7 5 3 | 9 2 8 |
| 9 2 3 | 8 4 1 | 5 7 6 |
| 7 5 8 | 2 9 6 | 1 4 3 |
-------------------------
| 3 7 9 | 4 1 5 | 6 8 2 |
| 5 1 6 | 3 2 8 | 7 9 4 |
| 2 8 4 | 6 7 9 | 3 5 1 |
-------------------------
Solved using 41 backtracks.

