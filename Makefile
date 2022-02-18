
randmst: main.o graph.o unionfind.o randmst.o
	g++ main.o graph.o unionfind.o randmst.o -o randmst

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp graph.hpp
	g++ -c graph.cpp

unionfind.o: unionfind.cpp unionfind.hpp
	g++ -c unionfind.cpp

randmst.o: randmst.cpp randmst.hpp
	g++ -c randmst.cpp

clean:
	rm *.o randmst