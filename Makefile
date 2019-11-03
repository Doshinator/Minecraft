CC = g++ -std=c++11
CFLAGS = -c 
OBJ = main.o
DEPS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -framework OpenGL
EXE = main

all: $(OBJ)
	$(CC) main.o -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
		rm $(OBJ) $(EXE)