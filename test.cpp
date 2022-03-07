#include "test.h"
#include <iostream>
#include <stdexcept>
#include <memory>

void test_domain() {
	Oferta of("bomba","roma","all_inclusive",10);
	///Getter
	assert(of.get_denumire() == "bomba");
	assert(of.get_destinatie() == "roma");
	assert(of.get_tip() == "all_inclusive");
	assert(of.get_pret() == 10);

	///Setter
	of.set_denumire("nou");
	assert(of.get_denumire() == "nou");
	of.set_destinatie("inima_mea");
	assert(of.get_destinatie() == "inima_mea");
	of.set_tip("individual");
	assert(of.get_tip() == "individual");
	of.set_pret(19.5);
	assert(of.get_pret() == 19.5);

}

void test_repository() {
	Repository rep;
	assert(rep.numar_elemente() == 0);
	Oferta of("new", "mama", "mancare", 10);
	//std::cout << "aici da -1" << std::endl;
	rep.adauga(of);
	//std::cout << "aici da 0" << std::endl;
	assert(rep.numar_elemente() == 1);
	assert(rep.get_oferta_cu_pozitie(0).get_denumire() == "new");
	//std::cout << "aici da 1" << std::endl;
	assert(rep.get_oferta_cu_pozitie(0).get_destinatie() == "mama");
	assert(rep.get_oferta_cu_pozitie(0).get_tip() == "mancare");
	assert(rep.get_oferta_cu_pozitie(0).get_pret() == 10);

	int poz = rep.cauta("new");
	assert(poz != -1);
	assert(rep.get_oferta_cu_pozitie(poz).get_denumire() == "new");
	assert(rep.get_oferta_cu_pozitie(poz).get_destinatie() == "mama");
	assert(rep.get_oferta_cu_pozitie(poz).get_tip() == "mancare");
	assert(rep.get_oferta_cu_pozitie(poz).get_pret() == 10);
	poz = rep.cauta("aici");
	assert(poz == -1);
	try {
		rep.sterge("koew");
		assert(false);}
	catch(ExceptieRepository ex){
	    assert(ex.get_mesaj_eroare()=="Pozitie invalida!");
		assert(true);
	}
	rep.sterge("new");
	poz = rep.cauta("new");
	assert(poz == -1);
	try {
		rep.sterge("new");
		assert(false);}
	catch (ExceptieRepository ex) {
        assert(ex.get_mesaj_eroare()=="Pozitie invalida!");
		assert(true);
	}
	Oferta of1("ala", "bala", "portocala", 10);
	rep.adauga(of);
	rep.adauga_pe_pozitie(0, of1);
	poz = rep.cauta("ala");
	assert(rep.get_oferta_cu_pozitie(poz).get_denumire() == "ala");
	assert(rep.get_oferta_cu_pozitie(poz).get_destinatie() == "bala");
	assert(rep.get_oferta_cu_pozitie(poz).get_tip() == "portocala");
	assert(rep.get_oferta_cu_pozitie(poz).get_pret() == 10);
	std::cout << "repo" << std::endl;
}

void test_controller_ascm() {
	Repository rep;
	assert(rep.numar_elemente() == 0);
	Controller cont;
	cont.adauga_in_lista(rep, "macarena", "uk", "refugiat", 15.5);
	//std::cout << "aici da 1" << std::endl;
	assert(rep.numar_elemente() == 1);
	int poz = cont.cauta_in_lista(rep, "macarena");
	//std::cout << "aici da 2" << std::endl;
	assert(poz != -1);
	assert(rep.get_oferta_cu_pozitie(poz).get_denumire() == "macarena");
	//std::cout << "aici da 3" << std::endl;
	assert(rep.get_oferta_cu_pozitie(poz).get_destinatie() == "uk");
	assert(rep.get_oferta_cu_pozitie(poz).get_tip() == "refugiat");
	assert(rep.get_oferta_cu_pozitie(poz).get_pret() == 15.5);
	cont.modifica(rep, "macarena", 1, "nou");
	//std::cout << "aici da 4" << std::endl;
	cont.modifica(rep, "nou", 2, "roma");
	cont.modifica(rep, "nou", 3, "acum");
	cont.modifica(rep, "nou", 4, "200.8");
	assert(rep.numar_elemente() == 1);
	poz = cont.cauta_in_lista(rep, "macarena");
	assert(poz == -1);
	poz = cont.cauta_in_lista(rep, "nou");
	assert(poz != -1);
	Oferta of1 = cont.oferta_cu_poz(rep, poz);
	assert(of1.get_denumire() == "nou");
	assert(of1.get_destinatie() == "roma");
	assert(of1.get_tip() == "acum");
	//std::cout << rep.get_oferta_cu_pozitie(poz).get_pret() << std::endl;
	assert(of1.get_pret() == (float)200.8);
	cont.sterge_din_lista(rep, "nou");
	assert(rep.numar_elemente() == 0);
	poz = cont.cauta_in_lista(rep, "nou");
	std::cout << "ascm" << std::endl;
	assert(poz == -1);
}

