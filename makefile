exec: main.o doublets.o
	  	g++ -Wall -g main.o doublets.o -o exec

main.o: main.cpp doublets.h
		g++ -Wall -g -c main.cpp

doublets.o: doublets.cpp doublets.h dictionary.h
		  g++ -Wall -g -c doublets.cpp

clean:
	  rm -f *.o exec