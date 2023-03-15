#include <iostream>
using namespace std;

template<class T>
class sharedPtr_1
{
public:
    sharedPtr_1(T *p);
    ~sharedPtr_1();
    sharedPtr_1(const sharedPtr_1<T>& p);
    sharedPtr_1<T>& operator=(const sharedPtr_1<T> &rhs);
private:
    T *ptr;
    int *use_count;
};

template<class T>
sharedPtr_1<T>::sharedPtr_1(T *p): ptr(nullptr), use_count(nullptr){
    use_count = new int(1);
    cout<<"Constructor is called!"<<endl;
}

template<class T>
sharedPtr_1<T>::~sharedPtr_1(){
    if(--(*use_count) == 0)
    {
        if(ptr){
           delete ptr;
           ptr = nullptr;
        }
        delete use_count;
        use_count = nullptr;
    }
    cout << "Destructor is called!" <<endl;
}

template<class T>
sharedPtr_1<T>::sharedPtr_1(const sharedPtr_1<T>& p){
    use_count = p.use_count;
    ptr = p.ptr;
    ++(*use_count);
    cout<<"Copy constructor is called!"<<endl;
}

template<class T>
sharedPtr_1<T>& sharedPtr_1<T>::operator=(const sharedPtr_1<T>& rhs){
    ++(*rhs.use_count);
    if(--(*use_count) == 0){
        if(ptr)
            delete ptr;
        delete use_count;
    }
    ptr = rhs.ptr;
    use_count = rhs.use_count;
    cout<<"Assignment operator overload is called!"<<endl;
    return *this;
}
