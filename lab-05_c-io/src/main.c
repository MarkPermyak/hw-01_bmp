#include <stdio.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"

#define MAXSIZE 20

void print_point(intrusive_node_t *node, void* fmt){
    point_t* point = get_point(node);
    printf(fmt, point->x, point->y);
};

void count_point(intrusive_node_t *node, int* p_count){
    *p_count = *p_count + 1;
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

            while (fgets(buffer, MAXSIZE, fp))
                fprintf(savef, "%s", buffer);
            
            fclose(savef);

            // savef = fopen(save_filename, "r");

            // while (fgets(buffer, MAXSIZE, savef))
            //     printf("%s", buffer);
            // fclose(savef); 
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

    }

    return 0;
}
