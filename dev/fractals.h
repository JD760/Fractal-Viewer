/* contain definitions and typedefs from fractals.c */

#ifndef FRACTAL_H
    #define FRACTAL_H

    typedef struct Point{
        long double x;
        long double y;
    }Point;

    void iterateMandelbrot(
        int width,
        int height,
        int scale,
        unsigned short maxIterations,
        unsigned short *iterationData,
        Point center
    );
    void modulusColouring(
        unsigned char *bitmapData,
        unsigned short *iterationData,
        int width,
        int height,
        int paddingBytes,
        unsigned short maxIterations
    );
    void iterateJulia(
        int width,
        int height,
        Point seed,
        unsigned short maxIterations,
        long double scale,
        Point center,
        unsigned short *iterationData
    );


#endif