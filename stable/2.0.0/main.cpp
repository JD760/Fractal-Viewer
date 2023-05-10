/* System includes */
#include <iostream>
/* Local includes */
#include "bitmap.hpp"
#include "fractals.hpp"
#include "colouring.hpp"

int main() {
    int width = 1920;
    int height = 1080;
    int maxIterations = 1000;
    double xScale = 3.0;
    double yScale = 3.0;
    Point center = {
        -0.5,   // Re
        0.0     // Im
    };

    // the seed to use when creating Julia Sets
    Point seed = {
        -0.5251993,
        -0.5251993
    };

    // for relevant iterators, the power to raise the iteration calculations to 
    // such that z = z^n + c
    int power = 3;

    // calculate necessary data to create a bitmap image
    // padding bytes ensure each row of pixels is the same length
    int paddingBytes = 4 - ((width * 3) % 4);
    if (paddingBytes == 4) {paddingBytes = 0;}

    // calculate the total file size and allocate necessary memory
    // 54 bytes is the total size of the file headers
    int fileSize = (width * 3 + paddingBytes) * height + 54;
    // allocate enough bytes of memory to store all of the image data
    unsigned char *bitmapData = (unsigned char *) malloc(sizeof(unsigned char) * fileSize);
    int *iterationData = (int*) malloc(sizeof(int) * (width * height));

    
    // create a bitmap file (this populates the bitmapData declared earlier)
    createBitmap(width, height, paddingBytes, fileSize, bitmapData);
    std::cout << "Created bitmap file\n";

    // Calculate fractal data
    //IteratePixelsMandelbrot(width, height, xScale, yScale, center, maxIterations, iterationData);
    //juliaSet(width, height, xScale, yScale, seed, center, maxIterations, iterationData);
    //burningShip(width, height, xScale, yScale, center, maxIterations, iterationData);
    //tricorn(width, height, xScale, yScale, center, maxIterations, iterationData);
    iteratePixels(width, height, xScale, yScale, center, seed, power, maxIterations, iterationData, tricornIterator);

    std::cout << "Iterated over pixels\n";

    // apply a colouring function
    modulusColouring(bitmapData, iterationData, width, height, maxIterations);
    //iterationChangeColouring(bitmapData, iterationData, width, height, paddingBytes, maxIterations);

    // write the bitmap to a file
    writeBitmap(bitmapData, fileSize);
    std::cout << "Written bitmap to fractal.bmp\n";

    

    // free memory items
    free(iterationData);
    free(bitmapData);
}