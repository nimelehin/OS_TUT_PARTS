all: rwlock

rwlock: main.o rwlock.o
	g++ main.o rwlock.o -o rwlock

main.o: main.cpp
	g++ -c main.cpp

rwlock.o: rwlock.cpp
	g++ -c rwlock.cpp

clean:
	rm -rf *.o rwlock
