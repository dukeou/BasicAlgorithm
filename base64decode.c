#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//const char baseMap[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static int decode_char(char c)
{
    int i;
    if(isupper(c))
    {
        i = c - 'A';
    }
    else if(islower(c))
    {
        i = c - 'a' + 26;
    }
    else if(isdigit(c))
    {
        i = c - '0' + 52;
    }
    else if(c == '+')
    {
        i = 62;
    }
    else if(c == '/')
    {
        i = 63;
    }
    else
    {
        assert(0);
    }
    return i;
}
char *base64decode(char *str)
{
    int j, phase;
    char *decode, *byteP, c;
    decode = (char*)malloc(strlen(str) * 3 / 4 + 1);
    byteP = str;
    for(j = 0, phase = 0; *byteP; ++phase, ++byteP)
    {
        phase %= 4;
        if(*byteP == '=')
            break;
        c = decode_char(*byteP);
        switch(phase)
        {
            case 0:
                decode[j++] = (c << 2);
                break;
            case 1:
                decode[j-1] |= ((c >> 4) & 0x03);
                decode[j++] = (c << 4);
                break;
            case 2:
                decode[j-1] |= (c >> 2);
                decode[j++] = (c << 6);
                break;
            case 3:
                decode[j-1] |= c;
                break;
        }
    }
    decode[j] = '\0';
    return decode;
}
#ifdef TEST
int main(int argc, char * const argv[])
{
    int i;
    char *decode;
    for(i = 1; i < argc; i++)
    {
        decode = base64decode(argv[i]);
        printf("%s", decode);
        free(decode);
        if(argc > (i + 1))
            printf(" ");
    }
    if(isatty(1))
        printf("\n");
}
#endif
