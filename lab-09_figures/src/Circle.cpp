#include "Circle.hpp"
#include <cmath>

Circle::Circle(int id, int x, int y, int radius, const char* label) : 
    Figure(id, x, y), radius_(radius) {
        label_ = new char[strlen(label) + 1];
        strcpy(label_, label);
    }

Circle::~Circle(){
    delete[] label_;
}

void Circle::print() const{
    std::cout <<"Circle " << id <<": x = " << x <<" y = "<< y << " radius = " 
    << radius_ << " label = " << label_ << '\n';
}

bool Circle::is_inside(int other_x, int other_y) const{
    return ((pow(other_x - x, 2.0) + pow(other_y - y, 2.0) <= pow(radius_, 2.0)));
}

void Circle::zoom(int factor){
    radius_*=factor;
}

