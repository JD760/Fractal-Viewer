/* main.c - Fractal viewer, a program to explore the world of fractal geometry */

/* system includes */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* project includes */
#include "bitmap.h"
#include "fractals.h"
/* externs */
/* defines */
/* typedefs */
/* globals */
/* function prototypes */

/* program */

int main(int argc, char *argv[])
{
    /* user-defined variables */
    int width = 1920;
    int height = 1080;
    Point center = {0.0, 0.0};
    unsigned short maxIterations = 1000;
    long double scale = 1.0;

    /* calculated variables */
    int paddingBytes = 4 - ((width * 3) % 4);
    if (paddingBytes == 4) paddingBytes = 0;
    // (width of each row in bytes * height) + header size
    int fileSize = (((width * 3) + paddingBytes) * height) + 54;
    unsigned char *bitmapData = malloc(sizeof(unsigned char) * fileSize);
    unsigned short *iterationData = malloc(sizeof(unsigned short) * (width * height));

    /* program */

    time_t start = time(NULL);

    createBitmap(width, height, paddingBytes, fileSize, bitmapData);
    printf("Created bitmap data\n");
    iterateMandelbrot(width, height, scale, maxIterations, iterationData, center);
    printf("created iteration data\n");
    modulusColouring(bitmapData, iterationData, width, height, paddingBytes, maxIterations);
    printf("Created colouring data\n");
    writeBitmap(bitmapData, width, height, fileSize);
    printf("Written bytes into bitmap image data\n");
    time_t end = time(NULL);
    printf("Execution time: %f\n", difftime(end, start));
}

/* functions */