CC = gcc
FLAGS = -std=c99 -Wall -Wextra -O0 -g
SRC = ./src/*.c
EXE = ./bin/azvm
OPTI = -O3


all: main folder

folder: .PHONY
	mkdir -p ./bin

main: .PHONY folder
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