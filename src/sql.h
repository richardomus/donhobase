#ifndef __SQL_H__
#define __SQL_H__

#define MAX_COMMAND_PARAMETERS_BUFFER_SIZE 256
#define MAX_BUFFER_SQL_ACTIONS 32
#define MAX_BUFFER_SQL_SETS_CHILDS 8

extern const char* sql_keywords[];

enum sqlActionsEnum {
    create = 0,
    delete,
    drop,
    from,
    inner_join,
    order_by,
    outer_join,
    select,
    where,
    sqlActionsEnumMaxItens
};

typedef struct SqlActionType {
    unsigned int action;
    char buffer[MAX_COMMAND_PARAMETERS_BUFFER_SIZE];
} SqlAction;

typedef struct SqlActionSetType {
    unsigned int count;
    unsigned int childCount;
    SqlAction actions[MAX_BUFFER_SQL_ACTIONS];
    void** children;
} SqlActionSet;

SqlActionSet* sqlActionSetMalloc();
unsigned int  sqlActionSetFree(SqlActionSet*);

unsigned int parseSqlString(const char*, SqlActionSet*);
#endif //__SQL_H__