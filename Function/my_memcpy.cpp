#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

void* my_memcpy(void* dest, const void* src, size_t size){
    if(dest == nullptr || src == nullptr)
        return nullptr;
    // 倒
    if(dest > src){
        char* d = (char*)dest + size - 1;
        const char* s = (const char*)src + size - 1;
        while(size--)
            *d-- = *s--;
    }else{
        char* d = (char*)dest;
        const char* s = (const char*)src;     
        while(size--)
            *d++ = *s++;
    }
    return dest;
}

int main(){
    int a[10] = {1, 2, 3, 4};
    int b[3];
    cout<<sizeof(b)<<endl;
    my_memcpy(b, a, sizeof(b));
    for_each(begin(b), end(b), [](const int i){cout<<i<<endl;});
    return 0;
}