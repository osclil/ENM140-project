CC = clang++
CFLAGS = -std=c++17 -Wall -O2 -g
SRC = src/
OBJ = obj/

all: main

main: $(OBJ)main.o $(OBJ)move_gen.o $(OBJ)board.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ)%.o: $(SRC)%.cpp
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)main.o: $(SRC)main.cpp $(SRC)move_gen.h $(SRC)board.h $(SRC)piece.h $(SRC)minmax_impl.h $(SRC)minmax.h
$(OBJ)move_gen.o: $(SRC)move_gen.cpp $(SRC)board.h $(SRC)piece.h
$(OBJ)board.o: $(SRC)board.cpp $(SRC)piece.h

clean:
	rm -rf $(OBJ)*.o main
