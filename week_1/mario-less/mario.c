#include <stdio.h>
#include <ctype.h>

/*
implement a program in C that recreates that pyramid, using hashes (#) for 
bricks, as in the below:
But prompt the user for an int for the pyramid’s actual height, so that the 
program can also output shorter pyramids like the below:
Re-prompt the user, again and again as needed, if their input is not greater 
than 0 or not an int altogether.
*/

int query_user(void) {
    int answer = 0;
    // if 'answer' is less than 1, more than 10, or not a number, prompt the user
    while (answer < 1 || answer > 10) { 
        printf("How high should Mario jump (1-10)? ");
        scanf("%i", &answer);
    }
    return answer;
}

void print_rows(int answer) {
    int rows;
    int spaces;
    int hashes;
    for (rows = 0; rows < answer; rows++) {
        for (spaces = 0; spaces < answer-rows-1; spaces++)
            printf(" ");
        for (hashes = 0; hashes <= rows; hashes++)
            printf("#");
        printf("\n");
    }
}

int main(void) {
    // prompt the user for number of rows
    int answer = query_user();
    // print the rows
    print_rows(answer);
}

