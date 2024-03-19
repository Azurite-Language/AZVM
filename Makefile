CC = gcc
FLAGS = -std=c99 -Wall -Wextra -O0 -g
SRC = ./src/*.c
EXE = main
OPTI = -O3

all: main

main: .PHONY
	$(CC) $(SRC) -o $(EXE) $(FLAGS) $(OPTI)

benchmark: main
	time ./$(EXE)

benchmark_no_opti: .PHONY
	$(CC) $(SRC) -o $(EXE) $(FLAGS)
	time ./$(EXE)

no_opti: .PHONY
	$(CC) $(SRC) -o $(EXE) $(FLAGS)
	./$(EXE)

debug: .PHONY
	$(CC) -g $(SRC) -o $(EXE) $(FLAGS)

.PHONY: