void merge(int* nums, int left, int mid, int right){
    int* temp = new int[mid - left + 1];
    for(int i = left; i <= mid; ++i)
        temp[i - left] = nums[i];
    int i = 0, j = mid + 1, k = left;
    while(i <= mid - left && j <= right){
        if(temp[i] <= nums[j]){
            nums[k++] = temp[i++];
        }
        else
            nums[k++] = nums[j++]; 
    }
    if(i > mid - left){
        while(j <= right)
            nums[k++] = nums[j++];
    } else if(j > right){
        while(i <= mid - left)
            nums[k++] = temp[i++];
    }
}

void merge_sort(int* nums, int left, int right){
    if(left >= right)
        return;
    int mid = left + (right - left) / 2;
    merge_sort(nums, left, mid);
    merge_sort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}