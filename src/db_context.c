#include <stdio.h>
#include "db_context.h"
#include "db_table.h"

bool db_context_create_context(db_context_schema_t* db, const char* name){
    return NULL;
}


bool db_context_add_table(db_context_schema_t* db, const char* table_name){
    if (db->num_of_entries == 8){ //TODO yeah that's a const. that's bad.
        fprintf(stderr, "DB %s is full, failed to add table\n", db->name);
        return NULL;
    }

    db_table_schema_t* new_table = db_schema_create_table(table_name);
    if (!new_table) return NULL;

    db->tables[db->num_of_entries] = new_table;
    db->num_of_entries++;

    return true;
}

__uint8_t db_context_get_num_of_entries(db_context_schema_t* db){
    return 0;
}

void db_context_print_properties(db_context_schema_t* db){
    if (!db) return;
    printf("db name: %s\n", db->name);
    printf("tables:");
    for (int i = 0; i < db->num_of_entries ; i++){
        printf(" %s |", db->tables[i]->name);
    }
    printf("\ntables amount: %d\n", db->num_of_entries);
}

