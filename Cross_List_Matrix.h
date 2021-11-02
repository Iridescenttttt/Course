#include<stdio.h>
#include<stdlib.h>

#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 10

typedef struct LNode{
    int row, col, e;
    struct LNode* right;
    struct LNode* down;
}LNode;

typedef struct CLMatrix{
    LNode *rowhead;
    LNode *colhead;
    int Rows;
    int Cols;
    int Nums;
}CLMatrix;

// Status CreatMatrix(CLMatrix *M)
// {
//     printf("Please input the matrix's rows and cols.\n");
//     scanf("%d%d", &M->Rows, &M->Cols);
//     M->rowhead = (LNode*)malloc(M->Rows * sizeof(LNode));
//     if(!M->rowhead)return OVERFLOW;
//     M->colhead = (LNode*)malloc(M->Cols * sizeof(LNode));
//     if(!M->colhead)return OVERFLOW;
//     for(int i = 0; i < M->Rows; i++){
//         M->rowhead[i].right = NULL;
//         M->rowhead[i].down = NULL;
//     }
//     for(int i = 0; i < M->Cols; i++){
//         M->colhead[i].right = NULL;
//         M->colhead[i].down = NULL;
//     }
//     printf("Please input the Sparse Matrix.\n");
//     LNode *p, *q;
//     int a, b, c;
//     M->Nums = 0;
//     while(~scanf("%d%d%d", &a, &b, &c)){            //按照行优先规则输入
//         p = (LNode*)malloc(sizeof(LNode));
//         if(!p)return OVERFLOW;
//         p->row = a;
//         p->col = b;
//         p->e = c;
//         p->right = NULL;
//         p->down = NULL;
//         if(M->rowhead[p->row].right == NULL){
//             M->rowhead[p->row].right = p;
//         }
//         else{
//             q = M->rowhead[p->row].right;
//             while(q->right){
//                 q = q->right;
//             }
//             q->right = p;
//         }
//         if(M->colhead[p->col].down == NULL){
//             M->colhead[p->col].down = p;
//         }
//         else{
//             q = M->colhead[p->col].down;
//             while(q->down){
//                 q = q->down;
//             }
//             q->down = p;
//         }
//     }
//     return OK;
// }

Status CreatMatrix(CLMatrix *M)
{
    printf("Please input the matrix's rows and cols.\n");
    scanf("%d%d", &M->Rows, &M->Cols);
    M->rowhead = (LNode*)malloc(M->Rows * sizeof(LNode));
    if(!M->rowhead)return OVERFLOW;
    M->colhead = (LNode*)malloc(M->Cols * sizeof(LNode));
    if(!M->colhead)return OVERFLOW;
    for(int i = 0; i < M->Rows; i++){
        M->rowhead[i].right = NULL;
        M->rowhead[i].down = NULL;
    }
    for(int i = 0; i < M->Cols; i++){
        M->colhead[i].right = NULL;
        M->colhead[i].down = NULL;
    }
    int e;
    LNode *p, *q;
    for(int i = 0; i < M->Rows; i++){
        for(int j = 0; j < M->Cols; j++){
            scanf("%d", &e);
            if(e != 0){
                p = (LNode*)malloc(sizeof(LNode));
                if(!p)return OVERFLOW;
                p->row = i;
                p->col = j;
                p->e = e;
                p->right = NULL;
                p->down = NULL;
                if(M->rowhead[p->row].right == NULL){
                    M->rowhead[p->row].right = p;
                }
                else{
                    q = M->rowhead[p->row].right;
                    while(q->right){
                        q = q->right;
                    }
                    q->right = p;
                }
                if(M->colhead[p->col].down == NULL){
                    M->colhead[p->col].down = p;
                }
                else{
                    q = M->colhead[p->col].down;
                    while(q->down){
                        q = q->down;
                    }
                    q->down = p;
                }
            }
        }
    }
    return OK;
}

