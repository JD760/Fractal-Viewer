// includes

// function prototypes

// creates data for a bitmap image with 24-bit colours and variable width/height in the form of 
// a byte array
unsigned char *createBitmapData(int width, int height)
{
    // size calculations
    int paddingBytes = 4 - ((width * 3) % 4); // works for all results of (width * 3) % 4 except 0
    if (paddingBytes == 4) paddingBytes = 0; // fixes above flaw 
    // size of pixel data + size of headers
    int fileSize = (((width * 3) + paddingBytes) * height) + 54;
    unsigned char *bitmapData = malloc(sizeof(unsigned char) * fileSize);

    // - FILE HEADER - //

    // file signature
    bitmapData[0] = 'B';
    bitmapData[1] = 'M';

    // file size (use byte splitting later)
    splitBytes(bitmapData, 2, fileSize);

    // reserved area
    bitmapData[6] = 0;
    bitmapData[7] = 0;
    bitmapData[8] = 0;
    bitmapData[9] = 0;

    // pixel data offset (always 54 with selected headers)
    bitmapData[10] = 54;
    bitmapData[11] = 0;
    bitmapData[12] = 0;
    bitmapData[13] = 0;

    // bitmap header
    // - BITMAP HEADER - //
    
    // header size
    bitmapData[14] = 40;
    bitmapData[15] = 0;
    bitmapData[16] = 0;
    bitmapData[17] = 0;

    // width
    splitBytes(bitmapData, 18, width);

    // height (use byte splitting later)
    splitBytes(bitmapData, 22, height);

    // reserved
    bitmapData[26] = 1;
    bitmapData[27] = 0;

    // bits per pixel (RGB = 24)
    bitmapData[28] = 24;
    bitmapData[29] = 0;

    // compression method
    bitmapData[30] = 0;
    bitmapData[31] = 0;
    bitmapData[32] = 0;
    bitmapData[33] = 0;

    // size of pixel data
    splitBytes(bitmapData, 34, ((width + paddingBytes) * 3) * height);

    // horizontal resolution (pixels per metre)
    bitmapData[38] = 10;
    bitmapData[39] = 0;
    bitmapData[40] = 0;
    bitmapData[41] = 0;

    // vertical resolution (pixels per metre)
    bitmapData[42] = 10;
    bitmapData[43] = 0;
    bitmapData[44] = 0;
    bitmapData[45] = 0;

    // colour pallette - RGB doesn't need one
    bitmapData[46] = 0;
    bitmapData[47] = 0;
    bitmapData[48] = 0;
    bitmapData[49] = 0;
    
    // number of important colours
    bitmapData[50] = 0;
    bitmapData[51] = 0;
    bitmapData[52] = 0;
    bitmapData[53] = 0;

    return bitmapData;
}

// to be called when pixel data has been generated, creates a .bmp file from byte array
void BitmapDataToImage(unsigned char *input, int fileSize)
{
    FILE *fp;
    fp = fopen("output.bmp", "w+");
    for (int i = 0; i < fileSize; i++)
    {
        fputc(input[i], fp);
    }
}

// splits a 32 bit integer into 4 bytes, arranged based on processor endianness
void splitBytes(unsigned char *arr, int startAddr, int num)
{
    // test endianness
    int endianTestInt = 1;
    int endian = 0; // 0 is little endian, 1 is big endian

    if (*(char *)&num != 1)
    {
        endianTestInt = 1;
    }

    if (endian == 0)
    {
        if (num >= 16777216)
        {
            arr[startAddr + 3] = floor(num / 16777216);
            // this can be done as byte has been set and avoids nested if's while being a little less concise
            num = num % 16777216; 
        }
        if (num >= 65536)
        {
            arr[startAddr + 2] = floor(num / 65536);
            num = num % 65536;
        }
        if (num >= 256)
        {
            arr[startAddr + 1] = floor(num / 256);
            num = num % 256;
        }
        arr[startAddr] = num;
    }
    else
    {
        if (num >= 16777216)
        {
            arr[startAddr] = floor(num / 16777216);
            num = num % 16777216;
        }
        if (num >= 65536)
        {
            arr[startAddr + 1] = floor(num / 65536);
            num = num % 256;
        }
        if (num >= 256)
        {
            arr[startAddr + 2] = floor(num / 65536);
            num = num % 256;
        }
        arr[startAddr + 3] = num;
    }
}