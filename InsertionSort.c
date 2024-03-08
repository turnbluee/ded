#include "ServFuncHead.h"

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

        wchar_t* str = (wchar_t*)malloc((ptrArr->max_x + 1) * sizeof(wchar_t));
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
        int count = 0, StrNumPrev = StrNumNow - 1, j = 0;

        while (StrNumPrev >= 0) {
            if (StrComp(ptrArr, StrNumPrev, StrNumNow) == 2) {
                ++count;
                --StrNumPrev;
            }
            else if (StrComp(ptrArr, StrNumPrev, StrNumNow) == 1 ||
                StrComp(ptrArr, StrNumPrev, StrNumNow) == 0) {
                break;
            }
        }

        wchar_t* str = StrCopy(ptrArr, StrNumNow);

        for (int i = 0; i < count; ++i) {
            StrSwap(ptrArr, StrNumNow - i, StrNumNow - i - 1);
        }

        StrPaste(ptrArr, StrNumPrev, &str);
    }
}