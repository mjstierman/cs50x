#include <ctype.h>
#include <stdio.h>
#include <string.h>

char* query_user(const char *query) {
    // declare the response pointer
    char *answer;
    // ask the question
    printf("%s", query);
    // get the answer & allocate memory
    scanf("%ms", &answer);
    // return the answer
    return answer;
}

int compute_score(const char *word) {
    // array to map chars to their assigned values
    const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    // initialize the score; get the word lenth
    int score = 0;
    int length = strlen(word);

    // count the score
    int i;
    for (i = 0; i < length; i++ ){
        score += POINTS[tolower(word[i]) - 'a'];
    }
    return score;
}

void main(void) {
    // prompt players
    char *player_1 = query_user("Please enter Player 1's word: ");
    char *player_2 = query_user("Please enter Player 2's word: ");
    
    // store the scores
    int player_1_score = compute_score(player_1);
    int player_2_score = compute_score(player_2);

    // declare the winner
    if ( player_1_score == player_2_score ) {
        printf("Tie!\n");
    }
    else if ( player_1_score > player_2_score ) {
        printf("Player 1 wins!\n");
    }
    else if ( player_1_score < player_2_score ) {
        printf("Player 2 wins!\n");
    }
    else { printf("Error\n"); }
}