#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int *calculatePoint(int h, int currentByteNum, int width, int height);

int main()
{
    int *result;
    result = calculatePoint(1, 6, 640, 400);
}

int *calculatePoint(int h, int currentByteNum, int width, int height)
{
    // x,y position of pixel
    int x = currentByteNum / 3;
    int y = h;
    int iterations = 1000;
    int zoom = 1;
    int moveX = 0;
    int moveY = 0;
    // return the value of i (returnVal[0]) and whether the point is in the mandelbrot set (returnVal[1])
    int *returnVal = malloc(sizeof(int) * 2); 
    // get starting real and imaginary component
    long double real = 1.5 * (x - width / 2) / (0.5 * zoom * width) + moveX;
    long double imaginary = (y - height / 2) / (0.5 * zoom * height) + moveY;

    long double previousReal = 0;
    long double previousImaginary = 0;
    long double currentReal = 0;
    long double currentImaginary = 0;
    int i; // iteration counter
    for(i = 1; i <= iterations; i++)
    {
        previousReal = currentReal;
        previousImaginary = currentImaginary;

        currentReal = previousReal * previousReal - previousImaginary * previousImaginary + real;
        currentImaginary = 2 * previousReal * previousImaginary + imaginary;

        printf("iteration %d , real value: %Lf , imaginary value: %Lf\n", i, currentReal, currentImaginary);
        if ((currentReal * currentReal + currentImaginary * currentImaginary) > 4) break;
    }
    returnVal[0] = i;
    if (i == iterations-1) returnVal[1] = 1;
    else returnVal[1] = 0;

    return returnVal;
}