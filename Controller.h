#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Oferta.h"
#include "utils.h"
#include "Repository.h"
#include "exceptii.h"
#include "wishlist.h"
#include "undo.h"
#include <memory>
#include "Observer.h"
using std:: vector;using std::cout;using std::endl;
typedef bool(*FuncFilt)(const Oferta&,const std::string&);
typedef bool(*FuncSort)(const Oferta&,const Oferta&);

class Controller: public FBI
{
	friend class Repository;

private:
    std::vector<std::unique_ptr<ActiuneUndo>>undo_lista;

public:
    Controller()=default;
    Controller(const Controller& cont)=delete;
	/*
	* returneaza numarul de oferte din lista
	*/
	int get_numar_oferte(AbstractRepo& rep) {
		return rep.numar_elemente();
	}
    /*
    * returneaza liste de oferte din repo
    */
	vector<Oferta>& get_lista_repo(AbstractRepo& rep){
	    return rep.get_lista();
	}
	/*
	*valideaza datele ueni oferte
	* returneaza 0 daca obiectul este valid
	* arunca:
	* 1-pret negativ
	* 2-denumire vida
	* 3-destinatie vida
	* 4-tip vid
	* 5-denumirea contine cifre
	* 6-destinatie contine cifre
	* 7-tipul contine cifre
	* 8-oferta e deja in lista
	*/
	int validare(AbstractRepo& rep, const std::string& denumire, const std::string& destinatie, const std::string& tip, const std::string& pret)const;

	/*
	* adauga o oferta in lista
	* rep- referinta la lista de oferte
	* denumire,destinatie, tip- de tip string
	* tip de tip float
	*/
	void adauga_in_lista(AbstractRepo& rep, const std::string& denumire, const std::string& destinatie, const std::string& tip, const float pret);

	/*
	* sterge o oferta din lista
	* rep- referinta la lista de oferte
	* denumire- de tip string
	*/
	void sterge_din_lista(AbstractRepo& rep, const std::string& denumire);

	/*
	* cauta o oferta in lista
	* rep- referinta la lista de oferte
	* denumire- de tip string
	*/
	int cauta_in_lista(AbstractRepo& rep, const std::string& denumire);

	/*
	* modifica un camp dintr-o oferta din lista  
	* rep- referinta la lista de oferte
	* denumire, schimb- de tip string
	* optiune de tip int
	*/
	void modifica(AbstractRepo& rep, const std::string& denumire, const int optiune, const std::string& schimb);

	/*
	* returneaza o referinta la obiectul oferta de pe o anumita pozitie din lista
	* rep- referinta la lista de oferte
	* poz de tip int
	*/
	Oferta& oferta_cu_poz(AbstractRepo& rep, const int poz);

	/*
	* returneaza o lista care contine elemente ce satisfac un anumit filtru
	* rep- referinta la lista de oferte
	* filt- de tip string
	* funct este o functie de comparare care are 2 parametri
	*/
	vector<Oferta> filtru(AbstractRepo& rep, const std::string& filt, FuncFilt func)const;

	/*
	* returneaza o lista care contine elementele sortate dupa un anumit criteriu
	* rep- referinta la lista de oferte
	* rev- de tip bool
	* funct este o functie de comparare care are 2 parametri de tip Oferta
	*/
	vector<Oferta> sortare(AbstractRepo& rep, const bool rev, FuncSort func)const;

	/*
	 * Aceasta functie sterge toate elementele din cos
	 * wish de tip Wishlist
	 * Nu returneaza nimic
	 */
    void sterge_tot_wishlist(Wishlist &wish);

    /*
	 * Aceasta functie salveaza toate datele din cos intr-un fisier de un anumit tip
	 * wish de tip Wishlist
     * fis- de tip string
	 * Nu returneaza nimic
	 */
    void salveaza_fisier_wish(Wishlist &wish, string fis);
    /*
	 * Aceasta functie adauga o oferta dupa denumire in cos
	 * wish de tip Wishlist
     * of- o referinta catre obicetul oferta
	 * Nu returneaza nimic
	 */
    void adauga_oferta_in_wishlist(Wishlist &wish, const Oferta &of);

    /*
	 * Aceasta functie alege la intampla elementele din lista de oferte si le pune in cos
	 * wish de tip Wishlist
     * rep de tip Repository
     * nr_of de tip int
	 * Nu returneaza nimic
	 */
    void genereaza_wishlist(Wishlist &wish, AbstractRepo &rep, int nr_of);

    /*
	 * Aceasta functie salveaza datele din lista de oferte intr-un fisier
	 * rep de tip Repository
     * fis de tip string
	 * Nu returneaza nimic
	 */
    void salveaza_fisier_repo(AbstractRepo &rep, string fis);

    /*
	 * Aceasta functie citeste datele dintr-un fisier si le adauga in lista de oferte
	 * rep de tip Repository
     * fis de tip string
	 * Nu returneaza nimic
	 */
    void citeste_fisier_repo(AbstractRepo &rep, string fis);

    /*
     * aceasta functie organizeaza ofertele dupa tip
     * rep de tip Repository
     */
    std::map<string, std::pair<string, int>> dictionar(AbstractRepo &rep);

    /*
     * aceasta functie face operatia de undo
     * ExceptieRepository daca nu se mai poate face undo
     */
    void undo();
};