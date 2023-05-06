#include <iostream>

#include "colouring.hpp"

// colour the fractal based on the iterations % 255
void modulusColouring(
    unsigned char *bitmapData,
    int *iterationData,
    int width,
    int height,
    int maxIterations
) {
    // track which pixel is being coloured and how many have been completed
    int currentPixelNum;
    RGB currentPixel;
    int pixelsIterated = 0;
    // the number of individual bytes that have been coloured
    // initialised at 54, the size of the file header in bytes
    int totalBytes = 54;

    // for each row of pixels in the bitmap
    for (int y = 0; y < height; y++) {
        currentPixelNum = 0;
        while (currentPixelNum < width) {
            // if the point lies within the mandelbrot set
            if (iterationData[pixelsIterated] == maxIterations) {
                currentPixel.Red = 0;
                currentPixel.Blue = 0;
                currentPixel.Green = 0;
            } else {
                int mod = iterationData[pixelsIterated] % 255;
                // changing these can adjust the colour profile - maybe add settings for this later?
                currentPixel.Red = mod;
                currentPixel.Blue = ceil(mod / 4);
                currentPixel.Green = ceil(mod / 4);
            } 

            // update the bitmap data with the new pixel colouring
            // BGR is the order in which the bitmap file expects colours
            bitmapData[totalBytes] = currentPixel.Blue;
            bitmapData[totalBytes + 1] = currentPixel.Green;
            bitmapData[totalBytes + 2] = currentPixel.Red;
            currentPixelNum++;
            pixelsIterated++;
            // each pixel is 3 bytes
            totalBytes += 3;
        }
    }
}

// TODO: Implement a working version of this sometime
/* 
void iterationChangeColouring(
    unsigned char *bitmapData,
    int *iterationData,
    int width,
    int height,
    int paddingBytes,
    int maxIterations
) {
    int currentPixelNum;
    int change;
    RGB currentPixel;
    int pixelsIterated = 1;
    int totalBytes = 54;

    // make the first pixel black and start iteration from the second pixel
    bitmapData[totalBytes] = 0;
    bitmapData[totalBytes + 1] = 0;
    bitmapData[totalBytes + 2] = 0;
    totalBytes += 3;

    std::cout << "Begin colouring\n";

    for (int y = 0; y < height; y++) {
        currentPixelNum = 0;
        while (currentPixelNum < width) {
            change = iterationData[pixelsIterated-1] - iterationData[pixelsIterated];
            if (change < 0) { change = change * -1 ;}
            std::cout << change + '\n';

            bitmapData[totalBytes] = 255 - ceil(change / 255);
            bitmapData[totalBytes + 1] = 255 - ceil(change / 255);
            bitmapData[totalBytes + 2] = 255 - ceil(change / 255);

            currentPixelNum++;
            pixelsIterated++;
            totalBytes += 3;
        }
    }
}
*/

/* 
 * Splits the HSV pallette into a hexagon and approximates RGB values
 * based on the colours contained within the 6 sections
*/
RGB HSVtoRGB(HSV hsv) {
    // defines a scaled set of RGB colours
    RGB rgb;
    hsv.h = hsv.h / 60;
    double chroma = hsv.v * hsv.s;
    double x = chroma * (1 - abs(fmod(hsv.h, 2) -1));
    double m = hsv.v - chroma;

    // approximate RGB values based on hue
    if (hsv.h <= 1) {
        rgb.Red = chroma + m;
        rgb.Green = x + m;
        rgb.Blue = m;
    } else if (hsv.h <= 2) {
        rgb.Red = x + m;
        rgb.Green = chroma + m;
        rgb.Blue = m;
    } else if (hsv.h <= 3) {
        rgb.Red = m;
        rgb.Green = chroma + m;
        rgb.Blue = x + m;
    } else if (hsv.h <= 4) {
        rgb.Red = m;
        rgb.Green = x + m;
        rgb.Blue = chroma + m;
    } else if (hsv.h <= 5) {
        rgb.Red = x + m;
        rgb.Green = m;
        rgb.Blue = chroma + m;
    } else if (hsv.h <= 6) {
        rgb.Red = chroma + m;
        rgb.Green = m;
        rgb.Green = x + m;
    }

    // rescale the RGB colours to within their normal scale
    // instead of 0-1 required for the conversion
    rgb.Red = round(rgb.Red * 255);
    rgb.Green = round(rgb.Green * 255);
    rgb.Blue = round(rgb.Blue * 255);

    return rgb;
}