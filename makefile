CC = g++
DEBUG = -g
VER = -std=c++1y
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(VER) $(DEBUG)
LDFLAGS = -lncurses
SRC = src/
OBJS = main.o r_curses.o r_engine.o mainState.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

r_curses.o : $(SRC)r_curses.cpp $(SRC)r_curses.h
	$(CC) $(CFLAGS) $(SRC)r_curses.cpp

r_engine.o : $(SRC)r_engine.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)r_engine.cpp

mainState.o : $(SRC)mainState.cpp $(SRC)mainState.h
	$(CC) $(CFLAGS) $(SRC)mainState.cpp

main.o : $(SRC)main.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)main.cpp

clean:
	\rm *.o *~ $(EXE) $(SRC)*~ core.*

