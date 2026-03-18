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

    bool TListaPos::EsVacia() const
    {
        return pos == NULL;
    }

 //################
 //CLASE TLISTACOM
 //################

TListaCom::TListaCom():primero(), ultimo()
{
    //Los punteros primero y ultimo apuntan a NULL directamente
    //si no usara el inicializador : el compilador crearía los punteros
    //pero apuntarían a basura
}

TListaCom::TListaCom(const TListaCom& other):primero(), ultimo()
{
    TListaPos aux_other;
    TListaPos aux_newList;
    aux_other.pos = other.primero;
    aux_newList.pos = this->primero;

    while (aux_other.pos != NULL)
    {
        this->InsertarD(aux_other.pos->e, aux_newList);
        aux_other.pos = aux_other.pos->siguiente;
        //Como en InsertarD último es el nuevo nodo en caso
        //de que sea el útimo por la derecha se puede ir 
        //avanzando este puntero viendo dónde está la última posición.
        aux_newList.pos = this->ultimo;
    }
}

TListaCom::~TListaCom()
{
    TListaPos aux;
    TListaPos aux2;
    aux.pos = this->primero;

    while(aux.pos != NULL)
    {
        aux2.pos = aux.pos->siguiente;
        delete aux.pos;
        aux = aux2;
    }
}

TListaCom & TListaCom::operator=(const TListaCom& other)
{
    //Si se apunta a la misma dirección se devuelve tal cual
    if (this == &other) return *this;

    if (other.EsVacia())
    {
        this->~TListaCom();
        return *this;
    }

    this->primero = other.primero;
    this->ultimo = other.ultimo;

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

bool TListaCom::EsVacia() const
{
    return (primero == NULL & ultimo == NULL);
}

bool TListaCom::InsCabeza(const TComplejo& complejo)
{
    //Con esto tengo un puntero con siguiente y anterior a null y valor del complejo
    //Si no ha podido reservar memoria devuelve NULL.
    TListaNodo *cabeza = new TListaNodo(complejo);

    if (cabeza == NULL) return false;

    //Comprobar lista vacía
    if (this->EsVacia())
    {
        primero = ultimo = cabeza;
        return true;
    }
    //Enganchar el nuevo nodo a la cabeza
    cabeza->siguiente = this->primero;
    this->primero->anterior = cabeza;
    //Mover el dedo "último"
    this->primero = cabeza;

    return true;
}

bool TListaCom::InsertarI(const TComplejo& complejo, const TListaPos& posicion)
{
    //Puedo usar esta función ya que EsVacia() es const
    //y además TListaPos ha declarado como friend a TListaCom
    if (posicion.EsVacia()) return false;

    //Si el puntero anterior es NULL se trata como cabeza
    if (posicion.pos->anterior == NULL)
    return this->InsCabeza(complejo);
    
    TListaNodo *new_node = new TListaNodo(complejo);
    if (new_node == NULL) return false;

    //El nuevo nodo se engancha
    new_node->siguiente = posicion.pos;
    new_node->anterior = posicion.pos->anterior;
    //Ahora se enganchan al nodo
    posicion.pos->anterior->siguiente = new_node;
    posicion.pos->anterior = new_node;

    return true;
}

bool TListaCom::InsertarD(const TComplejo& complejo, const TListaPos& posicion)
{
    if (posicion.EsVacia()) return false;
    
    TListaNodo *new_node = new TListaNodo(complejo);
    if (new_node == NULL) return false;

    if (posicion.pos->siguiente == NULL)
    {
        //Ahora el nuevo nodo será la cola
        new_node->anterior = posicion.pos;
        posicion.pos->siguiente = new_node;
        this->ultimo = new_node;
    }
    else
    {
        //Enganchar el nuevo
        new_node->anterior = posicion.pos;
        new_node->siguiente = posicion.pos->siguiente;
        //Ahora los antiguos
        posicion.pos->siguiente->anterior = new_node;
        posicion.pos->siguiente = new_node;
    }

    return true;
}

bool TListaCom::Borrar(const TComplejo& complejo)
{
    TListaPos aux = this->BuscarPos(complejo);
    if (aux.EsVacia()) return false;

    return this->Borrar(aux);
}

//No es constante ya que se va a modificar, se elimina
bool TListaCom::Borrar(TListaPos& posicion)
{
    //Solo hay un elemento
    if (this->primero == posicion.pos && this->ultimo == posicion.pos)
    {
        primero=ultimo=NULL;
        delete posicion.pos;
        posicion.pos = NULL; //Eliminar la dirección que apunta a basura.
        return true;
    }
    //Se elimina el primer elemento
    if (this->primero == posicion.pos)
    {
        //Ahora primero apunta al nodo siguiente
        this->primero = primero->siguiente;
        //Siguiente de primero apunta a NULL para no apuntar a basura
        this->primero->anterior = NULL;
        delete posicion.pos;
        posicion.pos = NULL;
        return true;
    }
    //Se elimina el último elemento
    if (this->ultimo == posicion.pos)
    {
        this->ultimo = ultimo->anterior;
        this->ultimo->siguiente = NULL;
        delete posicion.pos;
        posicion.pos = NULL;
        return true;
    }
    //Se elimina un elemnto de por medio de la lista
    //El nodo de atrás apunta al siguiente de posicion.pos
    posicion.pos->anterior->siguiente = posicion.pos->siguiente;
    //El nodo de delante apunta al anterior de posicion.pos
    posicion.pos->siguiente->anterior = posicion.pos->anterior;
    delete posicion.pos;
    posicion.pos = NULL;
    return true;
}

bool TListaCom::BorrarTodos(const TComplejo& complejo)
{
    //Voy a intentar no usar Borrar(TComplejo) ni BuscarPos para evitar que la 
    //complejidad sea n2 (cuadrática)
    //Para ello he creado un método 
    TListaPos aux;
    TListaPos aux2;
    aux.pos = this->primero;
    bool borrado = false;

    while(aux.pos != NULL)
    {
        if(this->Obtener(aux) == complejo)
        {
            //Aquí aux2 apunta al siguiente de aux, ya que luego si 
            //intenta copiarse a aux tal cual apuntaría a basura, y el 
            //siguiente de basura es error de segmentación
            aux2.pos = aux.pos->siguiente;
            this->Borrar(aux);
            aux = aux2;
            borrado = true;
        } else {aux.pos = aux.pos->siguiente;}
    }
    return borrado;
}

bool TListaCom::Buscar(const TComplejo& complejo)
{
    TListaPos aux;
    aux.pos = this->primero;

    //Con esto también se comprueba si la lista está vacía
    while (aux.pos != NULL)
    {
        if (this->Obtener(aux) == complejo) return true;
        aux.pos = aux.pos->siguiente;
    }
    return false;
}

TListaPos TListaCom::BuscarPos(const TComplejo& complejo)
{
    TListaPos aux;
    aux.pos = this->primero;

    //Con esto también se comprueba si la lista está vacía
    while (aux.pos != NULL)
    {
        if (this->Obtener(aux) == complejo) return aux;
        aux.pos = aux.pos->siguiente;
    }
    return TListaPos();
}

TComplejo TListaCom::Obtener(const TListaPos& posicion)
{
    if (posicion.EsVacia()) return TComplejo();
    return posicion.pos->e;
}

TListaPos TListaCom::Primera()
{
    if (this->EsVacia()) return TListaPos();
    TListaPos aux;
    aux.pos = this->primero;
    return aux;
}

TListaPos TListaCom::Ultima()
{
    if (this->EsVacia()) return TListaPos();
    TListaPos aux;
    aux.pos = this->ultimo;
    return aux;
}


