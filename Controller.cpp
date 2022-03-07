#include "Controller.h"
//#include "Repository.h"
#include <iostream>
#include <random>
#include <ctime>
#include <memory>
//#include <gsl/gsl_util>

void Controller::adauga_in_lista(AbstractRepo& rep, const std::string& denumire, const std::string& destinatie, const std::string& tip, const float pret){
	Oferta of(denumire, destinatie, tip, pret);
	rep.adauga(of);
	undo_lista.push_back(std::make_unique<UndoAdauga>(rep,of));
	aresteaza();
	//return rep;
}
void Controller::sterge_din_lista(AbstractRepo& rep, const std::string& denumire){
    const int poz=rep.cauta(denumire);
    Oferta of=rep.get_oferta_cu_pozitie(poz);
	rep.sterge(denumire);
    undo_lista.push_back(std::make_unique<UndoSterge>(rep,of));
    aresteaza();
	//return rep;
}

int Controller::cauta_in_lista(AbstractRepo& rep,const std::string& denumire){
	return rep.cauta(denumire);

}

void Controller::modifica(AbstractRepo& rep,const std::string& denumire, const int optiune, const std::string& schimb) {
	const int poz = rep.cauta(denumire);
	Oferta of = rep.get_oferta_cu_pozitie(poz);
	Oferta copie=of;
	if (optiune == 1) {
		of.set_denumire(schimb);
	}
	else if (optiune == 2) {
		of.set_destinatie(schimb);
	}
	else if (optiune == 3) {
		of.set_tip(schimb);
	}
	else if (optiune == 4) {
		of.set_pret(std::stof(schimb));
	}
	rep.sterge(copie.get_denumire());
	rep.adauga(of);
	undo_lista.push_back(std::make_unique<UndoModifica>(rep,of,copie));
    aresteaza();
}

Oferta& Controller::oferta_cu_poz(AbstractRepo& rep, const int poz){
	return rep.get_oferta_cu_pozitie(poz);
}

vector<Oferta> Controller::filtru(AbstractRepo& rep,const std::string& filt,FuncFilt func)const {
	vector<Oferta> filtr(rep.numar_elemente());
	std::cout<<filtr.size()<<endl;
	auto lista=rep.get_lista();
    std::cout<<lista.size()<<endl;
	auto it=std::copy_if(lista.begin(),lista.end(),filtr.begin(),[filt,func](const Oferta& of){return func(of,filt);});
    filtr.resize(std::distance(filtr.begin(),it));
	return filtr;
}

vector<Oferta> Controller::sortare(AbstractRepo& rep,const bool rev, FuncSort func)const{
	vector<Oferta> sorta=rep.get_lista();
	std::sort(sorta.begin(),sorta.end(),func);
	if (!rev)
	    reverse(sorta.begin(),sorta.end());
	return sorta;
}

int Controller::validare(AbstractRepo& rep, const std::string& denumire, const std::string& destinatie,const std::string& tip,const std::string& pret)const {
    //cout<<pret<<endl;
    if(std::any_of(pret.begin(),pret.end(),[](char c){return !(c>='0'&&c<+'9'|| c=='-'|| c==' '||c=='.');}))throw ExceptieValidare(9,"Pretul nu trebuie sa contina litere");
    if (pret == "")throw ExceptieValidare(9,"Pretul nu trebuie sa fie vid");
    if (stof(pret) <= 0)throw ExceptieValidare(1,"Pretul nu trebuie sa fie negativ");
	if (denumire == "")throw ExceptieValidare(2,"Denumirea nu trebuie sa fie vida");
	if (destinatie == "")throw ExceptieValidare(3,"Destinatia nu trebuie sa fie vida");
	if (tip == "")throw ExceptieValidare(4,"Tipul nu trebuie sa fie vid");
    if(std::any_of(denumire.begin(),denumire.end(),[](char c){return c>='0'&&c<+'9';})) throw ExceptieValidare(5,"Denumirea nu trebuie sa contina cifre");
	if(std::any_of(destinatie.begin(),destinatie.end(),[](char c){return c>='0'&&c<+'9';}))throw ExceptieValidare(6,"Destinatia nu trebuie sa contina cifre");
    if(std::any_of(tip.begin(),tip.end(),[](char c){return c>='0'&&c<+'9';})) throw ExceptieValidare(7,"Tipul nu trebuie sa contina cifre");
	if (rep.cauta(denumire) != -1) throw ExceptieValidare(8,"Oferta se afla deja in baza de date");
	return 0;
}
void Controller::adauga_oferta_in_wishlist(Wishlist& wish,const Oferta& of){
    //Oferta& of= oferta_cu_poz(rep,rep.cauta(denumire));
    wish.adauga(of);
    aresteaza();
}
void Controller::sterge_tot_wishlist(Wishlist& wish){
    wish.sterge_tot();
    aresteaza();
}
void Controller:: salveaza_fisier_wish(Wishlist& wish,string fis){
    wish.salveaza(fis);
}
void Controller::genereaza_wishlist(Wishlist& wish,AbstractRepo& rep,int nr_of){
    srand((unsigned)time(nullptr));
    if(nr_of==get_numar_oferte(rep)){
        for (auto& el: rep.get_lista())
            wish.adauga(el);
        nr_of=0;
    }
    vector<int>alese;
    while (nr_of>0){
        bool gasit=false;
        int poz=-1;
        while(gasit==false) {
            gasit=false;
            const int optiune = rand() % (rep.numar_elemente()-1);
            for (auto el:alese){
                if(el==optiune){gasit=true;
                    break;}
            }
            if (!gasit){poz=optiune;
                break;}
            else gasit=false;
        }
        alese.push_back(poz);
        const Oferta& of=rep.get_oferta_cu_pozitie(poz);
        wish.adauga(of);
        nr_of--;
    }
    aresteaza();
}

void Controller:: salveaza_fisier_repo(AbstractRepo& rep,string fis){
    rep.salveaza_repo(fis);
}

void Controller:: citeste_fisier_repo(AbstractRepo & rep,string fis){
    rep.citeste_repo(fis);
}
std::map<string,std::pair<string,int>> Controller::dictionar(AbstractRepo& rep){
    std::map<string,std::pair<string,int>> lista;
    for (const auto& el:rep.get_lista()){
        if(lista.find(el.get_tip())!=lista.end()){
            lista[el.get_tip()].second++;
        }
        else {
            lista[el.get_tip()]=std::make_pair(el.get_tip(),1);
        }
    }
    return lista;
}

void Controller::undo(){
    if (undo_lista.empty()) throw ExceptieRepository("Undo nerealizabil!");
    undo_lista.back()->doUndo();
    undo_lista.pop_back();
    aresteaza();
}