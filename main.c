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
	saveImage("grayScale.ppm", batata);

	Image *filteredImage = gaussianFilter(image);
	saveImage("gaussianFilter.ppm", filteredImage);

	Image *sobel = sobelFilter(batata);
	saveImage("sobel.ppm", sobel);
}
