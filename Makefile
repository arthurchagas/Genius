RM = rm
MAIN = main
flags = -Wall
TARGET_O = main.o botao.o no.o fila.o util.o
LINKER_INCLUDE = -Llib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
PREPROCESSOR_INCLUDE = -Iinclude

ifeq ($(OS),Windows_NT)
	RM = del
	MAIN = main.exe
endif

all: $(TARGET_O)
	g++ $(TARGET_O) -o main $(flags) $(LINKER_INCLUDE)

main.o:
	g++ -c main.cpp $(flags) $(PREPROCESSOR_INCLUDE)

botao.o:
	g++ -c src/Botao.cpp $(flags) $(PREPROCESSOR_INCLUDE)

no.o:
	g++ -c src/No.cpp $(flags) $(PREPROCESSOR_INCLUDE)

fila.o:
	g++ -c src/Fila.cpp $(flags) $(PREPROCESSOR_INCLUDE)

util.o:
	g++ -c src/Util.cpp $(flags) $(PREPROCESSOR_INCLUDE)

clean:
	$(RM) $(MAIN) $(TARGET_O)