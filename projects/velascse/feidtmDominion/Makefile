CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g -w -std=c99 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g -w -std=c99 unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g -w -std=c99 unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g -w -std=c99 unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g -w -std=c99 cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g -w -std=c99 cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g -w -std=c99 cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g -w -std=c99 cardtest4.c dominion.o rngs.o $(CFLAGS)

assignment_3_test_suite: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.o *.gcda *.gcno playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

randomtestadventurer: randomtestadventurer.c dominion.c rngs.c
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.c -w $(CFLAGS)
	./randomtestadventurer > randomtestadventurer.out
	gcov randomtestadventurer.c -b >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
randomtestcard1: randomtestcard1.c dominion.c rngs.c
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.c -w $(CFLAGS)
	./randomtestcard1 > randomtestcard1.out
	gcov randomtestcard1.c -b >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.c rngs.c
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.c -w $(CFLAGS)
	./randomtestcard2 > randomtestcard2.out
	gcov randomtestcard2.c -f -b >> randomtestcard2.out
	gcov dominion.c - b >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	rm -f *.o *.gcda *.gcno playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe randomtestcard2

assignment_4_test_suite: randomtestadventurer randomtestcard1 randomtestcard2
	rm -f *.o *.gcda *.gcno playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe randomtestadventurer randomtestcard1 randomtestcard2

a5testsuite: randomtestadventurer.c randomtestcard1.c randomtestcard2.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest1.c unittest2.c unittest3.c unittest4.c dominion.c rngs.c
	echo "Assignment 5 test suit:" > a_5.out
	gcc -o unittest1 -g  unittest1.c dominion.c rngs.c -w $(CFLAGS)
	./unittest1 >> a_5.out
	gcov unittest1.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o unittest2 -g  unittest2.c dominion.c rngs.c -w $(CFLAGS)
	./unittest2 >> a_5.out
	gcov unittest2.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o unittest3 -g  unittest3.c dominion.c rngs.c -w $(CFLAGS)
	./unittest3 >> a_5.out
	gcov unittest3.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o unittest4 -g  unittest4.c dominion.c rngs.c -w $(CFLAGS)
	./unittest4 >> a_5.out
	gcov unittest4.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o cardtest1 -g  cardtest1.c dominion.c rngs.c -w $(CFLAGS)
	./cardtest1 >> a_5.out
	gcov cardtest1.c -f -b >> a_5.out
	gcov dominion.c >> a_5.out
	gcc -o cardtest2 -g  cardtest2.c dominion.c rngs.c -w $(CFLAGS)
	./cardtest2 >> a_5.out
	gcov cardtest2.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o cardtest3 -g  cardtest3.c dominion.c rngs.c -w $(CFLAGS)
	./cardtest3 >> a_5.out
	gcov cardtest3.c -f -b >> a_5.out
	gcov dominion.c -b  >> a_5.out
	gcc -o cardtest4 -g  cardtest4.c dominion.c rngs.c -w $(CFLAGS)
	./cardtest4 >> a_5.out
	gcov cardtest4.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.c -w $(CFLAGS)
	./randomtestcard1 >> a_5.out
	gcov randomtestcard1.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.c -w $(CFLAGS)
	./randomtestcard2 >> a_5.out
	gcov randomtestcard2.c -f -b >> a_5.out
	gcov dominion.c -b >> a_5.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.c -w $(CFLAGS)
	./randomtestadventurer >> a_5.out
	gcov randomtestadventurer.c -f -b >> a_5.out
	gcov dominion.c -f -b >> a_5.out
	rm -f *.o *.gcda *.gcno playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2

clean:
	rm -f *.o *.gcda *.gcno playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
