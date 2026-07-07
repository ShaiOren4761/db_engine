#ifndef SCHEMA_H
#define SCHEMA_H

#include "db_types.h"
#include <stdbool.h>

typedef struct __attribute__((packed)) {
    char name[128];
    db_builtin_type_t type;
    //size_t offset; 
    //size_t size;  
} db_field_schema_t;


typedef struct __attribute__((packed)){
    char name[128];
    db_field_schema_t fields[256]; //bigass table
    db_builtin_type_t* types;
    //size_t field_count; 
    size_t row_size; // TODO: Implement update and usage per field added to schema
} db_table_schema_t;

void db_destroy_table_schema(db_table_schema_t* schema);
db_table_schema_t* db_create_table_schema(const char* table_name);
bool db_table_schema_add_field(db_table_schema_t* schema, const char* field_name, db_builtin_type_t type);

#endif