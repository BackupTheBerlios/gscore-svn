all: musicxml

musicxml: musicxml.c export-musicxml.c
	gcc -ggdb -shared -fPIC musicxml.c export-musicxml.c -o musicxml.so `pkg-config libglade-2.0 --cflags --libs` -I../../src/include
