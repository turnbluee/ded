﻿#include "ServFuncHead.h"

Arr* Constr(int max_x, int max_y) {
    Arr* ptrArr = (Arr*)malloc(sizeof(Arr));

    ptrArr->max_x = max_x;
    ptrArr->max_y = max_y;
    ptrArr->arr = (wchar_t*)malloc(max_y * max_x * sizeof(wchar_t));;

    return ptrArr;
}

int ArrIn(Arr* ptrArr) {

    FILE* in;
    in = fopen("input.txt", "r");
    int c = 0, i = 0, j = 0;
    wchar_t k = fgetwc(in);


    while (k != WEOF) {
        while (k != '\n' && k != WEOF) {
            ptrArr->arr[ptrArr->max_x * i + j] = k;
            ++j;
            k = fgetwc(in);
        }

        ptrArr->arr[ptrArr->max_x * i + j] = '\0';

        if (i == ptrArr->max_y - 1) {
            ptrArr->max_y *= 2;
            ptrArr->arr = (wchar_t*)realloc(ptrArr->arr, ptrArr->max_y * ptrArr->max_x * sizeof(wchar_t));
        }

        ++i;
        j = 0;
        k = fgetwc(in);
    }
    fclose(in);

    return i;
}

void ArrOut(Arr* ptrArr) {
    FILE* out = fopen("output.txt", "w");

    int j = 0;
    wchar_t k = '\0';
    for (int i = 0; i < ptrArr->max_y; ++i) {
        while (j < ptrArr->max_x && ptrArr->arr[ptrArr->max_x * i + j] != k) {
            fputwc(ptrArr->arr[ptrArr->max_x * i + j], out);
            ++j;
        }
        j = 0;

        if (i != ptrArr->max_y - 1) {
            putc('\n', out);
        }
    }

    fclose(out);
}

void Destr(Arr* ptrAll) {
    free(ptrAll->arr);
    free(ptrAll);
}

wchar_t* StrCopy(Arr* ptrArr, int StrNum) {

    if (StrNum < 0 || StrNum >= ptrArr->max_y) {
        return NULL;
    }

    int i = 0;
    wchar_t* str = (wchar_t*)malloc(sizeof(wchar_t) * ptrArr->max_x);
    if (str == NULL) {
        return NULL;
    }

    while (ptrArr->arr[ptrArr->max_x * StrNum + i] != '\0' && i < ptrArr->max_x - 1) {
        str[i] = ptrArr->arr[ptrArr->max_x * StrNum + i];
        ++i;
    }
    str[i] = '\0';
    
    return str;
}

/* 
* ОГРАНИЧЕНИЕ: StrNum1 < StrNum2 

* если одинаковый символ, то увеличиваем позицию, если строки равны
возвращаем 0

* если символы строки1 совпадают с строкой2 и встречен символ из строки1,
стоящий по алфавиту ВЫШЕ, чем символ строки2 или строка1 совпадает
со строкой2 и при этом КОРОЧЕ неё, то НЕ МЕНЯЕМ местами
возвращаем 1

* если символы строки1 совпадают с строкой2 и встречен символ из строки1,
стоящий по алфавиту НИЖЕ, чем символ строки2 или строка1 совпадает
со строкой2 и при этом ДЛИННЕЕ неё, то МЕНЯЕМ местами
возвращаем 2
*/
int StrComp(Arr* ptrArr, int StrNum1, int StrNum2) {
    int j = 0;

    while (1) {
        wchar_t Str1 = ptrArr->arr[ptrArr->max_x * StrNum1 + j];
        wchar_t Str2 = ptrArr->arr[ptrArr->max_x * StrNum2 + j];

        if ('А' < Str1 && Str1 < 'Я')
        {
            Str1 += 32;
        }

        if ('А' < Str2 && Str2 < 'Я')
        {
            Str2 += 32;
        }

        if (Str1 == Str2) {
            if (Str1 == '\0' && Str2 == '\0') {
                return 0;
            }
            ++j;
        }

        if (Str1 < Str2 || Str1 == '\0' && Str2 != '\0') {
            return 1;
        }

        if (Str1 > Str2 || Str1 != '\0' && Str2 == '\0') {
            return 2;
        }
    }
}

void StrSwap(Arr* ptrArr, int StrNum1, int StrNum2) {
    int i = 0, j = 0;
    wchar_t* str = StrCopy(ptrArr, StrNum1);

    while (ptrArr->arr[ptrArr->max_x * StrNum2 + j] != '\0') {
        ptrArr->arr[ptrArr->max_x * StrNum1 + j] = ptrArr->arr[ptrArr->max_x * StrNum2 + j];
        ++j;
    }
    ptrArr->arr[ptrArr->max_x * StrNum1 + j] = '\0';

    while (*(str + i) != '\0') {
        ptrArr->arr[ptrArr->max_x * StrNum2 + i] = *(str + i);
        ++i;
    }
    ptrArr->arr[ptrArr->max_x * StrNum2 + i] = '\0';

    free(str);
}

void StrProc(Arr* ptrArr, int StrNum1, int StrNum2) {

    if (StrComp(ptrArr, StrNum1, StrNum2) == ZERO) {
        printf("%s", "Same lines");
    }
    else if (StrComp(ptrArr, StrNum1, StrNum2) == FIRST) {
        printf("%s", "First line is higher");
    }
    else if (StrComp(ptrArr, StrNum1, StrNum2) == SECOND) {
        StrSwap(ptrArr, StrNum1, StrNum2);
        printf("%s", "Second line is higher");
    }
}

void StrPaste(Arr* ptrArr, int StrNum, wchar_t *str) {
    int i = 0;
    while (str[i] != '\0' && i < ptrArr->max_x - 1) {
        ptrArr->arr[ptrArr->max_x * StrNum + i] = str[i];
        ++i;
    }
    ptrArr->arr[ptrArr->max_x * StrNum + i] = '\0';
}