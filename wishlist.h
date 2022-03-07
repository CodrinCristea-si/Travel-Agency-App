#pragma once
#include "Repository.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using std::vector;using std::string;

class Wishlist :public Repository{
public:
    /*
     * aceasta functie elibereaza toate elementele din cos
     */
    void sterge_tot()noexcept {
        lista.clear();
    }
    /*
     * aceasta functie salveaza elementele din cos intr-un fisier
     * fis de tip string
     */
    void salveaza(string nume_fisier);
};


