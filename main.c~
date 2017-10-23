#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"

int main(){
	Image *img = (Image*) malloc(sizeof(Image));

	FILE *file;
	
	file = fopen("Normal.ppm", "r");

	if(file == NULL){
		printf("File doesn't exist, check the local repository\n");
		return 0;
	}

	while( fgetc(file) != '\n');

	img->pixels = (Pixel*)malloc(img->height * img->width * sizeof(Pixel));

//	printf("Width:%d\nHeight:%d", img->width, img->height);

	fscanf(file, "%d %d", &img->height, &img->width);


	printf("Width:%d\nHeight:%d\n", img->width, img->height);
//	printf("Image data:\n Width: %d\n Height: %d\n", img->height, img->width);
	
	return 0;
}