Status DeatoryMatrix(CLMatrix *M)
{
    LNode *p, *q;
    for(int i = 0; i < M->Rows; i++){
        if(M->rowhead[i].down){
            p = q = M->rowhead[i].down;
            while(p->down){
                q = p->down;
                free(p);
                p = q;
            }
        }
    }
    free(M->rowhead);
    free(M->colhead);
    M->Rows = M->Cols = M->Nums = 0;
    return OK;
}

Status PrintMatrix(CLMatrix M)
{
    for(int i = 0; i < M.Rows; i++){
        if(M.rowhead[i].right == NULL){
            for(int j = 0; j < M.Cols; j++){
                printf("%d ", 0);
            }
            printf("\n");
        }
        else{
            LNode *p = M.rowhead[i].right;
            for(int j = 0; j < M.Cols; j++){
                if(p != NULL && p->col == j){
                    printf("%d ", p->e);
                    p = p->right;
                }
                else{
                    printf("%d ", 0);
                }
            }
            printf("\n");
        }
    }
    return OK;
}

Status CopyMatrix(CLMatrix M, CLMatrix *T)
{
    if(M.Nums == 0)return ERROR;
    
}

Status FindPos(CLMatrix *Q, LNode *p, LNode *q, LNode *r)
{
    LNode *s;
    if(!Q->rowhead[r->row].right){
        Q->rowhead[r->row].right = r;
        r->right = NULL;
    }
    else{
        s = Q->rowhead[r->row].right;
        while(s->right){
            s = s->right;
        }
        s->right = r;
        r->right = NULL;
    }
    if(!Q->colhead[r->col].down){
        Q->colhead[r->col].down = r;
        r->down = NULL;
    }
    else{
        s = Q->colhead[r->col].down;
        while(s->down){
            s = s->down;
        }
        s->down = r;
        r->down = NULL;
    }
    return OK;
}

Status AddMatrix(CLMatrix M, CLMatrix N, CLMatrix *Q)
{
    if(M.Rows != N.Rows || M.Cols != N.Cols)return ERROR;
    Q->rowhead = (LNode*)malloc(M.Rows * sizeof(LNode));
    if(!Q->rowhead)return OVERFLOW;
    Q->colhead = (LNode*)malloc(M.Cols * sizeof(LNode));
    if(!Q->colhead)return OVERFLOW;
    Q->Rows = M.Rows;
    Q->Cols = M.Cols;
    Q->Nums = 0;
    for(int i = 0; i < Q->Rows; i++){
        Q->rowhead[i].right = NULL;
        Q->rowhead[i].down = NULL;
    }
    for(int i = 0; i < Q->Cols; i++){
        Q->colhead[i].right = NULL;
        Q->colhead[i].down = NULL;
    }
    int i = 0;               // 迭代M与N的行数
    LNode *p, *q, *r, *s;
    while(i < M.Rows){
        p = M.rowhead[i].right;
        q = N.rowhead[i].right;
        while(p || q){
            r = (LNode*)malloc(sizeof(LNode));
            if(p && q && p->col == q->col){
                r->row = p->row;
                r->col = p->col;
                r->e = p->e + q->e;
                FindPos(Q, p, q, r);
                p = p->right;
                q = q->right;
            }
            else if((p && q && p->col < q->col) || (p && !q)){
                r->row = p->row;
                r->col = p->col;
                r->e = p->e;
                FindPos(Q, p, q, r);
                p = p->right;
            }
            else if((p && q && p->col > q->col) || (q && !p)){
                r->row = q->row;
                r->col = q->col;
                r->e = q->e;
                FindPos(Q, p, q, r);
                q = q->right;
            }
            Q->Nums++;
        }
        i++;
    }
    return OK;
}

Status PrintAsSqMa(CLMatrix M)
{
    LNode *p;
    for(int i = 0; i < M.Rows; i++){
        p = M.rowhead[i].right;
        while(p){
            printf("(%d,%d,%d)\n", p->row, p->col, p->e);
            p = p->right;
        }
    }
    return OK;
}