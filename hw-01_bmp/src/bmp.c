#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

void load_bmp(char* filename, bmpFILE* work_bmp){
    FILE* bmp = fopen(filename, "rb");
    
    // if(!bmp)
    //     return NULL;   
    
    BITMAPFILEHEADER* bfh = &work_bmp->bfh;
    BITMAPINFOHEADER* bih = &work_bmp->bih;

    // if (!bfh || !bih)
    //     return NULL;

    fread(bfh, sizeof(BITMAPFILEHEADER), 1, bmp);
    fread(bih, sizeof(BITMAPINFOHEADER), 1, bmp);

    int h = bih->biHeight;
    int w = bih->biWidth;
    
    int padding = (4 - ((w * sizeof(pixel)) % 4)) % 4;

    work_bmp->data = malloc(sizeof(pixel*) * h);
    pixel* pixels_massive = malloc(sizeof(pixel) * w * h);
    for (int i = 0; i < h; i++) {
        work_bmp->data[i] = pixels_massive + i * w;
    }

    // pixel** data = malloc(sizeof(pixel*) * h);

    for(int i = 0; i < h; i++){
        // data[i] = malloc(sizeof(pixel) * w);
        fread(work_bmp->data[i], sizeof(pixel), w, bmp);
        fseek(bmp, padding, SEEK_CUR);
    }

    fclose(bmp);

    // bmpFILE* bmpfile = malloc(bfh->bfSize);

    // if(!bmpfile)
    //     return NULL;

    work_bmp->bfh = *bfh;
    work_bmp->bih = *bih;
    //work_bmp->data = data;

    // return bmpfile;
};

void free_data(bmpFILE* bmp){
    // for(int i=0; i < rows; i++)
    //     free(data[i]);
    for(DWORD i =0; i<bmp->bih.biHeight; i++)
        free(bmp->data[i]);
    free(bmp->data);
};

// void free_bmp(bmpFILE* bmp){
//     free(&bmp->bfh);
//     free(&bmp->bih);
//     free_data(bmp->data, bmp->bih.biHeight);
//     free(bmp);
// };

void crop(bmpFILE* bmp, bmpFILE* bmp_cr, int x, int y, int w_cr, int h_cr){
    BITMAPINFOHEADER* bmp_bih = &bmp->bih;
    pixel** data = bmp->data;

    int h = bmp_bih->biHeight;
   
    pixel** data_cr = malloc(sizeof(pixel*) * h_cr);
    pixel* pixels_massive = malloc(sizeof(pixel) * w_cr * h_cr);
    for (int i = 0; i < h_cr; i++) {
        data_cr[i] = pixels_massive + i * w_cr;
    }


    for(int i = 0; i < h_cr; i++){        
        data_cr[i] = (pixel*)data[h - y - h_cr + i] + x;
    }    

    // for(int i=0; i < h; i++)
    //     free(data[i]);
    //free(data);

    // bih->biHeight = h_cr;
    // bih->biWidth = w_cr;
    
    //bmp->data = data_cr;

    bmp_cr->bfh = bmp->bfh;
    bmp_cr->bih = bmp->bih;
    bmp_cr->bih.biHeight = h_cr;
    bmp_cr->bih.biWidth = w_cr;
    bmp_cr->data = data_cr;
    //free_data(bmp);
};

void rotate(bmpFILE* bmp, bmpFILE* bmp_r){
    BITMAPINFOHEADER* bmp_bih = &bmp->bih;
    pixel** data = bmp->data;

    int h = bmp_bih->biHeight;
    int w = bmp_bih->biWidth;

    bmp_r->bfh = bmp->bfh;
    bmp_r->bih = bmp->bih;
    bmp_r->bih.biHeight = w;
    bmp_r->bih.biWidth = h;

    int h_r = bmp_bih->biHeight;
    int w_r = bmp_bih->biWidth;
    
    pixel** data_r = malloc(sizeof(pixel*) * h_r);
    pixel* pixels_massive = malloc(sizeof(pixel) * w_r * h_r);
    for (int i = 0; i < h_r; i++) {
        data_r[i] = pixels_massive + i * w_r;
    }
    // for(int i = 0; i < h_r; i++)
    //     data_r[i] = malloc(sizeof(pixel) * w_r);
    
    for(int i = 0; i < h_r; i++){
        for (int j = 0; j < w_r; j++){
            data_r[i][j] = data[j][w - 1 - i];
        }
    }

    // for(int i=0; i < h; i++)
    //     free(data[i]);
    // free(data);

    bmp_r->data = data_r;
    //free_data(bmp);
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

    // for(int i=0; i < h; i++)
    //     free(data[i]);
    // free(data);

    fclose(fp);
};
