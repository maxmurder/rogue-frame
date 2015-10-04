CC = g++
DEBUG = -g
VER = -std=c++1y
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(VER) $(DEBUG)
LDFLAGS = -lncurses -lSDL
SRC = src/
OBJS = main.o r_engine.o TestState.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

r_engine.o : $(SRC)r_engine.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)r_engine.cpp

TestState.o : $(SRC)TestState.cpp $(SRC)TestState.h
	$(CC) $(CFLAGS) $(SRC)TestState.cpp

main.o : $(SRC)main.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)main.cpp

clean:
	\rm *.o *~ $(EXE) $(SRC)*~ core.*

