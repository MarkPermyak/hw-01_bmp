#ifndef __BMP_H__
#define __BMP_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

     
#define SIZEOF_BFH 14
#define SIZEOF_BIH 40

typedef long LONG;
typedef uint32_t DWORD;   
typedef uint16_t WORD;    
typedef uint8_t BYTE;

 typedef struct tagBITMAPFILEHEADER{
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
 } BITMAPFILEHEADER, *PBITMAPFILEHEADER;

 typedef struct tagBITMAPINFOHEADER{
    DWORD  biSize;
    DWORD   biWidth;
    DWORD   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    DWORD   biXPelsPerMeter;
    DWORD   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
 } BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct bmp_file_t{
   BITMAPFILEHEADER bfh;
   BITMAPINFOHEADER bih;
   int** data;
} bmpFILE;

bmpFILE load_bmp(char*);

#endif
