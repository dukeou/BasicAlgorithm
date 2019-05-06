#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char baseMap[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char *base64encode(char *str)
{
    unsigned char *byteP = (unsigned char *)str;
    int len = (strlen(str) + 2) / 3 * 4 + 1;
    char *base64 = (char*)malloc(len);
    int phase = 0;
    int index = 0;
    while(*byteP != 0)
    {
        switch(phase)
        {
            case 0:
                base64[index++] = baseMap[*byteP >> 2];
                ++byteP;
                ++phase;
                break;
            case 1:
                base64[index++] = baseMap[(((*(byteP - 1) << 4) & 0x3f)) | ((*byteP) >> 4)];
                ++byteP;
                ++phase;
                break;
            case 2:
                base64[index++] = baseMap[((*(byteP - 1) << 2) & 0x3f) | ((*byteP) >> 6)];
                base64[index++] = baseMap[(*byteP) & 0x3f];
                ++byteP;
                phase = 0;
                break;
            default:
                assert(0);
                break;
        }
    }
    switch(phase)
    {
        case 0:
            base64[index] = 0;
            break;
        case 1:
            base64[index++] = baseMap[(*(byteP - 1) << 4) & 0x3f];
            base64[index++] = '=';
            base64[index++] = '=';
            base64[index] = 0;
            break;
        case 2:
            base64[index++] = baseMap[(*(byteP - 1) << 2) & 0x3f];
            base64[index++] = '=';
            base64[index] = 0;
            break;
        default:
            assert(0);
            break;
    }
    return base64;
}
#ifdef TEST
int main(int argc, char **argv)
{
    int i;
    char *base64;
    for(i = 1; i < argc; i++)
    {
        base64 = base64encode(argv[i]);
        printf("%s", base64);
        free(base64);
        if(argc > (i + 1))
            printf(" ");
    }
    if(isatty(1))
        printf("\n");
}
#endif
