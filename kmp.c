#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int *kmp(char *str)
{
    int len = strlen(str);
    int *kmp_arr = (int*)malloc(len * sizeof(int));
    int i, j;
    kmp_arr[i] = -1;
    for(i = 0, j = 1; j < len;)
    {
        if(str[j] == str[i])
        {
            kmp_arr[j] = kmp_arr[i];
            printf("next[%d] = %d\n", j, kmp_arr[i]);
            ++i;
            ++j;
        }
        else
        {
            kmp_arr[j] = i;
            printf("next[%d] = %d\n", j, i);
            if(kmp_arr[i] != -1)
                i = kmp_arr[i];
            else
                i = 0;
        }
    }
    return kmp_arr;
}
#ifdef TEST
int main(int argc, char *argv[])
{
    if(argc >1)
    {
        int *kmp_arr = kmp(argv[1]);
        int i;
        char *p;
        for(i = 0, p = argv[1]; *p; ++p, ++i)
        {
            printf("%c[%d]", *p, kmp_arr[i]);
        }
        printf("\n");
        free(kmp_arr);
    }
}
#endif
