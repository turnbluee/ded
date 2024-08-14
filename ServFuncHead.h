#pragma once
#define _HEADER_H_
#define _CRT_SECURE_NO_WARNINGS
#define MAX_X 100
#define MAX_Y 100
#define EOL 10 // узнал только исходя из отслеживания, никак иначе не удалось
#define SPACE 32
#define rus_A 192
#define rus_R 223
#define rus_a 224
#define rus_r 255
#define NON_LETTER_SYMBOL 256
#define BIG_SMALL_LETTER_DIFFERENCE 32
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
    int max_x, max_y;
    int* arr;
} Arr;

enum ErrorCodes {
    INDEX_OUT_OF_RANGE = 1,
    ALLOCATION_ERROR,
    REALLOCATION_ERROR,
    READING_FILE_ERROR,
    OPENING_FILE_ERROR,
    WRITING_FILE_ERROR,
    UNABLE_TO_COMPARE_STRINGS
};

extern const char* ErrorNames[];

Arr* Constr(int max_x, int max_y);

int ArrIn(Arr* ptrArr);

int ArrOut(Arr* ptrArr);

int ArrExt(Arr* ptrArr);

void Destr(Arr* ptrAll);

int* CreateArrStrCopy(const Arr* ptrArr, int StrNum);

int StrComp(const Arr* ptrArr, int StrNum1, int StrNum2);

int StrSwap(Arr* ptrArr, int StrNum1, int StrNum2);

void StrProc(Arr* ptrArr, int StrNum1, int StrNum2);

void StrPasteToArr(const Arr* ptrArr, int StrNum, const int* str);

int ArrInsSort(Arr* ptrArr);

void StringCopyPaste(int* StrIntoPaste, int* StrToPaste);

void PasteStrToStr(int* StrIntoPaste, const int* StrToPaste);

void SkipNonLetterSign (const int* StrPtr, int* col, int* CurrCharPtr);

void SmallLetterCheck (const int* CurrCharPtr1, const int* CurrCharPtr2, bool* small1, bool* small2);

void UpperToLowerCase(int* CurrCharPtr);

int HigherStrNum(int CurrChar1, int CurrChar2, int* col1, int* col2, bool small1, bool small2);
