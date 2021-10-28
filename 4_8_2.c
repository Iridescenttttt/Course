// #include "Sparse_Matrix.h"

// //顺序存储形式

// int main()
// {
//     SqSMatrix M;
//     CreatMatrix(&M);
//     PrintMatrix(M);
//     return 0;
// }


#include "Cross_List_Matrix.h"

// 十字链表

int main()
{
    CLMatrix M;
    CreatMatrix(&M);
    // PrintMatrix(M);
    PrintAsSqMa(M);
    return 0;
}