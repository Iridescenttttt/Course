#include "Cross_List_Matrix.h"

int main()
{
    CLMatrix M1, M2, M3;
    CreatMatrix(&M1);
    CreatMatrix(&M2);
    AddMatrix(M1, M2, &M3);
    PrintMatrix(M3);
    return 0;
}