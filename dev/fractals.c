/* fractals.c - Fractal viewer, a program to explore the world of fractal geometry */

/* system includes */
#include <stdlib.h>
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
unsigned short *iterateMandelbrot(
    int width,
    int height,
    int scale,
    unsigned short maxIterations,
    Point center // center of the image created
)
{
    /* variable declarations */
    // location in the x plane (-2.5 to +1)
    long double x;
    // location in the Y plane (-i to +i)
    long double y;
    // holds the new real value while y is calculated
    long double tempReal;
    // iteration count tracker
    unsigned short iterations;
    // complex number z where x is real and y is imaginary
    Point z;
    // current byte 
    int currentByteNum;
    // total pixels - incremented by the below loop
    int totalPixelsIterated = 0;


    /* code */

    /* Create an array to store iteration count for each pixel 
     * unsigned short used to save memory, could add an option to use
     * an int later. This has the issue of limiting iterations to 65k
     * however saves a large amount on memory*/
    // the last array element is the maximum iteration count
    unsigned short *iterationData = malloc((sizeof(unsigned short) * width * height) + 1);

   for (int i = 0; i < width; i++)
   {
       for (int j = 0; j < height; j++)
       {
           // (i, j) represents the x,y coord on the bitmap width*height
           // not the complex plane (3.5*2)

           /* x/y value in the mandelbrot set is determined by the x/y 
            * coordinates within the image, which are scaled to within
            * the ranges of (-2.5 -> 1) and (-i -> +i) respectively
            * and the precise position is calculated with these scaled
            * values */
           x =((((1.0 / width) * i * 3.5) - 2.5) / scale) + center.x;
           y =((((1.0 / height) * j * 2) - 1.0 ) / scale) + center.y;
           iterations = 0;
           while (iterations < maxIterations && x*x + y*y <= 4.0)
           {
               tempReal = z.x * z.x - z.y * z.y;
               z.y = 2 * z.x * z.y;
               z.x = tempReal;
               iterations += 1;
           }
           iterationData[totalPixelsIterated] = iterations;
           totalPixelsIterated++;
       }
   }
   // this value is needed for colouring later
   iterationData[totalPixelsIterated+1] = maxIterations;

   // pointer to the array of iteration counts
   return iterationData;
}