CC = g++
DEBUG = -g
VER = -std=c++1y
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(VER) $(DEBUG)
LDFLAGS = -lSDL2 -lSDL2_image
SRC = src/
OBJS = main.o r_engine.o TestState.o r_SDL.o RTexture.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

r_engine.o : $(SRC)r_engine.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)r_engine.cpp

r_SDL.o : $(SRC)r_SDL.cpp $(SRC)r_SDL.h 
	$(CC) $(CFLAGS) $(SRC)r_SDL.cpp 
	
RTexture.o : $(SRC)RTexture.cpp $(SRC)RTexture.h
	$(CC) $(CFLAGS) $(SRC)RTexture.cpp

TestState.o : $(SRC)TestState.cpp $(SRC)TestState.h
	$(CC) $(CFLAGS) $(SRC)TestState.cpp

main.o : $(SRC)main.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)main.cpp

clean:
	\rm *.o *~ $(EXE) $(SRC)*~ core.*

