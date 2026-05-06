#include "tabbcom.h"
#include <queue>

//Invoca a los constructores de TABBCom y TComplejo
TNodoABB::TNodoABB():item(),iz(),de()
{
    //Se utllizan inicializadores por rendimiento, en caso de inciciarlo aquí C++ hace su propio incializador
    //y luego lo sobrescribe con lo que haya puesto aquí, poco eficiente.
}

//Invoca a los constructores de copia de TABBCom y TComplejo
TNodoABB::TNodoABB(const TNodoABB& other):item(other.item),iz(other.iz),de(other.de)
{}

//Al ser una composición invoca a los destructores, es una cascada de destrucción 
//Composicón de 1 TNodo con 1 TComplejo y 2 TABBCom
TNodoABB::~TNodoABB()
{}

TNodoABB& TNodoABB::operator=(const TNodoABB& other)
{
    if(this != &other)
    {
        this->item = other.item; //Iguala valores
        this->iz = other.iz; 
        this->de = other.de; 
    }
    //Se devuelve el valor por referencia para evitar hacer una copia.
    //Esto se hace para poder hacer asignaciones múltiples.
    return *this;
}
//#################################################
//#################################################
//Comprueba si el árbol está vacío
bool TABBCom::EsVacio() const
{
    //Comprueba si hay raíz del árbol
    return this->nodo == NULL;
}

TABBCom::TABBCom()
{
    this->nodo = NULL;
}

TABBCom::TABBCom(const TABBCom& other)
{
    if (other.nodo != NULL)
    {
        this->nodo = new TNodoABB(*other.nodo); //Como other.nodo es un puntero se pone el * para obtener el objeto, el contenido
        //Además aquí empieza la reaccion en cadena de llamar al Constructor de cpia de TNodo que volverá a llamar a este ya que hace iz(other.iz)
    } else
    {
        this->nodo = NULL; //Si el árbol está vacío
    }
}

TABBCom::~TABBCom()
{
    //Evita borrar un nodo ya en NULL
    if (!this->EsVacio())
    {
        delete this->nodo; //Cuando se hace el delete del nodo se llama a los destructores de iz y de
        this->nodo = NULL; //Asegurarse de que no apunta a basura
    }
}

//Iguala un árbol a otro, se hace una copia de other y se elimina el original
TABBCom& TABBCom::operator=(const TABBCom& other)
{
    //Comprueba que no estén en la misma posición de memoria
    if (this != &other)
    {
        //Si el nodo no está vacío se elimina
        if(!this->EsVacio())
        {
            delete this->nodo;
            this->nodo = NULL;
        }
        //Si el otro nodo no está vacío se crea uno nuevo en una nueva posición de memoria
        if (!other.EsVacio())
        {
            this->nodo = new TNodoABB(*other.nodo);
        } else
        {
            this->nodo = NULL;
        }
    }
    return *this;
}

//Cantidad de nodos de un árbol
int TABBCom::Nodos() const
{
    //Caso base, el árbol vacío
    if (this->EsVacio())
    {
        return 0;
    } else
    {
        //En la recursión se van comprobando por la derecha y por la izquierda los nodos que hay sumando 1 si encuentra uno.
        return 1 + this->nodo->iz.Nodos() + this->nodo->de.Nodos();
    }
}

//Se pasa por referencia para que en la recursividad se actue en el mismo vector
void TABBCom::InordenAux(TVectorCom& vector, int& pos)
{
    //Comprobar que no esté vacío
    if (!this->EsVacio())
    {
        //Inorden es Izquierda -> Raíz -> Derecha
        //Si hay hijo iz entra por aquí
        this->nodo->iz.InordenAux(vector, pos);

        //SI ya no hay hijo iz se copia el complejo en el vector
        vector[pos] = this->nodo->item;
        pos++;

        //Por último se hace el hijo de
        this->nodo->de.InordenAux(vector, pos);

    }
}


TVectorCom TABBCom::Inorden()
{
    //Crear un vector del tamaño de los nodos que tiene en árbol 
    TVectorCom vector(this->Nodos());
    //Comprobar que el árbol no está vacío
    if (vector.Tamano() > 0 )
    {
        int pos = 1;
        this->InordenAux(vector, pos);
    }
    return vector;
}

