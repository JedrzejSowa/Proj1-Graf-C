#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "extract.h"

static int word_to_number(const char *word) {
    if (strcasecmp(word, "zero") == 0) return 0;
    if (strcasecmp(word, "one") == 0) return 1;
    if (strcasecmp(word, "two") == 0) return 2;
    if (strcasecmp(word, "three") == 0) return 3;
    if (strcasecmp(word, "four") == 0) return 4;
    if (strcasecmp(word, "five") == 0) return 5;
    if (strcasecmp(word, "six") == 0) return 6;
    if (strcasecmp(word, "seven") == 0) return 7;
    if (strcasecmp(word, "eight") == 0) return 8;
    if (strcasecmp(word, "nine") == 0) return 9;
    if (strcasecmp(word, "ten") == 0) return 10;
    return -1; 
}

// Funkcja wyciągająca liczbę z ciągu wejściowego
int extract_number(const char *input) {
    char word[16];
    const char *ptr = input;
    while (*ptr) {
        if (isdigit(*ptr)) {
            return atoi(ptr);
        }

        if (isalpha(*ptr)) {
            int i = 0;
            while (isalpha(*ptr) && i < (int)(sizeof(word) - 1)) {
                word[i++] = *ptr;
                ptr++;
            }
            word[i] = '\0';

            int number = word_to_number(word);
            if (number != -1) {
                return number;
            }
        } else {
            ptr++;
        }
    }
    return -1;
}
