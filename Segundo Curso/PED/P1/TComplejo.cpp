#include "TComplejo.hpp"

TComplejo::TComplejo()
{
    re = 0;
    im = 0;
}

TComplejo::TComplejo(double real)
{
    re = real;
    im = 0; 
}

TComplejo::TComplejo(double real, double imaginario)
{
    re = real;
    im = imaginario;
}
//Se pasa const porque el objeto other no va a ser modificado, y se pasa por referencia por la velocidad
TComplejo::TComplejo(const TComplejo& other)
{
    re = other.re;
    im = other.im;
}

TComplejo& TComplejo::operator=(const TComplejo& other)
{
    //Comprobar que el objeto no sea él mismo para que no se autodestruya
    //other se pasa por referencia para comparar punteros, ya que this es la refencia del objeto
    if (this != &other)
    {

    }
}