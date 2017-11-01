#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"
#include "ppmTreatment.h"

int main(){
	int i, j;
	FILE *file = readFile("Normal.ppm");
	Image *image = getImage(file);
	
	printf("Largura: %i\n", image->width);
	printf("Altura: %i\n", image->height);	

	//Tentando inicializar matriz de pixels

	Pixel matrizPixel[image->width][image->height];

	for(i = 0; i < image->width; i++){
		for(j = 0; j < image->height; j++){
			fscanf(file, "%i", &matrizPixel[i][j].r);
			fscanf(file, "%i", &matrizPixel[i][j].g);
			fscanf(file, "%i", &matrizPixel[i][j].b);
		}
	}

	return 0;
}
