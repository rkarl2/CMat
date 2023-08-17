#include "matrix.h"
#include "matrix_utils.h"
#include "gen_macros.h"
#include "errorHandler.h"
#include <stdlib.h>



MATRIX nullMatrix(){
    MATRIX a = {
        .data.U8 =NULL,
        .dim.num_dim =0,
        .dim.size = 0,
        .dim.shape = NULL,
    };
    return a;
}
void printMat(MATRIX a){
    fprintMat(stdout, a);
}


MATRIX createMatU8(DIMENSION d,uint8_t* data){return createMat(d,U8,data);}
MATRIX createMatU16(DIMENSION d,uint16_t* data){return createMat(d,U16,data);}
MATRIX createMatU32(DIMENSION d,uint32_t* data){return createMat(d,U32,data);}
MATRIX createMatU64(DIMENSION d,uint64_t* data){return createMat(d,U64,data);}
MATRIX createMatI8(DIMENSION d,int8_t* data){return createMat(d,I8,data);}
MATRIX createMatI16(DIMENSION d,int16_t* data){return createMat(d,I16,data);}
MATRIX createMatI32(DIMENSION d,int32_t* data){return createMat(d,I32,data);}
MATRIX createMatI64(DIMENSION d,int64_t* data){return createMat(d,I64,data);}
MATRIX createMatF32(DIMENSION d,float* data){return createMat(d,F32,data);}
MATRIX createMatF64(DIMENSION d,double* data){return createMat(d,F64,data);}

void fprintMat(FILE* stream, MATRIX a){
    const char formater[][5] = {"%hhu","%hu","%lu","%llu","%hhd","%hd","%ld","%lld", "%f", "%lf"};
    fprintMatFormat(stream, a, formater[a.type]);
}

void printMatFormat(MATRIX a, const char* formater){
   fprintMatFormat(stdout,a,formater);
}

void fprintMatFormat(FILE* stream, MATRIX a, const char* formater){
     MATRIXswitch( a.type, a.data, data,
            uint64_t i;
            int16_t bracketChecker=0;
            for(i = 0; i<a.dim.size; i++){
                uint8_t openBracket = 0;
                uint8_t closeBracket = 0;
                openBracket = 0;
                uint32_t mod = i % a.dim.shape[a.dim.num_dim-1];
                int16_t j = 0;
                uint64_t runningTotal=1;
                if(mod ==0){
                    for(j = a.dim.num_dim-1; j>=0;j--){
                        runningTotal = runningTotal * a.dim.shape[j];
                        if(runningTotal ==0) runningTotal=1;
                        mod = i % runningTotal;
                        if((mod) ==(0)) openBracket++;
                    }
                }
                runningTotal=1;
                for(j = a.dim.num_dim-1; j>=0;j--){
                    runningTotal = runningTotal * a.dim.shape[j];
                    if(runningTotal ==0) runningTotal=1;
                    mod = i % runningTotal;
                    if((mod) ==(runningTotal-1)) closeBracket++;
                }
                if(openBracket){
                    for(j=a.dim.num_dim-openBracket; j>0; j--) fprintf(stream," ");
                    for(j=1; j<=openBracket; j++) fprintf(stream,"[");
                }
                fprintf(stream,formater, data[i]);
                for(j=1; j<=closeBracket; j++) fprintf(stream,"]");
                if(closeBracket){ fprintf(stream,"\n");
                }else fprintf(stream,", "); 
            }
     )
    
}

DIMENSION createDim(uint8_t NumberDim, ...){
    DIMENSION dim;
    dim.num_dim = NumberDim;
    dim.shape = (uint32_t*) malloc(NumberDim*sizeof(uint32_t));
    if(dim.shape == NULL){
        MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "createDim");
        return dim;
    }

    va_list inShape;
    va_start(inShape,NumberDim);
    uint8_t i;
    dim.size = 1;
    for(i=0;i<NumberDim;i++){
        uint32_t s = va_arg(inShape, uint32_t);
        if(s == 0){
            MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "createDim");
            s = 1;
        }
        dim.size *= s;
        dim.shape[i] = s;
    }
    va_end(inShape);
    return dim;
}

