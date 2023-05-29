main.exe: main.o ecc.o input.o
	g++ main.o ecc.o input.o -o main.exe

main.o: main.cpp ecc.h
	g++ -c main.cpp -o main.o

ecc.o: ecc.cpp ecc.h
	g++ -c ecc.cpp -o ecc.o

input.o: input.cpp input.h
	g++ -c input.cpp -o input.o