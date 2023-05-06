#ifndef TRICORN_H
#define TRICORN_H

#include "mandelbrot.hpp"

void tricorn(
    int width,
    int height, 
    double xScale,
    double yScale,
    Point center,
    int maxIterations,
    int *iterationData
);

#endif