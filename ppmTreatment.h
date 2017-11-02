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
	char header[2];
	int i, j, jumpLine;
	
	//fgets lê a primeira linha do arquivo e atribui ao tipo
	fscanf(file, "%s", header);

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
	fscanf(file, "%d %d", &img->width, &img->height);

	//Gambiarra para pular linha do tamanho
	fscanf(file, "%d", &jumpLine);

	img->pixels = (Pixel **)malloc(sizeof(Pixel*) * img->width);

	for(i = 0; i < img->width; i++){
		img->pixels[i] = (Pixel*)malloc(img->height * sizeof(Pixel));
	}

	for(i = 0; i < img->width; i++){
		for(j = 0; j < img->height; j++){
			fscanf(file, "%i%i%i", &img->pixels[i][j].r, &img->pixels[i][j].g, &img->pixels[i][j].b);		
		}
	}
	
	fclose(file);

	return img;
}
