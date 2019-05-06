#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define EXCHANGE(a, b) {(a)^=(b);(b)^=(a);(a)^=(b);}
#define GT(a, b, cmp) (cmp((a),(b))>0)
#define GE(a, b, cmp) (cmp((a),(b))>=0)
#define LT(a, b, cmp) (cmp((a),(b))<0)
#define LE(a, b, cmp) (cmp((a),(b))<=0)
void bubble_sort(int key_arr[], int sort_arr[], int arr_len, comp_func cmp)
{
    int i, j;
    for(i = 0; i < arr_len; ++i)
        sort_arr[i] = i;
    for(j = (arr_len - 1); j > 0; --j)
    {
        for(i = 0; i < j; ++i)
        {
            if(GT(key_arr[sort_arr[i]], key_arr[sort_arr[i + 1]], cmp))
            {
                EXCHANGE(sort_arr[i], sort_arr[i + 1]);
            }
        }
    }
}
static void _quick_sort(int key_arr[], int sort_arr[], int arr_len, comp_func cmp)
{
    int i = 0, j = arr_len - 1, pivot = sort_arr[i];
    while(i < j)
    {
        while(i < j && GE(key_arr[sort_arr[j]], key_arr[pivot], cmp)) --j;
        sort_arr[i] = sort_arr[j];
        while(i < j && LE(key_arr[sort_arr[i]], key_arr[pivot], cmp)) ++i;
        sort_arr[j] = sort_arr[i];
    }
    sort_arr[i] = pivot;
    if(i)
        _quick_sort(key_arr, sort_arr, i, cmp);
    if(i < arr_len - 2)
        _quick_sort(key_arr, sort_arr + i + 1, arr_len - i - 1, cmp);
}
void quick_sort(int key_arr[], int sort_arr[], int arr_len, comp_func cmp)
{
    int i;
    for(i = 0; i < arr_len; ++i)
        sort_arr[i] = i;
    if(arr_len > 1)
        _quick_sort(key_arr, sort_arr, arr_len, cmp);
}
void heap_sort(int key_arr[], int sort_arr[], int arr_len, comp_func cmp)
{
    int i, j, k, m, n;
    if(arr_len < 2)
        return;
    for(i = 0; i < arr_len; ++i)
        sort_arr[i] = i;
    i = arr_len/2 - 1;
    if(arr_len % 2 == 0)
    {
        j = arr_len - 1;
        if(GT(key_arr[sort_arr[j]], key_arr[sort_arr[i]], cmp))
            EXCHANGE(sort_arr[m], sort_arr[j]);
        --i;
    }
    for(; i >= 0; --i)
    {
        j = i * 2 + 1;
        k = j + 1;
        m = LT(key_arr[sort_arr[j]], key_arr[sort_arr[k]], cmp) ? k : j;
        if(GT(key_arr[sort_arr[m]], key_arr[sort_arr[i]], cmp))
        {
            EXCHANGE(sort_arr[m], sort_arr[i]);
            while(1)
            {
                j = m * 2 + 1;
                k = j + 1;
                if(k < arr_len)
                    n = LT(key_arr[sort_arr[j]], key_arr[sort_arr[k]], cmp) ? k : j;
                else if(j < arr_len)
                    n = j;
                else
                    break;
                if(GT(key_arr[sort_arr[n]], key_arr[sort_arr[m]], cmp))
                {
                    EXCHANGE(sort_arr[n], sort_arr[m]);
                    m = n;
                }
                else
                    break;
            }
        }
    }
    for(i = arr_len - 1; i > 0; --i)
    {
        EXCHANGE(sort_arr[0], sort_arr[i]);
        m = 0;
        while(1)
        {
            j = m * 2 + 1;
            k = j + 1;
            if(k < i)
                n = LT(key_arr[sort_arr[j]], key_arr[sort_arr[k]], cmp) ? k : j;
            else if(j < i)
                n = j;
            else
                break;
            if(GT(key_arr[sort_arr[n]], key_arr[sort_arr[m]], cmp))
            {
                EXCHANGE(sort_arr[n], sort_arr[m]);
                m = n;
            }
            else
                break;
        }
    }
}
int compare_int(int a, int b)
{
    return a > b ? 1 : (a == b ? 0 : -1);
}
#ifdef TEST
int main(int argc, char *argv[])
{
    char *temp;
    int *array, *sort_array;
    int i, j, d;
    if(argc > 1)
    {
        array = (int*)malloc((argc - 1) * sizeof(int));
        sort_array = (int*)malloc((argc - 1) * sizeof(int));
        for(i = 1, j = 0; i < argc; ++i)
        {
            temp = NULL;
            d = strtol(argv[i], &temp, 10);
            if(!temp[0])
                array[j++] = d;
        }
        if(j)
        {
            printf("original array:\n");
            for(i = 0; i < j; ++i) printf("%d ", array[i]); if(i) printf("\n");
            printf("%-12s:", "bubble_sort");
            bubble_sort(array, sort_array, j, compare_int);
            for(i = 0; i < j; ++i) printf("%d ", array[sort_array[i]]); if(i) printf("\n");
            printf("%-12s:", "quick_sort");
            quick_sort(array, sort_array, j, compare_int);
            for(i = 0; i < j; ++i) printf("%d ", array[sort_array[i]]); if(i) printf("\n");
            printf("%-12s:", "heap_sort");
            heap_sort(array, sort_array, j, compare_int);
            for(i = 0; i < j; ++i) printf("%d ", array[sort_array[i]]); if(i) printf("\n");
        }
        free(array);
        free(sort_array);
    }
}
#endif
