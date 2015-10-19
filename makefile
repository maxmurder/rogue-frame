CC = g++
DEBUG = -g
VER = -std=c++1y
LFLAGS = -Wall $(DEBUG)
CFLAGS = -Wall -c $(VER) $(DEBUG)
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
SRC = src/
OBJS = main.o r_engine.o r_entity.o r_component.o r_SDL.o r_utils.o r_util_components.o r_animation.o r_render.o r_sprite.o TestState.o RTexture.o RSprite.o RTimer.o RWindow.o
EXE = rogue-frame

$(EXE) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

r_engine.o : $(SRC)r_engine.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)r_engine.cpp

r_SDL.o : $(SRC)r_SDL.cpp $(SRC)r_SDL.h 
	$(CC) $(CFLAGS) $(SRC)r_SDL.cpp 

r_utils.o : $(SRC)r_utils.cpp $(SRC)r_utils.h 
	$(CC) $(CFLAGS) $(SRC)r_utils.cpp 

r_entity.o : $(SRC)r_entity/r_entity.cpp $(SRC)r_entity/r_entity.h 
	$(CC) $(CFLAGS) $(SRC)r_entity/r_entity.cpp 

r_component.o : $(SRC)r_entity/r_component.cpp $(SRC)r_entity/r_component.h
	$(CC) $(CFLAGS) $(SRC)r_entity/r_component.cpp $(SRC)r_entity/r_component_detail.h

r_util_components.o : $(SRC)r_util_components.cpp $(SRC)r_util_components.h 
	$(CC) $(CFLAGS) $(SRC)r_util_components.cpp 

r_animation.o : $(SRC)r_animation.cpp $(SRC)r_animation.h 
	$(CC) $(CFLAGS) $(SRC)r_animation.cpp

r_render.o : $(SRC)r_render.cpp $(SRC)r_render.h 
	$(CC) $(CFLAGS) $(SRC)r_render.cpp
	
r_sprite.o : $(SRC)r_sprite.cpp $(SRC)r_sprite.h 
	$(CC) $(CFLAGS) $(SRC)r_sprite.cpp

RSprite.o : $(SRC)RSprite.cpp $(SRC)RSprite.h
	$(CC) $(CFLAGS) $(SRC)RSprite.cpp

RTexture.o : $(SRC)RTexture.cpp $(SRC)RTexture.h
	$(CC) $(CFLAGS) $(SRC)RTexture.cpp

RTimer.o : $(SRC)RTimer.cpp $(SRC)RTimer.h
	$(CC) $(CFLAGS) $(SRC)RTimer.cpp

RWindow.o : $(SRC)RWindow.cpp $(SRC)RWindow.h
	$(CC) $(CFLAGS) $(SRC)RWindow.cpp

TestState.o : $(SRC)TestState.cpp $(SRC)TestState.h
	$(CC) $(CFLAGS) $(SRC)TestState.cpp

main.o : $(SRC)main.cpp $(SRC)r_engine.h
	$(CC) $(CFLAGS) $(SRC)main.cpp

clean:
	\rm *.o *~ $(EXE) $(SRC)*~ core.*

