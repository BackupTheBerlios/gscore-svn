CC=gcc
CFLAGS=`pkg-config gtk+-2.0 --cflags` `pkg-config cairo --cflags`
LIBS=-lgscore `pkg-config gtk+-2.0 --libs` `pkg-config cairo --libs`

all: demo

demo: demo.c
	$(CC) demo.c -o demo $(CFLAGS) $(LIBS)
