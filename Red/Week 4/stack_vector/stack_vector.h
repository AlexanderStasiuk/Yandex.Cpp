#pragma once
#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) : current_size(a_size) {
        if (current_size > N) {
            throw invalid_argument("Try less");
        }
    }

    T& operator[](size_t index) {
        return data[index];
    }
    const T& operator[](size_t index) const {
        return data[index];
    }

    typename array< T, N>::iterator begin() {
        return data.begin();
    }
    typename array< T, N>::iterator end() {
        return data.begin() + current_size;
    }
    const typename array< T, N>::const_iterator begin() const {
        return data.begin();
    }
    const typename array< T, N>::const_iterator end() const {
        return data.begin() + current_size;
    }

    size_t Size() const {
        return current_size;
    }
    size_t Capacity() const {
        return N;
    }

    void PushBack(const T& value) {
        if (current_size >= N) {
            throw overflow_error("Can't push. Hasn't space");
        } else {
            data[current_size] = value;
            current_size++;
        }
    }
    T PopBack() {
        if (current_size == 0) {
            throw underflow_error("Can't pop. Hasn't elements");
        } else {
            current_size--;
            return data[current_size];   
        }
    }

private:
    array<T, N> data;
    size_t current_size = 0;
};

