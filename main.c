#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libs/filters.h"

int main(int argc, char *argv[]){
	char *entrada = argv[2];
	char *images = "images/";
	char fileName[80];
	fileName[0] = '\0';
	
	strcat(fileName, images);
	strcat(fileName, entrada);

	FILE *file = fopen(fileName, "r");
	
	if(! file){
		printf("Ops, ocorreu algum erro com seus argumentos\n");
		printf("Os nomes devem ser no formato: \n");
		printf("./catarata -i images/Catarata.ppm\n");
		exit(1);
	}else{
		printf("Inicializando image, aguarde... %s\n", argv[2]);
	}

	file = readFile(fileName);
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
	
	file = readFile(fileName);
	image = getImage(file);
	
	Image *hough = houghTransform(binaryImage, image, false);
	saveImage("images/hough.ppm", hough, 255);

	diagnosis(hough, "diagnosis.txt");
}
