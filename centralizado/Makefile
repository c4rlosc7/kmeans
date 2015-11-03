CC = clang++ -std=c++11

punto: punto.o
	$(CC) -o punto punto.o

punto.o: punto.cc
	$(CC) -c punto.cc

clean:
	rm -f punto.o punto
