#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>

#include "solitaire.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a board */
bool get_board_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a board from a file*/
char **load_board(const char *filename, int &height, int &width) {

  cout << "Loading puzzle board from '" << filename << "'...";
  
  bool success = get_board_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width + 1);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }

  cout << " done (height = " << height << ", width = " << width << ")." << endl;
    
  return m;
}

/* pre-supplied function to print a board */
void print_board(char **board, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << static_cast<char>('A' + c);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << board[r][c];
    cout << endl;
  }
}

/* add your function definitions below */

/*QUESTION 1 */

bool are_identical(char** first, char** second, int height, int width) {
    // go through each element in both arrays
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            // if not equal, return false
            if (first[row][column] != second[row][column]) {
                return false;
            }
        }
    }
    return true;
}

/* QUESTION 2 */
bool make_move(char** board, const char* move, int height, int width) {
    int sourceRow, sourceColumn, destRow, destColumn, marbleRow, marbleColumn;
    char direction;

    // converting string info to int coordinates
    sourceColumn = static_cast<int>(*move - 'A');
    sourceRow = static_cast<int>(*(move + 1) - '0');
    direction = *(move + 2);

    get_destPos_marblePos(sourceRow, sourceColumn, direction, destRow, destColumn, marbleRow, marbleColumn);
    
    // coordinates out of bounds, move illegal
    if (sourceRow >= height || destRow >= height || sourceColumn >= width || destColumn >= width) {
        return false;
    }

    if (sourceRow < 0 || destRow < 0 || sourceColumn < 0 || destColumn < 0) {
        return false;
    }


    // source square empty, illegal move

    if (source_empty(board, sourceRow, sourceColumn)) {
        return false;
    }

    // destination square not empty, move illegal
    if (!destination_empty(board, destRow, destColumn)) {
        return false;
    }

    //adjacent square not a marble
    if (!adjacent_marble(board, marbleRow, marbleColumn)) {
        return false;
    }

    changeBoardState(board, sourceRow, sourceColumn, destRow, destColumn, marbleRow, marbleColumn);
    return true;
}

void get_destPos_marblePos(int sourceRow, int sourceColumn, char direction, int& destRow, int&destColumn, int& marbleRow, int& marbleColumn) {
    switch (direction) {
        case 'N':
        destRow = sourceRow - 2;
        marbleRow = sourceRow - 1;
        destColumn = sourceColumn;
        marbleColumn = sourceColumn;
        break;

        case 'E':
        destRow = sourceRow;
        marbleRow = sourceRow;
        destColumn = sourceColumn + 2;
        marbleColumn = sourceColumn + 1;
        break;

        case 'S':
        destRow = sourceRow + 2;
        marbleRow = sourceRow + 1;
        destColumn = sourceColumn;
        marbleColumn = sourceColumn;
        break;

        case 'W':
        destRow = sourceRow;
        marbleRow = sourceRow;
        destColumn = sourceColumn - 2;
        marbleColumn = sourceColumn - 1;
        break;
    }
}

bool source_empty(char** board, int sourceRow, int sourceColumn) {
    return (board[sourceRow][sourceColumn] == '_');
}

bool destination_empty(char** board, int destRow, int destColumn) {
    return (board[destRow][destColumn] == '_');
}

bool adjacent_marble(char** board, int marbleRow, int marbleColumn) {
    return (board[marbleRow][marbleColumn] == 'O');
}

void changeBoardState(char** board, int sourceRow, int sourceColumn, int destRow, int destColumn, int marbleRow, int marbleColumn) {
    board[sourceRow][sourceColumn] = '_';
    board[destRow][destColumn] = 'O';
    board[marbleRow][marbleColumn] = '_';
}

/* QUESTION 3 */
bool find_solution(char** begin, char** end, int height, int width, char* solution, int depth) {
    char potentialMove[5];

    depth++; 
    
    // solution exceeds depth
    if (depth > 6) {
        return false;
    }

    // board is identical to solution, return true
    if (are_identical(begin, end, height, width)) {
        return true;
    }

    // go through every square
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            // skip invalid squares
            if (begin[row][column] == '.' || begin[row][column] == '_') {
                continue;
            }
            // add the relevant source square to potentialMove string
            potentialMove[0] = static_cast<char>(column + 'A');
            potentialMove[1] = static_cast<char>(row + '0');
            // for every source square, try every direction
            for(int directionCount = 0; directionCount < 4; directionCount++) {
                if (directionCount == 0) {
                    potentialMove[2] = 'N';
                }
                else if (directionCount == 1) {
                    potentialMove[2] = 'E';
                }
                else if (directionCount == 2) {
                    potentialMove[2] = 'S';
                }
                else {
                    potentialMove[2] = 'W';
                }
                potentialMove[3] ='\0';
                 // if move valid, add a , to potential move
                if (make_move(begin, potentialMove, height, width)) {
                    potentialMove[3] = ',';
                    potentialMove[4] = '\0';
                    // add the move to the set of valid moves
                    strcat(solution, potentialMove);
                    if (find_solution(begin, end, height, width, solution, depth)) {
                        return true;
                    }
                    // move was legal initially, however, it has produced no solution, so revert the changes
                    revertChanges(begin, static_cast<int>(potentialMove[1] - '0'), static_cast<int>(potentialMove[0] - 'A'), potentialMove[2]);
                    // get the null of the solution so to remove the last added move 
                    int posNull = getNull(solution);
                    removeMoveFromSol(solution, posNull);
                }
            }   
        }
    }
    return false;
}

void revertChanges(char** board, int sourceRow, int sourceColumn, char direction) {
    int destRow, destColumn, marbleRow, marbleColumn;

    get_destPos_marblePos(sourceRow, sourceColumn, direction, destRow, destColumn, marbleRow, marbleColumn);

    board[sourceRow][sourceColumn] = 'O';
    board[destRow][destColumn] = '_';
    board[marbleRow][marbleColumn] = 'O';

}

int getNull(const char* solution) {
    int pos = 0;

    while (*solution != '\0') {
        pos++;
        solution++;
    }

    return pos;
}

void removeMoveFromSol(char* solution, int posNull) {
    solution[posNull - 4] = '\0';
}
