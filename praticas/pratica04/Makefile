# Makefile da Pratica 04 - Conectividade (articulacoes/pontes) e Planaridade

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
