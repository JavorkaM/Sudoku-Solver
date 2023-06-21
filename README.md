# Sudoku Solver

This is a Sudoku solver program written in C++. It solves Sudoku puzzles using a backtracking algorithm and provides solutions for given Sudoku boards.

## Features
- Solves Sudoku puzzles of varying difficulty levels.
- Supports input from both files and the console.
- Provides solutions as output on the console or writes them to an output file.
- Validates input Sudoku boards for correctness.
- Includes a visual representation of the Sudoku board during solving.

## How to Use

### Prerequisites
- C++ compiler (e.g., GCC for Linux or MinGW for Windows)

### Installation
1. Clone the repository or download the source code.

2. Compile the code using the following command:
   ```
   g++ -o sudoku_solver sudoku_solver.cpp
   ```
   If you're using a different compiler, adjust the command accordingly.

### Usage
1. Run the program using one of the following methods:

   a. Running with input and output files:
      ```
      ./sudoku_solver -i input.txt -o output.txt
      ```
      Replace `input.txt` with the path to your input file, and `output.txt` with the desired path for the output file.

   b. Running with only an input file:
      ```
      ./sudoku_solver -i input.txt
      ```
      Replace `input.txt` with the path to your input file. The solutions will be printed on the console.

   c. Running with no input or output files:
      ```
      ./sudoku_solver
      ```
      The program will read the Sudoku board strings from the console and display the solutions on the console.

2. Provide input:

   - If you're running the program without an input file, enter the Sudoku board strings one by one, pressing Enter after each board.
   - Each board string should be a sequence of 81 characters, representing the Sudoku board row by row. Use digits from 1 to 9 for filled cells and dots (.) for empty cells.
   - To exit the program when running without an input file, type "exit" and press Enter.

3. View the results:

   - If you specified an output file, open it to view the solutions.
   - If you didn't use an output file, the solutions will be displayed on the console.

## Examples

### Example 1: Running with Input and Output Files
```
./sudoku_solver -i input.txt -o output.txt
```

### Example 2: Running with Only an Input File
```
./sudoku_solver -i input.txt
```

### Example 3: Running with No Input or Output Files
```
./sudoku_solver
```

## License
This project is licensed under the [MIT License](LICENSE).

## Acknowledgments
The Sudoku solver algorithm is based on the backtracking technique commonly used to solve Sudoku puzzles.