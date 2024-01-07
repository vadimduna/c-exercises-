#ifndef MAZE_H
#define MAZE_H

/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

/* helper functions to allocate and deallocate dynamic 2D arrays */
char** allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char** m, int rows);

/* pre-supplied function to load a maze from a file */
char** load_maze(const char* filename, int& height, int& width);

/* pre-supplied function to print a maze */
void print_maze(char** m, int height, int width);


/* QUESTION 1 */

bool find_marker(char ch, char** maze, int height, int width, int& row, int& column);


/* QUESTION 2 */

bool valid_solution(const char* path, char** maze, int height, int width);
bool rowWithinBounds(int row, int height);
bool columnWithinBounds(int column, int width);


/* QUESTION 3 */
std::string find_path(char** maze, int height, int width, char start, char end);
bool going_direction_valid(char** maze, int height, int width, std::string& solution, int row, int column, char start, char end);

#endif