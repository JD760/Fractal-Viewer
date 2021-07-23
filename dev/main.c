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
    /* variable declarations */
    unsigned char *bitmapData;
    unsigned short *iterationData;
    unsigned char mode;

    /* represents the type of fractal to be drawn 
    * 1 - mandelbrot
    * 2 - julia
    */


    /* process commandline options */
    if (argv[1] == "mandelbrot") mode = 1;
    else if (argv[1] == "julia") mode = 2;
    else mode = 1; // default to mandelbrot mode

    /* do the rest */

    time_t start = time(NULL);
    Point center = {0.0, 0.0};
    bitmapData = createBitmap(1920, 1080);
    printf("Created bitmap data\n");
    iterationData = iterateMandelbrot(1920, 1080, 1, 250, center);
    printf("created iteration data\n");
    time_t end = time(NULL);
    printf("Execution time: %f\n", difftime(end, start));
}

/* functions */