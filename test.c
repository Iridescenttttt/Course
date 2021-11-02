#include "String.h"

int main()
{
    string a, b, c;
    StrInit(&a);
    StrAssign(&a);
    StrInit(&b);
    StrAssign(&b);
    StrInit(&c);
    StrAssign(&c);
    Replace(&a, b, c);
    StrPrint(a);
    return 0;
}