// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int length = strlen(word);
    if (length > LENGTH+1) {
        printf("Word too long.");
        return false;
    }

    char *little_word[LENGTH + 1];

    // validate the word -> to lowercase
    for (int i = 0; i < length; i++) {
        if (isalpha(word[i])) {
            *little_word[i] = tolower(word[i]);
        }
        else if (word[i] == '\'') { // ignore the apostrophe as it is valid
            *little_word[i] = word[i];
        }
        else { 
            printf("Error. Could not read word.");
        }
    }
    // calculate its hash
    unsigned int hash_index = hash(*little_word); 

    // iterate through linked list @hash until found
    for(node *tmp = table[hash_index]; tmp != NULL; tmp = tmp->next) {
        if (strcmp(*little_word, tmp->word) == 0) {
            return true;
        } 
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    
    // ensure word exists
    if (word != NULL && word[0] != '\0') {
        int length = strlen(word);

        // create a temporary string to work with
        char *tmp = malloc((length + 1) * sizeof(char));

        if (tmp == NULL) {
            printf("Memory allocation failed.");
            return N+1;
        }

        // make sure all are letters and lower case
        for (int i = 0; i < length; i++) {
            if (isalpha(word[i])) {
                tmp[i] = tolower(word[i]);
            }
            else if (word[i] == '\'') { // ignore the apostrophe as it is valid
                tmp[i] = word[i];
            }
            else { 
                printf("Error. Could not read word.");
                free(tmp);
                // return a number > buckets in the hash table
                return N+1;
            }
        }
        
        // Null-terminate the string
        tmp[length] = '\0';

        // iterate through the word to create an arbitrary index
        // "a polynomial rolling hash"
        unsigned int h = 0;
        int p = 31; // A small prime number

        for (int i = 0; word[i] != '\0'; i++) {
            h = (h * p + word[i] - 'a' + 1) % N; // Adjust based on character
        }

        // return a number between 0 and N
        free(tmp);
        return h;
    }

    // handle any other errors
    else {
        printf("Error. Could not read word.");
        // return a number greater than the number of buckets in the hash table
        return N+1;
    }    
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // Verify the file was loaded
    if (source == NULL) {
        printf("Could not open file.");
        return false;
    }

    // Provision memory for copying the word
    char *word = malloc((LENGTH + 1) * sizeof(char));

    if (word == NULL) {
        printf("Could not create word.");
        return false;
    }

    // read the words
    while (fscanf(source, "%s", word) == 1) {
        // ensure the word isn't too long
        if (strlen(word) > LENGTH+1){
            printf("Word too long.");
            return false;
        }

        // hash the word to get index for dictionary
        int hash_index = hash(word); 

        // initialize the new node
        node *newnode = malloc(sizeof(struct node));
        // catch for malloc fail
        if (word == NULL) {
            printf("Could not create node.");
            return false;
        }

        strcpy(newnode->word, word);
        newnode->next=NULL; 
        
        node *tmp = table[hash_index]; // create temporary pointer
        if (table[hash_index]) { // if pointer is empty
            table[hash_index] = newnode; // add the new node
        }
        else {
            node *current = table[hash_index];
            while (current->next != NULL) {
                current = current->next; // Traverse to the end of the list
            }
            current->next = newnode; // Add the new node at the end
        }
    }

    // Close the dictionary file
    fclose(source);

    // if any errors occurred, false would be returned
    // if we get to end, then all was successful
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // iterate through buckets
    unsigned int count = 0; // initialize the counting
    // loop through the hash table
    for (int i = 0; i < N; i++) {
        // *tmp starts with the head of i, and iterates until it finds NULL
        for(node *tmp = table[i]; tmp != NULL; tmp = tmp->next) {
            count++; // if there is another item, add to the count
        }
    }
    // if all of the table->next are NULL, this returns 0
    return count; // return the count
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // loop through the hash table
    for (int i = 0; i < N; i++) {
        // *tmp starts with the head of i, and iterates until it finds NULL
        for(node *tmp = table[i]; tmp != NULL; tmp = tmp->next) {
            node *next = tmp->next; // Store the next node
            free(tmp); // free the tmp 
            tmp = next; // Move to the next node
        }
    }
    return true;
}
