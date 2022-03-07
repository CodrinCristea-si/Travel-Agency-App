#include "Oferta.h"
Oferta::Oferta(const std::string& denumire,const std::string& destinatie, const std::string& tip,const float pret) {
	this->denumire = denumire;
	this->destinatie = destinatie;
	this->tip = tip;
	this->pret = pret;
}

//Oferta::~Oferta() {
	//this->denumire ='\0';
	//this->destinatie ='\0';
	//this->tip = '\0';
	//this->pret =NULL;
//}