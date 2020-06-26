#include "menu.h"

Menu::Menu()
{
    //usuarios=administrador_de_archivos.recuperar_usuarios();

    grafo_global=administrador_de_archivos.recupera_grafo_global("Grafo_Global.txt");
    grafos=administrador_de_archivos.recupera_grafos();
    indice.actualizar();
    diccionario=administrador_de_archivos.construir_diccionario(indice);
    indice_grafos=administrador_de_archivos.carga_indice_grafos();
}

void Menu::principal()
{
    int opc;
    while(true){
        cout<<"1.-Registrar Nuevo Usuario"<<endl;
        cout<<"2.-Acceder"<<endl;
        cout<<"3.-Recuperar"<<endl;
        cout<<"4.-Administracion"<<endl;
        cout<<"5.-Crear N usuarios aleatorios"<<endl;
        cout<<"0.-Salir"<<endl<<endl;
        cin>>opc;
        cin.ignore();
        switch (opc) {
        case 1:{
            agregar_usuario();
            break;
        }
        case 2:{
            if(indice.size()==0){
                cout<<"No hay usuarios registrados"<<endl<<endl;
                break;
            }
            string us,con;
            bool acceso=false;

            cout<<"Ingresa tu Username:"<<endl;
            getline(cin, us);
            cout<<"Ingresa tu Contrasena:"<<endl;
            getline(cin, con);

            int binary=indice.size()/2,max=indice.size(),menor=0;

            while (!acceso) {
                if(us==indice.at(binary).getLlave_primaria()){
                    usuario=indice.getAt(binary);
                    nrr_usuario=binary;
                    if(usuario.getPassword()==con && !indice.at(binary).getBloqueado())
                        acceso=true;
                    break;
                }

                if(binary==menor||binary==max)
                    break;

                if(us<indice.at(binary).getLlave_primaria()){
                    max=binary;
                    binary=(binary-menor)/2;
                }
                else {
                    menor=binary;
                    binary= (max-binary)/2+binary;
                }
            }

//            for (int i=0;i<indice.size();i++) {
//                if(indice.at(i).getUsername()==us && indice.at(i).getPassword()==con){
//                    usuario=indice.at(i);
//                    acceso=true;
//                    break;
//                }
//            }

            if(acceso){
                cout<<endl;
                acceder_usuario();
            }
            else {
                cout<<"El Username y la Contrasena no coinciden o el Usuario esta bloqueado."<<endl<<endl;
            }
            break;
        }
        case 3:{
            string us;
            cout<<"Escribe el Username de el acuenta a recuperar: "<<endl;
            getline(cin,us);

            int binary=indice.size()/2,max=indice.size(),menor=0;
            bool acceso=false;

            while (!acceso) {
                if(us==indice.at(binary).getLlave_primaria()){
                    indice.bloquear_temporalmente(binary,false);
                    indice.modificarAt(binary,indice.getAt(binary));
                    acceso=true;
                    break;
                }

                if(binary==menor||binary==max)
                    break;

                if(us<indice.at(binary).getLlave_primaria()){
                    max=binary;
                    binary=(binary-menor)/2;
                }
                else {
                    menor=binary;
                    binary= (max-binary)/2+binary;
                }
            }

            if(acceso){
                cout<<"Se ha recuperado tu cuenta."<<endl<<endl;
            }
            else {
                cout<<"No se encontro ninguna cuenta con ese username o ya estaba desbloqueada."<<endl<<endl;
            }

            break;
        }
        case 4:{
            cout<<"1.-Mostrar Cuentas"<<endl;
            cout<<"2.-Mostrar Lista invertida"<<endl;
            cout<<"0.-Regresar"<<endl;
            int admin;
            cin>>admin;
            cin.ignore();
            switch (admin) {
            case 1:{
                mostrar_usuarios();
                break;
            }
            case 2:{
                fstream aux;
                aux.open("Personajes.bin", ios::binary |ios::out|ios::in);
                aux.seekg(0,ios::end);
                if(aux.tellg()<=4){
                    cout<<"No hay personajes registrados"<<endl<<endl;
                    break;
                }
                else {
                    string username;
                    cout<<"\nEscribe el username de la cuenta."<<endl;
                    getline(cin,username);
                    bool validator=false;
                    for (int i=0;i<diccionario.size();i++) {
                        if(diccionario.at(i)->getLlaveSec()==username){
                            validator=true;
                        }
                    }
                    if(validator){
                        administrador_de_archivos.mostrar_personajes_de_usuario(username,diccionario);
                        cout<<endl;
                    }
                    else {
                        cout<<"El username que escribiste no existe."<<endl<<endl;
                    }
                }
                aux.close();

                break;
            }
            case 0:{
                cout<<endl;
                break;
            }
            default:{
                cout<<"Opcion no valida"<<endl<<endl;
                break;
            }
            }


            break;
        }
        case 5:{
            int num_usu;
            cout<<"Cuantos usuarios quieres crear?"<<endl;
            cin>>num_usu;
            cin.ignore();
            cout<<"Creando usuarios..."<<endl;
            srand(time(NULL));

            for (int i=0;i<num_usu;i++) {

                User u;
                stringstream str;
                int num;
                do{
                    num=1+ rand() % 1000000;
                    str.str("");
                    str<<"Username_"<<num;
                }
                while (!isvalid_name(str.str()));

                u.setUsername(str.str());
                str.str("");
                str<<"Usuario_num_"<<num;
                u.setNombre(str.str());
                str.str("");
                str<<"u"<<num<<"@u"<<num<<".com";
                u.setCorreo(str.str());
                str.str("");
                str<<"contrasena_"<<num;
                u.setPassword(str.str());

                administrador_de_archivos.respaldar_usuario(u);
                indice.actualizar();
            }
            cout<<"Se han creado "<<num_usu<<" usuarios aleatorios."<<endl<<endl;
            break;
        }
        case 0:{
            return;
        }
        default:{
            cout<<"Ingreso una opcion no valida."<<endl<<endl;
            break;
        }
        }
    }
}

void Menu::agregar_usuario()
{
    string str;
    User u;
    cout<<"No puedes usar el simbolo '|' en ningun campo"<<endl;
    do{
        cout<<"Nombre del usuario: ";
        getline(cin,str);
        if(!isvalid_string(str)){
            cout<<"Escribiste el caracter reservado '|' "<<endl;
            char car=0;
            cout<<"Aun quieres registrar un usuario? s/n"<<endl;
            cin>>car;
            cin.ignore();
            if(car=='n'){
                cout<<endl<<endl;
                return;
            }
        }
    }while (!isvalid_string(str));
    u.setNombre(str);
    do {
        cout<<"Correo del usuario: ";
        getline(cin,str);
        if(!isvalid_string(str)){
            cout<<"Escribiste el caracter reservado '|' "<<endl;
        }
        if(!isvalid_mail(str)){
            cout<<"Este correo no es valido."<<endl;
        }
        if(!isvalid_string(str)||!isvalid_mail(str)){
            char car=0;
            cout<<"Aun quieres registrar un usuario? s/n"<<endl;
            cin>>car;
            cin.ignore();
            if(car=='n'){
                cout<<endl<<endl;
                return;
            }
        }
    }while (!isvalid_mail(str)||!isvalid_string(str));
    u.setCorreo(str);
    do{
        cout<<"Username del usuario: ";
        getline(cin,str);
        if(!isvalid_string(str)){
            cout<<"Escribiste el caracter reservado '|' "<<endl;
        }
        if(!isvalid_name(str)){
            cout<<"Este username ya esta en uso."<<endl;
        }
        if(!isvalid_string(str)||!isvalid_name(str)){
            char car=0;
            cout<<"Aun quieres registrar un usuario? s/n"<<endl;
            cin>>car;
            cin.ignore();
            if(car=='n'){
                cout<<endl<<endl;
                return;
            }
        }
    }while (!isvalid_name(str)||!isvalid_string(str));
    u.setUsername(str);
    do{
        cout<<"Contrasena del usuario: ";
        getline(cin,str);
        if(!isvalid_string(str)){
            cout<<"Escribiste el caracter reservado '|' "<<endl;
            char car=0;
            cout<<"Aun quieres registrar un usuario? s/n"<<endl;
            cin>>car;
            cin.ignore();
            if(car=='n'){
                cout<<endl<<endl;
                return;
            }
        }
    }while(!isvalid_string(str));
    u.setPassword(str);

    administrador_de_archivos.respaldar_usuario(u);
    indice.actualizar();

    cout<<"Se registro el usuario con exito."<<endl<<endl<<endl;
}

