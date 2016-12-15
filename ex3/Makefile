CC = g++ -Wall -std=c++11
ALL = Matrix.hpp Rational.cpp RationalExcaptions.h MatrixExcaptions.h
O_FILE = Rational.o GenericMatrixDriver.o

defaulf: GenericMatrixDriver

GenericMatrixDriver: $(O_FILE)
	$(CC) $(O_FILE) -o GenericMatrixDriver

GenericMatrixDriver.o: Matrix.hpp Rational.h GenericMatrixDriver.cpp
	$(CC) -c GenericMatrixDriver.cpp

Rational.o: Rational.h Rational.cpp
	$(CC) -c Rational.cpp

tar:
	tar cvf ex3.tar $(ALL) Makefile

clean:
	rm -f *.o GenericMatrixDriver

.PHONY: tar clean
