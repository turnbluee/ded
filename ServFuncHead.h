#pragma once
#define _HEADER_H_
#define _CRT_SECURE_NO_WARNINGS
#define EOL 10 // узнал только исходя из отслеживания, никак иначе не удалось
#define SPACE 32
#define rus_A 192
#define rus_R 223
#define rus_a 224
#define rus_r 255
#define NON_LETTER_SYMBOL 256
#define BIG_SMALL_LETTER_DIFFERENCE 32
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <assert.h>
#include "MainHeader.h"

typedef enum StrCompRes {
    SAME_STRINGS,
    FIRST_HIGHER,
    SECOND_HIGHER
} StrCompRes;

int ArrExt(Arr* ptrArr);

void Destr(Arr* ptrAll);

int* CreateArrStrCopy(const Arr* ptrArr, int StrNum);

int StrComp(const Arr* ptrArr, int StrNum1, int StrNum2);

int StrSwap(Arr* ptrArr, int StrNum1, int StrNum2);

void StrProc(Arr* ptrArr, int StrNum1, int StrNum2);

int StrPasteToArr(const Arr* ptrArr, int StrNum, const int* str);

void StringCopyPaste(int* StrIntoPaste, int* StrToPaste);

int PasteStrToStr(int* StrIntoPaste, const int* StrToPaste);

int SkipNonLetterSign (const int* StrPtr, int* col, int* CurrCharPtr);

//void SmallLetterCheck (const int* CurrCharPtr1, const int* CurrCharPtr2, int small1, int small2);

void UpperToLowerCase(int* CurrCharPtr);

int HigherStrNum(int CurrChar1, int CurrChar2, int* col1, int* col2);
