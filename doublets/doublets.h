#ifndef DOUBLETS_H
#define DOUBLETS_H

/*  This pre-supplied function looks up a given word in the dictionary
    of approved words. It is assumed that the input word is in uppercase.
    The function returns true if the word is in the dictionary.
    Otherwise returns false. */

bool dictionary_search(const char *word);

/* add your function prototypes here */

/* QUESTION 1 */

bool valid_step(const char* current_word, const char* next_word);

/* QUESTION 2 */
bool display_chain(const char** chain, std::ostream& out);
void word_to_lower(char* word);

/* QUESTION 3 */
bool valid_chain(const char** chain);
bool seen_before(const char** chain, const char* word, int pos);

/* QUESTION 4 */
bool find_chain(const char* start_word, const char* target_word, const char** answer_chain, int max_steps,  int current_step = 0);

#endif 