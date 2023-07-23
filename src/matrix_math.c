#include "matrix.h"
#include "matrix_utils.h"
#include "gen_macros.h"
#include "errorHandler.h"
#include "matrix_math.h"

MATRIX MAT_addS(MATRIX a, MATRIX* c, MATRIX_TYPES scalar_type, void* scalar){
    if(c == NULL){
        MATRIX c_resutls = emptyMat(a.dim,a.type);
        c = &c_resutls;
    }else if(c->dim.size != a.dim.size){
        MATRIX c_resutls = emptyMat(a.dim,a.type);
        c = &c_resutls;        
    }else if(c->type != a.type){
        changeTypeMatrix(c,a.type);
    }

}




MATRIX MAT_addSU8(MATRIX a, MATRIX* c, uint8_t scalar){
    return MAT_addS(a,c,U8,&scalar);
}
MATRIX MAT_addSU16(MATRIX a, MATRIX* c, uint16_t scalar){
    return MAT_addS(a,c,U16,&scalar);
}
MATRIX MAT_addSU32(MATRIX a, MATRIX* c, uint32_t scalar){
    return MAT_addS(a,c,U32,&scalar);
}
MATRIX MAT_addSU64(MATRIX a, MATRIX* c, uint64_t scalar){
    return MAT_addS(a,c,U64,&scalar);
}
MATRIX MAT_addSI8(MATRIX a, MATRIX* c, int8_t scalar){
    return MAT_addS(a,c,I8,&scalar);
}
MATRIX MAT_addSI16(MATRIX a, MATRIX* c, int16_t scalar){
    return MAT_addS(a,c,I16,&scalar);
}
MATRIX MAT_addSI32(MATRIX a, MATRIX* c, int32_t scalar){
    return MAT_addS(a,c,I32,&scalar);
}
MATRIX MAT_addSI64(MATRIX a, MATRIX* c, int64_t scalar){
    return MAT_addS(a,c,I64,&scalar);
}
MATRIX MAT_addSF32(MATRIX a, MATRIX* c, float scalar){
    return MAT_addS(a,c,F32,&scalar);
}
MATRIX MAT_addSF64(MATRIX a, MATRIX* c, double scalar){
    return MAT_addS(a,c,F64,&scalar);
}
