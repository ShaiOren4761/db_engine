#include <stdio.h>
#include "db_reader.h"
#include "db_table.h"
#include <stdlib.h>

db_table_buffer_reader_t* db_buffer_reader_create(){
    db_table_buffer_reader_t* reader = malloc(sizeof(db_table_buffer_reader_t));
    if (reader == NULL) {
        fprintf(stderr, "Failed to allocate memory for db_table_buffer_reader_t\n");
        return NULL;
    }

    return reader;
}

void db_buffer_reader_read(db_table_buffer_reader_t* reader){
    void* buffer = reader->buffer; // table data
    db_field_schema_t* fields = reader->schema->fields; // table field    
}

// void print_rows(char* buffer, int amount){ //print x rows.. TODO convert to reader
//     row* r = (row*)buffer;
//     for (int i=0; i < amount; i++){
//         printf("row: %d -- ID: %d | age: %d | employed: %d | gender: %d\n", i, r->ID, r->age, r->employd, r->gender);
//         r++;
//     }
// }


void db_buffer_reader_destroy(){

}
