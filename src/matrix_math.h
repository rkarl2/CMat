#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "matrix.h"
#include <stdbool.h>


MATRIX MAT_addS(MATRIX a, MATRIX* c, MATRIX_TYPES scalar_type, void* scalar);

MATRIX MAT_addSU8(MATRIX a, MATRIX* c, uint8_t scalar);
MATRIX MAT_addSU16(MATRIX a, MATRIX* c, uint16_t scalar);
MATRIX MAT_addSU32(MATRIX a, MATRIX* c, uint32_t scalar);
MATRIX MAT_addSU64(MATRIX a, MATRIX* c, uint64_t scalar);
MATRIX MAT_addSI8(MATRIX a, MATRIX* c, int8_t scalar);
MATRIX MAT_addSI16(MATRIX a, MATRIX* c, int16_t scalar);
MATRIX MAT_addSI32(MATRIX a, MATRIX* c, int32_t scalar);
MATRIX MAT_addSI64(MATRIX a, MATRIX* c, int64_t scalar);
MATRIX MAT_addSF32(MATRIX a, MATRIX* c, float scalar);
MATRIX MAT_addSF64(MATRIX a, MATRIX* c, double scalar);

#endif