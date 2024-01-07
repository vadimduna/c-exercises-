#ifndef MINESWEEPER_H
#define MINESWEEPER_H

enum MoveResult { INVALID_MOVE=-3, REDUNDANT_MOVE=-2, BLOWN_UP=-1, SOLVED_BOARD=1, VALID_MOVE=0 };

void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
void initialise_board(char board[9][9]);

/* QUESTION 1 */
bool is_complete(char mines[9][9], char revealed[9][9]);


/* QUESTION 2 */
int count_mines(const char* position, char mines[9][9]);

/* QUESTION 3 */

MoveResult make_move(const char* position, char mines[9][9], char revealed[9][9]);

/* QUESTION 4 */
bool find_safe_move(char revealed[9][9], char* move);
bool squareSurroundedByBombs(int row, int column, char revealed[9][9]);
void adjustNumInSquare(int row, int column, char revealed[9][9], int& count);

#endif