#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
static int validateOperand(const char* operand)
{
    if(NULL == operand || *operand == 0)
        return FALSE;
    const char* p = operand;
    for(; *p != 0; ++p)
        if(*p < '0' || *p > '9')
            return FALSE;
    return TRUE;
}
char *multiply(char *operandA, char *operandB)
{
    char *pA, *pB, *result, *pRa, *pRb, carry, tmp;
    int lenA, lenB;
    if(!validateOperand(operandA) || !validateOperand(operandA))
        return NULL;
    lenA = strlen(operandA);
    lenB = strlen(operandB);
    result = (char*)calloc(sizeof(char), lenA + lenB + 1);
    for(pA = operandA + lenA - 1, pRa = result; pA >= operandA; --pA, ++pRa)
    {
        for(carry = 0, pRb = pRa, pB = operandB + lenB - 1; pB >= operandB; --pB, ++pRb)
        {
            tmp = (*pA - '0') * (*pB - '0') + carry + *pRb;
            *pRb = tmp % 10;
            carry = tmp / 10;
        }
        if(carry)
            *pRb++ = carry;
        *pRb = 0;
    }
    for(pRa = result; pRa < pRb; ++pRa, --pRb)
    {
        pRa[0] += '0';
        pRb[0] += '0';
        pRa[0] ^= pRb[0];
        pRb[0] ^= pRa[0];
        pRa[0] ^= pRb[0];
    }
    return result;
}
#ifdef TEST
int main(int argc, char *argv[])
{
    char *ret;
    if(argc < 3)
        return 1;
    ret = multiply(argv[1], argv[2]);
    if(ret)
    {
        printf("%s", ret);
        free(ret);
        if(isatty(1))
            printf("\n");
    }
}
#endif
