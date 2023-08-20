#include "errorHandler.h"

void MATRIX_ERROR_HANDLER(MATRIX_ERROR_TYPE error_type, const char* functionName){
    switch (error_type)
    {
    case ALLOCATION_ERROR:
        fprintf(stderr, "ERROR Allocating Memory in Function: %s\n", functionName);
        exit(1);
        break;
    case NULL_POINTER_ERROR:
        fprintf(stderr, "ERROR NULL MATRIX in Function: %s\n", functionName);
        exit(1);
        break;

    case INDEX_OUT_OF_BOUNDS:
        fprintf(stderr, "ERROR INDEX out of Bounds in Function: %s\n", functionName);
        exit(1);
        break;
    case INVALID_DIM_ERROR:
        fprintf(stderr, "ERROR Incompatable Dimensions in Function: %s\n", functionName);
        exit(1);
        break;
    case NON_DEFINED_OPERATION_ERROR:
        fprintf(stderr, "ERROR Undefined Operations in Function: %s\n", functionName);
        exit(1);
        break;
    default:
        fprintf(stderr, "ERROR in ERROR Handler\n");
        exit(1);
        break;
    }
}