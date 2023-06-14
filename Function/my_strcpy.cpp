#include <cassert>
#include <iostream>
#include <cstring>
using namespace std;

char* my_strcpy(char* dest, const char* src){
    assert(dest && src);
    char* ret = dest;
    while(*dest++ = *src++)
    {;}
    return ret;
}

char* test(){
    char s1[] = "hello";
    s1[2] = 'a';
    return s1;
}

int main(){
    // 记住char*和char[]的区别
    char s1[] = "hello, this is a test program;";
    char s2[] = "dddd";
    my_strcpy(s1, s2);
    cout<<s1<<endl;
    char* t = test();
    return 0;
}