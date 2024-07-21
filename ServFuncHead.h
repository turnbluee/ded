#define _HEADER_H_
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
    int* arr;
} Arr;

Arr* Constr(int max_x, int max_y);

void ArrIn(Arr* ptrArr);

void ArrOut(Arr* ptrArr);

int CharCheck(unsigned char ch);

int ArrExt(Arr* ptrArr);

void Destr(Arr* ptrAll);