#include "matrix.h"
#include "matrix_utils.h"
#include "gen_macros.h"
#include "errorHandler.h"
#include "matrix_math.h"


// TODO: change to work with iterators, need new iterators.
MAT_dimCompatabilies MAT_determineIters(const DIMENSION* a, const DIMENSION* b, MATRIX* dst, 
                                       MAT_iterator* iterA, MAT_iterator* iterB, MAT_iterator* iterDst){
    if(a == NULL || b == NULL || dst == NULL){
        MATRIX_ERROR_HANDLER(NULL_POINTER_ERROR,__func__);
        return MAT_incomatiableDim;
    }
    if(a->num_dim == 0 || b->num_dim == 0 || a->size ==0 || b->size == 0){
        return MAT_incomatiableDim;
    }
    if(MAT_compareDims(a, b)){
        if(MAT_compareDims(a, &dst->dim)){
            return MAT_compatableMatrix;
        }else{
            resizeMatrix(dst,copyDim(*a),true);
            return MAT_compatableMatrix;
        }
    }
    return  0;
}
bool MAT_compareDims(const DIMENSION* a, const DIMENSION* b){
    if(a == NULL || b == NULL){
        MATRIX_ERROR_HANDLER(NULL_POINTER_ERROR,__func__);
        return MAT_incomatiableDim;
    }
    if(a->num_dim == 0 || b->num_dim == 0){
        return 0;
    }
    bool fullyEqual = a->size == b->size;
    uint8_t aPointer = a->num_dim, bPointer = b->num_dim;
    uint8_t aCounter = 0, bCounter = 0;
    while(aPointer != 0 && bPointer != 0){
        if(aPointer != 0){
            aPointer--;
            aCounter++;
        }
        if(bPointer != 0){
            bPointer--;
            bCounter++;
        }
        
        //Determine if both matricies are fully equal (even if there a few leading 1s before the dimesion)
        if(fullyEqual){
            if(aCounter == bCounter){
                fullyEqual = a->shape[aPointer] == b->shape[bPointer];
            }else{
                if( aCounter < bCounter){
                    fullyEqual = a->shape[aPointer] == 1;
                }else{
                    fullyEqual = b->shape[bPointer] == 1;
                }
            }
        }else{
            return false;
        }
    }
    return  fullyEqual;
}




MATRIX_TYPES MAT_determineOutputType(MATRIX_TYPES a, MATRIX_TYPES b){
    enum overallType{unIntType, intType, floatType};
    enum overallType aType = unIntType;
    enum overallType bType = unIntType;
    if(a > U64){
        if(a > I64){
            aType = floatType;
        }else{
            aType = intType;
        }
    }

    if(b > U64){
        if(b > I64){
            bType = floatType;
        }else{
            bType = intType;
        }
    }
#define COMP_RETURN_TYPES(a,b) if(a>b){return a;}else{return b;}
    if(aType == bType){
        COMP_RETURN_TYPES(a,b)
    }
    //handle Floats
    if(aType == floatType || bType == floatType){
        COMP_RETURN_TYPES(a,b)
    }

    // Find which int type is greater.
    MATRIX_TYPES c;
    if(aType == intType){
        c = a -4;
        if(c == b){
            return a;
        }else if(c > b){
            return a;
        }else{
            return b+4;
        }
    }else{
        c = b -4;
        if(c == a){
            return b;
        }else if(c > a){
            return b;
        }else{
            return a+4;
        }
    }
#undef COMP_RETURN_TYPES
}
