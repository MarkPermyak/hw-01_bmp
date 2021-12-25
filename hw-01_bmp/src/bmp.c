#include "bmp.h"

bmpFILE* load_bmp(char* filename){
    FILE* bmp = fopen(filename, "rb");

    BITMAPFILEHEADER* bfh = malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER* bih = malloc(sizeof(BITMAPINFOHEADER));

    fread(bfh, 14, 1, bmp);
    fread(bih, 40, 1, bmp);

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

    DWORD h = bih->biHeight;
    DWORD w = bih->biWidth;
    int byte1pxl = bih->biBitCount / 8; 
    int padding = (4 - ((w * byte1pxl) % 4)) % 4;

    int number_of_pxls = h * w;

    pixel** data = malloc(sizeof(pixel) * h * w);

    for(int i = 0; i < h; i++)
        data[i] = malloc(sizeof(pixel) * w);

    //fseek(bmp, bfh->bfOffBits, SEEK_SET);
    for(int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            fread(&data[i][j].blue, 1, 1, bmp);
            fread(&data[i][j].green, 1, 1, bmp);
            fread(&data[i][j].red, 1, 1, bmp);
        }
        
        fseek(bmp, padding, SEEK_CUR);
    }

    // for(int i=0; i<h; i++){
    //     for(int j=0; j<w; j++)
    //         printf("(%x %x %x)", data[i][j].blue, data[i][j].green, data[i][j].red);
    //     printf("\n");
    // }

    fclose(bmp);

    bmpFILE* bmpfile = malloc(bfh->bfSize);
    bmpfile->bfh = *bfh;
    bmpfile->bih = *bih;
    bmpfile->data = data;

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

void rotate(bmpFILE* bmp){
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
            data_r[i][j].blue = data[j][w - 1 - i].blue;
            data_r[i][j].green = data[j][w - 1 - i].green;
            data_r[i][j].red = data[j][w - 1 - i].red;
        }
    }

    bmp->data = data_r;
};

void save_bmp(char* filename, bmpFILE* bmp){
    FILE* fp = fopen(filename, "wb");

    BITMAPFILEHEADER* bfh = &bmp->bfh;
    BITMAPINFOHEADER* bih = &bmp->bih;
    
    fwrite(bfh, 14, 1 , fp);
    fwrite(bih, 40, 1, fp);
    int w = bih->biWidth;
    int h = bih->biHeight;
    int byte1pxl = bih->biBitCount / 8;
    int padding = (4 - ((byte1pxl * w) % 4)) % 4;
    
   
    pixel** data = bmp->data;
    
    char* padding_str[padding];
    for(int i=0; i<padding; i++)
        padding_str[i] = 0b00000000;

    
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            fwrite(&data[i][j].blue, 1, 1, fp);
            fwrite(&data[i][j].green, 1, 1, fp);
            fwrite(&data[i][j].red, 1, 1, fp);
        }
        fwrite(padding_str, 1, padding, fp);
    }

    fclose(fp);
};