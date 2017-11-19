/**
* Go through the file to check if it has any comments
* if there is a comment, it will be ignored
*
* @params FILE *file_img
**/
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

/**
* Open and read a file
*
* @params char filename
* @return FILE file
**/
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

/**
* Read a file line per line.
* Create a primitive type Image img and
* set its params width, height and
* its pixels, returning
*
* @params FILE *file
* @return Image img
**/
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

/*
Image * adaptiveThreshold(Image * img){
	int i, j, k, l, m, n, max, min, media, limiar=0;
	
	for(i = 1; i < img->height-1; ++i){
		for(j = 1; j < img->width-1; ++j){
			max = -1;
			min = 256;
			//Recuperando o valor máximo e min dos vizinhos
			for(k = 0; k < 3; ++k){
				for(l = 0; l < 3; ++l){	
					if(img->pixels[i-1+k][j-1+l].r > max){
						max = img->pixels[i-1+k][j-1+l].r;
					}
					if(img->pixels[i-1+k][j-1+l].r < min){
						min = img->pixels[i-1+k][j-1+l].r;
					}
				}
			}
			media = (max - min)/2;
			
			//128 é o contraste das imagens
			if((max - min) > 128){
				limiar = media/2;
			}else if(media < 100){
				limiar = max;
			}else{
				limiar = min;
			}
			for(m = 1; m < img->height-1; ++m){
				for(n = 1; n < img->width-1; ++n){
					if(img->pixels[m][n].r > limiar){
						img->pixels[m][n].r = 1;
						img->pixels[m][n].g = 1;
						img->pixels[m][n].b = 1;
					}else{
						img->pixels[m][n].r = 0;
						img->pixels[m][n].g = 0;
						img->pixels[m][n].b = 0;
					}
				}
			}							
		}
	}		
	
	return img;
}
*/
