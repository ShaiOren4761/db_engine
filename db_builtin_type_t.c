#include <stdio.h>

typedef enum { //Am I supposed to give them a value manually? Imma just do. God is great.
    BUILTIN_TYPE_UINT8,
    BUILTIN_TYPE_UINT16,
    BUILTIN_TYPE_UINT32,
    BUILTIN_TYPE_UINT64,
    BUILTIN_TYPE_UINT128,
    BUILTIN_TYPE_INT32,
    BUILTIN_TYPE_BOOL
} db_builtin_type_t;

size_t db_builtin_type_size(db_builtin_type_t type) {
    switch(type){
        case BUILTIN_TYPE_UINT8:
            return 1;
        case BUILTIN_TYPE_UINT16:
            return 2;
        case BUILTIN_TYPE_UINT32:
            return 4;
        case BUILTIN_TYPE_UINT64:
            return 8;
        case BUILTIN_TYPE_UINT128:
            return 16;
        case BUILTIN_TYPE_INT32:
            return 4;
        case BUILTIN_TYPE_BOOL:
            return 1;
        default:
            return 0; // Unknown type
    }
}

int main() { // TODO = who the fuck makes a main function for builtin??? delete asap

    return 0;
}