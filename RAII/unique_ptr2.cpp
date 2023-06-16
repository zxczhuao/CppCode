#include <memory>
#include <iostream>
using namespace std;

template<class T, class Deleter = std::default_delete<T>>
class My_Unique_Ptr{
public:
    My_Unique_Ptr(T* _t, Deleter _deleter = Deleter()): t(_t), deleter(_deleter){}
    My_Unique_Ptr(My_Unique_Ptr&& _p) noexcept: t(_p.t), deleter(std::move(_p.deleter)){}
    My_Unique_Ptr& operator=(My_Unique_Ptr&& _p) noexcept {
        if(&_p == this) return *this;
        _deleter(t);
        t = _p.release();
        deleter = std::move(_p.deleter);
        return *this;
    }
    My_Unique_Ptr(const My_Unique_Ptr&) = delete;
    My_Unique_Ptr& operator=(const My_Unique_Ptr&) = delete;
    ~My_Unique_Ptr() noexcept{
        if(t)
            deleter(t);
        t = nullptr;
    } 

    T& operator*(){
        return *p;   
    }
    T* operator->(){
        return t;
    }
    T* get() const{
        return t;
    }
    T* release(){
        T* ptr = t;
        t = nullptr;
        return ptr;
    }
    void resest(){
        if(p) deleter(p);
        p = nullptr;
    }
private:
    T* t;
    Deleter deleter;
};