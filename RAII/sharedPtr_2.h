#include <iostream>

template <class T>
class smartptr
{
public:
    smartptr<T>(T* ptr);
    ~smartptr<T>();
    smartptr<T>(const smartptr<T>& rhs);
    smartptr<T>& operator=(const smartptr<T>& rhs);
    T* operator->();
    T& operator*();
private:
    int *use_count;
    T* ptr;
};

template<class T>
smartptr<T>::smartptr(T* p): use_count(nullptr), ptr(p){
    use_count = new int(1);
}

template<class T>
smartptr<T>::~smartptr(){
    --(*use_count);
    if(*use_count == 0){
        delete ptr;
        delete use_count;
        ptr = nullptr;
        use_count = nullptr;
    }
}

template<class T>
smartptr<T>::smartptr(const smartptr<T>& rhs){
    ptr = rhs.ptr;
    use_count = rhs.use_count;
    ++(*use_count);
}

template<class T>
smartptr<T>& smartptr<T>::operator=(const smartptr<T>& rhs){
    ++(*rhs.use_count);
    if(--(*use_count) == 0){
        delete use_count;
        delete ptr;
    }
    use_count = rhs.use_count;
    ptr = rhs.ptr;
    return *this;
}

template<class T>
T* smartptr<T>::operator->(){
    return ptr; 
}

template<class T>
T& smartptr<T>::operator*(){
    return *ptr;
}