DIMENSION createDimA(uint8_t NumberDim, uint32_t* inShape){
    DIMENSION dim;

    dim.num_dim = NumberDim;
    dim.shape = (uint32_t*) malloc(NumberDim*sizeof(uint32_t*));
    if(dim.shape == NULL){
         MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "createDimA");
        return dim;
    }

    uint8_t i;
    dim.size = 1;
    for(i=0;i<NumberDim;i++){
        uint32_t s = inShape[i];
        if(s == 0){
            MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "createDim");
            s = 1;
        }
        dim.size *= s;
        dim.shape[i] = s;
    }
    return dim;
}

void printDim(DIMENSION d){
    fprintDim(stdout, d);
}

void fprintDim(FILE* stream, DIMENSION d){
    int i;
    fprintf(stream,"(");
    for(i = 0; i< d.num_dim-1;i++){
        fprintf(stream,"%u, ",d.shape[i]);
    }
    fprintf(stream,"%u)\n",d.shape[i]);
}

void printMatInfo(MATRIX a){
    fprintMatInfo(stdout, a);
}

void fprintMatInfo(FILE* stream, MATRIX a){
    const char typeNames[][9] ={"uint8_t ","uint16_t ","uint32_t ","uint64_t ","int8_t ","int16_t ","int32_t ","int64_t ", "float ", "double "};
    fprintf(stream,"%s",typeNames[a.type]);
    fprintDim(stream, a.dim);
}

void* atMatA(MATRIX a, uint32_t* at){
    return atIndexMat(a, point2index(a.dim, at));
}

void* atMat(MATRIX a, ...){

    uint64_t index =0;
    uint64_t multiple =a.dim.size;
    uint8_t i;

    va_list at;
    va_start(at,a);

    for(i=0;i<a.dim.num_dim;i++){
        uint32_t atVal = va_arg(at, uint32_t);
        multiple = multiple/a.dim.shape[i];
        if(atVal>=a.dim.shape[i]){
            MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "atMat");
            printf("%u \n",atVal);
            index += (a.dim.shape[i]-1)*multiple;
            continue;
        }
        index += atVal*multiple;
        
    }
    va_end(at);
    return atIndexMat(a, index);
}

void* atIndexMat(MATRIX a, uint64_t index){
    if(a.dim.size<=index){
        MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "atIndexMat");
        return NULL;
    }
    MATRIXswitch(a.type, a.data, data,
            return (void*) &data[index];   
    )
}

MATRIX createMat(DIMENSION d, MATRIX_TYPES t, void* data){
    MATRIX a = emptyMat(d,t);
    MATRIXswitch( a.type, a.data, adata,
        uint64_t i;
        typeof(adata) da =data;
        for(i =0; i< a.dim.size;i++){
            adata[i]=da[i];
        }
    )
    return a;
}

MATRIX allocMat(MATRIX* a){
    MATRIXswitch(a->type, a->data, data,
        data =(typeof(data)) malloc(a->dim.size*sizeof(typeof(*data)));
        if(data == NULL){
            MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "allocMat");
        }
        a->data.U8 = (uint8_t*)data;    
    )
    return *a;
}

void setAllMat(MATRIX a, void* value){
    MATRIXswitch( a.type, a.data, data, 
            uint64_t i;
            typeof(data) da = (typeof(data)) value;
            for(i =0; i< a.dim.size;i++){
                 data[i]=*da;
            }
    )
}

MATRIX zerosMat(DIMENSION d,MATRIX_TYPES t){
    MATRIX a = emptyMat(d,t);
    
    MATRIXswitch(a.type, a.data, data, 
            uint64_t i;
            for(i =0; i< a.dim.size;i++) data[i]=0;
    )
    return a;
}

MATRIX onesMat(DIMENSION d,MATRIX_TYPES t){
    MATRIX a = emptyMat(d,t);
    MATRIXswitch(a.type, a.data, data,
            uint64_t i;
            for(i =0; i< a.dim.size;i++) data[i]=1;
    )
    return a;
}

