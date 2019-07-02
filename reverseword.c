#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reverseword.h"

void reverse_str(char *str)
{
    if(!str || !str[0])
        return;
    int len = strlen(str);
    if(len < 2)
        return;
    int i, j;
    for(i = 0, j = len - 1; i < j; ++i, --j)
    {
        str[i] ^= str[j];
        str[j] ^= str[i];
        str[i] ^= str[j];
    }
}
void reverse_word(char *str)
{
    if(!str || !str[0])
        return;
    reverse_str(str);
    char *end, *start, saved_char;
    for(start = str; start[0] && (end = strchr(start, ' ')); start = end)
    {
        saved_char = end[0];
        end[0] = 0;
        reverse_str(start);
        end[0] = saved_char;
        while(end[0] == ' ') ++end;
    }
    if(start[0])
    {
        reverse_str(start);
    }
}

#ifdef TEST
int main(int argc, char *argv[])
{
    if(argc < 2)
        return 0;
    int i;
    for(i = 1; i < argc; ++i)
    {
        reverse_word(argv[i]);
        printf("\"%s\"\n", argv[i]);
    }
}
#endif
