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
    int64_t (*callFunc) (struct MAT_iteratorS* self, uint64_t*);
    void **miscParams; 
    uint32_t sizeOfMiscParams;
} MAT_iteratorS;


/*
* \brief Calls an Iterator, the index is stored in index
* \return -1 when end of iterator, 0 when it is at no boundary, >=1 indicates which boundary it is ad 
* \param iter iterator to call
* \param index index to save the result in
*/
int64_t MAT_callIter(MAT_iteratorS iter, uint64_t* index);


/*
* \brief Creates and returns an empty iterator
*/
MAT_iteratorS MAT_emptyIter();

/*
* \brief Frees an iterator
* Will free the dimesion, and every pointer in miscParams, and miscParams itself, 
* use MAT_freeIterDim to free the iter dimesion without freeing miscParams
*/
void MAT_freeIter(MAT_iteratorS* iter);

/*
* \brief Frees only an iterator's dimesion
* Use MAT_freeIter to free all of miscParams (if allocated)
*/
void MAT_freeIterDim(MAT_iteratorS* iter);

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