MATRIX emptyMat(DIMENSION d, MATRIX_TYPES t){
    MATRIX a;
    a.type = t;
    a.dim = d;
    return allocMat(&a);
}

MATRIX identMat(uint32_t shape, MATRIX_TYPES t){
    DIMENSION d = createDim(2, shape,shape);
    MATRIX a = zerosMat(d, t);
    MATRIXswitch( a.type, a.data, data, 
        
        uint64_t i;
        for(i =0; i< a.dim.shape[0];i++){
            uint32_t diag[2];
            diag[0] = i;
            diag[1] = i;
            data[point2index(a.dim, diag)]=1;
        }
        
    )
    return a;
}

void freeMat(MATRIX* a){
    freeDim(&a->dim);
    free(a->data.U8);
    a->data.U8 = NULL;
}

void freeDim(DIMENSION* d){
    free(d->shape);
    d->shape = NULL;
    d->size = 0;
    d->num_dim = 0;
}

uint64_t point2index(DIMENSION d,uint32_t* at){
    uint64_t index =0;
    uint64_t multiple =d.size;
    uint8_t i;
    for(i=0;i<d.num_dim;i++){
        multiple = multiple/d.shape[i];
        if(at[i]>=d.shape[i]){
            MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "point2index");
            index += (d.shape[i]-1)*multiple;
            continue;
        }
        index += at[i]*multiple;
        
    }
    return index;
}

uint32_t* index2point(DIMENSION d,uint64_t index){
    uint32_t* point = (uint32_t*) malloc(d.num_dim*sizeof(uint32_t));
    if(point == NULL){
        MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "index2point");
        return NULL;
    }
    int16_t i;
    uint64_t multiple =1;
    if(index >= d.size){
        MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "index2point");
        index = d.size-1;
    }
    for(i=d.num_dim-1;i>=0;i--){
        multiple *= d.shape[i];
        point[i] = index % multiple; 
        index = index - (point[i]);
        point[i] =point[i]/ (multiple/d.shape[i]);
    }
    return point;
}

DIMENSION copyDim(const DIMENSION d){
    return createDimA(d.num_dim,d.shape);
}

DIMENSION emptyDim(){
    return (DIMENSION) {.num_dim = 0, .size = 0, .shape =NULL};
}

MATRIX asTypeMatix(const MATRIX a, MATRIX_TYPES type){
    MATRIX b = emptyMat(copyDim(a.dim),type);
    MATRIXswitch(b.type, b.data, to, 
        MATRIXswitch(a.type, a.data, from,
            uint64_t i;
            for(i=0; i<a.dim.size; i++){ 
                to[i] = (typeof(*to)) from[i]; 
                
            }
        )
    )
    return b;
}

void changeTypeMatrix(MATRIX* a, MATRIX_TYPES type){
    MATRIXswitch(type, a->data, to, 
        MATRIXswitch(a->type, a->data, from,
            if(sizeof(typeof(*to)) > sizeof(typeof(*from))){
                to =( typeof(to)) malloc(a->dim.size*sizeof(typeof(*to)));
                if(to == NULL){
                    MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "changeTypeMatrix");
                    return;
                } 
            }
            uint64_t i;
            for(i=0; i<a->dim.size; i++){ 
                to[i] = (typeof(*to)) from[i]; 
            }
            if(sizeof(typeof(*to)) > sizeof(typeof(*from))){
                free(from);
                a->data.U8 = (void*) to;
            }else if(sizeof(typeof(*to)) < sizeof(typeof(*from))){
                a->data.U8 = realloc(to, a->dim.size*sizeof(typeof(*to)));
            }
            a->type = type;
        )
    )
}


MATRIX copyMatrix(MATRIX a){
    return createMat(copyDim(a.dim),a.type, a.data.U8);
}


