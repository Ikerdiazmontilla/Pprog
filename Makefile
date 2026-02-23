# Variables
CC = gcc
CFLAGS = -Wall -g
EXE = castle

# Regla principal
all: $(EXE)

# Añadimos todos los .o necesarios
$(EXE): game_loop.o game.o game_actions.o game_reader.o command.o graphic_engine.o player.o object.o character.o space.o
	$(CC) $(CFLAGS) -o $(EXE) $^ -L. -lscreen

# Compilación de módulos individuales
game_loop.o: game_loop.c command.h game.h game_reader.h game_actions.h graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c

game.o: game.c game.h space.h player.h object.h character.h types.h
	$(CC) $(CFLAGS) -c game.c

game_actions.o: game_actions.c game_actions.h command.h game.h space.h player.h object.h types.h
	$(CC) $(CFLAGS) -c game_actions.c

game_reader.o: game_reader.c game_reader.h space.h game.h player.h object.h types.h
	$(CC) $(CFLAGS) -c game_reader.c

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c

graphic_engine.o: graphic_engine.c graphic_engine.h libscreen.h command.h space.h types.h
	$(CC) $(CFLAGS) -c graphic_engine.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -c character.c

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c space.c

character_test: character_test.o character.o
	$(CC) $(CFLAGS) -o $@ $^

character_test.o: character_test.c character.h types.h
	$(CC) $(CFLAGS) -c character_test.c

# Limpieza
clean:
	rm -f *.o $(EXE) character_test

# Ejecución
run:
	./$(EXE) castle.dat
