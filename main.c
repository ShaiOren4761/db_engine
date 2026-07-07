#include <stdio.h>
#include "db_schema.h"
#include "db_types.h"
#include "db_writer.h"






int main(){

    db_table_schema_t* My_Table = db_create_table_schema("First_Table");


    return 0;
}

// why press play when this fun little game can be played:
//gcc main.c src/db_writer.c src/db_schema.c src/db_types.c -Iheaders -o db