#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

using namespace std;


class Location
{
private:
    string nombre;
    string tipo;

    int dificultad;
    int nivel_tienda;


public:
    Location();

    string getNombre() const;
    void setNombre(const string &value);


    friend ostream& operator<<(ostream &strm, const Location &a) {
      return strm << a.getNombre();
    }

    friend bool operator==(Location &uan,Location &chu){
        if(uan.getNombre()==chu.getNombre()){
            return true;
        }
        else {
            return false;
        }
    }

    string getTipo() const;
    void setTipo(const string &value);
    int getDificultad() const;
    void setDificultad(int value);
    int getNivel_tienda() const;
    void setNivel_tienda(int value);
};







#endif // LOCATION_H
