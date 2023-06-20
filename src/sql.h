#ifndef __SQL_H__
#define __SQL_H__

#define MAX_COMMAND_PARAMETERS_BUFFER_SIZE 256
#define MAX_BUFFER_SQL_ACTIONS 32

extern const char* sql_keywords[];

typedef struct SqlActionType {
    unsigned int action;
    char buffer[MAX_COMMAND_PARAMETERS_BUFFER_SIZE];
} SqlAction;

typedef struct SqlActionSetType {
    unsigned int count;
    SqlAction actions[MAX_BUFFER_SQL_ACTIONS];
} SqlActionSet;

unsigned int parseSqlString(const char*, SqlActionSet*);
#endif //__SQL_H__