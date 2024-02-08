#include "Header.h"

int main() {

    setlocale(LC_ALL, "");

    int max_y = 100;

    Arr* ptrArr = Constr(MAX_X, max_y);

    ptrArr->max_y = ArrIn(ptrArr);

    //ArrInsSort(ptrArr);
    StrProc(ptrArr, 2, 3);
    ArrOut(ptrArr);

    Destr(ptrArr);
}