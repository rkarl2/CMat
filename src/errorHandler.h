#ifndef MATRIX_ERROR_H
#define MATRIX_ERROR_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    ALLOCATION_ERROR,
    NULL_POINTER_ERROR,
    INDEX_OUT_OF_BOUNDS,
    INVALID_DIM_ERROR,
    NON_DEFINED_OPERATION_ERROR
}MATRIX_ERROR_TYPE;

void MATRIX_ERROR_HANDLER(MATRIX_ERROR_TYPE error_type, const char* functionName);

#endif