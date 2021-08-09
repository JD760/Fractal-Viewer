#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned char BYTE;

void BMPmake(int width, int height, BYTE *pixelData);
void splitBytes(BYTE *arr, int startAddr, int num);

int main()
{
    int width = 4;
    int height = 1;
    BYTE *pixelData = malloc(sizeof(BYTE) * 1);
    BMPmake(width, height, pixelData);
}

void BMPmake(int width, int height, BYTE *pixelData)
{
    BYTE *bitmap = malloc(sizeof(BYTE) * 54);
    for(int i = 0; i < 55; i++) bitmap[i] = 0;
    // -- FILE HEADER -- //

    // bitmap signature
    bitmap[0] = 'B';
    bitmap[1] = 'M';

    // file size calculations

    int paddingBytes = 4 - ((width * 3 ) % 4);
    if (paddingBytes == 4)
    {
        paddingBytes = 0;
    }
    int widthBytes = (width * 3) + paddingBytes;
    // height is just image height as pixels are only 1 byte 'tall'
    int pixelStorageBytes = widthBytes * height;

    int fileSize = 40 + 14 + pixelStorageBytes; // file header + bitmap header + pixel data size
    splitBytes(bitmap, 2, fileSize);
    printf("File size will be: %d\n", fileSize);

    if (realloc(bitmap, fileSize) == NULL)
    {
        printf("Failed to change bitmap array size to %d bytes \n", fileSize);
        return;
    }   

    // reserved field (in hex. 00 00 00 00)
    bitmap[6] = 0;
    bitmap[7] = 0;
    bitmap[8] = 0;
    bitmap[9] = 0;

    // offset of pixel data (starting byte to first pixel data byte)
    bitmap[10] = 54;
    bitmap[11] = 0;
    bitmap[12] = 0;
    bitmap[13] = 0;

    // -- BITMAP HEADER -- // 

    // header size - doesn't include file header (bytes 1-14)
    bitmap[14] = 40;
    bitmap[15] = 0;
    bitmap[16] = 0;
    bitmap[17] = 0;

    // width and height of the image
    splitBytes(bitmap, 18, width);
    splitBytes(bitmap, 22, height); 

    // reserved field
    bitmap[26] = 1;
    bitmap[27] = 0;

    // number of bits per pixel
    bitmap[28] = 24; // 3 byte
    bitmap[29] = 0;

    // compression method (no compression here)
    bitmap[30] = 0;
    bitmap[31] = 0;
    bitmap[32] = 0;
    bitmap[33] = 0;

    // size of pixel data
    splitBytes(bitmap, 34, pixelStorageBytes);

    // horizontal resolution of the image - pixels per meter (2835)
    bitmap[38] = 0;
    bitmap[39] = 0;
    bitmap[40] = 48;
    bitmap[41] = 177;

    // vertical resolution of the image - pixels per meter (2835)
    bitmap[42] = 0;
    bitmap[43] = 0;
    bitmap[44] = 48;
    bitmap[45] = 177;

    // colour pallette information
    bitmap[46] = 0;
    bitmap[47] = 0;
    bitmap[48] = 0;
    bitmap[49] = 0;

    // number of important colours
    bitmap[50] = 0;
    bitmap[51] = 0;
    bitmap[52] = 0;
    bitmap[53] = 0;

    // -- PIXEL DATA -- //
    for(int i = 54; i < 66; i++)
    {
        bitmap[i] = 255;
    }

    // writing to bitmap file
    FILE *file;
    file = fopen("bitmap.bmp", "w+");
    for(int i = 0; i < bitmap[10]; i++) // write headers
    {
        fputc(bitmap[i], file);
    }
    // write pixel data
    for(int i = 54; i < fileSize; i++)
    {
        if ((i-54) % (width * 3) == 0 && i-54 != 0) // end of a row
        {
            for (int j = 0; j < paddingBytes; j++)
            {
                bitmap[i + j] = 0;
            }
            i += paddingBytes;
            printf("End of row at byte: %d\n", i);
        }
        else
        {
            bitmap[i] = 255;
            i+= 1;
        }
        printf("Byte %d written to pixeldata\n", i);
    }
    // clean up
    fclose(file);
    free(bitmap);
}

// splits num into 4 (consecutive) bytes at their respective addresses with startAddr being the least significant
// addr 1 is 1's, addr 2 is 256's etc.
void splitBytes(BYTE *arr, int startAddr, int num)
{
    //TODO: make this compatible with big-endian processors
    if (num >= 16777216)
    {
        arr[startAddr + 3] = floor(num / 16777216);
        // this can be done as byte has been set and avoids nested if's while being a little less concise
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