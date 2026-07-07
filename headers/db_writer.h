#ifndef WRITER_H
#define WRITER_H

#include <stddef.h>
#include "db_schema.h"
#include <stdbool.h>

typedef struct {
    db_table_schema_t* schema;
    char* buffer;
    // size_t capacity;
    size_t offset; 
    // size_t rows_written; 
} db_table_buffer_writer_t;

db_table_buffer_writer_t* db_buffer_writer_create(db_table_schema_t* schema, char* buffer, size_t capacity);
void db_buffer_writer_destroy(db_table_buffer_writer_t* writer);
bool db_buffer_writer_write(db_table_buffer_writer_t* writer, void* row);

#endif

