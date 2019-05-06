#include <stdio.h>
#include <string.h>

#include "reverse.h"

void reverse(char *str)
{
    int i, j;
    j = strlen(str) - 1;
    for(i = 0; i < j; ++i, --j)
    {
        str[i] ^= str[j];
        str[j] ^= str[i];
        str[i] ^= str[j];
    }
}
#ifdef TEST
int main(int argc, char* const argv[])
{
    if(argc < 2)
        return 1;
    reverse(argv[1]);
    printf("%s\n", argv[1]);
}
#endif
