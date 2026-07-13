#ifndef DB_CONTEXT
#define DB_CONTEXT

#include <stdio.h>
#include <stdbool.h>
#include <db_table.h>

typedef struct {
    char name[128];
    __uint8_t num_of_entries;
    db_table_schema_t* tables[8]; 
} db_context_schema_t; // Should I just name this db_context?

bool db_context_create_context(db_context_schema_t* db, const char* name);
bool db_context_add_table(db_context_schema_t* db, const char* table_name);
__uint8_t db_context_get_num_of_entries(db_context_schema_t* db);
void db_context_print_properties(db_context_schema_t* db);

#endif