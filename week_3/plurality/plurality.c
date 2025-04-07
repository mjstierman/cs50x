// #include <cs50.h>
// #include <char*.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char* name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
int get_int(const char *query);
int print_winner(void);
char* query_user(const char *query);
bool vote(char* name);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char* name = query_user("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

int get_int(const char *query) {
    char *answer = query_user(query);
    int length = sizeof(*answer) / sizeof(*answer);
    // if any of the answer is a character, return 0
    for (int i = 0; i < length; i++) {
        if (isalpha(answer[i])) {
            printf("Invalid number\n");
            exit(3);
        }  
    }
    int number = atoi(answer);
    return number;
}

// Print the winner (or winners) of the election
int print_winner(void)
{
    // Find the maximum number of votes
    char* winners[candidate_count];
    int most_votes = 0;
    int winner_index = 0;

    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > most_votes) {
            most_votes = candidates[i].votes;
            winners[winner_index] = candidates[i].name;
            winner_index += 1;
        }
        if (candidates[i].votes == most_votes && strcmp(candidates[i].name, winners[winner_index-1]) != 0 ) {
            winners[winner_index] = candidates[i].name;
            winner_index += 1;
        }
    }

    // Print the candidate (or candidates) with maximum votes
    for (int i = 0; i < winner_index; i++) {
        printf("Your winner is: %s\n", winners[i]);
    }
    return 0;
}

char* query_user(const char *query) {
    // Declare the response pointer
    char *answer = NULL;
    size_t size = 0;

    // Ask the question
    printf("%s", query);
    
    // Get the answer & allocate memory
    getline(&answer, &size, stdin); // Use getline to read the entire line

    // Remove the newline character if it exists
    size_t len = strlen(answer);
    if (len > 0 && answer[len - 1] == '\n') {
        answer[len - 1] = '\0'; // Replace newline with null terminator
    }

    // Return the answer
    return answer;
}

// Update vote totals given a new vote
bool vote(char* name)
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++) {
        // Check if candidate's name matches given name
        if (strcmp(name, candidates[i].name) == 0) {
            // If yes, increment candidate's votes and return true
            candidates[i].votes += 1;
            return true;
        }
    }
    // If no match, return false
    return false;
}