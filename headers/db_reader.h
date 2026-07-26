#ifndef READER_H
#define READER_H

#include <stdio.h>
#include "db_table.h"

typedef struct {
    db_table_schema_t* table;
    char* buffer;
} db_table_buffer_reader_t;

db_table_buffer_reader_t* db_buffer_reader_create(db_table_schema_t* table, char* buffer);
void db_buffer_reader_read(db_table_buffer_reader_t* reader/*, void* buffer*/); // reader already has a buffer pointer.. why send it again? 
void db_buffer_reader_destroy();

#endif 
