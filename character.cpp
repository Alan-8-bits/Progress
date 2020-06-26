#include "character.h"

string Character::getNombre() const
{
    return nombre;
}

void Character::setNombre(const string &value)
{
    nombre = value;
}

Character::Character(string nombre, string sexo, string team, int exp, int vida,
                     int dinero, string nivel, int acertar, int critico, Historial his,
                     Inventario inv, Objeto blin, Arma prim, Arma sec)
{
    this->nombre=nombre;
    this->sexo=sexo;
    this->team=team;

    this->experiencia=exp;
    this->vida=vida;
    this->dinero=dinero;
    this->nivel=nivel;

    this->habilidad_acertar=acertar;
    this->habilidad_critico=critico;

    this->historial=his;
    this->inventario=inv;

    this->blindaje=blin;

    this->primaria=prim;
    this->secundaria=sec;
}

Character::Character()
{
    nombre="Unknown";
    sexo="Diario";
    team="ND";

    experiencia=0;
    vida=100;
    dinero=0;
    nivel=calcular_nivel();

    habilidad_acertar=30;
    habilidad_critico=5;

    Objeto blindaje("Ropa","Blindaje",0);
    this->blindaje=blindaje;

    Arma revolver("Revolver Oxidado",10,5,"Canion basico","Canion de revolver");
    Arma escopeta("Escopeta vieja",50,1,"Canion basico","Canion de escopeta");
    primaria=revolver;
    secundaria=escopeta;
}

string Character::calcular_nivel()
{
    if(experiencia<25)
        return "Pelele";
    if(experiencia<50)
        return "Aprendiz";
    if(experiencia<75)
        return "Pistolero";
    if(experiencia<100)
        return "Experto";
    if(experiencia==100)
        return "Leyenda";
    if(experiencia>100){
        return "Hacker";
    }

    return "";
}

string Character::to_string()
{
    stringstream ss;
    ss<<nombre<<" | "<<sexo<<" | "<<experiencia<<" | "<<team<<endl;
    return ss.str();
}

Inventario::Inventario()
{

}

Arma::Arma()
{

}

Arma::Arma(string nombre, int danio, int cadencia,string nom_c,string nom_t)
{
    Objeto canion(nom_c,nom_t,danio);
    //Objeto tambor(nom_t,"Tambor",cadencia);

    this->nombre=nombre;
    this->canion=canion;
    //this->tambor=tambor;
    this->danio=this->canion.nivel;
    this->cadencia=cadencia;
}

Objeto::Objeto(string nombre, string tipo, int nivel)
{
    this->nombre=nombre;
    this->tipo=tipo;
    this->nivel=nivel;
}

Objeto::Objeto()
{

}

Historial::Historial()
{

}

Historial::Historial(int asesinatos, int misiones)
{
    this->asesinatos=asesinatos;
    this->misiones_completadas=misiones;
}

void ElemDiccionario::setPos(int value)
{
    pos = value;

}

int ElemDiccionario::getPos()
{
    return pos;
}

string ElemDiccionario::getLlaveSec() const
{
    return llaveSec;
}

void ElemDiccionario::setLlaveSec(const string &value)
{
    llaveSec = value;
}

ElemDiccionario::ElemDiccionario()
{
    pos=-1;
}

ElemDiccionario::ElemDiccionario(string secundaria, int pos)
{
    this->llaveSec = secundaria;
    this->pos = pos;
}
