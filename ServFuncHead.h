﻿#define _HEADER_H_
#define _CRT_SECURE_NO_WARNINGS
#define MAX_X 100
#define ZERO 0
#define FIRST 1
#define SECOND 2
#define EOL 10 // узнал только исходя из отслеживания, никак иначе не удалось
#define SPACE 32
#define rus_A 192
#define rus_R 223
#define rus_a 224
#define rus_r 255
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>

typedef struct {
    int max_x, max_y;
    int* arr;
} Arr;

enum ErrorCodes {
    INDEX_OUT_OF_RANGE = 1,
    ALLOCATION_ERROR,
    REALLOCATION_ERROR,
    READING_FILE_ERROR
};

extern const char* ErrorNames[];

Arr* Constr(int max_x, int max_Sy);

void ArrIn(Arr* ptrArr);

void ArrOut(Arr* ptrArr);

void ArrExt(Arr* ptrArr);

void Destr(Arr* ptrAll);

int* StrCopy(Arr* ptrArr, int StrNum);

int StrComp(Arr* ptrArr, int StrNum1, int StrNum2);

void StrSwap(Arr* ptrArr, int StrNum1, int StrNum2);

void StrProc(Arr* ptrArr, int StrNum1, int StrNum2);

void StrPaste(Arr* ptrArr, int StrNum, int* str);

void ArrInsSort(Arr* ptrArr);

void ErrorProc (int ErrorCode);