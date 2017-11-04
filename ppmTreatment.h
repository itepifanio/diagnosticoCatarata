/**
* Check the file to check if has comment on line
* if has a comment, his will be ignored
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

/**
* Read a file line per line.
* Create a primitive type Image img and
* set your params width, height and
* your pixels, returning 
*
* @params FILE *file
* @return Image img
**/
Image * getImage(FILE *file){
	char header[3];
	int i, j, tamanhoMaximo;
	
	fscanf(file, "%s ", header);

	if(header[0] != 'P' && header[1]!= '3'){
		printf("Tipo da imagem não suportado");
		exit(1);
	}
	
	Image *img = malloc(sizeof(Image));

	if(! img){
		printf("A imagem não conseguiu ser alocada na memória");
		exit(1);
	}
    	skip_comments(file);
	fscanf(file, "%d %d", &img->width, &img->height);

	fscanf(file, "%d", &tamanhoMaximo);    	

	img->pixels = (Pixel **)malloc(sizeof(Pixel*) * img->width);

	for(i = 0; i < img->width; i++){
		img->pixels[i] = (Pixel*)malloc(img->height * sizeof(Pixel));
	}

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
