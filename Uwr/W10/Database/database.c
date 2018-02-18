//
// Created by i300791 on 03.01.18.
//

#include "database.h"
#include <string.h>
#include <stdarg.h>

Database *DB_NEW() {
    Database *db = malloc(sizeof(Database));
    db->tables = NULL;
    db->tables_count = 0;
    return db;
}

void DB_TABLE_CREATE(Database *db, char *table_name, unsigned int col_count, ...) {
    if (db == NULL
        || table_name == NULL
        || col_count == 0)
        return;

    for (int i = 0; i < db->tables_count; ++i)
        if (strcmp(table_name, db->tables[i]->table_name) == 0)
            return; // return if table with this name already exists

    Table *table = _DB_TABLE_new(table_name);

    va_list args;
    va_start(args, col_count);
    for (int i = 0; i < col_count; ++i)  // TODO cancel if two names the same
        _DB_TABLE_column_push(table, va_arg(args, char*), va_arg(args, enum DB_FIELD_TYPE));

    va_end(args);
    realloc(db->tables, sizeof(Table *) * (++db->tables_count)); // creating tables isn't often, so resize + 1 is OK
    db->tables[db->tables_count - 1] = table; /// ??? FIXME check if works
}

void DB_TABLE_DROP(Database *db, char *table_name) {
    if (db == NULL
        || table_name == NULL)
        return;

    Table *table = NULL;
    int it;
    for (it = 0; it < db->tables_count && table == NULL; ++it)
        if (strcmp(db->tables[it]->table_name, table_name) == 0)
            table = db->tables[it];

    if (table == NULL) return; // not found, return

    _DB_TABLE_destroy(table);
    while (it < db->tables_count)  // move all other tables backwards in array
        db->tables[it - 1] = db->tables[it];

    realloc(db->tables, sizeof(Table *) * (--db->tables_count)); //shrink array of tables

}

Table *DB_SELECT_FROM_WHERE(Database *db, char *table_name, bool (*predicate)(Record *)) {
    if (db == NULL
        || table_name == NULL
        || predicate == NULL)
        return NULL;

    Table *search_table = _DB_find_table(db, table_name);
    if (search_table == NULL) return NULL;
    Table *result_table = _DB_TABLE_new("result");
    for (int i = 0; i < search_table->records_count; ++i)
        if (predicate(search_table->records[i]))
            _DB_TABLE_insert(result_table, search_table->records[i]);

    return result_table;
}

void DB_INSERT_INTO(Database *db, char *table_name, Record *record) {
    if (db == NULL
        || table_name == NULL
        || record == NULL)
        return;

    Table *table = _DB_find_table(db, table_name);
    if (table == NULL) return;

    _DB_TABLE_insert(table, record);
}


void DB_DELETE_FROM_WHERE(Database *db, char *table_name, bool (*predicate)(Record *)) {

}

void DB_UPDATE_WHERE(Database *db, char *table_name, char *column_name, void *value_ptr, bool (*predicate)(Record *)) {

}

bool DB_SAVE(Database *db, FILE *file) {
    return 0;
}

Database *DB_LOAD(FILE *file) {
    return NULL;
}


//----------------------------------------------------------------------------------------------------------------------


Table *_DB_find_table(const Database *db, const char *table_name) {
    for (int it = 0; it < db->tables_count; ++it)
        if (strcmp(db->tables[it]->table_name, table_name) == 0)
            return db->tables[it];
    return NULL;
}
