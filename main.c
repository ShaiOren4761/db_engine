#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db_context.h"
#include "db_table.h"
#include "db_field.h"
#include "db_types.h"
#include "db_writer.h"
#include "db_reader.h"
#include "db_parser.h"

// example row type for testing
typedef struct __attribute__((packed)) row_example_struct{
    __uint32_t ID;
    __uint8_t age;
    bool employd;
    __uint8_t gender;
} row;

void print_rows(db_table_schema_t* table, char* buffer, int amount);

int main(){
    
    // Create db
    db_context_schema_t* db = db_context_create_context("my_db");

    // Create tables in db
        char s[32];
        for (int i=0; i<8; i++){
            snprintf(s, sizeof(s), "table_%d", i);
            db_table_schema_t* temp_schema = db_table_schema_create(s);
            db_context_add_table(db, temp_schema);
        }
        //db_context_print_properties(db);

    // Add fields to table_0 && table_1
        
        db_table_schema_t* table_0 = db_context_get_table(db, db->tables[0]->name);

            db_table_schema_add_field(table_0, "ID", BUILTIN_TYPE_UINT32);
            db_table_schema_add_field(table_0, "age", BUILTIN_TYPE_UINT8);
            db_table_schema_add_field(table_0, "employed", BUILTIN_TYPE_BOOL);
            db_table_schema_add_field(table_0, "gender", BUILTIN_TYPE_UINT8);

            db_table_schema_print_properties(table_0);

        db_table_schema_t* table_1 = db_context_get_table(db, db->tables[1]->name);

            db_table_schema_add_field(table_1, "ID", BUILTIN_TYPE_UINT32);
            db_table_schema_add_field(table_1, "age", BUILTIN_TYPE_UINT8);
            db_table_schema_add_field(table_1, "employed", BUILTIN_TYPE_BOOL);
            db_table_schema_add_field(table_1, "gender", BUILTIN_TYPE_UINT8);

            db_table_schema_print_properties(table_1);


    // Make memory for rows in table_0 and table_1
        char* buffer_table_0 = malloc(sizeof(row)*10); 
        char* buffer_table_1 = malloc(sizeof(row)*10);
    
    
    // write rows
        db_table_buffer_writer_t* writer_table_0;
        writer_table_0 = db_writer_buffer_create(table_0, buffer_table_0);
    
        row r1 = {123456789, 99, true, 50};
        row r2 = {987654321, 22, false, 17};
        
        db_writer_buffer_write(writer_table_0, &r1);
        db_writer_buffer_write(writer_table_0, &r2);
        
        print_rows(table_0, buffer_table_0, 2);
        
    // reader
    
        db_table_buffer_reader_t* reader_table_0 = db_buffer_reader_create(table_0, buffer_table_0);

        db_buffer_reader_read(reader_table_0, buffer_table_1, 1, 1); // copy 2nd row into table_1 from table_0
        //void* row_pointer = db_buffer_reader_get_pointer(reader, 1);
        print_rows(table_1, buffer_table_1, 1);



    // serde testing

        // serialize table_0
        char* serialized_table_0 = db_parser_table_to_json(reader_table_0, 2);

        // de-serialize table_0 into table_0_de
        db_table_schema_t* table_0_de = NULL;
        char* buffer_table_0_de = NULL;
        db_parser_json_to_table(serialized_table_0, &table_0_de, &buffer_table_0_de);
            
        printf("table_0_de properties and data: \n");
        db_table_schema_print_properties(table_0_de);
        print_rows(table_0_de, buffer_table_0_de, table_0_de->records);

    // WRITER TO FILE TESTING
        //db_writer_to_bin_file(writer_table_0);
            

    // free()
        free(buffer_table_0);
        free(buffer_table_1);
        db_writer_buffer_destroy(writer_table_0);

    return 0;
}

void print_rows(db_table_schema_t* table, char* buffer, int amount){ //print x rows.. for row type example
    row* r = (row*)buffer;
    printf("table %s requested rows: \n", table->name);
    for (int i=0; i < amount; i++){
        printf("row: %d -- ID: %d | age: %d | employed: %d | gender: %d\n", i, r->ID, r->age, r->employd, r->gender);
        r++;
    }
    printf("\n");
}


// compile command
// gcc main.c src/* -Iheaders -o db
