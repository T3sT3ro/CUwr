//
// Created by Tooster on 11.02.2018.
//

#ifndef CUWR_DATABASE_H
#define CUWR_DATABASE_H

#include <stdbool.h>
#include <stdio.h>
#include "stdlib.h"
#include "table.h"
#include "record.h"
#include "field.h"

typedef struct _database {
    Table **tables;
    unsigned int tables_count;
} Database;

/**
 * Creates new database;
 * @return
 */
Database *DB_NEW();

/**
 * Creates new table with with specified name and columns of given type
 * @param db database to add the table to
 * @param table_name name of the new table
 * @param col_count number of columns in new table
 * @param ... arguments in pairs <char* name, enum DB_FIELD_TYPE type> specifying the column, names should be unique
 *
 * @example DB_TABLE_CREATE(db, "Users", 2, "Nick", DB_FIELD_STRING, "Bananas", DB_FIELD_INT)
 */
void DB_TABLE_CREATE(Database *db, char *table_name, unsigned int col_count, ...);

/**
 * Drops the table with specified name
 * If no table with such name exists, nothing happens
 * @param db database to drop table from
 * @param table_name name of the table to drop
 */
void DB_TABLE_DROP(Database *db, char *table_name);

/**
 * Returns table of records for which the predicate function returns true
 * @example DB_SELECT(db, "Users", all);
 * @param db database to select from
 * @param table_name name of the table to select from
 * @param predicate function returning true if record should be included in the result
 * @return table containing records satisfying predicate
 */

Table *DB_SELECT_FROM_WHERE(Database *db, char *table_name, bool (*predicate)(Record *));

/**
 * Inserts given record into the table of given name inside database
 * @param db database to add to
 * @param table_name table to add to
 * @param record record
 */
void DB_INSERT_INTO(Database *db, char *table_name, Record *record);

/**
 * Deletes records satisfying predicate from given table in database
 * @param db database
 * @param table_name table name from which to remove
 * @param predicate function returning true if record should be deleted
 */
void DB_DELETE_FROM_WHERE(Database *db, char *table_name, bool (*predicate)(Record *));

/**
 * Updates all records in table satisfying predicate with given value at given column
 * @param db database
 * @param table_name table to modify
 * @param column_name name of the column
 * @param value_ptr pointer to the new value
 * @param predicate function returning true if record should be modified
 */
void DB_UPDATE_WHERE(Database *db, char *table_name, char *column_name, void *value_ptr, bool (*predicate)(Record *));

/**
 * Saves database to binary file
 * @param db to save
 * @param file binary file to save to
 * @return true if save was a successful, false otherwise
 */
bool DB_SAVE(Database *db, FILE *file);

/**
 * Loads database from the file, or creates new if file is empty
 * @param file load database from
 * @return pointer to database or NULL if load failed
 */
Database *DB_LOAD(FILE *file);

Table *_DB_find_table(const Database *db, const char *table_name);

#endif //CUWR_DATABASE_H
