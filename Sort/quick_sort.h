void quick_sort(int* arr, int low, int high){
    if(low >= high) return;
    int i = low, j = high;
    int pivot = arr[low];
    while(i < j){
        while(i < j && arr[j] >= pivot)
            --j;
        while(i < j && arr[i] <= pivot)
            ++i;
        if(i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    arr[low] = arr[j];
    arr[j] = pivot;
    quick_sort(arr, low, i - 1);
    quick_sort(arr, i + 1, high);
}