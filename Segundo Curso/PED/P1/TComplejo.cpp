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
        re = other.re;
        im = other.im;
    }
    //Se devuelve *this para  asiganciones múltiples 
    //No se crea una copia del objeto ya que TComplejo& hace que se devuelva una referencia 
    return *this;
}

TComplejo TComplejo::operator+ (const TComplejo& complejo) 
{
    //Se declara el objeto directamente, no es un puntero
    TComplejo temp; 
    temp.re = this->re + complejo.re;
    temp.im = this->im + complejo.im;
    //Se devuelve el objeto por valor (copia) ya que es temporal, se borraría en caso contrario
    return temp;
}

TComplejo TComplejo::operator- (const TComplejo& complejo)
{
    TComplejo temp; 
    temp.re = this->re - complejo.re;
    temp.im = this->im - complejo.im;
    return temp;
}

TComplejo TComplejo::operator* (const TComplejo& complejo)
{
    TComplejo temp; 
    temp.re = this->re * complejo.re;
    temp.im = this->im * complejo.im;
    return temp;
}

TComplejo TComplejo::operator+ (double real)
{
    TComplejo temp; 
    temp.re = this->re + real;
    return temp;
}

TComplejo TComplejo::operator- (double real)
{
    TComplejo temp; 
    temp.re = this->re - real;
    return temp;
}

TComplejo TComplejo::operator* (double real)
{
    TComplejo temp; 
    temp.re = this->re * real;
    return temp;
}

bool TComplejo::operator== (const TComplejo& other)
{
    if ((this == &other) || (re == other.re && im == other.im))
    {
        return true;
    } else 
    {
        return false;
    }
}

bool TComplejo::operator!= (const TComplejo& other)
{
    //Se pasan por valor para comparar re e im, no las direcciones de memoria
    if (*this == other)
    {
        return false;
    } else 
    {
        return true;
    }
}

double TComplejo::Arg()
{
    //atan2 gestiona la división por 0 y devuelve un ángulo en el rango [-pi, pi]
    double a = atan2(im, re);
    return a;
}

double TComplejo::Mod()
{
    double m = sqrt(pow(re, 2) + pow(im, 2));
    return m;
}

ostream & operator<<(ostream & os, const TComplejo & complejo)
{
    os << "(" << complejo.re << " " << complejo.im << ")";
    return os;
}

TComplejo operator+ (double real, const TComplejo& complejo)
{
    TComplejo temp;
    temp.re = real + complejo.re;
    temp.im = complejo.im;
    return temp;
}

TComplejo operator- (double real, const TComplejo& complejo)
{
    TComplejo temp;
    temp.re = real - complejo.re; 
    temp.im = -complejo.im; //El menos es porque la parte imaginaria se ve afectada por la resta de los reales
    return temp;
}

TComplejo operator* (double real, const TComplejo& complejo)
{
    TComplejo temp;
    temp.re = real * complejo.re; 
    temp.im = real * complejo.im;
    return temp;
}





