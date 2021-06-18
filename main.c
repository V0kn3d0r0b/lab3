#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "bmp.h"


/*
 * The function reflects horizontally an uncompressed 24-bit bmp file
 * read through the ReadFile () function.
 *
 * original - array containing the original pixels
 * rows     - number of rows
 * cols     - number of columns
 *
 * new      - array containing the result of the function flip()
 */
int flip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  	int row, col;
  	if ((rows <= 0) || (cols <= 0)) return -1;

  	*new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  	for (row=0; row < rows; row++)
    		for (col=0; col < cols; col++) {
      			PIXEL* o = original + row*cols + col;
      			PIXEL* n = (*new) + row*cols + (cols-1-col);
      			*n = *o;
    		}

  return 0;
}

int main(int argc, char *argv[])
{
  	int r, c;
  	PIXEL *b, *nb;


	int g;
	extern int optind;
	extern char *optarg;

	//Possible options for the program

	int fFlag = 0;
	int oFlag = 0;

	//Place to store the file name
	char inputFileName[25];
	char outputFileName[25];


	char usage[] = "Usage: bmp_flip_tool [-f] [-o output_File] [input_file]";


	while((g = getopt(argc, argv, " o:f")) != -1){
		switch(g){
		//All possible options
		case 'f':
			fFlag = 1;
			break;
		case 'o':
			oFlag = 1;
			strncpy(outputFileName, optarg, 25);
			break;

		}
	}

	if((fFlag ==0)){
		printf("Atleast one argument is necessary!\n%s \n", usage);
		exit(1);
	}


	//Reading a BMP file
	if(optind == argc){
		//The input file is not specified
		readFile(NULL, &r, &c, &b);
	}else{
		strncpy(inputFileName, argv[optind], 25);
		readFile(inputFileName, &r, &c, &b);
	}


	//Horizontal reflection
	if(fFlag == 1){
			flip(b, &nb, r, c);
		}

	//Writing a BMP file
	if(oFlag == 0){
		//Output file not specified
		writeFile(NULL, r, c, nb);
	}else if(oFlag == 1){
		writeFile(outputFileName, r, c, nb);
	}

	//Freeing up allocated memory
  	free(b);
  	free(nb);
  return 0;
}
