bin/main: build/test.o build/md5.o
	gcc -o bin/main build/* -g
build/test.o: src/test.c
	gcc -c -o build/test.o src/test.c -g -I./include
build/md5.o: src/md5.c include/md5.h
	gcc -c -o build/md5.o src/md5.c -g -I./include

clean:
	rm build/* bin/*
