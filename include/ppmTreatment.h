#ifndef _PPMTREATMENT_H_
#define _PPMTREATMENT_H_

#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"
#define PI 3.14159265


/**
* Go through the file to check if it has any comments
* if there is a comment, it will be ignored
*
* @params FILE *file_img
**/
void skipComments(FILE *file_img);


/**
* Open and read a file
*
* @params char filename
* @return FILE file
**/
FILE * readFile(char filename[]);


/**
* Receive width and height and build
* a brand new image with this properties
*
* @params int width, int height
* @return Image img
**/
Image * buildImage(int width, int height);


/**
* Free alocate memory for image pixels
*
* @params Image *img
**/
void freeMemory(Image * img);

/**
* Read a file line per line.
* Create a primitive type Image img and
* set its params width, height and
* its pixels, returning
*
* @params FILE *file
* @return Image img
**/
Image * getImage(FILE *file);


/**
* Treat the image to ignore the borders
*
* @params Image img, int width, int height
* @return &img->pixels[height][width]
**/
Pixel * pixelReturn(Image *img, int width, int height);


/**
* Receive a image and save then like a file.
* If comp == 1, then the image receive binaries
* values, else 0..255 values
*
* @params char *file, Image img, int comp
* @return &img->pixels[height][width]
**/
int saveImage(char *file, Image *img, int comp);

#endif
