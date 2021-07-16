// external libraries
#include <stdio.h>
#include <stdlib.h>

// project files
#include "structs.h"
#include "bitmap.h"
#include "mandelbrot.h"

//structs
//function prototypes

// program
int main()
{

}

struct Settings *setup()
{
    struct Settings *settings = malloc(sizeof(struct Settings));

    settings->width = 3840;
    settings->height = 2160;
    settings->centerX = 0.0;
    settings->centerY = 0.0;
    settings->scale = 1.0;

    return settings;
}

