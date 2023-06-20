#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "columns.h"
#include "database.h"
#include "sql.h"

//SQL PARSER ALGORITHM

//SELECT T1.id, T2.id FROM TABELA1 as T1, TABELA2 as T2 WHERE T1.value = T2.value ORDER BY T1.id

enum sqlActionsEnum {
    create = 0,
    delete,
    drop,
    from,
    inner_join,
    order_by,
    outer_join,
    select,
    where
};

const char* sql_keywords[] = {
    "create",
    "delete",
    "drop",
    "from",
    "inner join",
    "order by",
    "outer join",
    "select",
    "where"
};

//"SELECT TITLE FROM database WHERE id = 1 AND id = 2 ORDER BY id DESC";

unsigned int parseSqlString(const char* sqlstring, SqlActionSet* actionSet) {
    
    if(sqlstring == NULL || actionSet == NULL) return 0;

    unsigned int i = 0, j = 0, k = 0, w = 0;
    unsigned int size = strlen(sqlstring);
    unsigned int arraySize = sizeof(sql_keywords) / sizeof(char*);

    char c = 0;
    char* buffer = malloc(MAX_COMMAND_PARAMETERS_BUFFER_SIZE);

    do {
        c = sqlstring[i] >= 65 && sqlstring[i] <= 90 ? sqlstring[i] + 32 : sqlstring[i]; 

        if (sql_keywords[j][k] == c) {
            buffer[w] = sqlstring[i];
            ++i; ++w; ++k;
        } else { 
            ++j; k = 0;
        }

        if(j >= arraySize) {
            buffer[w] = sqlstring[i];
            ++i; ++w;
            j = 0;
        } else if (k >= strlen(sql_keywords[j])) {
            buffer[w-k] = '\0'; w = 0;
            //record buffer in last action
            if(actionSet->count > 0) strcpy(actionSet->actions[actionSet->count-1].buffer, buffer);
            //record action in current action
            actionSet->actions[actionSet->count].action = j;
            //increment to next action
            ++actionSet->count;
        }

    } while(i < size);

    buffer[w] = '\0';
    //record last buffer in current action
    strcpy(actionSet->actions[actionSet->count-1].buffer, buffer);

    free(buffer);
    return i;
}