#ifndef POINT_LIST_H__
#define POINT_LIST_H__

#include "clist.h"

struct point {
    int x;
    int y;
    intrusive_node_t node;
};

typedef struct point point_t;

point_t* get_point(intrusive_node_t*);
void add_point(intrusive_list_t*, int, int);
void remove_point(intrusive_list_t*, int, int);
void remove_all_points(intrusive_list_t*);
void show_all_points(intrusive_list_t*);

#endif
