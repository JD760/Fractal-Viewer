#include "burningship.hpp"
// contains the definition of the Point structure
#include "util.h"

void burningShip(
    int width,
    int height,
    double xScale,
    double yScale,
    Point center,
    int maxIterations,
    int *iterationData
) {
    long double Re;
    long double Im;
    long double temp;
    long double ReSquare;
    long double ImSquare;

    Point z;
    int pixelsIterated = 0;
    int iterations;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
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
            iterationData[pixelsIterated] = iterations;
            pixelsIterated++;
        }
    }
}