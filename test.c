#include "ServFuncHead.h"
    const char* ErrorNames[] = {
    "Index Out Of Range",
    "Allocation Error",
    "Reallocation Error",
    "Reading File Error",
    "Open File Error"
    };

int main() {

    setlocale(LC_ALL, ".1251");


    int max_y = 100;

    Arr* ptrArr = Constr(MAX_X, max_y);

    ArrIn(ptrArr);

    ArrInsSort(ptrArr);

    ArrOut(ptrArr);
}