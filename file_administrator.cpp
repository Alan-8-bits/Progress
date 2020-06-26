#include "file_administrator.h"

File_Administrator::File_Administrator()
{

}

void File_Administrator::respaldar_usuario(User usuario)
{
    fstream fout;
    fout.open("usuarios.txt", ios::app);
    string aux;
    for (int i=0;i<20-int(usuario.getNombre().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<usuario.getNombre().substr(0,20)<<aux<<'|';
    aux.clear();
    for (int i=0;i<20-int(usuario.getCorreo().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<usuario.getCorreo().substr(0,20)<<aux<<'|';
    aux.clear();
    for (int i=0;i<20-int(usuario.getUsername().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<usuario.getUsername().substr(0,20)<<aux<<'|';
    aux.clear();
    for (int i=0;i<20-int(usuario.getPassword().size());i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<usuario.getPassword().substr(0,20)<<aux<<'|';
    fout<<'0'<<'|';
    aux.clear();
    int count = 0,n=usuario.getDireccion_personaje();
    while (n > 0) {
        n = n / 10;
        ++count;
    }
    if(n==-1)
        count=2;
    for (int i=0;i<20-count;i++) {
        aux.insert(aux.end(),' ');
    }
    fout<<usuario.getDireccion_personaje()<<aux<<endl;

    fout.close();
}

Lista_doble_ligada<User> File_Administrator::recuperar_usuarios()
{
    Lista_doble_ligada<User> usuarios;

    ifstream fin;
    fin.open("usuarios.txt");
    if (fin.is_open()){
        string s;
        getline(fin,s);
        while(!fin.eof()){
            User u;
            size_t nom=0,cor=0,us=0;
            for (size_t i=0;i<s.size();i++) {
                if(s.at(i)=='|'){
                    nom=i;
                    u.setNombre(s.substr(0,nom));
                    break;
                }
            }
            for (size_t i=nom+1;i<s.size();i++) {
                if(s.at(i)=='|'){
                    cor=i;
                    u.setCorreo(s.substr(nom+1,cor-nom-1));
                    break;
                }
            }
            for (size_t i=cor+1;i<s.size();i++) {
                if(s.at(i)=='|'){
                    us=i;
                    u.setUsername(s.substr(cor+1,us-cor-1));
                    break;
                }
            }
            u.setPassword(s.substr(us+1,s.size()-us-1));

            usuarios.push_back(u);
            getline(fin,s);
        }
    }
    else {
        cout<<"No se ha encontrado ningun archivo de Usuarios."<<endl<<endl;
    }
    fin.close();
    return usuarios;
}

void File_Administrator::respaldar_personaje(Character personaje,int &num_per,int nrr,string destino,Lista_doble_ligada<ElemDiccionario> &diccionario,string cuenta)
{
    int total_per=tamano_total_personaje(personaje);
    fstream fout;

    if(nrr!=-1)
        elimina_personaje(nrr,num_per,diccionario,cuenta);

//    if(num_per==0)
//        fout.open(destino, ios::binary  | fstream::out);
//    else{
//        fout.open(destino, ios::binary  | ios::out |ios::in );
//    }
    fout.open(destino,ios::binary|ios::out|ios::in);

    fout.seekg(0,ios::end);
    int calculator=int(fout.tellg());

        if(calculator==4||calculator==0){
            num_per++;
            fout.seekp(0,ios::beg);
            fout.write(reinterpret_cast<char*>(&num_per),sizeof(int));            //Numero de personajes
        }
        else {
            int tamano;
            fout.seekg(0,ios::end);
            tamano=int(fout.tellg());
            num_per++;
            fout.seekp(0,ios::beg);
            fout.write(reinterpret_cast<char*>(&num_per),sizeof(int));
            fout.seekp(tamano,ios::beg);
        }

        int pos=int(fout.tellp());                                            // HEY1


    fout.write(reinterpret_cast<char*>(&total_per),sizeof(int));             //Tamaño total personaje

    int dim = int(personaje.nombre.length());       //Nombre
    const char* cP = personaje.nombre.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    dim=int(personaje.sexo.length());           //Sexo
    cP = personaje.sexo.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    dim=int(personaje.team.length());           //Team
    cP = personaje.team.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    fout.write(reinterpret_cast<char*>(&personaje.experiencia),sizeof(int));         //Experiencia
    fout.write(reinterpret_cast<char*>(&personaje.vida),sizeof(int));               //Vida
    fout.write(reinterpret_cast<char*>(&personaje.dinero),sizeof(int));                //Dinero

    dim=int(personaje.nivel.length());           //Nivel
    cP = personaje.nivel.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    fout.write(reinterpret_cast<char*>(&personaje.habilidad_acertar),sizeof(int));         //Habilidad Acertar
    fout.write(reinterpret_cast<char*>(&personaje.habilidad_critico),sizeof(int));         //Habilidad Critico

    fout.write(reinterpret_cast<char*>(&personaje.historial.asesinatos),sizeof(int));        //Hitorial Asesinatos
    fout.write(reinterpret_cast<char*>(&personaje.historial.misiones_completadas),sizeof(int));      //Hitorial Misiones

    dim=personaje.inventario.armas.size();              //Numero de Armas
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));

    for (int i=0;i<personaje.inventario.armas.size();i++) {
        dim=int(personaje.inventario.armas.at(i)->nombre.length());         //Arma Nombre
        cP = personaje.inventario.armas.at(i)->nombre.c_str();
        fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
        fout.write(cP,dim);

        fout.write(reinterpret_cast<char*>(&personaje.inventario.armas.at(i)->danio),sizeof(int));       //Arma Daño
        fout.write(reinterpret_cast<char*>(&personaje.inventario.armas.at(i)->cadencia),sizeof(int));       //Arma Cadencia

        dim=int(personaje.inventario.armas.at(i)->canion.nombre.length());          //Arma Cañon
        cP = personaje.inventario.armas.at(i)->canion.nombre.c_str();
        fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
        fout.write(cP,dim);

        dim=int(personaje.inventario.armas.at(i)->canion.tipo.length());      //Arma Tipo
        cP = personaje.inventario.armas.at(i)->canion.tipo.c_str();
        fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
        fout.write(cP,dim);
    }

    dim=personaje.inventario.objetos.size();                    //Numero de objetos
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));

    for (int i=0;i<personaje.inventario.objetos.size();i++) {
        dim=int(personaje.inventario.objetos.at(i)->nombre.length());       //Objeto Nombre
        cP = personaje.inventario.objetos.at(i)->nombre.c_str();
        fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
        fout.write(cP,dim);

        dim=int(personaje.inventario.objetos.at(i)->tipo.length());     //Objeto Tipo
        cP = personaje.inventario.objetos.at(i)->tipo.c_str();
        fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
        fout.write(cP,dim);

        fout.write(reinterpret_cast<char*>(&personaje.inventario.objetos.at(i)->nivel),sizeof(int));     //Objeto nivel
    }

    dim=int(personaje.blindaje.nombre.length());                //Blindaje Nombre
    cP = personaje.blindaje.nombre.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    fout.write(reinterpret_cast<char*>(&personaje.blindaje.nivel),sizeof(int));          //Blindaje nivel

    dim=int(personaje.primaria.nombre.length());                //Primaria Nombre
    cP = personaje.primaria.nombre.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    fout.write(reinterpret_cast<char*>(&personaje.primaria.danio),sizeof(int));          //Primaria Daño
    fout.write(reinterpret_cast<char*>(&personaje.primaria.cadencia),sizeof(int));       //Primaria Cadencia

    dim=int(personaje.primaria.canion.nombre.length());             //Primaria Cañon
    cP = personaje.primaria.canion.nombre.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    dim=int(personaje.primaria.canion.tipo.length());             //Primaria Tambor
    cP = personaje.primaria.canion.tipo.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    dim=int(personaje.secundaria.nombre.length());          //Secundaria Nombre
    cP = personaje.secundaria.nombre.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    fout.write(reinterpret_cast<char*>(&personaje.secundaria.danio),sizeof(int));        //Secundaria daño
    fout.write(reinterpret_cast<char*>(&personaje.secundaria.cadencia),sizeof(int));     //Secundaria cadencia

    dim=int(personaje.secundaria.canion.nombre.length());               //Secundaria cañon
    cP = personaje.secundaria.canion.nombre.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    dim=int(personaje.secundaria.canion.tipo.length());           //Secundaria Tambor
    cP = personaje.secundaria.canion.tipo.c_str();
    fout.write(reinterpret_cast<char*>(&dim),sizeof(int));
    fout.write(cP,dim);

    //---------------------------------------------------------------------HEY2

    ElemDiccionario* elemDiccionario = nullptr;
    for (int i=0;i<diccionario.size();i++) {
        if(diccionario.at(i)->getLlaveSec()==cuenta){
            elemDiccionario=diccionario.at(i);break;
        }
    }
    int posInv;

    if(elemDiccionario==nullptr)
        posInv=-1;
    else
        posInv= elemDiccionario->getPos();

    fout.write((char*)&posInv, sizeof (int));
    if (elemDiccionario != nullptr){
        elemDiccionario->setPos(pos);
    }
    else {
        ElemDiccionario e(cuenta,pos);
        diccionario.push_back(e);
    }

    fout.close();
}

int File_Administrator::num_personajes(string cuenta,Lista_doble_ligada<ElemDiccionario> &diccionario)
{
    ifstream fin;
    ElemDiccionario* e = nullptr;
    for (int i=0;i<diccionario.size();i++) {
        if(diccionario.at(i)->getLlaveSec()==cuenta)
            e=diccionario.at(i);
    }
    if (e == nullptr)
        return 0;

    int pos = e->getPos(),num=0,auxtam=0;
    fin.open("Personajes.bin", ios::binary);
    fin.seekg(pos,ios::beg);
    fin.read((char*)&auxtam,sizeof(int));

    fin.seekg(auxtam-2*int(sizeof (int)),ios::cur);
    fin.read((char*)&pos,sizeof(int));
    while(pos != -1){
        num++;
        fin.seekg(pos,ios::beg);
        fin.read((char*)&auxtam,sizeof(int));
        fin.seekg(auxtam-2*int(sizeof (int)),ios::cur);
        fin.read((char*)&pos,sizeof(int));
    }
    num++;
    fin.close();
    return num;

//  -----------------------------------------------------------------------------------
//    ifstream fin;

//        int num_per;

//        fin.open("Personajes.bin", ios::binary);
//        fin.read(reinterpret_cast<char*>(&num_per), sizeof(int));

//        return num_per;
}

int File_Administrator::tamano_total_personaje(Character personaje)
{
    int total=int(sizeof (int))*27;                     //26 HEY
    total+=int(sizeof (char)*personaje.nombre.length());
    total+=int(sizeof (char)*personaje.sexo.length());
    total+=int(sizeof (char)*personaje.team.length());
    total+=int(sizeof (char)*personaje.nivel.length());

    for (int i=0;i<personaje.inventario.armas.size();i++) {
        total+=int(sizeof (int)*5);
        total+=int(sizeof (char)*personaje.inventario.armas.at(i)->nombre.length());
        total+=int(sizeof (char)*personaje.inventario.armas.at(i)->canion.nombre.length());
        total+=int(sizeof (char)*personaje.inventario.armas.at(i)->canion.tipo.length());
    }

    for (int i=0;i<personaje.inventario.objetos.size();i++) {
        total+=int(sizeof (int)*3);
        total+=int(sizeof (char)*personaje.inventario.objetos.at(i)->nombre.length());
        total+=int(sizeof (char)*personaje.inventario.objetos.at(i)->tipo.length());
    }

    total+=int(sizeof (char)*personaje.blindaje.nombre.length());
    total+=int(sizeof (char)*personaje.primaria.nombre.length());
    total+=int(sizeof (char)*personaje.primaria.canion.nombre.length());
    total+=int(sizeof (char)*personaje.primaria.canion.tipo.length());
    total+=int(sizeof (char)*personaje.secundaria.nombre.length());
    total+=int(sizeof (char)*personaje.secundaria.canion.nombre.length());
    total+=int(sizeof (char)*personaje.secundaria.canion.tipo.length());

    return total;
}

void File_Administrator::elimina_personaje(int pos, int &num_per,Lista_doble_ligada<ElemDiccionario>&diccionario,string cuenta)
{
    fstream fin("Personajes.bin",ios::binary|ios::in|ios::out);
//    fstream output("Personajes.bin",ios::binary|ios::app);

    int auxtam=0,posini=0,reference=0;
//    fin.open("Personajes.bin", ios::binary);

    ElemDiccionario* e=nullptr;
    for (int i=0;i<diccionario.size();i++) {
        if(diccionario.at(i)->getLlaveSec()==cuenta)
            e=diccionario.at(i);
    }

    posini=e->getPos();

    fin.seekg(posini,ios::beg);
    fin.read((char*)&auxtam,sizeof(int));
    fin.seekg(posini+auxtam-int(sizeof(int)),ios::beg);
    fin.read((char*)&reference,sizeof(int));

    if(posini==pos){                          //posicion a eliminar es la primera (actualizamos diccionario)
        fin.seekg(posini,ios::beg);
        fin.read((char*)&auxtam,sizeof(int));
        fin.seekg(posini+auxtam-int(sizeof(int)),ios::beg);
        fin.read((char*)&reference,sizeof(int));

        e->setPos(reference);
    }
    else {                                     //si no recorremos el flujo de referencias actualizandolas
        fin.seekg(posini,ios::beg);
        fin.read((char*)&auxtam,sizeof(int));
        int reference_to_change=posini+auxtam-int(sizeof(int));

        fin.seekg(reference_to_change,ios::beg);
        fin.read((char*)&reference,sizeof(int));

        while(reference != -1 && reference!=pos){
            fin.seekg(reference,ios::beg);
            fin.read((char*)&auxtam,sizeof(int));
            reference_to_change=reference+auxtam-int(sizeof(int));
            fin.seekg(reference_to_change,ios::beg);
            fin.read((char*)&reference,sizeof(int));
        }

        if(reference==-1){
            fin.seekg(reference_to_change,ios::beg);
            posini=-1;
            fin.write(reinterpret_cast<char*>(&posini),sizeof (int));
        }
        else {
            fin.seekg(reference,ios::beg);
            fin.read((char*)&auxtam,sizeof(int));
            fin.seekg(reference+auxtam-int(sizeof(int)),ios::beg);
            fin.read((char*)&reference,sizeof(int));
            fin.seekg(reference_to_change,ios::beg);
            fin.write(reinterpret_cast<char*>(&reference),sizeof (int));
        }
    }



    // actualizar referencias de los demas registros no relacionados a esta cuenta

    int tam_borrado=0,posaux=sizeof (int);
    fin.seekg(pos,ios::beg);
    fin.read((char*)&tam_borrado,sizeof (int));

    fin.seekg(0,ios::end);
    int compare=int(fin.tellg());
    while (posaux<compare) {
        fin.seekg(posaux,ios::beg);
        fin.read((char*)&auxtam,sizeof (int));
        fin.seekg(posaux+auxtam-int(sizeof(int)),ios::beg);
        fin.read((char*)&posini,sizeof (int));
        if(posini>pos){
            fin.seekg(posaux+auxtam-int(sizeof(int)),ios::beg);
            int niu=posini-tam_borrado;
            fin.write(reinterpret_cast<char*>(&niu),sizeof (int));
        }
        posaux+=auxtam;
    }

    for (int i=0;i<diccionario.size();i++) {
        if(diccionario.at(i)->getPos()>pos){
            diccionario.at(i)->setPos(diccionario.at(i)->getPos()-tam_borrado);
        }
    }

    // eliminacion fisica
    string copy1(pos-int(sizeof(int)),' ');
    ofstream output;
    output.open("Temporary.bin",ios::binary|ios::app);
    output.seekp(0,ios::beg);
    fin.seekg(0,ios::beg);

    fin.read((char*)&auxtam,sizeof(int));
    auxtam--;

    output.write(reinterpret_cast<char*>(&auxtam),sizeof (int));

    fin.read(&copy1[0],pos-int(sizeof(int)));
    fin.read((char*)&auxtam,sizeof(int));

    output<<copy1;

    fin.seekg(0,ios::end);
    int posfinal=int(fin.tellg()),pos2=pos+auxtam;
    string copy2(posfinal-pos2, ' ');

    fin.seekg(pos2,ios::beg);
    fin.read(&copy2[0],posfinal-pos2);

    output<<copy2;

    fin.close();
    output.close();

    num_per--;

    remove("Personajes.bin");
    rename("Temporary.bin","Personajes.bin");

//    int aux=0;
//    for (int i=0;i<pos;i++) {
//        respaldar_personaje(recupera_personaje(i,"Personajes.bin"),aux,-1,"Temporal.bin",diccionario,cuenta);
//    }
//    for (int i=pos+1;i<num_per;i++) {
//        respaldar_personaje(recupera_personaje(i,"Personajes.bin"),aux,-1,"Temporal.bin",diccionario,cuenta);
//    }
//    remove("Personajes.bin");
//    rename("Temporal.bin","Personajes.bin");
    //    num_per--;
}

Lista_doble_ligada<ElemDiccionario> File_Administrator::construir_diccionario(Indice indice)
{
    fstream fin;
    fin.open("usuarios.txt");
    Lista_doble_ligada<ElemDiccionario> diccionario;

    for (int i=0;i<indice.size();i++) {
        ElemDiccionario aux;
        aux.setLlaveSec(indice.at(i).getLlave_primaria());
        fin.seekg(indice.at(i).getDireccion(),ios::beg);
        string s;
        getline(fin,s);
        stringstream ss(s.substr(86,s.size()-86));
        int dir;
        ss>>dir;
        aux.setPos(dir);
        diccionario.push_back(aux);
    }

    return diccionario;
}

void File_Administrator::mostrar_personajes_de_usuario(string cuenta, Lista_doble_ligada<ElemDiccionario> &diccionario)
{
    ifstream fin;
    fin.open("Personajes.bin", ios::binary);

    ElemDiccionario* e=nullptr;
    for (int i=0;i<diccionario.size();i++) {
        if(diccionario.at(i)->getLlaveSec()==cuenta)
            e=diccionario.at(i);
    }

    int actual=e->getPos(),tamaux;

    cout<<"Personajes: "<<endl;
    cout<<"Direccion:\tNombre:\t  Siguiente:"<<endl;
    while (actual!=-1) {
        Character aux=load_character(actual);
        int refaux=actual;
        fin.seekg(actual,ios::beg);
        fin.read((char*)&tamaux,sizeof(int));
        fin.seekg(actual+tamaux-int(sizeof (int)),ios::beg);
        fin.read((char*)&actual,sizeof(int));
        cout<<"("<<refaux<<")\t-\t"<<aux.getNombre()<<"->\t\t"<<actual<<endl;
    }

}

string File_Administrator::read_string(ifstream &archivo)
{
    int dim;
    string ret;
    archivo.read(reinterpret_cast<char*>(&dim), sizeof(int));
    char cad_c[dim+1];
    archivo.read(cad_c, dim);
    cad_c[dim] = '\0';
    ret=cad_c;

    return ret;
}

Character File_Administrator::load_character(int inicial)
{
    Character aux;
    int tamano_total;

    ifstream fin;
    fin.open("Personajes.bin", ios::binary | ios::in |ios::out  );

    fin.seekg(inicial,ios::beg);
    fin.read(reinterpret_cast<char*>(&tamano_total), sizeof(int));

    aux.nombre=read_string(fin);
    aux.sexo=read_string(fin);
    aux.team=read_string(fin);
    fin.read(reinterpret_cast<char*>(&aux.experiencia), sizeof(int));
    fin.read(reinterpret_cast<char*>(&aux.vida), sizeof(int));
    fin.read(reinterpret_cast<char*>(&aux.dinero), sizeof(int));
    aux.nivel=read_string(fin);
    fin.read(reinterpret_cast<char*>(&aux.habilidad_acertar), sizeof(int));
    fin.read(reinterpret_cast<char*>(&aux.habilidad_critico), sizeof(int));
    fin.read(reinterpret_cast<char*>(&aux.historial.asesinatos), sizeof(int));
    fin.read(reinterpret_cast<char*>(&aux.historial.misiones_completadas), sizeof(int));

    int num_armas;
    fin.read(reinterpret_cast<char*>(&num_armas), sizeof(int));
    for (int i=0;i<num_armas;i++) {
        int danio,cadencia;
        string nombre,canion,tambor;

        nombre=read_string(fin);
        fin.read(reinterpret_cast<char*>(&danio), sizeof(int));
        fin.read(reinterpret_cast<char*>(&cadencia), sizeof(int));
        canion=read_string(fin);
        tambor=read_string(fin);

        Arma arm(nombre,danio,cadencia,canion,tambor);
        aux.inventario.armas.push_back(arm);
    }

    int num_objetos;
    fin.read(reinterpret_cast<char*>(&num_objetos), sizeof(int));
    for (int i=0;i<num_objetos;i++) {
        Objeto obj;
        obj.nombre=read_string(fin);
        obj.tipo=read_string(fin);
        fin.read(reinterpret_cast<char*>(&obj.nivel), sizeof(int));

        aux.inventario.objetos.push_back(obj);
    }

    Objeto blin;
    blin.nombre=read_string(fin);
    blin.tipo="Blindaje";
    fin.read(reinterpret_cast<char*>(&blin.nivel), sizeof(int));

    aux.blindaje=blin;

    int danio,cadencia;
    string nombre,canion,tambor;
    nombre=read_string(fin);
    fin.read(reinterpret_cast<char*>(&danio), sizeof(int));
    fin.read(reinterpret_cast<char*>(&cadencia), sizeof(int));
    canion=read_string(fin);
    tambor=read_string(fin);
    Arma arm(nombre,danio,cadencia,canion,tambor);

    aux.primaria=arm;

    nombre=read_string(fin);
    fin.read(reinterpret_cast<char*>(&danio), sizeof(int));
    fin.read(reinterpret_cast<char*>(&cadencia), sizeof(int));
    canion=read_string(fin);
    tambor=read_string(fin);
    Arma arm2(nombre,danio,cadencia,canion,tambor);

    aux.secundaria=arm2;

    return aux;
}

void File_Administrator::save_character(Character *obj, Lista_doble_ligada<ElemDiccionario> &diccionario, string cuenta)
{
    fstream fout;
    fout.open("Personajes.bin",ios::binary|ios::app);
    fout.seekp(0,ios::end);
    int pos = int(fout.tellp());
    fout.write((char*)obj, sizeof (Character));
    //Indice ind(obj->getEntero(),pos);

    ElemDiccionario* elemDiccionario = nullptr;
    for (int i=0;i<diccionario.size();i++) {
        if(diccionario.at(i)->getLlaveSec()==cuenta){
            elemDiccionario=diccionario.at(i);
            break;
        }
    }
    int posInv;
    if(elemDiccionario==nullptr)
        posInv = -1;
    else
        posInv = elemDiccionario->getPos();

    fout.write((char*)&posInv, sizeof (int));
    if (posInv != -1){
        elemDiccionario->setPos(pos);
    }
    else {
        ElemDiccionario e(cuenta,pos);
        diccionario.push_back(e);

    }
    fout.close();
}

Grafo<Location> File_Administrator::recupera_grafo_global(string nombre_archivo)
{
    ifstream fin;
    fin.open(nombre_archivo);
    Grafo<Location> global;
    if (fin.is_open()){
        string aux;
        getline(fin,aux);

        while (aux!="Aristas") {                        //Agrego los vertices
            if(aux.size()>3){
                Location locacion;
                size_t band=0;
                string array[4];

                for (size_t i=0,x=0;i<aux.size();i++) {
                    if(aux.at(i)=='|'){
                        array[x++]=(aux.substr(band,i-band));
                        band=i+1;
                    }
                }

                locacion.setNombre(array[0]);
                locacion.setTipo(array[1]);
                locacion.setDificultad(stoi(array[2]));
                locacion.setNivel_tienda(stoi(array[3]));

                global.insertaVertice(locacion);
            }
            getline(fin,aux);
        }

        getline(fin,aux);           //Ignoro el mensaje de "Aristas"

        while (!fin.eof() && aux!="Grafo") {                             //Agrego las aristas
            if(aux.size()>3){
                size_t band=0;
                string array[3];

                for (size_t i=0,x=0;i<aux.size();i++) {
                    if(aux.at(i)=='|'){
                        array[x++]=(aux.substr(band,i-band));
                        band=i+1;
                    }
                }
                size_t nrr1=0,nrr2=0;

                for (size_t i=0;i< size_t(global.size());i++) {
                    if(global.at(i).getNombre()==array[0])
                        nrr1=i;
                    if(global.at(i).getNombre()==array[1])
                        nrr2=i;
                }
                global.InsertaArista(global.at(nrr1),global.at(nrr2),stoi(array[2]));
            }
            getline(fin,aux);
        }
    }
    else {
        cout<<"No se ha encontrado el acrhivo del Grafo Global."<<endl<<endl;
    }
    fin.close();
    return global;
}

Lista_doble_ligada<Grafo<Location> > File_Administrator::recupera_grafos()
{
    ifstream fin;
    fin.open("Grafos.txt");
    Lista_doble_ligada<Grafo<Location>> grafos;
    if (fin.is_open()){
        string aux;
        int actual_pos;
        getline(fin,aux);

        while (!fin.eof()) {
            Grafo<Location> global;

            global.setId(aux.substr(6,aux.size()-6));
            getline(fin,aux);
            actual_pos=stoi(aux);
            getline(fin,aux);

            while (aux!="Aristas") {                        //Agrego los vertices
                if(aux.size()>3){
                    Location locacion;
                    size_t band=0;
                    string array[4];

                    for (size_t i=0,x=0;i<aux.size();i++) {
                        if(aux.at(i)=='|'){
                            array[x++]=(aux.substr(band,i-band));
                            band=i+1;
                        }
                    }

                    locacion.setNombre(array[0]);
                    locacion.setTipo(array[1]);
                    locacion.setDificultad(stoi(array[2]));
                    locacion.setNivel_tienda(stoi(array[3]));

                    global.insertaVertice(locacion);
                }
                getline(fin,aux);
            }

            getline(fin,aux);           //Ignoro el mensaje de "Aristas"


            while (!fin.eof() && aux.substr(0,5)!="Grafo") {                             //Agrego las aristas
                if(aux.size()>3){
                    size_t band=0;
                    string array[3];

                    for (size_t i=0,x=0;i<aux.size();i++) {
                        if(aux.at(i)=='|'){
                            array[x++]=(aux.substr(band,i-band));
                            band=i+1;
                        }
                    }
                    size_t nrr1=0,nrr2=0;

                    for (size_t i=0;i< size_t(global.size());i++) {
                        if(global.at(i).getNombre()==array[0])
                            nrr1=i;
                        if(global.at(i).getNombre()==array[1])
                            nrr2=i;
                    }
                    global.InsertaArista(global.at(nrr1),global.at(nrr2),stoi(array[2]));
                }
                getline(fin,aux);
            }

            global.setPosActual(actual_pos);
            grafos.push_back(global);
        }
    }
    else {
        cout<<"No se ha encontrado ningun archivo de los grafos."<<endl<<endl;
    }
    fin.close();
    return grafos;
}

Grafo<Location> File_Administrator::recupera_grafo(int pos)
{
    ifstream fin;
    fin.open("Grafos.txt",ios::in);
    string aux;
    int actual_pos;
    Grafo<Location> global;

    fin.seekg(pos,ios::beg);
    getline(fin,aux);
    cout<<aux<<endl;

    global.setId(aux.substr(6,aux.size()-6));
    getline(fin,aux);
    actual_pos=stoi(aux);
    getline(fin,aux);

    while (aux!="Aristas") {                        //Agrego los vertices
        if(aux.size()>3){
            Location locacion;
            size_t band=0;
            string array[4];

            for (size_t i=0,x=0;i<aux.size();i++) {
                if(aux.at(i)=='|'){
                    array[x++]=(aux.substr(band,i-band));
                    band=i+1;
                }
            }

            locacion.setNombre(array[0]);
            locacion.setTipo(array[1]);
            locacion.setDificultad(stoi(array[2]));
            locacion.setNivel_tienda(stoi(array[3]));

            global.insertaVertice(locacion);
        }
        getline(fin,aux);
    }

    getline(fin,aux);           //Ignoro el mensaje de "Aristas"


    while (!fin.eof() && aux.substr(0,5)!="Grafo") {                             //Agrego las aristas
        if(aux.size()>3){
            size_t band=0;
            string array[3];

            for (size_t i=0,x=0;i<aux.size();i++) {
                if(aux.at(i)=='|'){
                    array[x++]=(aux.substr(band,i-band));
                    band=i+1;
                }
            }
            size_t nrr1=0,nrr2=0;

            for (size_t i=0;i< size_t(global.size());i++) {
                if(global.at(i).getNombre()==array[0])
                    nrr1=i;
                if(global.at(i).getNombre()==array[1])
                    nrr2=i;
            }
            global.InsertaArista(global.at(nrr1),global.at(nrr2),stoi(array[2]));
        }
        getline(fin,aux);
    }

    fin.close();

    global.setPosActual(actual_pos);

    return global;
}

void File_Administrator::respalda_grafos(Lista_doble_ligada<Grafo<Location> > grafos)
{
    fstream fout;
    fout.open("Grafos.txt", ios::out);

    for (int i=0;i<grafos.size();i++) {

        int actual_pos=0;
        for (int j=0;j<grafos.at(i)->size();j++) {
            if(grafos.at(i)->getPosActual().getNombre()==grafos.at(i)->at(size_t(j)).getNombre()){
                actual_pos=j;
                break;
            }
        }

        fout<<"Grafo "<<grafos.at(i)->getId()<<endl;
        fout<<actual_pos<<endl;

        for (int j=0;j<grafos.at(i)->size();j++) {
            fout<<grafos.at(i)->at(size_t(j)).getNombre()<<'|'
               <<grafos.at(i)->at(size_t(j)).getTipo()<<'|'<<grafos.at(i)->at(size_t(j)).getDificultad()
              <<'|'<<grafos.at(i)->at(size_t(j)).getNivel_tienda()<<'|'<<endl;
        }
        fout<<"Aristas"<<endl;
        for (int j=0;j<grafos.at(i)->size();j++) {
            for (int x=0;x<grafos.at(i)->vertices.at(j)->aristas.size();x++) {
                fout<<grafos.at(i)->at(size_t(j)).getNombre()<<'|'<<grafos.at(i)->vertices.at(j)->aristas.at(x)->destino->dato.getNombre()<<'|'<<grafos.at(i)->vertices.at(j)->aristas.at(x)->pond<<'|'<<endl;
            }
        }
    }
    fout.close();
}

void File_Administrator::respalda_grafo(Grafo<Location> grafo, int pos_old, Lista_doble_ligada<ElemDiccionario>& indie)
{
    if(pos_old!=-1){
        elimina_grafo(pos_old,indie);
    }
    fstream fout;

    fout.open("Grafos.txt", ios::out|ios::app);

    fout.seekp(0,ios::end);

    for (int i=0;i<indie.size();i++) {
        if(indie.at(i)->getLlaveSec()==grafo.getId()){
            indie.at(i)->setPos(int(fout.tellp()));
            break;
        }
    }

    int actual_pos=0;
    for (int j=0;j<grafo.size();j++) {
        if(grafo.getPosActual().getNombre()==grafo.at(size_t(j)).getNombre()){
            actual_pos=j;
            break;
        }
    }

    fout<<"Grafo "<<grafo.getId()<<endl;
    fout<<actual_pos<<endl;

    for (int j=0;j<grafo.size();j++) {
        fout<<grafo.at(size_t(j)).getNombre()<<'|'
           <<grafo.at(size_t(j)).getTipo()<<'|'<<grafo.at(size_t(j)).getDificultad()
          <<'|'<<grafo.at(size_t(j)).getNivel_tienda()<<'|'<<endl;
    }
    fout<<"Aristas"<<endl;
    for (int j=0;j<grafo.size();j++) {
        for (int x=0;x<grafo.vertices.at(j)->aristas.size();x++) {
            fout<<grafo.at(size_t(j)).getNombre()<<'|'<<grafo.vertices.at(j)->aristas.at(x)->destino->dato.getNombre()<<'|'<<grafo.vertices.at(j)->aristas.at(x)->pond<<'|'<<endl;
        }
    }
    fout.close();

    indie=carga_indice_grafos();
}

void File_Administrator::elimina_grafo(int pos,Lista_doble_ligada<ElemDiccionario>& indie)
{
    ifstream final;
    final.open("Grafos.txt",ios::in|ios::ate);
    string aux;
    int final_archie=0,hidden=0;

    final_archie=int(final.tellg());
    final.close();

    ofstream output;

    output.open("Temp.txt", ios::out);
    final.open("Grafos.txt",ios::in);
    final.seekg(0,ios::beg);

    while (hidden!=pos) {
        getline(final,aux);
        hidden+=aux.size()+2;
        output<<aux<<endl;
    }

    getline(final,aux);
    getline(final,aux);
    while (!final.eof() && aux.substr(0,5)!="Grafo") {
        getline(final,aux);
    }

    if(!final.eof()){
        output<<aux<<endl;
    }
    while (!final.eof()) {
        getline(final,aux);
        if(!final.eof())
            output<<aux<<endl;
    }

    final.close();
    output.close();

    remove("Grafos.txt");
    rename("Temp.txt","Grafos.txt");

}

Lista_doble_ligada<ElemDiccionario> File_Administrator::carga_indice_grafos()
{
    Lista_doble_ligada<ElemDiccionario> ret;

        ifstream fin;
        int hidden=0;
        fin.open("Grafos.txt",ios::in);
        if (fin.is_open()){
            string aux;
            int actual_pos=hidden;
            getline(fin,aux);
            hidden+=aux.size()+2;

            while (!fin.eof()) {
                ElemDiccionario elem;
                elem.setLlaveSec(aux.substr(6,aux.size()-6));
                elem.setPos(actual_pos);

                getline(fin,aux);
                hidden+=aux.size()+2;
                while (!fin.eof() && aux.substr(0,5)!="Grafo") {                             //Agrego las aristas
                    actual_pos=hidden;
                    getline(fin,aux);
                    hidden+=aux.size()+2;
                }

                ret.push_back(elem);
            }
        }
        fin.close();

    return ret;
}

Character File_Administrator::recupera_oponente(int mision)
{
    ifstream fin;
    fin.open("rivales.txt");
    Character rival;
    if (fin.is_open()){
        string s;
        size_t aux=0,aux2=0;
        getline(fin,s);
        for (int i=0;i<mision;i++) {
            getline(fin,s);
        }
        for (size_t i=0;i<s.size();i++) {
            if(s.at(i)=='|'){
                aux2=i;
                rival.nombre=(s.substr(aux,aux2-aux));
                break;
            }
        }
        aux=aux2+1;
        for (size_t i=aux;i<s.size();i++) {
            if(s.at(i)=='|'){
                aux2=i;
                rival.dinero=stoi(s.substr(aux,aux2-aux));
                break;
            }
        }
        aux=aux2+1;
        for (size_t i=aux;i<s.size();i++) {
            if(s.at(i)=='|'){
                aux2=i;
                rival.habilidad_acertar=stoi(s.substr(aux,aux2-aux));
                break;
            }
        }
       aux=aux2+1;
        for (size_t i=aux;i<s.size();i++) {
            if(s.at(i)=='|'){
                aux2=i;
                rival.habilidad_critico=stoi(s.substr(aux,aux2-aux));
                break;
            }
        }
        int iteraciones=0;
        aux=aux2+1;
         for (size_t i=aux;i<s.size();i++) {
             if(s.at(i)=='|'){
                 aux2=i;
                 iteraciones=stoi(s.substr(aux,aux2-aux));
                 break;
             }
         }
         for (int i=0;i<iteraciones;i++) {
             Objeto obj;
             aux=aux2+1;
              for (size_t i=aux;i<s.size();i++) {
                  if(s.at(i)=='|'){
                      aux2=i;
                      obj.nombre=(s.substr(aux,aux2-aux));
                      break;
                  }
              }
              aux=aux2+1;
               for (size_t i=aux;i<s.size();i++) {
                   if(s.at(i)=='|'){
                       aux2=i;
                       obj.tipo=(s.substr(aux,aux2-aux));
                       break;
                   }
               }
               aux=aux2+1;
                for (size_t i=aux;i<s.size();i++) {
                    if(s.at(i)=='|'){
                        aux2=i;
                        obj.nivel=stoi(s.substr(aux,aux2-aux));
                        break;
                    }
                }
                rival.inventario.objetos.push_back(obj);
         }
         aux=aux2+1;
          for (size_t i=aux;i<s.size();i++) {
              if(s.at(i)=='|'){
                  aux2=i;
                  rival.blindaje.nombre=(s.substr(aux,aux2-aux));
                  break;
              }
          }
          aux=aux2+1;
           for (size_t i=aux;i<s.size();i++) {
               if(s.at(i)=='|'){
                   aux2=i;
                   rival.blindaje.nivel=stoi(s.substr(aux,aux2-aux));
                   break;
               }
           }

           string nom,can,tam;
           int dan=0,cad=0;
           aux=aux2+1;
            for (size_t i=aux;i<s.size();i++) {
                if(s.at(i)=='|'){
                    aux2=i;
                    nom=(s.substr(aux,aux2-aux));
                    break;
                }
            }
            aux=aux2+1;
            for (size_t i=aux;i<s.size();i++) {
                if(s.at(i)=='|'){
                    aux2=i;
                    dan=stoi(s.substr(aux,aux2-aux));
                    break;
                }
            }
            aux=aux2+1;
            for (size_t i=aux;i<s.size();i++) {
                if(s.at(i)=='|'){
                    aux2=i;
                    cad=stoi(s.substr(aux,aux2-aux));
                    break;
                }
            }
            aux=aux2+1;
            for (size_t i=aux;i<s.size();i++) {
                if(s.at(i)=='|'){
                    aux2=i;
                    can=(s.substr(aux,aux2-aux));
                    break;
                }
            }
            aux=aux2+1;
            for (size_t i=aux;i<s.size();i++) {
                if(s.at(i)=='|'){
                    aux2=i;
                    tam=(s.substr(aux,aux2-aux));
                    break;
                }
            }
            Arma prim(nom,dan,cad,can,tam);
            rival.primaria=prim;

            aux=aux2+1;
             for (size_t i=aux;i<s.size();i++) {
                 if(s.at(i)=='|'){
                     aux2=i;
                     nom=(s.substr(aux,aux2-aux));
                     break;
                 }
             }
             aux=aux2+1;
             for (size_t i=aux;i<s.size();i++) {
                 if(s.at(i)=='|'){
                     aux2=i;
                     dan=stoi(s.substr(aux,aux2-aux));
                     break;
                 }
             }
             aux=aux2+1;
             for (size_t i=aux;i<s.size();i++) {
                 if(s.at(i)=='|'){
                     aux2=i;
                     cad=stoi(s.substr(aux,aux2-aux));
                     break;
                 }
             }
             aux=aux2+1;
             for (size_t i=aux;i<s.size();i++) {
                 if(s.at(i)=='|'){
                     aux2=i;
                     can=(s.substr(aux,aux2-aux));
                     break;
                 }
             }
             aux=aux2+1;
             for (size_t i=aux;i<s.size();i++) {
                 if(s.at(i)=='|'){
                     aux2=i;
                     tam=(s.substr(aux,aux2-aux));
                     break;
                 }
             }
             Arma sec(nom,dan,cad,can,tam);
             rival.secundaria=sec;
    }
    else {
        cout<<"No se ha encontrado ningun archivo de Rivales."<<endl<<endl;
    }
    fin.close();
    return rival;
}
