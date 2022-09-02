///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//      Author:         PRAVEER SHARAN                                                               //
//      Program:        GAME OF LIFE                                                                 //
//                                                                                                   //
//      Description:    The user plays the game of life with the computer. The user enters the size  //
//                      of the square board as N, which is also how many generations there will be.  //
//                      Then, the user fills in the board by entering 0s for where there is no       //
//                      creature and by entering 1s for where there is a creature. If a creature     //
//                      has less than 2 or more than 3 neighbors, it dies. If an empty cell has      //
//                      exactly 3 neighbors, it becomes a creature. Using this algorithm, the next   //
//                      N generations can be calculated. A recursive function is used to calculate   //
//                      each generation in the game.                                                 //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////





#include <iostream>
using namespace std;

void displayBoard(bool board[], int N) {            // this function displays the most updated Game Of Life board
    for (int i = 1; i < N - 1; i++) {
        cout << "\t";
        for (int j = 1; j < N - 1; j++) {
            if (board[N * i + j])
                cout << "* | ";
            else
                cout << "  | ";
        }
        cout << "\n\t";
        for (int j = 1; j < N - 1; j++)
            cout << "_   ";
        cout << "\n";
    }
    cout << "---------------------------------------------------\n" << endl;
}

int findNeighbors(bool board[], int N, int x, int y) {          // calculates how many neighbors there are around one cell (maximum of 8)
    int neighbors = 0;
    if (board[N * (x + 1) + y])
        neighbors++;
    if (board[N * (x - 1) + y])
        neighbors++;
    if (board[N * (x + 1) + (y + 1)])
        neighbors++;
    if (board[N * (x - 1) + (y + 1)])
        neighbors++;
    if (board[N * (x + 1) + (y - 1)])
        neighbors++;
    if (board[N * (x - 1) + (y - 1)])
        neighbors++;
    if (board[N * x + (y + 1)])
        neighbors++;
    if (board[N * x + (y - 1)])
        neighbors++;
    return neighbors;
    
}

void nextGen(bool board[], bool copyBoard[], int N, int gen) {          // transforms the board into the next generation
    if (gen <= N - 2) {                             // uses recursion until the generation is above what the user entered as N
        for (int i = 1; i < N - 1; i++) {           // iterates through all of the cells
            for (int j = 1; j < N - 1; j++) {
                if (!(board[N * i + j]) && (findNeighbors(board, N, i, j) == 3))        // if the cell is empty and has exactly 3 neighbors, put a creature there
                    copyBoard[N * i + j] = true;
                else if ((board[N * i + j]) && (findNeighbors(board, N, i, j) < 2 || findNeighbors(board, N, i, j) > 3))    // if the cell is full and has less than 2 or more than 3 neighbors, remove the creature
                    copyBoard[N * i + j] = false;
            }
        }
        for (int i = 0; i < N * N; i++)             // board becomes a copy of the copyBoard
            board[i] = copyBoard[i];
        cout << "Generation " << gen << ":" << endl;
        displayBoard(board, N);                     // displays current generation of the board
        nextGen(board, copyBoard, N, gen + 1);      // redoes the function, but generation is incremented
    }
}

int main() {
    cout << "WELCOME to this GAME OF LIFE!\n\n" << endl;         // explains the instructions
    cout << "In this game, you will enter in how big the square board is, which is also the same number of generations there will be. Each generation, ";
    cout << "a cell in the board may be occupied by a creature. If the creature has less than 2 neighbors or more than 3 neighbors, the creature will ";
    cout << "die. However, if an area with no creature has exactly 3 neighbors, a creature is born in that spot. This continues throughout the entire board." << endl;
    cout << "You will be prompted to enter in where the creatures are at the beginning. HERE'S HOW:" << endl;
    cout << "For each row, you will be prompted. If you don't want a creature, put a 0. If you do, put a 1. Keep putting these numbers with spaces in between ";
    cout << "until you have N numbers. Enter that, and the computer will move on to the next row. There will be N rows. For example, the prompt:" << endl;
    cout << "N = 4" << endl;
    cout << "Row 1: 1 0 1 0" << endl;
    cout << "Row 2: 1 1 0 1" << endl;
    cout << "Row 3: 0 1 0 1" << endl;
    cout << "Row 4: 0 0 1 0" << endl;
    cout << "will create the board:" << endl;
    cout << "\t* |   | * |   |" << endl;
    cout << "\t_   _   _   _  " << endl;
    cout << "\t* | * |   | * |" << endl;
    cout << "\t_   _   _   _  " << endl;
    cout << "\t  | * |   | * |" << endl;
    cout << "\t_   _   _   _  " << endl;
    cout << "\t  |   | * |   |" << endl;
    cout << "\t_   _   _   _  " << endl;
    cout << "\n\nThat's everything! Let's PLAY!\n\n";
    int N, k;
    cout << "N = ";
    cin >> N;
    N += 2;                                     // for padding, so that corners and sides don't need special consideration
    bool board[N * N], copyBoard[N * N];        // used a 1D array instead of a 2D one because 2D ones are hard to pass to different functions
                                                // 2D arrays can be transformed into 1D arrays - for example, board[3][2] is now board[N * 3 + 2]
                                                // everything in the Game of Life happens simultaneously, so a copyBoard is needed to store the boolean values temporarily
                                                // when necessary, the copyBoard can be copied onto the normal board and it will proceed correctly
    for (int i = 0; i < N * N; i++)             // sets the entire board to false
        copyBoard[i] = board[i] = false;
    for (int i = 1; i < N - 1; i++) {           // user enters the data, N rows and N numbers for each row
        cout << "Row " << i << ": ";
        for (int j = 1; j < N - 1; j++) {
            cin >> k;
            copyBoard[N * i + j] = board[N * i + j] = (k == 1);
        }
    }
    cout << "ORIGINAL: " << endl;
    displayBoard(board, N);                     // displays the original board
    nextGen(board, copyBoard, N, 1);            // gets the first generation
    return 0;
}