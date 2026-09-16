#ifndef PARSER_H
#define PARSER_H

#include "db_reader.h"
#include "../3rdparty/parson.h"


char* db_parser_table_to_json(db_table_buffer_reader_t* reader, int nof);

#endif 