#ifndef CHARACTER_H
#define CHARACTER_H
#include "iostream"
#include "lista_doble_ligada.h"
#include <string.h>
#include <sstream>

class Menu;

using namespace std;

class Arma;
class Objeto;
class Character;

class ElemDiccionario{
private:
    string llaveSec;
    int pos;

public:
    int getPos();
    void setPos(int value);
    string getLlaveSec() const;
    void setLlaveSec(const string &value);

    ElemDiccionario();
    ElemDiccionario(string secundaria,int pos);
};

class Inventario
{
private:
    Lista_doble_ligada<Arma> armas;
    Lista_doble_ligada<Objeto> objetos;
public:
    Inventario();
    friend class File_Administrator;
    friend class Menu;
};



class Historial
{
private:
    int asesinatos=0;
    int misiones_completadas=0;
public:
    Historial();
    Historial(int asesinatos, int misiones);

    friend class File_Administrator;
    friend class Menu;
};



class Objeto
{
private:
    string nombre;
    string tipo;
    int nivel;
public:
    Objeto(string nombre,string tipo,int nivel);
    Objeto();

    friend class Arma;
    friend class File_Administrator;
    friend class Menu;
};



class Arma
{
private:
    string nombre;

    int danio;
    int cadencia;

    Objeto canion;
    //Objeto tambor;

public:
    Arma();
    Arma(string nombre, int danio, int cadencia, string nom_c, string nom_t);

    friend class Menu;
    friend class File_Administrator;
};

class Character
{
private:
    string nombre;      //Editables
    string sexo;
    string team;

    int experiencia;    //No editables
    int vida;
    int dinero;
    string nivel;

    int habilidad_acertar;
    int habilidad_critico;

    Historial historial;
    Inventario inventario;

    Objeto blindaje;

    Arma primaria;
    Arma secundaria;

public:
    Character(string nombre,string sexo,string team,int exp,
              int vida,int dinero,string nivel,int acertar,int critico,
              Historial his,Inventario inv,Objeto blin, Arma prim, Arma sec);
    Character();

    string calcular_nivel();
    string to_string();

    friend class Menu;
    friend class File_Administrator;

    string getNombre() const;
    void setNombre(const string &value);
};

#endif // CHARACTER_H
