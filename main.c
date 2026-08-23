#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db_context.h"
#include "db_table.h"
#include "db_field.h"
#include "db_types.h"
#include "db_writer.h"
#include "db_reader.h"

typedef struct __attribute__((packed)){
    __uint32_t ID;
    __uint8_t age;
    bool employd;
    __uint8_t gender;
} row;

void print_rows(db_table_schema_t* table, char* buffer, int amount);

int main(){
    
    
    // Create db
    db_context_schema_t* db = malloc(sizeof(db_context_schema_t));
    strcpy(db->name, "my_db");

    // Create tables in db
        char s[32];
        for (int i=0; i<8; i++){
            snprintf(s, sizeof(s), "table_%d", i);
            db_context_add_table(db, s);
        }
        //db_context_print_properties(db);

    // Add fields to table_0 && table_1
        
        db_table_schema_t* table_0 = db_context_get_table(db, db->tables[0]->name);

            db_field_add_field_to_table(table_0, "ID", BUILTIN_TYPE_UINT32);
            db_field_add_field_to_table(table_0, "age", BUILTIN_TYPE_UINT8);
            db_field_add_field_to_table(table_0, "employed", BUILTIN_TYPE_BOOL);
            db_field_add_field_to_table(table_0, "gender", BUILTIN_TYPE_UINT8); //256 options just in case

            db_table_print_properties(table_0);

        db_table_schema_t* table_1 = db_context_get_table(db, db->tables[1]->name);

            db_field_add_field_to_table(table_1, "ID", BUILTIN_TYPE_UINT32);
            db_field_add_field_to_table(table_1, "age", BUILTIN_TYPE_UINT8);
            db_field_add_field_to_table(table_1, "employed", BUILTIN_TYPE_BOOL);
            db_field_add_field_to_table(table_1, "gender", BUILTIN_TYPE_UINT8); //256 options just in case

            db_table_print_properties(table_1);
        
    // Make memory for rows in table_0 and table_1
        char* buffer_table_0 = malloc(sizeof(row)*10); //a zillion memory please
        char* buffer_table_1 = malloc(sizeof(row)*10); //a zillion memory please
    
    
    // write rows
        db_table_buffer_writer_t* writer_table_0;
        writer_table_0 = db_writer_buffer_create(table_0, buffer_table_0);
    
        row r1 = {123456789, 99, true, 50};
        row r2 = {987654321, 22, false, 17};
        
        db_writer_buffer_write(writer_table_0, &r1);
        db_writer_buffer_write(writer_table_0, &r2);
        
        print_rows(table_0, buffer_table_0, 2);
        
    // READER TESTING
        db_table_buffer_reader_t* reader_table_0 = db_buffer_reader_create(table_0, buffer_table_0);

        db_buffer_reader_read(reader_table_0, buffer_table_1, 1, 1);
        //void* row_pointer = db_buffer_reader_get_pointer(reader, 1);
        print_rows(table_1, buffer_table_1, 1);


    // No memory leaks in this mofo
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


// why press play when this fun little game can be played:
//gcc main.c src/* -Iheaders -o db
