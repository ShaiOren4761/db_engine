#ifndef TABLE_H
#define TABLE_H

#include "db_types.h"
#include "db_field.h"
#include <stdbool.h>

typedef struct __attribute__((packed)) db_table_schema{
    char name[128];
    db_field_schema_t fields[256]; //bigass table
    db_builtin_type_t* types;
    size_t field_count;
    size_t row_size; 
} db_table_schema_t;

db_table_schema_t* db_schema_create_table(const char* table_name);
void db_schema_table_destroy(db_table_schema_t* schema);
void db_schema_table_print_properties(db_table_schema_t* table);

#endif 
