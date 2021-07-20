/* contain definitions and typedefs from bitmap.h */

#ifndef BITMAP_H
    #define BITMAP_H

    unsigned char *createBitmap(int width, int height);
    void splitBytes(unsigned char *arr, int startAddr, int num);
    void writeBitmap(unsigned char *data, int fileSize, char fileName[68]);

#endif