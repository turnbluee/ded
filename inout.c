#include "ServFuncHead.h"

Arr* Constr(int max_x, int max_y) {
    Arr* ptrArr = (Arr*)malloc(sizeof(Arr));

    if (ptrArr == NULL) {
        printf("Allocate error, ServFunc str7\n");
        return NULL;
    }

    ptrArr->max_x = max_x;
    ptrArr->max_y = max_y;
    ptrArr->arr = (int*)malloc(max_y * max_x * sizeof(int));
    
    if (ptrArr->arr == NULL) {
        printf("Allocate error, ServFunc str15\n");
        return NULL;
    }

    return ptrArr;
}

void ArrIn(Arr* ptrArr) {
    FILE* in;
    in = fopen("input.txt", "r");
    if(in == NULL) {
        printf("Error occured while opening input.txt\n");
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
        printf("End of file\n");
    }
    else if (ferror(in)) {
        printf("Reading file error, str36\n");
        return -2;
    }

    fclose(in);
    ptrArr->max_y = row;
}

int ArrExt(Arr* ptrArr) {
    ptrArr->max_y *= 2;
    ptrArr->arr = (int*)realloc(ptrArr->arr,
        ptrArr->max_y * ptrArr->max_x * sizeof(int));
    if (ptrArr->arr == NULL) {
        printf("Reallocation error\n");
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
    printf("%i\n", ptrArr->max_y);
    int curr_num;
    for (int row = 0; row < ptrArr->max_y; ++row) {
        for (int col = 0; (curr_num = ptrArr->arr[ptrArr->max_x * row + col]) != '\n'; ++col) {
            unsigned char curr_char = (char)curr_num;
            fputc(curr_char, out);
        }
        fputc('\n', out);
    }

    fclose(out);
    Destr(ptrArr);
}

void Destr(Arr* ptrAll) {
    free(ptrAll->arr);
    free(ptrAll);
}
