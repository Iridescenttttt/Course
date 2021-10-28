#include<stdio.h>
#include<stdlib.h>

#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 10

typedef struct Triple{
    int row;
    int col;
    int e;
}Triple;

typedef struct SqSMatrix{
    Triple arr[MAXSIZE];
    int Rows, Cols, Nums;
}SqSMatrix;

// Status CreatMatrix(SqSMatrix *M)
// {
//     printf("Please input the Matrix's rows and cols.\n");
//     scanf("%d%d", &M->Rows, &M->Cols);
//     printf("Please input the Sparse Martix.\n");
//     M->Nums = 0; 
//     while(~scanf("%d%d%d", &M->arr[M->Nums].row, &M->arr[M->Nums].col, &M->arr[M->Nums].e)){
//         M->Nums++;
//     }
//     return OK;
// }

Status CreatMatrix(SqSMatrix *M)
{
    printf("Please input the Matrix's rows and cols.\n");
    scanf("%d%d", &M->Rows, &M->Cols);
    printf("Please input the Matrix.\n");
    int e;
    M->Nums = 0;
    for(int i = 0; i < M->Rows; i++){
        for(int j = 0; j < M->Cols; j++){
            scanf("%d", &e);
            if(e != 0){
                M->arr[M->Nums].row = i;
                M->arr[M->Nums].col = j;
                M->arr[M->Nums].e = e;
                M->Nums++;
            }
        }
    }
    return OK;
}

Status DestoryMatrix(SqSMatrix *M)
{
    if(M->arr != NULL){
        free(M->arr);
    }
    M->Cols = 0;
    M->Rows = 0;
    M->Nums = 0;
    return OK;
}

Status PrintMatrix(SqSMatrix M)
{
    if(M.arr == NULL)return ERROR;
    int n = 0;
    for(int i = 0; i < M.Rows; i++){
        for(int j = 0; j < M.Cols; j++){
            if(i == M.arr[n].row && j == M.arr[n].col){
                printf("%d ", M.arr[n].e);
                n++;
            }
            else{
                printf("%d ", 0);
            }
        }
        printf("\n");
    }
    return OK;
}

Status CopyMatrix(SqSMatrix M, SqSMatrix *T)
{
    if(M.arr == NULL)return ERROR;
    for(int i = 0; i < M.Nums; i++){
        T->arr[i] = M.arr[i];
    }
    T->Cols = M.Cols;
    T->Rows = M.Rows;
    T->Nums = M.Nums;
    return OK;
}

Status AddMatrix(SqSMatrix M, SqSMatrix N, SqSMatrix *Q)
{
    Q->Rows = M.Rows;
    Q->Cols = N.Cols; 
    Q->Nums = 0;
    int num_m = 0, num_n = 0;
    while(num_m < M.Nums || num_n < N.Nums){
        if(num_m != M.Nums && num_n != N.Nums && M.arr[num_m].row == N.arr[num_n].row && M.arr[num_m].col == N.arr[num_n].col){
            Q->arr[Q->Nums].row = M.arr[num_m].row;
            Q->arr[Q->Nums].col = M.arr[num_m].col;
            Q->arr[Q->Nums].e = M.arr[num_m].e + N.arr[num_n].e;
            Q->Nums++;
            num_m++;
            num_n++;
        }
        else if(num_n == N.Nums || M.arr[num_m].row < N.arr[num_n].row){
            Q->arr[Q->Nums].row = M.arr[num_m].row;
            Q->arr[Q->Nums].col = M.arr[num_m].col;
            Q->arr[Q->Nums].e = M.arr[num_m].e;
            Q->Nums++;
            num_m++;
        }
        else if(num_m == M.Nums || M.arr[num_m].row > N.arr[num_n].row){
            Q->arr[Q->Nums].row = N.arr[num_m].row;
            Q->arr[Q->Nums].col = N.arr[num_m].col;
            Q->arr[Q->Nums].e = N.arr[num_n].e;
            Q->Nums++;
            num_n++;
        }
    }
    return OK;
}

Status SubMatrix(SqSMatrix M, SqSMatrix N, SqSMatrix *Q)
{
    int num_m = 0, num_n = 0, num_q = 0;
    while(num_m < M.Nums || num_n < N.Nums){
        if(num_m != M.Nums && num_n != N.Nums && M.arr[num_m].row == N.arr[num_n].row && M.arr[num_m].col == N.arr[num_n].col){
            Q->arr[num_q].row = M.arr[num_m].row;
            Q->arr[num_q].col = M.arr[num_m].col;
            Q->arr[num_q].e = M.arr[num_m].e - N.arr[num_n].e;
            Q->Rows++;
            Q->Cols++;
            Q->Nums++;
            num_m++;
            num_n++;
            num_q++;
        }
        else if(num_n == N.Nums || M.arr[num_m].row < N.arr[num_n].row){
            Q->arr[num_q].row = M.arr[num_m].row;
            Q->arr[num_q].col = M.arr[num_m].col;
            Q->arr[num_q].e = M.arr[num_m].e;
            Q->Rows++;
            Q->Cols++;
            Q->Nums++;
            num_m++;
            num_q++;
        }
        else{
            Q->arr[num_q].row = N.arr[num_m].row;
            Q->arr[num_q].col = N.arr[num_m].col;
            Q->arr[num_q].e = N.arr[num_n].e;
            Q->Rows++;
            Q->Cols++;
            Q->Nums++;
            num_n++;
            num_q++;
        }
    }
    return OK;   
}

Status MultMatrix(SqSMatrix M, SqSMatrix N, SqSMatrix *Q)
{
    Q->Nums = 0;
    Q->Rows = M.Rows;
    Q->Cols = N.Cols;
    if(M.Rows != N.Cols)return ERROR;
    for(int i = 0; i < M.Nums; i++){
        int flag = 0, j;
        for(j = 0; j < N.Nums; j++){
            if(M.arr[i].row == N.arr[j].row && M.arr[i].col == N.arr[j].col){
                flag = 1;
                break;
            }
        }
        if(flag){
            Q->arr[Q->Nums].row = M.arr[i].row;
            Q->arr[Q->Nums].col = M.arr[i].col;
            Q->arr[Q->Nums].e = M.arr[i].e * N.arr[j].e;
            Q->Nums++;
        }
    }
    return OK;
}

Status TransposeMatrix(SqSMatrix M, SqSMatrix *T)
{
    if(M.arr == NULL)return ERROR;
    T->Rows = M.Cols;
    T->Cols = M.Rows;
    T->Nums = M.Nums;
    int num[MAXSIZE] = {0};
    for(int i = 0; i < M.Nums; i++){
        num[M.arr[i].col]++;
    }
    int next[MAXSIZE] = {0};
    for(int i = 1; i < M.Cols; i++){
        next[i] = next[i - 1] + num[i - 1];
    }
    for(int i = 0; i < M.Nums; i++){
        T->arr[next[M.arr[i].col]].row = M.arr[i].col;
        T->arr[next[M.arr[i].col]].col = M.arr[i].row;
        T->arr[next[M.arr[i].col]].e = M.arr[i].e;
        next[M.arr[i].col]++;
    }
    return OK;
}