void Menu::acceder_usuario()
{
    int opc;
    do{
        cout<<"\tBienvenido "<<usuario.getNombre()<<"."<<endl;
        cout<<"1.-Mostrar"<<endl;
        cout<<"2.-Modificar"<<endl;
        cout<<"3.-Bloquear Temporalmente"<<endl;
        cout<<"4.-Eliminar Definitivamente"<<endl;
        cout<<"5.-Personajes"<<endl;
        cout<<"0.-Regresar"<<endl;
        cin>>opc;
        cin.ignore();
        switch (opc) {
        case 1:{
            cout<<endl<<endl;
            mostrar_usuario();
            break;
        }
        case 2:{
            cout<<endl<<endl;
            modificar_usuario();
            break;
        }
        case 3:{
            indice.bloquear_temporalmente(nrr_usuario,true);
            indice.modificarAt(nrr_usuario,usuario);
            cout<<"Se bloqueo tu cuenta con exito."<<endl<<endl;
            opc=0;
            break;
        }
        case 4:{
            int aux=-1;
            for (int i=0;i<diccionario.size();i++) {
                if(usuario.getUsername()==diccionario.at(i)->getLlaveSec()){
                    aux=diccionario.at(i)->getPos();
                    break;
                }
            }

            while (aux!=-1) {

                ifstream fin;
                fin.open("Personajes.bin", ios::binary);
                fin.seekg(aux,ios::beg);
                int auxtam,dim;
                fin.read((char*)&auxtam,sizeof(int));
                fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
                char cad_c[dim+1];
                fin.read(cad_c, dim);
                cad_c[dim] = '\0';
                fin.close();

                indice_grafos=administrador_de_archivos.carga_indice_grafos();
                for (int i=0;i<indice_grafos.size();i++) {
                    if(indice_grafos.at(i)->getLlaveSec()==cad_c){
                        administrador_de_archivos.elimina_grafo(indice_grafos.at(i)->getPos(),indice_grafos);
                        indice_grafos=administrador_de_archivos.carga_indice_grafos();
                        break;
                    }
                }

                administrador_de_archivos.elimina_personaje(aux,numero_personajes,diccionario,usuario.getUsername());
                actualizar_diccionario();

                for (int i=0;i<diccionario.size();i++) {
                    if(usuario.getUsername()==diccionario.at(i)->getLlaveSec()){
                        aux=diccionario.at(i)->getPos();
                        break;
                    }
                }

            }

            indice.eliminar(nrr_usuario);
            opc=0;
            break;
        }
        case 5:{
            cout<<endl;
            menu_personajes();
            break;
        }
        case 0:{
            cout<<endl<<endl;
            break;
        }
        default:{
            cout<<"Ingreso una opcion no valida."<<endl<<endl;
            break;
        }
        }
    }while(opc!=0);
}

void Menu::mostrar_usuarios()
{
    cout<<"Username:\tDireccion:\tPrimer personaje:"<<endl;
    for (int i=0;i<indice.size();i++) {
        if(!indice.at(i).getBloqueado()){
            int dic; bool found=false;
            for (int x=0;x<diccionario.size();x++) {
                if(diccionario.at(x)->getLlaveSec()==indice.at(i).getLlave_primaria()){
                    found=true; dic=x;
                }
            }
            if(found)
                cout<<indice.at(i).getLlave_primaria()<<"\t-\t"<<indice.at(i).getDireccion()<<"\t-\t"<<diccionario.at(dic)->getPos()<<endl;
            else {
                cout<<indice.at(i).getLlave_primaria()<<"\t-\t"<<indice.at(i).getDireccion()<<"\t-\t-1"<<endl;
            }
        }
    }
    cout<<endl;
}

void Menu::mostrar_usuario()
{
    cout<<"Nombre: "<<usuario.getNombre()<<endl;
    cout<<"Correo: "<<usuario.getCorreo()<<endl;
    cout<<"Username: "<<usuario.getUsername()<<endl;
    cout<<"Contrasena: "<<usuario.getPassword()<<endl<<endl;
}

void Menu::modificar_usuario()
{
    int opc;
    string str;
    cout<<"\tQue deseas modificar?"<<endl;
    cout<<"1.-Nombre"<<endl;
    cout<<"2.-Correo"<<endl;
    cout<<"3.-Username"<<endl;
    cout<<"4.-Contrasena"<<endl;
    cin>>opc;
    cin.ignore();

    switch (opc) {
    case 1:{
        do{
            cout<<"Escribe el nuevo nombre: ";
            getline(cin,str);
            if(!isvalid_string(str)){
                cout<<"Escribiste el caracter reservado '|' "<<endl;
                char car=0;
                cout<<"Aun quieres modificar al usuario? s/n"<<endl;
                cin>>car;
                cin.ignore();
                if(car=='n'){
                    cout<<endl<<endl;
                    return;
                }
            }
        }while(!isvalid_string(str));
        usuario.setNombre(str);
        cout<<"El nombre se cambio."<<endl<<endl<<endl;
        break;
    }
    case 2:{
        do{
            cout<<"Escribe el nuevo correo: ";
            getline(cin,str);
            if(!isvalid_mail(str)){
                cout<<"El correo no es valido."<<endl;
            }
            if(!isvalid_string(str))
                cout<<"Escribiste el caracter reservado '|' "<<endl;
            if(!isvalid_string(str)||!isvalid_mail(str)){
                char car=0;
                cout<<"Aun quieres modificar al usuario? s/n"<<endl;
                cin>>car;
                cin.ignore();
                if(car=='n'){
                    cout<<endl<<endl;
                    return;
                }
            }
        }while(!isvalid_mail(str)||!isvalid_string(str));

        usuario.setCorreo(str);
        cout<<"El correo se cambio."<<endl<<endl<<endl;
        break;
    }
    case 3:{
        do{
            cout<<"Escribe el nuevo username: ";
            getline(cin,str);
            if(!isvalid_name(str))
                cout<<"El username ya esta en uso."<<endl;
            if(!isvalid_string(str))
                cout<<"Escribiste el caracter reservado '|' "<<endl;
            if(!isvalid_string(str)||!isvalid_name(str)){
                char car=0;
                cout<<"Aun quieres modificar al usuario? s/n"<<endl;
                cin>>car;
                cin.ignore();
                if(car=='n'){
                    cout<<endl<<endl;
                    return;
                }
            }
        }while(!isvalid_name(str)||!isvalid_string(str));

        for (int i=0;i<diccionario.size();i++) {
            if(usuario.getUsername()==diccionario.at(i)->getLlaveSec()){
                diccionario.at(i)->setLlaveSec(str);
                break;
            }
        }

        for (int i=0;i<indice.size();i++) {
            if(usuario.getUsername()==indice.at(i).getLlave_primaria()){
                indice.at(i).setLlave_primaria(str);
                break;
            }
        }

        usuario.setUsername(str);
        cout<<"El username se cambio."<<endl<<endl<<endl;
        break;
    }
    case 4:{
        do{
            cout<<"Escribe la nueva contrasena: ";
            getline(cin,str);
            if(!isvalid_string(str)){
                cout<<"Escribiste el caracter reservado '|' "<<endl;
                char car=0;
                cout<<"Aun quieres modificar al usuario? s/n"<<endl;
                cin>>car;
                cin.ignore();
                if(car=='n'){
                    cout<<endl<<endl;
                    return;
                }
            }
        }while(!isvalid_string(str));

        usuario.setPassword(str);
        cout<<"La contrasena se cambio."<<endl<<endl<<endl;
        break;
    }
    }

    indice.modificarAt(nrr_usuario,usuario);

}

