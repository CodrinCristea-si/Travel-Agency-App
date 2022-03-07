#pragma once
#include <string>
#include <iostream>
class Oferta
{
private:
	std::string denumire;
 	std::string destinatie;
	std::string tip;
	float pret=0;
public:
	/* constructor de copiere
	* of- referinta la obiectul Oferta
	*/
	Oferta(const Oferta& of) {
		denumire= of.denumire ;
		destinatie= of.destinatie ;
		tip= of.tip;
		pret= of.pret;
		std::cout << "copie"<<std::endl;
	}
	///Getters
	///retruneaza campul denumire al obiectului oferta
	std::string get_denumire()const {
		return this->denumire;
	}
	///retruneaza campul dstinatie obiectului oferta
	std::string get_destinatie()const {
		return this->destinatie;
	}
	///retruneaza campul tip al obiectului oferta
	std::string get_tip()const {
		return this->tip;
	}
	///retruneaza campul pret al obiectului oferta
	float get_pret()const noexcept{
		return this->pret;
	}
	///Setters
	///modificarea campului denumire al obiectului oferta
	/// denumir- de tip string
	void set_denumire(const std::string& denumir) {
		this->denumire = denumir;
	}
	///modificarea campului destinatie al obiectului oferta
	/// destinati- de tip string
	void set_destinatie(const std::string& destinati) {
		this->destinatie = destinati;
	}
	///modificarea campului tip al obiectului oferta
	/// ti- de tip string
	void set_tip(const std::string& ti) {
		this->tip = ti;
	}
	///modificarea campului pret al obiectului oferta
	/// pre- de tip float
	void set_pret(const float pre)noexcept {
		this->pret = pre;
	}

	///construnctor personalizat
	Oferta(const std::string& denumire, const std::string& destinatie, const std::string& tip, const float pret);
	
	///constructor default
	Oferta() = default;
	
	//~Oferta();
};

