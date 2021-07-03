#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int pixelsToBitmap(int width, int height);
void splitBytes(unsigned char *arr, int startAddr, int num);
void createPixelData(int startingIndex, unsigned char *bitmap, int pixelDataSize, int paddingBytes, int width, int height);
void calculatePoint(int h, int currentByteNum, int width, int height, unsigned char *colourBGR);

int main()
{
    time_t seconds;
    seconds = time(NULL);
    pixelsToBitmap(640, 400); // 640 x 400 for mandelbrot


    // leave this last
    printf("Program execution time: %ld\n", time(NULL) - seconds);
    return 0;
}

void createPixelData(int startingIndex, unsigned char *bitmap, int pixelDataSize, int paddingBytes, int width, int height)
{
    int currentByteNum = 0;
    int totalBytesIterated = 0;
    unsigned char *ColourBGR = malloc(sizeof(unsigned char) * 3);
    for (int h = 0; h < height; h++)
    {
        currentByteNum = 0;
        // set pixel colours
        while (currentByteNum < (width * 3))
        {
            calculatePoint(h, currentByteNum, width, height, ColourBGR);

            bitmap[startingIndex + totalBytesIterated] = ColourBGR[0];
            bitmap[startingIndex + totalBytesIterated + 1] = ColourBGR[1];
            bitmap[startingIndex + totalBytesIterated + 2] = ColourBGR[2];
            totalBytesIterated+= 3;
            currentByteNum+= 3;
        }
        // add padding
        for (int i = 0; i < paddingBytes; i++)
        {
            //printf("Byte number: %d , value: %d , bitmap index: %d\n", totalBytesIterated, 0, startingIndex + totalBytesIterated);
            bitmap[startingIndex + totalBytesIterated] = 0;
            totalBytesIterated++;
        }
    }
}

void calculatePoint(int h, int currentByteNum, int width, int height, unsigned char *colourBGR)
{
    // x,y position of pixel
    int x = currentByteNum / 3;
    int y = h;
    int iterations = 100;
    int zoom = 1;
    int cenX = 0;
    int cenY = 0;
    int inSet = 1;
    // calculate whether pixel is in the mandelbrot set
    int i = 0; // keep track of how many iterations have passed

    // initial values for real and imaginary components
    long double point[2];
    point[0] = (x - width/2) * (4/width) * (16/(9 * zoom)) + cenX;
    point[1] = (y - height/2) * (4/height) * (1/zoom) + cenY;

    long double currentVal[2];
    currentVal[0] = 0; currentVal[1] = 0;

    while ( i < iterations && inSet == 0)
    {
        currentVal[0] = (currentVal[0] * currentVal[0]) - (currentVal[1] * currentVal[1]) + point[0];
        currentVal[1] = (2 * currentVal[0] * currentVal[0]) + point[1];
        i++;
        if (currentVal[0] > 2)
        {
            inSet = 0;
            break;
        }
    }

    if (inSet == 1)
    {
        colourBGR[0] = 0;
        colourBGR[1] = 0;
        colourBGR[2] = 0;
    }
    else
    {
        colourBGR[0] = 255;
        colourBGR[1] = 255;
        colourBGR[2] = 255;
    }

    printf("Point x: %d , y: %d inSet: %d\n", x,y,inSet);
}

// creates a bitmap file from a table of pixel data
// pixel data is an unsigned char (byte) array with 3 bytes per pixel, with each row of pixels
// padded to the next multiple of 4 bytes. First pixel is bottom left corner and progresses left to right
int pixelsToBitmap(int width, int height)
{
    int paddingBytes = 4 - ((width * 3) % 4); // works for all results of (width * 3) % 4 except 0
    if (paddingBytes == 4) paddingBytes = 0;
    // size of pixel data + size of headers
    int fileSize = (((width * 3) + paddingBytes) * height) + 54; 

    unsigned char *bitmap = malloc(sizeof(unsigned char) * fileSize);
    if(bitmap == NULL)
    {
        printf("Failed to allocate %d bytes of memory for bitmap array\n", fileSize);
        return 1; // exit code failure
    }
    else
    {
        printf("Successfully allocated %d bytes of memory for bitmap array\n", fileSize);
    }

    // - FILE HEADER - //

    // file signature
    bitmap[0] = 'B';
    bitmap[1] = 'M';

    // file size (use byte splitting later)
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

    // width
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

    // size of pixel data (use byte splitting later)
    splitBytes(bitmap, 34, ((width + paddingBytes) * 3) * height);

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

    // pixel data - 3 bytes (BGR)
    /*
    // bottom left pixel
    bitmap[54] = 0;
    bitmap[55] = 0;
    bitmap[56] = 255;
    // bottom right pixel
    bitmap[57] = 255;
    bitmap[58] = 255;
    bitmap[59] = 255;
    // padding - 2 bytes
    bitmap[60] = 0;
    bitmap[61] = 0;
    // top left pixel
    bitmap[62] = 255;
    bitmap[63] = 0;
    bitmap[64] = 0;
    // top right pixel
    bitmap[65] = 0;
    bitmap[66] = 255;
    bitmap[67] = 0;
    // padding - 2 bytes
    bitmap[68] = 0;
    bitmap[69] = 0;
    */

   createPixelData(bitmap[10], bitmap, ((width * 3) + paddingBytes) * height, paddingBytes, width, height);

    // write out file
    FILE *file;
    file = fopen("bitmap.bmp", "w+");
    for (int i = 0; i < fileSize; i++)
    {
        fputc(bitmap[i], file);
    }
    fclose(file);
    free(bitmap);
    return 0;
}

// splits a 32 bit integer into 4 bytes, arranged based on processor endianness
void splitBytes(unsigned char *arr, int startAddr, int num)
{
    // test endianness
    int endianTestInt = 1;
    int endian = 0; // 0 is little endian, 1 is big endian

    if (*(char *)&num != 1)
    {
        endianTestInt = 1;
    }

    if (endian == 0)
    {
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