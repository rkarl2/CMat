#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "matrix.h"
#include <stdbool.h>

/*
* Creates a Dimesion 
* @param NumberDim that many arguments must follow
* Arguments (other than NumberDim) should be of type uint32_t
* Last number given is the number of rows
*/
DIMENSION createDim(uint8_t NumberDim, ...);
/*
* Creates a Dimesion 
* Given NumberDim, that size array must follow
* Last number given is the number of rows
*/
DIMENSION createDimA(uint8_t NumberDim, uint32_t* shape);

/*
* Delets the Dimesion, and sets all values to 0
*/
void freeDim(DIMENSION* d);
/*
* Creates a unique carbon copy of dim d
*/
DIMENSION copyDim(const DIMENSION d);

/*
* /brief returns an 0'd out diminesion
*/
DIMENSION emptyDim();




/*
* Matrix Creation Functions
*/
/*
* Safer Type createMat
* uint_8
*/
MATRIX createMatU8(DIMENSION d,uint8_t* data);
/*
* Safer Type createMat
* uint_16
*/
MATRIX createMatU16(DIMENSION d,uint16_t* data);
/*
* Safer Type createMat
* uint_32
*/
MATRIX createMatU32(DIMENSION d,uint32_t* data);
/*
* Safer Type createMat
* uint_64
*/
MATRIX createMatU64(DIMENSION d,uint64_t* data);
/*
* Safer Type createMat
* int_8
*/
MATRIX createMatI8(DIMENSION d,int8_t* data);
/*
* Safer Type createMat
* int_16
*/
MATRIX createMatI16(DIMENSION d,int16_t* data);
/*
* Safer Type createMat
* int_32
*/
MATRIX createMatI32(DIMENSION d,int32_t* data);
/*
* Safer Type createMat
* int_64
*/
MATRIX createMatI64(DIMENSION d,int64_t* data);
/*
* Safer Type createMat
* float
*/
MATRIX createMatF32(DIMENSION d,float* data);
/*
* Safer Type createMat
* double 
*/
MATRIX createMatF64(DIMENSION d,double* data);


/*
* Creates a matrix based on the data given
* Will interpret data as the type t
* Matrix will have dimesions d
*/
MATRIX createMat(DIMENSION d, MATRIX_TYPES t,void* data);

/*
* Creates a matrix with no pre-init value
* Matrix will be of type t and have dimesions d
*/
MATRIX emptyMat(DIMENSION d, MATRIX_TYPES t);

/*
* Allocates a Matrix based on its dimensions stored
*/
MATRIX allocMat(MATRIX* a);
/*
* Creates a matrix with 0 in every spot
* Matrix will be of type t and have dimesions d
*/
MATRIX zerosMat(DIMENSION d,MATRIX_TYPES t);
/*
* Creates a matrix with 1 in every spot
* Matrix will be of type t and have dimesions d
*/
MATRIX onesMat(DIMENSION d,MATRIX_TYPES t);
/*
* Sets all values of a with the value given
* Will interpret value as the same type as a
*/
void setAllMat(MATRIX a, void* value);

/*
* Creates a square matrix with dimesions (shape, shape)
* Matrix will have 1s on the diagnal and 0s everywhere else
* Type will be of type t
*/
MATRIX identMat(uint32_t shape, MATRIX_TYPES t);
/*
* Deletes the given matrix's memory
* Matrix will be set to NullMatrix
*/
void freeMat(MATRIX* a);
/*
* Creates a matrix with all values set to 0
*/
MATRIX nullMatrix();

/*
* Creates a unique carbon copy of matrix a
*/
MATRIX copyMatrix(MATRIX a);

/*
* Creates a Random matrix
* If type float no decimal will be given (.000)
* based on standard rand() (set srand first)
* values will be in range [min, max), min and max are not checked for min>max
* Matrix will be of type t and have dimesions d
*/
MATRIX randIntMatrix(DIMENSION d,MATRIX_TYPES t, int64_t min, int64_t max);

/*
* Creates a Random matrix
* If type float range will include decimals
* based on standard rand() (set srand first)
* values will be in range [min, max), min and max are not checked for min>max
* Matrix will be of type t and have dimesions d
*/
MATRIX randMatrix(DIMENSION d,MATRIX_TYPES t, double min, double max);






