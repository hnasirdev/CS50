# Questions

## What's `stdint.h`?

It is a header file in the C standard library which provides exact data type sizes that
remain the same under any platform

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

This specifies exactly which type of data type to deal with and will not give any complications when moving from one
computer that deals with 16-bt and another which might interpret an int (for eg) as a 32 bit.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1 byte in a byte
4 bytes in a DWORD (32 bit)
4 bytes in a LONG (32 bit)
2 bytes in a WORD (2 bit)
## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

TODO

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the bmp file. biSize is the size of the structure.
Both in bytes.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount specifies the BMP's color depth - the number of bits per
pixel.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

fopen might return a NULL pointer if the file that fopen is trying to
write to doesn't exist.

## Why is the third argument to `fread` always `1` in our code?

fread's third argument is always 1 because we are iterating over every
pixel.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

If biWidth is 3:
int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4 = 3.
his step ensures the number of bytes in every row is a multiple of 4

## What does `fseek` do?

fseek allows us to change the offset of a pointer.

## What is `SEEK_CUR`?

SEEK_CUR is the current position indicator in the file.