MATRIX rangeMatrix(MATRIX a,  uint32_t* start,  uint32_t* end){
    uint32_t* b_dimShape = malloc(sizeof(uint32_t)*a.dim.num_dim);
    if(b_dimShape == NULL) {
        MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "rangeMatrixRef"); 
        return nullMatrix();
    }

    uint8_t i;
    for(i=0;i<a.dim.num_dim;i++){
        if(a.dim.shape[i] < end[i] || end[i]<=start[i]){
            MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "rangeMatrix");
            return nullMatrix();
        } 
        b_dimShape[i] = end[i] -start[i];
    }
    DIMENSION bdim = createDimA(a.dim.num_dim,b_dimShape);
    MATRIX b = emptyMat(bdim, a.type);
    
    for(i=0;i<a.dim.num_dim;i++) b_dimShape[i] =start[i];

    MATRIXswitch(a.type, a.data, adata,
        uint64_t  i = point2index(a.dim, b_dimShape);
        uint64_t  bIndex = 0;
        typeof(adata) bdata = (void*) b.data.U8;
        bool done = false;
        while(!done){
            bdata[bIndex] = adata[i];
            bIndex++;
            for(int16_t j = b.dim.num_dim-1; j>-1;j--){
                if(++b_dimShape[j]<end[j]){
                    break;
                }else{
                    b_dimShape[j] = start[j];
                    if(j == 0) done =true;
                }
            }
            i = point2index(a.dim, b_dimShape);
        }    
    )
    free(b_dimShape);
    return b;
}

MATRIX rangeMatrixRef(MATRIX a,  uint32_t* start,  uint32_t* end){
    uint32_t* b_dimShape = malloc(sizeof(uint32_t)*a.dim.num_dim);
    if(b_dimShape == NULL) {MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "rangeMatrixRef"); return nullMatrix();}

    bool spansChecker = false;
    for(int16_t i=a.dim.num_dim-1;i>=0;i--){
        if(a.dim.shape[i] < end[i] || end[i]<=start[i]) MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "rangeMatrixRef");
        b_dimShape[i] = end[i] -start[i];
        if((b_dimShape[i] != a.dim.shape[i]) || spansChecker){
            if(spansChecker && (b_dimShape[i] != 1)){
                free(b_dimShape);
                return rangeMatrix(a,start,end);
            }
            spansChecker = true;
        }
    }
    MATRIX b;
    b.type = a.type;
    b.dim = createDimA(a.dim.num_dim, b_dimShape);
    b.data.U8 = atMatA(a,start);
    return b;
}

MATRIX randMatrix(DIMENSION d,MATRIX_TYPES t, double min, double max){
    MATRIX a = emptyMat(d,t);
    MATRIXswitch(a.type,a.data,data,
        for(uint64_t i = 0; i<a.dim.size;i++){
            data[i] =(typeof(data[0])) min +((int64_t) rand()/(double) (RAND_MAX +1))*(max-min+1);
        }
    
    )
    return a;
}

MATRIX randIntMatrix(DIMENSION d,MATRIX_TYPES t, int64_t min, int64_t max){
    MATRIX a = emptyMat(d,t);
    MATRIXswitch(a.type,a.data,data,
        for(uint64_t i = 0; i<a.dim.size;i++){
            
            int64_t r = min +(rand()/(double) (RAND_MAX +1))*(max-min+1);
            data[i] = (typeof(data[0])) r;
        }
    )
    return a;
}

void resizeMatrix(MATRIX* a, DIMENSION d, bool freeDima){
    if(a->dim.size != d.size){
        MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "resizeMatrix");
        return;
    }
    if(freeDima) freeDim(&a->dim);
    a->dim = d;
}

void closeMatrixRef(MATRIX a, MATRIX* b, uint32_t* start){
    if(b->data.U8 == atMatA(a,start)){
        
        freeDim(&b->dim);
        return;
    }
    if(b->data.U8 == NULL){
        MATRIX_ERROR_HANDLER(NULL_MATRIX_ERROR, "closeMatrixRef");
        return;
    }
    
    copyAtMatrix(a,*b,start);
    printMat(a);
    freeMat(b);
}



