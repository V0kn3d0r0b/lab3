#ifndef BMP_H
#define BMP_H

typedef struct {
  unsigned short padding;
  unsigned int bfOffBits;
  unsigned short bfType;
  unsigned int bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
} BITMAPFILEHEADER;

typedef struct {
  unsigned int biSize;
  int biWidth;
  int biHeight;
  unsigned short biBitCount;
  unsigned short biPlanes;
  unsigned int biSizeImage;
  unsigned int biCompression;
  unsigned int biXPelsPerMeter;
  unsigned int biYPelsPerMeter;
  unsigned int biClrImportant;
  unsigned int biClrUsed;
} BITMAPINFOHEADER;

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} PIXEL;

#define DEFAULT_BITMAP_OFFSET 1078

/* Reading an uncompressed 24-bit BMP file from 'filename';
   returns the number of 'rows', the number of 'columns'
   and ' bitmap' as an array of pixels.
   The function returns 0 as a result of successful execution. */
int readFile (char* filename, int* rows, int* cols, PIXEL** bitmap);

/* Write a 24-bit BMP file without compression.
BMP size-the number of rows multiplied by the number of columns, bitmap-an array of pixels.
The function returns 0 as a result of successful execution. */

int writeFile (char* filename, int rows, int cols, PIXEL* bitmap);

/* Reading the BMP file header from the fd. Returns the number of rows, columns, and the starting position of the BMP.
The function returns 0 as a result of successful execution.
*/

int readHeader(int fd, int *rows, int *cols, unsigned int *start);

/* Record the BMP file header from the fd. Returns the number of rows, columns, and the starting position of the BMP.
The function returns 0 as a result of successful execution.
*/

int writeHeader(int fd, int rows, int cols, unsigned int start);

/* Reading a BMP file from the fd. BMP size - number of rows per number of columns.
The function returns 0 as a result of successful execution. */

int readBits(int fd, PIXEL* bitmap, int rows, int cols, unsigned int start);

/* Writing a bmp file to fd. BMP size - number of rows per number of columns.
The function returns 0 as a result of successful execution.*/

int writeBits(int fd, int rows, int cols, PIXEL* bitmap, unsigned int start);

#endif /*BMP_H*/
