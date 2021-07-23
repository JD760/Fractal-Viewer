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
    Point center // center of the image created
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
    Point z = {0.0 , 0.0};
    // total pixels - incremented by the below loop
    int totalPixelsIterated = 0;


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
           x =((((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / scale) + center.x;
           y =((((1.0 / (height - 1)) * (i * 2.0)) - 1.0 ) / scale) + center.y;
           //printf("scaled positions: x: %Lf , y: %Lf\n", x, y);
           iterations = 0;
           while (iterations < maxIterations && (z.x * z.x) + (z.y * z.y) <= 4.0)
           {
               printf("x: %d , y: %d , z.x: %Lf , z.y: %Lf\n", j, i, z.x, z.y);
               tempReal = z.x * z.x - z.y * z.y;
               z.y = 2 * z.x * z.y + y;
               z.x = tempReal;
               iterations += 1;
           }
           iterationData[totalPixelsIterated] = iterations;
           //printf("x: %d , y: %d , iterations: %hu\n", j, i, iterations);
           totalPixelsIterated++;
       }
       //printf("y: %d\n", i);
   }
}

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
    int totalBytesIterated;

    /* program */

    // calculate padding bytes required for image structure
    paddingBytes = 4 - ((width * 3) % 4);
    if (paddingBytes == 4) paddingBytes = 0;

    // structure the pixel data
    for (int y = 0; y < height; y++)
    {
        while (currentPixelNum < width)
        {
            if (iterationData[totalBytesIterated / 3] == maxIterations)
            {
                bitmapData[54 + totalBytesIterated] = 255;
                bitmapData[54 + totalBytesIterated + 1] = 255;
                bitmapData[54 + totalBytesIterated + 2] = 255;
            } else {
                //int result = 255 - iterationData[totalBytesIterated / 3] % 255;
                int result = iterationData[totalBytesIterated / 3] % 255;
                bitmapData[54 + totalBytesIterated] = result; // blue
                bitmapData[54 + totalBytesIterated + 1] = result; // green
                bitmapData[54 + totalBytesIterated + 2] = result; // red
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