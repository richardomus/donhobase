#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "database.h"

unsigned int createNewTable(const char* dbTableName) {
    
    FILE* file = fopen(dbTableName, "rb+");

    if(file != NULL) {
        fclose(file);
        return 0;
    }

    file = fopen(dbTableName, "wb+");

    IndexSet index;
    index.count = 0;

    fwrite(&index, sizeof(IndexSet), 1, file);

    fclose(file);

    return 1;

}

unsigned int writeNewChunkOnTable(const char* dbTableName, void* chunk, const unsigned int chunkSize) {
    
    IndexSet index;

    FILE* file = fopen(dbTableName, "rb+");
    
    if(file == NULL) return 0;

    fread(&index, sizeof(IndexSet), 1, file);

    IndexObject lastItem = index.set[index.count - 1];

    unsigned long int newPosition = lastItem.initPosition + lastItem.size;

    // recording the chunk on the file newPosition 
    fseek(file, newPosition, 0);
    fwrite(chunk, chunkSize, 1, file);

    //adding new index
    
    IndexObject newItem;
    newItem.initPosition = newPosition;
    newItem.size = chunkSize;

    index.set[index.count] = newItem;
    index.count++;

    fseek(file, 0, 0);
    fwrite(&index, sizeof(IndexSet), 1, file);

    fclose(file);

    return 1;
}

void* readPositionOnTable(const char* dbTableName, const unsigned int position) {

    FILE* file = fopen(dbTableName, "rb+");
    
    if(file == NULL) return NULL;

    IndexSet index;

    fread(&index, sizeof(IndexSet), 1, file);

    if(position >= index.count) { 
        fclose(file); 
        return NULL;
    }

    IndexObject item = index.set[position];
    void* chunk = malloc(sizeof(item.size));
    fseek(file, item.initPosition, 0);
    fread(chunk, item.size, 1, file);

    fclose(file);
    
    return chunk;
}
