#include <iostream>
#include "sharedPtr_1.h"
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

int main()
{
    test_ptr1();
    return 0;
}