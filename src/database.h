#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "sql.h"

#define INDEX_CHUNK_DEFAULT_SIZE 512

typedef struct IndexObjectType {
    unsigned long int initPosition; //8
    unsigned long int size; //8
} IndexObject;

typedef struct IndexSetType {
    unsigned int count;
    IndexObject set[INDEX_CHUNK_DEFAULT_SIZE];
} IndexSet;

//ColumSet     | IndexSet      | CHUNKS
//############ | ############# | ####### | ####### | #######

unsigned int createNewTable(const char* dbTableName, ColumnSet* columnSet);
unsigned int writeNewChunkOnTable(const char* dbTableName, void* chunk, const unsigned int chunkSize);
void* readPositionOnTable(const char* dbTableName, const unsigned int position);

unsigned int printActionSet(SqlActionSet* set, unsigned int spaces);
unsigned int executeActionSet(SqlActionSet* set);
#endif //__DATABASE_H__