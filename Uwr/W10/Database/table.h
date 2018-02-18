//
// Created by Tooster on 11.02.2018.
//

#ifndef CUWR_TABLE_H
#define CUWR_TABLE_H

#include "record.h"
#include "field.h"

typedef struct _table {
    char *table_name;

    unsigned int columns_count;
    char **column_names; // list of strings
    enum DB_FIELD_TYPE *column_types; // list of types

    unsigned int records_count;
    Record **records;
} Table;

/**
 * Creates new table
 */
Table *_DB_TABLE_new(const char *table_name);

/**
 * Adds new column at the end of the table filling it with NULLs
 * @param table
 * @param col_name
 * @param col_type
 */
void _DB_TABLE_column_push(Table *table, char *col_name, enum DB_FIELD_TYPE col_type);

/**
 * Inserts record into table
 * @param table
 * @param record
 */
void _DB_TABLE_insert(Table *table, Record *record);

/**
 * Destroys the table
 * @param table table to destroy
 */
void _DB_TABLE_destroy(Table *table);

#endif //CUWR_TABLE_H
