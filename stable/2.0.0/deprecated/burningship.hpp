#ifndef BURNING_SHIP_H
#define BURNING_SHIP_H
#include "util.h"

void burningShip(
    int width,
    int height,
    double xScale,
    double yScale,
    Point center,
    int maxIterations,
    int *iterationData
);

#endif