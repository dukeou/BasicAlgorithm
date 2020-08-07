#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifdef TEST
void hanoi(int h, int src, int dst);
int main(int argc, char* argv[])
{
    int ret = 0;
    do {
        if (argc < 2) {
            fprintf(stderr, "Need a hight of the tower.\n");
            ret = 1;
            break;
        }
        char* end = NULL;
        int h = strtol(argv[1], &end, 10);
        if (end == NULL || *end != 0) {
            ret = 1;
            break;
        }
        hanoi(h, 0, 2);
    } while(0);
    return ret;
}
#endif

void hanoi(int h, int src, int dst)
{
    int avail;
    switch(src + dst) {
        case 1:
            avail = 2;
            break;
        case 2:
            avail = 1;
            break;
        case 3:
            avail = 0;
            break;
        default:
            break;
    }
    if (h <= 0) {
    } if (h == 1) {
        printf("Move %d %d->%d.\n", h, src, dst);
    } else {
        hanoi(h - 1, src, avail);
        printf("Move %d %d->%d.\n", h, src, dst);
        hanoi(h - 1, avail, dst);
    }
}
