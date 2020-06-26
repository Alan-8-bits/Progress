#ifndef MENU_H
#define MENU_H

#include<stdlib.h>
#include<time.h>
#include <vector>
#include <user.h>
#include <iostream>
#include <fstream>
#include "lista_doble_ligada.h"
#include "file_administrator.h"
#include "grafo.h"
#include "location.h"
#include "indice.h"
using namespace std;

class Menu
{
public:
    Menu();
    void principal();
    void agregar_usuario();
    void acceder_usuario();
    void mostrar_usuarios();

    void mostrar_usuario();
    void modificar_usuario();

    bool isvalid_mail(string correo);
    bool isvalid_name(string username);
    bool isvalid_string(string str);

    void menu_personajes();
    void acceder_personaje();

    void principal_grafos();
    void acceder_grafo(Grafo<Location> *personal);

    void editor_de_armas();
    void combate(Character oponente);

    void actualizar_diccionario();

private:

    //Lista_doble_ligada<User> usuarios;
    Indice indice;
    User usuario;
    int nrr_usuario;

    File_Administrator administrador_de_archivos;

    Lista_doble_ligada<ElemDiccionario> diccionario;
    Character personaje;
    int NRR;
    int numero_personajes=0;

    Grafo<Location> grafo_global;
    Grafo<Location> grafo;
    Lista_doble_ligada<Grafo<Location>> grafos;
    Lista_doble_ligada<ElemDiccionario> indice_grafos;

    friend class Character;
    friend class File_Administrator;
};

#endif // MENU_H
