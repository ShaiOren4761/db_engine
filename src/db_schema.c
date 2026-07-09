// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include "db_schema.h"


// db_table_schema_t* db_schema_create_table(const char* table_name){
//     db_table_schema_t* schema = malloc(sizeof(db_table_schema_t));
//     if (!schema) {
//         fprintf(stderr, "Failed to allocate memory for table schema\n");
//         return NULL;
//     }
//     strncpy(schema->name, table_name, sizeof(schema->name) - 1);
//     schema->name[sizeof(schema->name) - 1] = '\0'; // Ensure null-termination
//     schema->types = NULL; // Initialize types pointer to NULL
//     schema->row_size=0;
//     return schema;
// }

// void db_schema_table_destroy(db_table_schema_t* schema){
//     if (schema) {
//         free(schema->types); // Deep destruction
//         free(schema);
//     }
// }

// bool db_schema_table_add_field(db_table_schema_t* schema, const char* field_name, db_builtin_type_t type){
//     if (schema->field_count == 256) return false;
    
//     db_field_schema_t new_field;
//     strcpy(new_field.name, field_name);
//     new_field.type = type;
//     memcpy(schema->fields + (schema->field_count), &new_field, sizeof(db_field_schema_t)); 
//     schema->field_count++;
//     schema->row_size += db_builtin_type_size(type);
//     return true;
// }

// void db_schema_table_print_properties(db_table_schema_t* table){
//     if (!table) return;
//     printf("table name: %s\n", table->name);
//     printf("fields:");
//     for (int i = 0; i < table->field_count; i++){
//         printf(" %s |", table->fields[i].name);
//     }
//     printf("\nrow size: %zu\n", table->row_size);
// }

