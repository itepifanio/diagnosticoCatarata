#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libs/filters.h"

int main(int argc, char *argv[]){
	//Check image args
	char *arg2 = argv[2];
	char *images = "images/";
	char fileName[80];
	fileName[0] = '\0';

	strcat(fileName, images);
	strcat(fileName, arg2);

	FILE *file = fopen(fileName, "r");

	if(! file){
		printf("Ops, ocorreu algum erro com seus argumentos\n");
		printf("Os nomes devem ser no formato: \n");
		printf("./catarata -i Catarata.ppm -f ppm -o diagnosis.txt\n");
		exit(1);
	}else if(strcmp(argv[4], "ppm") != 0 || strcmp(argv[3], "-f") != 0 || strcmp(argv[5],"-o") != 0){
		printf("Ops, ocorreu algum erro com seus argumentos\n");
		printf("Os nomes devem ser no formato: \n");
		printf("./catarata -i Catarata.ppm -f ppm -o diagnosis.txt\n");
		printf("\n");
		exit(1);
	}else{
		printf("Inicializando imagem %s, aguarde...\n", argv[2]);
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
	
	Image *hough;
	
	if(argc == 8 && strcmp(argv[7], "-t") == 0){
		hough = houghTransform(binaryImage, image, true);
	}else{
		hough = houghTransform(binaryImage, image, false);
	}	

	saveImage("images/hough.ppm", hough, 255);

	diagnosis(hough, argv[6]);
}
