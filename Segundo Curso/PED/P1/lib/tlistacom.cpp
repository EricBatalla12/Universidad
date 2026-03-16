#include "tlistacom.h"

 //################
 //CLASE TLISTANODO
 //################

 //Constructor por defecto 
    TListaNodo::TListaNodo():e()
    {
        anterior=siguiente=NULL;
    }

    TListaNodo::TListaNodo(const TComplejo& complejo):e(complejo)
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
       //Crear una posición temporal que como se devuelve por valor
       //se devolverá una copia. COmo es por defecto, pos = NULL.
       TListaPos aux;
       //Comprobar que existe un anterior
       if (pos->anterior != NULL) aux.pos = pos->anterior;
       return aux;
    }

    TListaPos TListaPos::Siguiente()
    {
       TListaPos aux;
       //Comprobar que existe un siguiente
       if (pos->siguiente != NULL) aux.pos = pos->siguiente;
       return aux;
    }

    bool TListaPos::EsVacia()
    {
        return pos == NULL;
    }

 //################
 //CLASE TLISTACOM
 //################

TListaCom::TListaCom():primero(), ultimo()
{
    //Los punteros primero y ultimo apuntan a NULL
}

TListaCom::TListaCom(const TListaCom& other):primero(other.primero), ultimo(other.ultimo)
{
    //Copia profunda de la lista
    //TO-DO
}

TListaCom::~TListaCom()
{
    //Usar delete para vaciar memoria
}

TListaCom & TListaCom::operator=(const TListaCom& other)
{
    if (this != &other)
    {
        if (other.EsVacia())
        {
            for
        }
    }
    return *this;
}

bool TListaCom::operator==(const TListaCom& other)
{
    re
}

int TListaCom::Longitud()
{
    int longitud = 0;
    TListaNodo *aux = this->primero;

    while (aux != NULL)
    {
        longitud++;
        aux = aux->siguiente;
    }
    return longitud;
}

bool TListaCom::InsCabeza(const TComplejo& complejo)
{
    //Con esto tengo un puntero con siguiente y anterior a null y valor del complejo
    //Si no ha podido reservar memoria devuelve NULL.
    TListaNodo *cabeza = new TListaNodo(complejo);

    if (cabeza != NULL)
    {
        //Comprobar lista vacía
        if (primero == NULL && ultimo == NULL)
        {
            primero=ultimo=cabeza;
        }
        else
        {        
            //Enganchar el nuevo nodo a la cabeza
            cabeza->anterior = this->primero;
            this->primero->siguiente = cabeza;
            //Mover el dedo "último"
            this->primero = cabeza;
        }
    }
    else
    {
        return false;
    }

    return true;
}


