all:
	g++ -c -o passgen.o passgen.cpp
	g++ -o passgen passgen.o

install:
	install passgen /usr/local/bin
