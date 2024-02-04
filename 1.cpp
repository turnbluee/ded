#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int MallIn(wchar_t** a, int x, int y) {

    FILE* in;
    in = fopen("input.txt", "r");
    int c = 0, i = 0, j = 0;
    wchar_t k = fgetwc(in);

    while (k != WEOF) {
        while (k != '\n' && k != WEOF) {
            *(*a + x * i + j) = k;
            ++j;
            k = fgetwc(in);
        }

        for (; j < x; ++j) {
            *(*a + x * i + j) = '\n';
        }

        if (i == y - 1) {
            y *= 2;
            *a = (wchar_t*)realloc(*a, y * x * sizeof(wchar_t));
        }

        ++i;
        j = 0;
        k = fgetwc(in);
    }
    fclose(in);

    return i;
}

void MallSort(wchar_t** a, int x, int y) {

    for (int i = 1; i < y; ++i) {

        int count = 0, l = i - 1, j = 0;
        
        while (l >= 0 && *(*a + x * i + j) <= *(*a + x * l + j)) {

            if (*(*a + x * i + j) == *(*a + x * l + j)) {
                ++j;
            }

            if (*(*a + x * i + j) < *(*a + x * l + j) ||
                *(*a + x * i + j) == '\n' || *(*a + x * l + j) == '\n') {
                ++count;
                --l;
                j = 0;
            }
        }

        wchar_t* str = (wchar_t*)malloc((x + 1) * sizeof(wchar_t));
        for (j = 0; j < x; ++j) {
            *(str + j) = *(*a + x * i + j);
        }

        l = i;
        while (count != 0) {
            for (j = 0; j < x; ++j) {
                *(*a + x * l + j) = *(*a + x * (l - 1) + j);
            }
            --count;
            --l;
        }
        
        for (j = 0; j < x; ++j) {
            *(*a + x * l + j) = *(str + j);
        }

        free(str);
    }
}

void MallOut(wchar_t** a, int x, int y) {
    FILE* out = fopen("output.txt", "w");

    int j = 0;
    wchar_t k = '\n';
    for (int i = 0; i < y; ++i) {
        while (j < x && *(*a + x * i + j) != k) {
            fputwc(*(*a + x * i + j), out);
            ++j;
        }
        j = 0;

        if (i != y - 1) {
            putc('\n', out);
        }
    }

    fclose(out);
}

int main() {
    setlocale(LC_ALL, "");

    int y = 100, x = 100;
    wchar_t* a = (wchar_t*)malloc(y * x * sizeof(wchar_t));
    
    y = MallIn(&a, x, y);

    MallSort(&a, x, y);

    MallOut(&a, x, y);
}