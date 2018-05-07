PROG = bin/catarata
CC = gcc
CFLAGS = -O0 -g -W -Wall -pedantic
OBJS = main.o ppmTreatment.o filters.o
RM = -f *.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG) -lm
	mv *.o build/

main.o: include/ppmTreatment.h include/filters.h
	$(CC) $(CFLAGS) -c src/main.c -g -W -lm

ppmTreatment.o: include/ppmTreatment.h
	$(CC) $(CFLAGS) -c src/ppmTreatment.c -g -W -lm

filters.o: include/filters.h
	$(CC) $(CFLAGS) -c src/filters.c -g -W -lm

clean:
	rm -f build/*.o \
	rm bin/catarata \
	images/gaussianFilter.ppm \
	images/sobel.ppm \
	images/binary.ppm \
	images/grayScale.ppm \
	images/hough.ppm \
