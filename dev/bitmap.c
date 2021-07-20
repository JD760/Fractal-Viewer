/* main.c - Fractal viewer, a program to explore the world of fractal geometry */

/* system includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* project includes */
/* externs */
/* defines */
/* typedefs */
/* globals */
/* function prototypes */


/*
* Create an array of bytes and add file and bitmap headers to create an
* image, with space for pixel data reserved but not used or zeroed-out
*
* returns: a pointer to the byte array that contains all of the image data
*/
unsigned char *createBitmap(
    int width,  // image width in pixels
    int height // image height in pixels
)
{
    /* variable declarations */
    int fileSize; // the size of the image to be created in bytes
    unsigned char *bitmap; // byte array containing all image data
    int numPaddingBytes; // number of bytes to pad each row of pixels


    /* code */

    numPaddingBytes = 4 - ((width * 3) % 4);
    // above formula fails to work when 0 padding bytes required
    // this allows the padding bytes to always be correctly calculated
    if (numPaddingBytes == 4) numPaddingBytes = 0;

    // (width * 3) is used as each pixel is 3 bytes. 54 is the size of
    // the file and bitmap headers
    fileSize = (((width * 3) + numPaddingBytes) * height) + 54; 

    bitmap = malloc(sizeof(unsigned char) * fileSize);
    // ensure memory has actually been allocated
    if (bitmap != 0) printf("Failed to allocate memory\n"); return;

    // FILE HEADER //
    bitmap[0] = 'B';
    bitmap[1] = 'M';

    // file size (int -> 4 bytes)
    splitBytes(bitmap, 2, fileSize);

    // reserved area
    bitmap[6] = 0;
    bitmap[7] = 0;
    bitmap[8] = 0;
    bitmap[9] = 0;

    // pixel data offset (always 54 with selected headers)
    bitmap[10] = 54;
    bitmap[11] = 0;
    bitmap[12] = 0;
    bitmap[13] = 0;

    // - BITMAP HEADER - //
    
    // header size
    bitmap[14] = 40;
    bitmap[15] = 0;
    bitmap[16] = 0;
    bitmap[17] = 0;

    // width (int -> 4 bytes)
    splitBytes(bitmap, 18, width);

    // height (use byte splitting later)
    splitBytes(bitmap, 22, height);

    // reserved
    bitmap[26] = 1;
    bitmap[27] = 0;

    // bits per pixel (RGB = 24)
    bitmap[28] = 24;
    bitmap[29] = 0;

    // compression method
    bitmap[30] = 0;
    bitmap[31] = 0;
    bitmap[32] = 0;
    bitmap[33] = 0;

    // size of pixel data
    splitBytes(bitmap, 34, ((width + numPaddingBytes) * 3) * height);

    // horizontal resolution (pixels per metre)
    bitmap[38] = 10;
    bitmap[39] = 0;
    bitmap[40] = 0;
    bitmap[41] = 0;

    // vertical resolution (pixels per metre)
    bitmap[42] = 10;
    bitmap[43] = 0;
    bitmap[44] = 0;
    bitmap[45] = 0;

    // colour pallette - RGB doesn't need one
    bitmap[46] = 0;
    bitmap[47] = 0;
    bitmap[48] = 0;
    bitmap[49] = 0;
    
    // number of important colours
    bitmap[50] = 0;
    bitmap[51] = 0;
    bitmap[52] = 0;
    bitmap[53] = 0;

    /* returns a pointer to the array of bytes - this is used later to
    * add pixel data in the colouring functions 
    */
    return bitmap;
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
    unsigned char *data,
    int fileSize,
    char fileName[68]
)
{
    // variable declaration
    FILE *fp;
    // code
    strcat(fileName, ".bmp");
    fp = fopen(fileName, "w+");

    // write each byte in the bitmap data to the output file
    for (int i = 0; i < fileSize; i++)
    {
        fputc(data[i], fp);
    }
}