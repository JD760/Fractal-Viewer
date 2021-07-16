#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Colour{
    unsigned char red;
    unsigned char blue;
    unsigned char green;
};

struct Point{
    long double x;
    long double y;
};

struct Colour calculatePoint(int h, int currentByteNum);

int main()
{
    calculatePoint(640, 400);
    return 0;
}

struct Colour calculatePoint(int width, int height)
{
    // x,y position of pixel
    int x = 319;
    int y = 23;
    int maxIterations = 1000;
    int iteration = 0;
    struct Colour pixelColour;

    // complex plane goes from x = -2.5 to x = 1, y = -1 to y = 1
    // find scaled position of each pixel
    long double xPos = ((1.0 / width) * x * 3.5) - 2.5; // convert 0 -> width into -2.5 -> 1
    long double yPos = ((1.0 / height) * y * 2) - 1; // convert 0 -> height into -1 -> 1
    //printf("Scaled positions: x: %Lf , y: %Lf\n", xPos, yPos);
    struct Point c = {0.0,0.0};
    long double xTemp;

    while ((c.x * c.x) + (c.y * c.y) <= 4 && iteration < maxIterations)
    {
        xTemp = c.x * c.x - c.y * c.y + xPos;
        c.y = (2 * c.x * c.y) + yPos;
        c.x = xTemp;
        //printf("iteration: %d , x: %Lf , y: %Lf\n", iteration, c.x, c.y);
        iteration += 1;
    }

    if (iteration == maxIterations)
    {
        pixelColour.blue = 0;
        pixelColour.green = 0;
        pixelColour.red = 0;
    }
    else
    {
        pixelColour.blue = 255;
        pixelColour.green = 255;
        pixelColour.red = 255;
    }
    //printf("x : %d , y: %d , iterations: %d\n", x, y, iteration);
    return pixelColour;
}