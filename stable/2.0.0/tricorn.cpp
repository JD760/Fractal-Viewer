#include "mandelbrot.hpp"

void tricorn(
    int width,
    int height, 
    double xScale,
    double yScale,
    Point center,
    int maxIterations,
    int *iterationData
){
    double Re;
    double Im;
    double temp;
    double ReSquare;
    double ImSquare;

    Point z;
    int iterations;
    int pixelsIterated = 0;

    for (int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            z.Re = 0.0;
            z.Im = 0.0;

            Re = (((1.0 / (width - 1)) * (j * 3.5)) - 2.5) / xScale + center.Re;
            Im = (((1.0 / (height - 1)) * ((height - i) * 2.0)) - 1.0) / yScale + center.Im;

            iterations = 0;
            while (iterations < maxIterations) {
                ReSquare = z.Re * z.Re;
                ImSquare = z.Im * z.Im;

                if (ReSquare + ImSquare > 4) {
                    break;
                }

                // tricorn uses the complex conjugate (z*) in place of z, such that
                temp = (z.Re * z.Re - z.Im * z.Im) + Re;
                z.Im = (-2 * z.Re * z.Im) + Im;
                z.Re = temp;

                iterations++;
            }
            iterationData[pixelsIterated] = iterations;
            pixelsIterated++;
        }
    }
}