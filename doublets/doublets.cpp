#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */
bool valid_step(const char* current_word, const char* next_word) {
    int differenceCount = 0;
    int curWordLen = strlen(current_word);
    int nextWordLen = strlen(next_word);
    if (curWordLen != nextWordLen) {
        return false;
    }
    // compare each letter of the two words
    for (int i = 0; current_word[i] != '\0' || next_word[i] != '\0'; i++) {
        // if letters different, increase count
        if (current_word[i] != next_word[i]) {
            differenceCount++;
        }
    }
    // if count exactly 1 and word part of the glossary, then return true
    if (differenceCount == 1 && dictionary_search(next_word)) {
        return true;
    }
    // else, return false
    return false;
}

/* QUESTION 2 */

bool display_chain(const char** chain, std::ostream& out) {
    // number of elements in array
    int numElements = 0;
    // buffer to modify words
    char buffer[256];

    for(int i = 0; chain[i] != nullptr; i++) {
        numElements++;
    }
    
    // go through every element in array 
    for (int i = 0; chain[i] != nullptr; i++) {
        // failure? return false
        if (out.fail()) {
            return false;
        }
        // output the first and last element in capital letters
        if (i == 0 || i == numElements - 1) {
            out << chain[i] << endl;
            continue;
        }
        // copy the rest one by one to the buffer and turn them into lowercase words
        strcpy(buffer, chain[i]);
        word_to_lower(buffer);
        out << buffer << endl;
    }
    return true;
}

void word_to_lower(char* word) {
    while (*word != '\0') {
        *word = tolower(*word);
        word++;
    }
}

/* QUESTION 3 */
bool valid_chain(const char** chain) {
    int numElements = 0;
  
    for(int i = 0; chain[i + 1] != nullptr; i++) {
        numElements = i + 1;
        if (seen_before(chain, chain[i + 1], i)) {
            return false;
        }

        if (!valid_step(chain[i], chain[i + 1])) {
            return false;
        }
    }
    if (numElements == 0) {
        return false;
    }
    return true;
}

bool seen_before(const char** chain, const char* word, int pos) {
    for (int i = 0; i < pos; i++) {
        if (!strcmp(chain[i], word)) {
            return true;
        }
        }
    return false;
}

/* QUESTION 4 */
bool find_chain(const char* start_word, const char* target_word, const char** answer_chain, int max_steps, int current_step) {
    ifstream fin;
    fin.open("words.txt");
    char currentWord[256];
    char* wordOnHeapPtr;
    // if current step is 0, add start word to chain 
    if (current_step == 0)  {
        answer_chain[0] = start_word;
        // find next word for chain
        if (find_chain(start_word, target_word, answer_chain, max_steps, current_step + 1)) {
            return true;
        }
        return false;
    }

    if (current_step > max_steps) {
        return false;
    }
    // add target_word to chain if the target_word is a valid step 
    if (valid_step(answer_chain[current_step - 1], target_word)) {
        answer_chain[current_step] = target_word;
        answer_chain[current_step + 1] = nullptr;
        return true;
    }

    fin >> currentWord;

    while (!fin.eof()) {
        // to reduce the number of recursions, only add words that are a valid step
        if (valid_step(answer_chain[current_step - 1], currentWord)) {
            // allocate memory for the word on the heap
            try {
                wordOnHeapPtr = new char[strlen(currentWord) + 1];
            }
            catch (bad_alloc) {
                cerr << "error in allocating memory on the heap\n";
            }
           // copy current word to the allocated memory on the heap
            strcpy(wordOnHeapPtr, currentWord);
            // add the word on the heap to the chain, end the chain with a nullptr 
            answer_chain[current_step] = wordOnHeapPtr;
            answer_chain[current_step + 1] = nullptr;
            if (valid_chain(answer_chain)) {
                // if chain valid, look for the next word
                if (find_chain(start_word, target_word, answer_chain, max_steps, current_step + 1)) {
                fin.close();
                return true;
                }
                // word did not lead to a solution, make it a nullptr in the chanin and the delete the word on the heap
                answer_chain[current_step] = nullptr;
                delete wordOnHeapPtr;
            }
        }
        fin >> currentWord;
    }

    fin.close();
    return false;
}
