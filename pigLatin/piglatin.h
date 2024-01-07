#ifndef PIGLATIN_H
#define PIGLATIN_H

/* QUESTION 1 */
int findFirstVowel(const char* word);
bool isVowel(char letter, int position, int length);

/* QUESTION 2 */

void translateWord(const char* english, char piglatin []);

/* QUESTION 3 */
void translateStream(std::istream& input, std::ostream& output);

#endif
