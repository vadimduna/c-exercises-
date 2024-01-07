#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include "laser.h"

using namespace std;

/* pre-supplied helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **array = new char *[rows];
  assert(array);
  for (int r=0; r<rows; r++) {
    array[r] = new char[columns];
    assert(array[r]);
  }
  return array;
}

/* pre-supplied helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **array, int rows) {
  for (int r=0; r<rows; r++)
    delete [] array[r];
  delete [] array;
}

/* internal helper function which gets the dimensions of a board */
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

/* internal helper function which removes carriage returns and newlines from end of strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* pre-supplied function to load a board from a file*/
char **load_board(const char *filename, int &height, int &width) {

  bool success = get_board_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **board = allocate_2D_array(height, width + 1);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    filter(line);
    strcpy(board[r], line);
  }
  
  return board;
}

/* pre-supplied function to print a board */
void print_board(char **board, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << board[r][c];
    cout << endl;
  }
}

/* add your own function definitions here */

// QUESTION 1 

bool find_laser(char** board, int height, int width, int& row) {
  for (int currentRow = 0; currentRow < height; currentRow++) {
    if (board[currentRow][0] == '>') {
      row = currentRow;
      return true;
    }
  }
  row = -1;
  return false;
}

// QUESTION 2
char mirror_label(char** board, int height, int width, int row, int column) {
  char mirror = board[row][column];
  if (mirror != '\\' && mirror != '/') {
    return '\0';
  }
  // go through squares immediately next to the target square 
  for (int currentRow = row - 1; currentRow <= row + 1; currentRow++) {
    for (int currentColumn = column - 1; currentColumn <= column + 1; currentColumn++) {
      if (currentRow >= height || currentColumn >= width) {
        continue;
      }
      if (currentRow == row) {
        continue;
      }
      // if there is a letter, then check if the label belongs to the mirror
      if (isalpha(board[currentRow][currentColumn])) {
        if (mirror == '\\') {
          if ((currentRow == row - 1 && currentColumn == column - 1) || (currentRow == row + 1 && currentColumn == column + 1)) {
              return board[currentRow][currentColumn];
          }
        }
        if (mirror == '/') {
          if ((currentRow == row - 1 && currentColumn == column + 1) || (currentRow == row + 1 && currentColumn == column - 1)) {
              return board[currentRow][currentColumn];
          }
        }
      }
    }
  }
  return '\0';
}

// QUESTION 3
bool shoot(char** board, int height, int width, char* message, int& last_row, int& last_col) {
  int currentRow;
  // laser at the edge, next available square is one to the right
  int currentColumn = 1;
  Direction currentDirection = EAST;

  //adding null to message
  message[0] = '\0';
  
  // find laser start position 
  if (find_laser(board, height, width, currentRow)) {
    while (board[currentRow][currentColumn]!= '#' && board[currentRow][currentColumn]!= '@' 
           && board[currentRow][currentColumn]!= '?') {
            determineDirection(board, board[currentRow][currentColumn], currentDirection, height, width, currentRow, currentColumn, message);

            switch (currentDirection) {
              case NORTH:
              moveNorth(board, currentRow, currentColumn);
              break;

              case EAST:
              moveEast(board, currentRow, currentColumn);
              break;

              case SOUTH:
              moveSouth(board, currentRow, currentColumn);
              break;

              case WEST:
              moveWest(board, currentRow, currentColumn);
              break;
            }
           }
  }

  last_row = currentRow;
  last_col = currentColumn;

  if (board[last_row][last_col] == '@') {
    return true;
  }
  return false;
}

