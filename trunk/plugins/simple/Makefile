all: simple

simple: simple.c
	gcc -DDATA_DIR=\"/usr/local/share\" -ggdb -shared -fPIC simple.c -o simple.so `pkg-config libglade-2.0 --cflags --libs` -I../../src/include
