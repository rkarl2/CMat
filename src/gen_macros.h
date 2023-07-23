
#define MATRIXswitch(type, data, dataName, func) \
        switch (type){\
		case U8: \
            {\
                uint8_t* dataName = data.U8;\
                func\
            }\
			break;\
		case U16:\
            {\
                uint16_t* dataName = data.U16;\
                func\
            }\
			break;\
		case U32:\
            {\
                uint32_t* dataName = data.U32;\
                func\
            }\
			break;\
		case U64:\
            {\
                uint64_t* dataName = data.U64;\
                func\
            }\
			break;\
		case I8:\
            {\
                int8_t* dataName = data.I8;\
                func\
            }\
			break;\
		case I16:\
            {\
                int16_t* dataName = data.I16;\
                func\
            }\
			break;\
		case I32:\
            {\
                int32_t* dataName = data.I32;\
                func\
            }\
			break;\
		case I64:\
            {\
                int64_t* dataName = data.I64;\
                func\
            }\
			break;\
		case F32:\
            {\
                float* dataName = data.F32;\
                func\
            }\
			break;\
		case F64:\
            {\
                double* dataName = data.F64;\
                func \
            } \
            break; \
        }\



