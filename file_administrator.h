#ifndef FILE_ADMINISTRATOR_H
#define FILE_ADMINISTRATOR_H

#include "lista_doble_ligada.h"
#include "user.h"
#include "character.h"
#include "grafo.h"
#include "location.h"
#include "indice.h"
#include <sstream>

class File_Administrator
{
public:
    File_Administrator();

    void respaldar_usuario(User usuario);
    Lista_doble_ligada<User> recuperar_usuarios();

    void respaldar_personaje(Character personaje, int &num_per, int nrr, string destino, Lista_doble_ligada<ElemDiccionario> &diccionario, string cuenta);
    int num_personajes(string cuenta, Lista_doble_ligada<ElemDiccionario> &diccionario);
    int tamano_total_personaje(Character personaje);
    void elimina_personaje(int pos, int &num_per, Lista_doble_ligada<ElemDiccionario> &diccionario, string cuenta);
    Lista_doble_ligada<ElemDiccionario> construir_diccionario(Indice indice);
    void mostrar_personajes_de_usuario(string cuenta, Lista_doble_ligada<ElemDiccionario> &diccionario);
    string read_string(ifstream &archivo);

    Character load_character(int inicial);
    void save_character(Character *obj, Lista_doble_ligada<ElemDiccionario> &diccionario, string cuenta);

    Grafo<Location> recupera_grafo_global(string nombre_archivo);
    Lista_doble_ligada<Grafo<Location>> recupera_grafos();
    Grafo<Location> recupera_grafo(int pos);
    void respalda_grafos(Lista_doble_ligada<Grafo<Location>> grafos);
    void respalda_grafo(Grafo<Location> grafo, int pos_old, Lista_doble_ligada<ElemDiccionario> &indie);
    void elimina_grafo(int pos, Lista_doble_ligada<ElemDiccionario> &indie);
    Lista_doble_ligada<ElemDiccionario> carga_indice_grafos();

    Character recupera_oponente(int mision);
};

#endif // FILE_ADMINISTRATOR_H
