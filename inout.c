#include "ServFuncHead.h"
#include "stdlib.h"
#include "stdio.h"

Arr* Constr(const int max_x, const int max_y) {
    Arr* ptrArr = malloc(sizeof(Arr));

    if (ptrArr == NULL) {
        return NULL;
    }

    ptrArr->max_x = max_x;
    ptrArr->max_y = max_y;
    ptrArr->arr = (int*)malloc(max_y * max_x * sizeof(int));
    
    if (ptrArr->arr == NULL) {
        return NULL;
    }

    return ptrArr;
}

int ArrIn(Arr* ptrArr) {
    FILE* in = fopen("input.txt", "r");
    if (in == NULL) {
        return OPENING_FILE_ERROR;
    }
    int row = 0, col = 0, curr_char = EOF;

    while ((curr_char = getc(in)) != EOF) {
        if (row == ptrArr->max_y - 1) {
            ArrExt(ptrArr);
            if (ptrArr->arr == NULL) {
                return ALLOCATION_ERROR;
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
        return READING_FILE_ERROR;
    }

    fclose(in);
    ptrArr->max_y = row + 1;
    return 0;
}

int ArrExt(Arr* ptrArr) {
    ptrArr->max_y *= 2;
    ptrArr->arr = (int*)realloc(ptrArr->arr,
        ptrArr->max_y * ptrArr->max_x * sizeof(int));
    if (ptrArr->arr == NULL) {
        return ALLOCATION_ERROR;
    }
    return 0;
}

int ArrOut(Arr* ptrArr) {
    FILE* out = fopen("output.txt", "w");
    if (out == NULL) {
        return OPENING_FILE_ERROR;
    }
    printf("%i\n", ptrArr->max_y);
    int curr_num;
    for (int row = 0; row < ptrArr->max_y; ++row) {
        for (int col = 0; (curr_num = ptrArr->arr[ptrArr->max_x * row + col]) != '\n' && col < MAX_X; ++col) {
            unsigned char curr_char;
            if (curr_num == NON_LETTER_SYMBOL) {
                curr_char = ' ';
            }
            else {
                curr_char = curr_num;
            }
            const unsigned char res = fputc(curr_char, out);
            if (res == EOF) {
                return WRITING_FILE_ERROR;
            }
        }
        const char res = fputc('\n', out);
        if (res == EOF) {
            return WRITING_FILE_ERROR;
        }
    }

    fclose(out);
    Destr(ptrArr);
    return 0;
}

void Destr(Arr* ptrAll) {
    free(ptrAll->arr);
    free(ptrAll);
}

/*
* �����������: StrNum1 < StrNum2

* ���� ���������� ������, �� ����������� �������, ���� ������ �����
���������� 0

* ���� ������� ������1 ��������� � �������2 � �������� ������ �� ������1,
������� �� �������� ����, ��� ������ ������2 ��� ������1 ���������
�� �������2 � ��� ���� ������ ��, �� �� ������ �������
���������� 1

* ���� ������� ������1 ��������� � �������2 � �������� ������ �� ������1,
������� �� �������� ����, ��� ������ ������2 ��� ������1 ���������
�� �������2 � ��� ���� ������� ��, �� ������ �������
���������� 2
*/
int StrComp(const Arr* ptrArr, const int StrNum1, const int StrNum2) {
    int col1 = 0, col2 = 0;
    enum StrCompRes {
        SAME_STRINGS,
        FIRST_HIGHER,
        SECOND_HIGHER
    };

    while (col1 < ptrArr->max_x && col2 < ptrArr->max_x) {
        const int* Str1 = &ptrArr->arr[ptrArr->max_x * StrNum1 + col1];
        const int* Str2 = &ptrArr->arr[ptrArr->max_x * StrNum2 + col2];
        int CurrChar1 = *Str1, CurrChar2 = *Str2;
        bool small1 = 0, small2 = 0;

        SkipNonLetterSign (Str1, &col1, &CurrChar1);
        SkipNonLetterSign (Str2, &col2, &CurrChar2);

        // нам не важен случай, если обе строчки содержат маленькие или большие буквы
        // нам важно лишь отношение между этими символами
        SmallLetterCheck(&CurrChar1, &CurrChar2, &small1, &small2);

        UpperToLowerCase(&CurrChar1);
        UpperToLowerCase(&CurrChar2);

        const int HigherStrNumInt = HigherStrNum(CurrChar1, CurrChar2, &col1, &col2, small1, small2);

        switch (HigherStrNumInt) {
            case SAME_STRINGS:
            case FIRST_HIGHER:
            case SECOND_HIGHER:
                return HigherStrNumInt;

            default:
                break;
        }
    }
    return UNABLE_TO_COMPARE_STRINGS;
}

void SkipNonLetterSign (const int* StrPtr, int* col, int* CurrCharPtr) {
    const unsigned char NonLetterSigns[] = {'"', '(', ' '};
    for (int i = 0; i < sizeof(NonLetterSigns) / sizeof(unsigned char); ++i) {
        if (*StrPtr == (int)NonLetterSigns[i]) {
            ++StrPtr;
            *col += 1;
            i = 0;
        }
    }
    *CurrCharPtr = *StrPtr;
}

void SmallLetterCheck (const int* CurrCharPtr1, const int* CurrCharPtr2, bool* small1, bool* small2) {
    if (*CurrCharPtr1 == *CurrCharPtr2 - BIG_SMALL_LETTER_DIFFERENCE) {
        *small2 = 1;
    }
    else if (*CurrCharPtr2 == *CurrCharPtr1 - BIG_SMALL_LETTER_DIFFERENCE) {
        *small1 = 1;
    }
}

void UpperToLowerCase(int* CurrCharPtr) { // ошибка здесь, нужно сделать флаг, помечающий изменённый регистр символа
    if (rus_a <= *CurrCharPtr && *CurrCharPtr <= rus_r) {
        *CurrCharPtr -= BIG_SMALL_LETTER_DIFFERENCE;
    }
    else if (!(rus_A <= *CurrCharPtr && *CurrCharPtr <= rus_r)) {
        *CurrCharPtr = NON_LETTER_SYMBOL;
    }
}

int HigherStrNum(const int CurrChar1, const int CurrChar2, int* col1, int* col2,
    const bool small1, const bool small2) {
    if (CurrChar1 == CurrChar2 && small1 == 0 && small2 == 0) {
        if (CurrChar2 == NON_LETTER_SYMBOL) {
            return 0;
        }
        *col1 += 1;
        *col2 += 1;
        return -1;
    }

    if (CurrChar1 < CurrChar2 || CurrChar1 != NON_LETTER_SYMBOL && CurrChar2 == NON_LETTER_SYMBOL || small2 == 1) {
        return 1;
    }

    if (CurrChar1 > CurrChar2 || CurrChar1 == NON_LETTER_SYMBOL && CurrChar2 != NON_LETTER_SYMBOL || small1 == 1) {
        return 2;
    }
    return -1;
}

int StrSwap(Arr* ptrArr, const int StrNum1, const int StrNum2) {
    int* str = CreateArrStrCopy(ptrArr, StrNum1);
    if (str == NULL) {
        return ALLOCATION_ERROR;
    }

    PasteStrToStr(&ptrArr->arr[ptrArr->max_x * StrNum1], &ptrArr->arr[ptrArr->max_x * StrNum2]);
    PasteStrToStr(&ptrArr->arr[ptrArr->max_x * StrNum2], str);

    free(str);
    return 0;
}

/*void StrProc(Arr* ptrArr, const int StrNum1, const int StrNum2) {
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
}*/

int* CreateArrStrCopy(const Arr* ptrArr, const int StrNum) {
    assert(!(StrNum < 0 || StrNum >= ptrArr->max_y) && "Allocation error");

    int* str = malloc(sizeof(int) * ptrArr->max_x);
    if (str == NULL) {
        return NULL;
    }

    PasteStrToStr(str, &ptrArr->arr[ptrArr->max_x * StrNum]);
    return str;
}

void StrPasteToArr(const Arr* ptrArr, const int StrNum, const int* str) {
    PasteStrToStr(&ptrArr->arr[ptrArr->max_x * StrNum], str);
}

void PasteStrToStr(int* StrIntoPaste, const int* StrToPaste) {
    int curr_pos = 0;
    for (; StrToPaste[curr_pos] != '\n' && curr_pos < MAX_X - 1; ++curr_pos) {
        StrIntoPaste[curr_pos] = StrToPaste[curr_pos];
    }
    StrIntoPaste[curr_pos] = '\n';
}