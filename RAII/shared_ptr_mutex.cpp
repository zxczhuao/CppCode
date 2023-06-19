#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

template<class T>
class My_Shared_Ptr{
public:
    My_Shared_Ptr(): _ptr(nullptr), _count(nullptr), _mtx(new mutex){}
    My_Shared_Ptr(T* ptr): _ptr(ptr), _count(new int(1)), _mtx(new mutex){}
    ~My_Shared_Ptr(){
        release();
    }
    void release(){
        {
            uniuqe_lock<mutex> m(*_mtx);
            if(--(*_count) == 0){
                delete _ptr;
                delete _count;
                _ptr = nullptr;
                _count = nullptr;
            }
        }
        if(_count == nullptr && _mtx){
            delete _mtx; 
            _mtx = nullptr;
        }
    }    

    My_Shared_Ptr(const My_Shared_Ptr& other):_ptr(other._ptr), _count(other._ptr), _mtx(other._mtx){
        unique_lock<mutex> m(*other._mtx);
        _ptr = other._ptr;
        _count = other._count;
        _mtx = other._mtx;
        ++(*count);
    }

    My_Shared_Ptr& operator=(const My_Shared_Ptr& other){
        if(&other == this)  return *this;
        release();
        unique_lock<mutex> m(*other._mtx); 
        _mtx = other._mtx;
        _ptr = other._count;
        _count = other._count;
        ++(*_count);
        return *this;
    }

    T& operator*(){
        return *_ptr;
    }

    T* operator->(){
        return _ptr;
    }
private:
    T* _ptr;
    size_t* _count;
    mutex* _mtx;
};