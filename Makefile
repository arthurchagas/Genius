sfml_path = C:/SFML
RM = rm
MAIN = main
flags = -Wall
TARGET_O = main.o botao.o no.o fila.o util.o

ifeq ($(OS),Windows_NT)
	RM = del
	MAIN = main.exe
endif

all: $(TARGET_O)
	g++ $(TARGET_O) -o main $(flags) -L$(sfml_path)/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

main.o:
	g++ -c main.cpp $(flags) -I$(sfml_path)/include -Iinclude

botao.o:
	g++ -c src/Botao.cpp $(flags) -I$(sfml_path)/include -Iinclude

no.o:
	g++ -c src/No.cpp $(flags) -Iinclude

fila.o:
	g++ -c src/Fila.cpp $(flags) -Iinclude

util.o:
	g++ -c src/Util.cpp $(flags) -I$(sfml_path)/include -Iinclude

clean:
	$(RM) $(MAIN) $(TARGET_O)