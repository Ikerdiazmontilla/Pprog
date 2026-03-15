CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
LDFLAGS = -L.
LDLIBS = -lscreen

EXE = castle
TESTS = character_test set_test space_test command_test

GAME_OBJS = game_loop.o game.o game_actions.o game_reader.o command.o \
	graphic_engine.o player.o object.o character.o space.o set.o

all: $(EXE)

$(EXE): $(GAME_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

tests: $(TESTS)

character_test: character_test.o character.o
	$(CC) -o $@ $^ $(LDFLAGS)

set_test: set_test.o set.o
	$(CC) -o $@ $^ $(LDFLAGS)

space_test: space_test.o space.o set.o
	$(CC) -o $@ $^ $(LDFLAGS)

command_test: command_test.o command.o
	$(CC) -o $@ $^ $(LDFLAGS)

game_loop.o: game_loop.c command.h types.h game.h character.h object.h player.h \
	space.h game_reader.h game_actions.h graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c

game.o: game.c game.h character.h types.h command.h object.h player.h space.h
	$(CC) $(CFLAGS) -c game.c

game_actions.o: game_actions.c game_actions.h command.h types.h game.h \
	character.h object.h player.h space.h
	$(CC) $(CFLAGS) -c game_actions.c

game_reader.o: game_reader.c game_reader.h game.h character.h types.h command.h \
	object.h player.h space.h
	$(CC) $(CFLAGS) -c game_reader.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h character.h types.h \
	command.h object.h player.h space.h libscreen.h
	$(CC) $(CFLAGS) -c graphic_engine.c

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -c character.c

space.o: space.c set.h types.h space.h
	$(CC) $(CFLAGS) -c space.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

character_test.o: character_test.c character.h types.h
	$(CC) $(CFLAGS) -c character_test.c

set_test.o: set_test.c set.h types.h
	$(CC) $(CFLAGS) -c set_test.c

space_test.o: space_test.c space.h set.h types.h
	$(CC) $(CFLAGS) -c space_test.c

command_test.o: command_test.c command.h types.h
	$(CC) $(CFLAGS) -c command_test.c

clean:
	rm -f *.o $(EXE) $(TESTS)

run: $(EXE)
	./$(EXE) castle.dat

.PHONY: all clean run tests
