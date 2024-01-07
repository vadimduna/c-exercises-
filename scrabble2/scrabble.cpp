#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"

using namespace std;

/* insert your function definitions here */

// QUESTION 1
int tile_score(char tile) {
    if (isalpha(tile) && islower(tile)) {
        tile = toupper(tile);
    }
    switch (tile) {
        case 'A':
        case 'E':
        case 'I':
        case 'L':
        case 'N':
        case 'O':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        return 1;

        case 'D':
        case 'G':
        return 2;

        case 'B':
        case 'C':
        case 'M':
        case 'P':
        return 3;

        case 'H':
        case 'V':
        case 'W':
        case 'Y':
        return 4;

        case 'K':
        return 5;

        case 'J':
        case 'X':
        return 8;

        case 'Q':
        case 'Z':
        return 10;

        case ' ':
        case '?':
        return 0;

    }
    return -1;
}

// QUESTION 2
bool can_form_word_from_tiles(const char* word, const char* tiles, char* played_tiles, int played_tiles_pos) {
    char availableTiles[8];
    bool emptyAvailable = false;
    int emptyPos;
    // copy tiles to modify them
    strcpy(availableTiles, tiles);
    // end of word reached, meaning that it was succesfully formed 
    if (*word == '\0') {
        played_tiles[played_tiles_pos] = '\0';
        return true;
    } 
    // go through every available tile 
    for (int i = 0; availableTiles[i] != '\0'; i++) {
       // if empty tile encountered, then set emptyAvailable to true, and save its position
        if (emptyAvailable == false && (availableTiles[i] == ' ' || availableTiles[i] == '?')) {
            emptyAvailable = true;
            emptyPos = i;
        }
        // if the current word letter corresponds to the current available tile, then remove the tile
        if (*word == availableTiles[i]) {
            played_tiles[played_tiles_pos] = availableTiles[i];
            removeTile(availableTiles, i);
            // move to next letter
            if (can_form_word_from_tiles(word + 1, availableTiles, played_tiles + 1)) {
                return true;
            }
        }
    }
    // if no letter could have been placed, then if empty available, place that instead
    if (emptyAvailable) {
        played_tiles[played_tiles_pos] = '?';
        removeTile(availableTiles, emptyPos);
        if (can_form_word_from_tiles(word + 1, availableTiles, played_tiles + 1)) {
            return true;
        }
    }

    return false;
}

void removeTile(char* availableTiles, int pos) {
    availableTiles = availableTiles + pos;
    while (*availableTiles != '\0') {
        *availableTiles = *(availableTiles + 1);
        availableTiles++;
    }
}

// QUESTION 3
int compute_score(const char* played_tiles, ScoreModifier sm[]) {
    int tilesPlayed = 0;
    int currentScore = 0;
    bool doubleTotalScore = false;
    bool trippleTotalScore = false;

    for (int i = 0; played_tiles[i] != '\0'; i++) {
        if (sm[i] == DOUBLE_WORD_SCORE) {
            currentScore += tile_score(played_tiles[i]);
            doubleTotalScore = true;
        }
        else if (sm[i] == TRIPLE_WORD_SCORE) {
            currentScore += tile_score(played_tiles[i]);
            trippleTotalScore = true;
        }
        else if (sm[i] == DOUBLE_LETTER_SCORE) {
            currentScore += tile_score(played_tiles[i]) * 2;
        }
        else if (sm[i] == TRIPLE_LETTER_SCORE) {
            currentScore += tile_score(played_tiles[i]) * 3; 
        }
        else {
            currentScore += tile_score(played_tiles[i]);
        }

        tilesPlayed++;
    }
    if (doubleTotalScore) {
        currentScore *= 2;
    }
    else if (trippleTotalScore) {
        currentScore *= 3;
    }

    if (tilesPlayed == 7) {
        currentScore += 50;
    }
    return currentScore;
}
// QUESTION 4
int highest_scoring_word_from_tiles(const char* tiles, ScoreModifier sm[], char* word) {
    ifstream fin;
    char currentInputWord[256];
    char buffer[256];
    int currentHighestScore = 0;
    int currentScore;
    
    fin.open("words.txt");
    if (fin.fail()) {
        cerr << "Error opening file\n";
        return -1;
    }

    fin >> currentInputWord;

    while (!fin.eof()) {
       if (can_form_word_from_tiles(currentInputWord, tiles, buffer)) {
            currentScore = compute_score(buffer, sm);
            if (currentScore > currentHighestScore) {
                currentHighestScore = currentScore;
                strcpy(word, currentInputWord);
            }
       }

       fin >> currentInputWord;
    }
    
    fin.close();
    if (word[0] == '\0') {
        return -1;
    }
    return currentHighestScore;
}
