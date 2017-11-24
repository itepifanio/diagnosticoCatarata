#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libs/filters.h"
/*
void checkArgv(char *argv[]){
	char *nomeArquivo = strcat("images/", argv[2]);
	FILE *file = fopen(nomeArquivo, "r");

	if(! file){
		printf("Ops, ocorreu algum erro com seus argumentos\n");
		printf("Os nomes devem ser no formato: \n");
		printf("./catarata -i images/Catarata.ppm\n");
		exit(1);
	}else{
		printf("Inicializando image, aguarde... %s\n", argv[2]);
	}
}
*/
int main(int argc, char *argv[]){
	char *nomeArquivo = argv[2];
	char *batata = "batata";
	strcat(batata, nomeArquivo);
	
	if((out = (char *)malloc(strlen(nomeArquivo) + strlen(batata) + 1)) != NULL)
	{
   		strcpy(out, nomeArquivo);
   		strcat(out, batata);
	}


	FILE *file = readFile(strcat("images/", nomeArquivo));
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
	
	file = readFile(argv[2]);
	image = getImage(file);
	
	Image *hough = houghTransform(binaryImage, image);
	saveImage("images/hough.ppm", hough, 255);
}
