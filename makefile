CFLAGS = -I src/include
LDFLAGS = -L src/lib -lSDL3 -lopengl32
BIN = src/bin/main

SRC = $(wildcard src/game/*.c) $(wildcard src/engine/*.c)

all:
	gcc $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)
	.\$(BIN).exe