#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char** argv){

    if(argc != 8){
        printf("Wrong number of arguments\n");
        return 1;
    }

    if(strcmp(argv[1], "crop-rotate")){
        printf("Wrong operation\n");
        return 1;
    }

    char* in_bmp = argv[2];
    char* out_bmp = argv[3];
    int x = atoi(argv[4]);
    int y = atoi(argv[5]);
    int w = atoi(argv[6]);
    int h = atoi(argv[7]);

    if(w <= 0 || h <= 0){
        printf("Invalid size of rectangle\n");
        return 1;
    }

    bmpFILE bmp;

    if(load_bmp(in_bmp, &bmp))
        return 1;
    

    int width = bmp.bih.biWidth;
    int height = bmp.bih.biHeight;

    if(x >= width || y >= height || x < 0 || y < 0){
        free_data(&bmp);
        printf("Point is out of bounds\n");
        return 1;
    }
    
    if(x + w > width || y + h > height){
        free_data(&bmp);
        printf("Rectangle is out of bounds\n");
        return 1;
    }

    
    if(crop(&bmp, x, y, w, h))
        return 1;
    
    if(rotate(&bmp))
        return 1;
   
    save_bmp(out_bmp, &bmp);
  
    return 0;
};
