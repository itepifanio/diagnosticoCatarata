/**
* A enum to create booleans 
* type in c
**/
typedef enum bool
{
	true = 1,
	false = 0
} bool;

/**
* A new typedef with rgb pattern
**/
typedef struct Pixels
{
	int r, g, b;
} Pixel;

/**
* A new typedef that read an image
* with width, height integer,
* an header char[54] and the 
* typedef Pixel
**/
typedef struct Images
{
	int width, height;
	int maxLength;
	Pixel **pixels;
} Image;

