#include <cs50.h>
#include <stdio.h>

int main(void){

    int height;

    do{
         height = get_int("Height: ");
    }
    while(height>23 || height<0);


    for(int i=0; i<height; i++){
        // for every ith row, print height-ith+1 black spaces
        int blankSpace = height-(i+1);
        for(int x=0; x<blankSpace; x++){
            printf(" ");
        }
        //for every ith row, print i+2 #
        for(int x=0; x<(i+2); x++){
            printf("#");
        }
        printf("\n");


    }



}