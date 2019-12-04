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

bug1: bug1_unit.c dominion.o
	gcc -o bug1 bug1_unit.c dominion.o rngs.o -g $(CFLAGS)

bug2: bug2_unit.c dominion.o
	gcc -o bug2 bug2_unit.c dominion.o rngs.o -g $(CFLAGS)

bug3: bug3_unit.c dominion.o
	gcc -o bug3 bug3_unit.c dominion.o rngs.o -g $(CFLAGS)

bug4: bug4_unit.c dominion.o
	gcc -o bug4 bug4_unit.c dominion.o rngs.o -g $(CFLAGS)
	
bug7: unitTest7.c dominion.o rngs.o 
	gcc -o bug7 -g unitTest7.c dominion.o rngs.o  $(CFLAGS)
	
bug9: unitTest9.c dominion.o rngs.o 
	gcc -o bug9 -g unitTest9.c dominion.o rngs.o  $(CFLAGS)
	
bug10: unitTest10.c dominion.o rngs.o
	gcc -o bug10 -g unitTest10.c dominion.o rngs.o  $(CFLAGS)
	

unittestresults: bug1 bug2 bug3 bug4 bug7 bug9 bug10
	bug1 &> unittestresults.out
	bug2 >> unittestresults.out
	bug3 >> unittestresults.out
	bug4 >> unittestresults.out
	bug7 >> unittestresults.out
	bug9 >> unittestresults.out
	bug10 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player bug1 bug2 bug3 bug4 bug7 bug9 bug10

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe bug1.exe bug1 bug2.exe bug2 bug3.exe bug3 bug4.exe bug4 unittestresults.out\
	bug7.exe bug7 bug9.exe bug9 bug10.exe bug10 
