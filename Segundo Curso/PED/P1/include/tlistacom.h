#ifndef TLISTACOM_H
#define TLISTACOM_H
#include "tvectorcom.h"
class TListaNodo
{
    //Permite a la clase TListaPos acceder a los atributos privados de esta clase
    friend class TListaPos;
    friend class TListaCom;
    private:
    //Elemento del nodo
    TComplejo e;
    //Nodo anterior
    TListaNodo *anterior;
    //Nodo siguiente
    TListaNodo *siguiente;
    // :e() incializador de objeto, llama al constructor de TComplejo, si no se pone se llama al defecto de TComplejo
    //No se hace dentro de las llaves porque se llamaría dos veces, el compilador sabe que es una composición (dentro de ListaNodo hay Tcomplejos)
    //EN el destructor no hace falta :e(), lo hace bien directamente, no llama 2 veces
    
    //Constructor por defecto 
    TListaNodo();
    //CREADO POR MÍ, para método InsCabeza
    TListaNodo(const TComplejo&);
    //Copia
    TListaNodo(const TListaNodo&);
    //Destructor
    ~TListaNodo();
    //Sobrecarga operador asiganción
    TListaNodo & operator=(const TListaNodo&);

};

class TListaPos
{
    friend class TListaCom;
    TListaNodo *pos;
    //Cosntrucor por defecto
    TListaPos();
    //Copia
    TListaPos(const TListaPos&);
    //Para el destructor se hace pos=NULL, no se hace delete pos porque te llevas el nodo contigo, pos apunta a un nodo.
    ~TListaPos();
    //Sobrecarga del operador asignación
    TListaPos& operator=(const TListaPos&);


    //Sobrecarga operador igualdad
    bool operator==(const TListaPos&);
    //Sobrecarga operador desigualdad
    bool operator!=(const TListaPos&);
    TListaPos Anterior();
    TListaPos Siguiente();
    // Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
    bool EsVacia() const;
};

class TListaCom
{
    //Este destrucotr si que tiene que hacer delete para liberar memoria
    //Copia profunda
    private:
    // Primer elemento de la lista
    TListaNodo *primero;
    // Ultimo elemento de la lista
    TListaNodo *ultimo;

    // Constructor por defecto
    TListaCom ();
    // Constructor de copia
    TListaCom (const TListaCom &);
    // Destructor
    ~TListaCom ();
    // Sobrecarga del operador asignación
    TListaCom & operator=(const TListaCom &);
    // Sobrecarga del operador igualdad
    bool operator==(const TListaCom &);
    // Sobrecarga del operador desigualdad
    bool operator!=(const TListaCom &);
    // Sobrecarga del operador suma
    TListaCom operator+(const TListaCom &);
    // Sobrecarga del operador resta
    TListaCom operator-(const TListaCom &);
    // Devuelve true si la lista está vacía, false en caso contrario
    bool EsVacia();
    // Inserta el elemento en la cabeza de la lista
    bool InsCabeza(const TComplejo &);
    // Inserta el elemento a la izquierda de la posición indicada
    bool InsertarI(const TComplejo &, const TListaPos &);
    // Inserta el elemento a la derecha de la posición indicada
    bool InsertarD(const TComplejo &, const TListaPos &);
    // Busca y borra la primera ocurrencia del elemento
    bool Borrar(const TComplejo &);
    // Busca y borra todas las ocurrencias del elemento
    bool BorrarTodos(const TComplejo &);
    // Borra el elemento que ocupa la posición indicada
    //No se pone const ya que se va a modificar la TListaPos.
    bool Borrar(TListaPos &);
    // Obtiene el elemento que ocupa la posición indicada
    TComplejo Obtener(const TListaPos &);
    // Devuelve true si el elemento está en la lista, false en caso contrario
    bool Buscar(const TComplejo &);
    // Devuelve la posición dónde está el complejo
    TListaPos BuscarPos(const TComplejo &);
    // Devuelve la longitud de la lista
    int Longitud();
    // Devuelve la primera posición en la lista
    TListaPos Primera();
    // Devuelve la última posición en la lista
    TListaPos Ultima();


    // Sobrecarga del operador salida
    friend ostream & operator<<(ostream &, const TListaCom &);
};

#endif;