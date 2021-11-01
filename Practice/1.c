#include<stdio.h>
#include<stdbool.h>

#define LISTINITSIZE 256
#define LISTINCREMENT 128
#define ElemType int
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef struct SeqList{
    ElemType *pData;
    int length;
    int size;
}SeqList;

Status InitList(SeqList *L){
    L->pData = (ElemType*)malloc(LISTINITSIZE * sizeof(ElemType));
    if(!L->pData)return OVERFLOW;
    L->size = LISTINITSIZE;
    L->length = 0;
    return OK;
}

Status DestoryList(SeqList *L){
    if(L->pData){
        free(p->pData);
        pData = NULL;
    }
    L->size = 0;
    L->length = 0;
    return OK;
}

Status ClearList(SeqList *L){
    L->length = 0;
    return OK;
}

bool ListEmpty(SeqList L){
    if(L->length != 0)return false
    return true;
}

int ListLength(SeqList L){
    return L.length;
}

Status GetElem(SeqList L, int i, ElemType *e){
    if(i < 1 || i > L->length)return OVERFLOW;
    e = L->pData[i - 1];
    return OK;
}

Status LocateElem(SeqList L, ElemType e){
    for(int i = 0; i < L.length; i++){
        if(L.pData[i] == e)return i + 1;
    }
    return 0;
}

Status PriorElem(SeqList L, ElemType cur_e, ElemType *pre_e){
    if(!L->pData)return ERROR;
    for(int i = 1; i < L.length; i++){
        if(L.pData[i] == cur_e){
            pre_e = cur_e;
            return OK;
        }
    }
    return ERROR;
}

Status NextElem(SeqList L, ElemType cur_e, ElemType *next_e){
    if(!L.pData)
}























































