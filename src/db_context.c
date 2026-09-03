#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_context.h"
#include "db_table.h"

db_context_schema_t* db_context_create_context(const char* name){
    db_context_schema_t* ctx = malloc(sizeof(db_context_schema_t));
    if (!ctx) {
        fprintf(stderr, "Failed to allocate memory for DB context\n");
        return NULL;
    }
    strncpy(ctx->name, name, sizeof(ctx->name) - 1);
    ctx->name[sizeof(ctx->name) - 1] = '\0'; // Ensure null-termination
    ctx->num_of_entries=0;
    return ctx;
}

bool db_context_add_table(db_context_schema_t* db, db_table_schema_t* schema){
    if (db->num_of_entries == 8){ //TODO yeah that's a const. that's bad.
        fprintf(stderr, "DB %s is full, failed to add table\n", db->name);
        return NULL;
    }
    if (!schema){
        fprintf(stderr, "null table cannot be added to DB\n");
        return NULL;
    }

    db->tables[db->num_of_entries] = schema;
    db->num_of_entries++;

    return true;
}

uint8_t db_context_get_nof_entries(db_context_schema_t* db){
    return db->num_of_entries; // Why did I create a function that's just a getter for a non-private member of context? THIS AIN'T OOP
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

db_table_schema_t* db_context_get_table(db_context_schema_t* db, char* table_name){
    if (!table_name) return false;
    
    for (int i = 0; i < db->num_of_entries; i++)
    {
        if (strcmp(db->tables[i]->name, table_name) == 0) return db->tables[i];
    }

    fprintf(stderr, "ERROR - db_context_get_table: table \"%s\" not found\n", table_name);
    return NULL;
    
}