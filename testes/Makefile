#
# Makefile para programas de teste
# 

CC=gcc
LIB_DIR=../lib

all: priority_queue ccreate cyield


priority_queue: priority_queue_test.c 
	$(CC) -o priority_queue_test priority_queue_test.c -Wall -L$(LIB_DIR) -lcthread -Wall

ccreate: ccreate_test.c
	$(CC) -o ccreate_test ccreate_test.c -Wall -L$(LIB_DIR) -lcthread -Wall

cyield: cyield_test.c
	$(CC) -o cyield_test cyield_test.c -Wall -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf priority_queue_test ccreate_test cyield_test *.o *~




