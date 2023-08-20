#include <stdio.h>
#include <stdint.h>
#include "../src/matrix.h"
#include "../src/matrix_utils.h"
#include <stdlib.h>
#include "../src/gen_macros.h"
#include "../src/iterators.h"


int main(void)
{
    DIMENSION d = createDim(2, 2,3);
    MATRIX mat =  randIntMatrix(d,U32,0,20);
    printMatFormat(mat,"%2d");
    MAT_iterator iter = MAT_transposeIter(d,0,1);
    uint64_t i;
    int16_t a = 0;
    while((a =MAT_callIter(&iter,&i)) >= 0){
        printf("%2d %2d %2d\n",i,a,mat.data.U32[i]);
    }
    return 0;
}