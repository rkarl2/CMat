#ifndef ITERATORS_H
#define ITERATORS_H
#include <stdint.h>
#include "matrix.h"
#include "matrix_utils.h"

typedef struct MAT_iteratorS{
    DIMENSION dim;
    uint64_t index;
    uint64_t loopCounter;
    int64_t indexParam;
    int64_t (*callFunc) (struct MAT_iteratorS* , uint64_t*);
    void **miscParams; 
    uint32_t sizeOfMiscParams;
} MAT_iteratorS;


enum{
    MAT_FAILED_TO_CALL_ITER = -2,
    MAT_FINISHED_ITER = -1,
    MAT_NON_ENDCAP_RESULT_ITER = 0
};

/*
* \brief Calls an Iterator, the index is stored in index
* \return -1 when end of iterator, 0 when it is at no boundary, >=1 indicates which boundary it is ad 
* \param iter iterator to call
* \param index index to save the result in
*/
int64_t MAT_callIter(MAT_iteratorS* iter, uint64_t* index);


/*
* \brief Creates and returns an empty iterator
*/
MAT_iteratorS MAT_emptyIter();


/*
* \brief Frees only an iterator's dimesion
*/
void MAT_freeIterDim(MAT_iteratorS* iter);


/*
* \brief Calculates if an endcap was passed while incrementing the iterator
* \param index updated index value
* \param previousIndex provided by the MAT_iteratorS struct
* \param dim provided by the MAT_iteratorS struct
*/
int64_t MAT_DetectEndcaps(uint64_t index, uint64_t previousIndex, const DIMENSION* dim);


/*
* \brief Creates an incremental iterator, that increments by increment each time it is called
* \param dim Dimesion of the Matrix to iterate through, will create a copy
* \param increment Increment amount, can be positive or negative
* \param startingIndex Index to start at
* \param totalLoops total amount of loops to perform
*/
MAT_iteratorS MAT_incrementalIter(const DIMENSION dim, int64_t increment, uint64_t startingIndex, uint64_t totalLoops);


/*
* \brief Creates a transposed iterator, will iterate through the transposed Dimesion given
* \param dim Dimesion of the Matrix to iterate through, will create a copy
* \param startingIndex Index to start at
* \param totalLoops total amount of loops to perform
*/
MAT_iteratorS MAT_transposeIter(const DIMENSION dim, uint64_t startingIndex, uint64_t totalLoops);

/*
* \brief Call function for incremental iterator
*/
int64_t MAT_incrementalIterCallFunc(MAT_iteratorS* iter, uint64_t* index);


/*
* \brief Call function for transpose iterator
*/
int64_t MAT_incrementalIterCallFunc(MAT_iteratorS* iter, uint64_t* index);


#endif