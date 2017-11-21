#include <stdio.h>
#include <stdlib.h>
#include "libs/primitive.h"
#include "libs/ppmTreatment.h"
#include "libs/filters.h"

int main(){
	int i, j;
	FILE *file = readFile("images/Catarata.ppm");
	Image *image = getImage(file);

	Image *grayImage = grayScale(image);
	saveImage("images/grayScale.ppm", grayImage, 255);

	Image *filteredImage = gaussianFilter(grayImage);
	saveImage("images/gaussianFilter.ppm", filteredImage, 255);
	freeMemory(grayImage);

	Image *sobel = sobelFilter(filteredImage);
	saveImage("images/sobel.ppm", sobel, 255);
	freeMemory(filteredImage);

	Image *binaryImage = binary(sobel);
	saveImage("images/binary.ppm", binaryImage, 1);
	
	houghTransform(binaryImage, image);
	
}
