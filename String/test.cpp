#include "String.h"

void test1(){
    String s1;
    String s2("hello world!");
    String s3 = s2;
    s1 += "12345";
    std::cout<<s1<<std::endl;
    std::cout<<s2<<std::endl;
    std::cout<<s3<<std::endl;
}

int main(){
    test1();
    return 0;
}