/* contain definitions and typedefs from bitmap.h */

#ifndef BITMAP_H
    #define BITMAP_H

    void createBitmap(
        int width,
        int height,
        int paddingBytes,
        int fileSize,
        unsigned char *bitmapData
    );
    void splitBytes(
        unsigned char *arr,
        int startAddr,
        int num
    );
    void writeBitmap(
        unsigned char *data,
        int width,
        int height,
        int fileSize,
        char fileName[68]
    );

#endif