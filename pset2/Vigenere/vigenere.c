#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{



     //Only 1 arguement can be passed
    if (argc==2)
    {
        string key= argv[1];
        int key_num[strlen(argv[1])];
        int k=strlen(key); //length of key
        //ensure all characters are alphbetical

        for(int i=0; i<k;i++)
        {
            //if any of the characters are not part of the alphabet, give error
            if(!isalpha(key[i])){
                printf("Key should only be from the alphabet");
                return 1;
            }
            if(isupper(key[i]))
                key_num[i]=key[i]-'A';
            if(islower(key[i]))
                key_num[i]=key[i]-'a';
     //       printf("key_num[%d] is %d",i,key_num[i]);

        }

        string plaintext = get_string("plaintext: ");
        int a =strlen(plaintext);
        int c=0;
        printf("ciphertext: ");


        for (int i=0, j=0; i<a; i++)
        {
             if(j==k) // j is equal to key length - 1
             {
                j=0;
             }
             //If text is part of the alphabet, then do this
            if(isalpha(plaintext[i]))
            {
                // is the plaintext char uppercase
                if(isupper(plaintext[i]))
                {
                    //is the key upper case
                    if(isupper(key[j]))
                    {
                        c = ((((int)plaintext[i]-65)+((int)key[j]-65))%26);
                        c+=65;
                        printf("%c",(char)c);
                    }
                    if(islower(key[j]))
                    {
                        c = ((((int)plaintext[i]-65)+((int)key[j]-97))%26);
                        c+=65;
                        printf("%c",(char)c);
                    }
                }
                else if(islower(plaintext[i]))
                {
                    if(isupper(key[j]))
                    {
                        c = ((((int)plaintext[i]-97)+((int)key[j]-65))%26);
                        c=c+97;
                        printf("%c",(char)c);
                    }
                    if(islower(key[j]))
                    {
                        c = (( ((int)plaintext[i]-97) + ((int)key[j]-97) )%26);
                        c=c+97;
                        printf("%c",(char)c);
                    }
                }
                j++;

            }
            else{
                printf("%c", plaintext[i]);
            }

        }
        printf("\n");





       // printf("ciphertext: %s\n", ciphertext);
      // printf("ciphertext: %s\n", plaintext);
    }
    else
    return 1;

}