bool Menu::isvalid_mail(string correo)
{
    if(correo.size()<7){
        return false;
    }
    for (int i = 0; i < indice.size(); i++) {
        if(indice.getAt(i).getCorreo()==correo)
            return false;
    }
    bool arroba=false;
    for (size_t i=1;i <correo.size();i++) {
        if(correo.at(i)=='@'&& i<correo.size()-5)
            arroba=true;
    }
    bool dominio=false;
    if(".com"==correo.substr(correo.size()-4,4)){
        dominio=true;
    }
    if(arroba&&dominio)
        return true;
    else
        return false;
}

bool Menu::isvalid_name(string username)
{
    if(indice.size()==0)
        return true;

    bool acceso=false;
    int binary=indice.size()/2,max=indice.size(),menor=0;

    while (!acceso) {
        if(username==indice.at(binary).getLlave_primaria()){
            return false;
        }
        if(binary==menor||binary==max)
            break;

        if(username<indice.at(binary).getLlave_primaria()){
            max=binary;
            binary=(binary-menor)/2;
        }
        else {
            menor=binary;
            binary= (max-binary)/2+binary;
        }
    }
    return true;
}

bool Menu::isvalid_string(string str)
{
    for (size_t i = 0; i < str.size(); i++) {
        if(str.at(i)=='|')
            return false;
    }
    return true;
}

