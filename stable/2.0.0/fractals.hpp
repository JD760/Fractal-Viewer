#ifndef FRACTALS_H
#define FRACTALS_H
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
);

// function pointers

int mandelbrotIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point z
);

int JuliaIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
);

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
);


int burningShipIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
);

int tricornIterator(
    double Re,
    double Im,
    int maxIterations,
    int power,
    Point seed
);

#endif