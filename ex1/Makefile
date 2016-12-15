CC = g++ -Wall

all: MyLinkedList MyHashMap HashMapBinaryOperations
MyLinkedList: MyLinkedListT.o
	$(CC) MyLinkedList.o -o MyLinkedList

MyHashMap: MyHashMapT.o MyLinkedList.o
	$(CC) MyHashMap.o MyLinkedList.o -o MyHashMap

HashMapBinaryOperations: HashMapBinaryOperations.o MyHashMap.o MyLinkedList.o
	$(CC) HashMapBinaryOperations.o MyHashMap.o MyLinkedList.o -o HashMapBinaryOperations

MyHashMap.o: MyHashMap.cpp MyHashMap.h MyLinkedList.h
	$(CC) -c MyHashMap.cpp

MyLinkedList.o: MyLinkedList.cpp MyLinkedList.h
	$(CC) -c MyLinkedList.cpp

HashMapBinaryOperations.o: HashMapBinaryOperations.cpp MyHashMap.h
	$(CC) -c HashMapBinaryOperations.cpp

ListExample.o: ListExample.cpp
	$(CC) -c ListExample.cpp

tar:  Makefile
	tar cfv ex1.tar MyLinkedList.cpp MyLinkedList.h MyHashMap.cpp \
	MyHashMap.h HashMapBinaryOperations.cpp Makefile

clean:
	rm -f *.o MyLinkedList MyHashMap HashMapBinaryOperations

.PHONY: all tar clean
