#include <stdio.h>
#include "db_reader.h"
#include "db_table.h"
#include <stdlib.h>

db_table_buffer_reader_t* db_buffer_reader_create(db_table_schema_t* table, char* buffer){
    db_table_buffer_reader_t* reader = malloc(sizeof(db_table_buffer_reader_t));
    if (reader == NULL) {
        fprintf(stderr, "Failed to allocate memory for db_table_buffer_reader_t\n");
        return NULL;
    }
    reader->buffer = buffer;
    reader->table = table;
    return reader;
}

void* db_buffer_reader_get_pointer(db_table_buffer_reader_t* reader, size_t row_index){
    if (row_index >= reader->table->records) {
        fprintf(stderr, "Row index out of bounds\n");
        return NULL;
    }

    void* row_pointer = reader->buffer;
    row_pointer += reader->table->row_size * row_index;
    return row_pointer;
} 


void db_buffer_reader_read(db_table_buffer_reader_t* reader, char* dest, size_t row_amount, size_t start_index){ // TODO..
    void* buffer = reader->buffer; // table data
    db_field_schema_t* fields = reader->table->fields; // table fields
    size_t fields_count = reader->table->field_count;
    size_t rows_amount = reader->table->records;
    
    
}

void db_buffer_reader_destroy(db_table_buffer_reader_t* reader){
    if (reader != NULL) {
        free(reader);
    }
}
