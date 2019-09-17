#
# Makefile para programas de teste
# 

CC=gcc
LIB_DIR=../lib

all: priority_queue


priority_queue: priority_queue_test.c 
	$(CC) -o priority_queue_test priority_queue_test.c -Wall -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf priority_queue_test *.o *~




