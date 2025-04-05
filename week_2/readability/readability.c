#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* query_user(const char *query) {
    // Declare the response pointer
    char *answer = NULL;
    size_t size = 0;

    // Ask the question
    printf("%s", query);
    
    // Get the answer & allocate memory
    getline(&answer, &size, stdin); // Use getline to read the entire line

    // Return the answer
    return answer;
}

int count_sentences(const char *phrase) {
    // count the sentences in the phrase
    int sc = 0;
    int i;
    for (i = 0; i < strlen(phrase); i++){
        if (phrase[i] == '.' || phrase[i] == '!' || phrase[i] == '?') { 
            sc += 1;
        }
    }
    return sc;
}

int count_words(const char *phrase) {
    // count the number of words in the prase
    int wc = 0;
    int i;
    for (i = 0; i < strlen(phrase); i++){
        if (phrase[i] == ' ') { 
            wc += 1;
        }
    }
    // add 1 to wc as we assume there is a word after the last space
    wc++;
    return wc;
}

int count_letters(const char *phrase) {
    // count the letters in the phrase
    int lc = 0;
    
    // declare what a letter is (lowercase)
    char letters[26] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
        'u', 'v', 'w', 'x', 'y', 'z'
    };

    int i;
    for (i = 0; i < strlen(phrase); i++) {
        char lower_char = tolower(phrase[i]);
        for (int j = 0; j < 26; j++) {
            if (lower_char == letters[j]) {
                lc += 1;
                break;
            }
        }
    }
    return lc;
}

float get_gradelevel(const int sentences, const int words, const int letters) {
    printf("Getting Grade Level: \n");
    // L = average number of letters per 100 words
    float l = (float)letters / (float)words * 100.0;
    // S = average number of sentences per 100 words
    float s = (float)sentences / (float)words * 100.0;
    // Turn input string into a vector of sentences, count, divide by 100
    float f_index = (0.0588 * l) - (0.296 * s) - 15.8;
    int index = (int)f_index;
    return index;
}

int main(void) {
    // Get the phrase from the user
    char *phrase = query_user("Please enter a text to evaluate: ");
    // count the sentences, letters, words
    int sentences = count_sentences(phrase);
    int words = count_words(phrase);
    int letters = count_letters(phrase);

    // Print grade levels
    int gradelevel = get_gradelevel(sentences, words, letters);

    if (gradelevel <= 1) { 
        printf("Before Grade 1\n"); 
    }
    else if (gradelevel >= 16) { 
        printf("Grade 16+\n"); 
    }
    else { printf("Grade %i\n", gradelevel); }

    free(phrase);
    return 0;
}