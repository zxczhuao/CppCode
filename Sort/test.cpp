#include <iostream>
#include "quick_sort.h"

void quicksort_test(int* arr){

}

void show(int* arr, int length){
    for(int i = 0; i < length; ++i)
        std::cout<<arr[i]<<std::endl;
    std::cout<<std::endl;
}

int main(){
    int arr[] = {9, 5, 8, 1, 3, 7, 2, 4, 6};
    quick_sort(arr, 0, sizeof(arr)/sizeof(int) - 1);
    show(arr, sizeof(arr)/sizeof(int));
    return 0;
}