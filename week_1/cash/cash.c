#include <stdio.h>

/*
In a file called cash.c in a folder called cash, implement a program in C that 
prints the minimum coins needed to make the given amount of change, in cents.
Prompt the user for an int greater than 0, so that the program works for 
any amount of change.
Re-prompt the user, again and again as needed, if their input is not greater 
than or equal to 0 (or if their input isn’t an int at all!).
*/

// how much was paid?
int query_user(void) {
    int answer;
    while (answer < 50) { 
        printf("How much was paid (in cents)? ");
        scanf("%d", &answer);
    }
    return answer;
}

// return the change owed in dollars
int calc_change(int payment) {
    int price = 50;
    int change = (payment - price);
    return change;
}

// return minimum number of coins
int calc_coins(int change) {
    int coin_count = 0;
    while (change > 24) {
        change = change - 25;
        coin_count++;
    }
    while (change > 9) {
        change = change - 10;
        coin_count++;
    }
    while (change > 4) {
        change = change - 5;
        coin_count++;
    }
    while (change > 0) {
        change = change -1;
        coin_count++;
    }
    return coin_count;
}

void main(void) {
    int paid = query_user();
    int change = calc_change(paid);
    int coinage = calc_coins(change);
    printf("Change owned: %d\n", change);
    printf("Number of Coins: %i\n", coinage);
}