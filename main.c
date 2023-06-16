#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "database.h"

int main(int argc, char* argv[]) {

    createNewTable("database.donho");

    void* chunk = NULL;
    unsigned int i = 0;

    DataSet row1, row2;

    row1.id = 0;
    sprintf(row1.title, "Essa e a row chunk 1"); 

    row2.id = 1;
    sprintf(row2.title, "Essa e a row chunk 2"); 

    writeNewChunkOnTable("database.donho", &row1, sizeof(DataSet));
    writeNewChunkOnTable("database.donho", &row2, sizeof(DataSet));

    chunk = readPositionOnTable("database.donho", 0);

    while(chunk != NULL) {
        printf("%d | %s\n", ((DataSet*)chunk)->id, ((DataSet*)chunk)->title);
        i++;
        chunk = readPositionOnTable("database.donho", i);
    }

    return 0;
}