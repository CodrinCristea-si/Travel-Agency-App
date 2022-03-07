#include "Repository.h"

 Oferta& Repository::get_oferta_cu_pozitie(const int poz ){
	if (poz<0 || poz>this->numar_elemente() - 1) throw ExceptieRepository("Pozitie invalida!");
	return lista.at(poz);
}
void Repository::adauga(const Oferta& of) {
	this->lista.push_back(of);
}
void Repository::adauga_pe_pozitie(const int poz,const Oferta& of) {
	if (poz<0 || poz>this->numar_elemente() - 1) throw ExceptieRepository("Pozitie invalida!");
	this->lista.at(poz)=of;
}

void Repository::sterge(const std::string& denumire) {
	const int poz = this->cauta(denumire);
	if (poz == -1) throw ExceptieRepository("Pozitie invalida!");
	else this->lista.erase(lista.begin()+poz);
}
int Repository::cauta(const std::string& denumire){
    if (std::any_of(lista.begin(),lista.end(),[denumire](const Oferta& of){return of.get_denumire()==denumire;})){
	    auto it=std::find_if(lista.begin(),lista.end(),[denumire](const Oferta& of){return of.get_denumire()==denumire;});
	return it-lista.begin();}
    return -1;
}
void Repository::citeste_repo(std::string fis){
    std::ifstream fin(fis);
    std::string denumire,destinatie,tip;
    float pret=0;
    std::string text;
    const std::string delimitator=":";
    std::vector<std::string>cuvinte;
    while(fin>>text){
        //std::cout<<text<<std::endl;
        int poz=0;
        while(poz!=std::string::npos){
            poz=text.find(delimitator);
            std::string cuvant=text.substr(0,poz);
            cuvinte.push_back(cuvant);
            text.erase(0,poz+delimitator.size());
        }
        denumire=cuvinte.at(0);
        destinatie=cuvinte.at(1);
        tip=cuvinte.at(2);
        pret=std::stof(cuvinte.at(3));
        Oferta of{denumire,destinatie,tip,pret};
        lista.push_back(of);
        cuvinte.clear();
    }
    fin.close();
}

void Repository:: salveaza_repo(std::string fis){
    std::ofstream fout(fis,std::ios_base::out);
    while(!lista.empty()){
        const int poz = 0;
        const Oferta& of=lista.at(0);
        fout<<of.get_denumire()<<":"<<of.get_destinatie()<<":"<<of.get_tip()<<":"<<of.get_pret()<<std::endl;
        lista.erase(lista.begin()+poz);
    }
    fout.close();
}
/*
void RepositoryFile::adauga(const Oferta &of) {
    std::ofstream fisier(nume_fisier,std::ios_base::app);
    fisier<<of.get_denumire()<<":"<<of.get_destinatie()<<":"<<of.get_tip()<<":"<<of.get_pret()<<std::endl;
    numar++;
    fisier.close();
}

int RepositoryFile::cauta(const std::string& denumire) {
    std::ifstream fisier(nume_fisier);
    const std::string delimitator=":";
    std::vector<std::string>cuvinte;
    string text;
    std::string denumire_fis;
    int pozitie=-1;
    int contor=0;
    while(fisier>>text) {
        int poz = 0;
        while (poz != std::string::npos) {
            poz = text.find(delimitator);
            std::string cuvant = text.substr(0, poz);
            cuvinte.push_back(cuvant);
            text.erase(0, poz + delimitator.size());
        }
        denumire_fis = cuvinte.at(0);
        if (denumire==denumire_fis){
            pozitie=contor;
            break;
        }
        cuvinte.clear();
        contor++;
    }
    fisier.close();
    return pozitie;
}

void RepositoryFile::sterge(const std::string& denumire) {
    const int poz = this->cauta(denumire);
    if (poz == -1) throw ExceptieRepository("Pozitie invalida!");
    std::ifstream fisier(nume_fisier);
    std::ofstream fisier_aux(nume_fisier_auxiliar);
    string text;
    int contor=0;
    while(fisier>>text) {
        if(contor!=poz){
            fisier_aux<<text<<std::endl;
        }
        contor++;
    }
    numar--;
    fisier.close();
    fisier_aux.close();
    copiaza_fisiere();
}
void RepositoryFile::copiaza_fisiere(){
    std::ofstream fisier(nume_fisier);
    std::ifstream fisier_aux(nume_fisier_auxiliar);
    string text;
    while(fisier_aux>>text)
        fisier<<text<<std::endl;
    fisier.close();
    fisier_aux.close();
}

std::vector<Oferta>& RepositoryFile::get_lista() {
    if (!lista.empty())lista.clear();
    std::ifstream fisier(nume_fisier);
    //std::vector<Oferta> lista;
    std::string denumire,destinatie,tip;
    float pret=0;
    std::string text;
    const std::string delimitator=":";
    std::vector<std::string>cuvinte;
    while(fisier>>text){
        int poz=0;
        while(poz!=std::string::npos){
            poz=text.find(delimitator);
            std::string cuvant=text.substr(0,poz);
            cuvinte.push_back(cuvant);
            text.erase(0,poz+delimitator.size());
        }
        denumire=cuvinte.at(0);
        destinatie=cuvinte.at(1);
        tip=cuvinte.at(2);
        pret=std::stof(cuvinte.at(3));
        Oferta of{denumire,destinatie,tip,pret};
        lista.push_back(of);
        cuvinte.clear();
    }
    fisier.close();
    return lista;
}

Oferta& RepositoryFile::get_oferta_cu_pozitie(const int poz){
    if (poz<0 || poz>this->numar_elemente() - 1) throw ExceptieRepository("Pozitie invalida!");
    std::ifstream fisier(nume_fisier);
    std::string denumire,destinatie,tip;
    float pret=0;
    std::string text;
    const std::string delimitator=":";
    std::vector<std::string>cuvinte;
    int contor=0;
    Oferta of;
    while(fisier>>text) {
        if(contor==poz){
            int pozi=0;
            while(pozi!=std::string::npos){
                pozi=text.find(delimitator);
                std::string cuvant=text.substr(0,pozi);
                cuvinte.push_back(cuvant);
                text.erase(0,pozi+delimitator.size());
            }
            denumire=cuvinte.at(0);
            destinatie=cuvinte.at(1);
            tip=cuvinte.at(2);
            pret=std::stof(cuvinte.at(3));
            of.set_denumire(denumire);
            of.set_destinatie(destinatie);
            of.set_tip(tip);
            of.set_pret(pret);

        }
        contor++;
    }
    lista_of.push_back(of);
    fisier.close();
    return lista_of.at(lista_of.size()-1);
}

int RepositoryFile::numar_elemente() const {
    std::ifstream fisier(nume_fisier);
    string text;
    int contor=0;
    while(fisier>>text) {
        contor++;
    }
    fisier.close();
    return contor;
}
*/
void ExceptionRepo::adauga(const Oferta& of){
    int prob=rand()%100+1;
    if (prob<=probabilitate*100) throw ExceptieRepository("GHINION!");
    if(lista.find(of.get_denumire())==lista.end()){
        lista[of.get_denumire()]=of;
    }
}
void ExceptionRepo::sterge(const string& denumire){
    int prob=rand()%100+1;
    if (prob<=probabilitate*100) throw ExceptieRepository("GHINION!");
    const int poz = this->cauta(denumire);
    if (poz == -1) throw ExceptieRepository("Pozitie invalida!");
    else this->lista.erase(denumire);
}

