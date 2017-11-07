#include <math.h>
/**
* Create a gray scale image
*
* @params Image *img
* return FILE grayScale
**/

Image * grayScale(Image *img){
	FILE *grayScale = fopen("grayScale.ppm", "w+");;
	int i, j;

	fprintf(grayScale, "P3\n");
	fprintf(grayScale, "%i %i\n", img->width, img->height);
	fprintf(grayScale, "255\n");

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			int luminance = (int)(img->pixels[i][j].r*0.3 + img->pixels[i][j].g*0.59 +
				img->pixels[i][j].b*0.11);
			fprintf(grayScale, "%i\n", luminance);
			fprintf(grayScale, "%i\n", luminance);
			fprintf(grayScale, "%i\n", luminance);
		}
	}

	FILE *file = readFile("grayScale.ppm");

	Image *newGrayImage = getImage(file);

	return newGrayImage;
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

	Image  *filteredImage = buildImage(img->width, img->height);
	
	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			sum = 0;
			div = 0;
			for(k = 0; k < 5; k++){
				for(l = 0; l < 5; l++){
			                px = pixelReturn(img,  j + (l - 2), i + (k - 2));
					sum += (px->r * filter[k][l]);
					div += filter[k][l];
					
				}
			}
			newpx = sum / div;

			filteredImage->pixels[i][j].r = (int) newpx;
			filteredImage->pixels[i][j].g = (int) newpx;
			filteredImage->pixels[i][j].b = (int) newpx;
		}
	}
	return filteredImage;
}

/**
* Applying sobel filter.
* Receiving gray scale file and filtering
*
*
**/
void sobelFilter(Image *img){
	int sobelX[3][3] = {
		{ 1, 2, 1},
		{ 0, 0, 0},			
		{-1,-2,-1},
	};

	int sobelY[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},			
		{-1, 0, 1},
	};

	FILE *sobelFilter = fopen("sobelFilter.ppm", "w+");

	fprintf(sobelFilter, "P3\n");
	fprintf(sobelFilter, "%i %i\n", img->width, img->height);
	fprintf(sobelFilter, "255\n");

	/*Sobel é o valor inteiro que corresponde a fórmula
		int sobel = sqrt(valueX^2 + valueX^2);
	*/
	int valueX, valueY, sobel;
	int i, j;

	//Não pegar as bordas da imagem, pois retorna segmentation fault
	for(i = 1; i < img->height-1; i++){
		for(j = 1; j < img->width-1; j++){
			valueX = (
				(sobelX[0][0] * img->pixels[i-1][j-1].r) +
				(sobelX[0][1] * img->pixels[i][j-1].r) +
				(sobelX[0][2] * img->pixels[i+1][j-1].r) +
			        (sobelX[1][0] * img->pixels[i-1][j].r) +
			        (sobelX[1][1] * img->pixels[i][j].r) +
				(sobelX[1][2] * img->pixels[i+1][j].r) +
			        (sobelX[2][0] * img->pixels[i-1][j+1].r) +
				(sobelX[2][1] * img->pixels[i][j+1].r) +
				(sobelX[2][2] * img->pixels[i+1][j+1].r)
			);

			valueY = (
				(sobelY[0][0] * img->pixels[i-1][j-1].r) +
				(sobelY[0][1] * img->pixels[i][j-1].r) +
				(sobelY[0][2] * img->pixels[i+1][j-1].r) +
			        (sobelY[1][0] * img->pixels[i-1][j].r) +
			        (sobelY[1][1] * img->pixels[i][j].r) +
				(sobelY[1][2] * img->pixels[i+1][j].r) +
			        (sobelY[2][0] * img->pixels[i-1][j+1].r) +
				(sobelY[2][1] * img->pixels[i][j+1].r) +
				(sobelY[2][2] * img->pixels[i+1][j+1].r)
			);
			

			sobel = (int)(sqrt(pow(valueX, 2) + pow(valueY, 2)));

			printf("%i\n", sobel);

			if(sobel > 255){
				sobel = 255;
			}

			fprintf(sobelFilter, "%i\n", sobel);
			fprintf(sobelFilter, "%i\n", sobel);
			fprintf(sobelFilter, "%i\n", sobel);
		}
	}

}
