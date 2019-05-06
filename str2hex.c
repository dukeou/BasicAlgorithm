#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *str2hex(char *str)
{
    char *hex, *p;
    hex = (char*)malloc(strlen(str) << 1 + 1);
    for(p = hex, p[0] = 0; str[0]; ++str)
    {
        p += sprintf(p, "%02hhX", str[0]);
    }
    return hex;
}
#ifdef TEST
int main(int argc, char **argv)
{
    int n, i;
    char *p, buf[1024], *hex;
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            hex = str2hex(argv[i]);
            printf("%s", hex);
            free(hex);
            if(argc > (i + 1))
                printf(" ");
        }
    }
    else if(!isatty(0))
    {
        while((n = read(0, buf, sizeof(buf) - 1)) > 0)
        {
            buf[n] = 0;
            hex = str2hex(argv[i]);
            printf("%s", hex);
            free(hex);
        }
    }
    if(isatty(1))
        printf("\n");
}
#endif
