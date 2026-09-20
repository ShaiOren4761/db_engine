#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "db_types.h"

size_t db_builtin_type_size(db_builtin_type_t* type) {
    switch(*type){
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

const char* db_builtin_type_to_name(db_builtin_type_t type)
{
    switch (type) {
        case BUILTIN_TYPE_UINT8:   return "uint8";
        case BUILTIN_TYPE_UINT16:  return "uint16";
        case BUILTIN_TYPE_UINT32:  return "uint32";
        case BUILTIN_TYPE_UINT64:  return "uint64";
        case BUILTIN_TYPE_UINT128: return "uint128";
        case BUILTIN_TYPE_INT32:   return "int32";
        case BUILTIN_TYPE_BOOL:    return "bool";
        default:                  return NULL;
    }
}

bool db_builtin_name_to_type(const char* name, db_builtin_type_t* out_type)
{
    if (!name || !out_type) return false;

    if      (strcmp(name, "uint8") == 0)   *out_type = BUILTIN_TYPE_UINT8;
    else if (strcmp(name, "uint16") == 0)  *out_type = BUILTIN_TYPE_UINT16;
    else if (strcmp(name, "uint32") == 0)  *out_type = BUILTIN_TYPE_UINT32;
    else if (strcmp(name, "uint64") == 0)  *out_type = BUILTIN_TYPE_UINT64;
    else if (strcmp(name, "uint128") == 0) *out_type = BUILTIN_TYPE_UINT128;
    else if (strcmp(name, "int32") == 0)   *out_type = BUILTIN_TYPE_INT32;
    else if (strcmp(name, "bool") == 0)    *out_type = BUILTIN_TYPE_BOOL;
    else return false;

    return true;
}

