genkey: genkey1
	./genkey1 ${MPRIME} ${NPRIME}
genkey1: genkey.c
	gcc -lm -o genkey1 genkey.c 
keycrack: keycrack1
	./keycrack1 ${E} ${C}
keycrack1: keycrack.c
	gcc -o keycrack1 keycrack.c
client: client1
	./client1 ${SERVER} ${PORT} ${E} ${C} ${D} ${DC}
client1: client.c csapp.o
	gcc -o client1 client.c csapp.o -lpthread
server: server1
	./server1 ${PORT} ${E} ${C} ${D} ${DC}
server1: server.c csapp.o
	gcc -o server1 server.c csapp.o -lpthread
csapp.o: csapp.c
	gcc -c csapp.c
clean:
	rm -rf *o genkey1 keycrack1 client1 server1
