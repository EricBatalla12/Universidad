#ifndef TLISTACOM_H
#define TLISTACOM_H
#include "tvectorcom.h"
class TListaNodo
{
    friend class TListaPos;
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
    //Copia
    TListaNodo(const TListaNodo&);
    //Destructor
    ~TListaNodo();
    //Sobrecarga operador asiganción
    TListaNodo & operator=(const TListaNodo&);

};

class TListaPos
{
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
    bool EsVacia();
};

class TListaCom
{
    //Este destrucotr si que tiene que hacer delete para liberar memoria
    //Copia profunda
};

#endif;