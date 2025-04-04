#include <stdio.h>
#include <stdbool.h>

int get_ccn(void) {
    unsigned int answer = 0;
    // no cc numbers are less than 13 or longer than 16 numbers long
    while (answer < 3000000000000 || answer > 5100000000000000) { 
        printf("What is your Credit Card Number? ");
        scanf("%i", &answer);
    }
    return answer;
}

bool cc_checksum(int ccnum) {
    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    
    // return FALSE
    // return TRUE
}

char which_card(int ccnum) {
    // if array pos[1,2] are [3,4], [3,7]; print AmEx
    // if array pos[1,2] are 51, 52, 53, 54, or 55; print MC
    // if array pos[1] is 4 print Visa
    // else invalid
}

void main(void) {
    int ccn = get_ccn();
    printf("\nNumber: %d", ccn);
    if (cc_checksum(ccn) == true) {
        which_card(ccn);
    } else {
        printf("INVALID");
    }
}