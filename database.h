#ifndef __DATABASE_H__
#define __DATABASE_H__

#define COLUMNS_CHUNK_DEFAULT_SIZE 32
#define INDEX_CHUNK_DEFAULT_SIZE 512

enum ColumnObjectTypeEnum {
    Int = 0,
    Float,
    Varchar,
    Char,
    DateTime
} ColumnObjectTypeEnum;

typedef struct ColumnObjectType {
    unsigned int type; //4
    unsigned int size; //4
} ColumnObject;

typedef struct ColumnSetType {
    unsigned int count; //4
    ColumnObject set[COLUMNS_CHUNK_DEFAULT_SIZE];
} ColumnSet;

typedef struct IndexObjectType {
    unsigned long int initPosition; //8
    unsigned long int size; //8
} IndexObject;

typedef struct IndexSetType {
    unsigned int count;
    IndexObject set[INDEX_CHUNK_DEFAULT_SIZE];
} IndexSet;

typedef struct dataSetType {
    unsigned int id;
    char title[256];
    char subtitle[512];
    float value;
} DataSet;

//ColumSet     | IndexSet      | CHUNKS
//############ | ############# | ####### | ####### | #######

unsigned int createNewTable(const char* dbTableName);
unsigned int writeNewChunkOnTable(const char* dbTableName, void* chunk, const unsigned int chunkSize);
void* readPositionOnTable(const char* dbTableName, const unsigned int position);

#endif //__DATABASE_H__