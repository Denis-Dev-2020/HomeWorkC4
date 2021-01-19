CFLAGS = -O0 -fPIC -g -Wall -Werror
CC = gcc
all : Main Exe clean
Main : frequency.c
	$(CC) $(CFLAGS)  frequency.c -g -o frequency
Exe : 
	echo "it was the best of times, it was the worst of times. it was the age of wisdom, it was the age of foolishness." >> input.txt
	./frequency<input.txt
	./frequency<input.txt r
.PHONY : clean
clean : input.txt
	rm input.txt