int ExceptionRepo::cauta(const string& denumire) {
    int prob=rand()%100+1;
    if (prob<=probabilitate*100) throw ExceptieRepository("GHINION!");
    int poz=-1;
    if(lista.find(denumire)==lista.end()){
        return -1;
    }
    else {
        int contor=0;
        for ( const auto& [cheie,val]:lista){
           if(cheie==denumire){poz=contor;
               break;}
           contor++;
        }
        return contor;
    }
}

std::vector<Oferta>& ExceptionRepo::get_lista() {
    int prob=rand()%100+1;
    if (prob<=probabilitate*100) throw ExceptieRepository("GHINION!");
    lista_of.clear();
    for ( const auto& [cheie,val]:lista)
        lista_of.push_back(val);
    return lista_of;
}
Oferta& ExceptionRepo::get_oferta_cu_pozitie(const int poz){
    int prob=rand()%100+1;
    if (prob<=probabilitate*100) throw ExceptieRepository("GHINION!");
    Oferta of;
    int contor=0;
    for ( const auto& [cheie,val]:lista) {
        if (contor == poz) {
            of = lista[cheie];
            break;
        }
        contor++;
    }
    lista_junk.push_back(of);
    return lista_junk[lista_junk.size()-1];
}

void ExceptionRepo::citeste_repo(std::string fis){
    std::ifstream fin(fis);
    std::string denumire,destinatie,tip;
    float pret=0;
    std::string text;
    const std::string delimitator=":";
    std::vector<std::string>cuvinte;
    while(fin>>text){
        //std::cout<<text<<std::endl;
        int poz=0;
        while(poz!=std::string::npos){
            poz=text.find(delimitator);
            std::string cuvant=text.substr(0,poz);
            cuvinte.push_back(cuvant);
            text.erase(0,poz+delimitator.size());
        }
        denumire=cuvinte.at(0);
        destinatie=cuvinte.at(1);
        tip=cuvinte.at(2);
        pret=std::stof(cuvinte.at(3));
        Oferta of{denumire,destinatie,tip,pret};
        lista[denumire]=of;
        cuvinte.clear();
    }
    fin.close();
}

void ExceptionRepo::salveaza_repo(std::string fis){
    std::ofstream fout(fis);
    for ( const auto& [cheie,val]:lista) {
        fout<<val.get_denumire()<<":"<<val.get_destinatie()<<":"<<val.get_tip()<<":"<<val.get_pret()<<std::endl;
    }
    fout.close();
    lista.clear();
}
