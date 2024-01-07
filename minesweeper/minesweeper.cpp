#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load mine positions from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || buffer[n] == '*' || buffer[n] == ' ' || buffer[n] == '?' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << "|";
  for (int i=0; i<9; i++) 
    cout << ( (data[i]=='.') ? ' ' : data[i]);
  cout << "|" << endl;
}

/* pre-supplied function to display a minesweeper board */
void display_board(const char board[9][9]) {
  cout << "  ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r);
  cout <<  endl;
  cout << " +---------+" << endl;
  for (int r=0; r<9; r++) 
    print_row(board[r],r);
  cout << " +---------+" << endl;
}

/* pre-supplied function to initialise playing board */ 
void initialise_board(char board[9][9]) {
  for (int r=0; r<9; r++)
    for (int c=0; c<9; c++)
      board[r][c] = '?';
}

/* add your functions here */


/* QUESTION 1 */

bool is_complete(char mines[9][9], char revealed[9][9]) {
   // go through each square for each board
   for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            // if the mines board has a bomb and the other does not, return false;
            if (mines[row][column] == '*' && revealed[row][column] != '*') {
                return false;
            }
        }
    }
    // else return true;
    return true;
}

/* QUESTION 2 */
int count_mines(const char* position, char mines[9][9]) {
    // converting position into ints 
    int row = static_cast<int>(*position - 'A');
    int column = static_cast<int>(*(position + 1) - '1');
    int mineCount = 0;

    // establishing a square 3 x 3 square around the chosen square
    for (int currentRow = row - 1; currentRow <= row + 1; currentRow++) {
        for (int currentColumn = column - 1; currentColumn <= column + 1; currentColumn++) {
            // illegal values
            if (currentRow < 0 || currentColumn < 0) {
                continue;
            }
            // illegal values
            if (currentRow >= 9 || currentColumn >= 9) {
                continue;
            }
            // mine found, increase count
            if (mines[currentRow][currentColumn] == '*') {
                mineCount++;
            }
        }
    }
    return mineCount;
}

/* QUESTION 3 */
MoveResult make_move(const char* position, char mines[9][9], char revealed[9][9]) {
    //storing position in a modifiable array
    char modifiablePos[4];
    strcpy(modifiablePos, position);
    // converting position into ints
    int row = static_cast<int>(*position - 'A');
    int column = static_cast<int>(*(position + 1) - '1');
    bool flagIndicated = false;
    int minesCount;
    
    // indicate that the player wants to flag a square
    if (*(position + 2) != '\0') {
        if (*(position + 2) == '*') {
            flagIndicated = true;
            // the position array now only has two letters
            modifiablePos[2] = '\0';
        }
        else {
            // invalid third character
            return INVALID_MOVE;
        }
    }

    // square outside of game boundaries
    if (row >= 9 || column >= 9 || row < 0 || column < 0) {
        return INVALID_MOVE;
    }

    if (revealed[row][column] != '?') {
        return REDUNDANT_MOVE;
    }
    
    if (mines[row][column] == '*' && flagIndicated == false) {
        return BLOWN_UP;
    }

    if (flagIndicated == true) {
        revealed[row][column] = '*';
        return VALID_MOVE;
    }

    minesCount = count_mines(modifiablePos, mines);
    // add minesCount to square
    if (minesCount != 0) {
        revealed[row][column] = static_cast<char>(minesCount + '0');
    }
    else {
        revealed[row][column] = ' ';

        // go through a 3 x 3 matrix around the current square and see whehther they can be revealed
        for (int currentRow = row - 1; currentRow <= row + 1; currentRow++) {
            // new x coordinate of square to analyze 
            modifiablePos[0] = static_cast<char>(currentRow + 'A');
            for (int currentColumn = column - 1; currentColumn <= column + 1; currentColumn++) {
                // skip the current square in the analysis 
                if (currentRow == row && currentColumn == column) {
                    continue;
                }
                // new y cooridante of square to analyze
                modifiablePos[1] = static_cast<char>(currentColumn + '1');
                // recursively check squares
                make_move(modifiablePos, mines, revealed);
            }
        }
    }

    return VALID_MOVE;
}

bool find_safe_move(char revealed[9][9], char* move) {
    move[0] = '\0';
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            if (revealed[row][column] == '?') {
                if (squareSurroundedByBombs(row, column, revealed)) {
                move[0] = static_cast<char>(row + 'A');
                move[1] = static_cast<char>(column + '1');
                move[2] = '*';
                move[3] = '\0';
                return true;
                }
                else {

                }
            }
        }
    }
    return false;
}

bool squareSurroundedByBombs(int row, int column, char revealed[9][9]) {
    int count = 0;

    for (int currentRow = row - 1; currentRow <= row + 1; currentRow++) {
        for (int currentColumn = column - 1; currentColumn <= column + 1; currentColumn++) {
            if (currentRow < 0 || currentColumn < 0) {
                continue;
            }
            if (currentRow >= 9 || currentColumn >= 9) {
                continue;
            }
            if (currentRow == row && currentColumn == column) {
                continue;
            }
            if (isdigit(revealed[currentRow][currentColumn])) {
                count += static_cast<int>(revealed[currentRow][currentColumn] - '0');   
                //adjustNumInSquare(currentRow, currentColumn, revealed, count);
            }
        }
    }
    if (count >= 3) {
        return true;
    }
    return false;
}



