#ifndef SCRABBLE_H
#define SCRABBLE_H

enum ScoreModifier { NONE, DOUBLE_LETTER_SCORE, TRIPLE_LETTER_SCORE, DOUBLE_WORD_SCORE, TRIPLE_WORD_SCORE };

/* insert your function prototypes here */

// QUESTION 1
int tile_score(char tile);

// QUESTION 2
bool can_form_word_from_tiles(const char* word, const char* tiles, char* played_tiles, int played_tiles_pos = 0);
void removeTile(char* availableTiles, int pos);

// QUESTION 3
int compute_score(const char* played_tiles, ScoreModifier sm[]);

// QUESTION 4
int highest_scoring_word_from_tiles(const char* tiles, ScoreModifier sm[], char* word);
#endif