#include "clist.h"
#include "point_list.h"

#define BYTES_IN_NUMBER 3
#define BITS_IN_BYTE 8

int get_size(FILE* fp){
    long Size;
    fseek (fp, 0 , SEEK_END);
    Size = ftell(fp) ;
    rewind(fp);
    return Size;
};

void add_points_text(intrusive_list_t* l, FILE* fp){
    int x = 0, y = 0;

    while(fscanf(fp, "%d %d", &x, &y) != EOF)
        add_point(l, x, y);
};

void add_points_bin(intrusive_list_t* l, FILE* fp){
    
    int Size = get_size(fp);
    int read_Size = 0;

    while (read_Size != Size){
        unsigned char point[2 * BYTES_IN_NUMBER];

        read_Size += fread(point, sizeof(unsigned char), 2 * BYTES_IN_NUMBER, fp);
        
        int x = 0, y = 0;

        for (int i = 0; i < BYTES_IN_NUMBER; i++){
            int shift = point[i] << i*BITS_IN_BYTE;
            x |= shift;    
        }
        
        for (int i = 3; i < 2 * BYTES_IN_NUMBER; i++){
            int shift = point[i] << (i-3)*BITS_IN_BYTE;
            y |= shift;    
        }
        

        add_point(l, x, y);
        
    }
};

void add_points_from_file(intrusive_list_t* l, FILE* fp, char* file_type){
    if (!strcmp(file_type, "loadtext"))
        add_points_text(l, fp);
    
    else if (!strcmp(file_type, "loadbin"))
        add_points_bin(l, fp);
};

void print_point(intrusive_node_t *node, void* fmt){
    point_t* point = get_point(node);
    printf(fmt, point->x, point->y);
};

void count_point(intrusive_node_t *node, void* p_count){
    *(int*)p_count = *(int*)p_count + 1;
};

void save_point_text(intrusive_node_t *node, void* savef){
    point_t* point = get_point(node);
    fprintf(savef, "%d %d\n", point->x, point->y);
};

void save_point_bin(intrusive_node_t* node, void* savef){
    point_t* point = get_point(node);

    unsigned char bin_point[2*BYTES_IN_NUMBER];
    int x = point->x;
    int y = point->y;
    for (int i = 0; i < BYTES_IN_NUMBER; i++)
        bin_point[i] = (x >> (BITS_IN_BYTE * i)) & ((1 << BITS_IN_BYTE) - 1);
    
    for (int i = 3; i < 2*BYTES_IN_NUMBER; i++)
        bin_point[i] = (y >> (BITS_IN_BYTE * (i-3))) & ((1 << BITS_IN_BYTE) - 1);
    
    fwrite(bin_point, sizeof(bin_point), 1, savef);    
};

int main(int argc, char** argv){
   
    intrusive_list_t my_list;
    init_list(&my_list);    
    
    char* filename = argv[2];
    FILE* fp = fopen(filename, "r");

    char* file_type = argv[1];
    add_points_from_file(&my_list, fp, file_type);
    
    if (!strcmp(argv[3], "savetext")){
        char *save_filename = argv[4];
        FILE *savef = fopen(save_filename, "w");
        
        apply(&my_list, save_point_text, savef);
        
        fclose(savef);
    }

    else if(!strcmp(argv[3], "savebin")){
        fseek(fp, 0, SEEK_SET);

        char* save_filename = argv[4];
        FILE* savef = fopen(save_filename, "w");
        
        apply(&my_list, save_point_bin, savef);
        
        fclose(savef);
    }

    else if (!strcmp(argv[3], "count")){
        int count = 0;
        int* p_count = &count;

        apply(&my_list, count_point, p_count);
        
        printf("%d\n", count);    
    }
    
    else if (!strcmp(argv[3], "print")){
        char* fmt = argv[4];
        
        apply(&my_list, print_point, fmt);
        
        printf("\n");
    }


    fclose(fp);    
    remove_all_points(&my_list);
    return 0;
}
