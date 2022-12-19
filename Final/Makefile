CC=gcc
CFLAGS=-g -Wall
TARGET=final
OBJS=main.o switch.o dotmatrix.o lcd.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lwiringPi -lbcm2835

main.o : main.c
	$(CC) -c -o main.o main.c

switch.o : switch.c
	$(CC) -c -o switch.o switch.c

dotmatrix.o : dotmatrix.c
	$(CC) -c -o dotmatrix.o dotmatrix.c

lcd.o : lcd.c
	$(CC) -c -o lcd.o lcd.c

clean:
	rm $(OBJS) $(TARGET)
