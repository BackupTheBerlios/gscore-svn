all: midi

midi: midi.c
	gcc -ggdb -shared -fPIC midi.c -o midi.so `pkg-config libglade-2.0 simili --cflags --libs` -I../../src/include

