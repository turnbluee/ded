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

int ArrIn(Arr* ptrArr) {
    FILE* in;
    in = fopen("input.txt", "r");
    if (in == NULL) {
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
        ptrArr->arr[ptrArr->max_x * row + col] = '\n';
        printf("End of file\n");
    }
    else if (ferror(in)) {
        printf("Reading file error, str36\n");
        return -2;
    }

    fclose(in);
    ptrArr->max_y = row + 1;
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

void ArrOut(Arr* ptrArr) {
    FILE* out = fopen("output.txt", "wb");
    printf("%i\n", ptrArr->max_y);
    int curr_num;
    for (int row = 0; row < ptrArr->max_y; ++row) {
        for (int col = 0; (curr_num = ptrArr->arr[ptrArr->max_x * row + col]) != '\n' && col < MAX_X; ++col) {
            unsigned char curr_char;
            if (curr_num == 256) {
                curr_char = ' ';
            }
            else {
               curr_char = curr_num;
            }
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
    int col1 = 0, col2 = 0;

    while (1) {
        float Str1 = ptrArr->arr[ptrArr->max_x * StrNum1 + col1];
        float Str2 = ptrArr->arr[ptrArr->max_x * StrNum2 + col2];
        
        if ((Str1 == '"' || Str1 == '(') && col1 == 0) {
            ++col1;
            Str1 = ptrArr->arr[ptrArr->max_x * StrNum1 + col1];
        }

        if (rus_A <= Str1 && Str1 <= rus_R) {
            Str1 -= 0.5;
        }
        else if (rus_a <= Str1 && Str1 <= rus_r) {
            Str1 -= 32;
        }
        else if (!(rus_A <= Str1 && Str1 <= rus_r)) {
            Str1 = 256;
        }
        
        
        if ((Str2 == '"' || Str2 == '(') && col2 == 0) {
            ++col2;
            Str2 = ptrArr->arr[ptrArr->max_x * StrNum2 + col2];
        }
        
        if (rus_A <= Str2 && Str2 <= rus_R) {
            Str2 -= 0.5;
        }
        else if (rus_a <= Str2 && Str2 <= rus_r) {
            Str2 -= 32;
        }
        else if (!(rus_A <= Str2 && Str2 <= rus_r)) {
            Str2 = 256;
        }

        if (Str1 == Str2) {
            if (Str2 == 256) {
                return 0;
            }
            ++col1;
            ++col2;
        }

        if (Str1 < Str2 || Str1 != 256 && Str2 == 256) {
            return 1;
        }

        if (Str1 > Str2 || Str1 == 256 && Str2 != 256) {
            return 2;
        }
    }
}

void StrSwap(Arr* ptrArr, int StrNum1, int StrNum2) {
    int curr_pos = 0, col = 0;
    int* str = StrCopy(ptrArr, StrNum1);

    while (ptrArr->arr[ptrArr->max_x * StrNum2 + col] != '\n' && col < MAX_X) {
        ptrArr->arr[ptrArr->max_x * StrNum1 + col] = ptrArr->arr[ptrArr->max_x * StrNum2 + col];
        ++col;
    }
    ptrArr->arr[ptrArr->max_x * StrNum1 + col] = '\n';

    while (*(str + curr_pos) != '\n') {
        ptrArr->arr[ptrArr->max_x * StrNum2 + curr_pos] = *(str + curr_pos);
        ++curr_pos;
    }
    ptrArr->arr[ptrArr->max_x * StrNum2 + curr_pos] = '\n';

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

int* StrCopy(Arr* ptrArr, int StrNum) {

    if (StrNum < 0 || StrNum >= ptrArr->max_y) {
        return NULL;
    }

    int curr_pos = 0;
    int* str = (int*)malloc(sizeof(int) * ptrArr->max_x);
    if (str == NULL) {
        return NULL;
    }

    while (ptrArr->arr[ptrArr->max_x * StrNum + curr_pos] != '\n' && curr_pos < ptrArr->max_x - 1) {
        str[curr_pos] = ptrArr->arr[ptrArr->max_x * StrNum + curr_pos];
        ++curr_pos;
    }
    str[curr_pos] = '\n';

    return str;
}

void StrPaste(Arr* ptrArr, int StrNum, int* str) {
    int curr_pos = 0;
    while (str[curr_pos] != '\n' && curr_pos < ptrArr->max_x - 1) {
        ptrArr->arr[ptrArr->max_x * StrNum + curr_pos] = str[curr_pos];
        ++curr_pos;
    }
    ptrArr->arr[ptrArr->max_x * StrNum + curr_pos] = '\n';
}