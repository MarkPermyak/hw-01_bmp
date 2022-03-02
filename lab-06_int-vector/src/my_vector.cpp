#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "my_vector.hpp"


MyVector::MyVector(){
    _capacity = 2;
    _size = 0;
    _data = new int[_capacity];
}

MyVector::MyVector(size_t init_capacity){
    _capacity = init_capacity;
    _size = 0;
    _data = new int[_capacity];
}

MyVector::MyVector(const MyVector& vector){
    _size = vector._size;
    _capacity = vector._capacity;
    _data = new int[_capacity];
    memcpy(_data, vector._data, sizeof(int)*_size);
}

MyVector::~MyVector(){
    delete[] _data;
}

void MyVector::set(size_t i, int value){
    _data[i] = value;
}

int MyVector::get(size_t i){
    return _data[i];
}

size_t MyVector::size(){
    return _size;
}

size_t MyVector::capacity(){
    return _capacity;
}

void MyVector::reserve(size_t new_capacity){
    if (new_capacity > _capacity){
        // int* new_data = new int[new_capacity];

        // for (size_t i = 0; i < _size; i++)
        //     new_data[i] = _data[i];
        
        // delete[] _data;
 
        _data = (int *)realloc(_data, new_capacity * sizeof(int));
        _capacity = new_capacity;
    }
}

void MyVector::resize(size_t new_size){
    if(new_size <= _size)
        for (size_t i = new_size; i < _size; i++)    
            _data[i] = 0;
    
    else{
        //int* new_data = new int[new_size];
        if (new_size > _capacity)
            reserve(std::max(2*_capacity, new_size));

        for (size_t i = _size; i < _capacity; i++)
            _data[i] = 0;
 
    }

    _size = new_size;
}

void MyVector::push_back(int value){
    if(_size >= _capacity){
        reserve(_capacity*2);
    }

    _data[_size] = value;
    _size++;
}

void MyVector::insert(size_t index, int value){
    if(index == _size)
        push_back(value);
    else{
        int tmp = _data[index];
        _data[index] = value;
        for(size_t i = index; i < _size-1 ; i++){
            int tmp2 = _data[i+1];
            _data[i+1] = tmp;
            tmp = tmp2;
        }
        push_back(tmp);
    }
}

void MyVector::erase(size_t index){
    if (index == _size-1)
        _data[index] = 0;
    else{
        for(size_t i = index + 1; i < _size; i++){
            _data[i - 1] = _data[i];
        }
        _data[_size-1] = 0;
    }
    _size--;
}