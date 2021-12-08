#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clist.h"

#define LINESIZE 239


// /* ? */ add_point(intrusive_list *l, int x, int y) {
//     point A;
    
// }

// /* ? */ remove_point(intrusive_list /* ? */, int x, int y) { // removes all (x, y) pairs

// }


int main() {

  intrusive_list_t my_list;
  init_list(&my_list);

  while (1)
  {
    char input[LINESIZE] = "";
    fgets(input, LINESIZE, stdin);
    input[strlen(input) - 1] = '\0';
    

    if(input[0] == 'a' && input[1] == 'd' && input[2] == 'd' && input[3] == ' '){
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
     
      add_node(&my_list, alloc_point(x, y));  
    }
    else{
      if(!strcmp(input, "rma")){
        remove_all_points(&my_list);
      }
      else{
        if(!strcmp(input, "print")){
          show_all_points(my_list);
        }

        else{  
          if(!strcmp(input, "len"))
            printf("%d\n", get_length(&my_list));
          else{
            if(!strcmp(input, "exit")){
              break;
            }
            else{
              if (input[0] == 'r' && input[1] == 'm' && input[2] == ' '){
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
                remove_point(&my_list, alloc_point(x, y));
              }
              else
                printf("%s\n", "Unknown command");
            }
          }
        }  
      }
    }
    fflush (stdout);
  }
  return 0;

}
