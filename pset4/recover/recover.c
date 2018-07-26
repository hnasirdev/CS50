#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <stdint.h>

int main(int argc, string argv[])
{
    //If not 1 command line arguement, give an error.
    if (argc != 2)
    {
        fprintf(stderr, "Only one arguement is acceptable\n");
        return 1;
    }

    typedef uint8_t  BYTE;
     // remember filenames
    char *inputFile = argv[1];

    FILE *inptr = fopen(inputFile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", inputFile);
        return 2;
    }

    fseek(inptr, 0L, SEEK_END);
    long int sz;
    sz = ftell(inptr);
    int totalBlocks = sz/512;
    fseek(inptr, 0L, SEEK_SET);


    BYTE buffer_block[513];
    char jpg[sz];
    int jpg_counter=0;
    FILE *img=NULL;

    //loop through however many blocks there are
    for(int i =0; i<totalBlocks; i++){
        //put every 512 bytes in this buffer, unless it is the last buffer
        if((fread(buffer_block, 1, 512, inptr)!=512)){
            if(img!=NULL){
                  fclose(img);
              }
        }
        //if this buffer_block starts with these bytes it is a jpg
        else if(buffer_block[0]== 0xff && buffer_block[1]==0xd8 && buffer_block[2]==0xff && (buffer_block[3]& 0xf0)==0xe0){
              //close existing jpg file
              if(img!=NULL){
                  fclose(img);
              }
              //create a new jpg file
              sprintf(jpg, "%03i.jpg",jpg_counter);
              jpg_counter++;
              //open the new jpg file
              img = fopen(jpg, "w");

              //write whaterver is in the buffer to the new jpg file
              fwrite(buffer_block, 1, 512, img);

        }
        else if (img!=NULL){
            fwrite(buffer_block, 1, 512, img);
        }

    }



}