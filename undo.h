#pragma once
#include "Repository.h"
#include "Oferta.h"

class ActiuneUndo{
public:
    virtual void doUndo()=0;
    virtual ~ActiuneUndo(){};
};

class UndoAdauga: public ActiuneUndo{
private:
    AbstractRepo& rep;
    Oferta oferta_adaugata;
public:
    /*
     * constructor de clasa
     */
    UndoAdauga(AbstractRepo& rep, Oferta& of): rep{rep}, oferta_adaugata{of}{};
    /*
    * functia aceasta face operatia de undo
    * ExceptieRepository daca obiectul adaugat nu exista in lista
    */
    void doUndo(){
        rep.sterge(oferta_adaugata.get_denumire());
    }
};

class UndoSterge: public ActiuneUndo{
private:
    AbstractRepo& rep;
    Oferta oferta_stearsa;
public:
    /*
     * constructor de clasa
     */
    UndoSterge(AbstractRepo& rep, const Oferta& of): rep{rep}, oferta_stearsa{of}{};
    /*
    * functia aceasta face operatia de undo
    */
    void doUndo(){
        rep.adauga(oferta_stearsa);
    }
};

class UndoModifica: public ActiuneUndo{
private:
    AbstractRepo& rep;
    Oferta oferta_stearsa;
    Oferta oferta_adaugata;
public:
    /*
     * constructor de clasa
     */
    UndoModifica(AbstractRepo& rep, const Oferta& of_ad, const Oferta& of_st): rep
    {rep}, oferta_adaugata{of_ad},oferta_stearsa{of_st}{};
    /*
     * functia aceasta face operatia de undo
     * ExceptieRepository daca obiectul modificat nu se gaseste in lista
     */
    void doUndo()override{
        rep.adauga(oferta_stearsa);
        rep.sterge(oferta_adaugata.get_denumire());
    }
};

