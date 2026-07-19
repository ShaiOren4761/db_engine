#include <stdio.h>
#include "db_writer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

db_table_buffer_writer_t* db_writer_buffer_create(db_table_schema_t* schema, char* buffer){
    db_table_buffer_writer_t* writer = malloc(sizeof(db_table_buffer_writer_t));
    if (!writer) {
        return NULL;
    }
    writer->schema = schema;
    writer->buffer = buffer;
    writer->offset = 0;
    return writer;
}

void db_writer_buffer_destroy(db_table_buffer_writer_t* writer) {
    if (writer) {
        free(writer);
    }
}

bool db_writer_buffer_write(db_table_buffer_writer_t* writer, void* row){
    memcpy(writer->buffer + writer->offset, row, writer->schema->row_size);
    writer->offset += writer->schema->row_size;    
}
