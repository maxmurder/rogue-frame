CC = g++
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(DEBUG)
OBJS = rcurses_manager.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

rcurses_manager.o : src/rcurses_manager.cpp src/rcurses_manager.h
	$(CC) $(CFLAGS) src/rcurses_manager.cpp

clean:
	\rm *.o *~ $(EXE)

