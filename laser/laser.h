#ifndef LASER_H
#define LASER_H

/* pre-supplied function and type declarations */

char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **array, int rows);
char **load_board(const char *filename, int &height, int &width);
void print_board(char **board, int height, int width);

enum Direction {NORTH, EAST, SOUTH, WEST};

/* add your own function and type declarations here */
// QUESTION 1
bool find_laser(char** board, int height, int width, int& row);

// QUESTION 2
char mirror_label(char** board, int height, int width, int row, int column);

// QUESTION 3
bool shoot(char** board, int height, int width, char* message, int& last_row, int& last_col);
void determineDirection(char** board, char ch, Direction& currentDirection, int height, int width, int&currentRow, int& currentColumn, char* message);
void moveNorth(char** board, int& row, int column);
void moveEast(char** board, int row, int& column);
void moveSouth(char** board, int& row, int column);
void moveWest(char** board, int row, int& column);


//QUESTION 4
bool solve(char** board, int height, int width, const char* target);

#endif