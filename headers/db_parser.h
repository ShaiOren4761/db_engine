#ifndef PARSER_H
#define PARSER_H

#include "db_reader.h"
#include "../3rdparty/parson.h"


char* db_parser_table_to_json(db_table_buffer_reader_t* reader, int nof);
void db_parser_json_to_table(char* json, db_table_schema_t** out_schema, char** out_buffer);
static bool json_field_to_binary(JSON_Object *object, const char *name, db_builtin_type_t type, char *dest);

#endif 