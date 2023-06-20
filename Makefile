all:
	gcc -g -ggdb src/sql.c src/columns.c src/database.c src/main.c -o bin/database
