#include <stdio.h>
#include <cs50.h>

int main(void){

   //Do this till the user gives a valid input
   int rows;
    do{

         rows = get_int("Number to climb: ");
    }

    while(rows<0 && rows>24);


    for(int currentRow=0; currentRow<rows; currentRow++){

        //write spaces
        for(int x=0; x<(rows-(currentRow+1)) ; x++){
            printf(" ");
        }
        //write hashes
        for(int x=0; x<currentRow+1; x++){
           printf("#");
        }
        //Write end lines
        printf("\n");

    }

}