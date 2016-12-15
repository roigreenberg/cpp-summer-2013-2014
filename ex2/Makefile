CC = g++ -Wall -std=c++11

defaulf: all demo

all: MyMatrix.o Matrix.o RegMatrix.o SparseMatrix.o

demo:
	$(CC) MyMatrix.cpp Matrix.cpp RegMatrix.cpp SparseMatrix.cpp DemoMyMatrix.cpp -o DemoMyMatrix

MyMatrix.o: MyMatrix.cpp MyMatrix.h Matrix.h Map.h Vector.h
	$(CC) -c MyMatrix.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(CC) -c Matrix.cpp

RegMatrix.o: RegMatrix.cpp RegMatrix.h Matrix.h Vector.h
	$(CC) -c RegMatrix.cpp

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h Matrix.h Map.h
	$(CC) -c SparseMatrix.cpp

matrix:
	$(CC) MyMatrix.cpp Matrix.cpp RegMatrix.cpp SparseMatrix.cpp main.cpp -o matrix
	matrix
	matrix > matrix.out
	FC matrix.out roitest.out

test:
	$(CC) MyMatrix.cpp Matrix.cpp RegMatrix.cpp SparseMatrix.cpp test.cpp -o test
	test > test.out
	FC test.out test_result

tar:
	tar cvf ex2.tar MyMatrix.cpp Matrix.cpp RegMatrix.cpp SparseMatrix.cpp \
			MyMatrix.h Matrix.h RegMatrix.h SparseMatrix.h \
			Map.h Vector.h Makefile

clean:
	rm -f *.o demo

.PHONY: all tar clean test default matrix
