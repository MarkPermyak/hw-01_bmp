#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "clist.h"
#include "point_list.h"

#define MAXSIZE 20
#define BYTES_IN_NUMBER 3
#define BITS_IN_BYTE 8

static void bin_to_int(unsigned char * data, int * result) {
	*result = 0;
	for (size_t position = 0; position < BYTES_IN_NUMBER; position++) {
		*result |= data[position] << (position * BITS_IN_BYTE);
	}
}

bool read_point_bin(FILE * infile, int * x, int * y) {
	unsigned char input[2 * BYTES_IN_NUMBER];
	if (fread(input, sizeof(unsigned char), 2 * BYTES_IN_NUMBER, infile) != 2 * BYTES_IN_NUMBER) {
		return false;
	}
	bin_to_int(input, x);
	bin_to_int(&input[BYTES_IN_NUMBER], y);
	return true;
}

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

int main(int argc, char** argv){
   
    intrusive_list_t my_list;
    init_list(&my_list);    
    char *filename = argv[2];
    
    if (!strcmp(argv[1], "loadtext")){
        

        FILE *fp = fopen(filename, "r");
        

       

        int x, y;

        while(fscanf(fp, "%d %d", &x, &y) != EOF)
            add_point(&my_list, x, y);


        if (!strcmp(argv[3], "savetext")){
            char *save_filename = argv[4];
            FILE *savef = fopen(save_filename, "w");
            char buffer[MAXSIZE];
            fseek(fp, 0, SEEK_SET);
            while (fgets(buffer, MAXSIZE, fp))
                fprintf(savef, "%s", buffer);
            
            fclose(savef);
        }

        else if(!strcmp(argv[3], "savebin")){
            fseek(fp, 0, SEEK_SET);

            char *save_filename = argv[4];

            FILE *savef = fopen(save_filename, "wb");

            int x;
            
            while (!feof(fp)){
                fscanf(fp, "%d", &x);
                // int* pair[2];
                // pair[0] = &x;
                // pair[1] = &y;
                x >> 8;
                x << 8;
                fwrite(&x, 3, 1, savef);
            }
            
            
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

    if (!strcmp(argv[1], "loadbin")){
        
        FILE *fp = fopen(filename, "rb");
        long Size;
        fseek (fp, 0 , SEEK_END);
        Size = ftell(fp) ;
        rewind(fp);

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
            

            add_point(&my_list, x, y);
            
        }
     
        if (!strcmp(argv[3], "savetext")){
            char *save_filename = argv[4];
            FILE *savef = fopen(save_filename, "w");
            apply(&my_list, save_point_text, savef);
            fclose(savef);
        }

        else if(!strcmp(argv[3], "savebin")){
            char *save_filename = argv[4];
            FILE *savef = fopen(save_filename, "wb");
            char buffer[Size];
            fseek(fp, 0, SEEK_SET);
            
            fread(buffer, sizeof(unsigned char), Size, fp);
            fwrite(buffer, sizeof(buffer), 1, savef);

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
        //show_all_points(&my_list);

        return 0;
    }
    
}
