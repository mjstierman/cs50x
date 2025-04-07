// #include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    char* name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, char* name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
char* query_user(const char *query);
int get_int(const char *query);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            // MJS replaced CS50's `get_string()` here with a simple printf/scanf
            // TODO: Update my `query_user()` to accept additional params for passing vars
            char* name;
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, char* name)
{
    // The function takes three arguments: voter, rank, and name.    
    for (int i = 0; i < candidate_count; i++) {
        // If name is a match for the name of a valid candidate
        if (strcmp(candidates[i].name, name) == 0) {
            // then you should update the global preferences array to indicate that the voter voter has that candidate as their rank preference
            preferences[voter][rank] = i;
            // If the preference is successfully recorded, the function should return true
            return true;
        }
    }
    // The function should return false otherwise. Consider, for instance, when name is not the name of one of the candidates.
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{   
    // The function should update the number of votes each candidate has at this stage in the runoff.
    // Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already been eliminated.
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++)
            if (candidates[i].eliminated == false) {
                candidates[preferences[i][j]].votes++;
            }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Find the maximum number of votes
    char* winners[candidate_count];
    int most_votes = 0;
    int winner_index = 0;

    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > most_votes && candidates[i].eliminated == false) {
            most_votes = candidates[i].votes;
            winners[winner_index] = candidates[i].name;
            winner_index += 1;
        }
    }

    // Print the candidate (or candidates) with maximum votes
    for (int i = 0; i < winner_index; i++) {
        printf("Your winner is: %s\n", winners[i]);
    }
    return true;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes < min) {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count-1; i++) {
        if (!candidates[i].eliminated && candidates[i].votes) {
            return true;
        }
        else { return false; }
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes <= min) {
            candidates[i].eliminated = true;
        }
    }
    return;
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