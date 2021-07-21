/* contain definitions and typedefs from fractals.c */

#ifndef FRACTAL_H
    #define FRACTAL_H

    typedef struct Point{
        long double x;
        long double y;
    }Point;

    unsigned short *iterateMandelbrot(int width, int height, int scale, unsigned short maxIterations, Point center);


#endif