void Menu::menu_personajes()
{
    int opc;
    numero_personajes=administrador_de_archivos.num_personajes(usuario.getUsername(),diccionario);

    while (true) {
        cout<<"1.- Agregar Personaje"<<endl;
        cout<<"2.- Acceder a Personaje"<<endl;
        cout<<"3.- Eliminar Personaje"<<endl;
        cout<<"4.- Mostrar Personajes capturados"<<endl;
        cout<<"0.- Salir"<<endl<<endl;
        cout<<"Opcion: ";
        cin>>opc;
        cin.ignore();

        switch (opc) {
        case 1:{
            bool valido=true;
            Character personaje_aux;
            string str;
            if(numero_personajes==10){
                cout<<"Lo lamentamos solo puedes tener 10 personajes en total."<<endl<<endl;
                break;
            }
            if(numero_personajes==3){
                cout<<"Solo tienes permitido tener 3 personajes gratuitos."<<endl;
                cout<<"Deseas adquirir uno mas por 15$MX ?  S/N"<<endl<<endl;
                cout<<"Opcion:";
                char compra;
                cin>>compra;
                cin.ignore();
                if(compra=='s')
                    cout<<"Gracias por adquirir un nuevo personaje."<<endl;
                else if(compra=='n')
                    break;
                else {
                    cout<<"opcion no valida"<<endl;
                    break;
                }
            }
            if(numero_personajes>3){
                cout<<"A partir del 3 personaje tienes que comprar los personajes."<<endl;
                cout<<"Deseas adquirir uno mas por 15$MX ?  S/N"<<endl<<endl;
                cout<<"Opcion:";
                char compra;
                cin>>compra;
                cin.ignore();
                if(compra=='s')
                    cout<<"Gracias por adquirir un nuevo personaje."<<endl;
                else if(compra=='n')
                    break;
                else {
                    cout<<"opcion no valida"<<endl;
                    break;
                }
            }
            cout<<"Ingresa el nombre del personaje: "<<endl;
            getline(cin,str);

            ifstream fin;

            int pos = sizeof (int),auxtam=0,dim,tama;
            fin.open("Personajes.bin", ios::binary);
            fin.seekg(0,ios::end);
            tama=int(fin.tellg());
            fin.seekg(pos,ios::beg);


            while (pos<tama) {
                fin.read((char*)&auxtam,sizeof(int));

                fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
                char cad_c[dim+1];
                fin.read(cad_c, dim);
                cad_c[dim] = '\0';
                if(cad_c==str){
                    cout<<"Nombre no valido"<<endl<<endl;
                    valido=false;
                }
                pos+=auxtam;
                fin.seekg(pos,ios::beg);
            }
            fin.close();

//            for (int i=0;i<numero_personajes;i++) {
//                if(str==administrador_de_archivos.recupera_personaje(i,"Personajes.bin").nombre){
//                    cout<<"Nombre no valido"<<endl<<endl;
//                    valido=false;
//                    break;
//                }
//            }


            if(!valido)
                break;
            personaje_aux.nombre=str;

            cout<<"Ingresa el sexo del personaje: "<<endl;
            getline(cin,str);
            personaje_aux.sexo=str;

//            administrador_de_archivos.save_character(personaje_aux,diccionario,usuario.getUsername());
            administrador_de_archivos.respaldar_personaje(personaje_aux,numero_personajes,-1,"Personajes.bin",diccionario,usuario.getUsername());

//            for (int i=0;i<diccionario.size();i++) {
//                if(diccionario.at(i)->getLlaveSec()==usuario.getUsername()){
//                    usuario.setDireccion_personaje(diccionario.at(i)->getPos());
//                }
//            }

//            for (int i=0;i<indice.size();i++) {
//                if(indice.at(i).getLlave_primaria()==usuario.getUsername()){
//                    indice.modificarAt(i,usuario);
//                }
//            }

            numero_personajes=administrador_de_archivos.num_personajes(usuario.getUsername(),diccionario);
            actualizar_diccionario();

            Grafo<Location> aux;
            aux.setId(personaje_aux.getNombre());
            aux.insertaVertice(grafo_global.at(0));
            aux.setPosActual(0);

            ElemDiccionario elem;
            elem.setLlaveSec(personaje_aux.getNombre());
            elem.setPos(-1);

            indice_grafos.push_back(elem);
            administrador_de_archivos.respalda_grafo(aux,-1,indice_grafos);

            cout<<"Se agrego al personaje con exito"<<endl<<endl;
            break;
        }
        case 2:{
            if(numero_personajes==0){
                cout<<"No hay personajes registrados"<<endl<<endl;
                break;
            }

            string nom;
            int it=0;
            bool encontrado=false;
            cout<<"Escribe el nombre del personaje a acceder: "<<endl;
            getline(cin,nom);

            ifstream fin;
            ElemDiccionario* e = nullptr;
            for (int i=0;i<diccionario.size();i++) {
                if(diccionario.at(i)->getLlaveSec()==usuario.getUsername())
                    e=diccionario.at(i);
            }

            int pos = e->getPos(),auxtam=0,dim;
            fin.open("Personajes.bin", ios::binary);
            fin.seekg(pos,ios::beg);
            fin.read((char*)&auxtam,sizeof(int));

            fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
            char cad_c[dim+1];
            fin.read(cad_c, dim);
            cad_c[dim] = '\0';
            if(cad_c==nom){
                encontrado=true;
                it=pos;
            }
            fin.seekg(auxtam-3*int(sizeof (int))-dim*int(sizeof (char)),ios::cur);
            fin.read((char*)&pos,sizeof(int));

            while(pos != -1){
                fin.seekg(pos,ios::beg);
                fin.read((char*)&auxtam,sizeof(int));
                fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
                char cad_c[dim+1];
                fin.read(cad_c, dim);
                cad_c[dim] = '\0';
                if(cad_c==nom){
                    encontrado=true;
                    it=pos;
                }
                fin.seekg(auxtam-3*int(sizeof (int))-dim*int(sizeof (char)),ios::cur);
                fin.read((char*)&pos,sizeof(int));
            }
            fin.close();

//            for (int i=0;i<numero_personajes;i++) {
//                if(nom==administrador_de_archivos.recupera_personaje(i,"Personajes.bin").nombre){
//                    it=i;
//                    encontrado=true;
//                    break;
//                }
//            }

            if(encontrado){
                personaje=administrador_de_archivos.load_character(it);
                NRR= it;

                for (int i=0;i<indice_grafos.size();i++) {
                    if(indice_grafos.at(i)->getLlaveSec()==personaje.getNombre()){
                        grafo=administrador_de_archivos.recupera_grafo(indice_grafos.at(i)->getPos());
                        break;
                    }
                }
                acceder_personaje();
                break;
            }
            else {
                cout<<"No se encuentra ningun personaje con ese nombre."<<endl<<endl;
                break;
            }
        }
        case 3:{
            if(numero_personajes==0){
                cout<<"No hay personajes registrados"<<endl<<endl;
                break;
            }

            string nom;
            int it=0;
            bool encontrado=false;
            cout<<"Escribe el nombre del personaje a eliminar: "<<endl;
            getline(cin,nom);

            ifstream fin;
            ElemDiccionario* e = nullptr;
            for (int i=0;i<diccionario.size();i++) {
                if(diccionario.at(i)->getLlaveSec()==usuario.getUsername())
                    e=diccionario.at(i);
            }

            int pos = e->getPos(),auxtam=0,dim;
            fin.open("Personajes.bin", ios::binary);
            fin.seekg(pos,ios::beg);
            fin.read((char*)&auxtam,sizeof(int));

            fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
            char cad_c[dim+1];
            fin.read(cad_c, dim);
            cad_c[dim] = '\0';
            if(cad_c==nom){
                encontrado=true;
                it=pos;
            }
            fin.seekg(auxtam-3*int(sizeof (int))-dim*int(sizeof (char)),ios::cur);
            fin.read((char*)&pos,sizeof(int));

            while(pos != -1){
                fin.seekg(pos,ios::beg);
                fin.read((char*)&auxtam,sizeof(int));
                fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
                char cad_c[dim+1];
                fin.read(cad_c, dim);
                cad_c[dim] = '\0';
                if(cad_c==nom){
                    encontrado=true;
                    it=pos;
                }
                fin.seekg(auxtam-3*int(sizeof (int))-dim*int(sizeof (char)),ios::cur);
                fin.read((char*)&pos,sizeof(int));
            }
            fin.close();

//            for (int i=0;i<numero_personajes;i++) {
//                if(nom==administrador_de_archivos.recupera_personaje(i,"Personajes.bin").nombre){
//                    it=i;
//                    encontrado=true;
//                    break;
//                }
//            }
            if(encontrado){
                administrador_de_archivos.elimina_personaje(it,numero_personajes,diccionario,usuario.getUsername());
                actualizar_diccionario();

                for (int i=0;i<indice_grafos.size();i++) {
                    if(indice_grafos.at(i)->getLlaveSec()==nom){
                        administrador_de_archivos.elimina_grafo(indice_grafos.at(i)->getPos(),indice_grafos);
                        indice_grafos=administrador_de_archivos.carga_indice_grafos();
                        break;
                    }
                }

                break;
            }
            else {
                cout<<"No se encuentra ningun personaje con ese nombre."<<endl<<endl;
                break;
            }
        }
        case 4:{
            if(numero_personajes==0){
                cout<<"No hay personajes registrados"<<endl<<endl;
                break;
            }

//            int pos=sizeof (int);
//            for (int i=1;i<=numero_personajes;i++){
//                cout<<i<<") "<<administrador_de_archivos.recupera_personaje(pos,"Personajes.bin").nombre<<endl;
//                pos+=administrador_de_archivos.tamano_total_personaje(administrador_de_archivos.recupera_personaje(pos,"Personajes.bin"));
//            }
            administrador_de_archivos.mostrar_personajes_de_usuario(usuario.getUsername(),diccionario);
            cout<<endl;
            break;
        }
        case 0:{
            actualizar_diccionario();
            return;
        }
        default:{
            cout<<"Digitaste una opcion no valida"<<endl<<endl;
            break;
        }
        }
    }

}

