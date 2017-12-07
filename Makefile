CC=g++
CFLAGS= -Wall -Wextra -pedantic -Wfloat-equal -Wshadow -Wconversion -Wunreachable-code -std=c++11

Glaeser_Noemi_BTC: Block.o Transaction.o Blockchain.o Glaeser_Noemi_BTC.o
	$(CC) $^ $(CFLAGS) -o '$@'

%.o: %.cpp %.h glaeser_common.h utils.h picosha2.h
	$(CC) $(CFLAGS) -c $^

clean:
	-rm *.o
	-rm *.gch
	-rm Glaeser_Noemi_BTC
