#include <iostream>
#include <cctype>
#include "playfair.h"

/* QUESTION 1*/
void prepare(const char* input, char output[100]) {
    int outputIndex = 0;
    //parse through the string until the null character is found 
    while (*input != '\0') {
        if (isalpha(*input)) {
           //add letter to the output
           output[outputIndex] = *input; 
            // check if it is lower case, if yes, transform to upper case
            if (islower(output[outputIndex])) {
                output[outputIndex] = toupper(output[outputIndex]);
            }
            outputIndex++;
        }
        //if digit, add to output 
        else if (isdigit(*input)) {
            output[outputIndex] = *input;
            outputIndex++;
        }
        // go to next character in the input string
        input++;
    }
    // add an X if the number of elements in the array is odd
    if (outputIndex % 2 != 0) {
        output[outputIndex] = 'X';
        outputIndex++;
    }
    // add null character to signal to the program the end of the string 
    output[outputIndex] = '\0';
}

/* QUESTION 2 */

void grid(const char* codeword, char playfair[6][6]) {
char arrayOfSeenChars[36];
arrayOfSeenChars[0] = '\0';
int pos = 0;
char letter = 'A';
char num = '0';

// Looping through array
for (int row = 0; row < 6; row++) {
    for (int column = 0; column < 6; column++) {
        // inputting the codeword first. If its current letter has not been seen, add it to the playfair array and to the arrayOfSeenChars
        if (*codeword != '\0' && !occursBefore(arrayOfSeenChars, *codeword, pos)) {
            playfair[row][column] = *codeword;
            arrayOfSeenChars[pos] = *codeword;
            pos++;
            codeword++;
            // Continue to the next square
            continue;
        }
        // Inputting codeword, but its current letter has been seen
        else if ( *codeword != '\0' && occursBefore(arrayOfSeenChars, *codeword, pos)) {
            // loop through the codeword until a lettter that has not been seen is available
            while (*codeword!= '\0' && occursBefore(arrayOfSeenChars, *codeword, pos)) {
                codeword++;
            }
            // if the letter is not the null characeter, add it to the arrays s
            if (*codeword != '0') {
            playfair[row][column] = *codeword;
            arrayOfSeenChars[pos] = *codeword;
            pos++;
            codeword++;
            // go to the next squares
            continue;
            }
        }
        // end of codeword, now add letters in lexicographical order
        else if (letter >= 'A' && letter < 'Z' ) {
            // loop through letters until one has not been seen
            while (occursBefore(arrayOfSeenChars, letter, pos)) {
                letter += 1;
            }
            // add the new letter to the arrays
            playfair[row][column] = letter;
            arrayOfSeenChars[pos] = letter;
            pos++;
        } 
        else {
            // end of inputting the rest of the alphabet, now digits
            // loop through digits until one has has not been seen
            while (occursBefore(arrayOfSeenChars, num, pos)) {
                num += 1;
            }
            // add digits to the arrays
            playfair[row][column] = num;
            arrayOfSeenChars[pos] = num;
            pos++;
        } 
    }
}

}

bool occursBefore(const char str[], char letter, int pos) {
    for (int i = 0; i <= pos; i++) {
        if (str[i] == letter) {
            return true;
        }
    }
    return false;
}

/* QUESTION 3 */

void bigram(char square[6][6], const char inchar1, const char inchar2, char& outchar1, char& outchar2) {
    int rowInChar1, rowInChar2, columnInChar1, columnInChar2;

    // search for the coordinates of the first input character
    for (int row = 0; row < 6; row++) {
        for (int column = 0; column < 6; column++) {
            if (square[row][column] == inchar1) {
                rowInChar1 = row;
                columnInChar1 = column;
            }
        }
    }
    // search for the coordinates of the second input character 
    for (int row = 0; row < 6; row++) {
        for (int column = 0; column < 6; column++) {
            if (square[row][column] == inchar2) {
                rowInChar2 = row;
                columnInChar2 = column;
            }
        }
    }
    // use found coordinates to produce the output coordinates
    outchar1 = square[rowInChar1][columnInChar2];
    outchar2 = square[rowInChar2][columnInChar1];
}

/* QUESTION 4 */
void encode(char square[6][6], const char prepared[100], char encoded[100]) {
    int index = 0;
    char out1, out2;
    // go through prepared until null character
    while (prepared[index] != '\0') {
       // choose the current letter in prepared and susceeding letter to endcode (those are the bigrams)
       bigram(square, prepared[index], prepared[index + 1], out1, out2);
       // add encoded letters to encoded
       encoded[index] = out1;
       encoded[index + 1] = out2;
       // since two letters processed, increase index by 2
       index += 2;
    }
    // since encoded is a string, add a null character at the end
    encoded[index] = '\0';
}