void Menu::acceder_personaje()
{
    int opc;
    while (true) {
        cout<<"\tBienvenido "<<personaje.nombre<<endl;
        cout<<"1.-Modificar"<<endl;
        cout<<"2.-Mostrar"<<endl;
        cout<<"3.-Completar Mision"<<endl;
        cout<<"4.-Mapa"<<endl;
        cout<<"0.-Abandonar"<<endl<<endl;
        cin>>opc;
        cin.ignore();
        switch (opc) {
        case 1:{
            while (true) {
                int eleccion;
                string str;
                cout<<"1.-Nombre"<<endl;
                cout<<"2.-Sexo"<<endl;
                cout<<"3.-Team"<<endl;

                cout<<"4.-Arma primaria"<<endl;
                cout<<"5.-Arma secundaria"<<endl;
                cout<<"6.-Blindaje"<<endl;
                cout<<"7.-Nivel"<<endl;
                cout<<"8.-Editar Armas"<<endl;

                cout<<"0.-Regresar"<<endl;
                cin>>eleccion;
                cin.ignore();
                if(eleccion==0)
                    break;
                switch (eleccion) {
                case 1:{
                    bool valido=true;
                    cout<<"Escribe el nuevo nombre:"<<endl;
                    getline(cin,str);

                    ifstream fin;
                    ElemDiccionario* e = nullptr;
                    for (int i=0;i<diccionario.size();i++) {
                        if(diccionario.at(i)->getLlaveSec()==usuario.getUsername())
                            e=diccionario.at(i);
                    }

                    int pos = e->getPos(),auxtam=0,dim;
                    fin.open("Personajes.bin", ios::binary);
                    fin.seekg(pos,ios::beg);
                    fin.read((char*)&auxtam,sizeof(int));

                    fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
                    char cad_c[dim+1];
                    fin.read(cad_c, dim);
                    cad_c[dim] = '\0';
                    if(cad_c==str){
                        cout<<"Nombre no valido"<<endl<<endl;
                        valido=false;
                    }
                    fin.seekg(auxtam-3*int(sizeof (int))-dim*int(sizeof (char)),ios::cur);
                    fin.read((char*)&pos,sizeof(int));

                    while(pos != -1){
                        fin.seekg(pos,ios::beg);
                        fin.read((char*)&auxtam,sizeof(int));
                        fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
                        char cad_c[dim+1];
                        fin.read(cad_c, dim);
                        cad_c[dim] = '\0';
                        if(cad_c==str){
                            cout<<"Nombre no valido"<<endl<<endl;
                            valido=false;
                        }
                        fin.seekg(auxtam-3*int(sizeof (int))-dim*int(sizeof (char)),ios::cur);
                        fin.read((char*)&pos,sizeof(int));
                    }
                    fin.close();

                    if(valido){
                        personaje.nombre=str;
                        cout<<"Se ha actualizado el nombre del personaje."<<endl<<endl;
                    }
                    break;
                }
                case 2:{
                    cout<<"Escribe el nuevo sexo:"<<endl;
                    getline(cin,str);
                    personaje.sexo=str;
                    cout<<"Se ha actualizado el sexo del personaje."<<endl<<endl;
                    break;
                }
                case 3:{
                    int team;
                    cout<<"Escoge tu nuevo team: "<<endl<<endl;
                    cout<<"1.-Bandidos"<<endl;
                    cout<<"2.-Cazarecompenzas"<<endl;
                    cout<<"3.-Alguaciles"<<endl;
                    cout<<"4.-Crea tu propio Team"<<endl;
                    cin>>team;
                    cin.ignore();
                    switch (team) {
                    case 1:{
                        personaje.team="Bandidos";
                        cout<<"Se actualizo el team"<<endl<<endl;
                        break;
                    }
                    case 2:{
                        personaje.team="Cazarecompenzas";
                        cout<<"Se actualizo el team"<<endl<<endl;
                        break;
                    }
                    case 3:{
                        personaje.team="Alguaciles";
                        cout<<"Se actualizo el team"<<endl<<endl;
                        break;
                    }
                    case 4:{
                        cout<<"Escribe el nombre de tu Team:"<<endl;
                        getline(cin,str);
                        personaje.team=str;
                        cout<<"Se actualizo el team"<<endl<<endl;
                        break;
                    }
                    default:{
                        cout<<"Opcion no valida"<<endl<<endl;
                        break;
                    }
                    }
                    break;
                }
                case 4:{
                    if(personaje.inventario.armas.size()==0){
                        cout<<"No tienes otras armas en tu inventario"<<endl<<endl;
                        break;
                    }
                    else {
                        int nueva_arma;
                        cout<<"Selecciona tu nueva arma primaria: "<<endl<<endl;
                        for (int i=0;i<personaje.inventario.armas.size();i++) {
                            cout<<i<<") "<<personaje.inventario.armas.at(i)->nombre<<endl;
                        }
                        cout<<endl;
                        cin>>nueva_arma;
                        cin.ignore();
                        if(nueva_arma>=personaje.inventario.armas.size()||nueva_arma<0){
                            cout<<"Opcion no valida"<<endl<<endl;
                            break;
                        }
                        personaje.inventario.armas.push_back(personaje.primaria);
                        personaje.primaria=*personaje.inventario.armas.at(nueva_arma);
                        personaje.inventario.armas.erase(nueva_arma);
                        cout<<"Se ha cambiado tu arma primaria"<<endl<<endl;
                    }
                    break;
                }
                case 5:{
                    if(personaje.inventario.armas.size()==0){
                        cout<<"No tienes otras armas en tu inventario"<<endl<<endl;
                        break;
                    }
                    else {
                        int nueva_arma;
                        cout<<"Selecciona tu nueva arma secundaria: "<<endl<<endl;
                        for (int i=0;i<personaje.inventario.armas.size();i++) {
                            cout<<i<<") "<<personaje.inventario.armas.at(i)->nombre<<endl;
                        }
                        cout<<endl;
                        cin>>nueva_arma;
                        cin.ignore();
                        if(nueva_arma>=personaje.inventario.armas.size()||nueva_arma<0){
                            cout<<"Opcion no valida"<<endl<<endl;
                            break;
                        }
                        personaje.inventario.armas.push_back(personaje.secundaria);
                        personaje.secundaria=*personaje.inventario.armas.at(nueva_arma);
                        personaje.inventario.armas.erase(nueva_arma);
                        cout<<"Se ha cambiado tu arma secundaria"<<endl<<endl;
                    }
                    break;
                }
                case 6:{
                    bool tiene=false;
                    for (int i=0;i<personaje.inventario.objetos.size();i++) {
                        if(personaje.inventario.objetos.at(i)->tipo=="Blindaje"){
                            tiene=true;
                        }
                    }
                    if(!tiene){
                        cout<<"No tienes otros blindajes en tu inventario"<<endl<<endl;
                        break;
                    }
                    else {
                        int nueva_arma;
                        cout<<"Selecciona tu nuevo blindaje: "<<endl<<endl;
                        for (int i=0;i<personaje.inventario.objetos.size();i++) {
                            if(personaje.inventario.objetos.at(i)->tipo=="Blindaje"){
                                cout<<i<<") "<<personaje.inventario.objetos.at(i)->nombre<<endl;
                            }
                        }
                        cout<<endl;
                        cin>>nueva_arma;
                        cin.ignore();
                        if(nueva_arma>=personaje.inventario.objetos.size()||nueva_arma<0){
                            cout<<"Opcion no valida"<<endl<<endl;
                            break;
                        }
                        personaje.inventario.objetos.push_back(personaje.blindaje);
                        personaje.blindaje=*personaje.inventario.objetos.at(nueva_arma);
                        personaje.inventario.objetos.erase(nueva_arma);
                        cout<<"Se ha cambiado tu blindaje"<<endl<<endl;
                    }
                    break;
                }
                case 7:{
                    cout<<"Escribe el nuevo nivel:"<<endl;
                    getline(cin,str);
                    personaje.nivel=str;
                    cout<<"Se ha actualizado el nivel del personaje."<<endl<<endl;
                    break;
                }
                case 8:{
                    editor_de_armas();
                    break;
                }
                default:{
                    cout<<"Opcion no valida"<<endl<<endl;
                }
                }
                actualizar_diccionario();
                for (int i=0;i<indice_grafos.size();i++) {
                    if(indice_grafos.at(i)->getLlaveSec()==grafo.getId()){
                        grafo.setId(personaje.getNombre());
                        administrador_de_archivos.respalda_grafo(grafo,indice_grafos.at(i)->getPos(),indice_grafos);
                        break;
                    }
                }
                break;
            }
            break;
        }
        case 2:{
            int eleccion;
            cout<<"1.-Personaje"<<endl;
            cout<<"2.-Historial"<<endl;
            cout<<"3.-Inventario (Armas)"<<endl;
            cout<<"4.-Inventario (Objetos)"<<endl;
            cin>>eleccion;
            cin.ignore();

            if(eleccion==1){
                cout<<endl;
                cout<<"Nombre: "<<personaje.nombre<<endl;
                cout<<"Sexo: "<<personaje.sexo<<endl;
                cout<<"Team: "<<personaje.team<<endl;

                cout<<"Experiencia: "<<personaje.experiencia<<endl;
                cout<<"Vida: "<<personaje.vida<<endl;
                cout<<"Dinero: "<<personaje.dinero<<endl;
                cout<<"Nivel: "<<personaje.nivel<<endl;
                cout<<"Habilidad para acertar disparos: "<<personaje.habilidad_acertar<<endl;
                cout<<"Habilidad para hacer criticos: "<<personaje.habilidad_critico<<endl;

                cout<<"Total de armas en el inventario: "<<personaje.inventario.armas.size()<<endl;
                cout<<"Total de objetos en el inventario: "<<personaje.inventario.objetos.size()<<endl<<endl;

                cout<<"Arma primaria: "<<personaje.primaria.nombre<<endl;
                cout<<"Dano de arma primaria: "<<personaje.primaria.danio<<endl;
                cout<<"Cadencia de arma primaria: "<<personaje.primaria.cadencia<<endl<<endl;

                cout<<"Arma secundaria: "<<personaje.secundaria.nombre<<endl;
                cout<<"Dano de arma secundaria: "<<personaje.secundaria.danio<<endl;
                cout<<"Cadencia de arma secundaria: "<<personaje.secundaria.cadencia<<endl<<endl;
            }
            else if (eleccion==2) {
                cout<<endl<<"Asesinatos: "<<personaje.historial.asesinatos<<endl;
                cout<<"Misiones Completadas: "<<personaje.historial.misiones_completadas<<endl<<endl;
            }
            else if (eleccion==3) {
                cout<<endl<<endl;
                for (int i=0;i<personaje.inventario.armas.size();i++) {
                    cout<<i+1<<".- "<<personaje.inventario.armas.at(i)->nombre<<endl;
                    cout<<"Danio: "<<personaje.inventario.armas.at(i)->danio<<endl;
                    cout<<"Cadencia: "<<personaje.inventario.armas.at(i)->cadencia<<endl;
                    cout<<"Canion: "<<personaje.inventario.armas.at(i)->canion.nombre<<endl;
                    cout<<"Canion nivel: "<<personaje.inventario.armas.at(i)->canion.nivel<<endl<<endl;
                }
                cout<<endl;
            }
            else if (eleccion==4) {
                cout<<endl<<endl;
                for (int i=0;i<personaje.inventario.objetos.size();i++) {
                    cout<<i+1<<".- "<<personaje.inventario.objetos.at(i)->nombre<<endl;
                    cout<<"Tipo: "<<personaje.inventario.objetos.at(i)->tipo<<endl;
                    cout<<"Nivel: "<<personaje.inventario.objetos.at(i)->nivel<<endl<<endl;
                }
                cout<<endl;
            }
            else {
                cout<<"Opcion no valida"<<endl<<endl;
            }


            break;
        }
        case 3:{
            int mision;
            cout<<"1.-Completar siguiente mision"<<endl;
            cout<<"2.-Jugar siguiente mision"<<endl;
            cout<<"0.-Regresar"<<endl;
            cin>>mision;
            cin.ignore();

            if(mision==0)
                break;
            else if(mision==1){
                personaje.historial.misiones_completadas++;
                personaje.experiencia+=5;
                personaje.nivel=personaje.calcular_nivel();
                cout<<"Ahora tienes "<<personaje.historial.misiones_completadas<<" misiones completadas."<<endl;
                cout<<personaje.experiencia<<" de experiencia."<<endl;
                cout<<"Y eres nivel "<<personaje.nivel<<endl<<endl;
                if(personaje.experiencia>25 && personaje.team=="ND"){
                    cout<<"Ha llegado el momento de escoger un team"<<endl<<endl;
                    int team;
                    string str;
                    while (personaje.team=="ND") {
                        cout<<"Escoge tu nuevo team: "<<endl<<endl;
                        cout<<"1.-Bandidos"<<endl;
                        cout<<"2.-Cazarecompenzas"<<endl;
                        cout<<"3.-Alguaciles"<<endl;
                        cout<<"4.-Crea tu propio Team"<<endl;
                        cin>>team;
                        cin.ignore();
                        switch (team) {
                        case 1:{
                            personaje.team="Bandidos";
                            cout<<"Se actualizo el team"<<endl<<endl;
                            break;
                        }
                        case 2:{
                            personaje.team="Cazarecompenzas";
                            cout<<"Se actualizo el team"<<endl<<endl;
                            break;
                        }
                        case 3:{
                            personaje.team="Alguaciles";
                            cout<<"Se actualizo el team"<<endl<<endl;
                            break;
                        }
                        case 4:{
                            cout<<"Escribe el nombre de tu Team:"<<endl;
                            getline(cin,str);
                            personaje.team=str;
                            cout<<"Se actualizo el team"<<endl<<endl;
                            break;
                        }
                        default:{
                            cout<<"Opcion no valida"<<endl<<endl;
                            break;
                        }
                        }
                    }
                }
                break;
            }
            else if(mision==2){
                system("cls");
                combate(administrador_de_archivos.recupera_oponente(personaje.historial.misiones_completadas));
                break;
            }
            else {
                cout<<"Opcion no valida"<<endl<<endl;
            }
            break;

        }
        case 4:{
            acceder_grafo(&grafo);

            for (int i=0;i<indice_grafos.size();i++) {
                if(indice_grafos.at(i)->getLlaveSec()==personaje.getNombre()){
                    administrador_de_archivos.respalda_grafo(grafo,indice_grafos.at(i)->getPos(),indice_grafos);
                    break;
                }
            }
            break;
        }
        case 0:{
            cout<<endl<<endl;

            administrador_de_archivos.respaldar_personaje(personaje,numero_personajes,NRR,"Personajes.bin",diccionario,usuario.getUsername());

            actualizar_diccionario();

            for (int i=0;i<indice_grafos.size();i++) {
                if(indice_grafos.at(i)->getLlaveSec()==personaje.getNombre()){
                    administrador_de_archivos.respalda_grafo(grafo,indice_grafos.at(i)->getPos(),indice_grafos);
                    break;
                }
            }

            return;
        }
        default:{
            cout<<"Opcion no valida"<<endl<<endl;
            break;
        }
        }
    }
}

