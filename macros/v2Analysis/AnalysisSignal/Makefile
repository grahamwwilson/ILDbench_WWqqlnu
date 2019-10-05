


main: histset.o myselector.o ParTreeProcessing.c
	g++ -o compiledthreads ParTreeProcessing.c -pthread `root-config --cflags --libs`

histset.o: histset.c myselector.o
	g++ -c  histset.c -pthread `root-config --cflags --libs`

myselector.o: myselector.C myselector.h
	g++ -c -pthread myselector.C `root-config --cflags --libs` 

clean:
	rm *.o