/*
* Given the matrix a, prints its contents.
* Each dimension is seperated by []
* At the end of each row (final number in shape) a new line will be printed
* fprintMat allows for a specific stream (ie. stdout stderr...)
*/
void printMat(MATRIX a);
/*
* Given the matrix a, prints its contents.
* Allows for File specifiers
* Each dimension is seperated by []
* At the end of each row (final number in shape) a new line will be printed
*/
void fprintMat(FILE* stream, MATRIX a);
/*
* Extension of printMat, allows for the Format to be spefied.
* The format is inerted directly into printf, ex printf(formater,a.data)
*/
void printMatFormat(MATRIX a, const char* formater);
/*
* Extension of printMat, allows for the Format to be spefied.
* The format is inerted directly into printf, ex printf(formater,a.data)
*/
void fprintMatFormat(FILE* stream, MATRIX a,const  char* formater);

/*
* Prints the Dimension using this format:
* (dim[0],dim[1],..., dim[shape-1])
*/
void printDim(DIMENSION d);
/*
* Prints the Dimension using this format:
* (dim[0],dim[1],..., dim[shape-1])
* Allows for FILE specifiers
*/
void fprintDim(FILE* stream, DIMENSION d);
/*
* Prints type and Dimesion of the Matrix
*/
void printMatInfo(MATRIX a);
/*
* Prints type and Dimesion of the Matrix
* Allows for FILE specifiers
*/
void fprintMatInfo(FILE* stream, MATRIX a);





/*
* Returns the address of Matrix a at the given  point
* Must given the same number of arguments as the dimension size
* Arguments (other than Matrix a) should be of type uint32_t
* The least significant arguement is interperetted as the row
*/
void* atMat(MATRIX a, ...);

/*
* Returns the address of Matrix a at the given  point
* Must given the same size array as the dimension size
* The least significant arguement is interperetted as the row
*/
void* atMatA(MATRIX a, uint32_t* at);

/*
* Returns the address of Matrix a at the given index
*/
void* atIndexMat(MATRIX a, uint64_t index);

/*
* Converts an array of points to an index, based on the dimension d
* at Must be the exact same size at d's number of dimensions
*/
uint64_t point2index(DIMENSION d,uint32_t* at);

/*
* Converts an index to an array of points, based on the dimension d
* the result will be the same size as dim d's number of dimensions
*/
uint32_t* index2point(DIMENSION d,uint64_t index);

/*
* Changes the dimensions of matrix a to dim d
* dim d must match the size of matrix a
* if freeDima is true, it will free the dim of a before applying the new dimensions
*/
void reshapeMatrix(MATRIX* a, DIMENSION d, bool freeDima);

/*
* \brief resizes (and reallocs) the matrix to match dimesion d
*/
void resizeMatrix(MATRIX* a, DIMENSION d, bool freeDima);

/*
* Changes matrix a to match type type
* Does a typecast to convert the matrix
*/
void changeTypeMatrix(MATRIX* a, MATRIX_TYPES type);

/*
* Return a matrix to match type type
* Does a typecast to convert the matrix
* Will not change any values in a 
*/
MATRIX asTypeMatix(const MATRIX a, MATRIX_TYPES type);


/*
* Return a matrix copy from the given points [start, end)
* Start and end must have the same size as the number of dimensions of matrix a
* Must be rectangular in shape 
*/
MATRIX rangeMatrix(MATRIX a,  uint32_t* start,  uint32_t* end);

/*
* Return a matrix ref from the given points [start, end)
* [start, end) must be a continuous block of the matrix, otherwise a copy is returned
* Use closeMatrixRef to clean up the returned Matrix
*
* Start and end must have the same size as the number of dimensions of matrix a
* Must be rectangular in shape 
*/
MATRIX rangeMatrixRef(MATRIX a,  uint32_t* start,  uint32_t* end);

/*
* Closes the output of rangeMatrixRef
* If rangeMatrixRef returned a copy, it will copy it over to a
* Will free the contents of matrix b
*/
void closeMatrixRef(MATRIX a, MATRIX* b, uint32_t* start);

/*
* Copies Matrix contents of b over to a at a starting point
* Matrixes must be the same type, otherwise  copyAtMatrixDifTypes is called
* b must also not be larger than a given the offset start.
*/
void copyAtMatrix(MATRIX a, MATRIX b, uint32_t* start);
/*
* Copies Matrix contents of b over to a at a starting point
* b is cast to type a
* b must also not be larger than a given the offset start.
*/
void copyAtMatrixDifTypes(MATRIX a, MATRIX b, uint32_t* start);
#endif