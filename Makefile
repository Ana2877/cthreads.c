#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

CFLAGS= -Wall -Wextra -O2 -Wunreachable-code -Wuninitialized -Winit-self -pedantic
ARFLAGS= -rv


all: libcthread.a

libcthread.a: $(BIN_DIR)/cthread.o $(BIN_DIR)/priority_queue.o 
	ar $(ARFLAGS) $(LIB_DIR)/$@ $^ $(BIN_DIR)/support.o 

$(BIN_DIR)/cthread.o: $(SRC_DIR)/cthread.c 
	$(CC) $(CFLAGS) -o $@ -c $^

$(BIN_DIR)/priority_queue.o: $(SRC_DIR)/priority_queue.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/cthread.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ 


