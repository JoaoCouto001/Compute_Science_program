# Nome do projeto
PROJ_NAME = labirinto

# Arquivos .c
C_SOURCE = $(wildcard *.c)

# Arquivos .h
H_SOURCE = $(wildcard *.h)

# Arquivos objeto
OBJ = $(C_SOURCE:.c=.o)

# Compilador
CC = gcc

# Opções do compilador
CC_FLAGS = -Wall -Wextra -g -pedantic

# Compilação
all: $(PROJ_NAME)

# Linkagem
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

# Compilação dos arquivos .c em .o
%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f *.o $(PROJ_NAME) *~
