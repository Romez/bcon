bcon: main.c
	gcc -Wall main.c -o main

build: main.c
	gcc main.c -O3 -o bcon
