#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"

int main(){
	Image *img = (Image *)malloc(sizeof(Image));
	FILE *file;
	int pixel;
	char header[16];

	
	file = fopen("Normal.ppm", "r");
	
	//fgets lê a primeira linha do arquivo
	fgets(header, sizeof(header), file);

	//Lê uma sequência de caracteres como unsigned char
	//E atribui os valores da linha ao tipo Image *img
	fscanf(file, "%d %d", &img->width, &img->height);

	//Atribui no tipo Image *img as dimensões dela
	printf("Width:%d\nHeight:%d\n", img->width, img->height);

	//Atribui no tipo Image *img os valores em rgb
	img->pixels = malloc(
		 3 * img->width * img->height * sizeof(Pixel)
	);

	while(getc(file) != EOF){
		fscanf(file, "%d", &img->pixels->r);
		fscanf(file, "%d", &img->pixels->g);
		fscanf(file, "%d", &img->pixels->b);
	}

	/*
	int i = 0;
	int teste = 3 * img->width * img->height * sizeof(Pixel);
	while(i < teste){
		if(i == 10)
			break;
		printf("%i\n", img->pixels->r);
		printf("%i\n", img->pixels->g);
		printf("%i\n", img->pixels->b);
	}*/
	

	return 0;
}
