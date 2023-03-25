/*
 * @Author: zxczhuao
 * @Date: 2023-03-24 21:50:16
 * @LastEditTime: 2023-03-25 15:21:59
 * @FilePath: /CppCode/Sort/test.cpp
 * @Description: 
 * 
 */
#include <iostream>
#include "quick_sort.h"
#include "merge_sort.h"
#include "heap_sort.h"

using namespace std;
void show(int* arr, int length){
    for(int i = 0; i < length; ++i)
        std::cout<<arr[i]<<std::endl;
    std::cout<<std::endl;
}

int main(){
    int arr[] = {9, 5, 8, 1, 3, 7, 2, 4, 6};
    vector<int> nums(begin(arr), end(arr));
    heap_sort(nums);
    for(auto i:nums)
        cout<<i<<endl;
    // quick_sort(arr, 0, sizeof(arr)/sizeof(int) - 1);
    // merge_sort(arr, 0, sizeof(arr)/sizeof(int) - 1);
    //show(arr, sizeof(arr)/sizeof(int));
    return 0;
}