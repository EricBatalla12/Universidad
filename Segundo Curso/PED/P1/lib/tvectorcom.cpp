#include "tvectorcom.h"

TVectorCom::TVectorCom()
{
    tamano = 0;
    c = NULL;
}

TVectorCom::TVectorCom(int tam)
{
    if(tam < 0)
    {
        tamano = 0;
        c = NULL;
    } else {
        tamano = tam;
        c = new TComplejo[tamano]; //Array de complejos construidos por defecto
    }
}

TVectorCom::TVectorCom(const TVectorCom& other)
{
    tamano = other.tamano;
    if(tamano > 0)
    {
        c = new TComplejo[tamano];
        for(int i = 0; i < tamano; i++) c[i] = other.c[i]; 
    } else {
        c = NULL;
    }
}

TVectorCom::~TVectorCom()
{
    if(c != NULL) //Evita intentar borrar un array ya vacío
    {
        delete[] c; //Los [] son porque el tipo del array lo he definido yo, no es primitivo
        c = NULL;
        tamano = 0;
    }
}

TVectorCom& TVectorCom::operator=(const TVectorCom & other)
{
    if(this != &other)
    {
        if(c != NULL) //Evita intentar borrar un array ya vacío
        {
            delete[] c; //Los [] son porque el tipo del array lo he definido yo, no es primitivo
            c = NULL; //Para que no sea basura
        }
        tamano = other.tamano;
        if(tamano > 0)
        {
            c = new TComplejo[tamano];
            for(int i = 0; i < tamano; i++) c[i] = other.c[i]; 
        } else {
            c = NULL;
        }
    }
    //Se devuelve el valor por referencia para evitar hacer una copia.
    //Esto se hace para poder hacer asignaciones múltiples.
    return *this;
}

bool TVectorCom::operator==(const TVectorCom & other)
{
    if (this == &other) return true; //Si el puntero es el mismo, se está comparando el mismo array

    if (tamano == other.tamano)
    {
        for (int i = 0; i < tamano; i++){
            if (c[i] != other.c[i]) return false;
        }
    } else {
        return false;
    }
    return true;
}

bool TVectorCom::operator!=(const TVectorCom & other)
{
    if (tamano == other.tamano)
    {
        for (int i = 0; i < tamano; i++){
            if (c[i] != other.c[i]) return true;
        }
    } else {
        return true;
    }
    return false;
}

//Parte izquierda
TComplejo& TVectorCom::operator[](int dim)
{
    if (dim > 0 && dim <= tamano) return c[dim - 1];
    return error; //devuelve un TComplejo ya generado por defecto (0,0)
    //No se puede devolver un TComplejo(); porque sería una variable local y esas
    //no se pueden devolver por referencia ya que se destruyen.
    
}

//Parte derecha
TComplejo TVectorCom::operator[](int dim) const
{
     if (dim > 0 && dim <= tamano) return c[dim - 1];
    return TComplejo(); //Aquí se crea una variable temporal ya que se va a devolver
    //por valor, es decir, llama al constructor de copia para crear un nuevo objeto, 
    //se destruye el temporal pero se mantiene la copia.
}