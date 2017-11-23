#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"
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


Image * buildImage(int width, int height);

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


Pixel * pixelReturn(Image *img, int width, int height);

int saveImage(char *file, Image *img, int comp);
