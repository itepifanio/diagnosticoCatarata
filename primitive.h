/**
* A enum to create booleans 
* type in c
**/
enum bool
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
* A new typedef who read an image
* with width, height integer,
* an header char[54] and the 
* Pixel typedef
**/
typedef struct Images
{
	int width, height;
	char header[54];
	Pixel **pixels;
} Image;

