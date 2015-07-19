CC = g++
DEBUG = -g
VER = -std=c++1y
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(VER) $(DEBUG)
LDFLAGS = -lncurses
SRC = src/
OBJS = test.o rcurses_manager.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

rcurses_manager.o : $(SRC)rcurses_manager.cpp $(SRC)rcurses_manager.h
	$(CC) $(CFLAGS) $(SRC)rcurses_manager.cpp

test.o : $(SRC)test.cpp $(SRC)rcurses_manager.h
	$(CC) $(CFLAGS) $(SRC)test.cpp

clean:
	\rm *.o *~ $(EXE) $(SRC)*~

