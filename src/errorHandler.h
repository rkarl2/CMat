#ifndef MATRIX_ERROR_H
#define MATRIX_ERROR_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    ALLOCATION_ERROR,
    NULL_MATRIX_ERROR,
    INDEX_OUT_OF_BOUNDS
}MATRIX_ERROR_TYPE;

void MATRIX_ERROR_HANDLER(MATRIX_ERROR_TYPE error_type, char* functionName);

#endif