#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User
{
public:
    User();
    User(string nombre, string correo, string username, string password, int primera_direccion);
    string getCorreo() const;
    string getUsername() const;
    string getPassword() const;
    string getNombre() const;

    void setNombre(const string &value);
    void setCorreo(const string &value);
    void setUsername(const string &value);
    void setPassword(const string &value);

    int getDireccion_personaje() const;
    void setDireccion_personaje(int value);

private:
    string nombre;
    string correo;
    string username;
    string password;

    int direccion_personaje;
};

#endif // USER_H
