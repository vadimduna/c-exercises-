#ifndef PLAYFAIR_H
#define PLAYFAIR_H

/* QUESTION 1 */
void prepare(const char* input, char output[100]);

/* QUESTION 2 */
void grid(const char* codeword, char playfair[6][6]);
bool occursBefore(const char str[], char letter, int pos);

/* QUESTION 3 */
void bigram(char square[6][6], char inchar1, char inchar2, char& outchar1, char& outchar2);

/* QUESTION 4 */
void encode(char square[6][6], const char prepared[100], char encoded[100]);

#endif