#ifndef MANDELBROT_H
#define MANDELBROT_H

struct Point {
    // may use long doubles in future if precision breaks down with high scale factors
    double Re;
    double Im;
};

void IteratePixelsMandelbrot(
    int width,
    int height,
    double xScale,
    double yScale,
    Point center,
    int maxIterations,
    int *iterationData
);

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
);

#endif