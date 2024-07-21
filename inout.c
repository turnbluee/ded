#include "ServFuncHead.h"

Arr* Constr(int max_x, int max_y) {
    Arr* ptrArr = (Arr*)malloc(sizeof(Arr));

    if (!ptrArr) {
        printf("Allocate error, ServFunc str7");
        return NULL;
    }

    ptrArr->max_x = max_x;
    ptrArr->max_y = max_y;
    ptrArr->arr = (int*)malloc(max_y * max_x * sizeof(int));
    
    if (!ptrArr->arr) {
        printf("Allocate error, ServFunc str15");
        return NULL;
    }

    return ptrArr;
}

int ArrIn(Arr* ptrArr) {
    FILE* in;
    in = fopen("input.txt", "r");
    if(in == NULL)
    {
        printf("Error occured while opening input.txt");
        return 1;
    }
    int row = 0, col = 0, curr_char = 0;

    while ((curr_char = getc(in)) != EOF) {
        if (row == ptrArr->max_y - 1) {
            int res = ArrExt(ptrArr);
            if (res == -1) {
                return -1;
            }
        }

        ptrArr->arr[ptrArr->max_x * row + col] = curr_char;
        ++col;

        if (curr_char == '\n') {
            col = 0;
            ++row;
        }
    }

    if (feof(in)) {
        printf("End of file");
    }
    else if (ferror(in)) {
        printf("Reading file error, str36");
        return -2;
    }

    fclose(in);
    return row;
}

int ArrExt(Arr* ptrArr) {
    ptrArr->max_y *= 2;
    ptrArr->arr = (int*)realloc(ptrArr->arr,
        ptrArr->max_y * ptrArr->max_x * sizeof(int));
    if (ptrArr->arr == NULL) {
        printf("Reallocation error");
        return -1;
    }
    return 0;
}

int CharCheck(unsigned char ch) {
    if ('À' < (int) ch && (int) ch < 'ÿ' || (int) ch == ' ') {
        return 1;
    }
    else {
        return 0;
    }
}

void ArrOut(Arr* ptrArr) {
    FILE* out = fopen("output.txt", "wb");
    printf("%i", ptrArr->max_y);
    for (int row = 0; row < ptrArr->max_y; ++row) {
        int col = 0;
        while (col < ptrArr->max_x && ptrArr->arr[ptrArr->max_x * row + col] != '\n') {
            int curr_num = ptrArr->arr[ptrArr->max_x * row + col];
            unsigned char curr_char = (char)curr_num;
            fputc(curr_num, out);
            ++col;
            fputc(col, out);
        }

        if (row != ptrArr->max_y - 1) {
            fputc('\n', out);
        }
    }

    fclose(out);
    Destr(ptrArr);
}

void Destr(Arr* ptrAll) {
    free(ptrAll->arr);
    free(ptrAll);
}
