# Makefile para a prática de AEDs II
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = exec_arvore
OBJS = main.o arvore.o

# Regra padrao de compilacao
all: $(TARGET)

# Linkagem do executavel
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regras de compilacao dos modulos individuais
main.o: main.c arvore.h
	$(CC) $(CFLAGS) -c main.c

arvore.o: arvore.c arvore.h
	$(CC) $(CFLAGS) -c arvore.c

# Limpeza dos binarios e objetos
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean