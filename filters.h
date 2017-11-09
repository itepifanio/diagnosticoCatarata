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
Image * sobelFilter(Image *img){
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

	Image  *filteredImage = buildImage(img->width, img->height);
	
	/*Sobel é o valor inteiro que corresponde a fórmula
		int sobel = sqrt(valueX^2 + valueY^2);
	*/
	int valueX=0, valueY=0, sobel;
	int i, j, k, l;

	//Não pegar as bordas da imagem, pois retorna segmentation fault
	for(i = 1; i < img->height-1; ++i){
		for(j = 1; j < img->width-1; ++j){
			valueX=0;
			valueY=0;
			for(k = 0; k < 3; ++k){
				for(l = 0; l < 3; ++l){	
					valueX += img->pixels[i-1+k][j-1+l].r * sobelX[k][l];
					valueY += img->pixels[i-1+k][j-1+l].r * sobelY[k][l];

					sobel = (int)(sqrt(pow(valueX, 2) + pow(valueY, 2)));

					if(sobel > 255){
						sobel = 255;
					}

					filteredImage->pixels[i][j].r = (int) sobel;
					filteredImage->pixels[i][j].g = (int) sobel;
					filteredImage->pixels[i][j].b = (int) sobel;
				}
			}
		}
	}

	return filteredImage;
}