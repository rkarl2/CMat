#include <stdio.h>
#include <stdint.h>
#include "../src/matrix.h"
#include "../src/matrix_utils.h"
#include <stdlib.h>
#include "../src/gen_macros.h"
#include "../src/iterators.h"



int main(void){
    float h[12] = {-1,1,2,3,4,5,6,7,8, 9,10,11};
    DIMENSION dim = createDim(3,2,2,5);
    MATRIX a = randIntMatrix(dim,I16,-200, 32);
    uint32_t start[] = {0,1,0};
    uint32_t end[] = {2,2,5};
    printMat(a);
    MATRIX b = rangeMatrixRef(a,start,end);
    // b.data.I16[0] = 25;
    // b.data.I16[1] = -8;
    // b.data.I16[2] = 36;
    // b.data.I16[3] = 15;
    // b.data.I16[4] = 20;
    // b.data.I16[5] = 13;
    printf("\n");
    changeTypeMatrix(&a,F32);
    printMat(a);
    printf("\n");

    printMat(b);
    printf("\n");
    // b.dim.shape[0] = 1;
    // b.dim.shape[0] = 5;
    // b.dim.num_dim = 2;
    // b.dim.size = 5;
    closeMatrixRef(a, &b,start);
    printf("\n");
    printMat(a);
    return 0;
}