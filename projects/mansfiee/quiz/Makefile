CFLAGS= -Wall -fpic -coverage -lm -std=c99

make:
	gcc -o testme ${CFLAGS} testme.c
	./testme
	
coverage:
	gcov testme.c

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.exe *.so *.out testme

