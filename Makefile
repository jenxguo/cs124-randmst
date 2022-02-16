
randmst: main.o graph.o
	g++ main.o graph.o -o randmst

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp graph.hpp
	g++ -c graph.cpp

clean:
	rm *.o randmst