// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
   // char *factor = argv[1];
    char *ptr;
    long ret = strtol(argv[1], &ptr, 10);
    //scale factor
    LONG scale = (LONG)ret;


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //determine old dimensions
    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    LONG old_width = bi.biWidth;
    LONG old_height = bi.biHeight;

    //Update the bf and bi header files before copying to scaled version
    bi.biWidth *=scale;
    bi.biHeight *=scale;
    //determine new padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage= (((sizeof(RGBTRIPLE)*bi.biWidth)+padding)*abs(bi.biHeight));
    bf.bfSize= bi.biSizeImage + sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    for (int i = 0, biHeight = abs(old_height); i < biHeight; i++)
    {
        for(int h=0; h<=(scale-1); h++){




            // iterate over pixels in scanline
            for (int j = 0; j < old_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
              //  RGBTRIPLE storage;
                 // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //repeat the pixel to scale it
                for(int a=0; a<=(scale-1); a++){
                    // write RGB triple to outfile n times
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            // skip over padding, if any
            fseek(inptr, padding_old, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }

            if (!(h==(scale-1))){
                //Go back in file unless this is copy of row for the last time
                fseek(inptr, -((old_width*3)+padding_old), SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);


    // close outfile
    fclose(outptr);

    // success
    return 0;
}
