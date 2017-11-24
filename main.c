#include <stdlib.h>
#include <stdio.h>
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
	
	file = readFile("images/Catarata.ppm");
	image = getImage(file);
	
	Image *hough = houghTransform(binaryImage, image);
	saveImage("images/hough.ppm", hough, 255);
}
