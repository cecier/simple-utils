/* ********** */
/* Purpose: Simple Vector Header-Lib
/* Author:  Mark 'EUL' Fours
/* ********** */


#ifndef SIMPLEVECTOR_HPP
#define SIMPLEVECTOR_HPP
#ifdef _WIN32
#pragma once
#endif


// @todo vector's logic here
namespace ss {


// @todo
// resizing
// ===

template <typename T>
class Vector
{
private:
    size_t data_size_;
    T* arr;

public:
    Vector(size_t = 1);
    ~Vector();

    // @todo 
    // size check and further resizing
    // ===
    void Set(size_t i, T value) { arr[i] = value; }
    
    T Get(size_t i) const { return arr[i]; }
};


template <typename T>
Vector<T>::Vector(size_t size) : data_size_(size) {
    arr = new T[data_size_];
}

template <typename T>
Vector<T>::~Vector() { 
    delete[] arr;
}





} // namespace ss

#endif // SIMPLEVECTOR_HPP