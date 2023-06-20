#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "columns.h"
#include "database.h"
#include "sql.h"

//const char sqlString[] = "select c.cid, c.cname, c.email, p.pid, p.pname, p.price from (select cid, cname, email from company where city = ‘Vancouver’) as c natural inner join (select cid, pid from sales where year = 2019) as s natural inner join (select pid, pname, price from products where company = ‘lego’) as p";
const char sqlString[] = "SELECT t1.id FROM (select * from (select * from lululu)) as t1, (select id from lilili) as t2 WHERE id > 10 ORDER BY id DESC";

int main(int argc, char* argv[]) {

    printf("%s\n", sqlString);

    SqlActionSet* set = sqlActionSetMalloc();

    parseSqlString(sqlString, set);
     
    printActionSet(set, 0);
    //executeActionSet(set);

    //unsigned int a;
    //for(a = 0; a < set.count; ++a) printf("%s %s\n", sql_keywords[set.actions[a].action], set.actions[a].buffer);
    
    return 0;

    unsigned int i = 0, j = 0;

    ColumnSet columnSet;
    memset(&columnSet, 0, sizeof(ColumnSet));

    columns_append(&columnSet, "PRIMARY_KEY", Int);
    columns_append(&columnSet, "TITLE", Char);
    columns_append(&columnSet, "SUBTITLE", Char);
    columns_append(&columnSet, "DATE", DateTime);
    columns_append(&columnSet, "QTDE", Int);

    createNewTable("database.donho", &columnSet);

    void* chunk = malloc(columnSet.chunkSize);
    
    unsigned int value = 1;
    unsigned int value2 = 345;
    unsigned long int dataTime= 543432423432;
    chunk_write_data(&columnSet, 0, chunk, &value);
    chunk_write_data(&columnSet, 1, chunk, "Esse é o texto numero 1");
    chunk_write_data(&columnSet, 2, chunk, "Esse aqui e o texto final");
    chunk_write_data(&columnSet, 3, chunk, &dataTime);
    chunk_write_data(&columnSet, 4, chunk, &value2);

    writeNewChunkOnTable("database.donho", chunk, columnSet.chunkSize);

    //print table

    for(i = 0; i < columnSet.count; ++i) {
        printf("%s | ", columnSet.set[i].name);
    }
    printf("\n");
    i = 0;

    chunk = readPositionOnTable("database.donho", 0);

    while(chunk != NULL) {
        
        for(j = 0; j < columnSet.count; ++j) {
            
            void* data = chunk_read_data(&columnSet, j, chunk);
            
            switch(columnSet.set[j].type) { 
                case Int: printf("%d | ", *((unsigned int*)(data))); break;
                case Char: printf("%s | ", (char*)(data)); break;
                case Float: printf("%f | ", *((float*)(data))); break;
                case DateTime: printf("%lu | ", *((unsigned long int*)(data))); break;
            }
        }
        printf("\n");
        chunk = readPositionOnTable("database.donho", ++i);
    }

    return 0;
}