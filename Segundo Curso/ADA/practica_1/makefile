# Eric Batalla Ortúzar 24503990C
quickSort: quickSort.cc
	g++ quickSort.cc -o quickSort

quickSort.CPUtimes: quickSort
	./quickSort > quickSort.CPUtimes

graphs: quickSort.gpi quickSort.CPUtimes
	gnuplot quickSort.gpi
	
all: graphs