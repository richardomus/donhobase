#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "columns.h"
#include "database.h"

unsigned int columns_append(ColumnSet* columnSet, const char* name, enum ColumnObjectTypeEnum type) {

    if(columnSet == NULL || name == NULL || type >= end) return 0;

    ColumnObject* object = &columnSet->set[columnSet->count];
    object->type = type;
    strcpy(object->name, name);

    switch(type) { 
        case Int: object->size = sizeof(unsigned int); break;
        case Float: object->size = sizeof(float); break;
        case Varchar: object->size = 256; break;
        case Char: object->size = 256; break;
        case DateTime: object->size = sizeof(unsigned long int); break;
        case end: break;
    }

    columnSet->count++;
    columnSet->chunkSize += object->size;

    return 1;
}

unsigned int chunk_write_data(ColumnSet* columnSet, const unsigned int column, void* chunk, void* data) {
    if(columnSet == NULL || data == NULL || column >= columnSet->count) return 0;

    unsigned int offset = 0;
    unsigned int i = 0;

    for(i = 0; i < column; ++i) offset += columnSet->set[i].size;
    
    ColumnObject* object = &columnSet->set[column];

    memcpy(chunk + offset, data, object->size);

    return 1;
}

void* chunk_read_data(ColumnSet* columnSet, const unsigned int column, void* chunk) {
    if(columnSet == NULL || chunk == NULL || column >= columnSet->count) return NULL;

    unsigned int offset = 0;
    unsigned int i = 0;

    for(i = 0; i < column; ++i) offset += columnSet->set[i].size;

    ColumnObject* object = &columnSet->set[column];

    return chunk + offset;
}

