#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void add_char(char *des, char *src, int len, int pos)
{
    int i;
    if(pos >= len)
    {
        des[len] = '\0';
        printf("%s\n", des);
        return;
    }
    for(i = pos, des[i] = src[pos]; i >= 0; --i)
    {
        add_char(des, src, len, pos + 1);
        if(i > 0)
        {
            des[i] ^= des[i-1];
            des[i-1] ^= des[i];
            des[i] ^= des[i-1];
        }
        else
        {
            for(i = 0; i < len - 1; ++i)
            {
                des[i] = des[i+1];
            }
            i = 0;
        }
    }
}
void str_permutations(char *str)
{
    int len;
    char *des;
    len = strlen(str);
    des = (char*)malloc(len + 1);
    add_char(des, str, len, 0);
}
int main(int argc, char* const argv[])
{
    if(argc < 2)
        return 1;
    str_permutations(argv[1]);
}
