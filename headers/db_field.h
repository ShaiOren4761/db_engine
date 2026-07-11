#ifndef FIELD_H
#define FIELD_H

#include "db_types.h"
#include <stdbool.h>

typedef struct db_table_schema db_table_schema_t;

typedef struct __attribute__((packed)){
    char name[128];
    db_builtin_type_t type;
} db_field_schema_t;

bool db_schema_table_add_field(db_table_schema_t* schema, const char* field_name, db_builtin_type_t type);

#endif
