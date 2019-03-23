all:
	-rm *.out *.o
	g++ -O3 main.cpp
	time ./a.out
clean:
	-rm *.out *.o
