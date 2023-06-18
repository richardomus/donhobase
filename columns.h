#ifndef __COLUMNS_H__
#define __COLUMNS_H__

#define COLUMNS_NAME_DEFAULT_SIZE 256
#define COLUMNS_CHUNK_DEFAULT_SIZE 32

enum ColumnObjectTypeEnum {
    Int = 0,
    Float,
    Varchar,
    Char,
    DateTime,
    end
};

typedef struct ColumnObjectType {
    unsigned int type; //4
    unsigned int size; //4
    char name[COLUMNS_NAME_DEFAULT_SIZE];
} ColumnObject;

typedef struct ColumnSetType {
    unsigned int count; //4
    unsigned int chunkSize; //4
    ColumnObject set[COLUMNS_CHUNK_DEFAULT_SIZE];
} ColumnSet;

unsigned int columns_append(ColumnSet* columnSet, const char* name, enum ColumnObjectTypeEnum type);
unsigned int chunk_write_data(ColumnSet* columnSet, const unsigned int column, void* chunk, void* data);
void* chunk_read_data(ColumnSet* columnSet, const unsigned int column, void* chunk);
#endif //__COLUMNS_H__