#include "db_parser.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "db_reader.h"
#include "db_writer.h"
#include "db_table.h"

       
       
char* db_parser_table_to_json(db_table_buffer_reader_t* reader, int nof){

    db_table_schema_t* schema = reader->schema;

    // Init Serilized JSON string
    JSON_Value* root_value = json_value_init_object();
    JSON_Object* root_object = json_value_get_object(root_value);
    char* serialized_string = NULL;
    
    // Table name
    json_object_set_string(root_object, "table_name", schema->name);
    
    // SCHEMA
    // Init schema array
    JSON_Value* schema_value = json_value_init_array();
    JSON_Array* schema_array = json_value_get_array(schema_value);
    json_object_set_value(root_object, "fields", schema_value);
    
    // Write all fields into an array object
    for (int i = 0; i < reader->schema->field_count; i++){

            JSON_Value *field_value = json_value_init_object();
            JSON_Object *field_object = json_value_get_object(field_value);

            char* field_name = schema->fields[i].name;
            const char* field_type = db_builtin_type_to_name(reader->schema->fields[i].type);

            json_object_set_string(field_object, "name", field_name);
            json_object_set_string(field_object, "type", field_type);
            
            json_array_append_value(schema_array, field_value);
    }


    // DATA
    // Init rows array
    JSON_Value* rows_value = json_value_init_array();
    JSON_Array* rows_array = json_value_get_array(rows_value);
    json_object_set_value(root_object, "rows", rows_value);
    
    // For each row, write all fields into an array object
    for (int i = 0; i < nof; i++){

        JSON_Value *row_value = json_value_init_object();
        JSON_Object *row_object = json_value_get_object(row_value);
        void* row = db_buffer_reader_get_pointer(reader, i);

        for (int f = 0; f < schema->field_count; f++){

            char* field_name = schema->fields[f].name;
            db_builtin_type_t field_type = schema->fields[f].type;

            switch(schema->fields[f].type){
                case BUILTIN_TYPE_UINT8:{
                    __uint8_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(row_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT16:{
                    __uint16_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(row_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT32:{
                    __uint32_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(row_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT64:{
                    __uint64_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(row_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT128:{
                    __uint128_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(row_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_INT32:{
                    __int32_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(row_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_BOOL:{
                    bool val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_boolean(row_object, field_name, val);
                    break;
                }
            }
            
            row += db_builtin_type_size(&field_type);
        }
        
        json_array_append_value(rows_array, row_value);
    }

    // Export JSON
    serialized_string = json_serialize_to_string_pretty(root_value);
    puts(serialized_string); // STDOUT
    json_value_free(root_value);

    return serialized_string;
}

void db_parser_json_to_table(char* json, db_table_schema_t** out_schema, char** out_buffer){
    // JSON to tree
    JSON_Value* root_value = json_parse_string(json);
    if (root_value == NULL) {
        fprintf(stderr, "db_parser_json_to_table: JSON is null\n");
        return;
    }

    JSON_Object* root_object = json_value_get_object(root_value);
    if (root_object == NULL) {
       fprintf(stderr, "db_parser_json_to_table: Unexpected JSON structure\n");
        return;
    }

    // Tree to 3 main json objects
    const char* table_name = json_object_get_string(root_object, "table_name");
    JSON_Array* fields = json_object_get_array(root_object, "fields");
    JSON_Array* rows = json_object_get_array(root_object, "rows");
    
    if (table_name == NULL || fields == NULL || rows == NULL) {
       fprintf(stderr, "db_parser_json_to_table: null value exception\n");
        return;
    }

    // Out schema - copy table name and fields
    db_table_schema_t* schema = db_table_schema_create(table_name);

    for (size_t f = 0; f < json_array_get_count(fields); f++) {

        JSON_Object* field = json_array_get_object(fields, f);
        if (field == NULL) {
            fprintf(stderr, "db_parser_json_to_table: null field in json file\n");
            return;
        }
        
        const char* name = json_object_get_string(field, "name");
        const char* type_name = json_object_get_string(field, "type");

        if (name == NULL || type_name == NULL) {
            fprintf(stderr, "db_parser_json_to_table: null field name or type in json file\n");
            return;
        }
        
        db_builtin_type_t field_type;
        bool result = db_builtin_name_to_type(type_name, &field_type);
        if (!result){
            fprintf(stderr, "db_parser_json_to_table: unkown field type\n");
            return;
        }
    
        db_table_schema_add_field(schema, name, field_type);
    }

    // Out buffer - copy table data

    size_t row_count = json_array_get_count(rows);

    // Reject zero-width rows and allocation-size overflow.
    if (schema->row_size == 0 || row_count > SIZE_MAX / schema->row_size) {
        db_table_schema_destroy(schema);
        json_value_free(root_value);
        return;
    }

    size_t buffer_size = row_count * schema->row_size;

    /* Allocate at least one byte so an empty table is handled consistently. */
    char *buffer = malloc(buffer_size ? buffer_size : 1);
    char *row = malloc(schema->row_size);

    db_table_buffer_writer_t *schema_writer = NULL;

    if (!buffer || !row)
        goto data_failure;

    schema_writer = db_writer_buffer_create(schema, buffer);
    if (!schema_writer)
        goto data_failure;

    for (size_t r = 0; r < row_count; r++) {
        JSON_Object *row_object = json_array_get_object(rows, r);
        if (!row_object)
            goto data_failure;

        char *dest = row;

        for (size_t f = 0; f < schema->field_count; f++) {
            const char *name = schema->fields[f].name;
            db_builtin_type_t type = schema->fields[f].type;

            if (!json_field_to_binary(row_object, name, type, dest)) {
                fprintf(stderr, "Invalid value at row %zu, field %s\n", r, name);
                goto data_failure;
            }

            dest += db_builtin_type_size(&type);
        }

        db_writer_buffer_write(schema_writer, row);
    }

    /* The writer copied each row, so these temporary objects can go. */
    free(row);
    db_writer_buffer_destroy(schema_writer);
    json_value_free(root_value);

    *out_schema = schema;
    *out_buffer = buffer;
    return;

    data_failure:
    free(row);
    db_writer_buffer_destroy(schema_writer);
    free(buffer);
    db_table_schema_destroy(schema);
    json_value_free(root_value);
    return;
}


static bool json_field_to_binary(JSON_Object *object, const char *name, db_builtin_type_t type, char *dest){
    if (type == BUILTIN_TYPE_BOOL) {
        int value = json_object_get_boolean(object, name);
        if (value == -1) return false;

        bool converted = value != 0;
        memcpy(dest, &converted, sizeof converted);
        return true;
    }

    if (!json_object_has_value_of_type(object, name, JSONNumber))
        return false;

    double value = json_object_get_number(object, name);

    if (!isfinite(value))
        return false;

    switch (type) {
        case BUILTIN_TYPE_UINT8: {
            if (value < 0 || value > UINT8_MAX) return false;
            uint8_t converted = (uint8_t)value;
            if ((double)converted != value) return false;
            memcpy(dest, &converted, sizeof converted);
            return true;
        }

        case BUILTIN_TYPE_UINT16: {
            if (value < 0 || value > UINT16_MAX) return false;
            uint16_t converted = (uint16_t)value;
            if ((double)converted != value) return false;
            memcpy(dest, &converted, sizeof converted);
            return true;
        }

        case BUILTIN_TYPE_UINT32: {
            if (value < 0 || value > UINT32_MAX) return false;
            uint32_t converted = (uint32_t)value;
            if ((double)converted != value) return false;
            memcpy(dest, &converted, sizeof converted);
            return true;
        }

        case BUILTIN_TYPE_INT32: {
            if (value < INT32_MIN || value > INT32_MAX) return false;
            int32_t converted = (int32_t)value;
            if ((double)converted != value) return false;
            memcpy(dest, &converted, sizeof converted);
            return true;
        }

        case BUILTIN_TYPE_UINT64: {
            if (value < 0 || value > 9007199254740991.0) return false;
            uint64_t converted = (uint64_t)value;
            if ((double)converted != value) return false;
            memcpy(dest, &converted, sizeof converted);
            return true;
        }

        case BUILTIN_TYPE_UINT128: {
            if (value < 0 || value > 9007199254740991.0) return false;
            __uint128_t converted = (__uint128_t)value;
            if ((double)converted != value) return false;
            memcpy(dest, &converted, sizeof converted);
            return true;
        }

        default:
            return false;
    }
}