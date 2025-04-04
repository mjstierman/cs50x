#include <stdio.h>

int main(void)
{
    char answer[30];
    printf("hello, user.\n");
    printf("What\'s your name? ");
    scanf("%s", &answer);
    printf("Hello, %s.\n", answer);
}