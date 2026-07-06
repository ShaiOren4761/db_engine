#include <stdio.h>
#include "db_writer.h"


db_table_buffer_writer_t* db_buffer_writer_create(db_table_schema_t* schema, char* buffer, size_t capacity){
    db_table_buffer_writer_t* writer = malloc(sizeof(db_table_buffer_writer_t));
    if (!writer) {
        return NULL;
    }
    writer->schema = schema;
    writer->buffer = buffer;
    // writer->capacity = capacity;
    // writer->offset = 0;
    // writer->rows_written = 0;
    return writer;
}

void db_buffer_writer_destroy(db_table_buffer_writer_t* writer) {
    if (writer) {
        free(writer);
    }
}

//The writer does not necessarily own the buffer.