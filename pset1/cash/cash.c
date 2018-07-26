#include <cs50.h>
#include <stdio.h>

int main(void){


    float cents;
    int counter=0;
    //int counter2=0;
    do{
        cents = get_float("Change owed: ");
    }

    while(cents<0.0); //while negative value keep repeating

    cents = cents*100; //gives value in cents

    int change = (int)cents;
    while (change>0){


        if(change>24){
            change = change-25;
            counter++;
        }
        else if (change>9){
            change=change-10;
            counter++;
        }
        else if(change>4){
            change=change-5;
            counter++;
        }
        else if(change>0){
            change=change-1;
            counter++;
        }
        else if(change==0){
            break;
        }


    }

    printf("%d\n", counter);
}