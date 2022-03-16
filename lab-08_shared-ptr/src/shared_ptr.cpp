#include <iostream>
#include "shared_ptr.hpp"

shared_ptr::Storage::Storage(Matrix* mtx){
    data_ = mtx;
    ref_count_ = 1;
}

int shared_ptr::Storage::getCounter() const {return ref_count_;}
Matrix* shared_ptr::Storage::getObject() const {return data_;}

shared_ptr::Storage::~Storage(){
    delete data_;
}

shared_ptr::shared_ptr(Matrix* obj){
    // if(obj != nullptr)
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other){
    storage_ = other.storage_;
    storage_->ref_count_++;
}

shared_ptr::~shared_ptr(){
    storage_->ref_count_--;
    // if (storage_->ref_count_ == 0){
    //     delete storage_->data_;
    //     delete storage_;
    // }
}

Matrix* shared_ptr::ptr() const {
    return storage_->data_;
}

bool shared_ptr::isNull() const {
    return (storage_->data_ == nullptr);
}

shared_ptr& shared_ptr::operator=(shared_ptr other){
    storage_ = other.storage_;
    storage_->ref_count_++;

    return *this;
}

Matrix& shared_ptr::operator*() const {return *storage_->data_;}

Matrix* shared_ptr::operator->() const {return storage_->data_;}

void shared_ptr::reset(Matrix* obj){ *this = shared_ptr(obj);}