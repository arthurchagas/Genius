RM = rm
MAIN = RuPaulsGenius
flags = -Wall
TARGET_O = main.o Botao.o No.o Fila.o Util.o
LINKER_INCLUDE = -Llib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
PREPROCESSOR_INCLUDE = -Iinclude

ifeq ($(OS),Windows_NT)
	RM = del
	MAIN = RuPaulsGenius.exe
endif

all: $(TARGET_O)
	g++ $(TARGET_O) -o Main $(flags) $(LINKER_INCLUDE)

main.o:
	g++ -c main.cpp $(flags) $(PREPROCESSOR_INCLUDE)

Botao.o:
	g++ -c src/Botao.cpp $(flags) $(PREPROCESSOR_INCLUDE)

No.o:
	g++ -c src/No.cpp $(flags) $(PREPROCESSOR_INCLUDE)

Fila.o:
	g++ -c src/Fila.cpp $(flags) $(PREPROCESSOR_INCLUDE)

Util.o:
	g++ -c src/Util.cpp $(flags) $(PREPROCESSOR_INCLUDE)

clean:
	$(RM) $(MAIN) $(TARGET_O)