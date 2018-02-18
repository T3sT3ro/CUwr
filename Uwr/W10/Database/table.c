//
// Created by Tooster on 11.02.2018.
//

#include "table.h"
#include <string.h>

Table *_DB_TABLE_new(const char *table_name) {
    Table *table = malloc(sizeof(Table));
    if (table == NULL) return NULL;
    table->table_name = calloc(strlen(table_name) + 1, sizeof(char));
    strcpy(table->table_name, table_name);

    table->columns_count = 0;
    table->column_names = NULL;
    table->column_types = NULL;

    table->records_count = 0;
    table->records = NULL;

    return table;
}

void _DB_TABLE_column_push(Table *table, char *col_name, enum DB_FIELD_TYPE col_type) {
    table->columns_count++;
    realloc(table->column_names, table->columns_count * sizeof(char *));
    realloc(table->column_types, table->columns_count * sizeof(enum DB_FIELD_TYPE));

    strcpy(table->column_names[table->columns_count - 1], col_name);
    table->column_types[table->columns_count - 1] = col_type;
}

void _DB_TABLE_insert(Table *table, Record *record) {

}

void _DB_TABLE_destroy(Table *table) {
    for (int i = 0; i < table->records_count; ++i)
        _DB_RECORD_destroy(table->records[i]);
}