void test_controller_filtru() {
	Repository rep;
	Controller cont;
	cont.adauga_in_lista(rep, "macarena", "uk", "refugiat", 15.5);
	std::cout << "aici da 0" << std::endl;
	cont.adauga_in_lista(rep, "nou", "uk", "all", 100);
	std::cout << "aici da 1" << std::endl;
	cont.adauga_in_lista(rep, "dada", "roma", "nush", 17.5);
	std::cout << "aici da 2" << std::endl;
	cont.adauga_in_lista(rep, "ma", "sua", "poc", 55.5);
	std::cout << "aici da 3" << std::endl;
	///Filtru dupa destinatie
    vector<Oferta> filt = cont.filtru(rep, "uk", compara_destinatie);
	std::cout << "aici da 4" << std::endl;
	assert(filt.size() == 2);
	Oferta& of = filt.at(0);
	Oferta& of1 =filt.at(1);
	std::cout << "aici da 5" << std::endl;
	assert(of.get_denumire() == "macarena");
	assert(of.get_destinatie() == "uk");
	assert(of.get_tip() == "refugiat");
	assert(of.get_pret() == (float)15.5);

	assert(of1.get_denumire() == "nou");
	assert(of1.get_destinatie() == "uk");
	assert(of1.get_tip() == "all");
	assert(of1.get_pret() == 100);

    vector<Oferta> filt1 = cont.filtru(rep, "roma", compara_destinatie);
	assert(filt1.size() == 1);
	of = filt1.at(0);
	assert(of.get_denumire() == "dada");
	assert(of.get_destinatie() == "roma");
	assert(of.get_tip() == "nush");
	assert(of.get_pret() == (float)17.5);

	///Filtru dupa pret
    vector<Oferta> filt2 = cont.filtru(rep, "20", compara_pret);
	assert(filt2.size() == 2);
	of =filt2.at(0);
	of1 = filt2.at(1);

	assert(of.get_denumire() == "macarena");
	assert(of.get_destinatie() == "uk");
	assert(of.get_tip() == "refugiat");
	assert(of.get_pret() == (float)15.5);

	assert(of1.get_denumire() == "dada");
	assert(of1.get_destinatie() == "roma");
	assert(of1.get_tip() == "nush");
	assert(of1.get_pret() == (float)17.5);

    vector<Oferta> filt3 = cont.filtru(rep, "10", compara_pret);
	assert(filt3.size() == 0);
	std::cout << "filtru" << std::endl;
}

