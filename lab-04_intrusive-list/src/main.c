#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clist.h"

#define LINESIZE  50


// /* ? */ add_point(intrusive_list *l, int x, int y) {
//     point A;
    
// }

// /* ? */ remove_point(intrusive_list /* ? */, int x, int y) { // removes all (x, y) pairs

// }

// /* ? */ show_all_points(/* ? */) {

// }

// /* ? */ remove_all_points(/* ? */) {

// }

int main() {

  intrusive_list_t my_list;
  init_list(&my_list);

  while (1)
  {
    char input[LINESIZE] = "";
    fgets(input, LINESIZE, stdin);
    input[strlen(input) - 1] = '\0';
    

    if(input[0] == 'a'){
      char num1[LINESIZE] = "";
      int i = 0;
      while(!isdigit((unsigned char)input[i]) && (input[i] != '-' ))
        i++;
      int j = 0;

      while(input[i] != ' '){
        num1[j] = input[i];
        j++;
        i++;
      }
      //printf("%s\n", "OK");
      int x = atoi(num1);
      char num2[LINESIZE] = "";
      i++;
      int k = 0;
      while(input[i]){
        num2[k] = input[i];
        i++;
        k++;
      }
      int y = atoi(num2);
      // printf("%s\n", "OK");
      // printf("%d\n", x);
      // printf("%d\n", y);
      
      //scanf("%d", &x);
      add_node(&my_list, alloc_point(x, y));  
      //printf("%s\n", "add");
    }
    else{
      if(!strcmp(input, "rma")){
        destroy(&my_list);
        //printf("%s\n", "rma");
      }
      else{
        if(!strcmp(input, "print")){
          apply(&my_list, print_point);
          printf("\n");
          //printf("%s\n", "print");
        }

        else{  
          if(!strcmp(input, "len"))
            printf("%d\n", get_length(my_list));
          else{
            if(!strcmp(input, "exit")){
              break;
            }
          }
        }  
      }
    }
    fflush (stdout);
  }
  return 0;

}
