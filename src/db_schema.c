#include <stdio.h>
#include <db_schema.h>

db_table_schema_t* db_create_table_schema_create(const char* table_name){
    db_table_schema_t* schema = malloc(sizeof(db_table_schema_t));
    if (!schema) {
        fprintf(stderr, "Failed to allocate memory for table schema\n");
        return NULL;
    }
    strncpy(schema->name, table_name, sizeof(schema->name) - 1);
    schema->name[sizeof(schema->name) - 1] = '\0'; // Ensure null-termination
    schema->types = NULL; // Initialize types pointer to NULL
    return schema;
}

void db_table_schema_destroy(db_table_schema_t* schema){
    if (schema) {
        free(schema->types); // Deep destruction
        free(schema);
    }
}

/* GPT Addition, necessary?
bool db_table_schema_add_field(
    db_table_schema_t* schema,
    const char* field_name,
    db_builtin_type_t type
);
*/