void determineDirection(char** board, char ch, Direction& currentDirection, int height, int width, int& currentRow, int& currentColumn, char* message) {
  char currentMessageChar[2];

  if (ch == '\\') {
    currentMessageChar[0] = mirror_label(board, height, width, currentRow, currentColumn);
    if (currentDirection == NORTH) {
      currentDirection = WEST;
      currentColumn--;
    }
    else if (currentDirection == EAST) {
      currentDirection = SOUTH;
      currentRow++;
    }
    else if (currentDirection == SOUTH) {
      currentDirection = EAST;
      currentColumn++;
    }
    else {
      currentDirection = NORTH;
      currentRow--;
    }
  }
  else if (ch == '/') {
    currentMessageChar[0] = mirror_label(board, height, width, currentRow, currentColumn);
    if (currentDirection == NORTH) {
      currentDirection = EAST;
      currentColumn++;
    }
    else if (currentDirection == EAST) {
      currentDirection = NORTH;
      currentRow--;
    }
    else if (currentDirection == SOUTH) {
      currentDirection = WEST;
      currentColumn--;
    }
    else {
      currentDirection = SOUTH;
      currentRow++;
    }
  }
  if (currentMessageChar[0] != '\0') {
    currentMessageChar[1] = '\0';
    strcat(message, currentMessageChar);
  }
}

void moveNorth(char** board, int& row, int column) {
  for (int currentRow = row; board[currentRow][column] != '#'
       && board[currentRow][column] != '/' && board[currentRow][column] != '\\' && board[currentRow][column] != '@' && board[currentRow][column] != '?' ; currentRow--) {
    if (board[currentRow][column] == '-') {
      board[currentRow][column] = '+';
      row--;
      continue;
    }
    board[currentRow][column] = '|';
    row--;
  }
}

void moveEast(char** board, int row, int& column) {
  for (int currentColumn = column; board[row][currentColumn] != '#'
       && board[row][currentColumn] != '/' && board[row][currentColumn] != '\\' && board[row][currentColumn] != '@' && board[row][currentColumn] != '?' ; currentColumn++) {
    if (board[row][currentColumn] == '|') {
      board[row][currentColumn] = '+';
      column++;
      continue;
    }
    board[row][currentColumn] = '-';
    column++;
  }
}

void moveSouth(char** board, int& row, int column) {
  for (int currentRow = row; board[currentRow][column] != '#'
       && board[currentRow][column] != '/' && board[currentRow][column] != '\\' && board[currentRow][column] != '@' && board[currentRow][column] != '?' ; currentRow++) {
    if (board[currentRow][column] == '-') {
      board[currentRow][column] = '+';
      row++; 
      continue;
    }
    board[currentRow][column] = '|';
    row++;
  }
}

void moveWest(char** board, int row, int& column) {
  for (int currentColumn = column; board[row][currentColumn] != '#'
       && board[row][currentColumn] != '/' && board[row][currentColumn] != '\\' && board[row][currentColumn] != '@' && board[row][currentColumn] != '?'; currentColumn--) {
    if (board[row][currentColumn] == '|') {
      board[row][currentColumn] = '+';
      column--;
      continue;
    }
    board[row][currentColumn] = '-';
    column--;
  }
}

// QUESTION 4 

bool solve(char** board, int height, int width, const char* target) {
    char message[512];
    int last_row, last_col;
    char boardCopy[height][width];
    bool shootingResult;
    for (int row = 0; row < height; row++) {
      for (int column = 0; column < width; column++) {
      boardCopy[row][column] = board[row][column];
      }
    }
    shootingResult = shoot(board, height, width, message, last_row, last_col);

    if (shootingResult == true && !strcmp(message, target)) {
      return true;
    }

    else if (shootingResult == false && board[last_row][last_col] == '?') {
      board[last_row][last_col] = '\\';
        if (solve(board, height, width, target)) {
            return true;
        }

        for (int row = 0; row < height; row++) {
          for (int column = 0; column < width; column++) {
            board[row][column] = boardCopy[row][column];
        }
          }
        board[last_row][last_col] = '/';
        if (solve(board, height, width, target)) {
            return true;
        }
        for (int row = 0; row < height; row++) {
          for (int column = 0; column < width; column++) {
              board[row][column] = boardCopy[row][column];
          }
        }

        board[last_row][last_col] = ' ';
        if (solve(board, height, width, target)) {
            return true;
        }
    }
    return false;
}
