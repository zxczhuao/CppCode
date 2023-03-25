/*
 * @Author: zxczhuao
 * @Date: 2023-03-25 00:04:38
 * @LastEditTime: 2023-03-25 00:16:52
 * @FilePath: /CppCode/ThreadPool/threadtest.cpp
 * @Description: 
 * 
 */
#include "ThreadPool.h"
#include <iostream>
#include <sstream>

using namespace std;

std::mutex mtx;

void print(int i){
    std::ostringstream oss;
    oss<<"Thread id = "<<std::this_thread::get_id() <<endl;
    oss<<"number i = " << i <<endl; 
    std::cout<<oss.str();
}

int main(){
    ThreadPool* pool = new ThreadPool(5);
    for(int i = 0; i < 100; ++i){
        pool->add(bind(print, i));
    }
    delete pool;
    return 0;
}