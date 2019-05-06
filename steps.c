
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "steps.h"

#define TRUE 1
#define FALSE 0

char buf[1024];
int validateSteps(const char* steps)
{
    char* endptr = NULL;
    int ret = strtol(steps, &endptr, 10);
    if(NULL == endptr || *endptr != 0)
        return FALSE;
    return ret;
}
void walk(int steps)
{
    static char* stepsRecord = NULL;
    if(NULL == stepsRecord)
    {
        stepsRecord = (char*)malloc(steps + 1);
        stepsRecord[0] = 0;
    }
    if(steps >= 1)
    {
        strcat(stepsRecord, "1");
        walk(steps - 1);
    }
    if(steps >= 2)
    {
        strcat(stepsRecord, "2");
        walk(steps - 2);
    }
    if(steps >= 3)
    {
        strcat(stepsRecord, "3");
        walk(steps - 3);
    }
    if(steps == 0)
        printf("%s\n", stepsRecord);
    stepsRecord[strlen(stepsRecord) - 1] = 0;
}
#ifdef TEST
int main(int argc, const char* const argv[])
{
    if(argc != 2)
    {
        write(2, buf, sprintf(buf, "only accept 1 args\n"));
        return 1;
    }
    int steps;
    if(!(steps = validateSteps(argv[1])))
    {
        write(2, buf, sprintf(buf, "steps not a num>0\n"));
        return 1;
    }
    walk(steps);
}
#endif