void test_controller_sort() {
	Repository rep;
	Controller cont;
	cont.adauga_in_lista(rep, "nou", "ukb", "all", 100);
	cont.adauga_in_lista(rep, "macarena", "uka", "all", 15.5);
	cont.adauga_in_lista(rep, "ma", "sua", "poc", 55.5);
	cont.adauga_in_lista(rep, "dada", "roma", "poc", 17.5);

	std::vector<Oferta> sorta = cont.sortare(rep, false, compara_oferta_destinatie);
	//std::cout << sorta.at(0).get_denumire() << std::endl;
	//std::cout << sorta.at(1).get_denumire() << std::endl;
	//std::cout << sorta.at(2).get_denumire() << std::endl;
	//std::cout << sorta.at(3).get_denumire() << std::endl;
	//std::cout << sorta.at(2).get_denumire() << std::endl;
	assert(sorta.at(0).get_denumire() == "dada");
	assert(sorta.at(1).get_denumire() == "ma");
	assert(sorta.at(2).get_denumire() == "macarena");
	assert(sorta.at(3).get_denumire() == "nou");

    std::vector<Oferta> sorta1 = cont.sortare(rep, true, compara_oferta_denumire);
	assert(sorta1.at(0).get_denumire() == "nou");
	assert(sorta1.at(1).get_denumire() == "macarena");
	assert(sorta1.at(2).get_denumire() == "ma");
	assert(sorta1.at(3).get_denumire() == "dada");

    std::vector<Oferta> sorta2 = cont.sortare(rep, false, compara_oferta_tip_si_pret);
	assert(sorta2.at(0).get_denumire() == "macarena");
	assert(sorta2.at(1).get_denumire() == "nou");
	assert(sorta2.at(2).get_denumire() == "dada");
	assert(sorta2.at(3).get_denumire() == "ma");
	std::cout << "sort" << std::endl;
}

