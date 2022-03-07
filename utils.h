#pragma once
#include "Oferta.h"
#include <string>

/*
* compara destinatia unei oferte cu un string pt filtru
* of-o referinta la obiectul Oferta
* filt de tip string
* true daca sunt egale, false in caz contrar
*/ 
bool compara_destinatie(const Oferta& of,const std::string& filt);

/*
* compara pretul unei oferte cu unul pt filtru
* of-o referinta la obiectul Oferta
* filt de tip string
* true daca sunt egale, false in caz contrar
*/
bool compara_pret(const Oferta& of, const std::string& filt);

/*
* compara destinatia a doua oferte
* of,of1 - o referinta la obiectele Oferta
* true daca destinatia primei oferte este mai mare decat a doua, false in caz contrar
*/
bool compara_oferta_destinatie(const Oferta& of,const Oferta& of1);

/*
* compara denumirea a doua oferte
* of,of1 - o referinta la obiectele Oferta
* true daca denumirea primei oferte este mai mare decat a doua, false in caz contrar
*/
bool compara_oferta_denumire(const Oferta& of, const Oferta& of1);

/*
* compara tipul si pretul a doua oferte
* of,of1 - o referinta la obiectele Oferta
* true daca tipul si pretul primei oferte este mai mare decat a doua, false in caz contrar
*/
bool compara_oferta_tip_si_pret(const Oferta& of, const Oferta& of1);

class Figuri{
private:
    int iX;
    int iY;
    int lung;
    int lat;

public:
    ///constructor default
    Figuri()=default;
    ///constructor personalizat
    Figuri(int incX,int incY,int lung,int lat): iX{incX},iY{incY},lung{lung},lat{lat}{};

    ///returneaza coordonata X a primului punct a figurii, de tip int
    int get_X(){return iX;}

    ///returneaza coordonata Y a primului punct a figurii, de tip int
    int get_Y(){return iY;}

    ///returneaza lungimea figurii, de tip int
    int get_lung(){return lung;}

    ///returneaza latimea figurii, de tip int
    int get_lat(){return lat;}
};