void Menu::principal_grafos()
{
    int opc;
    do{
        cout<<"1.- Crear Grafo"<<endl;
        cout<<"2.- Eliminar Grafo"<<endl;
        cout<<"3.- Mostrar Grafo Global"<<endl;
        cout<<"4.- Acceder"<<endl;
        cout<<"5.- Mostrar IDs"<<endl;
        cout<<"0.- Salir"<<endl;
        cin>>opc;
        cin.ignore();


        switch(opc){
        case 1:{//Crear Grafo
            string id_grafo;
            cout<<"Escribe el ID del nuevo grafo: ";
            getline(cin,id_grafo);

            bool validator=true;

            for (int i=0;i<grafos.size();i++) {
                if(grafos.at(i)->getId() == id_grafo){
                    validator=false;
                    break;
                }
            }

            if(validator){

            Grafo<Location> aux;

            aux.setId(id_grafo);
            aux.insertaVertice(grafo_global.at(0));
            aux.setPosActual(0);

            grafos.push_back(aux);

            administrador_de_archivos.respalda_grafos(grafos);

            cout<<"Se ha creado el grafo "<<id_grafo<<" con exito."<<endl<<endl;
            }
            else {
                cout<<"Este ID ya esta en uso."<<endl<<endl;
            }
            break;
        }
        case 2:{//Eliminar Grafo
            string eliminar;

            cout<<"Escribe el ID del grafo que quieres eliminar: ";
            getline(cin,eliminar);

            bool validator=true;
            for (int i=0;i<grafos.size();i++) {
                if(eliminar == grafos.at(i)->getId()){
                    grafos.erase(i);
                    administrador_de_archivos.respalda_grafos(grafos);
                    cout<<"Se ha borrado el grafo "<<eliminar<<" con exito."<<endl<<endl;
                    validator=false;
                    break;
                }
            }
            if(validator)
            cout<<"No se encuantra ningun grafo con esa ID"<<endl<<endl;
            break;
        }
        case 3:{//Mostrar global

            cout<<"Grafo Global:"<<endl<<endl;
            cout<<grafo_global.toString()<<endl<<endl;

            break;
        }
        case 4:{//Acceder
            string str;
            cout<<"Escribe el ID del grafo al que quieres acceder"<<endl<<endl;
            getline(cin,str);

            bool validator =true;
            for (int i=0;i<grafos.size();i++) {
                if(str == grafos.at(i)->getId()){
                    acceder_grafo(grafos.at(i));
                    validator=false;
                    break;
                }
            }
            if(validator)
            cout<<"No se encuentra ningun grafo con esa ID."<<endl<<endl;

            break;
        }
        case 5:{
            if(grafos.size()>0){

            cout<<"ID de lo grafos: "<<endl<<endl;

            for (int i=0;i<grafos.size();i++) {
                cout<<i<<".- "<<grafos.at(i)->getId()<<endl;
            }
            cout<<endl;

            }
            else {
                cout<<"No se ha registrado ningun grafo"<<endl<<endl;
            }
            break;
        }
        case 0:{
            administrador_de_archivos.respalda_grafos(grafos);
            break;
        }
        default:{
            cout<<"Opcion no valida"<<endl<<endl;
            break;
        }
        }
    }while(opc!=0);
}

