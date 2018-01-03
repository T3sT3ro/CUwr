//
// Created by i300791 on 03.01.18.
//

#include <string.h>
#include <stdlib.h>

//
//
//

typedef struct FIELD_ {
    char *key;
    void *val;
} Field;

typedef struct RECORD_ {
    int capacity_; // how much fields can be currently held
    int used_; // how much fields are used
    Field *map; // map of pairs key_val
} Record;

//
//
//

Record *newrecord() {
    Record *new_record_ = malloc(sizeof(Record)); // reserve space for record
    if (new_record_ == NULL) // alloc error
        return NULL;

    new_record_->capacity_ = 8; // initial field count for pairs <key, val>
    new_record_->used_ = 0;
    Field *new_map_ = malloc(new_record_->capacity_ * sizeof(Field)); // alloc initial map

    if (new_map_ == NULL) { // map alloc error - destroy and exit
        free(new_record_);
        return NULL;
    }

    new_record_->map = new_map_;
    return new_record_;
}


void recordSetField(Record *record, const char *key, const char *val, const size_t valSizeInBytes) {
    if (record == NULL)
        return;

    int foundIndex = recordFind(record, key);
    if (foundIndex != -1) { // key found
        Field *found = &record->map[foundIndex];
        realloc(found->val, sizeof(char) * (strlen(val) + 1));
        strcpy(found->val, val);
    } else { // new key - add to map

        if (record->used_ == record->capacity_) { // full capacity
            record->capacity_ *= 2;
            realloc(record, sizeof(Record) * record->capacity_);
        }

        record->map[record->used_].key = malloc(sizeof(char) * (strlen(key) + 1)); // copy key safely in case of BOF
        strcpy(record->map[record->used_].key, key);

        memcpy(record->map[record->used_].val, val, valSizeInBytes); // copy value to void* ptr in Record

        record->used_++; // update how many fields are stored
    }
}


void recordDeleteField(Record *record, const char *key) {
    if (record == NULL)
        return;

    int foundIndex = recordFind(record, key);
    if (foundIndex != -1) {
        for (int i = foundIndex + 1; i < record->used_; ++i)


            record->used_--;
    }
}

/// Returns index in map that compares equal with key or -1 if not found
int recordFind(Record *record, const char *key) {
    if (record == NULL)
        abort();

    for (int i = 0; i < record->used_; ++i) // update existing key
        if (strcmp(record->map[i].key, key) == 0) // if keys match
            return i; // return address of record field

    return -1; // return null when not found given key in map
}