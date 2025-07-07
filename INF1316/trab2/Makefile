# Nome do compilador
CC = gcc

# Flags de compilação:
# -g: Adiciona informações de depuração (para usar com gdb)
# -Wall: Habilita a maioria dos avisos (warnings) do compilador
CFLAGS = -g -Wall

# Nome do executável final
EXEC = main

# Lista de todos os arquivos de código-fonte (.c)
SRCS = main.c memoria.c acesso.c utils.c algoritmos.c

# Gera a lista de arquivos objeto (.o) substituindo a extensão .c por .o na lista SRCS
OBJS = $(SRCS:.c=.o)

# Regra principal (padrão): é executada quando você digita apenas "make"
all: $(EXEC)

# Regra para ligar (link) os arquivos objeto e criar o executável
# Adiciona -lm para a biblioteca matemática
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) -lm

# Regra para compilar main.o
main.o: main.c memoria.h acesso.h utils.h algoritmos.h
	$(CC) $(CFLAGS) -c main.c

# Regra para compilar memoria.o
memoria.o: memoria.c memoria.h
	$(CC) $(CFLAGS) -c memoria.c

# Regra para compilar acesso.o
acesso.o: acesso.c acesso.h utils.h
	$(CC) $(CFLAGS) -c acesso.c

# Regra para compilar utils.o
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# Regra para compilar algoritmos.o
algoritmos.o: algoritmos.c algoritmos.h memoria.h
	$(CC) $(CFLAGS) -c algoritmos.c

# Regra "clean": remove os arquivos gerados pela compilação
.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJS)

# Regra "run": compila se necessário e executa o programa com argumentos de exemplo
.PHONY: run
run: all
	./$(EXEC) lru texto.txt 4 64
