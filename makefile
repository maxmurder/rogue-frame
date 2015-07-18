CC = g++
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(DEBUG)
LDFLAGS = -lncurses
OBJS = test.o rcurses_manager.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

rcurses_manager.o : src/rcurses_manager.cpp src/rcurses_manager.h
	$(CC) $(CFLAGS) src/rcurses_manager.cpp

test.o : src/test.cpp src/rcurses_manager.h
	$(CC) $(CFLAGS) src/test.cpp

clean:
	\rm *.o *~ $(EXE)

