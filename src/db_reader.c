#include <stdio.h>
#include "db_reader.h"
#include "db_table.h"
#include <stdlib.h>
#include <string.h>

db_table_buffer_reader_t* db_buffer_reader_create(db_table_schema_t* schema, char* buffer){
    db_table_buffer_reader_t* reader = malloc(sizeof(db_table_buffer_reader_t));
    if (reader == NULL) {
        fprintf(stderr, "Failed to allocate memory for db_table_buffer_reader_t\n");
        return NULL;
    }
    reader->buffer = buffer;
    reader->schema = schema;
    return reader;
}

void* db_buffer_reader_get_pointer(db_table_buffer_reader_t* reader_src, size_t row_index){
    if (!reader_src){
        fprintf(stderr, "ERROR: reader_get_pointer - reader is null\n");
        return NULL;
    }
    if (row_index >= reader_src->schema->records) {
        fprintf(stderr, "ERROR: reader_get_pointer - Row index out of bounds\n");
        return NULL;
    }

    void* row_pointer = reader_src->buffer;
    row_pointer += reader_src->schema->row_size * row_index;
    return row_pointer;
} 

/*
Copy X rows into target address from a starting index
*/
void db_buffer_reader_read(db_table_buffer_reader_t* reader_src, char* dest, size_t n, size_t start_index){
    if (!reader_src){
        fprintf(stderr, "ERROR: reader_read: Reader is null\n");
        return;
    }
    if (!reader_src->buffer) {
        fprintf(stderr, "ERROR: reader_read: Source table null\n");
        return;
    }
    if (start_index >= reader_src->schema->records || start_index+n > reader_src->schema->records){
        fprintf(stderr, "ERROR: reader_read: Row index out of bounds\n");
        return;
    }

    size_t row_size = reader_src->schema->row_size;
    char* source = db_buffer_reader_get_pointer(reader_src, start_index);
    memcpy(dest, source, n*row_size);
    
}

void db_buffer_reader_destroy(db_table_buffer_reader_t* reader_src){
    if (reader_src != NULL) {
        free(reader_src);
    }
}
