/**
* Go through the file to check if it has any comments
* if there is a comment, it will be ignored
*
* @params FILE *file_img
**/
void skipComments(FILE *file_img) {
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

  	skipComments(file);
	fscanf(file, "%d %d", &width, &height);

	fscanf(file, "%d", &tamanhoMaximo);
	
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

int saveImage(char *file, Image *img){

	int i = 0;
	int j = 0;

	FILE * fileName = fopen( file , "w" );

	if(!fileName)
		return -1;

	fprintf( fileName, "P3\n");
	fprintf( fileName, "%d %d\n", img->width, img->height );
	fprintf( fileName, "255\n" );

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){

		    fprintf(fileName, "%d\n", img->pixels[i][j].r);
		    fprintf(fileName, "%d\n", img->pixels[i][j].g);
		    fprintf(fileName, "%d\n", img->pixels[i][j].b);
		}
	}

	fclose(fileName);

	return 0;

}
