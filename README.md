# Fractal-Viewer
This is a C project that can generate an image of the mandelbrot set at a given zoom, with the result being a bitmap image. Also supports the creation of Julia sets.
The project is made up of several parts:
 - user input
 - fractal creation
 - bitmap image creation

## Input
Input is performed through modifying the main.c file - several values can be changed including the seed and origin coordinates, scale and number of iterations performed per pixel
 - Seed - used in creating Julia sets, each seed creates a unique set
 - Origin coordinates - zoom happens upon the point of origin, changing this allows zooming in to a specific location rather than the center
 - Scale - the zoom factor - can be any positive real number
 - Iterations per pixel - controls the precision of the calculations creating the pixel data - larger means more precision and higher zoom before quality loss occurs, but     significantly longer times to create the images
 - Image resolution - larger resolution creates images that can be enlarged further before quality is lost

## Fractal Creation
- The fractals are generated using their respective formulae (z = z^2 + c for the mandelbrot set)
- For each pixel in the image, the (x,y) coordinates are converted into their respective complex number ( this depends on the scale and origin point of the image )
- This creates a value for z, which is iterated upon until the limit (usually 1000 times) is reached
- The output is a byte array, the pointer to which is passed into the colouring function

## Bitmap Creation
- The first function creates the file and bitmap header structure - allowing the operating system to recognise the type of image
- Each pixel is coloured based on the number of iterations it took for the value to leave the bounds of the set
- If the value does not escape, the pixel is coloured black
- Colouring may be customised by changing the colouring function in the bitmap.c file
- The default is colouring based on modulus, and creates a black set and background, with the boundary line being a gradient between the two colours![modulus-colouring](https://user-images.githubusercontent.com/28735273/152503137-bbc51576-60c0-4b2f-a386-b861a1804209.png)
![teal-fullbrot](https://user-images.githubusercontent.com/28735273/152503138-7e5ab084-b303-467b-9c71-e952d3df2158.png)
![teal-minibrots](https://user-images.githubusercontent.com/28735273/152503140-d0636f0d-2d00-4516-8776-b2642c0cf093.png)
