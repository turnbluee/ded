#include "ServFuncHead.h"

int main() {

    setlocale(LC_ALL, ".1251");

    int max_y = 100;

    Arr* ptrArr = Constr(MAX_X, max_y);

    ptrArr->max_y = ArrIn(ptrArr);

    if (ptrArr->max_y < 0) {
        return -1488;
    }

    ArrOut(ptrArr);
}