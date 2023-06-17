#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "columns.h"
#include "database.h"

int main(int argc, char* argv[]) {

    unsigned int i = 0;

    ColumnSet columnSet;
    memset(&columnSet, 0, sizeof(ColumnSet));

    columns_append(&columnSet, Int);
    columns_append(&columnSet, Char);
    columns_append(&columnSet, Char);
    columns_append(&columnSet, DateTime);

    createNewTable("database.donho", &columnSet);

    void* chunk = malloc(columnSet.chunkSize);
    
    unsigned int value = 1;
    chunk_write_data(&columnSet, 0, chunk, &value);
    chunk_write_data(&columnSet, 1, chunk, "Esse é o texto numero 1");
    chunk_write_data(&columnSet, 2, chunk, "Esse aqui e o texto final");

    writeNewChunkOnTable("database.donho", chunk, columnSet.chunkSize);

    chunk = readPositionOnTable("database.donho", 0);

    while(chunk != NULL) {
        
        for(i = 0; i < columnSet.count; ++i) {
            
            void* data = chunk_read_data(&columnSet, i, chunk);
            
            switch(columnSet.set[i].type) { 
                case Int: printf("%d |", *((unsigned int*)(data))); break;
                case Char: printf("%s |", (char*)(data)); break;
            }
        }

        chunk = readPositionOnTable("database.donho", ++i);
    }

    return 0;
}