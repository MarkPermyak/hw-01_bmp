#include <stdio.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"

#define MAXSIZE 20

int main(int argc, char** argv){
    if (!strcmp(argv[1], "loadtext")){
        
        char *filename = argv[2];

        FILE *fp = fopen(filename, "r");
        char buffer[MAXSIZE];

        if (!strcmp(argv[3], "savetext")){
            char *save_filename = argv[4];
            FILE *savef = fopen(save_filename, "w");

            while (fgets(buffer, MAXSIZE, fp))
                fprintf(savef, "%s", buffer);
            
            fclose(fp);    
            fclose(savef);

            // savef = fopen(save_filename, "r");

            // while (fgets(buffer, MAXSIZE, savef))
            //     printf("%s", buffer);
            // fclose(savef); 
        }

        else if (!strcmp(argv[3], "count")){
            int count = 0;
            while (fgets(buffer, MAXSIZE, fp))
                count++;
            printf("%d\n", count);    
        }
    }

    return 0;
}
