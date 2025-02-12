#include<bits/stdc++.h>

template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Constructor
    Vector() : data(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Add element
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    // Access element
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Get size
    size_t getSize() const {
        return size;
    }

    // Clear the vector
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }
};

// string class
template <typename T>
class String {
    private:
        Vector<T> data;
    public:
        String() {}
        ~String() {}
};


int main() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (size_t i = 0; i < vec.getSize(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // 创建并使用智能指针
    std::shared_ptr<Vector<int>> vecPtr = std::make_shared<Vector<int>>();
    vecPtr->push_back(1);
    vecPtr->push_back(2);
    vecPtr->push_back(3);
    // 使用智能指针时，不需要手动释放内存

    return 0;
}
