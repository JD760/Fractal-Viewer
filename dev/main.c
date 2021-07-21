/* main.c - Fractal viewer, a program to explore the world of fractal geometry */

/* system includes */
#include <stdlib.h>
#include <stdio.h>

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

    /* represents the type of fractal to be drawn 
    * 1 - mandelbrot
    * 2 - julia
    */
    unsigned char mode;

    /* process commandline options */
    if (argv[1] == "mandelbrot") mode = 1;
    if (argv[1] == "julia") mode = 2;
    else mode = 1; // default to mandelbrot mode

    /* do the rest */
    unsigned char *bitmapData;
    unsigned short *iterationData;
    Point center = {0.0, 0.0};
    bitmapData = createBitmap(3840, 2160);
    iterationData = iterateMandelbrot(3840, 2160, 1, 1000, center);
    printf("Max iterations: %hu", iterationData[3840 * 2160 + 1]);

}

/* functions */