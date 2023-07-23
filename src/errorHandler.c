#include "errorHandler.h"

void MATRIX_ERROR_HANDLER(MATRIX_ERROR_TYPE error_type, char* functionName){
    switch (error_type)
    {
    case ALLOCATION_ERROR:
        fprintf(stderr, "ERROR Allocating Memory in Function: %s\n", functionName);
        exit(1);
        break;
    case NULL_MATRIX_ERROR:
        fprintf(stderr, "ERROR NULL MATRIX in Function: %s\n", functionName);
        exit(1);
        break;

    case INDEX_OUT_OF_BOUNDS:
        fprintf(stderr, "ERROR INDEX out of Bounds in Function: %s\n", functionName);
        exit(1);
        break;
    default:
        fprintf(stderr, "ERROR in ERROR Handler\n");
        exit(1);
        break;
    }
}