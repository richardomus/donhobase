#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "columns.h"
#include "database.h"

unsigned int createNewTable(const char* dbTableName, ColumnSet* columnSet) {
    
    if(columnSet == NULL) return 0;

    IndexSet index;
    memset(&index, 0, sizeof(IndexSet));
    
    FILE* file = fopen(dbTableName, "rb+");

    if(file != NULL) {
        fclose(file);
        return 0;
    }

    file = fopen(dbTableName, "wb+");

    fwrite(columnSet, sizeof(ColumnSet), 1, file);
    fwrite(&index, sizeof(IndexSet), 1, file);

    fclose(file);

    return 1;

}

unsigned int writeNewChunkOnTable(const char* dbTableName, void* chunk, const unsigned int chunkSize) {
    
    IndexSet index;

    FILE* file = fopen(dbTableName, "rb+");
    
    if(file == NULL) return 0;
    
    fseek(file, sizeof(ColumnSet), SEEK_SET);
    fread(&index, sizeof(IndexSet), 1, file);

    IndexObject lastItem = index.set[index.count > 0 ? index.count -1 : 0];

    unsigned long int newPosition = lastItem.initPosition + lastItem.size;

    // recording the chunk on the file newPosition 
    fseek(file, newPosition, SEEK_CUR);
    fwrite(chunk, chunkSize, 1, file);

    //adding new index
    
    IndexObject newItem;
    newItem.initPosition = newPosition;
    newItem.size = chunkSize;

    index.set[index.count++] = newItem;
    
    fseek(file, sizeof(ColumnSet), SEEK_SET);
    fwrite(&index, sizeof(IndexSet), 1, file);

    fclose(file);

    return 1;
}

void* readPositionOnTable(const char* dbTableName, const unsigned int position) {

    FILE* file = fopen(dbTableName, "rb+");
    
    if(file == NULL) return NULL;

    IndexSet index;
    
    fseek(file, sizeof(ColumnSet), SEEK_SET);
    fread(&index, sizeof(IndexSet), 1, file);

    if(position >= index.count) { 
        fclose(file); 
        return NULL;
    }

    IndexObject item = index.set[position];
    void* chunk = malloc(item.size);
    fseek(file, item.initPosition, SEEK_CUR);
    fread(chunk, item.size, 1, file);

    fclose(file);
    
    return chunk;
}
