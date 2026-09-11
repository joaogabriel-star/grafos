# Makefile da Pratica 03 - Ordenacao Topologica e Deteccao de Ciclo em DAGs

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lm
TARGET = main
SRC = *.c
OBJ = *.o

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
