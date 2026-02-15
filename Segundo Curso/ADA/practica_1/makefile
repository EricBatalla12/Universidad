quickSort: quickSort.cc
	g++ quickSort.cc -o quickSort

quickSort.CPUtimes: quickSort
	./quickSort.cc > quickSort.CPUtimes

graphs: quickSort.gpi quickSort.CPUtimes
	gnuplot quickSort.gpi
	
all: graphs