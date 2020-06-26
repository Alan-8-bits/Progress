#include "indice.h"

Indice::Indice()
{
    actualizar();
}

void Indice::ordenar_indice()
{
    for (int x=0;x<tama-1;x++) {
        Referencia aux=cuentas[x];
        int nrr=x;
        for (int i=x;i<tama;i++) {
            if(aux.llave_primaria>cuentas[i].llave_primaria){
                aux=cuentas[i];
                nrr=i;
            }
        }
        swap(cuentas[x],cuentas[nrr]);
    }
}

Referencia Indice::at(int index)
{
    return cuentas[index];
}

int Indice::size()
{
    return tama;
}

User Indice::getAt(int index)
{
    ifstream fin;
    fin.open("usuarios.txt");
    fin.seekg(cuentas[index].direccion);

    string s;
    getline(fin,s);
    User u;
    for (size_t i=19;i>=0;i--) {
        if(s.at(i)!=' '){
            u.setNombre(s.substr(0,i+1));
            break;
        }
    }
    for (size_t i=40;i>=21;i--) {
        if(s.at(i)!=' '){
            u.setCorreo(s.substr(21,i+1-21));
            break;
        }
    }
    for (size_t i=61;i>=42;i--) {
        if(s.at(i)!=' '){
            u.setUsername(s.substr(42,i+1-42));
            break;
        }
    }
    for (size_t i=82;i>=63;i--) {
        if(s.at(i)!=' '){
            u.setPassword(s.substr(63,i+1-63));
            break;
        }
    }
    stringstream ss(s.substr(86,s.size()-86));
    int dir;
    ss>>dir;
    u.setDireccion_personaje(dir);

    return u;
}

void Indice::modificarAt(int &index, User nuevo)
{
    fstream fout;
    fout.open("usuarios.txt");
    fout.seekg(cuentas[index].direccion);
    string aux;

    for (int i=0;i<20-int(nuevo.getNombre().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<nuevo.getNombre().substr(0,20)<<aux<<'|';
    aux.clear();
    for (int i=0;i<20-int(nuevo.getCorreo().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<nuevo.getCorreo().substr(0,20)<<aux<<'|';
    aux.clear();
    for (int i=0;i<20-int(nuevo.getUsername().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<nuevo.getUsername().substr(0,20)<<aux<<'|';
    aux.clear();
    for (int i=0;i<20-int(nuevo.getPassword().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<nuevo.getPassword().substr(0,20)<<aux<<'|';
    fout<<cuentas[index].getBloqueado()<<'|';
    aux.clear();
    int count = 0,n=nuevo.getDireccion_personaje();
    while (n > 0) {
        n = n / 10;
        ++count;
    }
    if(n==-1)
        count=2;
    for (int i=0;i<20-count;i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<nuevo.getDireccion_personaje()<<aux<<endl;

    fout.close();

    actualizar();

    for (int i=0;i<tama;i++) {
        if(cuentas[i].llave_primaria==nuevo.getUsername()){
            index=i;
            break;
        }
    }
}

void Indice::bloquear_temporalmente(int index, bool bloq)
{
    cuentas[index].bloqueado=bloq;
}

void Indice::eliminar(int index)
{
    fstream arch,aux;
    arch.open("usuarios.txt");
    aux.open("temp.txt", ios::app);
    string s;

    arch.seekg(0);
    for (int i=0;i<cuentas[index].direccion;i+=108) {
        arch.seekg(i);
        getline(arch,s);
        aux<<s<<endl;
    }

    for (int i=cuentas[index].direccion+108;i<tama*108;i+=108) {
        arch.seekg(i);
        getline(arch,s);
        aux<<s<<endl;
    }

    arch.close();
    aux.close();

    remove("usuarios.txt");
    rename("temp.txt","usuarios.txt");

    actualizar();
}

void Indice::actualizar()
{
    delete[] cuentas;
    int tam=0;
    string s;

    ifstream fin;
    fin.open("usuarios.txt",ios::ate);

//    getline(fin,s);
//    while (!fin.eof()) {
//        tam++;
//        getline(fin,s);
//    }
//    fin.close();

    tam= int(fin.tellg())/108;            //tamaño del archivo entre el tamaño de cada registro para saber el numero de registros
    fin.close();

    cuentas = new Referencia[tam];
    tama=tam;
    if(tam==0){
        return;
    }
    fin.open("usuarios.txt");
    int nrr=0,dir=int(fin.tellg());
    getline(fin,s);
    while (!fin.eof()) {
        Referencia aux;
        for (size_t i=61;i>41;i--) {
            if(s.at(i)!=' '){
               aux.llave_primaria=s.substr(42,i+1-42);
               aux.direccion=dir;

               if(s.at(84)=='0')
                   aux.bloqueado=0;
               else
                   aux.bloqueado=1;

               cuentas[nrr++]=aux;
               break;
            }
        }
        dir=int(s.size()+2+size_t(dir));
        getline(fin,s);
    }
    ordenar_indice();
}

string Referencia::getLlave_primaria() const
{
    return llave_primaria;
}

bool Referencia::getBloqueado() const
{
    return bloqueado;
}

void Referencia::setBloqueado(bool value)
{
    bloqueado = value;
}

void Referencia::setLlave_primaria(const string &value)
{
    llave_primaria = value;
}

Referencia::Referencia()
{

}

int Referencia::getDireccion() const
{
    return direccion;
}
