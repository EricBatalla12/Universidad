all: pow2 pow2.png

#-lm es para que funcione math
pow2: pow2.c
	gcc -Wall -o pow2 pow2.c -lm

#generar la tabla ejecutando el programa
resultados.dat: pow2
	./pow2 > resultados.dat

#crear la gráfica
pow2.png: pow2.gpi resultados.dat
	gnuplot pow2.gpi

# Para limpiar los archivos generados con 'make clean'
clean:
	rm -f pow2 resultados.dat pow2.png