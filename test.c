#include "MainHeader.h"
const char* ErrorNames[] = {
    "Index Out Of Range",
    "Allocation Error",
    "Reallocation Error",
    "Reading File Error",
    "Opening File Error",
    "Writing File Error",
    "Unable To Compare Strings"
};

int main() {

    setlocale(LC_ALL, ".1251");

    Arr* ptrArr = Constr(MAX_X, MAX_Y);
    if (ptrArr == NULL || ptrArr->arr == NULL) {
        printf("%s\n%s%i", "Allocation error", "Error code: ", ALLOCATION_ERROR);
        return ALLOCATION_ERROR;
    }

    int res = ArrIn(ptrArr);
    switch (res) {
        case 0:
            break;
        default:
            printf("%s\n%s%i", ErrorNames[res - 1], "Error code: ", res);
            return res;
    }

    res = ArrInsSort(ptrArr);
    switch (res) {
        case 0:
            break;
        default:
            printf("%s\n%s%i", ErrorNames[res - 1], "Error code: ", res);
        return res;
    }

    res = ArrOut(ptrArr);
    switch (res) {
        case 0:
            break;
        default:
            printf("%s\n%s%i", ErrorNames[res - 1], "Error code: ", res);
        return res;
    }
}