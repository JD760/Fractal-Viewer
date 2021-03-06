/* fractals.c - Fractal viewer, a program to explore the world of fractal geometry */

/* system includes */
#include <stdlib.h>
#include <stdio.h>
/* project includes */
#include "fractals.h"
/* externs */
/* defines */
/* typedefs */
/* globals */
/* function prototypes */


/*
 * performs iteration to create an array of iteration counts, which 
 * are used to colour each pixel on the screen in later functions
 * outputs: pointer to the array of iteration counts of size
 * (width * height)
*/
void iterateMandelbrot(
    int width,
    int height,
    int scale,
    unsigned short maxIterations,
    unsigned short *iterationData,
    Point center, // center of the image created
    Point *interestingPoints
)
{
    /* variable declarations */
    // location in the x plane (-2.5 to +1)
    long double x = 0.0;
    // location in the Y plane (-i to +i)
    long double y = 0.0;
    // holds the new real value while y is calculated
    long double tempReal = 0.0;
    // iteration count tracker
    unsigned short iterations;
    // complex number z where x is real and y is imaginary
    Point z;
    // total pixels - incremented by the below loop
    int totalPixelsIterated = 0;
    // interesting points are on the edge of a set and may
    // be part of a visually pleasing pattern
    int interestingPointsLogged = 0;


    /* code */

   for (int i = 0; i < height; i++)
   {
       for (int j = 0; j < width; j++)
       {
           // (i, j) represents the x,y coord on the bitmap width*height
           // not the complex plane (3.5*2)

           /* x/y value in the mandelbrot set is determined by the x/y 
            * coordinates within the image, which are scaled to within
            * the ranges of (-2.5 -> 1) and (-i -> +i) respectively
            * and the precise position is calculated with these scaled
            * values */
           z.x = 0.0;
           z.y = 0.0;
           x =((((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / scale) + center.x;
           y =((((1.0 / (height - 1)) * (i * 2.0)) - 1.0 ) / scale) + center.y;
           //printf("scaled positions: x: %Lf , y: %Lf , pixel: %d  / %d\n", x, y, j, i);
           iterations = 0;
           while (iterations < maxIterations && (z.x * z.x) + (z.y * z.y) <= 4.0)
           {
               //printf("x: %d , y: %d , z.x: %Lf , z.y: %Lf , iteration: %hu\n", j, i, z.x, z.y, iterations);
               tempReal = (z.x * z.x - z.y * z.y) + x;
               z.y = 2 * z.x * z.y + y;
               z.x = tempReal;
               iterations += 1;
           }
           if (iterations <= 960 && iterations >= 940 && interestingPointsLogged < 3)
           {
               interestingPoints[interestingPointsLogged].x = x;
               interestingPoints[interestingPointsLogged].y = y;
               interestingPointsLogged++;
           }
           iterationData[totalPixelsIterated] = iterations;
           //printf("x: %d , y: %d , iterations: %hu\n", j, i, iterations);
           totalPixelsIterated++;
       }
       //printf("y: %d\n", i);
   }
}

/*
 * Create a mandelbrot set using z = z^3 + c 
 * instead of the usual formula
*/
void pow3Mandelbrot(
    int width,
    int height,
    long double scale,
    unsigned short maxIterations,
    unsigned short *iterationData,
    Point center,
    Point *interestingPoints
)
{
    /* variable declarations */
    // coordinates on the complex plane after sizing, scaling etc
    long double x = 0.0;
    long double y = 0.0;
    // placeholder value for x, while y is modified
    long double tempReal = 0.0;
    // iteration count tracker
    unsigned short iterations;
    int totalPixelsIterated = 0;
    // complex number holding the result of the iteration
    Point z;
    int interestingPointsLogged = 0;
    /* code */

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            z.x = 0.0;
            z.y = 0.0;
            x =((((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / scale) + center.x;
            y =((((1.0 / (height - 1)) * (i * 2.0)) - 1.0 ) / scale) + center.y;
            iterations = 0;
            while (iterations < maxIterations && (z.x * z.x) + (z.y * z.y) <= 4.0)
            {
                //printf("x: %d , y: %d , z.x: %Lf , z.y: %Lf , iteration: %hu\n", j, i, z.x, z.y, iterations);
                tempReal = ((z.x * z.x * z.x) - (2 * z.y * z.y * z.x) - (z.x * z.y * z.y)) + x;
                z.y = ((3 * z.y * z.x * z.x) - (z.y * z.y * z.y)) + y;
                z.x = tempReal;
                iterations++;
            }
            if (iterations <= 960 && iterations >= 940 && interestingPointsLogged < 3)
            {
                interestingPoints[interestingPointsLogged].x = j;
                interestingPoints[interestingPointsLogged].y = i;
                interestingPointsLogged++;
            }
            iterationData[totalPixelsIterated] = iterations;
            totalPixelsIterated++;
        }
    }
}


/*
 * Generate a mandelbrot set using z = z^4 + c
 * to form a differently shaped fractal
*/
void pow4Mandelbrot(

)
{
    return;
}

/*
 * Generate iteration daa=ta array for a Julia set
*/
void iterateJulia(
    int width,
    int height,
    Point seed,
    unsigned short maxIterations,
    long double scale,
    Point center,
    unsigned short *iterationData
)
{
    long double x = 0.0;
    long double y = 0.0;
    long double tempReal;
    Point z;
    int totalPixelsIterated = 0;
    int iterations;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            z.x =((((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / scale) + center.x;
            z.y =((((1.0 / (height - 1)) * (i * 2.0)) - 1.0 ) / scale) + center.y;
            iterations = 0;
            while (iterations < maxIterations && (z.x * z.x) + (z.y * z.y) <= 4)
            {
                tempReal = ((z.x * z.x) - (z.y * z.y)) + seed.x;
                z.y = (2 * z.x * z.y) + seed.y;
                z.x = tempReal;
                iterations++;
            }
            iterationData[totalPixelsIterated] = iterations;
            totalPixelsIterated++;
        }
    }
}


/*
 * Generate the burning ship fractal, calculated with z = abs(z)^2 + c
 * This fractal is a unique shape so sometimes requires a wider range
 * of values on the complex plane to be shown in its entirety
*/
void iterateBurningShip(
    int width,
    int height,
    unsigned short maxIterations,
    long double scale,
    Point center,
    unsigned short *iterationData
)
{
    /* variable declarations */
    long double x;
    long double y;
    long double tempReal;
    int totalPixelsIterated = 0;
    Point z;
    unsigned short iterations;
    /* code */

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            z.x = 0.0;
            z.y = 0.0;
            x =((((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / scale) + center.x;
            y =((((1.0 / (height - 1)) * (i * 2.0)) - 1.0 ) / scale) + center.y;
            iterations = 0;
            while (iterations < maxIterations && (z.x * z.x + z.y * z.y) <= 4.0)
            {
                tempReal = (z.x * z.x) + x;
                z.y = (z.y * z.y) + y;
                z.x = tempReal;
                iterations++;
            }
            iterationData[totalPixelsIterated] = iterations;
            totalPixelsIterated++;
        }
    }
}


/*
 * COLOURING SETTINGS
 * B: 255, G: 255 - result, R: 255- result -> black set, white bg, blue edges
 * All: 255 - result -> black set, white bg, grey edges
 * B: 255 - result, G: 255 - result, R:255 -> black set, white bg, red edges
*/
void modulusColouring(
    unsigned char *bitmapData,
    unsigned short *iterationData,
    int width,
    int height,
    int paddingBytes,
    unsigned short maxIterations
)
{
    /* variable declaration */
    int currentPixelNum;
    int totalBytesIterated = 0;

    /* program */

    // calculate padding bytes required for image structure
    paddingBytes = 4 - ((width * 3) % 4);
    if (paddingBytes == 4) paddingBytes = 0;

    // structure the pixel data
    for (int y = 0; y < height; y++)
    {
        currentPixelNum = 0;
        while (currentPixelNum < width)
        {
            if (iterationData[totalBytesIterated / 3] == maxIterations)
            {
                bitmapData[54 + totalBytesIterated] = 0;
                bitmapData[54 + totalBytesIterated + 1] = 0;
                bitmapData[54 + totalBytesIterated + 2] = 0;
            } else {
                int result = iterationData[totalBytesIterated / 3] % 255;
                //int result = iterationData[totalBytesIterated / 3] % 255;
                bitmapData[54 + totalBytesIterated] = 255 - result; // blue
                bitmapData[54 + totalBytesIterated + 1] = 255 - result; // green
                bitmapData[54 + totalBytesIterated + 2] = 255; // red
            }

            totalBytesIterated += 3;
            currentPixelNum++;
        }
        for (int i = 0; i < paddingBytes; i++)
        {
            bitmapData[54 + totalBytesIterated] = 0;
            totalBytesIterated++;
        }
    }
    free(iterationData);
}


/*
 * Colour pixels based on the frequency at which iterations occur
*/
void frequencyColouring(
    int width,
    int height,
    unsigned short *iterationData,
    unsigned char *bitmapData,
    unsigned short maxIterations
)
{
    /* variable declarations */
    int totalPixelsIterated = 0;
    int iterationFrequencies[maxIterations];


    /* code */
    while (totalPixelsIterated < width * height)
    {
        iterationFrequencies[iterationData[totalPixelsIterated]]++;
        totalPixelsIterated++;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
        }
    }
}