#ifndef MATRIX_H
#define MATRIX_H
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    U8 = 0, U16, U32, U64,
    I8, I16, I32, I64,
    F32, F64
}MATRIX_TYPES;

typedef struct {
    uint32_t* shape;
    uint8_t num_dim;
    uint64_t size;
}DIMENSION;

typedef union {
    uint8_t* U8;
    uint16_t* U16;
    uint32_t* U32;
    uint64_t* U64;
    int8_t* I8;
    int16_t* I16;
    int32_t* I32;
    int64_t* I64;
    float* F32;
    double* F64;
}MATRIX_STORAGE;

typedef struct {
    MATRIX_STORAGE data;
    DIMENSION dim;
    MATRIX_TYPES type;
}MATRIX;

#endif