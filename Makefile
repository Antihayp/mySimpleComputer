all: bin/memory

bin/memory: build/main.o lib/libmemory.a bin
	gcc -Wall build/main.o lib/libmemory.a -o bin/memory

build/main.o: src/main.c src/memory.h build
	gcc -Wall -c src/main.c -o build/main.o

lib/libmemory.a: build/memory.o lib
	ar rcs lib/libmemory.a build/memory.o

build/memory.o: src/memory.c src/memory.h build
	gcc -Wall -c src/memory.c -o build/memory.o

build:
	mkdir build

lib:
	mkdir lib

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf build/*.o
