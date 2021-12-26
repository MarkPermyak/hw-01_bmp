#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char** argv){

    if(argc != 7){
        printf("Wrong number of arguments\n");
        return 1;
    }

    char* in_bmp = argv[1];
    char* out_bmp = argv[2];
    int x = atoi(argv[3]);
    int y = atoi(argv[4]);
    int w = atoi(argv[5]);
    int h = atoi(argv[6]);

    if(w <= 0 || h <= 0){
        printf("Invalid size of rectangle\n");
        return 1;
    }

    bmpFILE* bmp = load_bmp(in_bmp);

    if(!bmp){
        printf("Input image doesn't exists\n");
        return 1;
    }

    int width = bmp->bih.biWidth;
    int height = bmp->bih.biHeight;

    if(x >= width || y >= height || x < 0 || y < 0){
        printf("Point is out of bounds\n");
        return 1;
    }
    
    if(x + w > width || y + h > height){
        printf("Rectangle is out of bounds\n");
        return 1;
    }

    bmpFILE* bmp_cropped = crop(bmp, x, y, w, h);
    bmpFILE* bmp_croppedrotated = rotate(bmp_cropped);

    save_bmp(out_bmp, bmp_croppedrotated);
    
    return 0;
};