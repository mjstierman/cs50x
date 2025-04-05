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

char* encrypt_message(char *message, int key) {
    printf("The message is: %s\n", message);
    
    int length = strlen(message);
    printf("The message length is: %i\n", length);
    char *cryptext = malloc(length);
    // Iterate through the message
    int i;
    for (int i = 0; i < length; i++) {
        char p = message[i];
        // only do things to letters.
        if (isalpha(p)) {
            // Handle upper case letters
            if (isupper(p)) {
                p = p - 65;
                char cryptletter = (p + key) % 26;
                cryptext[i] = cryptletter + 65;
            }
            // Handle lower case letters
            else if (islower(p)) {
                p = p - 97;
                char cryptletter = (p + key) % 26;
                cryptext[i] = cryptletter + 97;
            }
        }
        // everything just gets passed
        else { cryptext[i] = p; }
    }
    return cryptext;
}

int main(int argc, char *argv[]) {
    // Ensure the agument is passed and is a number
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);

    // Get phrase from user
    char *message = query_user("Please enter a phrase to encrypt: ");

    // Convert and send it
    char *cyphertext = encrypt_message(message, key);
    printf("Your plaintext was: %s\n", message);
    printf("Your cyphertext is: %s\n", cyphertext);
    free(cyphertext);
    return 0;
}