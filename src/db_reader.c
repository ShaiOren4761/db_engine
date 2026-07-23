#include <stdio.h>
#include "db_reader.h"
#include <stdlib.h>

db_table_buffer_reader_t* db_buffer_reader_create(){
    db_table_buffer_reader_t* reader = malloc(sizeof(db_table_buffer_reader_t));
    if (reader == NULL) {
        fprintf(stderr, "Failed to allocate memory for db_table_buffer_reader_t\n");
        return NULL;
    }

    return reader;
}

void db_buffer_reader_read(db_table_buffer_reader_t* reader, void* buffer){

}

void db_buffer_reader_destroy(){

}
