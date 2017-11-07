#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"
#include "ppmTreatment.h"

int main(){
	int i, j;
	FILE *file = readFile("Normal2.ppm");
	Image *image = getImage(file);
	printf("Largura: %i\n", image->width);
	printf("Altura: %i\n", image->height);	

	grayScale(image);

	Image *filteredImage = gaussianFilter(image);
	saveImage("filtroGaussiano.ppm", filteredImage);
}
