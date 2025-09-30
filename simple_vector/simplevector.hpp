/* ********** */
/* Purpose: Simple Vector Header-Lib
/* Author:  Mark 'EUL' Fours
/* ********** */

#ifndef SIMPLEVECTOR_HPP
#define SIMPLEVECTOR_HPP
#ifdef _WIN32
#pragma once
#endif

#include <stdexcept>  // for exceptions

namespace ss {

template <typename T>
class Vector
{
private:
    size_t size_;      // number of elements in use
    size_t capacity_;  // allocated array size
    T* arr;

    void InnerResize(size_t new_capacity);

public:
    Vector(size_t capacity = 1);
    ~Vector();

    void PushBack(const T& value);
    void Set(size_t i, const T& value);
    T Get(size_t i) const;

    size_t GetSize() const { return size_; }
    size_t GetCapacity() const { return capacity_; }
    void AddSize(size_t i);
};

// constructor
template <typename T>
Vector<T>::Vector(size_t capacity) : size_(0), capacity_(capacity ? capacity : 1) {
    arr = new T[capacity_];
}

// destructor
template <typename T>
Vector<T>::~Vector() {
    delete[] arr;
}

// resize (private)
template <typename T>
void Vector<T>::InnerResize(size_t new_capacity) {
    if (new_capacity < 1) new_capacity = 1;

    T* newArr = new T[new_capacity];
    for (size_t i = 0; i < size_; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    capacity_ = new_capacity;
}

// push back
template <typename T>
void Vector<T>::PushBack(const T& value) {
    if (size_ == capacity_) {
        InnerResize(capacity_ * 2);
    }
    arr[size_++] = value;
}

// set
template <typename T>
void Vector<T>::Set(size_t i, const T& value) {
    if (i >= size_) throw std::out_of_range("Index out of range");
    arr[i] = value;
}

// get
template <typename T>
T Vector<T>::Get(size_t i) const {
    if (i >= size_) throw std::out_of_range("Index out of range");
    return arr[i];
}

// add size
template <typename T>
void Vector<T>::AddSize(size_t i) {
    if (size_ + i > capacity_) {
        InnerResize(size_ + i);  // ensure enough memory
    }
    size_ += i;  // grow logical size
}

} // namespace ss

#endif // SIMPLEVECTOR_HPP
