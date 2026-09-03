#ifndef FIELD_H
#define FIELD_H

#include "db_types.h"
#include <stdbool.h>

typedef struct db_table_schema db_table_schema_t;

typedef struct __attribute__((packed)){
    char name[128];
    db_builtin_type_t type;
} db_field_schema_t;

#endif
