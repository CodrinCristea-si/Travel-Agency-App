#pragma once
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include<QMessageBox>
#include <QListWidget>
#include <QCloseEvent>
#include <QTableWidget>
#include <QSpinBox>
#include <qlistwidget.h>
#include <qobject.h>
#include <qstring.h>
#include <qdebug.h>
#include <QPainter>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "Oferta.h"
#include "Controller.h"
#include "Repository.h"
#include "wishlist.h"
#include "Observer.h"
#include "utils.h"
#include "model.h"
using std::string;using std::vector;using std::pair;

class MeniuAplicatie: public QWidget, public Suspect{
    friend class Casuta4LineEdit;
    friend class CasutaLineEdit2Butoane;
private:
    Controller& cont;
    Repository& rep;
    Wishlist& wish;
private:
    QWidget* WidMeniu;
    QWidget* WidCautareBara;
    QWidget* WidCautare;
    QWidget* WidAfisare;
    QWidget* WidButoaneMeniu;
    QWidget* WidMeniuStg;
    QHBoxLayout* LyCautare;
    QHBoxLayout* LyMeniu;
    QVBoxLayout* LyAfisare;
    QVBoxLayout* LyMeniuButoane;
    QVBoxLayout* LyMeniuButoaneCos;
    QVBoxLayout* LyMeniuStg;
    QLabel* DenLabCaut;
    QLabel* DenOfLabAf;
    QLineEdit* LineCautare;
    QPushButton* ButonCautare;
    QFormLayout* FormCautare;

    //ModelLista* modelLista;
    QListWidget* ListaAfisare;

    QPushButton* ButonAdauga;
    QPushButton* ButonSterge;
    QPushButton* ButonModifica;
    QPushButton* ButonIesire;
    QPushButton* ButonTabel;
    QPushButton* ButonUndo;
    QPushButton* ButonCos;

    QPushButton* ButonAdaugaCos;
    QPushButton* ButonGolireCos;
    QPushButton* ButonGenerareCos;
    QPushButton* ButonWriteCos;
    QPushButton* ButonWriteCosV2;
    QPushButton* ButonReadCos;

    QTableWidget* tabel;
    QListWidgetItem* ultim;

public:
    ///aceasta functie este constructorul clasei, el se ocupa de desenare,conectare si afisarea datelor
    MeniuAplicatie(Controller& cont, Repository& rep,Wishlist& wish): cont{cont},rep{rep}, wish{wish}{
        //MeniuAplicatie::ListaAfisare=nullptr;
        cont.citeste_fisier_repo(rep,"repo.txt");
        initializare();
        conectare();
        // afisare_totala();
        afisare(cont.get_lista_repo(rep));

}
    /*
     * aceasta functie afiseaza denumirile ofertelor intr-un mic chenar in aplicatia principala
     * lista_oferte este un vector de tip Oferta
     * Nu returneaza nimic
     */
    void afisare(vector<Oferta>& lista_oferte);

    /*
    * aceasta functie afiseaza toate datele intr-un format tabelar
    * Nu are parametri
    * Nu returneaza nimic
    */
    void afisare_totala();

    /*
    * aceasta functie extrage datele din casute, le valideaza si dupa adauga oferta in lista
    * Nu are parametri
    * Nu returneaza nimic
    */
    void adaugare();

    /*
    * aceasta functie sterge o oferta din lista daca denumirea este valida
    * Nu are parametri
    * Nu returneaza nimic
    */
    void sterge();

    /*
    * aceasta functie extrage datele din casute, le valideaza si dupa modifica oferta in lista
    * Nu are parametri
    * Nu returneaza nimic
    */
    void modifica();

    /*
     * aceatsa functie este un raspsuns al modificare datelor intr-o alta fereasca si actualizarea acestora in fereastra curenta
     * Nu are parametri
     * Nu returneaza nimic
     */
    void fugi() override{
        afisare(cont.get_lista_repo(rep));
        //afisare_totala();
        //afisare_tabel(cont.get_lista_repo(rep),tabel);
    }

private:

    /*
    * aceasta functie se ocupa de desenarea grafica a aplicatiei
    * Nu are parametri
    * Nu returneaza nimic
    */
    void initializare();

    /*
    * aceasta functie se ocupa de conectarea butoanelor si a evenimentelor din aplicatie
    * Nu are parametri
    * Nu returneaza nimic
    */
    void conectare();

    /*
    * aceasta functie ocupa de desenarea, preluarea si salvarea datelor din partea de modificare
    * denumire de tip string
    * Nu returneaza nimic
    */
    void modificare_casuta(string denumire);

