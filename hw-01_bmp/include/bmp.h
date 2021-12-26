#ifndef __BMP_H__
#define __BMP_H__

#include <stdint.h>

typedef uint32_t DWORD;   
typedef uint16_t WORD;    
typedef uint8_t BYTE;

#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER{
   WORD bfType;
   DWORD bfSize;
   WORD bfReserved1;
   WORD bfReserved2;
   DWORD bfOffBits;
} BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tagBITMAPINFOHEADER{
   DWORD biSize;
   DWORD biWidth;
   DWORD biHeight;
   WORD biPlanes;
   WORD biBitCount;
   DWORD biCompression;
   DWORD biSizeImage;
   DWORD biXPelsPerMeter;
   DWORD biYPelsPerMeter;
   DWORD biClrUsed;
   DWORD biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct pixel_t{
   BYTE blue;
   BYTE green;
   BYTE red;
} pixel;
#pragma pack(pop)

typedef struct bmp_file_t{
   BITMAPFILEHEADER bfh;
   BITMAPINFOHEADER bih;
   pixel** data;
} bmpFILE;

bmpFILE* load_bmp(char*);
// void free_bmp(bmpFILE*);
void crop(bmpFILE*, int, int, int, int);
void rotate(bmpFILE*);
void save_bmp(char*, bmpFILE*);

#endif
