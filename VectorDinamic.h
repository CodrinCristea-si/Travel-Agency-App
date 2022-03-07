#pragma once
#include "Oferta.h"
#include <vector>
#define memorie_initializare 5
template <typename Element>
class IteratorVectorDinamic;
template <typename Element>
class VectorDinamic
{
private:
	unsigned int cap;
	unsigned int lung;
	Element* elemente;
public:
	friend class IteratorVectorDinamic<Element>;
	///contructor 
	VectorDinamic<Element>();// :cap{ memorie_initializare }, lung{ 0 }, elemente{ new Oferta[memorie_initializare] }{};

	///contructor de copiere
	VectorDinamic<Element>(const VectorDinamic& ot);

	/*
	* supraincarcarea operatorului de asignare
	* ot - o referinta la obiectul VectorDinamic
	*/
	VectorDinamic<Element>& operator=(VectorDinamic<Element>& ot);

	/*
	* adauga un element pe ultima pozitie in VectorulDinamic
	* of- o copie a obiectului Element
	*/
	void push_back(const Element of);

	/*
	* realocarea spatiului de memorare a Vectorului Dinamic
	* dimensiune de tip int
	*/
	void redimensionare(const int dimensiune);

	/*
	* retruneaza numarul de elemente din Vector
	*/
	unsigned int size() const {
		return this->lung;
	}

	/*
	* retruneaza capacitatea maxima de memorare a Vectorului
	*/
	unsigned int capacity() const {
		return this->cap;
	}

	/*
	* retruneaza o referinta a obiectului Element de pe o anumita pozitie din vector
	* poz de tip int
	*/
	Element& get(const int poz)const {
		return elemente[poz];
	}

	/*
	* seteaza un element pe o anumita pozitie din lista
	* poz de tip int
	* of- o referinta a obiectului Element
	*/
	void set(const int poz, const Element& of) {
		elemente[poz] = of;
	}

	/*
	* sterge un element de pe o anumita pozitie din lista
	* poz de tip int
	*/
	void erase(int poz);

	/*
	* returneaza un interator care arata spre primul element din Vector
	*/
	IteratorVectorDinamic<Element> begin()const; 
	//IteratorVectorDinamic& begin();

	/*
	* returneaza un interator care arata spre ultimul element din Vector
	*/
	IteratorVectorDinamic<Element> end()const; 

	///destructor
	~VectorDinamic<Element>() {
		delete[] elemente;
	}
};
template <typename Element>
VectorDinamic<Element>::VectorDinamic() {
	this->cap = memorie_initializare;
	this->lung = { 0 };
	this->elemente = new Element[memorie_initializare];
}
//IteratorVectorDinamic(const VectorDinamic& vector) : vect{ vector } {};
template <typename Element>
void VectorDinamic<Element>::push_back(const Element of) {
	if (this->lung == this->cap)this->redimensionare(2 * this->cap);
	elemente[lung] = of;
	lung++;
}
template <typename Element>
VectorDinamic<Element>::VectorDinamic(const VectorDinamic<Element>& ot) {
	lung = ot.lung;
	cap = ot.cap;
	elemente = new Element[ot.cap];
	for (unsigned int i = 0; i < ot.lung; i++)
		elemente[i] = ot.elemente[i];
}
template <typename Element>
VectorDinamic<Element>& VectorDinamic<Element>::operator=(VectorDinamic<Element>& ot) {
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
template <typename Element>
void VectorDinamic<Element>::redimensionare(const int dimensiune) {
	Element* elemente_noi = new Element[dimensiune];
	if (elemente_noi != nullptr)
		for (unsigned int i = 0; i < this->lung; i++)
			elemente_noi[i] = elemente[i];
	delete[] elemente;
	this->elemente = elemente_noi;
	this->cap = dimensiune;
}
template <typename Element>
void VectorDinamic<Element>::erase(const int poz) {
	for (unsigned int i = poz; i < this->lung - 1; i++)
		elemente[i] = elemente[i + 1];
	lung--;
	if (lung <= cap / 2 && cap > memorie_initializare)redimensionare(cap / 2);
}
template <typename Element>
class IteratorVectorDinamic {

private:
	//friend class VectorDinamic;
	const VectorDinamic<Element>& vect;
	unsigned int poz=0;

public:
	///constructor cu pozitie
	IteratorVectorDinamic<Element>(const VectorDinamic<Element>& vector, const unsigned int valoare_pozitie): vect{ vector } ,poz{valoare_pozitie} {};

	///constructor default
	IteratorVectorDinamic<Element>(const VectorDinamic<Element>& vector) : vect{ vector }{};

	/*
	* verifica daca iteratorul este valid
	* true daca este valid, false altfel
	*/
	bool valid()noexcept {
		if (poz >= 0 || poz < vect.size()) return true;
			return false;
	}

	/*
	* returneaza o referinta la elementul aratat de iterator
	*/
	Element& element()noexcept {
 		return vect.elemente[poz];
	}
	/*
	* seteaza iteratorul pe urmatorul element din Vector
	*/
	void urmator() noexcept {
		poz++;
	}

	/*
	* supraincarcarea operatorului * cu acelasi rol ca si functia element() 
	*/
	Element& operator*()noexcept { return element();}

	/*
	* supraincarcarea operatorului ++ cu acelasi rol ca si functia urmator()
	*/
	IteratorVectorDinamic<Element>& operator++() noexcept {
		urmator();
		return *this;
	}

	/*
	* supraincarcarea operatorului != care verifica inegalitatea dintre doi iteratori
	*/
	bool operator!=(const IteratorVectorDinamic<Element>& it) {
		return poz != it.poz;
	}
	//std::vector<int>


};
template <typename Element>
IteratorVectorDinamic<Element> VectorDinamic<Element>::begin()const
{
	return IteratorVectorDinamic<Element>(*this, 0);
}
//IteratorVectorDinamic& begin();
template <typename Element>
IteratorVectorDinamic<Element> VectorDinamic<Element>::end()const
{
	return IteratorVectorDinamic<Element>(*this, lung);
}