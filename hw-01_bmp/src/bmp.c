#include "bmp.h"

bmpFILE load_bmp(char* filename){
    FILE* bmp = fopen(filename, "rb");

    BITMAPFILEHEADER* bfh = malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER* bih = malloc(sizeof(BITMAPINFOHEADER));

    
    fread(&bfh->bfType, 2, 1, bmp);
    fread(&bfh->bfSize, 4, 1, bmp);
    fread(&bfh->bfReserved1, 2, 1, bmp);
    fread(&bfh->bfReserved2, 2, 1, bmp);
    fread(&bfh->bfOffBits, 4, 1, bmp);

    fread(&bih->biSize , 4, 1, bmp);
    fread(&bih->biWidth , 4, 1, bmp);
    fread(&bih->biHeight , 4, 1, bmp);
    fread(&bih->biPlanes , 2, 1, bmp);
    fread(&bih->biBitCount , 2, 1, bmp);
    fread(&bih->biCompression , 4, 1, bmp);
    fread(&bih->biSizeImage , 4, 1, bmp);
    
    fread(&bih->biXPelsPerMeter , 4, 1, bmp);
    fread(&bih->biYPelsPerMeter , 4, 1, bmp);
    fread(&bih->biClrUsed , 4, 1, bmp);
    fread(&bih->biClrImportant , 4, 1, bmp);
    
    DWORD h = bih->biHeight;
    DWORD w = bih->biWidth;

    int* data[h];

    for (int i = 0; i < h; i++){
        data[i] = malloc(sizeof(int) * w);
    }
    
    
    int padding = (4 - ((w * 3) % 4)) % 4;

    for(int i = 0; i < h; i++){
        for (int j = 0; j < w; j++)
            fread(data[i], bih->biBitCount / 8, 1, bmp);

        fseek(bmp, padding, SEEK_CUR);
        
    }

    // for (int i=0; i<h; i++){
    //     for(int j=0; j<w; j++)
    //         printf("%x ", data[j][i]);
    //     printf("\n");
    // }
    fclose(bmp);
    bmpFILE bmpfile;
    bmpfile.bfh = *bfh;
    bmpfile.bih = *bih;
    bmpfile.data = data;
    // printf("Type: %d\n", bfh->bfType);
    // printf("Size: %d\n", bfh->bfSize);
    // printf("Reserved1: %d\n", bfh->bfReserved1);
    // printf("Reserved2: %d\n", bfh->bfReserved2);
    // printf("OffBits: %d\n", bfh->bfOffBits);
    // printf("\n%s\n", "infoheader");
    // printf("Size: %d\n", bih->biSize);
    // printf("Width: %d\n", bih->biWidth);
    // printf("Height: %d\n", bih->biHeight);
    // printf("Planes: %d\n", bih->biPlanes);
    // printf("BitCount: %d\n", bih->biBitCount);
    // printf("Compression: %d\n", bih->biCompression);
    // printf("SizeImage: %d\n", bih->biSizeImage);
    // printf("XPelsPerMeter: %d\n", bih->biXPelsPerMeter);
    // printf("YPelsPerMeter: %d\n", bih->biYPelsPerMeter);
    // printf("ClrUsed: %d\n", bih->biClrUsed);
    // printf("ClrImportant: %d\n", bih->biClrImportant);
    // printf("(%ld)", sizeof(BITMAPINFOHEADER));
    return bmpfile;
};