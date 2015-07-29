CC = g++
DEBUG = -g
VER = -std=c++1y
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(VER) $(DEBUG)
LDFLAGS = -lncurses
SRC = src/
OBJS = test.o r_curses.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

r_curses.o : $(SRC)r_curses.cpp $(SRC)r_curses.h
	$(CC) $(CFLAGS) $(SRC)r_curses.cpp

test.o : $(SRC)test.cpp $(SRC)r_curses.h
	$(CC) $(CFLAGS) $(SRC)test.cpp

clean:
	\rm *.o *~ $(EXE) $(SRC)*~ core.*

