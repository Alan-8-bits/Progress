#include "location.h"

string Location::getNombre() const
{
    return nombre;
}

void Location::setNombre(const string &value)
{
    nombre = value;
}

string Location::getTipo() const
{
    return tipo;
}

void Location::setTipo(const string &value)
{
    tipo = value;
}

int Location::getDificultad() const
{
    return dificultad;
}

void Location::setDificultad(int value)
{
    dificultad = value;
}

int Location::getNivel_tienda() const
{
    return nivel_tienda;
}

void Location::setNivel_tienda(int value)
{
    nivel_tienda = value;
}

Location::Location()
{

}
