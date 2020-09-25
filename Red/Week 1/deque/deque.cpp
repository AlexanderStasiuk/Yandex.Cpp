#include <iostream>
#include <vector>

using namespace std;

template<typename T> 
class Deque {
private:
    vector<T> deq1;
    vector<T> deq2;

    const T& getElement(size_t idx) const {
        if (idx >= deq1.size()) {
            return deq2[idx-deq1.size()];
        }
        return deq1[deq1.size() - idx - 1];
    }

    T& getElement(size_t idx) {
        if (idx >= deq1.size()) {
            return deq2[idx-deq1.size()];
        }
        return deq1[deq1.size() - idx - 1];
    }
public:
    Deque () {};

    const bool Empty() const { return (deq1.size() + deq2.size()) == 0;};
    const int Size() const { return (deq1.size() + deq2.size());};

    void PushFront(const T& element) {
        deq1.push_back(element);
    }
    void PushBack(const T& element) {
        deq2.push_back(element);
    }

    const T& operator [] (size_t idx) const {
        return getElement(idx);
    }

    T& operator [] (size_t idx) {
        return getElement(idx);
    }

    const T& At(size_t index) const {
        if (index >= Size()) {
            throw out_of_range("Index out");
        }
        return getElement(index);
    }

    T& At(size_t index) {
        if (index >= Size()) {
            throw out_of_range("Index out");
        }
        return getElement(index);
    }

    T& Front() {
        return At(0);
    }

    const T& Front() const {
        return At(0);
    }

    T& Back() {
        return At(Size()-1);
    }

    const T& Back() const {
        return At(Size()-1);
    }

};

int main() {
    
    Deque<int> d;

    d.PushBack(1);

    cout << d.At(0);
    cout << d.Front();
    cout << d.Back();
    // cout << d.At(2);

    return 0;
}