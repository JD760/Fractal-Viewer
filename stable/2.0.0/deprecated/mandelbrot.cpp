#include <iostream>
 
#include "mandelbrot.hpp"

void IteratePixelsMandelbrot(
    int width,
    int height,
    double xScale,
    double yScale,
    Point center,
    int maxIterations,
    int *iterationData
) {
    // initialise variables and for performing the iteration
    // set up the scale factor for the image
    double imageWidth = 3.5 / xScale;
    double imageHeight = 2 / yScale;
    // represents the coordinates on the complex plane
    double Re = 0.0;
    double Im = 0.0;
    double temp = 0.0;
    double ReSquare = 0.0;
    double ImSquare = 0.0;

    // create a new complex point z with the Re and Im fields
    Point z;
    // tracks how many pixels (out of a possible width * height) have been iterated over
    int pixelsIterated = 0;
    // loop counter
    int iterations = 0;

    // #pragma omp parallel for
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // i,j are the BMP coordinates, not complex coordinates
            // reset the point values from previous iteration
            z.Re = 0.0;
            z.Im = 0.0;

            // calculate the Real part to iterate by performing these steps
            // 1 / (bmp width -1)
            // multiply by current BMP position and the scaled image width
            // subtract 2.5/xScale to account for the range of the set being partly negative (this influences the iteration results)
            // add the real component of the centre point to shift the image by a given amount
            Re = (((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / xScale + center.Re;
            //Re =((((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / 1) + center.Re;
            // calculate the imaginary component by performing these steps
            Im = (((1.0 / (height - 1)) * (i * 2.0)) - 1.0) / yScale + center.Im;
            //Im =((((1.0 / (height - 1)) * (i * 2.0)) - 1.0 ) / 1) + center.Im;
            
            // perform a complex iteration using z = z^2 + c
            iterations = 0; // reset the iterator

            // it has been proven that a point is guaranteed to lie outside of the mandelbrot set if it has a magnitude of 
            // more than two - this loop checks against the max iterations
            while (iterations < maxIterations) {
                // check that the point lies within the mandelbrot set (magnitude <= 2)
                // calculate the squares now to avoid a second calculation later
                ReSquare = z.Re * z.Re;
                ImSquare = z.Im * z.Im;

                // stop the iterations if the points will not converge to an orbit within the set
                if (ReSquare + ImSquare > 4) {
                    break;
                }
                // expanding (a + bi)^2 gives a^2 + 2abi -b^2
                // adding the Re and Im calculated earlier serves as the +c
                // temp is needed to use the 'old' real value in calculating the imaginary component
                temp = (ReSquare - ImSquare) + Re;
                z.Im = (2 * z.Re * z.Im) + Im;
                z.Re = temp;

                //std::cout << "iteration";

                iterations++;
            }
            // once the iteration has finished, log the number of iterations taken
            // if this number reaches maxIterations, we know the point is within the set
            // if not, the point must lie outside the set
            // higher iteration counts give a higher precision set
            iterationData[pixelsIterated] = iterations;
            pixelsIterated++;
        }
    }
    std::cout << pixelsIterated;
}

/* 
    The Julia set is created by varying the value of c in the mandelbrot set equation
    and works similarly to the mandelbrot function - see this function for more detailed comments 
*/
void juliaSet(
    int width,
    int height,
    double xScale,
    double yScale,
    Point seed, // each seed value gives a different Julia Set
    Point center,
    int maxIterations,
    int *iterationData
) {
    double temp;
    int pixelsIterated = 0;
    Point z;
    int iterations;
    double reSquare;
    double imSquare;

    // iterate over each pixel in the bitmap
    for (int i=0; i < height; i++) {
        for (int j=0; j < width; j++) {
            // reset the values from previous iterations
            z.Im = (((1.0 / (height - 1)) * (i * 2.0)) - 1.0) / yScale + center.Im;
            z.Re = (((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / xScale + center.Re;

            iterations = 0;
            // generate the iteration data for the Julia Set
            while (iterations < maxIterations) {
                reSquare = z.Re * z.Re;
                imSquare = z.Im * z.Im;

                if (reSquare + imSquare > 4) {
                    break;
                }

                temp = (reSquare - imSquare) + seed.Re;
                z.Im = (2 * z.Re * z.Im) + seed.Im;
                z.Re = temp;
                iterations++;
            }
            iterationData[pixelsIterated] = iterations;
            pixelsIterated++;
        }
    }
}