void copyAtMatrix(MATRIX a, MATRIX b, uint32_t* start){
    if(b.data.U8 == NULL||a.data.U8 == NULL){
        MATRIX_ERROR_HANDLER(NULL_MATRIX_ERROR, "copyAtMatrix");
        return;
    }
    

    uint8_t i;
    for(i=0;i<a.dim.num_dim;i++){
        if(a.dim.shape[i] > b.dim.shape[i]+start[i] ||a.dim.shape[i] < start[i] ){
            MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "copyAtMatrix");
            return;
        } 
    }
    if(b.type != a.type) {
        copyAtMatrixDifTypes(a, b, start);
        return;
    }
    uint32_t *aShapePointer = malloc(sizeof(uint32_t)*a.dim.num_dim);
    if(aShapePointer == NULL) {
        MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "copyAtMatrix"); 
        return;
    }
    for(uint32_t i; i < a.dim.num_dim; i++) aShapePointer[i] = 0;
    MATRIXswitch(a.type, a.data, adata,
        uint64_t  i = point2index(a.dim, start);
        uint64_t  bIndex = 0;
        typeof(adata) bdata = (void*) b.data.U8;
        bool done = false;
        while(!done){
            adata[i] = bdata[bIndex];
            
            bIndex++;
            if (bIndex >= b.dim.size) break;
            uint32_t *b_pointer = index2point(b.dim,bIndex);
            
            uint32_t j;
            uint32_t k = a.dim.num_dim-1; 
            for(j = b.dim.num_dim-1; j>0; j--){
                aShapePointer[k] = start[k] + b_pointer[j];
                k--;
            }
            aShapePointer[k] = start[k] + b_pointer[0];
            if(k != 0){
                for(; k>0; k--){
                    aShapePointer[k] = start[k];
                }
                aShapePointer[0] = start[0];
            }
            
            i = point2index(a.dim, aShapePointer);
        }    
    )
    
}

void copyAtMatrixDifTypes(MATRIX a, MATRIX b, uint32_t* start){

    if(b.data.U8 == NULL||a.data.U8 == NULL){
        MATRIX_ERROR_HANDLER(NULL_MATRIX_ERROR, "copyAtMatrixDifTypes");
        return;
    }
    

    uint8_t i;
    for(i=0;i<a.dim.num_dim;i++){
        if(a.dim.shape[i] > b.dim.shape[i]+start[i] ||a.dim.shape[i] < start[i] ){
            MATRIX_ERROR_HANDLER(INDEX_OUT_OF_BOUNDS, "copyAtMatrixDifTypes");
            return;
        } 
    }
    uint32_t *aShapePointer = malloc(sizeof(uint32_t)*a.dim.num_dim);
    if(aShapePointer == NULL) {
        MATRIX_ERROR_HANDLER(ALLOCATION_ERROR, "copyAtMatrixDifTypes"); 
        return;
    }
    for(uint32_t i; i < a.dim.num_dim; i++) aShapePointer[i] = 0;
    MATRIXswitch(a.type, a.data, adata,
        MATRIXswitch(b.type,b.data, bdata,
            uint64_t  i = point2index(a.dim, start);
            uint64_t  bIndex = 0;
            bool done = false;
            printMat(a);
            while(!done){
                adata[i] = (typeof(*adata)) bdata[bIndex];

                bIndex++;
                if (bIndex >= b.dim.size) break;
                uint32_t *b_pointer = index2point(b.dim,bIndex);
                
                uint32_t j;
                uint32_t k = a.dim.num_dim-1; 
                for(j = b.dim.num_dim-1; j>0; j--){
                    aShapePointer[k] = start[k] + b_pointer[j];
                    k--;
                }
                aShapePointer[k] = start[k] + b_pointer[0];
                if(k != 0){
                    for(; k>0; k--){
                        aShapePointer[k] = start[k];
                    }
                    aShapePointer[0] = start[0];
                }
                
                i = point2index(a.dim, aShapePointer);
            }    
        )
    )
}