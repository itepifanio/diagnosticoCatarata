#include "ppmTreatment.h"


void skipComments(FILE *file_img) {
    char buffer = fgetc(file_img);

    do {
        if (buffer == '#'){
            while (buffer != '\n'){
                buffer = fgetc(file_img);
	    	}

		}else{
            ungetc(buffer, file_img);
		}
        
        buffer = fgetc(file_img);
    } while (buffer == '#');
    
    ungetc(buffer, file_img);
}


FILE * readFile(char filename[]){
	FILE *file;
	file = fopen(filename, "rw");
	
	if (! file){
		printf("Ocorreu algum erro durante a leitura do arquivo");
		exit(1);
	}

	return file;
}


Image * buildImage(int width, int height){
	int i = 0;

	Image *img = malloc(sizeof(Image));
	
	if(!img){
		printf("Não foi possível alocar a imagem na memória");
		exit(1);
	}
	
	img->width = width;
	img->height = height;

	img->pixels = (Pixel **)malloc(sizeof(Pixel*) * img->height);

	for( i = 0; i < height; i++ )
		img->pixels[i] = (Pixel*)malloc(img->width * sizeof(Pixel));

	return img;
}


void freeMemory(Image * img){
    int i = 0;

    for(i = 0; i < img->height; i++)
        free(img->pixels[i]);

    free(img->pixels);
    free(img);
}


Image * getImage(FILE *file){
	char header[3];
	int width, height, i, j, maxPixelValue;

	fscanf(file, "%s ", header);

	if(header[0] != 'P' && header[1]!= '3'){	
		printf("Tipo da imagem não suportado");
		exit(1);
	}

  	skipComments(file);
	fscanf(file, "%d %d", &width, &height);

	fscanf(file, "%d", &maxPixelValue);
	
	Image *img = buildImage(width, height);

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			skipComments(file);
			fscanf(file, "%i", &img->pixels[i][j].r);
			skipComments(file);
			fscanf(file, "%i", &img->pixels[i][j].g);
			skipComments(file);
			fscanf(file, "%i", &img->pixels[i][j].b);
			skipComments(file);
		}
	}

	fclose(file);

	return img;
}


Pixel * pixelReturn(Image *img, int width, int height){

    if( width >= img->width ) width = img->width - 1;
    if( height >= img->height ) height = img->height - 1;
    if( width < 0 ) width = 0;
    if( height < 0 ) height = 0;

    return &img->pixels[height][width];
}


int saveImage(char *file, Image *img, int comp){

	int i = 0;
	int j = 0;

	FILE * fileName = fopen(file , "w");

	if(! fileName)
		return -1;

	fprintf( fileName, "P3\n");
	fprintf( fileName, "%d %d\n", img->width, img->height );
	fprintf( fileName, "%d\n", comp);

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			// Check values of pixels
			if(img->pixels[i][j].r > 255) img->pixels[i][j].r = 1;
			if(img->pixels[i][j].g > 255) img->pixels[i][j].g = 1;
			if(img->pixels[i][j].b > 255) img->pixels[i][j].b = 1;
			if(img->pixels[i][j].r < 0) img->pixels[i][j].r = 0;
			if(img->pixels[i][j].g < 0) img->pixels[i][j].g = 0;
			if(img->pixels[i][j].b < 0) img->pixels[i][j].b = 0;
			fprintf(fileName, "%d\n", img->pixels[i][j].r);
			fprintf(fileName, "%d\n", img->pixels[i][j].g);
			fprintf(fileName, "%d\n", img->pixels[i][j].b);
		}
	}

	fclose(fileName);

	return 0;

}


int sinRecursive(float *sinTable, int iterator){
	if(iterator <= 361){
		sinTable[iterator] = sin(iterator*PI/180);

		return sinRecursive(sinTable, ++iterator);
	}
}


int cosRecursive(float *cosTable, int iterator){
	if(iterator <= 361){
		cosTable[iterator] = cos(iterator*PI/180);

		return cosRecursive(cosTable, ++iterator);
	}
}