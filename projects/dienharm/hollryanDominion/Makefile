CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unit1: unittest1.c dominion.o
	gcc -o unit1 unittest1.c dominion.o rngs.o -g $(CFLAGS)

unit2: unittest2.c dominion.o
	gcc -o unit2 unittest2.c dominion.o rngs.o -g $(CFLAGS)

unit3: unittest3.c dominion.o
	gcc -o unit3 unittest3.c dominion.o rngs.o -g $(CFLAGS)

unit4: unittest4.c dominion.o
	gcc -o unit4 unittest4.c dominion.o rngs.o -g $(CFLAGS)

unit5: unittest5.c dominion.o
	gcc -o unit5 unittest5.c dominion.o rngs.o -g $(CFLAGS)

unittestresults: unit1 unit2 unit3 unit4 unit5
	unit1
	unit2
	unit3
	unit4
	unit5
	gcov dominion.c -b -f > unittestresults.out

randomtest1: randomtestcard1.c dominion.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o -g $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o -g $(CFLAGS)

randomtest3: randomtestcard3.c dominion.o
	gcc -o randomtestcard3 randomtestcard3.c dominion.o rngs.o -g $(CFLAGS)

randomtestresults: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o -g $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o -g $(CFLAGS)
	gcc -o randomtestcard3 randomtestcard3.c dominion.o rngs.o -g $(CFLAGS)
	randomtestcard1 &> randomtestresults.out
	randomtestcard2 >> randomtestresults.out
	randomtestcard3 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

all: playdom player unit1 unit2 unit3 unit4 unit5

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unit1.exe unit1 unit2.exe unit2 unit3.exe unit3 unit4.exe unit4 unit5.exe unit5 unittestresults.out randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe randomtestcard3 randomtestcard3.exe
