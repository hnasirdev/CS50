
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    //Only 1 arguement can be passed
    if (argc==2){
        // Gives us an actual int for what was entered
        int key = atoi(argv[1]);

        //Take a string from user
        string plaintext = get_string("PLAINTEXT: ");
        string ciphertext= plaintext;

        for (int i=0; i<strlen(plaintext); i++){

            //If text is part of the alphabet, then do this
            if(isalpha(plaintext[i]))
            {
                //Is the text provided an Upper case, retain it as upper case
                if(isupper(plaintext[i]))
                {
                    //Create an alphabetical index
                    plaintext[i]=plaintext[i]-65;

                    ciphertext[i]=(plaintext[i]+key)%26;
                    ciphertext[i]=ciphertext[i]+65;
                }
                if(islower(plaintext[i]))
                {
                    plaintext[i]=plaintext[i]-97;
                    ciphertext[i]=(plaintext[i]+key)%26;
                    ciphertext[i]=ciphertext[i]+97;
                }

            }
            //Otherwise do this
            else
                ciphertext[i]=plaintext[i];
        }
        printf("ciphertext: %s\n", ciphertext);

    }

    else{

        printf("Error, incorrect input \n");
        return 1;
    }


}
