#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>
#include <cstdlib>


using namespace std;


void visualizeSudokuBoard(const std::vector<std::vector<int>>& board) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Draw Sudoku board
    std::cout << "-------------------------" << std::endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0) std::cout << "| ";
            if (board[i][j] != 0)
                std::cout << board[i][j] << " ";
            else
                std::cout << ". ";
        }
        std::cout << "|" << std::endl;
        if ((i + 1) % 3 == 0)
            std::cout << "-------------------------" << std::endl;
    }
    std::cout << std::endl;
}



std::vector<std::vector<int> > load_vector(string board_array)
{

    std::vector<std::vector<int>> board;
    board.reserve(9);
    for (int row = 0; row < 9; ++row) {
        std::vector<int> this_row;
        this_row.reserve(9);
        for (int col = 0; col < 9; ++col) {
            if(board_array[row * 9 + col] == '.')                       // Not checking if either/or '.' and '0'
                this_row.push_back(0);
            else
                this_row.push_back(board_array[row * 9 + col] - '0');
        }
        board.push_back(this_row);
    }
    return board;

}

string load_solution_string(std::vector<std::vector<int>> const& board) {
    string solution = "";

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            solution.append(to_string(board[i][j]));
        }
    }
    return solution;
}

void print_board(std::vector<std::vector<int>> const& board) {
    for (int row = 0; row < 9; row++) {
        if ((row % 3) == 0 && row != 0) {
            std::cout << "----------------------------\n";
        }
        for (int column = 0; column < 9; column++) {
            if (((column + 1) % 3) == 0)
                std::cout << board[row][column] << " | ";
            else
                std::cout << board[row][column] << "  ";
        }
        std::cout << "\n";
    }
}

bool is_board_full(std::vector<std::vector<int>> board) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++)
        {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool is_placement_correct(std::vector<std::vector<int>> const& board, int x, int y) {
    //check row
    for (int i = 0; i < 9; ++i) {
        if (i == y)
            continue;
        if (board[x][i] == board[x][y])
            return false;
    }
    //check col
    for (int i = 0; i < 9; ++i) {
        if (i == x)
            continue;
        if (board[i][y] == board[x][y])
            return false;
    }

    //check squares
    int square_row = 0, square_col = 0;
    if (x >= 0 && x <= 2)
        square_row = 0;
    if (x >= 3 && x <= 5)
        square_row = 3;
    if (x >= 6 && x <= 8)
        square_row = 6;

    if (y >= 0 && y <= 2)
        square_col = 0;
    if (y >= 3 && y <= 5)
        square_col = 3;
    if (y >= 6 && y <= 8)
        square_col = 6;

    for (int i = square_row; i < (square_row + 3); ++i) {
        for (int j = square_col; j < square_col + 3; ++j) {
            if (i == x && j == y)
                continue;
            if (board[i][j] == board[x][y])
                return false;
        }
    }
    return true;
}


bool validate_board(std::vector<std::vector<int>>& board) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] != 0) {
                if (!(is_placement_correct(board, i, j)))
                    return false;
            }
        }
    }
    return true;
}


bool validate_input_string(string input) {
    if (input.size() != 81)
        return false;
    for (unsigned int i = 0; i < input.size(); i++){
        if ((input[i] - '0' > 9) || (input[i] - '0' < 0))
            return false;
        if (input[i] == '.') {
            for (unsigned int j = i ; i < input.size(); i++){
                if (input[j] == '0' || input[i] - '0' > 9 || input[i] - '0' < 0)
                    return false;

            }
        }

        if (input[i] == '0') {
            for (unsigned int j = i; i < input.size(); i++) {
                if (input[j] == '.' || input[i] - '0' > 9 || input[i] - '0' < 0) {
                    return false;
                }
            }
        }
    }
    return true;
}





bool solve_board(std::vector<std::vector<int>>& board) {
    //is board full?
    if (is_board_full(board)) {
        return false;
        //Then Board is solved!
    }

    //find first empty space
    int empty_place_row = 0, empty_place_col = 0;

    for (int i = 0; i <= 8; i++) {
        for (int j = 0; j <= 8; j++) {
            if (board[i][j] == 0) {
                empty_place_row = i;
                empty_place_col = j;
                break;
            }
            else continue;
        }
        if (board[empty_place_row][empty_place_col] == 0)
            break;
    }
    //Empty space is at board[i][j]
    //Try to put in numbers

    for (int k = 1; k < 10; ++k) {
        board[empty_place_row][empty_place_col] = k;

        if (is_placement_correct(board, empty_place_row, empty_place_col)) {
            visualizeSudokuBoard(board);
            if (!solve_board(board)) {
                return false;
            }
        }
    }
    //if none fit - go back
    board[empty_place_row][empty_place_col] = 0;
    return true;
}



int main(int argc, char* argv[]) {
    string board_string;
    std::string input_path;
    std::string output_path;

    if (argc == 4 || argc == 2 || argc >= 6) {
        std::cout << "Number of parameters not supported!\n";
        return -1;
    }
    else if (argc == 3 || argc == 5 || argc == 1) {
        if (argc == 3 || argc == 5) {
            if (strcmp(argv[1], "-i") == 0) {
                input_path = argv[2];

                if (argc == 5) {
                    if (strcmp(argv[3], "-o") == 0) {
                        output_path = argv[4];
                    }
                }
            }
            else if (strcmp(argv[1], "-o") == 0) {
                output_path = argv[2];
                if (argc == 5) {
                    if (strcmp(argv[3], "-i") == 0) {
                        input_path = argv[4];
                    }
                }
            }
            else {
                std::cout << "Unknown parameter!\n";
                return -1;
            }
        }

        ifstream inputstream;
        inputstream.open(input_path);
        ofstream outputstream(output_path);


        std::string solution;

        if (inputstream.is_open() && input_path != "") {

            while (getline(inputstream, board_string)) {
                if (!validate_input_string(board_string))
                    return -1;
                std::vector<std::vector<int> > board_vector = load_vector(board_string);
                if (validate_board(board_vector)) {
                    solve_board(board_vector);
                    solution = load_solution_string(board_vector);
                }
                else {
                    solution = "";
                }
                if (outputstream.is_open()) {
                    outputstream << solution << endl;
                }
                else {
                    std::cout << solution << endl;
                }

            }
        }
        else if(input_path == ""){
            while (cin) {
                getline(cin, board_string);
                if (board_string == "exit") {
                    return 0;
                }
                if (!validate_input_string(board_string))
                    return -1;
                std::vector<std::vector<int> > board_vector = load_vector(board_string);
                if (validate_board(board_vector)) {
                    solve_board(board_vector);
                    solution = load_solution_string(board_vector);
                }
                else {
                    solution = "";
                }
                if (outputstream.is_open()) {
                    outputstream << solution << endl;
                }
                else {
                    std::cout << solution << endl;
                }
            };
        }
        else {
            return -1;
        }

        inputstream.close();
        outputstream.close();
    }
    return 0;
}
