#ifndef ITERATORS_H
#define ITERATORS_H
#include <stdint.h>
#include "matrix.h"
#include "matrix_utils.h"

typedef struct MAT_iteratorS{
    DIMENSION dim;
    uint64_t index;
    int16_t loopCounter;
    int64_t indexParam;
    int16_t (*callFunc) (struct MAT_iteratorS* self, uint32_t*);
    void **miscParams; 
    uint32_t sizeOfMiscParams;
    MAT_iteratorS(){
        dim; // TODO: Create empty Dim func
        index = 0;
        loopCounter = 0;
        indexParam = 0;
        callFunc = NULL;
        miscParams = NULL;
        sizeOfMiscParams = 0;
    }
} MAT_iteratorS;


/*
* \brief Calls an Iterator, the index is stored in index
* \return -1 when end of iterator, 0 when it is at no boundary, >=1 indicates which boundary it is ad 
* \param iter iterator to call
* \param index index to save the result in
*/
int16_t MAT_callIter(MAT_iteratorS iter, uint32_t* index);




#endif