#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

typedef enum {
    BUILTIN_TYPE_UINT8,
    BUILTIN_TYPE_UINT16,
    BUILTIN_TYPE_UINT32,
    BUILTIN_TYPE_UINT64,
    BUILTIN_TYPE_UINT128,
    BUILTIN_TYPE_INT32,
    BUILTIN_TYPE_BOOL
} db_builtin_type_t;

size_t db_builtin_type_size(db_builtin_type_t type);

#endif
