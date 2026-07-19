#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "db_table.h"
#include "db_field.h"

// why is this method here? What method should a field even have?
bool db_field_add_field_to_table(db_table_schema_t* schema, const char* field_name, db_builtin_type_t type){
    if (schema->field_count == 256) return false;
    
    db_field_schema_t new_field;
    strcpy(new_field.name, field_name);
    new_field.type = type;
    memcpy(schema->fields + (schema->field_count), &new_field, sizeof(db_field_schema_t)); 
    schema->field_count++;
    schema->row_size += db_builtin_type_size(type);
    return true;
}


