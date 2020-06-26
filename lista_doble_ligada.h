#ifndef LISTA_DOBLE_LIGADA_H
#define LISTA_DOBLE_LIGADA_H

#include <user.h>
#include "fstream"

template<class T> class Lista_doble_ligada;

template<class T>
class Nodo
{
private:
    Nodo<T>* sig;
    Nodo<T>* ant;
    T dato;

    friend class Lista_doble_ligada<T>;

public:
    Nodo();
    Nodo(T e);
};

template<class T>
class Lista_doble_ligada
{
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    int cont;

public:
    Lista_doble_ligada(): primero(nullptr), ultimo(nullptr), cont(0) {}
    ~Lista_doble_ligada();
    int size() { return cont; }
    T* at(int pos);
    void push_back(T usuario);
    void erase(int pos);

};








template <class T>
Nodo<T>::Nodo()
{

}

template <class T>
Nodo<T>::Nodo(T e)
{
    dato = e;
    ant = nullptr;
    sig = nullptr;
}


template<class T>
Lista_doble_ligada<T>::~Lista_doble_ligada()
{

}

template <class T>
T *Lista_doble_ligada<T>::at(int pos)
{
    Nodo<T>* aux = primero;
    for (int i = 0; i<pos; i++)
            aux = aux->sig;
    return &aux->dato;
}

template <class T>
void Lista_doble_ligada<T>::push_back(T usuario)
{
    Nodo<T>* nuevo = new Nodo<T>(usuario);

    if (!primero)
        primero = nuevo;
    else{
        nuevo->ant = ultimo;
        ultimo->sig = nuevo;
    }
    ultimo = nuevo;
    cont++;
}

template <class T>
void Lista_doble_ligada<T>::erase(int pos)
{
    Nodo<T>* aux = primero;

    if (cont == 1){
        primero = nullptr;
        ultimo = nullptr;
    }
    else {
        for (int i = 0; i<pos; i++){
            aux = aux->sig;
        }

        if (aux->sig)
            aux->sig->ant = aux ->ant;
        else{
            ultimo = aux->ant;
            ultimo->sig = nullptr;
        }
        if (aux->ant)
            aux->ant->sig = aux->sig;
        else{
            primero = aux->sig;
            primero->ant = nullptr;
        }
    }
    cont--;
    delete aux;
}

#endif // LISTA_DOBLE_LIGADA_H
