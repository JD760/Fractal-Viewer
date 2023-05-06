#ifndef BITMAP_H
#define BITMAP_H
/*
* Create an array of bytes and add file and bitmap headers to create an
* image, with space for pixel data reserved but not used or zeroed-out
*
* returns: a pointer to the byte array that contains all
* of the image data
*/
void createBitmap(
    int width,  // image width in pixels
    int height, // image height in pixels
    // number of bytes to make each image row a multiple of 4 bytes long
    int paddingBytes,
    int fileSize, // size of the bitmap in bytes
    unsigned char *bitmapData // array representing all image data
);

/*
* write out the bytes in a bitmap data array to create the image
* file name has a maximum length of 64 characters
*/
void writeBitmap(
    unsigned char *bitmapData,
    int fileSize
);

/*
* Splits a 4 byte number into 4 elements of a byte array, according to
* processor endianness which is checked within the function
*/
void splitBytes(
    unsigned char *arr, // array to write bytes to 
    int startAddr, // where to start writing bytes
    int num // the number to encode into 4 bytes
);

#endif