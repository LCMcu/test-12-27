#test:test.c
#	gcc -o test test.c -lsqlite3


LDFLAGS+=-lsqlite3
OBJ=server test
SRC=server.c test.c

$(OBJ):$(SRC)
	gcc -o $@  $^ $(LDFLAGS)