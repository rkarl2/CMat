#include "iterators.h"




MAT_iteratorReturnCodes MAT_callIter(MAT_iterator* iter, uint64_t* index){
    if(iter == NULL || index == NULL){
        return MAT_FAILED_TO_CALL_ITER;
    }
    return iter->callFunc(iter,index);
}

MAT_iterator MAT_emptyIter()
{
    return (MAT_iterator) {.dim =emptyDim(),
                            .index =0,  
                            .loopCounter = 0,
                            .indexParam = 0,
                            .callFunc = NULL,
                            .callsInThisLoop = 0,
                            .callsPerLoop = 0,
                            .miscParams = NULL,
                            .sizeOfMiscParams = 0};
}

void MAT_freeIterDim(MAT_iterator* iter)
{
    if(iter == NULL){
        return;
    }
    freeDim(&iter->dim);
}

MAT_iteratorReturnCodes MAT_calcReturnCodes(MAT_iterator* iter){
    if(iter == NULL){
        return MAT_FAILED_TO_CALL_ITER;
    }
    MAT_iteratorReturnCodes returnCode = MAT_NORMAL_RETURN_ITER;
    if(iter->index >= iter->dim.size){
        returnCode = MAT_PASSED_OVER_END_ITER;
    }
    iter->callsInThisLoop++;
    if(iter->callsInThisLoop >= iter->callsPerLoop){
        iter->loopCounter--;
        iter->callsInThisLoop = 0;
        if(returnCode > MAT_NORMAL_RETURN_ITER){
            returnCode = MAT_PASSED_OVER_END_AND_LOOPED_ITER;
        }else{
            returnCode = MAT_LOOPED_ITER;
        }
    }
    return returnCode;
}



MAT_iterator MAT_incrementalIter(const DIMENSION dim, int64_t increment, uint64_t startingIndex, uint64_t totalLoops)
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
    MAT_iterator res = MAT_emptyIter();
    res.dim = copyDim(dim);
    res.callsPerLoop = (dim.size % increment == 0) ? // Check for even increments
                        dim.size/increment: // Loop only through the elements that will apear
                        dim.size; // Loop through all elements 
    res.index = startingIndex;
    res.loopCounter = totalLoops;
    res.indexParam = increment;
    res.callFunc = &MAT_incrementalIterCallFunc;
    return res;
}

MAT_iteratorReturnCodes MAT_incrementalIterCallFunc(MAT_iterator* iter, uint64_t* index){
    if(index == NULL){
        return MAT_FAILED_TO_CALL_ITER;
    }
    if(iter->loopCounter == 0){
        *index = 0;
        return MAT_FINISHED_ITER;
    }
    *index = iter->index;
    iter->index = iter->index + iter->indexParam;
    MAT_iteratorReturnCodes returnCode = MAT_calcReturnCodes(iter);
    if(MAT_ITER_PASSED_END(returnCode)){
        iter->index = iter->index % iter->dim.size;
    }
    return returnCode;
}


MAT_iterator MAT_transposeIter(const DIMENSION dim, uint64_t startingIndex, uint64_t totalLoops){\
    if(startingIndex > dim.size)
    {
        if(dim.size == 0){
            startingIndex = 0;
        }else{
            startingIndex = dim.size-1;
        }
    }
    DIMENSION iterDim;
    if(dim.num_dim <= 1){
        if(dim.num_dim == 0 || dim.size == 0){
            return MAT_emptyIter();
        }
        iterDim = createDim(2, dim.shape[0], 1);
    }else{
        iterDim = copyDim(dim);
        iterDim.shape[1] = dim.shape[0];
        iterDim.shape[0] = dim.shape[1];
    }

    MAT_iterator res = MAT_emptyIter();
    res.dim = iterDim;
    res.index = startingIndex;
    res.callsPerLoop = dim.size;
    res.loopCounter = totalLoops;
    res.indexParam = dim.shape[dim.num_dim - 1];
    res.callFunc = &MAT_transposeCallFunc;
    return res;
}

MAT_iteratorReturnCodes MAT_transposeCallFunc(MAT_iterator* iter, uint64_t* index){
    if(index == NULL){
        return MAT_FAILED_TO_CALL_ITER;
    }
    if(iter->loopCounter == 0){
        *index = 0;
        return MAT_FINISHED_ITER;
    }

    *index = iter->index;
    iter->index = iter->index + iter->indexParam;
    MAT_iteratorReturnCodes returnCode = MAT_calcReturnCodes(iter);
    if(MAT_ITER_PASSED_END(returnCode)){
        iter->index = (iter->index % iter->dim.size) +1;
    }
    return returnCode;
}
