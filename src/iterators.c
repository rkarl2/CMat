#include "iterators.h"


int64_t MAT_callIter(MAT_iteratorS* iter, uint64_t* index){
    if(iter == NULL || index == NULL){
        return MAT_FAILED_TO_CALL_ITER;
    }
    return iter->callFunc(iter,index);
}

MAT_iteratorS MAT_emptyIter()
{
    return (MAT_iteratorS) {.dim =emptyDim(),
                            .index =0,  
                            .loopCounter = 0,
                            .indexParam = 0,
                            .callFunc = NULL,
                            .miscParams = NULL,
                            .sizeOfMiscParams = 0};
}

void MAT_freeIterDim(MAT_iteratorS* iter)
{
    if(iter == NULL){
        return;
    }
    freeDim(&iter->dim);
}

MAT_iteratorS MAT_incrementalIter(const DIMENSION dim, int64_t increment, uint64_t startingIndex, uint64_t totalLoops)
{
    if(startingIndex > dim.size)
    {
        if(dim.size == 0){
            startingIndex = 0;
        }else{
            startingIndex = dim.size-1;
        }
    }
    if(increment == 0){
        increment = 1;
    }
    MAT_iteratorS res = MAT_emptyIter();
    res.dim = copyDim(dim);
    res.index = startingIndex;
    res.loopCounter = totalLoops;
    res.indexParam = increment;
    res.callFunc = &MAT_incrementalIterCallFunc;
    return res;
}

int64_t MAT_DetectEndcaps(uint64_t index, uint64_t previousIndex, const DIMENSION* dim){
    if(dim == NULL || dim->num_dim == 0){
        return MAT_FAILED_TO_CALL_ITER;
    }
    // uint64_t blockSizeTotal=1;
    // const uint64_t differenceBetweenTimes = 

    // for(uint8_t i = dim->num_dim-1; i > 0; i--){

    // }
    if(index >= dim->size){
        return dim->num_dim;
    }
    return 0;
}

int64_t MAT_incrementalIterCallFunc(MAT_iteratorS* iter, uint64_t* index){
    if(index == NULL){
        return MAT_FAILED_TO_CALL_ITER;
    }
    if(iter->loopCounter == 0){
        *index = 0;
        return MAT_FINISHED_ITER;
    }
    *index = iter->index;
    iter->index = iter->index + iter->indexParam;
    int64_t result = MAT_DetectEndcaps(iter->index, *index, &iter->dim);
    if(result == iter->dim.num_dim){
        iter->index = iter->index % iter->dim.size;
        iter->loopCounter--;
    }
    return result;
}
