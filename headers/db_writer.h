#ifndef WRITER_H
#define WRITER_H

#include <stddef.h>
#include "db_schema.h"


typedef struct {
    db_table_schema_t* schema;
    char* buffer;
    // size_t capacity;
    // size_t offset; 
    // size_t rows_written; 
} db_table_buffer_writer_t;

#endif

