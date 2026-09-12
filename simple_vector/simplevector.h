// Simple vector

#ifndef SIMPLEVECTOR_HPP
#define SIMPLEVECTOR_HPP

#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>


namespace ss {

template <typename T>
class Vector {
private:
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
    T* arr_ = nullptr;

    void InnerResize(std::size_t new_capacity);

public:
    explicit Vector(std::size_t capacity = 1);
    ~Vector() noexcept;

    // Copy
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    // Move
    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    // Element operations
    void PushBack(const T& value);

    void Set(
        std::size_t i,
        const T& value
    );

    T& Get(std::size_t i);

    const T& Get(std::size_t i) const;

    // Subscript operator
    T& operator[](std::size_t i);

    const T& operator[](std::size_t i) const;

    // Information
    [[nodiscard]]
    std::size_t GetSize() const noexcept {
        return size_;
    }

    [[nodiscard]]
    std::size_t GetCapacity() const noexcept {
        return capacity_;
    }

    // Increase logical size
    void AddSize(std::size_t i);

    // Remove all elements
    void Clear() noexcept;
};


// ============================================================
// Constructor
// ============================================================

template <typename T>
Vector<T>::Vector(std::size_t capacity)
    : size_(0),
      capacity_(capacity == 0 ? 1 : capacity),
      arr_(new T[capacity_]) {
}


// ============================================================
// Destructor
// ============================================================

template <typename T>
Vector<T>::~Vector() noexcept {
    delete[] arr_;
}


// ============================================================
// Copy Constructor
// ============================================================

template <typename T>
Vector<T>::Vector(const Vector& other)
    : size_(other.size_),
      capacity_(other.capacity_),
      arr_(new T[other.capacity_]) {

    for (std::size_t i = 0; i < size_; ++i) {
        arr_[i] = other.arr_[i];
    }
}


// ============================================================
// Copy Assignment
// ============================================================

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    T* new_arr = new T[other.capacity_];

    try {
        for (std::size_t i = 0; i < other.size_; ++i) {
            new_arr[i] = other.arr_[i];
        }
    }
    catch (...) {
        delete[] new_arr;
        throw;
    }

    delete[] arr_;

    arr_ = new_arr;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}


// ============================================================
// Move Constructor
// ============================================================

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : size_(other.size_),
      capacity_(other.capacity_),
      arr_(other.arr_) {

    other.size_ = 0;
    other.capacity_ = 0;
    other.arr_ = nullptr;
}


// ============================================================
// Move Assignment
// ============================================================

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] arr_;

    arr_ = other.arr_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}


// ============================================================
// Internal Resize
// ============================================================

template <typename T>
void Vector<T>::InnerResize(
    std::size_t new_capacity
) {
    if (new_capacity < size_) {
        throw std::length_error(
            "Vector: new capacity is smaller than size"
        );
    }

    if (new_capacity == 0) {
        new_capacity = 1;
    }

    T* new_arr = new T[new_capacity];

    try {
        for (std::size_t i = 0; i < size_; ++i) {
            new_arr[i] = arr_[i];
        }
    }
    catch (...) {
        delete[] new_arr;
        throw;
    }

    delete[] arr_;

    arr_ = new_arr;
    capacity_ = new_capacity;
}


// ============================================================
// PushBack
// ============================================================

template <typename T>
void Vector<T>::PushBack(const T& value) {

    if (size_ == capacity_) {

        if (
            capacity_ >
            std::numeric_limits<std::size_t>::max() / 2
        ) {
            throw std::length_error(
                "Vector: capacity overflow"
            );
        }

        InnerResize(capacity_ * 2);
    }

    arr_[size_] = value;
    ++size_;
}


// ============================================================
// Set
// ============================================================

template <typename T>
void Vector<T>::Set(
    std::size_t i,
    const T& value
) {
    if (i >= size_) {
        throw std::out_of_range(
            "Vector::Set: index out of range"
        );
    }

    arr_[i] = value;
}


// ============================================================
// Get
// ============================================================

template <typename T>
T& Vector<T>::Get(std::size_t i) {
    if (i >= size_) {
        throw std::out_of_range(
            "Vector::Get: index out of range"
        );
    }

    return arr_[i];
}


template <typename T>
const T& Vector<T>::Get(
    std::size_t i
) const {
    if (i >= size_) {
        throw std::out_of_range(
            "Vector::Get: index out of range"
        );
    }

    return arr_[i];
}


// ============================================================
// operator[]
// ============================================================

template <typename T>
T& Vector<T>::operator[](std::size_t i) {
    if (i >= size_) {
        throw std::out_of_range(
            "Vector::operator[]: index out of range"
        );
    }

    return arr_[i];
}


template <typename T>
const T& Vector<T>::operator[](
    std::size_t i
) const {
    if (i >= size_) {
        throw std::out_of_range(
            "Vector::operator[]: index out of range"
        );
    }

    return arr_[i];
}


// ============================================================
// AddSize
// ============================================================

template <typename T>
void Vector<T>::AddSize(std::size_t i) {

    if (i == 0) {
        return;
    }

    if (
        i >
        std::numeric_limits<std::size_t>::max() - size_
    ) {
        throw std::length_error(
            "Vector: size overflow"
        );
    }

    const std::size_t new_size = size_ + i;

    if (new_size > capacity_) {

        std::size_t new_capacity = capacity_;

        while (new_capacity < new_size) {

            if (
                new_capacity >
                std::numeric_limits<std::size_t>::max() / 2
            ) {
                new_capacity = new_size;
                break;
            }

            new_capacity *= 2;
        }

        InnerResize(new_capacity);
    }

    size_ = new_size;
}


// ============================================================
// Clear
// ============================================================

template <typename T>
void Vector<T>::Clear() noexcept {
    size_ = 0;
}

} // namespace ss

#endif // SIMPLEVECTOR_HPP