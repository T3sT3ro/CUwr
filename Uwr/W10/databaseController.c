//
// Created by i300791 on 03.01.18.
//

#include <stdbool.h>
#include "record.h"

typedef struct DATABASE_ {
    Record **records;
    int used;
    int capacity;
} Database;

Database *newDatabase(int initialCapacity) {
    Database *db = malloc(sizeof(Database));
    if (db == NULL) // couldn't allocate database
        return NULL;

    db->capacity = initialCapacity;
    db->used = 0;
    if ((db->records = malloc(sizeof(Record *) * initialCapacity)) == NULL) { // couldn't alloc records table
        free(db);
        return NULL;
    }
    for (int i = 0; i < initialCapacity; ++i)
        if ((db->records[i] = newRecord()) == NULL) { // add new pointer to record to the table
            free(db); // TODO: deleteRecord();
            return NULL; // couldn't add next record
        }
}

void databaseAddRecord(Database *db, Record *record) {
    if (db == NULL || record == NULL) return;

    if (db->used == db->capacity) { // reallocate list of pointers to records
        db->capacity *= 2;
        Record **newTable = malloc(sizeof(Record *) * db->capacity);
        if (newTable == NULL) // couldn't resize table
            return;
        db->records = newTable;
    } else {
        db->records[db->used] = record;
        db->used++;
    };
}

Record *databaseFindIf(Database *db, const Record *record, bool (*predicate)(Record *)) const {}

// TODO: forEach(db, record, function)

int main() {
    Database *db = newDatabase(16);

}