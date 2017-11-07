/**
* Go through the file to check if it has any comments
* if there is a comment, it will be ignored
*
* @params FILE *file_img
**/
void skip_comments(FILE *file_img) {
    // Cria uma variável para armazenar cada caracter do comentário
    char buffer = fgetc(file_img);

    // Repete o laço enquanto a variável de buffer for igual a um '#'
    do {
        if (buffer == '#')
            // Se buffer for igual a '#', é por que está iniciando
            // um comentário, então a variável buffer recebe cada
            // caractere até que ele seja uma quebra de linha
            while (buffer != '\n')
                buffer = fgetc(file_img);
        else
            // Caso contrário, não é um comentário, então "devolve"
            // para o arquivo, para que ele possa ser lido novamente
            ungetc(buffer, file_img);
        // buffer pega novamente um caracter (para verificar
        // se tem mais algum comentário no arquivo)
        buffer = fgetc(file_img);
    } while (buffer == '#');
    // Quando o laço acabar (o último caracter pego for
    // diferente de um '#'), "devolve" para o arquivo o
    // caracter que está em buffer, pois não é um comentário
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


Image * buildImage( int width, int height ){
	int i = 0;

	Image *img = malloc(sizeof(Image));
	
	if(! img){
		printf("A imagem não conseguiu ser alocada na memória");
		exit(1);
	}
	
	img->width = width;
	img->height = height;

	img->pixels = (Pixel **)malloc(sizeof(Pixel*) * img->width);

	for( i = 0; i < width; i++ )
		img->pixels[i] = (Pixel*)malloc(img->height * sizeof(Pixel));

	return img;
}

/**
* Read a file line per line.
* Create a primitive type Image img and
* set its params width, height and
* your pixels, returning
*
* @params FILE *file
* @return Image img
**/
Image * getImage(FILE *file){
	char header[3];
	int width, height, i, j, tamanhoMaximo;

	fscanf(file, "%s ", header);

	if(header[0] != 'P' && header[1]!= '3'){
		printf("Tipo da imagem não suportado");
		exit(1);
	}

  	skip_comments(file);
	fscanf(file, "%d %d", &width, &height);

	fscanf(file, "%d", &tamanhoMaximo);
	
	Image *img = buildImage(width, height);

	for(i = 0; i < img->width; i++){
		for(j = 0; j < img->height; j++){
			skip_comments(file);
			fscanf(file, "%i", &img->pixels[i][j].r);
			skip_comments(file);
			fscanf(file, "%i", &img->pixels[i][j].g);
			skip_comments(file);
			fscanf(file, "%i", &img->pixels[i][j].b);
			skip_comments(file);
		}
	}

	fclose(file);

	return img;
}

/**
* Create a gray scale image
*
* @params Image *img
**/

void grayScale(Image *img){
	FILE *grayScale;
	int i, j;

	grayScale = fopen("grayScale.ppm", "w+");

	fprintf(grayScale, "P3\n");
	fprintf(grayScale, "%i %i\n", img->width, img->height);
	fprintf(grayScale, "255\n");
	//debug
	printf("%i\n", img->pixels[0][0].r);
	printf("%i\n", (int)(img->pixels[0][0].r*0.3));

	for(i = 0; i < img->width; i++){
		for(j = 0; j < img->height; j++){
			int luminance = (int)(img->pixels[i][j].r*0.3 + img->pixels[i][j].g*0.59 +
				img->pixels[i][j].b*0.11);
			fprintf(grayScale, "%i\n", luminance);
			fprintf(grayScale, "%i\n", luminance);
			fprintf(grayScale, "%i\n", luminance);
		}
	}
}


Image * gaussianFilter(Image *img){

	int i, j, k, l, newpx = 0;
	Pixel * px;
	int sum, div;
	int filter[5][5] = {{ 2,  4,  5,  4, 2 },
			    { 4,  9, 12,  9, 4 },
		            { 5, 12, 15, 12, 5 },
		            { 4,  9, 12,  9, 4 },
		            { 2,  4,  5,  4, 2 }};

	Image  *filteredImage = buildImage( img->width, img->height );
	
	for(i = 0; i < img->width; i++){
		for(j = 0; j < img->height; j++){
			sum = 0;
			div = 0;
			for(k = 0; k < 5; k++){
				for(l = 0; l < 5; l++){
					if((i+k >= 0 && i+k < img->width) && (j+l >= 0 && j+l < img->height)){ 
						sum += (img->pixels[i+k][j+l].r * filter[k][l]);
						div += filter[k][l];
					}
				}
			}
			newpx = sum / div;

			filteredImage->pixels[i][j].r = newpx;
			filteredImage->pixels[i][j].g = newpx;
			filteredImage->pixels[i][j].b = newpx;
		}
	}
	return filteredImage;
}

int saveImage(char *file, Image *img){

	int i = 0;
	int j = 0;

	FILE * fileName = fopen( file , "w" );

	if(!fileName)
		return -1;

	fprintf( fileName, "P3\n");
	fprintf( fileName, "%d %d\n", img->width, img->height );
	fprintf( fileName, "255\n" );

	for(i = 0; i < img->width; i++){
		for(j = 0; j < img->height; j++){

		    fprintf( fileName, "%u\n", img->pixels[i][j].r );
		    fprintf( fileName, "%u\n", img->pixels[i][j].g );
		    fprintf( fileName, "%u\n", img->pixels[i][j].b );
		}
	}

	fclose(fileName);

	return 0;

}
