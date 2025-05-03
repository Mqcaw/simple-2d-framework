CFLAGS = -I src/include 
LDFLAGS = -L src/lib -lSDL3
BIN = src/bin/main

SRC = $(wildcard src/*.c)

all:
	gcc $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)
	.\$(BIN).exe