#ifndef READER_H
#define READER_H

#include <stdio.h>
#include "db_table.h"

typedef struct {
    db_table_schema_t* schema;
    char* buffer;
} db_table_buffer_reader_t;

db_table_buffer_reader_t* db_buffer_reader_create(db_table_schema_t* table, char* buffer);
void* db_buffer_reader_get_pointer(db_table_buffer_reader_t* reader, size_t row_index); // return a pointer of a row.
void db_buffer_reader_read(db_table_buffer_reader_t* reader, char* dest, size_t row_amount, size_t start_index); 
void db_buffer_reader_destroy(db_table_buffer_reader_t* reader);


#endif 