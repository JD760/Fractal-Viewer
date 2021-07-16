#include "structs.h"

void plotMandelbrotSet(unsigned char *data, struct Settings *settings)
{
    long totalBytesIterated = 0;
    long currentByteNum = 0;
    short paddingBytes = (settings->width * 3) % 4;
    if (paddingBytes == 4) paddingBytes = 0;

    for (int i = 0; i < settings->height; i++)
    {
        while (currentByteNum < settings->width * 3)
        {
            
            totalBytesIterated+=3;
            currentByteNum+=3;
        }
        for (int i = 0; i < paddingBytes; i++)
        {
            data[54 + totalBytesIterated] = 0;
            totalBytesIterated++;
        }
    }
}