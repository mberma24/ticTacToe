CC = g++

TicTacToe: main.o gameloop.o moves.o board.o
	$(CC) -o TicTacToe main.o gameloop.o moves.o board.o

main.o: source/main.cpp
	$(CC) -c source/main.cpp

gameloop.o: source/gameloop.cpp
	$(CC) -c source/gameloop.cpp

moves.o: source/moves.cpp
	$(CC) -c source/moves.cpp

board.o: source/board.cpp
	$(CC) -c source/board.cpp
clean:
	rm -f *.o TicTacToe