    /*
    * aceasta functie ocupa de desenarea, preluarea si salvarea datelor din partea de cautare si selecte tabel
    * denumire de tip string
    * Nu returneaza nimic
    */
    void casuta_cautare_coloana(string &denumire,bool cu_modificare=true);

    /*
    * aceasta functie ocupa de afisarea tabelara a tuturor datelor
    * lista_oferte de tip vector de Oferte
    * tabel este un QTableWidget
    * Nu returneaza nimic
    */
    void afisare_tabel(vector<Oferta> lista_oferte, QTableWidget *tabel);

    /*
    * aceasta functie este meniul de filtrare a datelor
    * Nu are parametri
    * Nu returneaza nimic
    */
    void filtrare();

    /*
    * aceasta functie se ocupa de filtrarea datelor dupa destinatie
    * Nu are parametri
    * Nu returneaza nimic
    */
    void filtrare_destinatie();

    /*
    * aceasta functie se ocupa de filtrarea datelor dupa tip
    * Nu are parametri
    * Nu returneaza nimic
    */
    void filtrare_tip();

    /*
    * aceasta functie se ocupa de filtrarea datelor dupa pret
    * Nu are parametri
    * Nu returneaza nimic
    */
    void filtrare_pret();

    /*
    * aceasta functie se ocupa de sortare datelor dupa un anumit criteriu
    * Nu are parametri
    * Nu returneaza nimic
    */
    void sortare();

    /*
    * aceasta functie se ocupa de adaugarea unei oferte in cos
    * Nu are parametri
    * Nu returneaza nimic
    */
    void adauga_cos();

    /* aceasta functie se ocupa cu generarea unui cos
    * Nu are parametri
    * Nu returneaza nimic
    */
    void generare_cos();
};

class Cos_GUI: public QWidget, public Suspect{

private :

    Repository& rep;
    Controller& cont;
    Wishlist& wish;

    bool invizibil=true;

private :

    QWidget *widTotal;
    QHBoxLayout * lyTotal;

    QVBoxLayout* lyButoane;
    QVBoxLayout* lyCosTabel;
    QVBoxLayout* lyDispTabel;

    QPushButton* ButonAdauga;
    QPushButton* ButonGolire;
    QPushButton* ButonGenerare;
    QPushButton* ButonAfisare;
    QPushButton* ButonReAfisare;
    QPushButton* ButonWrite;
    QPushButton* ButonWriteV2;
    QPushButton* ButonRead;
    QPushButton* ButonExporta;
    QPushButton* ButonIesire;

    QLabel* statusCos;
    QLabel* statusDisp;

    QListWidget* listaCos;
    QListWidget* listaDisp;

public:

    ///constructor
    Cos_GUI(Repository& rep, Controller& cont, Wishlist& wish): rep{rep}, cont{cont}, wish{wish}{
        initializare();
        conectare();
        afisare_cos();
    };

    /*
    * aceasta functie se ocupa de adaugarea unei oferte in cos
    * Nu are parametri
    * Nu returneaza nimic
    */
    void adauga_cos();

    /*
    * aceasta functie se ocupa de afisarea datelor din cos intr-un format listat
    * Nu are parametri
    * Nu returneaza nimic
    */
    void afisare_cos();

    /* aceasta functie se ocupa de afisarea datelor din cos intr-un format tabelar
    * Nu are parametri
    * Nu returneaza nimic
    */
    void afisare_disponibil();

    /* aceasta functie se ocupa cu generarea unui cos
    * Nu are parametri
    * Nu returneaza nimic
    */
    void generare_cos();

    /* aceasta functie se ocupa cu salvarea unui cos intr-un fisier
    * Nu are parametri
    * Nu returneaza nimic
    */
    void exporta_cos();

    /* aceasta functie este un quick acces petru elementele din liste
    * denumire de tip string
     * cu_modificare- de tip bool
    * Nu returneaza nimic
    */
    void afisare_date(string& denumire,bool cu_modificare=false);

    /*
     * aceatsa functie este un raspsuns al modificare datelor intr-o alta fereasca si actualizarea acestora in fereastra curenta
     * Nu are parametri
     * Nu returneaza nimic
     */
    void fugi() override{
        afisare_cos();
        afisare_disponibil();
    }

private:

    /* aceasta functie se ocupa cu partea de desenare grafica a aplicatiei
    * Nu are parametri
    * Nu returneaza nimic
    */
    virtual void initializare();

    /* aceasta functie se ocupa cu conectarea butoanelor cu elementele corespunzatoare
    * Nu are parametri
    * Nu returneaza nimic
    */
    virtual void conectare();

    /* aceasta functie aloca spatiu in memorie pentru elementele grafice
    * Nu are parametri
    * Nu returneaza nimic
    */
    void alocare();
};

