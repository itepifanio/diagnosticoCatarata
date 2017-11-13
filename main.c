#include <stdio.h>
#include <stdlib.h>
#include "libs/primitive.h"
#include "libs/ppmTreatment.h"
#include "libs/filters.h"

int main(){
	int i, j;
	FILE *file = readFile("images/Normal2.ppm");
	Image *image = getImage(file);

	Image *batata = grayScale(image);
	saveImage("images/grayScale.ppm", batata, 255);

	Image *filteredImage = gaussianFilter(batata);
	saveImage("images/gaussianFilter.ppm", filteredImage, 255);

	Image *sobel = sobelFilter(filteredImage);
	saveImage("images/sobel.ppm", sobel, 255);
	//Tentativa binaria
	Image *binaryImage = binary(sobel);
	saveImage("images/binary.ppm", binaryImage, 1);
}
