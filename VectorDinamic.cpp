#include "VectorDinamic.h"
/*
VectorDinamic::VectorDinamic() {
	this->cap = memorie_initializare;
	this->lung = { 0 };
	this->elemente = new Oferta[memorie_initializare];
}
//IteratorVectorDinamic(const VectorDinamic& vector) : vect{ vector } {};
void VectorDinamic::push_back(const Oferta of) {
	if (this->lung == this->cap)this->redimensionare(2*this->cap);
	elemente[lung] = of;
	lung++;
}
VectorDinamic::VectorDinamic(const VectorDinamic& ot) {
	lung = ot.lung;
	cap = ot.cap;
	elemente = new Oferta[ot.cap];
	for (unsigned int i = 0; i < ot.lung; i++)
		elemente[i] = ot.elemente[i];
}

VectorDinamic& VectorDinamic::operator=(VectorDinamic& ot) {
	if (this == &ot)
		return *this;
	delete[] elemente;
	elemente = ot.elemente;
	lung = ot.lung;
	cap = ot.cap;
	ot.elemente = nullptr;
	ot.lung = 0;
	ot.cap = 0;
	return *this;
}

void VectorDinamic::redimensionare(const int dimensiune) {
	Oferta* elemente_noi = new Oferta[dimensiune];
	if(elemente_noi!=nullptr)
	for (unsigned int i = 0; i<this->lung; i++)
		elemente_noi[i] = elemente[i];
	delete[] elemente;
	this->elemente = elemente_noi;
	this->cap = dimensiune;
}

void VectorDinamic::erase(const int poz) {
	for (unsigned int i = poz; i < this->lung - 1; i++)
		elemente[i] = elemente[i + 1];
	lung--;
	if (lung <= cap / 2 && cap > memorie_initializare)redimensionare(cap / 2);
}
IteratorVectorDinamic VectorDinamic::begin()const
{
	return IteratorVectorDinamic(*this, 0); 
}
//IteratorVectorDinamic& begin();
IteratorVectorDinamic VectorDinamic::end()const
{
	return IteratorVectorDinamic(*this, lung); 
}
*/
//IteratorVectorDinamic VectorDinamic::begin() {
//	return IteratorVectorDinamic(*this);
//}
//IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& vector, const unsigned int valoare_pozitie) {
//	vect = vector;
//	poz =valoare_pozitie;
//}