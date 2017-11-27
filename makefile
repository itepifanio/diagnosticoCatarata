all: catarata

catarata: ppmTreatment.o filters.o
	gcc main.c ppmTreatment.o filters.o -o catarata -W -g -lm

ppmTreatment.o: libs/ppmTreatment.c
	gcc -c libs/ppmTreatment.c -g -W -lm 

filters.o: libs/filters.c
	gcc -c libs/filters.c -g -W -lm

clean:
	rm ppmTreatment.o filters.o catarata \
	images/gaussianFilter.ppm \
	images/sobel.ppm \
	images/binary.ppm \
	images/grayScale.ppm \
	images/hough.ppm \