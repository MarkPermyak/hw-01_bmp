#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

bmpFILE* load_bmp(char* filename){
    FILE* bmp = fopen(filename, "rb");

    if(!bmp)
        return NULL;   
    
    BITMAPFILEHEADER* bfh = malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER* bih = malloc(sizeof(BITMAPINFOHEADER));

    fread(bfh, 14, 1, bmp);
    fread(bih, 40, 1, bmp);

    DWORD h = bih->biHeight;
    DWORD w = bih->biWidth;
    
    int padding = (4 - ((w * sizeof(pixel)) % 4)) % 4;

    int number_of_pxls = h * w;

    pixel** data = malloc(sizeof(pixel) * h * w);

    for(int i = 0; i < h; i++)
        data[i] = malloc(sizeof(pixel) * w);

    for(int i = 0; i < h; i++){
        fread(data[i], sizeof(pixel), w, bmp);
        fseek(bmp, padding, SEEK_CUR);
    }


    fclose(bmp);

    bmpFILE* bmpfile = malloc(bfh->bfSize);
    bmpfile->bfh = *bfh;
    bmpfile->bih = *bih;
    bmpfile->data = data;

    

    return bmpfile;
};
void free_bmp(bmpFILE* bmp){

    // free(&bmp->bfh);
    // free(&bmp->bih);
    // for (int i = 0; i < bmp->bih.biHeight; i++){
    //     free(&bmp->data[i]);
    // }

    // free(&bmp->data);
    // free(bmp);
};

bmpFILE* crop(bmpFILE* bmp, int x, int y, int w_cr, int h_cr){
    
    BITMAPFILEHEADER* bfh = &bmp->bfh;
    BITMAPINFOHEADER* bih = &bmp->bih;
    pixel** data = bmp->data;

    int h = bih->biHeight;

    if(x == bih->biWidth || y == bih->biHeight)
        return bmp;

    //printf("OK1\n");
   

   

    pixel** data_cr = malloc(sizeof(pixel) * h_cr * w_cr);

    for(int i = 0; i < h_cr; i++)
        data_cr[i] = malloc(sizeof(pixel) * w_cr);

    // printf("OK2\n");

    // printf("%d %d %d %d %d\n", h_cr, w_cr, h, x, y);
    
    //printf("%ld\n", sizeof(data_cr[0]));

    for(int i = 0; i < h_cr; i++){
        
            data_cr[i] = data[h - y - h_cr + i];
            //printf("OK\n");
        
    }
    //printf("OK\n");
    bih->biHeight = h_cr;
    bih->biWidth = w_cr;
    bmp->data = data_cr;

    return bmp;
};

bmpFILE* rotate(bmpFILE* bmp){
    BITMAPFILEHEADER* bfh = &bmp->bfh;
    BITMAPINFOHEADER* bih = &bmp->bih;

    int h = bih->biHeight;
    int w = bih->biWidth;

    bih->biHeight = w;
    bih->biWidth = h;

    int h_r = bih->biHeight;
    int w_r = bih->biWidth;
    pixel** data = bmp->data;

    pixel** data_r = malloc(sizeof(pixel) * h_r * w_r);
    
    for(int i = 0; i < h_r; i++)
        data_r[i] = malloc(sizeof(pixel) * w_r);
    
    for(int i = 0; i < h_r; i++){
        for (int j = 0; j < w_r; j++){
            data_r[i][j] = data[j][w - 1 - i];
        }
    }
    //printf("OK3\n");
    bmp->data = data_r;
    
    return bmp;
};

void save_bmp(char* filename, bmpFILE* bmp){
    FILE* fp = fopen(filename, "wb");

    BITMAPFILEHEADER* bfh = &bmp->bfh;
    BITMAPINFOHEADER* bih = &bmp->bih;
    
    
    int w = bih->biWidth;
    int h = bih->biHeight;
    
    int padding = (4 - ((w* sizeof(pixel)) % 4)) % 4;
   

    bih->biSizeImage = w * h * sizeof(pixel) + padding * h;
    bfh->bfSize = bih->biSizeImage + bfh->bfOffBits;
    
    fwrite(bfh, 14, 1 , fp);
    fwrite(bih, 40, 1, fp);
    pixel** data = bmp->data;
    
    char* padding_str[padding];
    for(int i=0; i<padding; i++)
        padding_str[i] = 0b00000000;

    
    for (int i = 0; i < h; i++){
        fwrite(data[i], sizeof(pixel), w, fp);
        fwrite(padding_str, 1, padding, fp);
    }
    //printf("OK4\n");
    fclose(fp);
};
//printf("%ld", sizeof(data));
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