//Se pasa por referencia para que en la recursividad se actue en el mismo vector
void TABBCom::PreordenAux(TVectorCom& vector, int& pos)
{
    //Comprobar que no esté vacío
    if (!this->EsVacio())
    {
         vector[pos] = this->nodo->item;
        pos++;
        
        this->nodo->iz.PreordenAux(vector, pos);

        this->nodo->de.PreordenAux(vector, pos);

    }
}


TVectorCom TABBCom::Preorden()
{
    //Crear un vector del tamaño de los nodos que tiene en árbol 
    TVectorCom vector(this->Nodos());
    //Comprobar que el árbol no está vacío
    if (vector.Tamano() > 0 )
    {
        int pos = 1;
        this->PreordenAux(vector, pos);
    }
    return vector;
}

//Se pasa por referencia para que en la recursividad se actue en el mismo vector
void TABBCom::PostordenAux(TVectorCom& vector, int& pos)
{
    //Comprobar que no esté vacío
    if (!this->EsVacio())
    {
        
        this->nodo->iz.PostordenAux(vector, pos);

        this->nodo->de.PostordenAux(vector, pos);

        vector[pos] = this->nodo->item;
        pos++;
    }
}


TVectorCom TABBCom::Postorden()
{
    //Crear un vector del tamaño de los nodos que tiene en árbol 
    TVectorCom vector(this->Nodos());
    //Comprobar que el árbol no está vacío
    if (vector.Tamano() > 0 )
    {
        int pos = 1;
        this->PostordenAux(vector, pos);
    }
    return vector;
}

//Comprueba si dos árboles son iguales, sin tener en cuenta la posición de los nodos, solo los elementos
bool TABBCom::operator==(TABBCom& other) 
{
    if (this == &other) return true; //Se compara dónde están en memoria.
    if (this->Nodos() != other.Nodos()) return false; //Si no tienen el mismo número de nodos no pueden ser iguals.
    //Compara el Inorden de ambos árboles, como el orden de los nodos no importa solo se comparan los números.
    //Además, usará el operador == de TVector para comparar los vectores.
    return this->Inorden() == other.Inorden();
}

//Devuelve el complejo del nodo
TComplejo TABBCom::Raiz() const
{
    if (this->EsVacio())
    {
        return TComplejo(); //Devuelve un complejo vacío
    }
    else
    {
        return this->nodo->item; //Devuelve el complejo real
    }
}

//Comprobar si los hijos iz y de están vacíos, significa que es una hoja
bool TABBCom::EsHoja()
{
    if (this->EsVacio()) return false;
    return this->nodo->iz.EsVacio() && this->nodo->de.EsVacio();
}

//Devuelve el número de nodos hoja en el árbol
int TABBCom::NodosHoja()
{
    //Si no hay árbol no hay hojas
    if (this->EsVacio())
    {
        return 0;
    }
    //Si es hoja se suma 1
    else if (this->EsHoja())
    {
        return 1;
    }
    //Se suman las hojas
    else
    {
        return this->nodo->iz.NodosHoja() + this->nodo->de.NodosHoja();
    }
}

bool TABBCom::Buscar(const TComplejo &complejo) const
{
    //Caso base, árbol vacío
    if (this->EsVacio())
    {
        return false;
    }
    //Caso base, encontrado
    else if (this->nodo->item == complejo)
    {
        return true;
    }
    //Si el complejo es mayor, se busca por la derecha
    else if (this->nodo->item < complejo)
    {
        return this->nodo->de.Buscar(complejo);
    }
    //Si es menor, por la izquierda
    else
    {
        return this->nodo->iz.Buscar(complejo);
    }
}

bool TABBCom::Insertar(const TComplejo &complejo)
{
    //Caso base, hueco vacío
    if (this->EsVacio())
    {
        this->nodo = new TNodoABB();
        this->nodo->item = complejo;
        return true; //Insertado
    }
    //SI ya existe no se puede insertar
    else if (this->nodo->item == complejo)
    {
        return false;
    }
    //Si es menor se sigue por la izquierda
    else if (complejo < this->nodo->item) 
    {
        return this->nodo->iz.Insertar(complejo);
    }
    //Si es mayor, se va por la derecha
    else
    {
        return this->nodo->de.Insertar(complejo);
    }
}

