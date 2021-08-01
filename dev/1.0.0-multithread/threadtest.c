/*
 * Multithreading of mandelbrot computation works by diving the image
 * into many 'blocks' of user defined size. These are arranged into a
 * task list and completed by worker threads. The iteration count of 
 * each pixel is written into the iteration data array, one of which
 * exists for each block. A pointer to the start of the sequence of 
 * blocks is provided to the colouring function which uses worker 
 * threads to determine the colouring of each pixel on the bitmap
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


typedef struct PixelBlock{
    int startingX;
    int startingY;
    unsigned char complete;
}PixelBlock;

typedef struct computeBlockArg{
    PixelBlock *block;
    int maxIterations;
    int width;
    int height;
}computeBlockArg;

int main()
{
    computeMandelbrot(3840, 2160, 100);
}

void computeMandelbrot(
    int width,
    int height,
    int numThreads
)
{
    // number of blocks that make up each axis of the image
    int totalBlocksX = width / 40;
    int totalBlocksY = height / 40;
    int totalBlocks = totalBlocksX * totalBlocksY;
    // array representing all of the blocks that make up the image
    PixelBlock *imageBlocks = malloc(
        sizeof(PixelBlock) * totalBlocks);
    // array representing each pixel on the bitmap
    int *iterationData = malloc(sizeof(int) * width * height);
    int index;

    // possible TODO: make this part multithreaded?
    // calculate the starting pixel positions on each block
    for(int i = 0; i < totalBlocksY; i++)
    {
        for(int j = 0; j < totalBlocksX; j++)
        {
            // total number of rows completed + current row position
            index = (totalBlocksX * i) + j;
            imageBlocks[index].startingX = j * 40;
            imageBlocks[index].startingY = i * 40;
            //printf("BlockNum: %d , X: %d , Y: %d\n", index, imageBlocks[index].startingX, imageBlocks[index].startingY);
        }
    }

    // calculate thread task allocation
    int extraBlocks = totalBlocks % numThreads;
    int tasksPerThread = (totalBlocks - extraBlocks) / numThreads;
    
}

void computeBlock(void *arg)
{
    return;
}