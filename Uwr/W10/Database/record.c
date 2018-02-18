//
// Created by i300791 on 03.01.18.
//

#include <stdlib.h>
#include <mem.h>
#include "record.h"

#define INITIAL_FIELDS_COUNT 8
#define NOT_FOUND_CODE -1


Record *newRecord() {
    Record *new_record_ = malloc(sizeof(Record)); // reserve space for record
    if (new_record_ == NULL) // alloc error
        return NULL;

    new_record_->capacity = INITIAL_FIELDS_COUNT; // initial field count for pairs <key, val>
    new_record_->used = 0;
    Field *new_map_ = malloc(new_record_->capacity * sizeof(Field)); // alloc initial map

    if (new_map_ == NULL) { // map alloc error - destroy and exit
        free(new_record_);
        return NULL;
    }

    new_record_->map = new_map_;
    return new_record_;
}

/// Returns index in map that compares equal with key or -1 if not found
int recordFind(Record *record, const void *key, const size_t keySizeInBytes) {
    if (record == NULL || key == NULL || keySizeInBytes == 0)
        abort();

    for (int i = 0; i < record->used; ++i)
        if (record->map[i].keySizeInBytes == keySizeInBytes &&
            memcmp(record->map[i].key, key, keySizeInBytes) == 0) // if keys match
            return i; // return address of record field

    return NOT_FOUND_CODE; // return null when not found given key in map
}

void recordSetField(Record *record,
                    const void *key, const size_t keySizeInBytes,
                    const void *val, const size_t valSizeInBytes) {

    if (record == NULL || key == NULL || val == NULL || keySizeInBytes == 0 || valSizeInBytes == 0)
        return;

    int foundIndex = recordFind(record, key, keySizeInBytes);
    if (foundIndex != NOT_FOUND_CODE) { /// key found - update
        Field *found = &record->map[foundIndex];
        void *newVal = malloc(valSizeInBytes);
        if (newVal == NULL) // on error don't change key
            return;

        free(found->val); // otherwise free current value
        found->val = newVal; // assign pointer to it in Field
        found->valSizeInBytes = valSizeInBytes; // save new size of value in bytes inside found field
        return;
    } else { /// new key - add to map
        /// full capacity : re-alloc memory for record
        if (record->used == record->capacity) {
            record->capacity *= 2;
            Field *newMap = realloc(record->map, sizeof(Field) * record->capacity);
            if (newMap == NULL) // re-alloc failed
                return;
            record->map = newMap; // assign resized map
        }

        /// Alloc new Field
        Field *newField;
        void *newKey;
        void *newVal;

        if ((newField = malloc(sizeof(Field))) == NULL) // Field malloc failed
            return;
        if ((newKey = malloc(keySizeInBytes)) == NULL) { // key malloc failed
            free(newField);
            return;
        }
        if ((newVal = malloc(valSizeInBytes)) == NULL) { // value malloc failed
            free(newField);
            free(newKey);
            return;
        }

        /// Copy values and assign to Field
        memcpy(newKey, key, keySizeInBytes); // copy key to Field
        memcpy(newVal, val, valSizeInBytes); // copy value to Field

        record->[record->used] = newField; // point to the new Field
        record->map[record->used].keySizeInBytes = keySizeInBytes;
        record->map[record->used].key = newKey; // copy key safely in case of BOF
        record->map[record->used].valSizeInBytes = valSizeInBytes;
        record->map[record->used].val = newVal;

        /// Increment record used fields counter
        record->used++; // update how many fields are stored
    }
}

RecordReturnVal *recordGetField(Record *record, const void *key, const size_t keySizeInBytes) {

    if (record == NULL || key == NULL || keySizeInBytes == 0)
        return NULL;

    int foundIndex = recordFind(record, key, keySizeInBytes);
    if (foundIndex == NOT_FOUND_CODE)
        return NULL;

    RecordReturnVal *ret = malloc(sizeof(RecordReturnVal));
    ret->bytes = record->map[foundIndex].valSizeInBytes;
    ret->var = record->map[foundIndex].val;

    return ret;

}

void recordDeleteField(Record *record, const void *key, const size_t keySizeInBytes) {
    if (record == NULL || key == NULL || keySizeInBytes == NULL)
        return;

    int foundIndex = recordFind(record, key, keySizeInBytes);
    if (foundIndex != NOT_FOUND_CODE) // return if key not found
        return;
    for (int i = foundIndex + 1; i < record->used; ++i) // shift the fields table to the left when erased from inside
        record->map[foundIndex - 1] = record->map[foundIndex];

    record->used--;
}