#include <iostream>
#include <vector>
#include "sharedPtr_1.h"
#include "sharedPtr_2.h"
#include "sharedPtr_temp.h"

using namespace std;

void test_ptr1(){
    sharedPtr_1<int> p1(new int(0));
    p1 = p1;
    // Test Copy Constructor
    sharedPtr_1<int> p2(p1);
    // Test Assignment Operator Overloaded
    sharedPtr_1<int> p3(new int(1));
    p3 = p1;
}

void test_ptr2(){
    smartptr<int> p1(new int(10));
    p1 = p1;
    cout<<*p1<<endl;
    smartptr<int> p2(p1);
    *p1 = 4;
    smartptr<int> p3(new int(11));
    p3 = p1;
    cout<<*p3<<endl;
}

struct t1{
public:
    int print(int a = 10){
        cout<<size<<" "<<val<<" "<<a<<endl;
    }
private:
    int size = 0;
    int val = 1;
};

void test_ptr3(){
    sharedPtr<int> p1(new int(10));
    p1 = p1;
    cout<<*p1<<endl;
    sharedPtr<int> p2(p1);
    *p1 = 4;
    sharedPtr<int> p3(new int(11));
    p3 = p1;
    cout<<*p3<<endl;
    sharedPtr<int> p4(std::move(p3));
    cout<<*p4<<endl;
    sharedPtr<t1> p(new t1);
    p->print(11);
}

int main()
{
    test_ptr3();
    return 0;
}