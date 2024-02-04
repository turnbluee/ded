#define _CRT_SECURE_NO_WARNINGS
#define MAX_X 100
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

typedef struct {
    int max_x, max_y;
    wchar_t* arr;
} Arr;

Arr* Constr(int max_x, int max_y) {
    Arr* ptrArr = (Arr*)malloc(sizeof(Arr));
    
    ptrArr->max_x = max_x;
    ptrArr->max_y = max_y;
    ptrArr->arr = (wchar_t*)malloc(max_y * max_x * sizeof(wchar_t));;

    return ptrArr;
}

void Destr(Arr* ptrAll) {
    free(ptrAll->arr);
    free(ptrAll);
}

int MallIn(Arr *ptrArr) {

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

        for (; j < ptrArr->max_x; ++j) {
            ptrArr->arr[ptrArr->max_x * i + j] = '\n';
        }

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

void MallSort(Arr* ptrArr) {

    for (int i = 1; i < ptrArr->max_y; ++i) {

        int count = 0, l = i - 1, j = 0;

        while (l >= 0 && ptrArr->arr[ptrArr->max_x * i + j] <= ptrArr->arr[ptrArr->max_x * l + j]) {

            if (ptrArr->arr[ptrArr->max_x * i + j] == ptrArr->arr[ptrArr->max_x * l + j]) {
                ++j;
            }

            if (ptrArr->arr[ptrArr->max_x * i + j] < ptrArr->arr[ptrArr->max_x * l + j] ||
                ptrArr->arr[ptrArr->max_x * i + j] == '\n' || ptrArr->arr[ptrArr->max_x * l + j] == '\n') {
                ++count;
                --l;
                j = 0;
            }
        }

        wchar_t* str = (wchar_t*)malloc((ptrArr->max_x + 1) * sizeof(wchar_t));
        for (j = 0; j < ptrArr->max_x; ++j) {
            *(str + j) = ptrArr->arr[ptrArr->max_x * i + j];
        }

        l = i;
        while (count != 0) {
            for (j = 0; j < ptrArr->max_x; ++j) {
                ptrArr->arr[ptrArr->max_x * l + j] = ptrArr->arr[ptrArr->max_x * (l - 1) + j];
            }
            --count;
            --l;
        }

        for (j = 0; j < ptrArr->max_x; ++j) {
            ptrArr->arr[ptrArr->max_x * l + j] = *(str + j);
        }

        free(str);
    }
}

void MallOut(Arr* ptrArr) {
    FILE* out = fopen("output.txt", "w");

    int j = 0;
    wchar_t k = '\n';
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

int main() {

    setlocale(LC_ALL, "");

    int max_y = 100;

    Arr* ptrArr = Constr(MAX_X, max_y);

    max_y = MallIn(ptrArr);

    MallSort(ptrArr);

    MallOut(ptrArr);

    Destr(ptrArr);
}