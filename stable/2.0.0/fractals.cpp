#include <iostream>

#include "fractals.hpp"
#include "util.hpp"

void iteratePixels(
    int width,
    int height,
    double xScale,
    double yScale,
    Point center,
    Point seed,
    int power,
    int maxIterations,
    int *iterationData,
    int (*iterator) (double, double, int, int, Point)
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

            // iterator function goes here
            iterations = iterator(Re, Im, maxIterations, power, seed);
            // and above here

            // once the iteration has finished, log the number of iterations taken
            // if this number reaches maxIterations, we know the point is within the set
            // if not, the point must lie outside the set
            // higher iteration counts give a higher precision set
            iterationData[pixelsIterated] = iterations;
            pixelsIterated++;
        }
    }
}

int mandelbrotIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
) {
    int iterations = 0;
    Point z = {0.0, 0.0};
    double ReSquare;
    double ImSquare;
    double temp;
    while (iterations < maxIterations) {
        ReSquare = z.Re * z.Re;
        ImSquare = z.Im * z.Im;

        if (ReSquare + ImSquare > 4) {
            return iterations;
        }

        temp = (ReSquare - ImSquare) + Re;
        z.Im = (2 * z.Im * z.Re) + Im;
        z.Re = temp;

        iterations++;
    }
    return iterations;
}

int JuliaIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
) {
    int iterations = 0;
    double ReSquare;
    double ImSquare;
    Point z = {Re, Im};
    double temp;
    while (iterations < maxIterations) {
            ReSquare = z.Re * z.Re;
            ImSquare = z.Im * z.Im;

            if (ReSquare + ImSquare > 4) {
                //std::cout << iterations;
                break;
            }

            temp = (ReSquare - ImSquare) + seed.Re;
            z.Im = (2 * z.Re * z.Im) + seed.Im;
            z.Re = temp;
            iterations++;
    }
    return iterations;
}

/* Generate a mandelbrot set using z^n where n is an integer
 * Make use of De Moivre's theorem
 * 𝑧^𝑛=(𝑟^𝑛)(cos(𝑛𝜃)+𝑖sin(𝑛𝜃))
*/
int powNMandelbrotIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
) {
    int iterations = 1;
    double magnitude;
    double magnitudeN;
    double theta;
    Point z = {Re, Im};
    
    while (iterations < maxIterations) {
        magnitude = sqrt((z.Re * z.Re) + (z.Im * z.Im));
        magnitudeN = pow(magnitude, power);

        if (magnitudeN > 2) {
            break;
        }

        // convert to modulus-argument form
        if (z.Re == 0) {
            theta = 0;
        }
        theta = atan(z.Im / z.Re);

        // make use of De Moivre's theorem to compute the Nth power
        z.Re = (magnitudeN * cos(power * theta)) + Re;
        z.Im = (magnitudeN * sin(power * theta)) + Im;

        iterations++;
    }
    return iterations;
}

int burningShipIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
) {
    int iterations = 0;
    Point z = {0.0, 0.0};
    double ReSquare;
    double ImSquare;
    double temp;

    while (iterations < maxIterations) {
        ReSquare = z.Re * z.Re;
        ImSquare = z.Im * z.Im;

        if (ReSquare + ImSquare > 4) {
            return iterations;
        }

        // get absolute values before performing the calculation
        if (z.Re < 0) { 
            z.Re = z.Re * -1;
        }
        if (z.Im < 0) {
            z.Im = z.Im * -1;
        }

        ReSquare = z.Re * z.Re;
        ImSquare = z.Im * z.Im;

        temp = ReSquare - ImSquare;
        z.Im = (2 * z.Re * z.Im) + Im;
        z.Re = temp + Re;

        iterations++;
    }
    return iterations;
}

int tricornIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
) {
    int iterations = 0;
    double ReSquare;
    double ImSquare;
    double temp;
    Point z = {0.0, 0.0};

    while (iterations < maxIterations) {
        ReSquare = z.Re * z.Re;
        ImSquare = z.Im * z.Im;

        if (ReSquare + ImSquare > 4) {
            return iterations;
        }

        // tricorn uses the complex conjugate (z*) in place of z, such that
        temp = (z.Re * z.Re - z.Im * z.Im) + Re;
        z.Im = (-2 * z.Re * z.Im) + Im;
        z.Re = temp;

        iterations++;
    }
    return iterations;
}