class CosCRUDGUI: public QWidget,public Suspect{

private:
    Repository& rep;
    Controller& cont;
    Wishlist& wish;

private:
    QWidget* mainWid;
    QHBoxLayout* mainLy;

    QVBoxLayout* butLy;
    QPushButton* butGol;
    QPushButton* butGen;

    ModelLista* model;
    QListView* lista;


public:
    ///constructor
    CosCRUDGUI(Repository &rep, Controller &cont, Wishlist &wish):rep{rep}, cont{cont}, wish{wish} {
        initializare();
        conectare();
        //afisare_cos();
    };

    /*
    * aceasta functie se ocupa de afisarea datelor din cos intr-un format listat
    * Nu are parametri
    * Nu returneaza nimic
    */
    void afisare_cos();

    /* aceasta functie se ocupa cu generarea unui cos
    * Nu are parametri
    * Nu returneaza nimic
    */
    void generare_cos();

    /*
     * aceatsa functie este un raspsuns al modificare datelor intr-o alta fereasca si actualizarea acestora in fereastra curenta
     * Nu are parametri
     * Nu returneaza nimic
     */
    void fugi()override{
        //afisare_cos();
        model->set_Oferte(cont.get_lista_repo(wish));
    }

private:

    /* aceasta functie se ocupa cu partea de desenare grafica a aplicatiei
    * Nu are parametri
    * Nu returneaza nimic
    */
    void initializare();

    /* aceasta functie se ocupa cu conectarea butoanelor cu elementele corespunzatoare
    * Nu are parametri
    * Nu returneaza nimic
    */
    void conectare();

};

class CosReadOnlyGUI:public QWidget, public Suspect{

private:
    Repository& rep;
    Controller& cont;
    Wishlist& wish;
    vector<Figuri> lista;

public:
    ///constructor
    CosReadOnlyGUI(Repository &rep, Controller &cont, Wishlist &wish):rep{rep}, cont{cont}, wish{wish} {
        cont.adauga_suspect(this);
        show();
        lista=calculeaza();
        //qDebug()<<QString::number(lista.size())<<"\n";

    };
    /*
     * aceasta functie se ocupa de redesenarea aplicatiei in caz de modificari
     * ev e tipul de eveniment QPaintEvent
     * Nu returneaza nimic
     */
    void paintEvent(QPaintEvent* ev) override ;

    /*
     * aceatsa functie este un raspsuns al modificare datelor intr-o alta fereasca si actualizarea acestora in fereastra curenta
     * Nu are parametri
     * Nu returneaza nimic
     */
    void fugi() override{
        lista=calculeaza();
        repaint();
    }
private:

    /*
     * aceasta functie calculea za coordonatele figurilor geometrice
     * Nu are parametri
     * Returneaza o lista cu figurile gasite
     */
    vector<Figuri>calculeaza();

    /*
     * Aceasta functie verifica daca o figura nou formata nu se suprapune peste o alta figura existenta
     * lista de tip lista de Figuri
     * fig este de tip Figuri
     * Returneaza true daca fig se suprapune peste o figura existenta, false in caz contrar
     */
    bool fara_coliziuni(vector<Figuri>& lista, Figuri& fig);
};

class CosV2CRUDGUI: public QWidget,public Suspect{

private:
    Repository& rep;
    Controller& cont;
    Wishlist& wish;

private:
    QWidget* mainWid;
    QHBoxLayout* mainLy;

    QVBoxLayout* butLy;
    QPushButton* butGol;
    QPushButton* butGen;

    ModelLista* model;
    QTableWidget* tabel;


public:
    ///constructor
    CosV2CRUDGUI(Repository &rep, Controller &cont, Wishlist &wish):rep{rep}, cont{cont}, wish{wish} {
        initializare();
        conectare();
        afisare_cos();
    };

    /*
    * aceasta functie se ocupa de afisarea datelor din cos intr-un format listat
    * Nu are parametri
    * Nu returneaza nimic
    */
    void afisare_cos();

    /* aceasta functie se ocupa cu generarea unui cos
    * Nu are parametri
    * Nu returneaza nimic
    */
    void generare_cos();

    /*
     * aceatsa functie este un raspsuns al modificare datelor intr-o alta fereasca si actualizarea acestora in fereastra curenta
     * Nu are parametri
     * Nu returneaza nimic
     */
    void fugi()override{
        afisare_cos();
        //model->set_Oferte(cont.get_lista_repo(wish));
    }

private:

    /* aceasta functie se ocupa cu partea de desenare grafica a aplicatiei
    * Nu are parametri
    * Nu returneaza nimic
    */
    void initializare();

    /* aceasta functie se ocupa cu conectarea butoanelor cu elementele corespunzatoare
    * Nu are parametri
    * Nu returneaza nimic
    */
    void conectare();

};