/*
 * @Author: zxczhuao
 * @Date: 2023-06-10 11:34:30
 * @LastEditTime: 2023-06-10 16:13:02
 * @FilePath: /CppCode/RAII/unique_ptr_1.cpp
 * @Description: 
 * 
 */
#include <memory>
#include <iostream>
using namespace std;

template<class _Tp, class Deleter = std::default_delete<_Tp>>
class MyUnique_Ptr{
public:
    MyUnique_Ptr(_Tp* ptr = nullptr, Deleter deleter = Deleter()) noexcept:
        _ptr(ptr), _deleter(deleter){}
    MyUnique_Ptr(MyUnique_Ptr&& _u) noexcept : _ptr(_u.release()), _deleter(std::move(_u._deleter)){}
    // 移动语义
    MyUnique_Ptr& operator=(MyUnique_Ptr&& _u) noexcept{
        if(_u == this)  return *this;
        _deleter(_ptr);
        _ptr = _u.release();
        _deleter = std::move(_u._deleter);
        return *this;
    }

    // 析构
    ~MyUnique_Ptr() noexcept{
        if(_ptr)
            _deleter(_ptr);
        _ptr = nullptr;
    }
    // 禁止拷贝
    MyUnique_Ptr(const MyUnique_Ptr&) = delete;
    MyUnique_Ptr& operator=(const MyUnique_Ptr&) = delete;
    //
    MyUnique_Ptr& operator=(nullptr_t) noexcept{
        if(_ptr)    
            _deleter(_ptr);
        _ptr = nullptr;
        return *this;
    }
    _Tp& operator*(){
        return *_ptr;
    }
    // 接口
    _Tp* get() const{
        return _ptr;
    }
    // 释放对象或者重置对象
    void reset(){
        if(_ptr)
            _deleter(_ptr);
       _ptr = nullptr; 
    }
    void reset(_Tp* ptr){
        if(_ptr)
            _deleter(_ptr);
        _ptr = ptr; 
    }
    // 放弃对指针的控制权，并返回裸指针
    _Tp* release(){
        _Tp* ptr = _ptr;
        _ptr = nullptr;
        return ptr;
    }
    
private:
    _Tp* _ptr;
    Deleter _deleter;
};

int main(){
    auto deleter = [](const int* ptr){
        cout<<"My Deleter worked;"<<endl;
        delete ptr;
    };
    MyUnique_Ptr<int, decltype(deleter)> p1(new int(20), deleter);
    MyUnique_Ptr<int, decltype(deleter)> ptr3(std::move(p1));
    cout<<*ptr3<<endl;
    return 0;
}