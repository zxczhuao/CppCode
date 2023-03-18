#include <iostream>
// #include <utility>

void print(){
    std::cout << std::endl;
}

template<typename... Args>
void foo(Args... args){
    // int arr[] = {(std::cout << args << " ", 0)...};
    int arr[] = {args...};
    for(auto it = std::begin(arr); it != std::end(arr); ++it)
        std::cout<<*it<<" ";
}

template<typename T>
void baz(T arg){
    std::cout<<arg<<" ";
}

template<typename T, typename... Args>
void baz(T arg, Args... args){
    baz(arg); // 处理第一个参数 
    baz(args...); // 递归处理剩余的参数
}

template<typename T, typename... Args>
void print(T&& t, Args&&... args){
    std::cout << std::forward<T>(t) << " ";
    print(std::forward<Args>(args)...);
}

int main()
{
    int a = 1;
    double b = 2.0;
    std::string c = "hello";
    print(a, b, c);
    foo(1, 2, 3, 4, 5, 6);
    std::cout << std::endl;
    return 0;    
}