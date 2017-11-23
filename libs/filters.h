#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ppmTreatment.h"
/**
* Create a gray scale image
*
* @params Image *img
* return FILE grayScale
**/

Image * grayScale(Image *img);

Image * gaussianFilter(Image *img);

/**
* Applying sobel filter.
* Receiving gray scale file and filtering
*
* @params Image *img
* return Image filteredImage
**/
Image * sobelFilter(Image *img);

/**
* Applying the binary process on a image, 
* creating a new image which will have  
* binary values, 255 and 0. 255 represent 
* the white color and the 0 the black.
*
* @params Image *img
* return Image filteredImage
**/
Image * binary(Image *img);
