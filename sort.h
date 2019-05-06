typedef int (*comp_func)(int, int);
void bubble_sort(int key_arr[], int sort_arr[], int arr_len, comp_func cmp);
void quick_sort(int key_arr[], int sort_arr[], int arr_len, comp_func cmp);
void heap_sort(int key_arr[], int sort_arr[], int arr_len, comp_func cmp);
