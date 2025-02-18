#define MAX_X 100
#define MAX_Y 100
#include <locale.h>
#include <stdio.h>

typedef struct {
    int max_x, max_y;
    int* arr;
} Arr;

enum ErrorCodes {
    INDEX_OUT_OF_RANGE = 1,
    ALLOCATION_ERROR,
    REALLOCATION_ERROR,
    READING_FILE_ERROR,
    OPENING_FILE_ERROR,
    WRITING_FILE_ERROR,
    UNABLE_TO_COMPARE_STRINGS,
    WRONG_STR_SIZE,
    UNABLE_TO_PROCESS_STRING
};

extern const char* ErrorNames[];

Arr* Constr(int max_x, int max_y);

int ArrIn(Arr* ptrArr);

int ArrInsSort(Arr* ptrArr);

int ArrOut(Arr* ptrArr);