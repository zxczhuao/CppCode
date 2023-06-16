#include <memory>
#include <iostream>
using namespace std;

template <class T>
class My_Shared_Ptr{
public:
    My_Shared_Ptr() : ptr(nullptr), count(nullptr){}
    My_Shared_Ptr(T* _ptr) : ptr(_ptr), count(new size_t(1)){}
    My_Shared_Ptr(const My_Shared_Ptr& p) {
        ptr = p.ptr;
        count = p.count;
        ++(*count);
    }
    My_Shared_Ptr(My_Shared_Ptr&& p) noexcept {
        ptr = p.ptr;
        count = p.count;
        p.ptr = nullptr;
        p.count = nullptr;
    }
    ~My_Shared_Ptr(){
        release();
    }
    void release(){
        if(count){
            --(*count);
            if(*count == 0){
                delete ptr;
                delete count;
            }
        }
        ptr = nullptr;
        count = nullptr;
    }
    My_Shared_Ptr& operator=(const My_Shared_Ptr& p){
        if(&p == this)
            return *this;
        release();
        ptr = p.ptr;
        count = p.count;
        ++(*count);
        return *this;
    }
    T& operator*() const {
        return *ptr;
    }
    T* operator->(){
        return ptr;
    }
    T* get(){
        return ptr;
    }
private:
    T* ptr;
    size_t* count;
};

int main(){
    My_Shared_Ptr<int> p1 = new int(2);
    cout<<*p1<<endl;
    My_Shared_Ptr<int> p2 = new int(3);
    p1 = p2;
    cout<<*p1<<endl;
    cout<<*p2<<endl;
    return 0;
}