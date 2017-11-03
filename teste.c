#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 

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

typedef struct {
    int r, g, b;
} pixel;

int i, j, w, h, cod, max, comp = 255;

void build_img(char file[], pixel img[max][max]){
    /**
     *  \brief Função para criar a imagem
     *
     *  Função que gera uma imagem ppm a partir de uma matriz de Pixels
     *
     *  \param file - Nome do arquivo de saída
     *  \param img - Matriz da imagem a ser gerada
     *  \return Nada
     */

    file = "lena_peb.ppm";

    // Cria uma variável do tipo arquivo
    FILE *img_f;
    // Cria um arquivo com o nome do arquivo + '_' + operação escolhida
    img_f = fopen(file, "w");

    // Cria o cabeçalho da imagem ppm
    fprintf(img_f, "%s\n", "P3");
    // Define a largura e altura da imagem
    fprintf(img_f, "%i %i\n", w, h);
    // Define a cor máxima (qualidade) da imagem
    fprintf(img_f, "%i\n", comp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Trata erros básicos, como de cor negativa e/ou maior que o máximo.
            fprintf(img_f, "%i %i %i\n",
            (img[i][j].r > comp) ? comp : (img[i][j].r < 0) ? 0 : img[i][j].r,
            (img[i][j].g > comp) ? comp : (img[i][j].g < 0) ? 0 : img[i][j].g,
            (img[i][j].b > comp) ? comp : (img[i][j].b < 0) ? 0 : img[i][j].b);

    // Fecha o arquivo aberto
    fclose(img_f);
}


int main(int argc, char** argv) {
	FILE *file_img;
	
	file_img = fopen("Normal.ppm", "r");

	skip_comments(file_img);
	fscanf(file_img, "P3 ");
	skip_comments(file_img);
	fscanf(file_img, "%d ", &w);
	skip_comments(file_img);
	fscanf(file_img, "%d ", &h);
	skip_comments(file_img);
	fscanf(file_img, "%d", &cod);


	if(w > h)
		max = w;
	else
		max = h;

	pixel img[max][max];

	for( i = 0; i < h; i++){
		for(j = 0; j < w; j++){
			fscanf(file_img, "%i ", &img[i][j].r);
			fscanf(file_img, "%i ", &img[i][j].g);
			fscanf(file_img, "%i ", &img[i][j].b);
		}
	}
	for( i = 0; i < h; i++){
		for(j = 0; j < w; j++){
			printf("%d ", img[i][j].r);
			printf("%d ", img[i][j].g);
			printf("%d ", img[i][j].b);
			printf("\n");
		}
	}

	printf("Até aqui foi\n");

	fclose(file_img);

	build_img("Normal", img);
    
	return 0;
}
