RM = del
MAIN = RuPaulsGenius.exe
flags = -Wall
TARGET_O = main.o Botao.o No.o Fila.o Util.o
LINKER_INCLUDE = -Llib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
PREPROCESSOR_INCLUDE = -Iinclude

all: $(TARGET_O)
	g++ -o $(MAIN) $(TARGET_O) $(flags) $(LINKER_INCLUDE)
	.\$(MAIN)

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