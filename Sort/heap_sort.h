#include <vector>
#include <iostream>

using namespace std;

void adjustHeap(vector<int>& nums, int start, int end){
    int dad = start;
    int son = dad * 2 + 1;
    while(son <= end){
        if(son + 1 <= end && nums[son] < nums[son + 1]){
            ++son;
        }
        if(nums[dad] < nums[son]){
            swap(nums[dad], nums[son]);
            dad = son;
            son = dad * 2 + 1;
        }
        else
            return;
    }
}

void buildHeap(vector<int>& nums){
    int len = nums.size();
    for(int i = len / 2 - 1; i >= 0; --i){
        adjustHeap(nums, i, len - 1);
    }
}

void heap_sort(vector<int>& nums){
    int len = nums.size();
    buildHeap(nums);
    for(int i = len - 1; i > 0; --i){
        swap(nums[0], nums[i]);
        adjustHeap(nums, 0, i - 1);
    }
}
