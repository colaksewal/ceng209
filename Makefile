# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source and object files
SRC = src/main.c src/game.c src/player.c src/room.c  src/map.c src/inventory.c src/attacker.c
OBJ = $(SRC:.c=.o)
EXE = dungeon_game

# Default target: build the executable and run it
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)
	./$(EXE)

# Clean target: remove object files and executable
clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(EXE)

# Phony targets to avoid conflicts with filenames
.PHONY: clean
