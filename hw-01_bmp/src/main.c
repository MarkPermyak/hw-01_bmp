#include "bmp.h"

int main(){
    bmpFILE* test = load_bmp("tests/small-one.bmp");
    
    BITMAPINFOHEADER bih = test->bih;
    BITMAPFILEHEADER bfh = test->bfh;
    pixel** data = test->data;
    
    int h = bih.biHeight;
    int w = bih.biWidth;
    
    
     printf("Type: %d\n", bfh.bfType);
    printf("Size: %d\n", bfh.bfSize);
    printf("Reserved1: %d\n", bfh.bfReserved1);
    printf("Reserved2: %d\n", bfh.bfReserved2);
    printf("OffBits: %d\n", bfh.bfOffBits);
    printf("\n%s\n", "infoheader");
    printf("Size: %d\n", bih.biSize);
    printf("Width: %d\n", bih.biWidth);
    printf("Height: %d\n", bih.biHeight);
    printf("Planes: %d\n", bih.biPlanes);
    printf("BitCount: %d\n", bih.biBitCount);
    printf("Compression: %d\n", bih.biCompression);
    printf("SizeImage: %d\n", bih.biSizeImage);
    printf("XPelsPerMeter: %d\n", bih.biXPelsPerMeter);
    printf("YPelsPerMeter: %d\n", bih.biYPelsPerMeter);
    printf("ClrUsed: %d\n", bih.biClrUsed);
    printf("ClrImportant: %d\n", bih.biClrImportant);

    // for(int i=0; i<h; i++){
    //     for(int j=0; j<w; j++)
    //         printf("(%x %x %x)", data[i][j].blue, data[i][j].green, data[i][j].red);
    //     printf("\n");
    // }
    //free_bmp(test);
    save_bmp("tests/copy.bmp", test);
};