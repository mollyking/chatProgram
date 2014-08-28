Molly King
CS283 Assignment 4

This is a chat program, where you run a server or client, and another person runs a client or server. You give your public key to them and they give theirs to you. The program will properly encrypt/decrypt any messages that you send to each other. This also contains a genkey.c file, which generates a public and private key for you to use. You need to enter two prime numbers when you run the program, and will generate the keys based off of those numbers. keycrack.c is a file that, when given a public key, can calculate the corresponding private key.


When testing the chat program, use the keys below. E and DC represents the other user's E and C, respectively. C and D represent your own C and D. The client will start the conversation. To quit, either the client or the server can quit by typing .bye

Test1:
SERVER=tux64-12.cs.drexel.edu PORT=8380 E=2027 C=2623 D=1283 DC=2623 make client
PORT=8380 E=2027 C=2623 D=1283 DC=2623 make server

Test2:
SERVER=tux64-14.cs.drexel.edu PORT=8380 E=2027 C=1271 D=323 DC=2623 make client
PORT=8380 E=587 C=2623 D=1283 DC=1271 make server



To run keycrack:
E=451 C=2623 make keycrack
Results:
M: 2520
D was found to be 1531
A was 43 and B was 61
1148:
This char is decrypted to 72
The letter is H



To run genkey:
MPRIME=15 NPRIME=19 make genkey
Results:
15th prime: = 43
19th prime: = 61
c = 2623
m = 2520
e = 2027
d = 1283
Public Key = (2027, 2623)
Private Key = (1283, 2623)
encrypt 72: 1148
decrypt 1148: 72

