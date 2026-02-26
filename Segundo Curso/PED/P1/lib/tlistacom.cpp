#include "tlistacom.h"

 //################
 //CLASE TLISTANODO
 //################

 //Constructor por defecto 
    TListaNodo::TListaNodo():e()
    {
        anterior=siguiente=NULL;
    }
    //Copia
    TListaNodo::TListaNodo(const TListaNodo& other):e(other.e)
    {
        //Los punteros se declaran a null porque es un nodo separado de la lista original
        anterior=siguiente=NULL;
    }
    //Destructor, sin incializador de objeto ya que el compilador lo hace solo
    TListaNodo::~TListaNodo()
    {
        //No hace falta delete ya que son punteros, no son objetos
        anterior=siguiente=NULL;
    }
    //Sobrecarga operador asiganción
    TListaNodo& TListaNodo::operator=(const TListaNodo& other)
    {
        //Operador asiganción de TComplejo
       if(this != &other)
       {
            this->e = other.e;
            anterior=siguiente=NULL;
       }
        return *this;
    }

 //################
 //CLASE TLISTAPOS
 //################

    TListaPos::TListaPos()
    {
        pos = NULL;
    }

    TListaPos::TListaPos(const TListaPos& other)
    {
        pos = other.pos;
    }

    TListaPos::~TListaPos()
    {
        pos = NULL;
    }

    TListaPos& TListaPos::operator=(const TListaPos& other)
    {
        if(this != &other)
        {
            pos = other.pos;
        }
        return *this;
    }

    bool TListaPos::operator==(const TListaPos& other)
    {
        if (pos == other.pos) return true;
        return false;
    }

    bool TListaPos::operator!=(const TListaPos& other)
    {
        if (pos == other.pos) return false;
        return true;
    }

    TListaPos TListaPos::Anterior()
    {
        //Si el anterior es nulo es el pimer nodo
        if(pos->anterior == NULL) return TListaPos();
        this->pos = pos->anterior;
    }

