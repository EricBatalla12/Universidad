#ifndef TCOMPLEJO_H
#define TCOMPLEJO_H

#include <iostream>
#include <cmath>
using namespace std;

class TComplejo {
private:
    double re;
    double im;

public:
//Constructor por defecto: inicializa a 0 la parte real e imaginariaA
TComplejo();
//Constructor a partir de la PARTE REAL
TComplejo (double re);
//Constructor a partir de la PARTE REAL e IMAGINARIA
TComplejo (double re, double im);
//Constructor copia
TComplejo (const TComplejo& other);
//Destructor
~TComplejo();
//Sobrecarga del operador asignación
TComplejo& operator= (const TComplejo& other);

TComplejo operator+ (const TComplejo& complejo);
TComplejo operator- (const TComplejo& complejo);
TComplejo operator* (const TComplejo& complejo);
TComplejo operator+ (double real);
TComplejo operator- (double real);
TComplejo operator* (double real);

bool operator== (const TComplejo& other); // IGUALDAD de números complejos
bool operator!= (const TComplejo& other); // DESIGUALDAD de números complejos

//Definciones inline para rendimiento, no tiene que buscarlo en el .cpp
//Se pone const en los getters ya que son métodos "consultivos", no se va a modificar el contenido
double Re() const {return this->re;} // Devuelve PARTE REAL
double Im() const {return this->im;} // Devuelve PARTE IMAGINARIA

void Re(double real) {this->re = real;} // Modifica PARTE REAL
void Im(double imaginario) {this->im = imaginario;} // Modifica PARTE IMAGINARIA

double Arg(void); // Calcula el Argumento (en Radianes)
double Mod(void); // Calcula el Módulo

friend ostream & operator<<(ostream & os, const  TComplejo & complejo);
friend TComplejo operator+ (double real, const TComplejo& complejo);
friend TComplejo operator- (double real, const TComplejo& complejo);
friend TComplejo operator* (double real, const TComplejo& complejo);
};

#endif