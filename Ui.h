#pragma once
#include "Repository.h"
#include "Controller.h"
#include "Oferta.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <exception>
#include "exceptii.h"
class Ui
{
public:
	/*
	* afiseaza optiunile de meniu
	*/
	void creeaza_meniu(const int nr);

	/*
	* meniul propriu-zis al aplicatiei
	*/
	void meniu();

	/*
	* citeste datele unei oferte si o baga in lista daca este valida
	* rep- o referinta la obiectul Repository
	* cont- o referinta la obiectul Controller
	*/
	void adaugare_oferta(AbstractRepo& rep,Controller& cont);
	
	/*
	* sterge ofertele din lista
	* rep- o referinta la obiectul Repository
	* cont- o referinta la obiectul Controller
	*/

	void stergere_oferta(AbstractRepo& rep,Controller& cont);

	/*
	* modifica ofertele din lista
	* rep- o referinta la obiectul Repository
	* cont- o referinta la obiectul Controller
	*/
	void modificare_oferta(AbstractRepo& rep, Controller& cont);

	/*
	* cauta ofertele in lista
	* rep- o referinta la obiectul Repository
	* cont- o referinta la obiectul Controller
	*/
	void cautare_oferta(AbstractRepo& rep, Controller& cont);

	/*
	* afiseaza o oferta din lista
	* of- referinta la obiectul Oferta
	*/
	void afiseaza_oferta(const Oferta& of);

	/*
	* afiseaza toate ofertele din lista
	* rep- o referinta la obiectul Repository
	* cont- o referinta la obiectul Controller
	*/
	void afisare_toate(vector<Oferta>& rep);

	/*
	* aplica un filtru asupra listei
	* rep- o referinta la obiectul Repository
	* cont- o referinta la obiectul Controller
	*/

	void filtrare_lista(AbstractRepo& rep,const Controller& cont);

	/*
	* sorteaza lista dupa un anumit criteriu
	* rep- o referinta la obiectul Repository
	* cont- o referinta la obiectul Controller
	*/
	void sortare_lista(AbstractRepo& rep,const Controller& cont);

    /*
     * aceasta functie este meniul principal al cosului de oferte
     * wish de tip Wishlist
     * rep de tip Repository
     * cont de etip Controller
     */
    void meniu_wishlist(Wishlist &wish, AbstractRepo &rep, Controller &cont);

    /*
	 * aceasta functie adauga un obiect in cos
	 * wish de tip Wishlist
	 * rep de tip Repository
	 * cont de etip Controller
	 */
    void adauga_wishlist(Wishlist &wish, AbstractRepo &rep, Controller &cont);

    /*
	 * aceasta functie sterge toate ofertele din cos
	 * wish de tip Wishlist
	 * cont de etip Controller
	 */
    void sterge_tot_wish(Wishlist &wish, Controller &cont);

    /*
	 * aceasta functie afiseaza toate ofertele din cos
	 * wish de tip Wishlist
	 * cont de etip Controller
	 */
    void afiseaza_wishlist(Wishlist &wish, Controller &cont);

    /*
	 * aceasta functie afiseaza meniul cosului de oferte
	 * wish de tip Wishlist
	 * cont de etip Controller
	 */
    void creeaza_meniu_wish(const int nr);

    /*
	 * aceasta functie genereaza ofertele unui cos
	 * wish de tip Wishlist
     * rep de tip Repository
	 * cont de etip Controller
	 */
    void genereaza_wish(Wishlist &wish, AbstractRepo &rep, Controller &cont);

    /*
	 * aceasta functie salveaza elementele unui cos intr-un fisier
	 * wish de tip Wishlist
	 * cont de etip Controller
	 */
    void salveaza_wish_fisier(Wishlist &wish, Controller &cont);

    /*
     * aceasta functie organizeaza ofertele dupa tip
     */
    void afiseaza_dictionar(AbstractRepo &rep, Controller &cont);

    /*
     * aceasta functie este meniul de undo
     */
    void do_undo(Controller &cont);
};

