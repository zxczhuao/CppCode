#include <iostream>
#include "sharedPtr_1.h"
#include "sharedPtr_2.h"
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

int main()
{
    test_ptr2();
    return 0;
}