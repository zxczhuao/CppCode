#include <iostream>
#include <vector>
#include <functional>
using namespace std;

void foo(int a, int b){
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
}

int main(){
    auto print = bind(foo, placeholders::_2, placeholders::_1);
    print(10, 20);
    return 0;
}