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
            int* StrNow = StrCopy(ptrArr, StrNumNow);

            for (int StrsBehindCurr = 0; StrsBehindCurr < count; ++StrsBehindCurr) {
                int* StrToPaste = StrCopy(ptrArr, StrNumNow - StrsBehindCurr - 1);
                StrPaste(ptrArr, StrNumNow - StrsBehindCurr, StrToPaste);
            }

            StrPaste(ptrArr, StrNumNow - count, StrNow);

            free(StrNow);
        }
    }
}

// void ArrBubbleSort(Arr* ptrArr) {
//     for (int counter)
// }