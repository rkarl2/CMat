#ifndef ITERATORS_H
#define ITERATORS_H
#include <stdint.h>
#include "matrix.h"
#include "matrix_utils.h"


typedef enum {
    MAT_FAILED_TO_CALL_ITER = -2,
    MAT_FINISHED_ITER = -1,
    MAT_NORMAL_RETURN_ITER = 0,
    MAT_LOOPED_ITER = 1,
    MAT_PASSED_OVER_END_ITER = 2,
    MAT_PASSED_OVER_END_AND_LOOPED_ITER = 3
}MAT_iteratorReturnCodes;


typedef struct MAT_iterator{
    DIMENSION dim;
    uint64_t index;
    uint64_t loopCounter;
    int64_t indexParam;
    MAT_iteratorReturnCodes (*callFunc) (struct MAT_iterator* , uint64_t*);
    uint64_t callsInThisLoop;
    uint64_t callsPerLoop;
    void **miscParams; 
    uint32_t sizeOfMiscParams;
} MAT_iterator;


// \brief Determines if the index from the return code is out of bounds
#define MAT_ITER_PASSED_END(code) (code == MAT_PASSED_OVER_END_ITER || code == MAT_PASSED_OVER_END_AND_LOOPED_ITER)

/*
* \brief Calls an Iterator, the output index is stored in index
* \return -1 when end of iterator, 0 when it is at no boundary, >=1 indicates which boundary it is ad 
* \param iter iterator to call
* \param index index to save the result in
*/
MAT_iteratorReturnCodes MAT_callIter(MAT_iterator* iter, uint64_t* index);


/*
* \brief Creates and returns an empty iterator
*/
MAT_iterator MAT_emptyIter();


/*
* \brief Frees only an iterator's dimesion
*/
void MAT_freeIterDim(MAT_iterator* iter);

/*
* \brief Determines the return code for an iterator
* \param iter overwrites callsInThisLoop, and loop counter when required
*/
MAT_iteratorReturnCodes MAT_calcReturnCodes(MAT_iterator* iter);


/*
* \brief Creates an incremental iterator, that increments by increment each time it is called. A loop is considered going through every possible value based on the incrment.
* \param dim Dimesion of the Matrix to iterate through, will create a copy
* \param increment Increment amount, can be positive or negative
* \param startingIndex Index to start at
* \param totalLoops total amount of loops to perform
*/
MAT_iterator MAT_incrementalIter(const DIMENSION dim, int64_t increment, uint64_t startingIndex, uint64_t totalLoops);


/*
* \brief Creates a transposed iterator, will iterate through the transposed Dimesion given
* \param dim Dimesion of the Matrix to iterate through, will create a copy
* \param startingIndex Index to start at
* \param totalLoops total amount of loops to perform
*/
MAT_iterator MAT_transposeIter(const DIMENSION dim, uint64_t startingIndex, uint64_t totalLoops);

/*
* \brief Call function for incremental iterator
*/
MAT_iteratorReturnCodes MAT_incrementalIterCallFunc(MAT_iterator* iter, uint64_t* index);


/*
* \brief Call function for transpose iterator
*/
MAT_iteratorReturnCodes MAT_transposeCallFunc(MAT_iterator* iter, uint64_t* index);


#endif