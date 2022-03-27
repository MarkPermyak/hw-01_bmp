#pragma once

#include "Figure.hpp"

class Scheme {
public:
    Scheme(int capacity); 
    ~Scheme();

    int find_id(int id);
    void push_back_figure(Figure* fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures();
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int x, int y) const; // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y);

private:
    int capacity_;
    int figures_count_;
    Figure** figures_; // размер массива задается в конструкторе и больше не растет
};
