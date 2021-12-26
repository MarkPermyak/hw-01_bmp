#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

bmpFILE* load_bmp(char* filename){
    FILE* bmp = fopen(filename, "rb");

    if(!bmp)
        return NULL;   
    
    BITMAPFILEHEADER* bfh = malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER* bih = malloc(sizeof(BITMAPINFOHEADER));

    if (!bfh || !bih)
        return NULL;

    fread(bfh, 14, 1, bmp);
    fread(bih, 40, 1, bmp);

    int h = bih->biHeight;
    int w = bih->biWidth;
    
    int padding = (4 - ((w * sizeof(pixel)) % 4)) % 4;

    pixel** data = malloc(sizeof(pixel) * h * w);

    for(int i = 0; i < h; i++){
        data[i] = malloc(sizeof(pixel) * w);
        fread(data[i], sizeof(pixel), w, bmp);
        fseek(bmp, padding, SEEK_CUR);
    }

    fclose(bmp);

    bmpFILE* bmpfile = malloc(bfh->bfSize);

    if(!bmpfile)
        return NULL;

    bmpfile->bfh = *bfh;
    bmpfile->bih = *bih;
    bmpfile->data = data;

    return bmpfile;
};

// void free_bmp(bmpFILE* bmp){

//     free(&bmp->bfh);
//     free(&bmp->bih);
//     for (int i = 0; i < bmp->bih.biHeight; i++){
//         free(&bmp->data[i]);
//     }

//     free(&bmp->data);
//     free(bmp);
// };

void crop(bmpFILE* bmp, int x, int y, int w_cr, int h_cr){
    BITMAPINFOHEADER* bih = &bmp->bih;
    pixel** data = bmp->data;

    int h = bih->biHeight;
   
    pixel** data_cr = malloc(sizeof(pixel) * h_cr * w_cr);

    for(int i = 0; i < h_cr; i++){        
        data_cr[i] = malloc(sizeof(pixel) * w_cr);
        data_cr[i] = (pixel*)data[h - y - h_cr + i] + x;
    }    

    bih->biHeight = h_cr;
    bih->biWidth = w_cr;
    bmp->data = data_cr;
};

void rotate(bmpFILE* bmp){
    BITMAPINFOHEADER* bih = &bmp->bih;
    pixel** data = bmp->data;

    int h = bih->biHeight;
    int w = bih->biWidth;

    bih->biHeight = w;
    bih->biWidth = h;

    int h_r = bih->biHeight;
    int w_r = bih->biWidth;
    
    pixel** data_r = malloc(sizeof(pixel) * h_r * w_r);
    
    for(int i = 0; i < h_r; i++)
        data_r[i] = malloc(sizeof(pixel) * w_r);
    
    for(int i = 0; i < h_r; i++){
        for (int j = 0; j < w_r; j++){
            data_r[i][j] = data[j][w - 1 - i];
        }
    }
    
    bmp->data = data_r;
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

    fclose(fp);
};
