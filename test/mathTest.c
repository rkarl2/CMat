#include <stdio.h>
#include <stdint.h>
#include "../src/matrix.h"
#include "../src/matrix_utils.h"
#include <stdlib.h>
#include "../src/gen_macros.h"
#include "../src/iterators.h"
#include "../src/matrix_math.h"


int main(void)
{
    DIMENSION d = createDim(2, 2,3);
    DIMENSION b = createDim(3,5, 2,6);
    MATRIX dst = randIntMatrix(b,U32,0, 5);
    printDim(dst.dim);
    printMat(dst);
    int i = MAT_determineIters(&d,&d,&dst, NULL, NULL, NULL);    
    printDim(dst.dim);
    printMat(dst);

    printf("%d\n",MAT_determineOutputType(U16,I64 ));
    return 0;
}