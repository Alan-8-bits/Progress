#ifndef INDICE_H
#define INDICE_H

#include <iostream>
#include "user.h"
#include <fstream>
#include <sstream>
using namespace std;

class Referencia
{
private:
    string llave_primaria;
    int direccion;
    bool bloqueado=false;
public:
    Referencia();

    friend class Indice;
    int getDireccion() const;
    string getLlave_primaria() const;
    bool getBloqueado() const;
    void setBloqueado(bool value);
    void setLlave_primaria(const string &value);
};

class Indice
{
private:
    Referencia* cuentas = nullptr;
    int tama=0;
public:
    Indice();
    void ordenar_indice();
    Referencia at(int index);
    int size();
    User getAt(int index);
    void modificarAt(int &index, User nuevo);
    void bloquear_temporalmente(int index,bool bloq);
    void eliminar(int index);

    void actualizar();
};

#endif // INDICE_H
