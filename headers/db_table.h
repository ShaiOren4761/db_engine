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
    size_t records; // how many rows in this talbe
} db_table_schema_t;

db_table_schema_t* db_table_schema_create(const char* table_name);
void db_table_destroy(db_table_schema_t* schema);
void db_table_print_properties(db_table_schema_t* table);
// TODO: add the field addition function from db_field.h
#endif 

// TODO:
// db_field_schema_t currently supports builtin types only
// Add support (somehow) for any type - generic type "db_type"? NOT YET
// There is a way to this