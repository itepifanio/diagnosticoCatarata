#include <stdio.h>
#include <stdlib.h>
#include "primitive.h"

int main(){
	Image *img = (Image *)malloc(sizeof(Image));
	FILE *file;
	int i, c;
	char header[16];

	
	file = fopen("Normal.ppm", "r");

	fgets(header, sizeof(header), file);


	fscanf(file, "%d %d", &img->height, &img->width);

	printf("Width:%d\nHeight:%d\n", img->width, img->height);

	return 0;
}
