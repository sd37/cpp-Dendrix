CC = g++
CFLAGS = -I.
Dendrix: Dendrix.cpp DendrixUtil.cpp debug.cpp
	$(CC) -g -o Dendrix Dendrix.cpp DendrixUtil.cpp debug.cpp $(CFLAGS)
clean:
	rm -f Dendrix
