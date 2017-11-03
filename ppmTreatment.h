void skip_comments(FILE *file_img) {
    /**
     *  \brief Ignora os comentários da imagem
     *
     *  Função para ignorar os comentários da
     *  imagem durante a sua leitura.
     *
     *  \return Nada
     */

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


FILE * readFile(char filename[]){
	FILE *file;

	file = fopen(filename, "r");

	if (! file){
		printf("Ocorreu algum erro durante a leitura do arquivo");
		exit(1);
	}

	//Adicionar testes no arquivo aqui
	return file;
}

//Read and return image
Image * getImage(FILE *file){
	char header[3];
	int i, j, jumpLine;
	
	//fgets lê a primeira linha do arquivo e atribui ao tipo
    skip_comments(file);
	fscanf(file, "%s ", header);

	//Checa tipo da imagem P3
	if(header[0] != 'P' && header[1]!= '3'){
		printf("Tipo da imagem não suportado");
		exit(1);
	}
	
	Image *img = malloc(sizeof(Image)*1);

	if(! img){
		printf("A imagem não conseguiu ser alocada na memória");
		exit(1);
	}
	
	//Lê uma sequência de caracteres como unsigned char
	//E atribui os valores da linha ao tipo Image *img
    skip_comments(file);
	fscanf(file, "%d ", &img->width);
    skip_comments(file);
	fscanf(file, "%d ", &img->height);
    
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
