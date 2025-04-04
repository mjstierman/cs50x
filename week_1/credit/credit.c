#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool check_digit(const char *ccnum) {
    // printf("Checking sums...\n");
    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    // `strlen(ccnum)-2` gets the penultimate index in the array
    int cclength = strlen(ccnum);
    int checksum = 0;
    int i;

    for (i = cclength-2; i >= 0; i -= 2 ) {
        int digit = ccnum[i] - '0'; // Convert char to int
        int product = digit * 2;

        // Add the digits of the product to the checksum
        if (product < 10) {
            checksum += product;
        } 
        else {
            checksum += (product - 9);
        }
    }

    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    for (i = cclength - 1; i >= 0; i -= 2) {
        checksum += ccnum[i] - '0';
    }

    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    // bool valid = checksum % 10 == 0;
    // printf("Checksum valid? %b\n", valid);
    return (checksum % 10 == 0);
}

void id_bank(const char *ccnum) {
    // printf("Identifying bank...\n");
    // if array pos[1,2] are [3,4], [3,7]; print AmEx
    if ((ccnum[0] == '3' && ccnum[1] == '4') || (ccnum[0] == '3' && ccnum[1] == '7')) {
        printf("AMEX\n");
    }
    // if array pos[1,2] are 51, 52, 53, 54, or 55; print MC
    else if (ccnum[0] == '5' && (ccnum[1] >= '1' && ccnum[1] <= '5')) {
        printf("MASTERCARD\n");
    }
    // if array pos[1] is 4 print Visa
    else if (ccnum[0] == '4') {
        printf("VISA\n");
    }
    // else invalid
    else { printf("INVALID\n"); }
}

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

int main(void) {
    char *ccn = query_user("Enter Credit Card Number to verify: ");
    while (strlen(ccn) < 12 || strlen(ccn) > 16) {
        ccn = query_user("Enter Credit Card Number to verify: ");
    }
    printf("CCN: %s\n", ccn);
    if (check_digit(ccn) == true) {
        id_bank(ccn);
    } else {
        printf("INVALID\n");
    }
    return 0;
}