#ifndef SOLITAIRE_H
#define SOLITAIRE_H

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a board from a file*/
char **load_board(const char *filename, int &height, int &width);

/* pre-supplied function to print a board */
void print_board(char **board, int height, int width);

/* place your headers below */

/* QUESTION 1 */
bool are_identical(char** first, char** second, int height, int width);

/* QUESTION 2 */
bool make_move(char** board, const char* move, int height, int width);
void get_destPos_marblePos(int sourceRow, int sourceColumn, char direction, int& destRow, int&destColumn, int& marbleRow, int& marbleColumn);
bool source_empty(char** board, int sourceRow, int sourceColumn);
bool destination_empty(char** board, int destRow, int destColumn);
bool adjacent_marble(char** board, int marbleRow, int marbleColumn);
void changeBoardState(char** board, int sourceRow, int sourceColumn, int destRow, int destColumn, int marbleRow, int marbleColumn);

/* QUESTION 3 */
bool find_solution(char** begin, char** end, int height, int width, char* solution, int depth = 0);
void revertChanges(char** board, int sourceRow, int sourceColumn, char direction);
int getNull(const char* solution);
void removeMoveFromSol(char* solution, int posNull);
#endif