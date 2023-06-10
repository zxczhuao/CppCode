#include <vector>
#include <iostream>

using namespace std;

void adjust_heap(vector<int>& nums, int start, int end){
    int dad = start;
    int son = dad * 2 + 1;
    while(son <= end){
        if(son <= end - 1 && nums[son] > nums[son + 1])
            son++;
        if(nums[dad] < nums[son])
            return;
        swap(nums[dad], nums[son]);
        dad = son;
        son = son * 2 + 1;
    }
}

void build_heap(vector<int>& nums){
    int len = nums.size();
    for(int i = len/2 - 1; i >= 0; i--){
        adjust_heap(nums, i, len - 1);
    }
}

void heap_sort(vector<int>& nums){
    int len = nums.size();
    build_heap(nums);
    for(int i = len - 1; i > 0; --i){
        swap(nums[0], nums[i]);
        adjust_heap(nums, 0, i - 1);
    }
}