all:
	g++ -std=c++17 -w main.cpp Colony.h Colony.cpp primes.h -o main;
	./main;