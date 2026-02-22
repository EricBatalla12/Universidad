#24503990C Eric Batalla Ortúzar

all: qs-vs-hs qs-vs-hs.Msteps graphs

#Pongo el -O3 porque es la única solución que he encontrado para que dure menos de 20seg
qs-vs-hs: qs-vs-hs.cc
	g++ -O3 qs-vs-hs.cc -o qs-vs-hs

qs-vs-hs.Msteps: qs-vs-hs
	./qs-vs-hs > qs-vs-hs.Msteps

graphs: qs-vs-hs.Msteps qs-vs-hs.gpi
	gnuplot qs-vs-hs.gpi

# Limpieza de archivos generados (opcional pero muy útil para pruebas)
clean:
	rm -f qs-vs-hs qs-vs-hs.Msteps *.png fit.log