void Menu::acceder_grafo(Grafo<Location>* personal)
{
    int opc;
    cout<<endl;
    do{
        cout<<"\tBienvenido al grafo "<<personal->getId()<<endl;
        cout<<"1.- Mostrar Grafo"<<endl;
        cout<<"2.- Mostrar Lugar Actual"<<endl;
        cout<<"3.- Mostrar Lugares Adyacentes"<<endl;
        cout<<"4.- Desplazarse"<<endl;
        cout<<"5.- Visitados"<<endl;
        cout<<"0.- Salir"<<endl;
        cin>>opc;
        cin.ignore();

        switch(opc){
        case 1:{//Actual  mostrar grafo

            cout<<"\tGrafo "<<personal->getId()<<endl<<endl;
            cout<<personal->toString()<<endl<<endl;

            break;
        }
        case 2:{//Adyacentes   actual

            cout<<"Posicion Actual: ";
            cout<<personal->getPosActual().getNombre()<<endl<<endl;

            break;
        }
        case 3:{//Visitados   adyacentes

            Lista_doble_ligada<Vertice<Location>> aux;
            aux= grafo_global.busca( personal->getPosActual() )->getAdyacentes();

            int cost=0;

            cout<<"Vertices Adyacentes: "<<endl<<endl;
            for (int i=0;i<aux.size();i++) {

                for (int j=0;j<grafo_global.busca( personal->getPosActual() )->aristas.size();j++) {
                    if(grafo_global.busca( personal->getPosActual() )->aristas.at(j)->destino->dato.getNombre() == aux.at(i)->getDato().getNombre()){
                        cost=grafo_global.busca( personal->getPosActual() )->aristas.at(j)->pond;
                    }
                }

                cout<<i<<".- "<<aux.at(i)->getDato().getNombre()<<"  -  Costo: "<<cost<<endl;
            }
            cout<<endl;

            break;
        }
        case 4:{ //moverse

            int mov;
            Lista_doble_ligada<Vertice<Location>> aux;
            aux= grafo_global.busca( personal->getPosActual() )->getAdyacentes();

            int cost=0;

            cout<<"A que lugar quieres moverte: "<<endl<<endl;
            for (int i=0;i<aux.size();i++) {

                for (int j=0;j<grafo_global.busca( personal->getPosActual() )->aristas.size();j++) {
                    if(grafo_global.busca( personal->getPosActual() )->aristas.at(j)->destino->dato.getNombre() == aux.at(i)->getDato().getNombre()){
                        cost=grafo_global.busca( personal->getPosActual() )->aristas.at(j)->pond;
                    }
                }

                cout<<i<<".- "<<aux.at(i)->getDato().getNombre()<<"  -  Costo: "<<cost<<endl;
            }
            cout<<endl;
            cin>>mov;
            cin.ignore();

            if(mov>=0 && mov<aux.size()){

                personal->InsertaArista(personal->getPosActual(),grafo_global.busca(aux.at(mov)->getDato())->getDato(),cost);

                for (int i=0;i<personal->size();i++) {
                    if(personal->at( size_t(i) ).getNombre() == aux.at(mov)->getDato().getNombre()){
                        personal->setPosActual(i);
                    }
                }

            }
            //administrador_de_archivos.respalda_grafos(grafos);
            break;
        }
        case 5:{
            cout<<"Lugares visitados: "<<endl<<endl;
            for (size_t i=0;i < size_t(personal->size());i++) {
                cout<<i<<".- "<<personal->at(i).getNombre()<<endl;
            }

            cout<<endl;

            break;
        }
        case 0:{
            cout << "Has salido del grafo "<< personal->getId() << endl<<endl;
            break;
        }
        default:{
            cout<<"Opcion no valida"<<endl<<endl;
            break;
        }
        }
    }while(opc!=0);
}

void Menu::editor_de_armas()
{
    int opc=1;
    while (opc!=0) {
        cout<<"Que arma quieres editar?"<<endl;
        cout<<"1.- Primaria"<<endl;
        cout<<"2.- Secundaria"<<endl;
        cout<<"3.- Otra del Inventario"<<endl;
        cout<<"0.- Regresar"<<endl;
        cin>>opc;
        cin.ignore();

        switch (opc) {
        case 0:break;
        case 1:{
            int pieza=1;
            while (pieza!=0) {
                cout<<"Actualmente tu arma primaria tiene: "<<endl<<endl;
                cout<<"Danio: "<<personaje.primaria.danio<<endl;
                cout<<"Cadencia: "<<personaje.primaria.cadencia<<endl;
                cout<<"Canion: "<<personaje.primaria.canion.nombre<<endl;
                cout<<"Nivel del canion: "<<personaje.primaria.canion.nivel<<endl<<endl;
                cout<<"Nota: El danio es igual al nivel del canion que tiene equipado."<<endl<<endl;

                cout<<"Selecciona el numero del arma con la que quieres cambiar canion o presiona 0 para regresar"<<endl<<endl;
                cout<<"Se muestran los caniones compatibles con esta arma:"<<endl;

                cout<<"0) Salir"<<endl;

                for (int i=0;i<personaje.inventario.armas.size();i++) {
                    if(personaje.inventario.armas.at(i)->cadencia==personaje.primaria.cadencia){
                        cout<<i+1<<") "<<personaje.inventario.armas.at(i)->canion.nombre<<"   -   Nivel:"<<personaje.inventario.armas.at(i)->canion.nivel<<endl;
                    }
                }
                cin>>pieza;
                cin.ignore();

                if(pieza!=0){
                Objeto aux=personaje.primaria.canion;
                personaje.primaria.canion=personaje.inventario.armas.at(pieza-1)->canion;
                personaje.inventario.armas.at(pieza-1)->canion=aux;

                personaje.primaria.danio=personaje.primaria.canion.nivel;
                personaje.inventario.armas.at(pieza-1)->danio=aux.nivel;
                cout<<"Se ha intercambiado el canion entre "<<personaje.primaria.nombre<<" y "<<personaje.inventario.armas.at(pieza-1)->nombre<<endl;
                getchar();
                system("cls");
                }
            }
            break;
        }
        case 2:{
            break;
        }
        case 3:{

            cout<<"Que arma del inventario quieres editar?"<<endl;
            for (int i=0;i<personaje.inventario.armas.size();i++) {
                cout<<i<<".- "<<personaje.inventario.armas.at(i)->nombre<<endl;
            }
            break;
        }
        default:{
            break;
        }
        }
    }
    system("cls");
}

