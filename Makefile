#/* Roeurn Tourn
#   Senior Project
#*/

CC = gcc

CFLAGS = -Wall -g #-ansi

LD = gcc

LDFLAGS = 

targetingControl: targeting.o Matrix.o
	$(CC) $(CFLAGS) -c Matrix.c -o Matrix.o 
	$(CC) $(CFLAGS) -c targeting.c -o targeting.o 
	$(LD) $(LDFLAGS)  targeting.o Matrix.o targetingControl.c -o target.out 

targeting.o: targeting.c
	$(CC) $(CFLAGS) -c targeting.c -o targeting.o 

Matrix.o: Matrix.c
	$(CC) $(CFLAGS) -c Matrix.c -o Matrix.o 


clean:
	rm *.o
	rm target.out
	rm *.data

test: 
	echo cleaning files
	make clean
	echo making files again
	make targetingControl
	echo Testing targetingControl
	./target.out
