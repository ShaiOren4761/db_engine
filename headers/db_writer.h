#ifndef WRITER_H
#define WRITER_H

#include <stddef.h>
#include "db_table.h"
#include <stdbool.h>

typedef struct {
    db_table_schema_t* schema;
    char* buffer;
    // size_t capacity;
    size_t offset; 
    // size_t rows_written; 
} db_table_buffer_writer_t;

db_table_buffer_writer_t* db_writer_buffer_create(db_table_schema_t* schema, char* buffer/*, size_t capacity*/);
void db_writer_buffer_destroy(db_table_buffer_writer_t* writer);
bool db_writer_buffer_write(db_table_buffer_writer_t* writer, void* row);

#endif
