#ifndef FIELD_H
#define FIELD_H

#include "db_types.h"
#include "db_table.h"
#include <stdbool.h>

typedef struct __attribute__((packed)){
    char name[128];
    db_builtin_type_t type;
} db_field_schema_t;

bool db_schema_table_add_field(db_table_schema_t* schema, const char* field_name, db_builtin_type_t type);

#endif
