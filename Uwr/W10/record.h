//
// Created by Tooster on 10.01.2018.
//

#ifndef CUWR_ENTRY_H
#define CUWR_ENTRY_H

#include <stdlib.h>

typedef struct FIELD_ {
    size_t keySizeInBytes;
    void *key;
    size_t valSizeInBytes;
    void *val;
} Field;

typedef struct RECORD_ {

    int capacity; // how much fields can be currently held
    int used; // how much fields are used
    Field *map; // map of pointe
} Record;

typedef struct RETURN_VAL_ {
    size_t bytes;
    void *var;
} RecordReturnVal;

Record *newRecord();

/// Returns index in map that compares equal with key or -1 if not found
int recordFind(Record *record, const void *key, size_t keySizeInBytes);

void recordSetField(Record *record,
                    const void *key, size_t keySizeInBytes,
                    const void *val, size_t valSizeInBytes);

RecordReturnVal *recordGetField(Record *record, const void *key, size_t keySizeInBytes);

void recordDeleteField(Record *record, const void *key, size_t keySizeInBytes);

// TODO: deleteRecord

#endif //CUWR_ENTRY_H
