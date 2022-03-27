#pragma once
#include <iostream>
#include <cstring>

class Figure {
public:
    Figure(int id, int x, int y);
    virtual ~Figure();

    int get_id();
    int get_x();
    int get_y();
    virtual void print();
    virtual bool is_inside(int x, int y);
    virtual void zoom(int factor);
    void move(int new_x, int new_y);

    // ...

protected:
    int id;
    int x;
    int y;
};
