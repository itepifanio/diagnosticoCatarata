#include "filters.h"


Image * grayScale(Image *img){
	int i, j;

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			img->pixels[i][j].r = (int)(img->pixels[i][j].r*0.3 + img->pixels[i][j].g*0.59 +
				img->pixels[i][j].b*0.11);
            img->pixels[i][j].g = img->pixels[i][j].r;
            img->pixels[i][j].b = img->pixels[i][j].r;
		}
	}

	return img;
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
	
	int valueX=0, valueY=0, sobel;
	int i, j, k, l;

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


Image * binary(Image *img){
	int threshold = 28;
	int i, j;
	Image *binary = buildImage(img->width, img->height);

	for(i = 1; i < img->height-1; i++){
		for(j = 1; j < img->width-1; j++){
			if(img->pixels[i][j].r > threshold){
				binary->pixels[i][j].r = 1;				
				binary->pixels[i][j].g = 1;
				binary->pixels[i][j].b = 1;
			}else{
				binary->pixels[i][j].r = 0;				
				binary->pixels[i][j].g = 0;
				binary->pixels[i][j].b = 0;
			}  			
		}
	}

	return binary;	
}


Image * houghTransform(Image *img, Image *coloredImg, bool boolean){
	//Helper parameters
	int i, j;
	//Cicle parameters
	int a, b, t;
    int r, rmin = 80, rmax = 85;
	
	//Radius with will track the radius os the iris.
	//The circles will be detect using the max and min radius.
	
	//int rmin = fmin(img->height, img->width)/20;
	//int rmax = fmin(img->height, img->width)/4;

	
	//Starting matrix with hough values
	int ***houghValues = (int***)calloc(img->height, sizeof(int**));
	
	for(i = 0; i < img->height; i++){
		houghValues[i] = (int**)calloc(img->width, sizeof(int*));
		for(j = 0; j < img->width; j++){
			houghValues[i][j] = (int*)calloc(rmax - rmin + 1, sizeof(int));
		}
	}
	
	//Processing pixels
	for(i = rmin; i < img->height - rmin; i++){
		for(j = rmin; j < img->width - rmin; j++){
			if(img->pixels[i][j].r == 1){
				for(r = rmin; r <= rmax; r++){
					for(t = 0; t <= 360; t++){
						a = (int)(i - r * cos((double)(t * (PI/180))));
						b = (int)(j - r * sin((double)(t * (PI/180))));

						if((a >= 0) & (a < img->height) & (b >= 0) & (b < img->width)){
							houghValues[a][b][r - rmin] += 1;
						}
					}
				}
			}
		}
	}

	//Searching max values for girth
	int max = 0, raux = 0, iaux = 0, jaux = 0;

	for(i = rmin; i < img->height - rmin; i++){
		for(j = rmin; j < img->width - rmin; j++){
			for(r = rmin; r <= rmax; r++){
				if(houghValues[i][j][r - rmin] > max){
					max = houghValues[i][j][r - rmin];
					raux = r;
					iaux = i;
					jaux = j;
				}
			}
		}	
	}
	
	printf("R: %i\n", raux);
	printf("I: %i\n", iaux);
	printf("J: %i\n", jaux);

	if(boolean == true){
		for (i = rmin; i < coloredImg->height - rmin; i++) {
			for (j = rmin; j < coloredImg->width - rmin; j++) { 
	    		int dist = (int) sqrt(pow(i-iaux, 2) + pow(j-jaux,2));
	    		if(dist == raux) {
	        		coloredImg->pixels[i][j].r = 255;
	        		coloredImg->pixels[i][j].g = 0;
	        		coloredImg->pixels[i][j].b = 0;
	      		}
	    	}
	    }
	}else{
		for (i = 0; i < img->height; i++) {
			for (j = 0; j < img->width; j++) { 
	    		int dist = (int) sqrt(pow(i-iaux, 2) + pow(j-jaux,2));
	    		if(dist > raux) {
	        		coloredImg->pixels[i][j].r = 255;
	        		coloredImg->pixels[i][j].g = 255;
	        		coloredImg->pixels[i][j].b = 255;
	      		}
	    	}
	    }
	}	

    saveImage("images/segmentation.ppm", coloredImg, 255);

	return coloredImg;
}