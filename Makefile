BIN=bin/match_compr.static
SRC=src/main.c
LIB=lib/libdnamatch.a
LIBOBJ=static/trie.o static/bit.o static/hashing.o static/haffman.o
LIBSRC=src/trie.c src/bit.c src/hashing.c src/haffman.c

all:$(LIBOBJ) $(LIB) $(BIN)

static/%.o:src/%.c
	gcc -o $@ -c $< -std=c99
$(LIB):$(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)
$(BIN):$(SRC)
	gcc -static -o $(BIN) $(SRC) -L./lib -ldnamatch -I./include

.PHONY:clean
clean:
	rm -rf $(BIN) $(LIB) $(LIBOBJ)
