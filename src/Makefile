CC = g++ -std=c++14
CFLAGS = -c 
OBJ = main.o
DEPS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -framework OpenGL -lglfw
EXE = main

all: $(OBJ) 
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
 
clean:
		rm $(OBJ) $(EXE)