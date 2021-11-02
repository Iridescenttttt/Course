#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 100

typedef char* string;

Status StrInit(string *s)
{
    *s = (char*)malloc(MAXSIZE * sizeof(char));
    if(!(*s))return OVERFLOW;
    return OK;
}

Status StrAssign(string *s)
{
    printf("Please input the string.\n");
    gets(*s);
    return OK;
}

Status StrPrint(string s)
{
    for(int i = 0; s[i] != '\0'; i++){
        printf("%c", s[i]);
    }
    printf("\n");
    return OK;
}

Status ClearString(string *s)
{
    string a = NULL;
    *s = a;
    return OK;  
}

Status DestoryString(string *s)
{
    if(s){
        free(*s);
        *s = NULL;
    }
    return OK;  
}

bool StrEmpty(string s)
{
    int flag = 1;
    for(int i = 0; i < MAXSIZE; i++){
        if(s[i] != '\0'){
            flag = 0;
            break;
        }
    }
    if(flag)return true;
    else return false;
}

int StrCompare(string s, string t)
{
    for(int i = 0; ; i++){
        if(s[i] == t[i])continue;
        else if((s[i] != '\0' && t[i] == '\0') || (s[i] > t[i]))return 1;
        else return -1;
    }
    return 0;
}

int StrLength(string s)
{
    int i;
    for(i = 0; ; i++){
        if(s[i] == '\0')break;
        else continue;
    }
    return i;
}

Status SubString(string sub, string s, int pos, int len)
{
    for(int i = 0; i < len; i++){
        sub[i] = s[pos - 1];
    }
    return OK;
}

int Index(string s, string t, int pos)
{
    if(!s || !t)return -1;
    int flag = 0, i;
    for(i = pos - 1; i < StrLength(s); i++){
        int j, k = i;
        for(j = 0; j < StrLength(t); j++){
            if(s[k] == t[j]){
                k++;
                continue;
            }
            else break;
        }
        if(j == StrLength(t)){
            flag = 1;
            break;
        }
    }
    if(flag){
        return i;
    }
    return -1;
}

Status StrCopy(string t, string s)
{
    if(!t)return ERROR;
    for(int i = 0; i < StrLength(t); i++){
        s[i] = t[i];
    }
    return OK;
}

Status Concat(string t, string s1, string s2)
{
    if(!s1 || !s2)return ERROR;
    for(int i = 0; i < StrLength(s1); i++){
        t[i] = s1[i];
    }
    for(int i = 0; i < StrLength(s2); i++){
        t[i + StrLength(s1)] = s2[i];
    }
    return OK;
}

Status Replace(string *s, string t, string v)
{
    int pos;
    int tlen = StrLength(t), vlen = StrLength(v);
    while(1){
        pos = 0;
        pos = Index(*s, t, pos);
        if(pos == -1)break;
        if(tlen == vlen){                   //要替换的字符长度与原字符长度相等
            for(int i = pos, j = 0; i < pos + vlen, j < vlen; i++, j++){
                (*s)[i] = v[j];
            }
        }
        else if(tlen > vlen){               //原字符较长，先左移vlen - tlen个位置
            for(int i = pos, j = 0; i < pos + vlen, j < vlen; i++, j++){
                (*s)[i] = v[j];
            }
            for(int i = pos + vlen; i < StrLength(*s); i++){
                (*s)[i] = (*s)[i + (tlen - vlen)];
            }
            for(int i = StrLength(*s) - (tlen - vlen) + 1; i < StrLength(*s); i++){
                (*s)[i] = '\0';
            }
        }
        else if(tlen < vlen){
            for(int i = StrLength(*s) + (vlen - tlen) - 1; i > pos + (vlen - tlen) - 1; i--){
                (*s)[i] = (*s)[i - (vlen - tlen)];
            }
            for(int i = pos, j = 0; i < pos + vlen, j < vlen; i++, j++){
                (*s)[i] = v[j];
            }
        }
        pos += tlen;    
    }
    return OK;
}