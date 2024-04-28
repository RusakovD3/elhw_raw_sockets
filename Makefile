CC=gcc
CFLAGS=-Wall

all: raw_socket_receiver udp_server

raw_socket_receiver: raw_socket_receiver.c
	$(CC) $(CFLAGS) raw_socket_receiver.c -o raw_socket_receiver

udp_server: udp_server.c
	$(CC) $(CFLAGS) udp_server.c -o udp_server

clean:
	rm -f raw_socket_receiver udp_server

.PHONY: all clean
