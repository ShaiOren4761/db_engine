#include <stdio.h>
#include "db_schema.h"
#include "db_types.h"
#include "db_writer.h"






int main(){

    db_table_schema_t* My_Table = db_create_table_schema("First_Table"); //0 fields, 0 types, only name
    
    bool res = db_table_schema_add_field(My_Table, "ID", BUILTIN_TYPE_UINT32);
    res = db_table_schema_add_field(My_Table, "age", BUILTIN_TYPE_UINT8);
    res = db_table_schema_add_field(My_Table, "employed", BUILTIN_TYPE_BOOL);
    res = db_table_schema_add_field(My_Table, "gender", BUILTIN_TYPE_UINT8); //256 options just in case

    print_table_properties(My_Table);

    return 0;
}

// why press play when this fun little game can be played:
//gcc main.c src/db_writer.c src/db_schema.c src/db_types.c -Iheaders -o db