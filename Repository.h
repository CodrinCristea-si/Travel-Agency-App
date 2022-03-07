#pragma once
#include "Oferta.h"
#include "VectorDinamic.h"
#include "exceptii.h"
#include <string>
#include <vector>
#include <exception>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>

using std::string;

class AbstractRepo{
public:
    virtual void adauga(const Oferta& of)=0;
    virtual void sterge(const std::string& denumire)=0;
    virtual int cauta(const std::string& denumire)=0;
    virtual int numar_elemente()=0;
    virtual std::vector<Oferta>& get_lista()=0;
    virtual Oferta& get_oferta_cu_pozitie(const int poz)=0;
    virtual void salveaza_repo(string fis)=0;
    virtual void citeste_repo(string fis)=0;
    virtual ~AbstractRepo(){};
};
class Repository: public AbstractRepo
{
//VectorDinamic<Oferta> lista;

protected:
//friend class Oferta;
std::vector<Oferta>lista;
public:
	Repository() noexcept {};

	Repository(const Repository& rep)=delete;
	/*
	* retunrneaza o referinta la obiectul oferta de pe o anumita pozitie din lista
	* poz de tip int
	*/
	virtual Oferta& get_oferta_cu_pozitie(const int poz)override;

	/*
	* retunrneaza numarul de oferte din lista
	*/
	virtual int numar_elemente()override{
		return lista.size();
	}

    /*
    * adauga o oferta pe o anumita pozitie din lista
    * of-referinta la obiectul Oferta
    * poz de tip int
    */
	void adauga_pe_pozitie(const int poz,const Oferta& of);

	/*
	* cauta o oferta in lista
	* denumire-de tip string
	* returneaza pozitia in lista la care se afla obiectul cu denumirea respectiva
	*/
	virtual int cauta(const std::string& denumire) override;

	/*
	* sterge o oferta din lista
	* denumire-de tip string
	*/
	virtual void sterge(const std::string& denumire)override;

	/*
	 * aceatsa functie returneaza lista de oferte
	 */
	virtual std::vector<Oferta>& get_lista() override{
	    return lista;
	}

    /*
    * adauga o oferta la sfarsitul listei
    * of-referinta la obiectul Oferta
    */
    virtual void adauga(const Oferta& of)override;

    /*
     * aceatsa functie salveaza datele din lista intr-un fisier
     * fis de tip string
     */
    virtual void salveaza_repo(std::string fis)override;

    /*
     * aceatsa functie citeste datele dintr-un fisier si le adauga in lista
     * fis de tip string
     */
    virtual void citeste_repo(std::string fis)override;
};
/*
class RepositoryFile:public Repository{
private:
    int numar=0;
    string nume_fisier;
    string nume_fisier_auxiliar="auxi.txt";
    std::vector<Oferta> lista_of;
    //std::vector<Oferta> lista;
    void copiaza_fisiere();
public:
    RepositoryFile(string nume):nume_fisier{nume}{};
    RepositoryFile(const RepositoryFile& ot)=delete;

    void adauga(const Oferta& of);

    void sterge(const std::string& denumire);

    int cauta(const std::string& denumire);

    int numar_elemente() const ;

    std::vector<Oferta>& get_lista() ;

    Oferta& get_oferta_cu_pozitie(const int poz);

};
*/
class ExceptionRepo:public AbstractRepo{
private:
    float probabilitate=0;
    std::map<std::string,Oferta> lista;
    std::vector<Oferta> lista_of;
    std::vector<Oferta> lista_junk;
public:

    ExceptionRepo(const float prob): probabilitate{prob}{
        srand((unsigned)time(nullptr));

    };

    void adauga(const Oferta& of)override;

    void sterge(const std::string& denumire)override;

    int cauta(const std::string& denumire)override;

    int numar_elemente() override{
        int prob=rand()%100+1;
        if (prob<=probabilitate*100) throw ExceptieRepository("GHINION!");
        return lista.size();
    }

    std::vector<Oferta>& get_lista()override;

    Oferta& get_oferta_cu_pozitie(const int poz)override;

    void salveaza_repo(string fis)override;

    void citeste_repo(string fis)override;
};