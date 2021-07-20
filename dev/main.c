/* main.c - Fractal viewer, a program to explore the world of fractal geometry */

/* system includes */
/* project includes */
#include "bitmap.h"
/* externs */
/* defines */
/* typedefs */
/* globals */
/* function prototypes */

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

}

/* functions */