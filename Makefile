BIN=bin/match_compr.static
SRC=src/main.c
LIB=lib/libmc.a
LIBOBJ=static/mc.o
LIBSRC=src/proj.c

all:$(LIBOBJ) $(LIB) $(BIN)

$(LIBOBJ):$(LIBSRC)
	gcc -c -o $(LIBOBJ) $(LIBSRC) -std=c99
$(LIB):$(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)
$(BIN):$(SRC)
	gcc -static -o $(BIN) $(SRC) -L./lib -lmc -I./include

.PHONY:clean
clean:
	rm -rf $(BIN) $(LIB) $(LIBOBJ)
