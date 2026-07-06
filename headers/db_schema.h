#ifndef SCHEMA_H
#define SCHEMA_H

#include "db_types.h"

typedef struct {
    char name[128];
    db_builtin_type_t type;
    //size_t offset; 
    //size_t size;  
} db_field_schema_t; //__attribute__((packed)) doesn't work in headers..?


typedef struct {
    char name[128];
    db_field_schema_t fields[256]; //bigass table
    db_builtin_type_t* types;
    //size_t field_count; 
    //size_t row_size; 
} db_table_schema_t; //__attribute__((packed)) doesn't work in headers..?


#endif