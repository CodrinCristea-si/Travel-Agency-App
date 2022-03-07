#pragma once
#include <string>
#include <exception>

class ExceptieRepository{
private:
    std::string mesaj="\0";
public:

    /*
     * constructor de clasa
     * mesaj_eroare de tip string
     */
    ExceptieRepository(std::string mesaj_eroare){
        this->mesaj=mesaj_eroare;
    }

    /*
     * constructor de clasa default
     */
    ExceptieRepository()=default;

    /*
     * aceatsa functie returneaza mesajul de eroare al obiectului
     */
    std::string get_mesaj_eroare() const{
        return this->mesaj;
    }
};

class ExceptieValidare{
private:
    int cod=0;
    std::string mesaj="\0";
public:
    /*
     * constructor de clasa
     * mesaj_eroare de tip string
     * cod de tip int
     */
    ExceptieValidare(int cod,std::string mesaj_eroare);

    /*
     * constructor de clasa default
     */
    ExceptieValidare()=default;

    /*
     * aceatsa functie returneaza mesajul de eroare al obiectului
     */
    std::string get_mesaj_eroare() const{
        return this->mesaj;
    }

    /*
     * aceatsa functie returneaza codul de eroare al obiectului
     */
    int get_cod()const noexcept {
        return this->cod;
    }
};