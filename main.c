#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db_schema.h"
#include "db_types.h"
#include "db_writer.h"


typedef struct {
    __uint32_t ID;
    __uint8_t age;
    bool employd;
    __uint8_t gender;
} row;

void print_rows(char* buffer, int amount);

int main(){

    // Create table
    db_table_schema_t* My_Table = db_create_table_schema("First_Table"); //0 fields, 0 types, only name
    
    bool res = db_table_schema_add_field(My_Table, "ID", BUILTIN_TYPE_UINT32);
    res = db_table_schema_add_field(My_Table, "age", BUILTIN_TYPE_UINT8);
    res = db_table_schema_add_field(My_Table, "employed", BUILTIN_TYPE_BOOL);
    res = db_table_schema_add_field(My_Table, "gender", BUILTIN_TYPE_UINT8); //256 options just in case

    print_table_properties(My_Table);

    // Write a row
    char* buffer = malloc(sizeof(row)*10); //a zillion memory please

    db_table_buffer_writer_t* writer;
    writer = db_buffer_writer_create(My_Table, buffer);

    row r1 = {123456789, 99, true, 50};
    row r2 = {987654321, 22, false, 17};
    
    db_buffer_writer_write(writer, &r1);
    db_buffer_writer_write(writer, &r2);
    
    print_rows(buffer, 2);

    return 0;
}

void print_rows(char* buffer, int amount){ //print x rows..
    row* r = (row*)buffer;
    for (int i=0; i < amount; i++){
        printf("row: %d -- ID: %d | age: %d | employed: %d | gender: %d\n", i, r->ID, r->age, r->employd, r->gender);
        r++;
    }
}


// why press play when this fun little game can be played:
//gcc main.c src/db_writer.c src/db_schema.c src/db_types.c -Iheaders -o db