#ifndef GRAFO_H
#define GRAFO_H
#include <string>
#include <sstream>
#include "lista_doble_ligada.h"
#include <iostream>

using namespace std;

template<class T> class Vertice;
template<class T> class Grafo;

class File_Administrator;
class Menu;

template<class T>
class Arista{
private:
    Vertice<T>* destino;
    int pond;

public:
    Arista(Vertice<T>* destino, int pond);
    Arista();
    string toString();

    friend class Vertice<T>;
    friend class Grafo<T>;
    friend class File_Administrator;
    friend class Menu;
};

template <class T>
class Vertice{
private:
    Lista_doble_ligada<Arista<T>> aristas;
    T dato;
    int contAristas;
public:
    Vertice(T id);
    Vertice();
    void insertaArista(Vertice* destino, int pond);
    string toString();
    T getDato() const;

    Lista_doble_ligada<Vertice<T>> getAdyacentes();

    friend class Grafo<T>;
    friend class File_Administrator;
    friend class Menu;
};

template <class T>
class Grafo
{
private:
    Lista_doble_ligada<Vertice<T>> vertices;
    int contVertices;

    Vertice<T>* posActual;
    string id;
public:
    Grafo();
    Vertice<T>* insertaVertice( T id );
    void InsertaArista(T origen, T destino, int pond);
    Vertice<T>* busca(T id);
    string toString();
    int getContVertices();

    T getPosActual();
    void setPosActual(int pos);
    int size();
    T at(size_t pos);
    string getId() const;
    void setId(const string &value);

    friend class File_Administrator;
    friend class Menu;
};



template<class T>
string Grafo<T>::getId() const
{
    return id;
}

template<class T>
void Grafo<T>::setId(const string &value)
{
    id = value;
}

template<class T>
Grafo<T>::Grafo()
{
    contVertices = 0;
    while (vertices.size()>0) {
        vertices.erase(0);
    }
    posActual=vertices.at(0);
}

template<class T>
Vertice<T>* Grafo<T>::insertaVertice(T id)
{
    if(!busca(id)){
        Vertice<T> v(id);
        vertices.push_back(v);
        contVertices++;
        return vertices.at(vertices.size()-1);
    }
    return nullptr;
}

template<class T>
void Grafo<T>::InsertaArista(T origen, T destino, int pond)
{
    Vertice<T>* v_o = busca(origen);
    Vertice<T>* v_d = busca(destino);

    if (!v_o)
        v_o = insertaVertice(origen);
    if (!v_d)
        v_d = insertaVertice(destino);

    bool validator=true;

    for (int i=0;i<busca(origen)->aristas.size();i++) {
        if(busca(origen)->aristas.at(i)->destino == busca(destino)){
            validator=false;
        }
    }

    if(validator){
    v_o->insertaArista(v_d, pond);
    v_d->insertaArista(v_o, pond);//porque es no dirigido
    }
}

template<class T>
Vertice<T> *Grafo<T>::busca(T id)
{
    for (int i = 0; i<vertices.size(); i++){
        if (vertices.at(i)->dato == id)
            return vertices.at(i);
    }
    return nullptr;
}

template<class T>
string Grafo<T>::toString()
{
    stringstream ss;
    for (int i = 0; i<vertices.size(); i++){
        ss<<vertices.at(i)->toString()<<endl;
    }
    return ss.str();
}

template<class T>
int Grafo<T>::getContVertices()
{
    return contVertices;
}

template<class T>
T Grafo<T>::getPosActual()
{
    return posActual->getDato();
}

template<class T>
void Grafo<T>::setPosActual(int pos)
{
    posActual=vertices.at(pos);
}

template<class T>
int Grafo<T>::size()
{
    return vertices.size();
}

template<class T>
T Grafo<T>::at(size_t pos)
{
    return vertices.at(pos)->dato;
}

template<class T>
T Vertice<T>::getDato() const
{
    return dato;
}

template<class T>
Lista_doble_ligada<Vertice<T> > Vertice<T>::getAdyacentes()
{
    Lista_doble_ligada<Vertice<T>> adyacentes;

    for (int i=0;i<aristas.size();i++) {
        adyacentes.push_back(*aristas.at(i)->destino);
    }

    return adyacentes;
}

template<class T>
Vertice<T>::Vertice(T id)
{
    this->dato = id;
    contAristas = 0;
}

template<class T>
Vertice<T>::Vertice()
{

}

template<class T>
void Vertice<T>::insertaArista(Vertice<T> *destino, int pond)
{
    Arista<T> a(destino,pond);
    aristas.push_back(a);
    contAristas++;
}

template<class T>
string Vertice<T>::toString()
{
    stringstream ss;
    ss<<getDato();
    if (contAristas>0){
        ss<<" ->cont: "<< contAristas <<": ["<<aristas.at(0)->toString();

        if (contAristas>1){
            for (int i=1;i<aristas.size();i++){
                ss<<", "<<aristas.at(i)->toString();
            }
        }
        ss<<"]";
    }
    return ss.str();
}

template<class T>
Arista<T>::Arista(Vertice<T> *destino, int pond)
{
    this->destino = destino;
    this->pond = pond;
}

template<class T>
Arista<T>::Arista()
{

}

template<class T>
string Arista<T>::toString()
{
    stringstream ss;
    ss<<destino->getDato();
    return ss.str();
}


#endif // GRAFO_H
