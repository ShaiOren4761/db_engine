#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db_context.h"
#include "db_table.h"
#include "db_field.h"
#include "db_types.h"
#include "db_writer.h"


typedef struct __attribute__((packed)){
    __uint32_t ID;
    __uint8_t age;
    bool employd;
    __uint8_t gender;
} row;

void print_rows(char* buffer, int amount);

int main(){
 
    // Create db
    db_context_schema_t* db = malloc(sizeof(db_context_schema_t));
    strcpy(db->name, "my_db");

    // Create tables in db
    char s[32];
    for (int i=0; i<8; i++){
        snprintf(s, sizeof(s), "table %d", i);
        db_context_add_table(db, s);
    }
    db_context_print_properties(db);
    
    // Add fields to table 0

    db_table_schema_t* table_0 = db_context_get_table(db, "table 0");

    db_field_add_field_to_table(table_0, "ID", BUILTIN_TYPE_UINT32);
    db_field_add_field_to_table(table_0, "age", BUILTIN_TYPE_UINT8);
    db_field_add_field_to_table(table_0, "employed", BUILTIN_TYPE_BOOL);
    db_field_add_field_to_table(table_0, "gender", BUILTIN_TYPE_UINT8); //256 options just in case

    db_table_print_properties(table_0);

    
    if (table_0) printf("table_get success, pointer: %s\n", table_0->name);
  
    // Write a row
    char* buffer = malloc(sizeof(row)*10); //a zillion memory please

    db_table_buffer_writer_t* writer;
    writer = db_writer_buffer_create(table_0, buffer);

    row r1 = {123456789, 99, true, 50};
    row r2 = {987654321, 22, false, 17};
    
    db_writer_buffer_write(writer, &r1);
    db_writer_buffer_write(writer, &r2);
    
    print_rows(buffer, 2);
    
    free(buffer);
    db_writer_buffer_destroy(writer);
    return 0;
}

void print_rows(char* buffer, int amount){ //print x rows.. TODO convert to reader
    row* r = (row*)buffer;
    for (int i=0; i < amount; i++){
        printf("row: %d -- ID: %d | age: %d | employed: %d | gender: %d\n", i, r->ID, r->age, r->employd, r->gender);
        r++;
    }
}


// why press play when this fun little game can be played:
//gcc main.c src/db_context.c src/db_writer.c src/db_table.c src/db_field.c src/db_types.c -Iheaders -o db
