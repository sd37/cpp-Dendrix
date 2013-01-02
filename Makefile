CC = g++
CFLAGS = -I.
Dendrix: Dendrix.cpp DendrixUtil.cpp
	$(CC) -g -o Dendrix Dendrix.cpp DendrixUtil.cpp $(CFLAGS)
clean:
	rm -f Dendrix
