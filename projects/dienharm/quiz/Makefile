CFLAGS= -Wall -coverage -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)
	testme

getcoverage: testme
	gcov testme.c -b -f > randomtestresults.out

clean:
	rm -f *.o testme testme.exe *.gcov *.gcda *.gcno *.so *.out
