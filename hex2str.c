#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *hex2str(char *hex)
{
    char *str = (char*)malloc(strlen(hex)/2);
    char *p, *dst_p, *endptr, save_char, c;
    for(p = hex, dst_p = str; *p != 0 && *(p + 1) != 0; p += 2)
    {
        endptr=NULL;
        save_char = p[0];
        p[2] = 0;
        c = (char)strtol(p, &endptr, 16);
        p[2] = save_char;
        if(endptr != NULL && *endptr == 0)
            *dst_p++ = c;
        p += 2;
    }
    *dst_p = 0;
    return str;
}
#ifdef TEST
int main(int argc, char **argv)
{
    int i, n, r;
    char *str, rdbuf[1024];
    if(argc > 1)
    {
        for(i = 1; i < argc; ++i)
        {
            str = hex2str(argv[i]);
        }
        printf("%s", str);
        free(str);
        if(argc > (i + 1))
            printf(" ");
    }
    else if(!isatty(0))
    {
        r = 0;
        while((n = read(0, rdbuf + r, sizeof(rdbuf) - r)) > 0)
        {
            str = hex2str(rdbuf);
            printf("%s", str);
            free(str);
            rdbuf[0] = rdbuf[n + r - 1];
            r = (n + r) % 2;
        }
    }
    if(isatty(1))
        printf("\n");
    return 0;
}
#endif
