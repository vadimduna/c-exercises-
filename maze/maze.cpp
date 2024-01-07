#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <string>
#include "maze.h"

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

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
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
      cout << m[r][c];
    cout << endl;
  }
}

/* QUESTION 1 */
bool find_marker(char ch, char** maze, int height, int width, int& row, int& column) {
    // loop through each square in the maze
    for (int currentRow = 0; currentRow < height; currentRow++) {
        for (int currentColumn = 0; currentColumn < width; currentColumn++) {
            // if square contains the character, set the row to currentRow and column to currentColumn and return true
            if (maze[currentRow][currentColumn] == ch) {
                row = currentRow;
                column = currentColumn;
                return true;
            }
        }
    }
    // marker was not found, set row and column to -1 and return false
    row = -1;
    column = -1;
    return false;
}

/* QUESTION 2 */

bool valid_solution(const char* path, char** maze, int height, int width) {
    int row;
    int column;
    find_marker('>', maze, height, width, row, column);
    // ensures that the null character is not considered
    while (*path != '\0') {
            if (*path == 'N') {
                // if N, then move one square up. If that square is within bounds and it is empty or has an X, then valid
                 if (rowWithinBounds(row - 1, height) && (isspace(maze[row - 1][column]) || maze[row][column +  1] == 'X')) {
                    row--;
                 }
                 else {
                    return false;
                 }
            }
            // if E, then move one square to the right. If that square is within bounds and it is empty or has an X, then valid
            else if (*path == 'E') {
                if (columnWithinBounds(column + 1, width) && (isspace(maze[row][column +  1]) || maze[row][column +  1] == 'X')) {
                    column++;
                }
                else {
                    return false;
                }
            }
             // if S, then move one square down. If that square is within bounds and it is empty or has an X, then valid
            else if (*path == 'S') {
                if (rowWithinBounds(row + 1, height) && (isspace(maze[row + 1][column]) || maze[row][column +  1] == 'X')) {
                row++;
                }
                else {
                    return false;
                }
            }
             // if W, then move one square to the left. If that square is within bounds and it is empty or has an X, then valid
            else if (*path == 'W') {
                if (columnWithinBounds(column - 1, width) && (isspace(maze[row][column -  1]) || maze[row][column +  1] == 'X')) {
                    column--;
                }
                else {
                    return false;
                }
            }
            else { // solution path contains unrecognizable characters 
                cerr << "Error, proposed path contains illegal characters\n";
                return false;
            }
            path++;
        }
    // the solution path is correct, no more input 
    return true;
}


bool rowWithinBounds(int row, int height) {
    return (row >= 0 && row < height);
}

bool columnWithinBounds(int column, int width) {
    return (column >= 0 && column < width);
}

/* QUESTION 3 */

std::string find_path(char** maze, int height, int width, char start, char end) {
    int row;
    int column;
    std::string solution;
    find_marker(start, maze, height, width, row, column);

    if(going_direction_valid(maze, height, width, solution, row, column, start, end)) {
        return solution;
    }
    return "no solution";
}

bool going_direction_valid(char** maze, int height, int width, std::string& solution, int row, int column, char start, char end) {
    if (maze[row][column] == end) {
        maze[row][column] = '#';
        return true;
    }
    if ((!isspace(maze[row][column]) && maze[row][column] != start) || !columnWithinBounds(column, width) || !rowWithinBounds(row, height)) {
        return false;
    }
    maze[row][column] = '#';

    for (int i = row - 1; i < row + 2; i++) {
        for (int j = column - 1; j < column + 2; j++) {
            if ((i == row || j == column) && !( i == row && j == column)) {
                if (i == row - 1) {
                    solution += 'N';
                }
                else if (i == row + 1) {
                    solution += 'S';
                }
                else if (j == column - 1) {
                    solution += 'W';
                }
                else if(j == column + 1) {
                    solution += 'E';
                }
                if (going_direction_valid(maze, height, width, solution,i , j, start, end)) {
                    return true;
                }
                solution.pop_back();
            }
        }
    }         
    maze[row][column] = ' ';
    return false;        
}