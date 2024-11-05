#include <iostream>

class IntSmartPointer {
private:
    int* ptr; // Raw pointer to manage

public:
    // Constructor
    explicit IntSmartPointer(int* p = nullptr) : ptr(p) {}

    // Destructor
    ~IntSmartPointer() {
        delete ptr; // Free the allocated memory
    }

    // Overload dereference operator
    int& operator*() const {
        return *ptr;
    }

    // Overload arrow operator
    int* operator->() const {
        return ptr;
    }

    // Disable copy constructor and copy assignment operator
    IntSmartPointer(const IntSmartPointer&) = delete;
    IntSmartPointer& operator=(const IntSmartPointer&) = delete;

    // Enable move constructor and move assignment operator
    IntSmartPointer(IntSmartPointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    IntSmartPointer& operator=(IntSmartPointer&& other) noexcept {
        if (this != &other) {
            delete ptr; // Free existing resource
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};

int main() {
    IntSmartPointer smartPtr(new int(42)); // Create smart pointer
    std::cout << "Value: " << *smartPtr << std::endl; // Use smart pointer

    // Move smart pointer
    IntSmartPointer anotherSmartPtr = std::move(smartPtr);
    std::cout << "Moved Value: " << *anotherSmartPtr << std::endl;

    return 0;
}
