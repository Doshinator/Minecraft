CC = g++ -std=c++14
CFLAGS = -c 
OBJ = main.o display.o
DEPS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -framework OpenGL
EXE = main

all: $(OBJ) 
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

display.o: src/display.cpp src/display.h
	$(CC) $(CFLAGS) src/display.cpp
 
clean:
		rm $(OBJ) $(EXE)