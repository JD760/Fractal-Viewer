#ifndef COLOURING_H
#define COLOURING_H

struct RGB {
    unsigned char Red;
    unsigned char Blue;
    unsigned char Green;
};

struct HSV {
    double h; // angle in degrees
    double s; // fraction 0-1
    double v; // fraction 0-1
};

// colour the fractal based on the iterations % 255
void modulusColouring(
    unsigned char *bitmapData,
    int *iterationData,
    int width,
    int height,
    int maxIterations
);

/*
void iterationChangeColouring(
    unsigned char *bitmapData,
    int *iterationData,
    int width,
    int height,
    int paddingBytes,
    int maxIterations
);
*/

/* 
 * Splits the HSV pallette into a hexagon and approximates RGB values
 * based on the colours contained within the 6 sections
*/
RGB HSVtoRGB(HSV hsv);

#endif