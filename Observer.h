#pragma once
#include <vector>
class Suspect{

public:
    ///treuie implementata
    virtual void fugi()=0;
};

class FBI {

private:
    vector<Suspect*>lista_suspecti;
public:
    /*
     * aceasta functie se ocupa de notificarea tuturor suspectilor
     * NU are parametri
     * Nu returneaza nimic
     */
    void aresteaza(){
        for (const auto& el: lista_suspecti) {
            el->fugi();
        }
    }

    /*
     * aceasta functie adauga un suspect in baza de date
     * crima de tip Suspect
     * Nu returneaza nimic
     */
    void adauga_suspect(Suspect* crima){
        lista_suspecti.push_back(crima);
    }

    /*
     * aceasta functie sterge un suspect din baza de date
     * crima de tip Suspect
     * Nu returneaza nimic
     */
    void dosar_inchis(Suspect* crima){
        lista_suspecti.erase(std::remove(begin(lista_suspecti), end(lista_suspecti),crima),lista_suspecti.end());
    }
};