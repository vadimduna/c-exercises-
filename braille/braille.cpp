#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <fstream>
#include "braille.h"

/* QUESTION 1 */
int encode_character(char ch, char braille[]) {
    const int MAX_NUM_CHAR = 12;
    const int MIN_NUM_CHAR = 6;
    int size = MIN_NUM_CHAR;
    const char* brailleLetter = "......";
    char brailleCharacter[MAX_NUM_CHAR + 1];

    if (isupper(ch)) {
        strcpy(brailleCharacter, ".....0");
        ch = tolower(ch);
        size = MAX_NUM_CHAR;
    }

    if (isdigit(ch)) {
        strcpy(brailleCharacter, "..0000");
        size = MAX_NUM_CHAR;
    }

    switch (ch) {
        case 'a':
        case '1':
        brailleLetter = "0.....";
        break;

        case 'b':
        case '2':
        brailleLetter = "00....";
        break;

        case 'c':
        case '3':
        brailleLetter = "0..0..";
        break;

        case 'd':
        case '4':
        brailleLetter = "0..00.";
        break;

        case 'e':
        case '5':
        brailleLetter = "0...0.";
        break;

        case 'f':
        case '6':
        brailleLetter = "00.0..";
        break;

        case 'g':
        case '7':
        brailleLetter = "00.00.";
        break;

        case 'h':
        case '8':
        brailleLetter = "00..0.";
        break;
        
        case 'i':
        case '9':
        brailleLetter = ".0.0..";
        break;

        case 'j':
        case '0':
        brailleLetter = ".0.00.";
        break;
        
        case 'k':
        brailleLetter = "0.0...";
        break;
        
        case 'l':
        brailleLetter = "000...";
        break;
        case 'm':
        brailleLetter = "0.00..";
        break;
        case 'n':
        brailleLetter = "0.000.";
        break;
        case 'o':
        brailleLetter = "0.0.0.";
        break;
        case 'p':
        brailleLetter = "0000..";
        break;
        case 'q':
        brailleLetter = "00000.";
        break;
        case 'r':
        brailleLetter = "000.0.";
        break;
        case 's':
        brailleLetter = ".000..";
        break;
        case 't':
        brailleLetter = ".0000.";
        break;
        case 'u':
        brailleLetter = "0.0..0";
        break;
        case 'v':
        brailleLetter = "000..0";
        break;
        case 'w':
        brailleLetter = ".0.000";
        break;
        case 'x':
        brailleLetter = "0.00.0";
        break;
        case 'y':
        brailleLetter = "0.0000";
        break;
        case 'z':
        brailleLetter = "0.0.00";
        break;
        case '.':
        brailleLetter = ".0..00";
        break;
        case ',':
        brailleLetter = ".0....";
        break;
        case ';':
        brailleLetter = ".00...";
        break;
        case '-':
        brailleLetter = "..0..0";
        break;
        case '!':
        brailleLetter = ".00.0.";
        break;
        case '?':
        brailleLetter = ".00..0";
        break;
        case '(':
        case ')':
        brailleLetter = ".00.00";
    }
    if (size == MAX_NUM_CHAR) {
        strcat(brailleCharacter, brailleLetter);
    }
    else {
        strcpy(brailleCharacter, brailleLetter);
    }

    strcpy(braille, brailleCharacter);
    return size;

}

/* QUESTION 2 */

void encode(const char* plaintext, char braille[]) {
    const int MAX_NUM_CHAR = 12;
    char brailleCharacter[MAX_NUM_CHAR + 1];
    if (*plaintext == '\0') {
        return;
    }
    encode_character(*plaintext, brailleCharacter);
    strcat(braille, brailleCharacter);
    encode(plaintext + 1, braille);
}

/* QUESTION 3 */

void print_braille(const char* plaintext, std::ostream& output) {
    char braille[512];
    braille[0] = '\0';
    char brailleCharacterArray[257][256];
    if (*plaintext == '\0') {
        return;
    }
    encode(plaintext, braille);

    int index = 0;
    int finalColumn = 0;
    int strSize = strlen(braille);
    bool addPlainChar = false;
    
    for (int column = 0; column < (strSize / 3); column ++) {
        for (int row = 0; row < 3; row++) {
            if (column % 2 == 0 && braille[index] == '0') {
                addPlainChar = true;
            }
            brailleCharacterArray[row][column] = braille[index];
            index++;
            finalColumn++;
        }
        if (column % 2 == 0 && addPlainChar == true) {
            brailleCharacterArray[3][column] = *plaintext;
            addPlainChar = false;
            plaintext++;
        }
        else {
             brailleCharacterArray[3][column] = ' ';
        }
    }

  for (int row = 0; row < 4; row++) {
    for (int column = 0; column < finalColumn; column++) {
        output << brailleCharacterArray[row][column];
    }
    output << std::endl;
  }
}
