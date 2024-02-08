#ifndef _HEADER_H_
#define HEADER_H_
#define _CRT_SECURE_NO_WARNINGS
#define MAX_X 100
#define ZERO 0
#define FIRST 1
#define SECOND 2
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

typedef struct {
    int max_x, max_y;
    wchar_t* arr;
} Arr;

Arr* Constr(int max_x, int max_y);

int ArrIn(Arr* ptrArr);

void ArrOut(Arr* ptrArr);

void Destr(Arr* ptrAll);

int StrComp(Arr* ptrArr, int StrNum1, int StrNum2);

void StrSwap(Arr* ptrArr, int StrNum1, int StrNum2);

void StrProc(Arr* ptrArr, int StrNum1, int StrNum2);

void ArrInsSort(Arr* ptrArr);

#endif _HEADER_H_