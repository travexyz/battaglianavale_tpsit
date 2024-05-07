# Tipo di compilatore
CC=g++

# Opzioni di compilazione
CFLAGS=

# Nome dell'eseguibile
TARGET=main

# Costruire l'eseguibile finale
$(TARGET): main.o
	$(CC) main.o -o $(TARGET)

# Costruire l'oggetto main
main.o: src/main.cpp
	$(CC) -c src/main.cpp

# Pulire i file oggetto e l'eseguibile
clean:
	rm -f *.o $(TARGET)

# salutare gabriel bella
gabriel:
	echo "gabriel bella ci manchi!!"