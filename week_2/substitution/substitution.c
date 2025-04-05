#include <ctype.h>
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

char letter_lookup(char letter, char* key) {
    char cryptletter;

    // Build the matrixes
    char upper_dict[2][26];
    char lower_dict[2][26];
    if (strlen(key) == 26) {
        int j;
        for (j = 0; j < 26; j++) {
            upper_dict[0][j] = 'A' + j;
            lower_dict[0][j] = 'a' + j;
        }
        // populate the second rows with the key 
        for (j = 0; j < 26; j++) {
            upper_dict[1][j] = toupper(key[j]);
            lower_dict[1][j] = tolower(key[j]);
        }
    }

    // if the letter is uppercase, match it to the letter in row 0
    if (isupper(letter)) {
        int j;
        for (j = 0; j < 26; j++) {
            if (upper_dict[0][j] == letter) {
                cryptletter = upper_dict[1][j];
                printf("Cryptletter: %c\n", cryptletter);
                break;
            }
        }
    }
    // if the letter is lowercase, match it to the letter in row 0
    else if (islower(letter)) {
        int j;
        for (j = 0; j < 26; j++) {
            if (lower_dict[0][j] == letter) {
                cryptletter = lower_dict[1][j];
                break;
            }
        }
    }

    return cryptletter;
}

char* encrypt_message(char *message, char* key) {
    // Iterate through the message and look up the letter
    int i;
    char* cyphertext = malloc(strlen(message));
    for (i = 0; i < strlen(message); i++) {
        // look up letter and add to message
        if (isalpha(message[i])) {
            cyphertext[i] = letter_lookup(message[i], key);
        }
        else { cyphertext[i] = message[i]; }
    }
    return cyphertext;
}

int main(int argc, char *argv[]) {
    // Validate the input
    // Ensure a key was passed
    if (argc != 2) {
        printf("Usage: ./substitution 26LETTERKEY\n");
        return 1;
    }
    // Ensure the key was 26 chars long
    if (strlen(argv[1]) != 26) {
        printf("Usage: ./substitution 26LETTERKEY\n");
        return 2;
    }
    // Ensure the key consisted of only alpha characters
    int i;
    for (i = 0; i < strlen(argv[1]); i++) {
        if (!isalpha(argv[1][i])) {
            printf("Usage: ./substitution 26LETTERKEY\n");
            return 3;
        }
    }
    // Once validated, store the key
    char* key = argv[1];

    // Process the message
    char *message = query_user("Please enter a phrase to encrypt: ");
    char *cyphertext = malloc(strlen(message));
    cyphertext = encrypt_message(message, key);

    // Display the results
    printf("Your plain text was: %s\n", message);
    printf("Your encrypted text is: %s\n", cyphertext);

    return 0;
}