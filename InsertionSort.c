#include "ServFuncHead.h"
/*
void ArrInsSort1(Arr* ptrArr) {

    for (int i = 1; i < ptrArr->max_y; ++i) {

        int count = 0, l = i - 1, j = 0;

        while (l >= 0 && ptrArr->arr[ptrArr->max_x * i + j] <= ptrArr->arr[ptrArr->max_x * l + j]) {

            if (ptrArr->arr[ptrArr->max_x * i + j] != '\0' && ptrArr->arr[ptrArr->max_x * l + j] == '\0') {
                break;
            }

            if (ptrArr->arr[ptrArr->max_x * i + j] == ptrArr->arr[ptrArr->max_x * l + j]) {
                ++j;
            }

            if (ptrArr->arr[ptrArr->max_x * i + j] < ptrArr->arr[ptrArr->max_x * l + j] ||
                ptrArr->arr[ptrArr->max_x * i + j] == '\0' && ptrArr->arr[ptrArr->max_x * l + j] != '\0') {
                ++count;
                --l;
                j = 0;
            }
        }
        j = 0;

        char* str = (char*)malloc((ptrArr->max_x + 1) * sizeof(char));
        while (ptrArr->arr[ptrArr->max_x * i + j] != '\0') {
            *(str + j) = ptrArr->arr[ptrArr->max_x * i + j];
            ++j;
        }
        *(str + j) = '\0';

        l = i;
        j = 0;
        while (count != 0) {
            while (ptrArr->arr[ptrArr->max_x * l + j] != '\0') {
                ptrArr->arr[ptrArr->max_x * l + j] = '\0';
                ++j;
            }
            j = 0;

            while (ptrArr->arr[ptrArr->max_x * (l - 1) + j] != '\0') {
                ptrArr->arr[ptrArr->max_x * l + j] = ptrArr->arr[ptrArr->max_x * (l - 1) + j];
                ++j;
            }
            ptrArr->arr[ptrArr->max_x * l + j] = '\0';

            --count;
            --l;
        }

        j = 0;
        while (*(str + j) != '\0') {
            ptrArr->arr[ptrArr->max_x * l + j] = *(str + j);
            ++j;
        }
        ptrArr->arr[ptrArr->max_x * l + j] = '\0';

        free(str);
    }
}

void ArrInsSort(Arr* ptrArr) {
    for (int StrNumNow = 1; StrNumNow < ptrArr->max_y; ++StrNumNow){
        int count = 0, StrNumPrev = StrNumNow - 1;

        while (StrNumPrev >= 0) {
            int res = StrComp(ptrArr, StrNumPrev, StrNumNow);
            if (res == 2) {
                ++count;
                --StrNumPrev;
            }
            else if (res == 1 || res == 0) {
                break;
            }
        }
        ++StrNumPrev;

        if (count > 0) {
            int* curr_str = StrCopy(ptrArr, StrNumNow);

            for (int StrsBehindCurr = 0; StrsBehindCurr < count; ++StrsBehindCurr) {
                StrSwap(ptrArr, StrNumNow - StrsBehindCurr, StrNumNow - StrsBehindCurr - 1);
            }

            StrPaste(ptrArr, StrNumNow, curr_str);

            free(curr_str);
        }
    }
}
*/


int ArrInsSort(Arr* ptrArr) {
    for (int StrNumNow = 1; StrNumNow < ptrArr->max_y; ++StrNumNow){
        int count = 0, StrNumPrev = StrNumNow - 1, HigherStrNumInt = 2;
        while (StrNumPrev >= 0 && HigherStrNumInt == 2) {
            HigherStrNumInt = StrComp(ptrArr, StrNumPrev, StrNumNow);
            switch (HigherStrNumInt) {
            case FIRST_HIGHER:
            case SAME_STRINGS:
            break;

            case SECOND_HIGHER: {
                ++count;
                --StrNumPrev;
                break;
            }

            case UNABLE_TO_COMPARE_STRINGS:
                return UNABLE_TO_COMPARE_STRINGS;

            case UNABLE_TO_PROCESS_STRING:
                return UNABLE_TO_PROCESS_STRING;
            }
        }
        ++StrNumPrev;

        if (count > 0) {
            int* StrNow = CreateArrStrCopy(ptrArr, StrNumNow);
            if (StrNow == NULL) {
                return ALLOCATION_ERROR;
            }

            for (int StrsBehindCurr = 0; StrsBehindCurr < count; ++StrsBehindCurr) {
                const int* StrToPaste = CreateArrStrCopy(ptrArr, StrNumNow - StrsBehindCurr - 1);
                if (StrToPaste == NULL) {
                    return ALLOCATION_ERROR;
                }
                StrPasteToArr(ptrArr, StrNumNow - StrsBehindCurr, StrToPaste);
            }

            StrPasteToArr(ptrArr, StrNumNow - count, StrNow);
            free(StrNow);
        }
    }
    return 0;
}