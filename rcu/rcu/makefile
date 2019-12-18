all: rcu

rcu: main.o rcu.o versionInfo.o
	g++ main.o rcu.o versionInfo.o -o rcu

main.o: main.cpp
	g++ -c main.cpp

rcu.o: rcu.cpp
	g++ -c rcu.cpp

versionInfo.o: versionInfo.cpp
	g++ -c versionInfo.cpp

clean:
	rm -rf *.o rcu