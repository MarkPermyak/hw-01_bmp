#include "Figure.hpp"

Figure::Figure(int _id, int _x, int _y){
    id = _id;
    x = _x;
    y = _y;
}
Figure::~Figure(){}

int Figure::get_id() const { return id;}

void Figure::move(int new_x, int new_y){
    x = new_x;
    y = new_y;
}
