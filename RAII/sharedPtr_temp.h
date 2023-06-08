#pragma once
#include <iostream>

template<class T>
class sharedPtr{
public:
    sharedPtr(): count(new int(1)), ptr(new T){};
    sharedPtr(T* p);
    sharedPtr(const sharedPtr<T>&);
    sharedPtr<T>& operator=(const sharedPtr<T>&);
    sharedPtr(sharedPtr<T>&&);
    sharedPtr<T>& operator=(sharedPtr<T>&&);
    T& operator*();
    T* operator->();
    ~sharedPtr();

private:
    int* count;
    T* ptr;
};

template<typename T, typename... Args>
sharedPtr<T>& make_sharedPtr(Args&&... arg){
    sharedPtr<T> sp = sharedPtr<T>(new T(std::forward<Args>(arg)...));
    return sp;
}

template<typename T>
sharedPtr<T>::sharedPtr(T* p): count(new int(1)){
    ptr = p;
}

template<typename T>
sharedPtr<T>::sharedPtr(const sharedPtr<T>& other){
    count = other.count;
    ptr = other.ptr;
    (*count)++;
}

template<typename T>
sharedPtr<T>::sharedPtr(sharedPtr<T>&& other){
    count = other.count;
    ptr = other.ptr;
    other.count = nullptr;;
    other.ptr = nullptr;
}

template<typename T>
sharedPtr<T>& sharedPtr<T>::operator=(const sharedPtr<T>& other){
    if(&other == this) return *this;
    ++(*(other.count));
    if(count != nullptr && --(*count) == 0){
        delete count;
        delete ptr;
    }
    count = other.count;
    ptr = other.ptr;
    (*count)++;
    return *this;
}

template<typename T>
sharedPtr<T>& sharedPtr<T>::operator=(sharedPtr<T>&& other){
    if(&other == this) return *this;
    if(count != nullptr && --(*count) == 0){
        delete count;
        delete ptr;
    }
    count = other.count;
    ptr = other.ptr;
    other.count = nullptr;
    ptr.count = nullptr;
    return *this;
}

template<typename T>
T& sharedPtr<T>::operator*(){
    return *ptr;
}

template<typename T>
T* sharedPtr<T>::operator->(){
    return ptr;
}

template<typename T>
sharedPtr<T>::~sharedPtr(){
    if(count == nullptr)
        return;
    if(--(*count) == 0){
        if(count)
            delete count;
        if(ptr)
            delete ptr;
        count = nullptr;
        ptr = nullptr;
    }
}