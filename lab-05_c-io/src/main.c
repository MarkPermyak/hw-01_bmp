#include <stdio.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"

#define MAXSIZE 20

void print_point(intrusive_node_t *node, void* fmt){
    point_t* point = get_point(node);
    printf(fmt, point->x, point->y);
};

void count_point(intrusive_node_t *node, void* p_count){
    *(int*)p_count = *(int*)p_count + 1;
};

int main(int argc, char** argv){
    if (!strcmp(argv[1], "loadtext")){
        
        char *filename = argv[2];

        FILE *fp = fopen(filename, "r");
        char buffer[MAXSIZE];

        intrusive_list_t my_list;
        init_list(&my_list);

        int x, y;

        while(fscanf(fp, "%d %d", &x, &y) != EOF)
            add_point(&my_list, x, y);


        if (!strcmp(argv[3], "savetext")){
            char *save_filename = argv[4];
            FILE *savef = fopen(save_filename, "w");

            fseek(fp, 0, SEEK_SET);
            while (fgets(buffer, MAXSIZE, fp))
                fprintf(savef, "%s", buffer);
            
            fclose(savef);

            // savef = fopen(save_filename, "r");

            // while (fgets(buffer, MAXSIZE, savef))
            //     printf("%s", buffer);
            // fclose(savef); 
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

    // if (!strcmp(argv[1], "loadbin")){
    //     char *filename = argv[2];
        
    //     FILE *fp = fopen(filename, "rb");
    //     fseek(fp , 0 , SEEK_END);                          
    //     long lSize = ftell(fp);                           
    //     rewind (fp);     
    //     char * buffer = (char*) malloc(sizeof(char) * lSize);
    //     size_t result = fread(buffer, 1, lSize, fp);
    //     puts(buffer);


        
    //     fclose(fp);
    //     free(buffer);




    //     return 0;
    // }
    
}
