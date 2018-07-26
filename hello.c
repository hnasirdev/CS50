#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("hello, world.\n");
    char c = get_char("Answer: ");

    if (c =='y'){
        printf("yes\n");
    }else if(c=='n'){
        printf("no\n");
    }
}