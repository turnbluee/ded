#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int MallIn(char** a, int x, int y) {

    FILE* in;
    in = fopen("input.txt", "r");
    int c = 0, i = 0, j = 0;
    char k = fgetc(in);

    while (k != EOF) {
        while (k != '\n' && k != EOF) {
            *(*a + x * i + j) = k;
            ++j;
            k = fgetc(in);
        }

        for (; j < x; ++j) {
            *(*a + x * i + j) = '\n';
        }

        if (i == y - 1) {
            y *= 2;
            *a = (char*)realloc(*a, y * x);
        }

        ++i;
        j = 0;
        k = fgetc(in);
    }
    fclose(in);

    return i;
}

void MallSort(char** a, int x, int y) {

    for (int i = 1; i < y; ++i) {

        int count = 0, l = i - 1, j = 0;
        
        while (*(*a + x * i + j) <= *(*a + x * l + j) && l >= 0) {

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

        char* str = (char*)malloc(x + 1);
        for (j = 0; j < x; ++j) {
            *(str + j) = *(*a + x * i + j);
        }
        
        char* cur_str = (char*)malloc(x);


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



/*

A
AA
AB
*/

void MallOut(char** a, int x, int y) {
    FILE* out = fopen("output.txt", "w");

    int j = 0;
    char k = '\n';
    for (int i = 0; i < y; ++i) {
        while (j < x && *(*a + x * i + j) != k) {
            putc(*(*a + x * i + j), out);
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

    std::setlocale(LC_ALL, "RU");
    
    int y = 100, x = 100;
    char* a;
    a = (char*)malloc(y * x);
    
    y = MallIn(&a, x, y);

    MallSort(&a, x, y);

    MallOut(&a, x, y);
}