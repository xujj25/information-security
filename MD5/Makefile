main: test.o md5.o
	gcc -o main test.o md5.o -g
test.o: test.c
	gcc -c -o test.o test.c -g
md5.o: md5.c md5.h
	gcc -c -o md5.o md5.c -g

clean:
	rm *.o main
