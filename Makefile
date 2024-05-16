# Tipo di compilatore
CC=g++

# Opzioni di compilazione
CFLAGS=-Iinclude

# Nome dell'eseguibile
TARGET=main

# Costruire l'eseguibile finale
$(TARGET): main.o campo.o utils.o
	$(CC) -g main.o campo.o utils.o -o $(TARGET)

# Costruire l'oggetto main
main.o: src/main.cpp 
	$(CC) $(CFLAGS) -c -g src/main.cpp

# Costruire l'oggetto campo
campo.o: src/campo.cpp
	$(CC) $(CFLAGS) -c -g src/campo.cpp

# Costruire l'oggetto utils
utils.o: src/utils.cpp
	$(CC) $(CFLAGS) -c -g src/utils.cpp

# Pulire i file oggetto e l'eseguibile
clean:
	rm -f *.o $(TARGET)