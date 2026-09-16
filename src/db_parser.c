#include "db_parser.h"
#include <string.h>
#include "db_reader.h"
#include "db_table.h"
       
       
       
char* db_parser_table_to_json(db_table_buffer_reader_t* reader, int nof){

    db_table_schema_t* schema = reader->schema;

    // Init Serilized JSON string
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    
    json_object_set_string(root_object, "table_name", schema->name);
    
    // For each row, write all fields
    for (int i = 0; i < nof; i++){

        void* row = db_buffer_reader_get_pointer(reader, i);

        for (int f = 0; f < schema->field_count; f++){

            char* field_name = schema->fields[f].name;
            db_builtin_type_t field_type = schema->fields[f].type;

            switch(schema->fields[f].type){
                case BUILTIN_TYPE_UINT8:{
                    __uint8_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(root_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT16:{
                    __uint16_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(root_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT32:{
                    __uint32_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(root_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT64:{
                    __uint64_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(root_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_UINT128:{
                    __uint128_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(root_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_INT32:{
                    __int32_t val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_number(root_object, field_name, val);
                    break;
                }
                case BUILTIN_TYPE_BOOL:{
                    bool val;
                    memcpy(&val, row, db_builtin_type_size(&field_type));
                    json_object_set_boolean(root_object, field_name, val);
                    break;
                }
            }

            row += db_builtin_type_size(&field_type);
        }
    }

    // Export JSON
    serialized_string = json_serialize_to_string_pretty(root_value);
    puts(serialized_string);
    json_value_free(root_value);

    return serialized_string;
}