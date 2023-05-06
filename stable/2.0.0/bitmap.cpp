#include <math.h>
#include <iostream>

#include "bitmap.hpp"

/*
* Create an array of bytes and add file and bitmap headers to create an
* image, with space for pixel data reserved but not used or zeroed-out
*
* returns: a pointer to the byte array that contains all
* of the image data
*/
void createBitmap(
    int width,  // image width in pixels
    int height, // image height in pixels
    // number of bytes to make each image row a multiple of 4 bytes long
    int paddingBytes,
    int fileSize, // size of the bitmap in bytes
    unsigned char *bitmapData // array representing all image data
)
{
    /* variable declarations */

    /* code */

    // FILE HEADER //
    bitmapData[0] = 'B';
    bitmapData[1] = 'M';

    // file size (int -> 4 bytes)
    splitBytes(bitmapData, 2, fileSize);

    // reserved area
    bitmapData[6] = 0;
    bitmapData[7] = 0;
    bitmapData[8] = 0;
    bitmapData[9] = 0;

    // pixel data offset (always 54 with selected headers)
    bitmapData[10] = 54;
    bitmapData[11] = 0;
    bitmapData[12] = 0;
    bitmapData[13] = 0;

    // - BITMAP HEADER - //
    
    // header size
    bitmapData[14] = 40;
    bitmapData[15] = 0;
    bitmapData[16] = 0;
    bitmapData[17] = 0;

    // width (int -> 4 bytes)
    splitBytes(bitmapData, 18, width);

    // height (use byte splitting later)
    splitBytes(bitmapData, 22, height);

    // reserved
    bitmapData[26] = 1;
    bitmapData[27] = 0;

    // bits per pixel (RGB = 24)
    bitmapData[28] = 24;
    bitmapData[29] = 0;

    // compression method
    bitmapData[30] = 0;
    bitmapData[31] = 0;
    bitmapData[32] = 0;
    bitmapData[33] = 0;

    // size of pixel data
    splitBytes(bitmapData, 34, ((width * 3) + paddingBytes) * height);

    // horizontal resolution (pixels per metre)
    bitmapData[38] = 10;
    bitmapData[39] = 0;
    bitmapData[40] = 0;
    bitmapData[41] = 0;

    // vertical resolution (pixels per metre)
    bitmapData[42] = 10;
    bitmapData[43] = 0;
    bitmapData[44] = 0;
    bitmapData[45] = 0;

    // colour pallette - RGB doesn't need one
    bitmapData[46] = 0;
    bitmapData[47] = 0;
    bitmapData[48] = 0;
    bitmapData[49] = 0;
    
    // number of important colours
    bitmapData[50] = 0;
    bitmapData[51] = 0;
    bitmapData[52] = 0;
    bitmapData[53] = 0;
    return;
}

/*
* Splits a 4 byte number into 4 elements of a byte array, according to
* processor endianness which is checked within the function
*/
void splitBytes(
    unsigned char *arr, // array to write bytes to 
    int startAddr, // where to start writing bytes
    int num // the number to encode into 4 bytes
)
{
    // test the processor endianness to ensure bytes are written in
    // the correct order 
    int endianTestInt = 1;
    int endian = 0; // 0 is little endian, 1 is big endian

    if (*(char *)&num != 1)
    {
        endianTestInt = 1;
    }

    // if the processor is little-endian
    if (endian == 0)
    {
        if (num >= 16777216)
        {
            arr[startAddr + 3] = floor(num / 16777216);
            /* find the remainder after x multiples have been
            written to the current byte */
            num = num % 16777216; 
        }
        if (num >= 65536)
        {
            arr[startAddr + 2] = floor(num / 65536);
            num = num % 65536;
        }
        if (num >= 256)
        {
            arr[startAddr + 1] = floor(num / 256);
            num = num % 256;
        }
        arr[startAddr] = num;
    }
    // if the processor is big-endian
    else
    {
        if (num >= 16777216)
        {
            arr[startAddr] = floor(num / 16777216);
            num = num % 16777216;
        }
        if (num >= 65536)
        {
            arr[startAddr + 1] = floor(num / 65536);
            num = num % 256;
        }
        if (num >= 256)
        {
            arr[startAddr + 2] = floor(num / 65536);
            num = num % 256;
        }
        arr[startAddr + 3] = num;
    }
}


/*
* write out the bytes in a bitmap data array to create the image
* file name has a maximum length of 64 characters
*/
void writeBitmap(
    unsigned char *bitmapData,
    int fileSize
)
{
    // variable declaration

    FILE *fp;
    // code

    fp = fopen("fractal.bmp", "w+");

    // write each byte in the bitmap data to the output file
    for (int i = 0; i < fileSize; i++)
    {
        fputc(bitmapData[i], fp);
    }
}