void test_validare() {
	Repository rep;
	Controller cont;
	cont.adauga_in_lista(rep, "nou", "ukb", "all", 100);
	try {
		cont.validare(rep, "", "a", "b", std::to_string(7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 2);
		assert(true);
	}
	try {
		cont.validare(rep, "a", "", "b", std::to_string(7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 3);
		assert(true);
	}
	try {
		cont.validare(rep, "a", "b", "", std::to_string(7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 4);
		assert(true);
	}
	try {
		cont.validare(rep, "a7", "a", "b", std::to_string(7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 5);
		assert(true);
	}
	try {
		cont.validare(rep, "a", "7b", "b", std::to_string(7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 6);
		assert(true);
	}
	try {
		cont.validare(rep, "a", "b", "7b", std::to_string(7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 7);
		assert(true);
	}
	try {
		cont.validare(rep, "a", "c", "b", std::to_string(-7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 1);
		assert(true);
	}
	try {
		cont.validare(rep, "nou", "b", "b", std::to_string(7));
		assert(false);}
	catch (const ExceptieValidare& err) {
		assert(err.get_cod() == 8);
		assert(true);
	}
    try {
        cont.validare(rep, "nou", "b", "b", "e");
        assert(false);}
    catch (const ExceptieValidare& err) {
        assert(err.get_cod() == 9);
        assert(err.get_mesaj_eroare()=="Pretul nu trebuie sa contina litere");
        assert(true);
    }
	const int ver=cont.validare(rep, "a", "b", "c", std::to_string(7));
	assert(ver == 0);
	assert(cont.get_numar_oferte(rep) == 1);
	std::cout << "validare" << std::endl;
}

void test_VectorDinamic() {
	VectorDinamic<Oferta> vect;
	Oferta of1{ "a","b","c",1};
	Oferta of2{ "a","b","c",12};
	Oferta of3{ "a","b","c",123};
	Oferta of4{ "a","b","c",1234};
	Oferta of5{ "a","b","c",12345};
	Oferta of6{ "a","b","c",123456};
	vect.push_back(of1);
	vect.push_back(of2);
	vect.push_back(of3);
	vect.push_back(of4);
	vect.push_back(of5);
	vect.push_back(of6);
	assert(vect.size() == 6);
	assert(vect.capacity() == 10);
	vect.erase(3);
	assert(vect.size() == 5);
	assert(vect.capacity() == 5);

	for (const auto& of : vect) {
		assert(of.get_pret() > 0);
	}
	std::cout << "vector dinamic" << std::endl;

	VectorDinamic<Oferta> vect_copy;
	vect_copy= vect;
	assert(vect_copy.size() == 5);
	assert(vect_copy.capacity() == 5);
	assert(vect.size() == 0);
	assert(vect.capacity() == 0);
	vect_copy = vect_copy;
	assert(vect_copy.size() == 5);
	assert(vect_copy.capacity() == 5);
	//vect.push_back(of4);
	//assert(vect_copy.size() == 5);
	//assert(vect_copy.capacity() == 5);
	//assert(vect.size() == 1);
	//assert(vect.capacity() == );
}

void test_wishlist(){
    Repository rep;
    Controller cont;
    Wishlist wish;
    cont.adauga_in_lista(rep, "nou", "ukb", "all", 100);
    cont.adauga_in_lista(rep, "macarena", "uka", "all", 15.5);
    cont.adauga_in_lista(rep, "ma", "sua", "poc", 55.5);
    cont.adauga_in_lista(rep, "dada", "roma", "poc", 17.5);
    cont.adauga_in_lista(rep, "a", "b", "c", 1);
    cont.adauga_in_lista(rep, "d", "e", "f", 2);
    cont.adauga_in_lista(rep, "g", "h", "i", 3);
    cont.adauga_in_lista(rep, "j", "k", "l", 4);
    cont.adauga_in_lista(rep, "m", "n", "o", 5);
    cont.adauga_in_lista(rep, "p", "q", "r", 6);
    cont.adauga_oferta_in_wishlist(wish,rep.get_oferta_cu_pozitie(0));
    assert(wish.numar_elemente()==1);
    cont.adauga_oferta_in_wishlist(wish,rep.get_oferta_cu_pozitie(1));
    assert(wish.numar_elemente()==2);
    cont.sterge_tot_wishlist(wish);
    assert(wish.numar_elemente()==0);
    cont.genereaza_wishlist(wish,rep,9);
    assert(wish.numar_elemente()==9);
    cont.salveaza_fisier_wish(wish,"test1.csv");
    cont.salveaza_fisier_wish(wish,"test1.html");
    Repository rept;
    cont.citeste_fisier_repo(rept,"test2.txt");
    cout<<rept.numar_elemente()<<endl;
    assert(rept.numar_elemente()==2);
    assert(rept.get_oferta_cu_pozitie(0).get_denumire()=="a");
    assert(rept.get_oferta_cu_pozitie(1).get_denumire()=="d");
    vector<Oferta> vect=cont.get_lista_repo(rep);
    assert(vect.size()==10);
    cont.salveaza_fisier_repo(rept,"test.txt");

}
void test_dictionar_controller(){
    Repository rep;
    Controller cont;
    cont.adauga_in_lista(rep, "a", "b", "a", 1);
    cont.adauga_in_lista(rep, "d", "e", "a", 2);
    cont.adauga_in_lista(rep, "g", "h", "a", 3);
    cont.adauga_in_lista(rep, "j", "k", "b", 4);
    cont.adauga_in_lista(rep, "m", "n", "b", 5);
    cont.adauga_in_lista(rep, "p", "q", "c", 6);
    std::map<string,std::pair<string,int>> lista=cont.dictionar(rep);
    assert(lista.size()==3);
    assert(lista["a"].second==3);
    assert(lista["b"].second==2);
    assert(lista["c"].second==1);
}
/*
void test_repo_file(){
    RepositoryFile rep{"test1.txt"};
    Controller cont;
    cont.adauga_in_lista(rep, "a", "b", "a", 1);
    cont.adauga_in_lista(rep, "d", "e", "a", 2);
    Oferta of{"g","h","i",3};
    Oferta of1{"j","k","b",4};
    rep.adauga(of);
    assert(rep.numar_elemente()==3);
    rep.adauga(of1);
    assert(rep.numar_elemente()==4);
    int poz=rep.cauta("d");
    //cout<<poz<<endl;
    assert( poz== 1);
    poz=rep.cauta("ala");
    assert(poz==-1);
    rep.sterge("d");
    assert(rep.numar_elemente()==3);
    try{
        rep.sterge("ala");
        assert(false);
    }
    catch(const ExceptieRepository& err){
        assert(true);
        assert(err.get_mesaj_eroare()=="Pozitie invalida!");
    }
    assert(cont.get_numar_oferte(rep)==3);
    Oferta of2=cont.oferta_cu_poz(rep,1);
    assert(of2.get_denumire()=="g");
    assert(cont.get_lista_repo(rep).size()==3);
    cont.sterge_din_lista(rep,"a");
    cont.sterge_din_lista(rep,"g");
    cont.sterge_din_lista(rep,"j");
    cout<<cont.get_numar_oferte(rep)<<std::endl;
    assert(cont.get_numar_oferte(rep)==0);
}
 */
void test_undo(){
    Repository rep;
    Controller cont;
    cont.adauga_in_lista(rep, "a", "b", "a", 1);
    cont.adauga_in_lista(rep, "d", "e", "a", 2);
    cont.adauga_in_lista(rep, "g", "h", "a", 3);
    assert(cont.get_numar_oferte(rep)==3);
    cont.sterge_din_lista(rep,"g");
    cont.adauga_in_lista(rep, "g", "h", "a", 3);
    cont.modifica(rep,"g",1,"h");
    cont.modifica(rep,"h",2,"g");
    cont.modifica(rep,"h",4,"5");
    cont.undo();
    //cout<<rep.get_oferta_cu_pozitie(2).get_denumire()<<" "<<rep.get_oferta_cu_pozitie(2).get_destinatie()<<" "<<rep.get_oferta_cu_pozitie(2).get_tip()<<" "<<rep.get_oferta_cu_pozitie(2).get_pret()<<endl;
    assert(rep.get_oferta_cu_pozitie(2).get_pret()==3);
    cont.undo();
    //cout<<rep.get_oferta_cu_pozitie(2).get_denumire()<<" "<<rep.get_oferta_cu_pozitie(2).get_destinatie()<<" "<<rep.get_oferta_cu_pozitie(2).get_tip()<<" "<<rep.get_oferta_cu_pozitie(2).get_pret()<<endl;
    assert(rep.get_oferta_cu_pozitie(2).get_destinatie()=="h");
    cont.undo();
    //cout<<rep.get_oferta_cu_pozitie(2).get_denumire()<<" "<<rep.get_oferta_cu_pozitie(2).get_destinatie()<<" "<<rep.get_oferta_cu_pozitie(2).get_tip()<<" "<<rep.get_oferta_cu_pozitie(2).get_pret()<<endl;
    assert(rep.get_oferta_cu_pozitie(2).get_denumire()=="g");
    cont.undo();
    int poz=rep.cauta("g");
    assert(poz==-1);
    assert(rep.numar_elemente()==2);
    cont.undo();
    assert(rep.numar_elemente()==3);
    cont.undo();
    assert(rep.numar_elemente()==2);
    cont.undo();
    assert(rep.numar_elemente()==1);
    cont.undo();
    assert(rep.numar_elemente()==0);
    try{
        cont.undo();
        assert(false);
    }
    catch(const ExceptieRepository& err){
        assert(true);
        assert(err.get_mesaj_eroare()=="Undo nerealizabil!");
    }
}
void test_exception_repo(){
    ExceptionRepo rep{0};
    Controller cont;
    cont.adauga_in_lista(rep, "a", "b", "a", 1);
    cont.adauga_in_lista(rep, "d", "e", "a", 2);
    cont.adauga_in_lista(rep, "g", "h", "a", 3);
    assert(cont.get_numar_oferte(rep)==3);
    cont.sterge_din_lista(rep,"g");
    assert(cont.get_numar_oferte(rep)==2);
    int poz=rep.cauta("g");
    assert(poz==-1);
    cont.adauga_in_lista(rep, "g", "h", "a", 3);
    assert(cont.get_numar_oferte(rep)==3);
    cont.undo();
    assert(cont.get_numar_oferte(rep)==2);
    Oferta of2=cont.oferta_cu_poz(rep,1);
    assert(of2.get_denumire()=="d");
    std::vector<Oferta>ls=cont.get_lista_repo(rep);
    assert(ls.size()==2);
    ExceptionRepo rep1{1};
    try{
        cont.adauga_in_lista(rep1, "g", "h", "a", 3);
        assert(false);
    }
    catch(const ExceptieRepository& err){
        assert(true);
        assert(err.get_mesaj_eroare()=="GHINION!");
    }
    ExceptionRepo rep2{0};
    cont.citeste_fisier_repo(rep,"test2.txt");
    assert(cont.get_numar_oferte(rep)==2);
    cont.salveaza_fisier_repo(rep,"test2.txt");
    assert(cont.get_numar_oferte(rep)==0);
}
void toate_testele() {
	test_domain();
	test_repository();
	test_controller_ascm();
	test_controller_filtru();
	test_controller_sort();
	test_validare();
	test_VectorDinamic();
    test_wishlist();
    test_dictionar_controller();
    //test_repo_file();
    test_undo();
    test_exception_repo();
}