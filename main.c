#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"
#include "ppmTreatment.h"
#include "filters.h"

int main(){
	int i, j;
	FILE *file = readFile("Normal2.ppm");
	Image *image = getImage(file);
	//printf("Largura: %i\n", image->width);
	//printf("Altura: %i\n", image->height);	

	Image *batata = grayScale(image);
	saveImage("grayScale.ppm", batata, 255);

	Image *filteredImage = gaussianFilter(batata);
	saveImage("gaussianFilter.ppm", filteredImage, 255);

	Image *sobel = sobelFilter(filteredImage);
	saveImage("sobel.ppm", sobel, 255);
	//Tentativa binaria
	Image *binaryImage = binary(sobel);
	saveImage("binary.ppm", binaryImage, 1);
}
