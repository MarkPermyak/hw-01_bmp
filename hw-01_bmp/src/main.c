#include "bmp.h"

int main(){
    bmpFILE test = load_bmp("tests/small-one.bmp");
    printf("Size: %d\n", test.bih.biSize);
    printf("Width: %d\n", test.bih.biWidth);
    printf("Height: %d\n", test.bih.biHeight);
    printf("Planes: %d\n", test.bih.biPlanes);
    printf("BitCount: %d\n", test.bih.biBitCount);
};