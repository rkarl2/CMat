#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "matrix.h"
#include "iterators.h"
#include <stdbool.h>


typedef enum{
    MAT_incomatiableDim = 0,
    MAT_compatableMatrix = 1,
    MAT_useIters = 2
}MAT_dimCompatabilies;

bool MAT_compareDims(const DIMENSION* a, const DIMENSION* b);
MAT_dimCompatabilies MAT_determineIters(const DIMENSION* a, const DIMENSION* b, MATRIX* dst, 
                                        MAT_iterator* iterA, MAT_iterator* iterB, MAT_iterator* iterDst);

MATRIX_TYPES MAT_determineOutputType(MATRIX_TYPES a, MATRIX_TYPES b);

MATRIX MAT_elementwiseOP(MATRIX* a, MATRIX* b, MATRIX* dst, void* (*operation) (void*, void*, MATRIX_TYPES, MATRIX_TYPES, MATRIX_TYPES));

MATRIX MAT_elementwiseOPfromITER(MATRIX* a, MATRIX* b, MATRIX* dst, 
                                 void* (*operation) (void*, void*, MATRIX_TYPES, MATRIX_TYPES, MATRIX_TYPES),
                                 MAT_iterator* iterA, MAT_iterator* iterB, MAT_iterator* iterDst);

MATRIX MAT_add(MATRIX* a, MATRIX* b, MATRIX* dst);

MATRIX MAT_sub(MATRIX* a, MATRIX* b, MATRIX* dst);

MATRIX MAT_divide(MATRIX* a, MATRIX* b, MATRIX* dst);

MATRIX MAT_multiply(MATRIX* a, MATRIX* b, MATRIX* dst);


#endif