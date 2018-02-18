//
// Created by Tooster on 11.02.2018.
//

#ifndef CUWR_FIELD_H
#define CUWR_FIELD_H
#define DB_FIELD_TYPE_ENUM_MIN DB_FIELD_CHAR
#define DB_FIELD_TYPE_ENUM_MAX DB_FIELD_REF
#define DB_FIELD_STRING_MAX_LEN 256

enum DB_FIELD_TYPE{
    DB_FIELD_CHAR,   // char
    DB_FIELD_INT,    // int
    DB_FIELD_LONG,   // long long
    DB_FIELD_STRING, // null terminated char* or string of max length 256 chars without null terminator
    DB_FIELD_REF     // reference to other record
};

typedef struct _field {
} Field;

#endif //CUWR_FIELD_H