TComplejo TABBCom::MayorIzquierda()
{
    //Hijo derecho está vacío, este el máximo
    if (this->nodo->de.EsVacio())
    {
        return this->nodo->item;
    }
    else
    {
        //Seguir buscando por la derecha
        return this->nodo->de.MayorIzquierda();
    }
}

bool TABBCom::Borrar(const TComplejo& complejo)
{ 
    //Árbol vacio
    if (this->EsVacio()) return false;
    //Si el complejo es menor que el item se busca por la izquierda
    if (complejo < this->nodo->item) return this->nodo->iz.Borrar(complejo);
    //Si el complejo es mayor que el item se busca por la derecha
    if (complejo > this->nodo->item) return this->nodo->de.Borrar(complejo);

    //### A partir de aquí el elemento ha sido ENCONTRADO ###//

    //Comprobar si es una hoja, el borrado es sencillo
    if (this->EsHoja())
        {
            delete this->nodo;
            this->nodo = NULL;
            return true;
        }

    //Comprobar si solo tiene un hijo a la izquierda
    if (this->nodo->de.EsVacio())
    {
        //Me guardo el nodo actual en un puntero temporal para poder eliminarlo después
        TNodoABB* aux = this->nodo;
        this->nodo = this->nodo->iz.nodo; //La raíz es ahora es su hijo iz
        aux->iz.nodo = NULL; //Se pone primero el aux a NULL para que no haga efecto cascada y borre al nieto
        delete aux;
        return true;
    } 
    
    //Solo tiene hijo a la derecha
    if (this->nodo->iz.EsVacio())
    {
        TNodoABB* aux = this->nodo;
        this->nodo = this->nodo->de.nodo; //raíz = hijo derecha
        aux->de.nodo = NULL;              
        delete aux;
        return true;
    }
    else
    {
        //En este punto la raíz tiene 2 hijos
        TComplejo reemplazo = this->nodo->iz.MayorIzquierda();
        //Cambio el nodo actual (el que quiero borrar) por el mayor de la izquierda 
        //que lo sustituye
        this->nodo->item = reemplazo;
        //Ahora se borra el reemplazo para evitar duplicados, 
        //irá directamente al caso que es una hoja y lo eliminará directamente.
        return this->nodo->iz.Borrar(reemplazo);
    }

} 

int TABBCom::Altura()
{
    //Caso base árbol vacío
    if (this->EsVacio())
    {
        return 0;
    }
    else
    {
        //Calcular la altura de cada subárbol
        int altIz = this->nodo->iz.Altura();
        int altDe = this->nodo->de.Altura();
        
        //Quedarse con el mayor + 1 que es el nodo actual, un árbol con 1 nodo por 
        //ejemplo sería caso base + 1
        if (altIz > altDe)
        {
            return altIz + 1;
        }
        else
        {
            return altDe + 1;
        }
    }
}

#include <queue>

TVectorCom TABBCom::Niveles() const
{
    //Tamaño del vector
    int tam = this->Nodos();
    TVectorCom vector(tam);
    
    if (this->EsVacio())
    {
        return vector; //Vector vacío
    }

    //Cola FIFO de punteros constantes ya que solo se lee del árbol al que apuntamos
    std::queue<const TABBCom*> cola;
    int indice = 1;

    //meter el árbol actual en la cola
    cola.push(this);

    while (!cola.empty())
    {
        //Primer elemento
        const TABBCom* actual = cola.front();
        cola.pop();

        //Guardar complejro en el vector
        vector[indice] = actual->nodo->item;
        indice++;

        //Encolar si hay hijos
        if (!actual->nodo->iz.EsVacio())
        {
            cola.push(&(actual->nodo->iz));
        }
        if (!actual->nodo->de.EsVacio())
        {
            cola.push(&(actual->nodo->de));
        }
    }

    return vector;
}

ostream& operator<<(ostream& os, const TABBCom& arbol)
{
    //Obtener árbol en un vector, podría ser Inorden
    TVectorCom v = arbol.Niveles(); 
    
    //uso el << de TVector
    os << v;

    return os;
}