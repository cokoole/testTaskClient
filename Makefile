CC=g++
CFLAGS=-g -Wall -Werror
SOURCES=client.cpp clientWebSocket.cpp arguments.cpp

all: client

client: 
	$(CC) $(CFLAGS) $(SOURCES) -o client