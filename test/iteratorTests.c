#include <stdio.h>
#include <stdint.h>
#include "../src/matrix.h"
#include "../src/matrix_utils.h"
#include <stdlib.h>
#include "../src/gen_macros.h"
#include "../src/iterators.h"


int main(void)
{
    DIMENSION d = createDim(2, 1,5);
    MATRIX mat =  randIntMatrix(d,U32,0,20);
    printMat(mat);
    MAT_iteratorS iter = MAT_incrementalIter(d,2,0,5);
    uint64_t i;
    while(MAT_callIter(&iter,&i) >= 0){
        printf("%d\n",i);
    }
    return 0;
}