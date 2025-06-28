# Variáveis
CC = gcc
CFLAGS = -Wall -g

# Alvos principais
ALL_TARGETS = main interpretador escalonador \
              P1 P2 P3 P4 P5 P6 P7 P8 P9 P10

# Objeto reutilizável
OBJ_PROCESSO = processo.o

# Regra padrão
all: $(ALL_TARGETS)

# Compila o módulo
$(OBJ_PROCESSO): processo.c processo.h
	$(CC) $(CFLAGS) -c processo.c

main: main.c
	$(CC) $(CFLAGS) -o main main.c

interpretador: interpretador.c $(OBJ_PROCESSO)
	$(CC) $(CFLAGS) -o interpretador interpretador.c $(OBJ_PROCESSO)

escalonador: escalonador.c $(OBJ_PROCESSO)
	$(CC) $(CFLAGS) -o escalonador escalonador.c $(OBJ_PROCESSO)

P%: p%.c
	$(CC) $(CFLAGS) -o $@ $<

# Limpeza
clean:
	rm -f $(ALL_TARGETS) *.o
