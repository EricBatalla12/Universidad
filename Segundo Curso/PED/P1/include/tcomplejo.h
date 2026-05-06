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
TComplejo& operator= (const TComplejo& other); //Paso por referencia "&" el TComplejo porque es un objeto grande y pasarlo por valor sería muy pesado, así que paso su direeción de memoria
                                               //Además lo paso const para prometer que no lo voy a modificar, solo leer
TComplejo operator+ (const TComplejo& complejo) const; //No se modifica ningún complejo, se crea uno nuevo
TComplejo operator- (const TComplejo& complejo) const;
TComplejo operator* (const TComplejo& complejo) const;
TComplejo operator+ (double real) const;
TComplejo operator- (double real) const;
TComplejo operator* (double real) const;

bool operator== (const TComplejo& other) const; // IGUALDAD de números complejos
bool operator!= (const TComplejo& other) const; // DESIGUALDAD de números complejos

//Definciones inline para rendimiento, no tiene que buscarlo en el .cpp
//Se pone const en los getters ya que son métodos "consultivos", no se va a modificar el contenido
double Re() const {return this->re;} // Devuelve PARTE REAL
double Im() const {return this->im;} // Devuelve PARTE IMAGINARIA

void Re(double real) {this->re = real;} // Modifica PARTE REAL
void Im(double imaginario) {this->im = imaginario;} // Modifica PARTE IMAGINARIA

double Arg() const; // Calcula el Argumento (en Radianes)
double Mod() const; // Calcula el Módulo

//Son friend porque como lo que manda es lo de la izquieda se intenta acceder a los atributos privados de mi clase y no pueden, por ejemplo "cout << complejo", con el 
//friend permito que acceda, esto no sería necesario si utilizo los getters que he definido
//NO son métodos de mi clase, son externos, por eso no llevan const, porque no hay this
friend ostream & operator<<(ostream & os, const  TComplejo & complejo);
friend TComplejo operator+ (double real, const TComplejo& complejo);
friend TComplejo operator- (double real, const TComplejo& complejo);
friend TComplejo operator* (double real, const TComplejo& complejo);
};

#endif