void Menu::combate(Character oponente)
{
    cout<<"En esta mision te toca enfrentarte a "<<oponente.nombre<<endl<<endl;

    cout<<"Cada uno escogera una arma a utilizar y en base a esto y a las habilidades de cada jugador,"<<endl;
    cout<<"se determinara quien es el ganador."<<endl<<endl;
    int ronda=1,opc=0;
    bool ganador=false;
    while (!ganador) {
        cout<<"Ronda: "<<ronda<<endl<<endl;
        cout<<"Tus habilidades: "<<endl;
        cout<<"Habilidad para acertar:"<<personaje.habilidad_acertar<<endl<<"Habilidad para hacer critico:"<<personaje.habilidad_critico<<endl<<endl;
        cout<<"Que arma usaras en esta ronda?"<<endl;
        cout<<"1.-"<<personaje.primaria.nombre<<" - Danio: "<<personaje.primaria.danio<<" - Cadencia: "<<personaje.primaria.cadencia<<endl;
        cout<<"2.-"<<personaje.secundaria.nombre<<" - Danio: "<<personaje.secundaria.danio<<" - Cadencia: "<<personaje.secundaria.cadencia<<endl<<endl;
        cout<<"Opcion: ";
        cin>>opc;

        Arma arma_usuario,arma_oponente;

        if(opc==1)
            arma_usuario=personaje.primaria;
        else
            arma_usuario=personaje.secundaria;

        srand(time(NULL));
        int arma_opo=1+ rand() % 2;

        if(arma_opo==1)
            arma_oponente=oponente.primaria;
        else
            arma_oponente=oponente.secundaria;

        system("cls");
        cout<<oponente.nombre<<" decidio usar su "<<arma_oponente.nombre<<endl<<endl;

        int tiros_usuario=arma_usuario.cadencia;
        int acertados_usuario=0,criticos_usuario=0;

        for (int i=0;i<tiros_usuario;i++) {
            int ran=1+rand() % 100;
            if(ran<=personaje.habilidad_acertar){
                acertados_usuario++;
                ran=1+rand() % 100;
                if(ran<=personaje.habilidad_critico)
                    criticos_usuario++;
            }
        }

        int tiros_oponente=arma_oponente.cadencia;
        int acertados_oponente=0,criticos_oponente=0;

        for (int i=0;i<tiros_oponente;i++) {
            int ran=1+rand() % 100;
            if(ran<=oponente.habilidad_acertar){
                acertados_oponente++;
                ran=1+rand() % 100;
                if(ran<=oponente.habilidad_critico)
                    criticos_oponente++;
            }
        }

        int total_usuario= acertados_usuario*arma_usuario.danio+criticos_usuario*arma_usuario.danio;
        int total_oponente= acertados_oponente*arma_oponente.danio+criticos_oponente*arma_oponente.danio;

        oponente.vida=oponente.vida-total_usuario;
        personaje.vida=personaje.vida-total_oponente;


        cout<<"                    Tu   -   "<<oponente.nombre<<endl;
        cout<<"Disparos hechos:    "<<tiros_usuario<<"    -    "<<tiros_oponente<<endl;
        cout<<"Disparos acertados: "<<acertados_usuario<<"    -    "<<acertados_oponente<<endl;
        cout<<"Criticos:           "<<criticos_usuario<<"    -    "<<criticos_oponente<<endl<<endl;
        cout<<"Total de danio:     "<<total_usuario<<"    -    "<<total_oponente<<endl;
        cout<<"Vida restante:      "<<personaje.vida<<"   -   "<<oponente.vida<<endl<<endl;

        if(personaje.vida<=0&&oponente.vida<=0){
            cout<<"Han muerto los dos al mismo tiempo!"<<endl;
            cout<<"Nadie gana"<<endl<<endl;
            ganador=true;
            personaje.vida=100;
            if(personaje.dinero>10){
                personaje.dinero=personaje.dinero-10;
                cout<<"Se te han descontado 10 de tu dinero para el doctor."<<endl<<endl;
            }
            else {
                cout<<"Eres tan pobre que el doctor no te cobra por esta vez."<<endl<<endl;
            }
        }
        else {
            if(personaje.vida<=0){
                cout<<"Has Muerto."<<endl;
                ganador=true;
                personaje.vida=100;
                if(personaje.dinero>10){
                    personaje.dinero=personaje.dinero-10;
                    cout<<"Se te han descontado 10 de tu dinero para el doctor."<<endl<<endl;
                }
                else {
                    cout<<"Eres tan pobre que el doctor no te cobra por esta vez."<<endl<<endl;
                }

            }
            if(oponente.vida<=0){
                cout<<oponente.nombre<<" ha Muerto."<<endl;
                ganador=true;
                personaje.historial.asesinatos++;
                personaje.historial.misiones_completadas++;
                personaje.experiencia+=5;
                personaje.habilidad_acertar+=3;
                personaje.habilidad_critico+=4;
                cout<<"Parece que "<<oponente.nombre<<" tenia "<<oponente.dinero<<" dolares"<<endl;
                personaje.dinero+=oponente.dinero;
                cout<<"Tu dinero ahora es: "<<personaje.dinero<<endl<<endl;

                personaje.inventario.armas.push_back(oponente.primaria);
                personaje.inventario.armas.push_back(oponente.secundaria);
                cout<<"Tomaste "<<oponente.primaria.nombre<<" y "<<oponente.secundaria.nombre<<endl;
                cout<<"Si quieres equiparte alguna ve a Modificar"<<endl<<endl;

                if(oponente.inventario.objetos.size()>0){
                    cout<<"Ademas tomaste los siguientes objetos: "<<endl<<endl;
                    for (int i=0;i<oponente.inventario.objetos.size();i++) {
                        personaje.inventario.objetos.push_back(*oponente.inventario.objetos.at(i));
                        cout<<i<<") "<<oponente.inventario.objetos.at(i)->nombre<<endl;
                    }
                    cout<<endl;
                }
                else {
                    cout<<"Parece que "<<oponente.nombre<<" no cargaba ningun objeto."<<endl<<endl;
                }

                cout<<"Decides tomar el blindaje de "<<oponente.nombre<<" ( "<<oponente.blindaje.nombre<<" )"<<endl;
                personaje.inventario.objetos.push_back(oponente.blindaje);
                cout<<"Si quieres equipartelo ve a Modificar"<<endl<<endl;

                personaje.vida=100;
                if(personaje.dinero>10){
                    personaje.dinero=personaje.dinero-10;
                    cout<<"Se te han descontado 10 de tu dinero para el doctor."<<endl<<endl;
                }
                else {
                    cout<<"Eres tan pobre que el doctor no te cobra por esta vez."<<endl<<endl;
                }
            }
        }

        ronda++;
    }
}

void Menu::actualizar_diccionario()
{
    for (int i=0;i<indice.size();i++) {
        User aux=indice.getAt(i);
        for (int x=0;x<diccionario.size();x++) {
            if(diccionario.at(x)->getLlaveSec()==aux.getUsername()){
                aux.setDireccion_personaje(diccionario.at(x)->getPos());
                break;
            }
        }
        indice.modificarAt(i,aux);
    }
}
