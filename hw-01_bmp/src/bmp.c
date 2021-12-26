#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int load_bmp(char* filename, bmpFILE* work_bmp){
    FILE* bmp = fopen(filename, "rb");
    
    if(!bmp){
        printf("Input image doesn't exists\n");
        return 1;
    }

    BITMAPFILEHEADER* bfh = &work_bmp->bfh;
    BITMAPINFOHEADER* bih = &work_bmp->bih;
    

    fread(bfh, sizeof(BITMAPFILEHEADER), 1, bmp);
    fread(bih, sizeof(BITMAPINFOHEADER), 1, bmp);

    int h = bih->biHeight;
    int w = bih->biWidth;
    
    int padding = (4 - ((w * sizeof(pixel)) % 4)) % 4;

    work_bmp->data = malloc(sizeof(pixel*) * h);

    pixel* pixels_row = malloc(sizeof(pixel) * w * h);

    if((!work_bmp->data) || (!pixels_row)){
        printf("Memory didn't allocated\n");
        return 1;
    }
    
    for (int i = 0; i < h; i++) {
        work_bmp->data[i] = pixels_row + i * w;
    }

    for(int i = 0; i < h; i++){
        fread(work_bmp->data[i], sizeof(pixel), w, bmp);
        fseek(bmp, padding, SEEK_CUR);
    }

    fclose(bmp);

    work_bmp->bfh = *bfh;
    work_bmp->bih = *bih;

    return 0;
};

void free_data(bmpFILE* bmp){
    free(bmp->data[0]);
    free(bmp->data);
};

int crop(bmpFILE* bmp, int x, int y, int w_cr, int h_cr){
    BITMAPINFOHEADER* bih = &bmp->bih;
    pixel** data = bmp->data;

    int h = bih->biHeight;

    pixel** data_cr = malloc(sizeof(pixel*) * h_cr);
    pixel* pixels_row = malloc(sizeof(pixel) * w_cr * h_cr);

    if((!data_cr) || (!pixels_row)){
        printf("Memory didn't allocated\n");
        return 1;
    }

    for (int i = 0; i < h_cr; i++) {
        data_cr[i] = pixels_row + i * w_cr;
    }

    for(int i = 0; i < h_cr; i++){        
        for(int j=0; j < w_cr; j++)
            data_cr[i][j] = data[h - y - h_cr + i][x + j];
    }    

    bih->biHeight = h_cr;
    bih->biWidth = w_cr;

    free_data(bmp);

    bmp->data = data_cr;
    
    return 0;
};

int rotate(bmpFILE* bmp){
    BITMAPINFOHEADER* bih = &bmp->bih;
    pixel** data = bmp->data;

    int h = bih->biHeight;
    int w = bih->biWidth;

    bih->biHeight = w;
    bih->biWidth = h;

    int h_r = bih->biHeight;
    int w_r = bih->biWidth;
    
    pixel** data_r = malloc(sizeof(pixel*) * h_r);
    pixel* pixels_row = malloc(sizeof(pixel) * w_r * h_r);

    if((!data_r) || (!pixels_row)){
        printf("Memory didn't allocated\n");
        return 1;
    }

    for (int i = 0; i < h_r; i++) {
        data_r[i] = pixels_row + i * w_r;
    }

    for(int i = 0; i < h_r; i++){
        for (int j = 0; j < w_r; j++){
            data_r[i][j] = data[j][w - 1 - i];
        }
    }

    free_data(bmp);

    bmp->data = data_r;
    
    return 0;
};

void save_bmp(char* filename, bmpFILE* bmp){
    FILE* fp = fopen(filename, "wb");

    BITMAPFILEHEADER* bfh = &bmp->bfh;
    BITMAPINFOHEADER* bih = &bmp->bih;
    pixel** data = bmp->data;
        
    int w = bih->biWidth;
    int h = bih->biHeight;
    
    int padding = (4 - ((w* sizeof(pixel)) % 4)) % 4;
   
    bih->biSizeImage = w * h * sizeof(pixel) + padding * h;
    bfh->bfSize = bih->biSizeImage + bfh->bfOffBits;
    
    fwrite(bfh, 14, 1 , fp);
    fwrite(bih, 40, 1, fp);
    
    char* padding_str[padding];

    for(int i=0; i<padding; i++)
        padding_str[i] = 0b00000000;

    for (int i = 0; i < h; i++){
        fwrite(data[i], sizeof(pixel), w, fp);
        fwrite(padding_str, 1, padding, fp);
    }

    free_data(bmp);
    fclose(fp);
};
