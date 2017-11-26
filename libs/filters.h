#define PI 3.14159265
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppmTreatment.h"


/**
* Create a gray scale image.
*
* @params Image *img
* return FILE grayScale
**/
Image * grayScale(Image *img);


/**
* Apply gauss filter kernel on the image.
* Receive an gray scale image to smooth.
*
* @params Image *img 
* return Image img
**/
Image * gaussianFilter(Image *img);


/**
* Applying sobel filter (two kernels).
* Receiving gray scale image and filter.
* This filter will highlight edges.
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


/**
* Hough implementation. This function receive
* three parameter, the first one should be a binary
* image, the second the colored image which will
* be segmented, the third a boolean. 
* If the b == true, then the function return an
* drawing circle in the eye. 
* else an segmented colored image.
*
* @params Image *img, Image *coloredImg
* @return Image coloredImg
**/
Image * houghTransform(Image *img, Image *coloredImg, bool b);


/**
* Receive a segmentated image, count the 
* unhealthy pixels and gives an diagnosis.
*
* @params Image *img
**/
void diagnosis(Image *img, char fileName[]);