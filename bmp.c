#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct Colour{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct Point{
    long double x;
    long double y;
};

int pixelsToBitmap(int width, int height);
void splitBytes(unsigned char *arr, int startAddr, int num);
void createPixelData(int startingIndex, unsigned char *bitmap, int pixelDataSize, int paddingBytes, int width, int height);
struct Colour calculatePoint(int x, int y, int width, int height, short iterationsMax, long double scale, struct Colour pixelColour, struct Point center);

int main()
{
    time_t seconds;
    seconds = time(NULL);
    pixelsToBitmap(1920, 1080); // 640 x 400 for mandelbrot


    // leave this last
    printf("Program execution time: %ld seconds\n", time(NULL) - seconds);
    return 0;
}

void createPixelData(int startingIndex, unsigned char *bitmap, int pixelDataSize, int paddingBytes, int width, int height)
{
    long double scale = 1.0;
    struct Point center = {0.0, 0.0};
    short iterationsMax = 1000;
    int currentByteNum = 0;
    int totalBytesIterated = 0;
    struct Colour pixelColour;
    int x;
    int y;

    for (int h = 0; h < height; h++)
    {
        currentByteNum = 0;
        // set pixel colours
        while (currentByteNum < (width * 3))
        {
            x = currentByteNum / 3;
            y = h;
            pixelColour = calculatePoint(x, y, width, height, iterationsMax, scale, pixelColour, center);

            bitmap[startingIndex + totalBytesIterated] = pixelColour.blue;
            bitmap[startingIndex + totalBytesIterated + 1] = pixelColour.green;
            bitmap[startingIndex + totalBytesIterated + 2] = pixelColour.red;
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

struct Colour calculatePoint(int x, int y, int width, int height, short iterationsMax, long double scale, struct Colour pixelColour, struct Point center)
{
    // x,y position of pixel
    int iteration = 0;

    // complex plane goes from x = -2.5 to x = 1, y = -1 to y = 1
    // find scaled position of each pixel
    long double xPos = ((((1.0 / width) * x * 3.5) - 2.5) / scale) + center.x; // convert 0 -> width into -2.5 -> 1
    long double yPos = ((((1.0 / height) * y * 2) - 1) / scale) + center.y; // convert 0 -> height into -1 -> 1
    //printf("Scaled positions: x: %Lf , y: %Lf\n", xPos, yPos);
    struct Point c = {0.0,0.0};
    long double xTemp;

    while ((c.x * c.x) + (c.y * c.y) <= 4 && iteration < iterationsMax)
    {
        xTemp = c.x * c.x - c.y * c.y + xPos;
        c.y = (2 * c.x * c.y) + yPos;
        c.x = xTemp;

        //printf("iteration: %d , x: %Lf , y: %Lf\n", iteration, c.x, c.y);
        iteration += 1;
    }

    if (iteration == iterationsMax)
    {
        pixelColour.blue = 0;
        pixelColour.green = 0;
        pixelColour.red = 0;
    }
    else
    {
        pixelColour.blue = (iterationsMax - iteration) % 255;
        pixelColour.green = (iterationsMax - iteration) % 255;
        pixelColour.red = (iterationsMax - iteration) % 255;
    }
    //printf("x : %d , y: %d , iterations: %d\n", x, y, iteration);
    return pixelColour;
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

    // size of pixel data
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