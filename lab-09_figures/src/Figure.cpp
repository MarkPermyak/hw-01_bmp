#include "Figure.hpp"

Figure::Figure(int _id, int _x, int _y){
    id = _id;
    x = _x;
    y = _y;
}
Figure::~Figure(){}
void Figure::print(){}
void Figure::zoom(int x){}
bool Figure::is_inside(int x, int y){return 0;}

int Figure::get_id(){ return id;}
int Figure::get_x(){ return x;}
int Figure::get_y(){ return y;}
void Figure::move(int new_x, int new_y){
    x = new_x;
    y = new_y;
}
