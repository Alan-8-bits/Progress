#include "user.h"

User::User(string nombre, string correo, string username, string password, int primera_direccion)
{
    this->nombre=nombre;
    this->correo=correo;
    this->username=username;
    this->password=password;
    this->direccion_personaje=primera_direccion;
}

User::User()
{
    direccion_personaje=-1;
    username="default";
}

string User::getCorreo() const
{
    return correo;
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

string User::getNombre() const
{
    return nombre;
}

void User::setNombre(const string &value)
{
    nombre = value;
}

void User::setCorreo(const string &value)
{
    correo = value;
}

void User::setUsername(const string &value)
{
    username = value;
}

void User::setPassword(const string &value)
{
    password = value;
}

int User::getDireccion_personaje() const
{
    return direccion_personaje;
}

void User::setDireccion_personaje(int value)
{
    direccion_personaje = value;
}
