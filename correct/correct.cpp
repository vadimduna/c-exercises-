#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include "correct.h"

using namespace std;

    /* You are supplied with two helper functions */

    void ascii_to_binary(char ch, char* binary) {
    for (int n = 128; n; n >>= 1) 
        *binary++ = (ch & n) ? '1' : '0';
    *binary = '\0';
    }

    char binary_to_ascii(char* binary) {
    int ch = 0;
    for (int n=0, slide=128; n<8; n++, slide >>= 1) {
        if (binary[n] == '1')
        ch = ch | slide;
    }
    return ch;
    }

/* now add your own functions here */

/* QUESTION 1 */

void text_to_binary(const char* str, char encoded[512]) {
    char binary[9];

    if (*str != '\0') {
        ascii_to_binary(*str,binary);
        strcat(encoded, binary);
        text_to_binary(str + 1, encoded);
    }
    return;
}

void binary_to_text(const char* binary, char str[32]) {
    char ch;
    char binaryPart[9];
    int strIndex = 0;
    while (*binary != '\0') {
        for (int i = 0; i < 8 && *binary != '\0'; i++) {
        binaryPart[i] = *binary;
        binary++;
        }   
        binaryPart[8] = '\0';
        ch = binary_to_ascii(binaryPart);
        str[strIndex] = ch;
        strIndex++; 
    }
    str[strIndex] = *binary;
}

/* QUESTION 2 */

void add_error_correction(const char* data, char correct[512]) {
    int fourDataBits[4];
    int checkBit1, checkBit2, checkBit3;
    int correctIndex = 0;
    int correctBitsAsInt[7];

    while (*data != '\0') {
        for (int i = 0; i < 4 && *data != '\0'; i++) {
        fourDataBits[i] = static_cast<int>(*data - '0');
        data++;
        }
        checkBit1 = parity(fourDataBits[0], fourDataBits[1], fourDataBits[3]);
        checkBit2 = parity(fourDataBits[0], fourDataBits[2], fourDataBits[3]);
        checkBit3 = parity(fourDataBits[1], fourDataBits[2], fourDataBits[3]);
    
        correctBitsAsInt[0] = checkBit1;
        correctBitsAsInt[1] = checkBit2;
        correctBitsAsInt[2] = fourDataBits[0];
        correctBitsAsInt[3] = checkBit3;

        for (int i = 1; i < 7; i++) {
        correctBitsAsInt[i + 3] = fourDataBits[i];
        }

        for (int i = 0; i < 7; i++) {
            correct[correctIndex] = static_cast<char>(correctBitsAsInt[i] + '0');
            correctIndex++;
        }
    }
    correct[correctIndex] = '\0';
}

int parity(int a, int b, int c) {
    if ((a + b + c) % 2 == 0) {
        return 0;
    }

    return 1;
}

/* QUESTION 3 */

int decode(const char* received, char decoded[512]) {
    int sevenDataBits[7];
    int decodedBitsAsInts[4];
    int checkBit[3];
    int errors = 0;
    int decodedIndex = 0;
    while (*received != '\0') {
        for (int i = 0; i < 7 && *received != '\0'; i++) {
            sevenDataBits[i] = static_cast<int>(*received - '0');
            received++;
            }
            checkBit[0] = parity(sevenDataBits[3], sevenDataBits[4], sevenDataBits[5], sevenDataBits[6]);
            checkBit[1] = parity(sevenDataBits[1], sevenDataBits[2], sevenDataBits[5], sevenDataBits[6]);
            checkBit[2] = parity(sevenDataBits[0], sevenDataBits[2], sevenDataBits[4], sevenDataBits[6]);

        if (!(checkBit[0] == 0 && checkBit[1] == 0 && checkBit[2] == 0)) {
            errors++;
            char errorPosStr[4];
            for (int i = 0; i < 3; i++) {
                errorPosStr[i] = static_cast<char>(checkBit[i] + '0');
                if (checkBit[i] != 0) {
                }
            }
            errorPosStr[3] = '\0';

            int errorPosInt = binaryToInt(errorPosStr);

            (sevenDataBits[errorPosInt - 1] == 0) ? sevenDataBits[errorPosInt - 1] = 1 : sevenDataBits[errorPosInt - 1] = 0;
        }

        for (int i = 0; i < 4; i++) {
            if (i == 0) {
                decodedBitsAsInts[i] = sevenDataBits[2];
                continue;
            }
            decodedBitsAsInts[i] = sevenDataBits[i + 3];
        }

        for (int i = 0; i < 4; i++) {
            decoded[decodedIndex] = static_cast<char>(decodedBitsAsInts[i] + '0');
            decodedIndex++;
        }
    }
    decoded[decodedIndex] = '\0';
    return errors;

}

int parity(int a, int b, int c, int d) {
     if ((a + b + c + d) % 2 == 0) {
        return 0;
    }

    return 1;
}

int binaryToInt(const char* errorPosStr) {
    int number = 0;
    const int MAX_POWER = 2;

    for (int i = 0; i < 3; i++) {
        if (*errorPosStr == '0') {
            errorPosStr++;
            continue;
        }
        number += static_cast<int>(pow(2, MAX_POWER - i));
        errorPosStr++;
    }
    return number;
}