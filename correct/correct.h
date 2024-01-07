#ifndef CORRECT_H
#define CORRECT_H

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char* binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

/* QUESTION 1 */
void text_to_binary(const char* str, char encoded[512]);
void binary_to_text(const char* binary, char str[32]);


/* QUESTION 2 */
void add_error_correction(const char* data, char correct[512]);
int parity(int a, int b, int c);

/* QUESTION 3 */

int decode(const char* received, char decoded[512]);
int parity(int a, int b, int c, int d);
int binaryToInt(const char* errorPosStr);
#endif