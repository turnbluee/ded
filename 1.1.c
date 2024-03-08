#include "ServFuncHead.h"

int main() {

    setlocale(LC_ALL, "");

    int max_y = 100;

    Arr* ptrArr = Constr(MAX_X, max_y);

    ptrArr->max_y = ArrIn(ptrArr);

    ArrInsSort(ptrArr);
    ArrOut(ptrArr);

    Destr(ptrArr);

    int a = 'А';
    printf(" %d ", a);
}